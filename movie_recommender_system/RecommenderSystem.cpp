#include "RecommenderSystem.h"

#define FEATURES_SIZE 4
#define LOWEST_POS_GRADE -1

RecommenderSystem::RecommenderSystem ()
{
  this->_data = std::map<sp_movie, std::vector<double>,
                equal_func> (cmp_movie);
}


sp_movie RecommenderSystem::add_movie (const std::string &name,
                     int year, const std::vector<double> &features)
{
  for(auto const &elem : features)
    {
      if ( elem < MIN_RATE || elem > MAX_RATE){
          throw std::range_error("grade should be 1-10");
        }
    }
  sp_movie m_ptr (new Movie (name, year));
  this->_data[m_ptr] = features;
  return m_ptr;
}

sp_movie RecommenderSystem::recommend_by_content (const RSUser &user)
{
  rank_map rm = user.get_ranks ();
  double avg = get_rank_avg (rm);
  rank_map norm_rank_map (rm);
  std::unordered_map<sp_movie, double, hash_func, equal_func>::iterator itr;
  for (itr = rm.begin (); itr != rm.end (); itr++){
      if (itr->second != 0){
          norm_rank_map[itr->first] = itr->second - avg;
        }
    }
  std::vector<double> pref_vec;
  int vec_size = (int) this->_data.begin()->second.size();
  pref_vec.reserve (vec_size);
  for (int i = 0; i < vec_size; i++){
      pref_vec.push_back (0);
    }
  for (itr = norm_rank_map.begin (); itr != norm_rank_map.end (); itr++){
      if (itr->second != 0){
          pref_vec = vec_add_vec (pref_vec, mult_vec_scalar
          (itr->second, this->_data[itr->first]));
        }
    }
  double best_score = LOWEST_POS_GRADE, grade;
  sp_movie best_match;
  for (itr = norm_rank_map.begin (); itr != norm_rank_map.end (); itr++){
      if (itr->second == 0){
          grade = get_compare_grade (this->_data[itr->first], pref_vec);
          if (grade > best_score){
              best_score = grade;
              best_match = itr->first;
            }
        }
    }
  return best_match;
}

double RecommenderSystem::predict_movie_score (const RSUser &user,
                                             const sp_movie &movie, int k)
{
  std::vector<double> movie_fea = this->_data[movie];
  rank_map rm = user.get_ranks ();
  std::map<sp_movie, double> grade_comp_map;
  std::unordered_map<sp_movie, double, hash_func, equal_func>::iterator itr;
  for (itr = rm.begin (); itr != rm.end (); itr++)
    {
      if (itr->second != 0){
          grade_comp_map[itr->first] = get_compare_grade
              (movie_fea, this->_data[itr->first]);
        }
    }
  while ((int) grade_comp_map.size () > k)
    {
      delete_min(grade_comp_map);
    }
  double grade_sum = 0, grade_mult_sum = 0;
  for (auto const &m : grade_comp_map)
    {
      grade_sum += m.second;
      grade_mult_sum += rm[m.first] * m.second;
    }
  return (double) grade_mult_sum / grade_sum;
}

sp_movie RecommenderSystem::recommend_by_cf (const RSUser &user, int k)
{
  sp_movie best_match;
  double best_score = 0, cur_score;
  rank_map rm = user.get_ranks();
  std::unordered_map<sp_movie, double, hash_func, equal_func>::iterator itr;
  for (itr = rm.begin (); itr != rm.end (); itr++)
    {
      if (itr->second == 0)
        {
          cur_score = predict_movie_score (user, itr->first, k);
          if (cur_score > best_score)
            {
              best_score = cur_score;
              best_match = itr->first;
            }
        }
    }
  return best_match;
}

sp_movie RecommenderSystem::get_movie (const std::string &name, int year) const
{
  sp_movie temp (new Movie (name, year));
  auto itr = (this->_data).find (temp);
  if (itr == this->_data.end ())
    {
      return nullptr;
    }
  return itr->first;
}

std::ostream &operator<< (std::ostream &s, const RecommenderSystem &rs)
{
  for (auto const &m: rs._data)
    {
      std::cout << *m.first;
    }
  return s;
}

/** HELPER FUNCTIONS **/

double RecommenderSystem::get_rank_avg (rank_map rm)
{
  double sum = 0;
  int counter = 0;
  std::unordered_map<sp_movie, double, hash_func, equal_func>::iterator itr;
  for (itr = rm.begin (); itr != rm.end (); itr++)
    {
      if (itr->second != 0){
          sum += itr->second;
          counter++;
        }
    }
  return sum / counter;
}

std::vector<double> RecommenderSystem::mult_vec_scalar (double scalar,
                                      const std::vector<double> &vec)
{
  std::vector<double> res;
  res.reserve (vec.size ());
  for (double i: vec)
    {
      res.push_back (scalar * i);
    }
  return res;
}

double RecommenderSystem::get_compare_grade (std::vector<double> vec1,
                                       const std::vector<double> &vec2)
{
  double mult = 0, norm1 = 0, norm2 = 0, norm;
  for (int i = 0; i < (int) vec2.size (); i++)
    {
      mult += vec1[i] * vec2[i];
    }
  for (int i = 0; i < (int) vec2.size (); i++)
    {
      norm1 += pow (vec1[i], 2);
      norm2 += pow (vec2[i], 2);
    }
  norm1 = sqrt (norm1);
  norm2 = sqrt (norm2);
  norm = norm1 * norm2;
  return mult / norm;
}

std::vector<double>& RecommenderSystem::vec_add_vec(std::vector<double> &vec1,
                                           const std::vector<double> &vec2)
{
  for (int i = 0; i < (int) vec1.size (); i++)
    {
      vec1[i] += vec2[i];
    }
  return vec1;
}

void RecommenderSystem::delete_min (std::map<sp_movie, double> &map)
{
  double min_val;
  sp_movie min_key;
  bool is_first = true;
  for (auto const &elem: map)
    {
      if (is_first)
        {
          min_key = elem.first;
          min_val = elem.second;
          is_first = false;
        }
      else
        {
          if (elem.second < min_val)
            {
              min_val = elem.second;
              min_key = elem.first;
            }
        }
    }
  map.erase (min_key);
}