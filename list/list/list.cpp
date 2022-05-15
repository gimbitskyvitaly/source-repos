#include "List.h"

#include <iostream>

#include "Iterator.h"

// extern List list;
// List::List() {//+
//  arrList = new int [capacity];
//  size = 0;
//}
class Iterator;
List ::List(int capacity, int size) {
  this->capacity = capacity;
  this->size = size;
  this->arrList = new int[capacity];
}
List::List(int arrList[], int capacity, int size) {
  this->capacity = capacity;
  this->size = size;
  this->arrList = new int[capacity];
  for (int i = 0; i < capacity; i++) {
    this->arrList[i] = arrList[i];
  }
}
List::List(const List &list) {  //+
  arrList = new int[list.capacity];
  for (int i = 0; i < list.size; i++) {
    arrList[i] = list.arrList[i];
  }
  size = list.size;
  capacity = list.capacity;
}
List ::List(List &&list) {
  this->capacity = list.capacity;
  this->size = list.size;
  this->arrList = list.arrList;
  list.arrList = nullptr;
  list.capacity = 0;
  list.size =
      0;  ////////////////////////////////////////////////////////////////////////////////////////////
}
List::List(const std::initializer_list<int> &initList)
    : List(initList.size(), initList.size()) {
  arrList = new int[initList.size()];
  for (auto &element : initList) {
    arrList[element] = element;
  }
}
List ::~List() {
  if (arrList != nullptr) {
    delete[] arrList;
  }
}
bool List::IsEmpty() { return size == 0; }  //+
int List::Size() {                          //+
  return size;
}
void List::Clear() {
  capacity = 1;
  if (size != 0) {
    size = 0;
    delete[] arrList;
    arrList =
        new int[capacity];  ////////////////////////////////////////////////
  }
}
int List::Front() {  //+
  try {
    if (size <= 0) {
      throw std ::logic_error{"No elements in the list"};
    }
  } catch (std ::logic_error) {
    std::cerr << "No elements";
  }
  if (size > 0) {
    return arrList[0];
  }
}
int List ::Back() {  //+
  try {
    if (size <= 0) {
      throw std ::logic_error{"No elements in the list"};
    }
  } catch (std ::logic_error) {
    std::cerr << "No elements";
  }
  if (size > 0) {
    return arrList[size - 1];
  }
}
void List::PushBack(int pushedElement) {  //+
  if (size + 1 > capacity) {
    Resize();
  }
  arrList[size++] = pushedElement;
}
void List::PushFront(int pushedElement) {
  if (size + 1 > capacity) {
    Resize();
  }
  int *bufArr = new int[size];
  for (int i = 0; i < size; i++) {
    bufArr[i] = arrList[i];
  }
  // delete[] arrList;
  // arrList = new int[capacity];
  size++;
  for (int i = 1; i < size; i++) {
    arrList[i] = bufArr[i - 1];
  }
  arrList[0] = pushedElement;
  delete[] bufArr;
}
int List::PopFront() {  //+
  try {
    if (size <= 0) {
      throw std ::logic_error{"There is no elements in the list"};
    }  ////////////////////////////////////////////////////////////////////////////////////////
  } catch (std::logic_error) {
    std::cerr << "Size of the list is lower than 0";
  }
  if (size > 0) {
    int popedElement = arrList[0];
    int y = arrList[1];
    int *bufArr = new int[--size];
    for (int i = 0; i < size; i++) {
      bufArr[i] = arrList[i + 1];
    }
    int x = bufArr[0];
    y = arrList[1];
    delete
        [] arrList;  ////////////////////////////////////////////////////////////////////////
    arrList = new int[capacity];
    for (int i = 0; i < size; i++) {
      arrList[i] = bufArr[i];
    }
    delete[] bufArr;
    return popedElement;
  }
}
int List::PopBack() {  //+
  try {
    if (size <= 0) {
      throw std ::logic_error{"There is no elements in the list"};
    }
  } catch (
      std::
          logic_error) {  ///////////////////////////////////////////////////////////////////////
    std::cerr << "Size of the list is lower than 0";
  }
  if (size > 0) {  /////////////////////////////////////////////////////
    int popedElement = arrList[size - 1];
    int *bufArr = new int[--size];
    for (int i = 0; i < size; i++) {
      bufArr[i] = arrList[i];
    }
    delete[] arrList;
    arrList = new int[capacity];
    for (int i = 0; i < size; i++) {
      arrList[i] = bufArr[i];
    }
    delete[] bufArr;
    return popedElement;
  }
}
void List::Swap(
    List &
        list1) {  ///////////////////////////////////////////////////////////////////+
  List bufList(list1);
  delete[] list1.arrList;
  list1.arrList = new int[capacity];
  for (int i = 0; i < size; i++) {
    list1.arrList[i] = arrList[i];
  }
  list1.size = size;
  list1.capacity = capacity;
  delete[] arrList;
  arrList = new int[bufList.capacity];
  for (int i = 0; i < bufList.size; i++) {
    arrList[i] = bufList.arrList[i];
  }
  size = bufList.size;
  capacity = bufList.capacity;
}
void List::Resize() {
  int *bufArr = new int[capacity];
  for (int i = 0; i < capacity; i++) {
    bufArr[i] = arrList[i];
  }
  delete[] arrList;
  capacity *= 2;
  arrList = new int[capacity];
  for (int i = 0; i < size; i++) {
    arrList[i] = bufArr[i];
  }
  delete[] bufArr;
}

std::ostream &operator<<(std::ostream &out, const List &list) {
  for (int i = 0; i < list.size; i++) {
    out << list.arrList[i] << ", ";
  }
  return out;
}

std::istream &operator>>(std::istream &in, List &list) {
  int ellement;
  in >> ellement;
  list.PushBack(ellement);
  return in;
}

List operator+(const List &list1, const List &list2) {
  List list;
  list.arrList = new int[list1.size + list2.size];
  for (int i = 0; i < list1.size; i++) {
    list.arrList[i] = list1.arrList[i];
  }
  for (int i = list1.size; i < list1.size + list2.size; i++) {
    list.arrList[i] = list2.arrList[i - list1.size];
  }
  list.capacity = list1.size + list2.size;
  list.size = list1.size + list2.size;
  return list;
}

bool operator==(const List &list1, const List &list2) {
  if (list1.size != list2.size) {
    return false;
  } else {
    for (int i = 0; i < list1.size; i++) {
      if (list1.arrList[i] != list2.arrList[i]) {
        return false;
      }
    }
  }
  return true;
}
bool operator!=(const List &list1, const List &list2) {
  if (list1.size != list2.size) {
    return true;
  } else {
    for (int i = 0; i < list1.size; i++) {
      if (list1.arrList[i] != list2.arrList[i]) {
        return true;
      }
    }
  }
  return false;
}
List operator+=(List &list1, const List &list2) {
  int *bufArr = new int[list1.size];
  for (int i = 0; i < list1.size; i++) {
    bufArr[i] = list1.arrList[i];
  }
  list1.size = list1.size + list2.size;
  list1.capacity = list1.capacity + list2.capacity;
  delete[] list1.arrList;
  list1.arrList = new int[list1.capacity];
  for (int i = 0; i < list1.size - list2.size; i++) {
    list1.arrList[i] = bufArr[i];
  }
  for (int i = list1.size - list2.size; i < list1.size; i++) {
    list1.arrList[i] = list2.arrList[i - list1.size + list2.size];
  }
  return list1;
}
Iterator List::Begin() {
  try {
    if (IsEmpty()) {
      throw std::logic_error{"Empty list can't have an iterator"};
    }
  } catch (std::logic_error) {
    std::cerr << "Empty list can't have an iterator";
  }
  if (!IsEmpty()) {
    Iterator iterator(this);
    iterator.index = 0;
    return iterator;
  }
}

Iterator List::End() {
  Iterator iterator(this);
  iterator.index = size;
  return iterator;
}
void List::Erase(Iterator iterator) {
  try {
    if (!iterator.IsInBorder()) {
      throw std ::logic_error{"Isn't in border"};
    }
  } catch (std::logic_error) {
    std::cerr << "Isn't in border";
  }
  if (iterator.IsInBorder()) {
    int *bufArr = new int[capacity];
    for (int i = 0; i < iterator.index; i++) {
      bufArr[i] = arrList[i];
    }
    for (int i = iterator.index + 1; i < size; i++) {
      bufArr[i - 1] = arrList[i];
    }
    delete[] arrList;
    size--;
    arrList = new int[capacity];
    for (int i = 0; i < size; i++) {
      arrList[i] = bufArr[i];
    }
    iterator.index = -1;
    delete[] bufArr;
  }
}

// int main() {
//  List list1;
//  List list2;
//  int x;
//  bool y;
//  x = list1.Front();
//  std::cout << x << std::endl;
//  list1.PopBack();
//  list1.PushBack(1);
//  list1.PushBack(2);
//  list1.PushBack(3);
//  list1.PushBack(4);
//  list1.PushBack(6);
//  list2.PushBack(1);
//  list2.PushBack(2);
//  list2.PushBack(3);
//  list2.PushBack(4);
//  list2.PushBack(6);
//  std::cin >> list1;
//  // y = list1 == list2;
//  // std::cout << y << std::endl;
//  // x = list2.PopBack();
//  // std::cout << x << std::endl;
//  // std::cout << list1 << std::endl;
//  // list1.PushFront(8);
//  // x = list1.PopFront();
//  // std ::cout << x;
//  // x = list1.PopFront();
//  // std::cout << x;
//  // x = list1.PopBack();
//  // std ::cout << list1 << std::endl;
//  // x = list1.Front();
//  // std::cout << x << std::endl;
//  // int* arrList = new int[1];
//  // arrList[0] = 1;
//  // List list(1, 1);
//  // list1.Clear();
//  // std::cout << list << std::endl;
//  // list1.Swap(list2);
//  // std::cout << list1 << std::endl;
//  // std::cout << list2 << std::endl;
//  list1.PushBack(1);
//  List list(list1);
//  std::cout << list1 + list2 << std::endl;
//  std::cout << list1 << std::endl;
//  std::cout << list2 << std::endl;
//  list1 += list1 += list2;
//  std::cout << list1 << std::endl;
//  // std::cin >> list2;
//  std::cout << list2 << std::endl;
//  // list1.~List();
//  // list2.~List();
//  // list.~List();
//  return 0;
//}
//#include <iostream>
//
//#include "Iterator.h"
//#include "List.h"
//
//  // extern List list;
//  // List::List() {//+
//  //  arrList = new int [capacity];
//  //  size = 0;
//  //}
//  class Iterator;
//  List ::List(int capacity, int size) {
//    this->capacity = capacity;
//    this->size = size;
//    this->arrList = new int[capacity];
//  }
//  List::List(int arrList[], int capacity, int size) {
//    this->capacity = capacity;
//    this->size = size;
//    this->arrList = new int[capacity];
//    for (int i = 0; i < capacity; i++) {
//      this->arrList[i] = arrList[i];
//    }
//  }
//  List::List(const List &list) {  //+
//    arrList = new int[list.capacity];
//    for (int i = 0; i < list.size; i++) {
//      arrList[i] = list.arrList[i];
//    }
//    size = list.size;
//    capacity = list.capacity;
//  }
//  List ::List(List &&list) {
//    this->capacity = list.capacity;
//    this->size = list.size;
//    this->arrList = list.arrList;
//    list.arrList = nullptr;
//    list.capacity = 0;
//    list.size =
//        0;
//        ////////////////////////////////////////////////////////////////////////////////////////////
//  }
//  List::List(const std::initializer_list<int> &initList)
//      : List(initList.size(), initList.size()) {
//    arrList = new int[initList.size()];
//    for (auto &element : initList) {
//      arrList[element] = element;
//    }
//  }
//  List ::~List() {
//    if (arrList != nullptr) {
//      delete[] arrList;
//    }
//  }
//  bool List::IsEmpty() { return size == 0; }  //+
//  int List::Size() {                          //+
//    return size;
//  }
//  void List::Clear() {
//    capacity = 1;
//    if (size != 0) {
//      size = 0;
//      delete[] arrList;
//      arrList =
//          new int[capacity];  ////////////////////////////////////////////////
//    }
//  }
//  int List::Front() {  //+
//    try {
//      if (size <= 0) {
//        throw std ::logic_error{"No elements in the list"};
//      }
//    } catch (std ::logic_error) {
//      std::cerr << "No elements";
//    }
//    if (size > 0) {
//      return arrList[0];
//    }
//  }
//  int List ::Back() {  //+
//    try {
//      if (size <= 0) {
//        throw std ::logic_error{"No elements in the list"};
//      }
//    } catch (std ::logic_error) {
//      std::cerr << "No elements";
//    }
//    if (size > 0) {
//      return arrList[size - 1];
//    }
//  }
//  void List::PushBack(int pushedElement) {  //+
//    if (size + 1 > capacity) {
//      Resize();
//    }
//    arrList[size++] = pushedElement;
//  }
//  void List::PushFront(int pushedElement) {
//    if (size + 1 > capacity) {
//      Resize();
//    }
//    int *bufArr = new int[size];
//    for (int i = 0; i < size; i++) {
//      bufArr[i] = arrList[i];
//    }
//    // delete[] arrList;
//    // arrList = new int[capacity];
//    size++;
//    for (int i = 1; i < size; i++) {
//      arrList[i] = bufArr[i - 1];
//    }
//    arrList[0] = pushedElement;
//    delete[] bufArr;
//  }
//  int List::PopFront() {  //+
//    try {
//      if (size <= 0) {
//        throw std ::logic_error{"There is no elements in the list"};
//      }
//      ////////////////////////////////////////////////////////////////////////////////////////
//    } catch (std::logic_error) {
//      std::cerr << "Size of the list is lower than 0";
//    }
//    if (size > 0) {
//      int popedElement = arrList[0];
//      int y = arrList[1];
//      int *bufArr = new int[--size];
//      for (int i = 0; i < size; i++) {
//        bufArr[i] = arrList[i + 1];
//      }
//      int x = bufArr[0];
//      y = arrList[1];
//      delete
//          [] arrList;
//          ////////////////////////////////////////////////////////////////////////
//      arrList = new int[capacity];
//      for (int i = 0; i < size; i++) {
//        arrList[i] = bufArr[i];
//      }
//      delete[] bufArr;
//      return popedElement;
//    }
//  }
//  int List::PopBack() {  //+
//    try {
//      if (size <= 0) {
//        throw std ::logic_error{"There is no elements in the list"};
//      }
//    } catch (
//        std::
//            logic_error) {
//            ///////////////////////////////////////////////////////////////////////
//      std::cerr << "Size of the list is lower than 0";
//    }
//    if (size > 0) {  /////////////////////////////////////////////////////
//      int popedElement = arrList[size - 1];
//      int *bufArr = new int[--size];
//      for (int i = 0; i < size; i++) {
//        bufArr[i] = arrList[i];
//      }
//      delete[] arrList;
//      arrList = new int[capacity];
//      for (int i = 0; i < size; i++) {
//        arrList[i] = bufArr[i];
//      }
//      delete[] bufArr;
//      return popedElement;
//    }
//  }
//  void List::Swap(
//      List &
//          list1) {
//          ///////////////////////////////////////////////////////////////////+
//    List bufList(list1);
//    delete[] list1.arrList;
//    list1.arrList = new int[capacity];
//    for (int i = 0; i < size; i++) {
//      list1.arrList[i] = arrList[i];
//    }
//    list1.size = size;
//    list1.capacity = capacity;
//    delete[] arrList;
//    arrList = new int[bufList.capacity];
//    for (int i = 0; i < bufList.size; i++) {
//      arrList[i] = bufList.arrList[i];
//    }
//    size = bufList.size;
//    capacity = bufList.capacity;
//  }
//  void List::Resize() {
//    int *bufArr = new int[capacity];
//    for (int i = 0; i < capacity; i++) {
//      bufArr[i] = arrList[i];
//    }
//    delete[] arrList;
//    capacity *= 2;
//    arrList = new int[capacity];
//    for (int i = 0; i < size; i++) {
//      arrList[i] = bufArr[i];
//    }
//    delete[] bufArr;
//  }
//
//  std::ostream &operator<<(std::ostream &out, const List &list) {
//    for (int i = 0; i < list.size; i++) {
//      out << list.arrList[i] << ", ";
//    }
//    return out;
//  }
//
//  std::istream &operator>>(std::istream &in, List &list) {
//    int ellement;
//    in >> ellement;
//    list.PushBack(ellement);
//    return in;
//  }
//
//  List operator+(const List &list1, const List &list2) {
//    List list;
//    list.arrList = new int[list1.size + list2.size];
//    for (int i = 0; i < list1.size; i++) {
//      list.arrList[i] = list1.arrList[i];
//    }
//    for (int i = list1.size; i < list1.size + list2.size; i++) {
//      list.arrList[i] = list2.arrList[i - list1.size];
//    }
//    list.capacity = list1.size + list2.size;
//    list.size = list1.size + list2.size;
//    return list;
//  }
//
//  bool operator==(const List &list1, const List &list2) {
//    if (list1.size != list2.size) {
//      return false;
//    } else {
//      for (int i = 0; i < list1.size; i++) {
//        if (list1.arrList[i] != list2.arrList[i]) {
//          return false;
//        }
//      }
//    }
//    return true;
//  }
//  bool operator!=(const List &list1, const List &list2) {
//    if (list1.size != list2.size) {
//      return true;
//    } else {
//      for (int i = 0; i < list1.size; i++) {
//        if (list1.arrList[i] != list2.arrList[i]) {
//          return true;
//        }
//      }
//    }
//    return false;
//  }
//  List operator+=(List &list1, const List &list2) {
//    int *bufArr = new int[list1.size];
//    for (int i = 0; i < list1.size; i++) {
//      bufArr[i] = list1.arrList[i];
//    }
//    list1.size = list1.size + list2.size;
//    list1.capacity = list1.capacity + list2.capacity;
//    delete[] list1.arrList;
//    list1.arrList = new int[list1.capacity];
//    for (int i = 0; i < list1.size - list2.size; i++) {
//      list1.arrList[i] = bufArr[i];
//    }
//    for (int i = list1.size - list2.size; i < list1.size; i++) {
//      list1.arrList[i] = list2.arrList[i - list1.size + list2.size];
//    }
//    return list1;
//  }
//  Iterator List::Begin() {
//    try {
//      if (IsEmpty()) {
//        throw std::logic_error{"Empty list can't have an iterator"};
//      }
//    } catch (std::logic_error) {
//      std::cerr << "Empty list can't have an iterator";
//    }
//    if (!IsEmpty()) {
//      Iterator iterator(this);
//      iterator.index = 0;
//      return iterator;
//    }
//  }
//
//  Iterator List::End() {
//    Iterator iterator(this);
//    iterator.index = size;
//    return iterator;
//  }
//  void List::Erase(Iterator iterator) {
//    try {
//      if (!iterator.IsInBorder()) {
//        throw std ::logic_error{"Isn't in border"};
//      }
//    } catch (std::logic_error) {
//      std::cerr << "Isn't in border";
//    }
//    if (iterator.IsInBorder()) {
//      int *bufArr = new int[capacity];
//      for (int i = 0; i < iterator.index; i++) {
//        bufArr[i] = arrList[i];
//      }
//      for (int i = iterator.index + 1; i < size; i++) {
//        bufArr[i - 1] = arrList[i];
//      }
//      delete[] arrList;
//      size--;
//      arrList = new int[capacity];
//      for (int i = 0; i < size; i++) {
//        arrList[i] = bufArr[i];
//      }
//      iterator.index = -1;
//      delete[] bufArr;
//    }
//  }
