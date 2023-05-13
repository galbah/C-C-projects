#ifndef _HASHMAP_HPP_
#define _HASHMAP_HPP_

#include <iostream>
#include <vector>
#include <cmath>

#define MAP_CAP 16
#define UPPER_LOAD_FACTOR 0.75
#define LOWER_LOAD_FACTOR 0.25
#define CAP_DEVIDER 2

template<typename KeyT, typename ValueT>
class HashMap {

 protected:

  std::vector<std::pair<KeyT, ValueT>> *_data;
  int _capacity = MAP_CAP;
  int _size = 0;

  /** checks the load factor after an erase of elements.
   * if load factor is lower than boundary it divides map capacity by 2
   * and re-hashes all element again */
  void check_load_factor_erase ()
  {
    double load_factor = get_load_factor ();
    if (load_factor >= LOWER_LOAD_FACTOR)
      {
        return;
      }
    HashMap<KeyT, ValueT> temp (*this);
    delete[] _data;
    if (_size == 0)
      {
        _capacity = 1;
      }
    else
      {
        while (get_load_factor () < LOWER_LOAD_FACTOR)
          {
            _capacity /= CAP_DEVIDER;
          }
      }
    _data = new std::vector<std::pair<KeyT, ValueT>>[_capacity];
    for (int i = 0; i < temp._capacity; i++)
      {
        for (auto const &elem : temp._data[i])
          {
            _data[hash (elem.first)].push_back (
                std::make_pair (elem.first, elem.second));
          }
      }
  }

  /** checks the load factor after an add of elements.
   * if load factor is higher than boundary it expands map capacity by 2
   * and re-hashes all element again */
  void check_load_factor_add ()
  {
    double load_factor = get_load_factor ();
    if (load_factor <= UPPER_LOAD_FACTOR)
      {
        return;
      }
    HashMap<KeyT, ValueT> temp (*this);
    delete[] _data;
    while (get_load_factor () > UPPER_LOAD_FACTOR)
      {
        _capacity *= CAP_DEVIDER;
      }
    _data = new std::vector<std::pair<KeyT, ValueT>>[_capacity];
    for (int i = 0; i < temp._capacity; i++)
      {
        for (auto const &elem : temp._data[i])
          {
            _data[hash (elem.first)].push_back (
                std::make_pair (elem.first, elem.second));
          }
      }
  }

  // returns the hash value for specific key
  int hash (const KeyT &key) const
  {
    return std::hash<KeyT>{} (key) & (_capacity - 1);
  }

  /** inserts given key and value as a pair to map
   * if key already exists it replaces the value */
  void force_insert (KeyT key, ValueT val)
  {
    if (contains_key (key))
      {
        (*this)[key] = val;
      }
    else
      {
        _data[hash (key)].push_back (std::make_pair (key, val));
        _size++;
      }
  }

 public:

  class ConstIterator;
  typedef ConstIterator const_iterator;

  // constructor
  HashMap ()
  {
    _data = new std::vector<std::pair<KeyT, ValueT>>[MAP_CAP];
    for (int i = 0; i < MAP_CAP; i++)
      {
        _data[i] = std::vector<std::pair<KeyT, ValueT>> (0);
      }
  }

  //constructor with 2 vectors as arguments
  HashMap (const std::vector<KeyT> &key_vec,
           const std::vector<ValueT> &val_vec)
  {
    if (key_vec.size () != val_vec.size ())
      {
        throw std::runtime_error ("vectors should be in the same size");
      }
    _data = new std::vector<std::pair<KeyT, ValueT>>[MAP_CAP];
    for (int i = 0; i < (int) key_vec.size (); i++)
      {
        force_insert (key_vec[i], val_vec[i]);
        check_load_factor_add ();
      }
  }

  // copy constructor
  HashMap (const HashMap &hm)
  {
    _size = hm._size;
    _capacity = hm._capacity;
    _data = new std::vector<std::pair<KeyT, ValueT>>[hm._capacity];
    for (int i = 0; i < _capacity; i++)
      {
        for (auto const &elem : hm._data[i])
          {
            _data[i].push_back (std::make_pair (elem.first, elem.second));
          }
      }
  }

  // destructor
  virtual ~HashMap ()
  {
    delete[] _data;
  }

  int size () const
  {
    return _size;
  }

  int capacity () const
  {
    return _capacity;
  }

  bool empty () const
  {
    return _size == 0;
  }

  /** checks if given key is in map
   * @return true if key is in, false otherwise */
  bool contains_key (const KeyT key) const
  {
    for (auto const &pair : _data[hash (key)])
      {
        if (pair.first == key)
          {
            return true;
          }
      }
    return false;
  }

  /** inserts given key and value as a pair to map,
   * if key already exists it return false, true otherwise */
  bool insert (KeyT key, ValueT val)
  {
    if (contains_key (key))
      {
        return false;
      }
    _data[hash (key)].push_back (std::make_pair (key, val));
    _size++;
    check_load_factor_add ();
    return true;
  }

  /** a non const version
   * @return the value that matches the given key */
  ValueT &at (const KeyT &key)
  {
    for (auto &pair : _data[hash (key)])
      {
        if (pair.first == key)
          {
            return pair.second;
          }
      }
    throw std::runtime_error ("didnt find the key");
  }

  /** a const version
   * @return the value that matches the given key */
  ValueT at (const KeyT &key) const
  {
    for (auto &pair : _data[hash (key)])
      {
        if (pair.first == key)
          {
            return pair.second;
          }
      }
    throw std::runtime_error ("didnt find the key");
  }

  /** erases the pair matches to given key
   * @return false if key is not in map, true otherwise */
  virtual bool erase (KeyT key)
  {
    if (!contains_key (key))
      {
        return false;
      }
    int index = hash (key);
    for (int i = 0; i < (int) _data[index].size (); i++)
      {
        if (_data[index][i].first == key)
          {
            _data[index].erase (_data[index].begin () + i);
            _size--;
            break;
          }
      }
    check_load_factor_erase ();
    return true;
  }

  double get_load_factor () const
  {
    return (double) _size / _capacity;
  }

  // the size of the vector contains given key
  int bucket_size (const KeyT &key) const
  {
    if (contains_key (key))
      {
        return (int) _data[hash (key)].size ();
      }
    throw std::runtime_error ("didnt find key");
  }

  // returns the index of vector contains given key
  int bucket_index (const KeyT &key) const
  {
    return hash (key);
  }

  void clear () // clears all elements in map
  {
    for (int i = 0; i < _capacity; i++)
      {
        _data[i].clear ();
      }
    _size = 0;
  }

  /** deep copies the rhs hash map in to the current hash map (this) */
  HashMap &operator= (const HashMap &hm)
  {
    if (this == &hm)
      {
        return *this;
      }
    _capacity = hm._capacity;
    _size = hm._size;
    delete[] _data;
    _data = new std::vector<std::pair<KeyT, ValueT>>[hm._capacity];
    for (int i = 0; i < _capacity; i++)
      {
        for (auto const &elem : hm._data[i])
          {
            _data[i].push_back (std::make_pair (elem.first, elem.second));
          }
      }
    return *this;
  }

  /** a const version
   * @return the value matching given key */
  ValueT operator[] (const KeyT &key) const
  {
    if (this->contains_key (key))
      {
        for (auto const &pair : _data[hash (key)])
          {
            if (pair.first == key)
              {
                return pair.second;
              }
          }
      }
    return ValueT ();
  }

  /** a non const version
   * @return the value matching to given key */
  ValueT &operator[] (const KeyT &key)
  {
    if (this->contains_key (key))
      {
        for (auto &pair : _data[hash (key)])
          {
            if (pair.first == key)
              {
                return pair.second;
              }
          }
      }
    insert (key, ValueT ());
    return at (key);
  }

  /** compare operator for hash maps
   * @return true if this and rhs are equal, false otherwise */
  bool operator== (const HashMap &rhs) const
  {
    if (this == &rhs)
      {
        return true;
      }
    if (_size != rhs._size)
      {
        return false;
      }
    for (int i = 0; i < std::min (_capacity, rhs._capacity); i++)
      {
        if (_data[i].size () != rhs._data[i].size ())
          {
            return false;
          }
        for (int j = 0; j < (int) _data[i].size (); j++)
          {
            if (_data[i][j].first != rhs._data[i][j].first ||
                _data[i][j].second != rhs._data[i][j].second)
              {
                return false;
              }
          }
      }
    return true;
  }

  /** compare operator for hash maps
   * @return true if this and rhs are not equal, false otherwise */
  bool operator!= (const HashMap &rhs) const
  {
    if (this == &rhs)
      {
        return false;
      }
    if (_size != rhs._size || _capacity != rhs._capacity)
      {
        return true;
      }
    for (int i = 0; i < _capacity; i++)
      {
        if (_data[i].size () != rhs._data[i].size ())
          {
            return true;
          }
        for (int j = 0; j < (int) _data[i].size (); j++)
          {
            if (_data[i][j].first != rhs._data[i][j].first ||
                _data[i][j].second != rhs._data[i][j].second)
              {
                return true;
              }
          }
      }
    return false;
  }

  // returns the const iterator that marks begin of iteration
  const_iterator cbegin () const
  {
    return ConstIterator (this);
  }

// returns the const iterator that marks end of iteration
  const_iterator cend () const
  {
    ConstIterator itr (this);
    for (int i = 0; i < _size; i++)
      {
        itr++;
      }
    return itr;
  }

// returns the const iterator that marks begin of iteration
  const_iterator begin () const
  {
    return ConstIterator (this);
  }

// returns the const iterator that marks end of iteration
  const_iterator end () const
  {
    ConstIterator itr (this);
    for (int i = 0; i < _size; i++)
      {
        itr++;
      }
    return itr;
  }

  // the iterator for hash map
  class ConstIterator {

   private:
    int pair_index = 0; //index of current pair in vector
    int bucket_index; //index of current vector
    const HashMap<KeyT, ValueT> *hash_map;

   public:
    typedef const std::pair<KeyT, ValueT> value_type;
    typedef const std::pair<KeyT, ValueT> &reference;
    typedef const std::pair<KeyT, ValueT> *pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::forward_iterator_tag iterator_category;

    // constructor for iterator
    explicit ConstIterator (const HashMap<KeyT, ValueT> *hm)
    {
      hash_map = hm;
      int i = 0;
      while (i < hm->_capacity && hm->_data[i].empty ())
        {
          i++;
        }
      bucket_index = i;
    }

    const std::pair<KeyT, ValueT> &operator* () const
    { return hash_map->_data[bucket_index][pair_index]; }

    const std::pair<KeyT, ValueT> *operator-> ()
    { return &(operator* ()); }

    // prefix ++ for iterator
    ConstIterator operator++ ()
    {
      if (pair_index + 1 < (int) hash_map->_data[bucket_index].size ())
        {
          pair_index++;
          return *this;
        }
      else
        {
          pair_index = 0;
          bucket_index++;
          while (bucket_index < hash_map->_capacity &&
                 hash_map->_data[bucket_index].empty ())
            {
              bucket_index++;
            }
          return *this;
        }
    }

    // postfix ++ for iterator
    ConstIterator operator++ (int)
    {
      const_iterator temp = *this;
      if (pair_index + 1 < (int) hash_map->_data[bucket_index].size ())
        {
          pair_index++;
          return temp;
        }
      else
        {
          pair_index = 0;
          bucket_index++;
          while (bucket_index < hash_map->_capacity &&
                 hash_map->_data[bucket_index].empty ())
            {
              bucket_index++;
            }
          return temp;
        }
    }

    bool operator== (const ConstIterator &a) const
    {
      return a.hash_map == this->hash_map && a.bucket_index ==
             this->bucket_index && a.pair_index == this->pair_index;
    };
    bool operator!= (const ConstIterator &a) const
    {
      return a.hash_map != this->hash_map || a.bucket_index !=
             this->bucket_index || a.pair_index != this->pair_index;
    };
  };

};

#endif //_HASHMAP_HPP_
