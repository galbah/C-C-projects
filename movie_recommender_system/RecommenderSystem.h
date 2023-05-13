
#ifndef RECOMMENDERSYSTEM_H
#define RECOMMENDERSYSTEM_H
#include "RSUser.h"
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>

typedef std::unique_ptr<RecommenderSystem> sp_rs;

class RecommenderSystem {

 private:

  std::map<sp_movie, std::vector<double>, equal_func> _data;
  equal_func cmp_movie = [] (const sp_movie &m1, const sp_movie &m2)
  { return (*m1) < (*m2); };

  // returns the average of all scored movies in rank map
  static double get_rank_avg (rank_map rm);

  // calculates the compare grade between 2 vectors
  static double get_compare_grade (std::vector<double> vec1,
                             const std::vector<double> &vec2);

  // multiplies every element of vector with scalar
  static std::vector<double> mult_vec_scalar (double scalar,
                                  const std::vector<double> &vec);

  // adds the second vec to the first and returns it
  static std::vector<double>& vec_add_vec (std::vector<double> &vec1,
                                  const std::vector<double> &vec2);

  // deletes the minimum element in the map (by value)
  static void delete_min (std::map<sp_movie, double> &map);

 public:

  explicit RecommenderSystem ();
  /**
   * adds a new movie to the system
   * @param name name of movie
   * @param year year it was made
   * @param features features for movie
   * @return shared pointer for movie in system
   */
  sp_movie add_movie (const std::string &name, int year,
                      const std::vector<double> &features);

  /**
   * a function that calculates the movie with highest score
   * based on movie features
   * @param ranks user ranking to use for algorithm
   * @return shared pointer to movie in system
   */
  sp_movie recommend_by_content (const RSUser &user);

  /**
   * a function that calculates the movie with highest predicted
   * score based on ranking of other movies
   * @param ranks user ranking to use for algorithm
   * @param k
   * @return shared pointer to movie in system
   */
  sp_movie recommend_by_cf (const RSUser &user, int k);

  /**
   * Predict a user rating for a movie given argument using item
   * cf procedure with k most similar movies.
   * @param user_rankings: ranking to use
   * @param movie: movie to predict
   * @param k:
   * @return score based on algorithm as described in pdf
   */
  double predict_movie_score (const RSUser &user, const sp_movie &movie,
                              int k);

  /**
   * gets a shared pointer to movie in system
   * @param name name of movie
   * @param year year movie was made
   * @return shared pointer to movie in system
   */
  sp_movie get_movie (const std::string &name, int year) const;

  /**
   * a print operator for recommender system
   * @param s output steam
   * @param rs recommender system that will be printed
   * @return the output stream to support chaining
   */
  friend std::ostream& operator<<(std::ostream &s,
                                  const RecommenderSystem& rs);

};


#endif //RECOMMENDERSYSTEM_H
