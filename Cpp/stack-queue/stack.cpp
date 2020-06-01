#include <iostream>
#include <list>
#include <stack>
#include <vector>
using namespace std;

namespace bit {
template<class T, class Container>
class stack1 {
  public:
    void push1(const T& x) {
      _con.push_back(x);
    }
    void pop1() {
      _con.pop_back();
    }
    bool empty1() {
      return _con.empty();
    }
    size_t size1() {
      return _con.size();
    }
    T& top1() {
      return _con.back();
    }
  private:
  Container _con;
};
void test_stack() {
  stack1<int, vector<int> > arr;
  arr.push1(1);
  cout << arr.top1() << endl;
}
}

int main () {
  bit:: test_stack();
  return 0;
}
