#include<iostream>
class Iterator;
class Integer;
class Float;

class Visitor {
 public:
  // virtual void visit(Set& nset) = 0;
  // virtual void visit(SetFloat& nset) = 0;
  virtual void visit(Integer a) = 0;
  virtual void visit(Float a) = 0;
  virtual ~Visitor() = default;
};
class E {
  virtual void accept(Visitor& v) = 0;
};
class Integer : public E {
 public:
  Integer() {}
  Integer(int a) { x = a; }
  int x;

  void accept(Visitor& v) override { v.visit(*this); }
};
class Float : public E {
 public:
  Float(float a) { x = a; }
  float x;
   void accept(Visitor& v) override { v.visit(*this); }
};
class S {
  virtual void accept(Visitor& v) = 0;
};
class StackInt {
 public:
  Integer** a;
  int length = 0;
  int capacity = 10;

  StackInt() {
    a = new Integer*[capacity];
    for (int i = 0; i < capacity; i++) {
      a[i] = new Integer;
    }
  }

  StackInt(std::initializer_list<int> list) {
    capacity = 4 * list.size();
    length = list.size();
    a = new Integer*[capacity];
    for (int i = 0; i < capacity; i++) {
      a[i] = new Integer;
    }
    int i = 0;
    for (auto x : list) {
      (a[i])->x = x;
      i++;
    }
  }
  void push(int v) {
    if (length + 1 < capacity) {
      capacity *= 2;
      Integer** x = new Integer*[capacity];
      for (int i = 0; i < capacity; i++) {
        x[i] = new Integer;
      }
   //   for (int i = 0; i < capacity / 2; i++) {
   //     delete a[i];
   //   }
      a = new Integer*[capacity];

      for (int i = 0; i < capacity; i++) {
        a[i] = new Integer;
      }
      for (int i = 0; i < length + 1; i++) {
        a[i] = x[i];
      }
      for (int i = 0; i < capacity; i++) {
        delete a[i];
      }
    }
    (a[length])->x = v;
    length++;
  }
  Integer pop() {
    Integer x;
      try {
      x.x = (a[length - 1])->x;
        length--;
      }
      catch (std::exception e) {
        std::cerr << e.what();
      }
      
      return x;
  }
  int size() const { return length; }
};class Average : public Visitor {
 public:
  int sum = 0;
  float s = 0;
  void visit(Integer a) override { sum += a.x; }
  void visit(Float a) override { sum += a.x; }
  float average(const StackInt& stack) {
    return ( float )( sum ) / stack.size();
  }
};

int main() {

  StackInt stack({1, 2, 2});
  Average a;
  for (int i = 0; i < stack.size(); i++) {
    ((stack.a)[i])->accept(a);
  }
  std::cout << a.average(stack);
    return 0; }