
#include <memory>
#include "RSUsersLoader.h"

std::vector<RSUser>
RSUsersLoader::create_users_from_file (const std::string& users_file_path,
                   std::unique_ptr<RecommenderSystem> rs) noexcept (false)
{
  std::vector<RSUser> users;
  std::fstream new_file;
  std::string line, word, m_name, year_str, u_name;
  std::shared_ptr<RecommenderSystem> rs_shared =
          std::shared_ptr<RecommenderSystem>(std::move(rs));
  int year, grade, i = 0;
  new_file.open (users_file_path, std::ios::in);
  if (!new_file.is_open ()){
      throw std::runtime_error("file didnt open");
    }
  std::getline (new_file, line);  // movies line
  std::vector<sp_movie> movies;
  sp_movie temp;
  std::istringstream iss1 (line);
  while (iss1 >> word)
    {
      std::istringstream iss2 (word);
      std::getline (iss2, m_name, '-');
      std::getline (iss2, year_str);
      year = std::stoi (year_str);
      temp = rs_shared->get_movie (m_name, year);
      if(temp != nullptr){
          movies.push_back (temp);
        }
    }
  while (std::getline (new_file, line)) // users
    {
      std::istringstream iss3 (line);
      iss3 >> u_name;
      rank_map rm (0, sp_movie_hash, sp_movie_equal);
      while (iss3 >> word)
        {
          if (word == "NA"){
              rm.insert ({movies[i], 0});
            }
          else{
              grade = std::stoi (word);
              if ( grade < MIN_RATE || grade > MAX_RATE){
                  throw std::range_error("grade should be 1-10");
                }
              rm.insert ({movies[i], grade});
            }
          i++;
        }
      users.push_back(RSUser(u_name, rm, rs_shared));
      i = 0;
    }
  return users;
}