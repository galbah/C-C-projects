#include <iostream>
#include <vector>
#include "HashMap.hpp"
#include "Dictionary.hpp"

int main ()
{
  Dictionary d2 ({"a", "b", "c", "d", "e"}, {"A", "B", "C", "D", "E"});
  int counter = 0;
  auto beg = d2.begin();
  auto en = d2.end();
  return 0;
}