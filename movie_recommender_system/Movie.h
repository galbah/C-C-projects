
#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <vector>
#include <memory>

#define HASH_START 17

class Movie;

typedef std::shared_ptr<Movie> sp_movie; // smart pointer to movie

/**
 * those declarations and typedefs are given to you and should be used in
 * the exercise
 */
typedef std::size_t (*hash_func) (const sp_movie &movie);
typedef bool (*equal_func) (const sp_movie &m1, const sp_movie &m2);
std::size_t sp_movie_hash (const sp_movie &movie);
bool sp_movie_equal (const sp_movie &m1, const sp_movie &m2);

class Movie {
 private:
  std::string _name;
  int _year;

 public:
  /**
   * constructor
   * @param name: name of movie
   * @param year: year it was made
   */
  Movie (const std::string &name, int year);

  /**
   * returns the name of the movie
   * @return const ref to name of movie
   */
  std::string get_name() const;

  /**
   * returns the year the movie was made
   * @return year movie was made
   */
  int get_year() const;

  /**
   * operator< for two movies
   * @param rhs: right hand side
   * @param lhs: left hand side
   * @return returns true if (rhs.year) < lhs.year or (rhs.year == lhs.year
   * & rhs.name == lhs.name) else return false
   */
  bool operator< (const Movie& rhs);

  /**
   * operator<< for movie
   * @param os ostream to output info with
   * @param movie movie to output
   */
  friend std::ostream &operator<< (std::ostream &s, Movie &m);
};


#endif //MOVIE_H
