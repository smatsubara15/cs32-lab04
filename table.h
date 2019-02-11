//  table.h
//  W19 - Lab04
//  Scott Matsubara 5794359

#ifndef table_h
#define table_h

#include <vector>
#include "entry.h"
#include <iostream>
#include <cstdlib>
typedef std::vector<Entry> CVector;
class Table {
public:
  Table(unsigned int size=100);
  Table(unsigned int entries, std::istream& input);
  ~Table();
  
  void put(unsigned int key, std::string data);
  void put(Entry e);

  std::string get(unsigned int key) const;
  bool remove(unsigned int key);

  friend std::ostream& operator<< (std::ostream& out, const Table& t);
private:
  unsigned int hash(int key) const;
  CVector *data;
  unsigned int size;
  unsigned int entries;
};

void mergesort(Entry *a, size_t n);
void merge(Entry *a, size_t n1, size_t n2);
#endif /* table_h */
