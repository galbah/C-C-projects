#include "HashMap.hpp"

// error class that inherits from invalid_argument
class InvalidKey: public std::invalid_argument {
 public:

  // constructors
  explicit InvalidKey ()
      : std::invalid_argument ("")
  {};

  explicit InvalidKey (const std::string &msg)
      : std::invalid_argument (msg)
  {};

};

class Dictionary: public HashMap<std::string, std::string> {

 public:

  using HashMap<std::string, std::string>::HashMap;

  /** adds the elements between begin iterator to end iterator
   * to the dictionary
   * @tparam Itr iterator type */
  template<typename Itr>
  void update (Itr begin, Itr end)
  {
    for (Itr itr = begin; itr != end; itr++)
      {
        force_insert (itr->first, itr->second);
      }
  }

  /** erases the pair that contains given key
   * @return true if element was erased, error otherwise */
  virtual bool erase (std::string key)
  {
    if (HashMap::erase (key)){
        return true;
      }
    else{
        throw InvalidKey ("element doesnt exist");
      }
  }
};