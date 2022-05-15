#pragma once
#include <initializer_list>
#include <iostream>
//#include "Iterator_Realization.cpp"
//#include "Iterator.h"
class Iterator;  //////////////////////////////
class List {
  friend class Iterator;

 private:
  int capacity = 1;
  int size = 0;
  int *arrList = nullptr;

 public:
  List(int capacity = 1, int size = 0);
  List(int arrList[], int capacity = 1, int size = 0);
  List(const List &list);
  List(List &&list);
  List(const std::initializer_list<int> &intiList);
  ~List();
  bool IsEmpty();
  int Size();
  void Clear();
  int Front();
  int Back();
  void PushFront(int pushedElement);
  void PushBack(int pushedElement);
  int PopFront();
  int PopBack();
  void Swap(List &list1);
  void Resize();
  friend std::ostream &operator<<(std::ostream &out, const List &list);
  friend std::istream &operator>>(std::istream &in, List &list);
  friend List operator+(const List &list1, const List &list2);
  friend bool operator==(const List &list1, const List &list2);
  friend bool operator!=(const List &list1, const List &list2);
  friend List operator+=(List &list1, const List &list2);
  List &operator=(List &&list) {
    if (&list == this) {
      return *this;
    }
    delete[] arrList;
    capacity = list.capacity;
    size = list.size;
    arrList = list.arrList;
    list.arrList = nullptr;
    return *this;
  }
  List &operator=(const List &list) {
    if (list == *this) {
      return *this;
    }
    delete[] arrList;
    size = list.size;
    capacity = list.capacity;
    arrList = new int[capacity];
    for (int i = 0; i < size; i++) {
      arrList[i] = list.arrList[i];
    }
    return *this;
  }
  Iterator Begin();
  Iterator End();
  void Erase(Iterator iterator);
};