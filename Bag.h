// FILE: Bag.h
// CLASS PROVIDED: Bag (adapted from textbook, CS Dept. Akira Kawaguchi)
// NOTE: this file may not be modified.
//
// TYPEDEF and MEMBER CONSTANTS for the Bag class:
//   typedef ____ value_type
//     Bag::value_type is the data type of the items in the Bag. It may be any of
//     the C++ built-in types (int, char, etc.), or a class with a default
//     constructor, an assignment operator, and operators to
//     test for equality (x == y) and non-equality (x != y).
//
//   typedef ____ size_type
//     Bag::size_type is the data type of any variable that keeps track of how many items
//     are in a Bag.
//
//   static const size_type CAPACITY = _____
//     Bag::CAPACITY is the maximum number of items that a Bag can hold.
//
// CONSTRUCTOR for the Bag class:
//   Bag()
//     Postcondition: The Bag has been initialized as an empty Bag.
//
// MODIFICATION MEMBER FUNCTIONS for the Bag class:
//   void erase_one(const value_type& target)
//     Postcondition: If target was in the Bag, then one copy has been removed;
//     otherwise the Bag is unchanged. A true return value indicates that one
//     copy was removed; false indicates that nothing was removed.
//
//   void insert(const value_type& entry)
//     Precondition:  size( ) < CAPACITY.
//     Postcondition: A new copy of entry has been added to the Bag.
//
// CONSTANT MEMBER FUNCTIONS for the Bag class:
//   size_type size() const
//     Postcondition: The return value is the total number of items in the Bag.
//
//   size_type count(const value_type& target) const
//     Postcondition: The return value is number of times target is in the Bag.
//
// VALUE SEMANTICS for the Bag class:
//    Assignments and the copy constructor may be used with Bag objects.

#ifndef MAIN_SAVITCH_BAG1_H
#define MAIN_SAVITCH_BAG1_H
#include <iostream>   
#include <cstdlib>    // Provides size_t
#include <cassert>

template<class Item>
class Bag {
public:
  // TYPEDEFS and MEMBER CONSTANTS
  typedef Item value_type;
  typedef std::size_t size_type;
  static const size_type DEFAULT_CAPACITY = 30;
  // CONSTRUCTORS and DESTRUCTOR
  Bag(size_type initial_capacity = DEFAULT_CAPACITY);
  Bag(const Bag& source);
  void operator =(const Bag& source);
  ~Bag() { delete [] data; }

  // MODIFICATION MEMBER FUNCTIONS
  void reserve(size_type new_capacity);
  bool erase_one(const value_type& target);
  size_type erase(const value_type& target);
  void insert(const value_type& entry);
  void operator +=(const Bag& addend);
  void sort_descending();
  value_type remove_random_element();

  // CONSTANT MEMBER FUNCTIONS
  size_type size() const { return used; }
  size_type count(const value_type& target) const;
  size_type get_current() const { return current; }
  value_type get_random_element() const { return data[rand() % used]; }


  //std::ostream& operator<<(std::ostream&, const Bag&);

  // SIMPLE ITERATOR
  void begin() { current = 0; }
  bool end() const { return current >= used; }
  int operator++(int) { assert(!end()); current++; return current; } //return statement added
  value_type& get() { assert(!end()); return data[current]; } //return type changed
private:
  value_type *data;     // Pointer to partially filled dynamic array
  size_type used;       // How much of array is being used
  size_type capacity;   // Current capacity of the Bag
  size_type current;    // Iterator's current position.
};
#include "Bag.template"
#endif
