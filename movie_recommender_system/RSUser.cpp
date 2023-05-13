
// don't change those includes
#include "RSUser.h"

#include <utility>
#include "RecommenderSystem.h"


// implement your cpp code here
RSUser::RSUser (std::string& name, rank_map& rm,
                std::shared_ptr<RecommenderSystem>& ptr_rs)
{
  _name = name;
  _rm = rm;
  _ptrs = ptr_rs;
}

std::string RSUser::get_name () const
{
  return _name;
}

rank_map RSUser::get_ranks () const
{
  return this->_rm;
}

void RSUser::add_movie_to_rs (const std::string &name, int year,
                              const std::vector<double> &features,
                              double rate)
{
  if ( rate < MIN_RATE || rate > MAX_RATE){
      throw std::range_error("rate should be 1-10");
    }
  sp_movie new_movie = std::make_shared<Movie>(Movie(name, year));
  this->_ptrs->add_movie (name, year, features);
  this->_rm[new_movie] = rate;
}

sp_movie RSUser::get_recommendation_by_content () const
{
  return this->_ptrs->recommend_by_content(*this);
}

sp_movie RSUser::get_recommendation_by_cf (int k) const
{
  return this->_ptrs->recommend_by_cf(*this, k);
}


double RSUser::get_prediction_score_for_movie (const std::string &name,
                                               int year, int k) const
{
  const sp_movie m(new Movie(name,year));
  return this->_ptrs->predict_movie_score(*this, m, k);
}
std::ostream &operator<< (std::ostream &s, const RSUser &user)
{
  std::cout << "name: " << user._name << std::endl;
  std::cout << *user._ptrs << std::endl;
  return s;
}
