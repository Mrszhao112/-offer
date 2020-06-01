#include <vector>
#include <algorithm>
#include <iostream>
namespace mypri {
  //仿函数 函数对象 
  template<class T> 
    struct less {
      bool operator()(const T& x1, const T& x2){return x1 > x2;} 
    };
  template<class T>
    struct greater {
      bool operator()(const T& x1, const T& x2){return x1 < x2;}
    };
  //默认大堆
  template<class T, class Container = std::vector<T>, class Compare = less<T> > 
    class priority_queue {
      public:
        void Adiustup(int child) {//up
          Compare com;//实例化一个对象 当伪函数使用
          int partent = (child -1) / 2;
          while (child > 0) {
            if (com(_con[partent], _con[child])) {//调整后更新位置
              std::swap(_con[partent], _con[child]);
              child = partent;
              partent = (child-1) / 2;
            }else {
              break;
            }
          }
        }
        void Adjustdown(int root) {//down
          Compare com;
          int partent = root;
          int child = 2 * partent + 1;
          while (child < _con.size()) {
            if (child + 1 < _con.size() && _con[child] < _con[child+1]) {
              child++;
            }
            if (com(_con[partent], _con[child])) {
              swap(_con[child], _con[partent]);
              partent = child;
              child = partent * 2 + 1;
            }else {
              break;
            }
          }

        }
        void push(const T& x) {
          _con.pushback(x);
          Adjustup(_con,size() - 1);
        }
        void pop() {
          swap(_con[0], _con[_con.size()-1]);
          _con.pop_back();
          Adjustdown(0);
        }
        T& top() {
          return _con[0];
        }
        size_t size() {
          return _con.size();
        }
        bool empty() {
          return _con.empty();
        }
      private:
        Container _con;
    };

  void test() {
    priority_queue<int, std::vector<int>, greater<int> > pro;
    pro.push(1);
    pro.push(1);
    pro.push(7);
    pro.push(4);
    while (!pro.empty()) {
      std::cout << pro.top() << " ";
      pro.pop();
    }
    std::cout << std::endl;


  }

}
