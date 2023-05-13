#include "RecommenderSystemLoader.h"


sp_rs RecommenderSystemLoader::create_rs_from_movies_file
      (const std::string &movies_file_path) noexcept (false)
{
  sp_rs ptrs (new RecommenderSystem());
  std::ifstream new_file;
  new_file.open (movies_file_path, std::ios::in);
  if (!new_file.is_open ())
    {
      throw std::runtime_error("file didnt open") ;
    }
  std::string movie_id, name, year_str, line;
  int year;
  double val;
  std::vector<double> features;
  while (std::getline (new_file, line))
    {
      std::istringstream iss1(line);
      iss1 >> movie_id;
      while(iss1 >> val)
        {
          features.push_back (val);
        }
      std::istringstream iss2(movie_id);
      std::getline (iss2, name, '-');
      std::getline (iss2, year_str);
      year = std::stoi (year_str);
      ptrs->add_movie (name, year ,features);
      features.clear();
      iss2.clear ();
    }
  return ptrs;
}


