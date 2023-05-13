#include "RecommenderSystemLoader.h"
#include "RSUsersLoader.h"

int main(){
  Movie m("A",1999);
  std::cout << m << std::endl;
  auto rs = RecommenderSystemLoader::create_rs_from_movies_file("../RecommenderSystemLoader_input.txt");
  std::cout << *rs << std::endl;
  auto users = RSUsersLoader::create_users_from_file("../RSUsersLoader_input.txt",std::move(rs));
  std::cout << users[0] << std::endl;
}