#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void test_vector1() {
  vector<int> v1;
  v1.push_back(1);
  v1.push_back(2);
  v1.push_back(3);
  v1.push_back(4);
  v1.push_back(5); 
  for (size_t i = 0; i < v1.size(); ++i) {
    cout << v1[i] << "";
  }
  cout << endl;


  vector<int> v2(v1);  //vector的拷贝构造
  for (size_t i = 0; i < v2.size(); ++i) {
    cout << v2[i] << " ";
  }
  cout << endl;

  vector<int> v3; 
  v3.push_back(4);
  v3.push_back(4);
  v3.push_back(4);
  v3.push_back(4);
  
  v1 = v3;
  for (size_t i = 0; i < v1.size(); ++i) {
    cout << v1[i] << " ";
  }
  cout << endl;
}

void test_vector2() {
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);

  //遍历修改数据 使用operator[] + size
  for (size_t i = 0; i < v.size(); ++i) {
    v[i] *= 2;
    cout << v[i] << " ";
  }
  cout << endl;

  //迭代器
  vector<int>::iterator it = v.begin();
  while (it != v.end()) {
    cout << *it << " ";
    ++it;
  }
  cout << endl;

  //范围for
//  for (auto e : v) {
//    cout << e << " ";
 // }
//  cout << endl; 
}

void prinf_vector(const vector<int>& vt) {
  //只读
  vector<int>::const_iterator it = vt.begin();
  while (it != vt.end()) {
    cout << *it << " ";
    ++it;
  }
  cout << endl;
}

//三种类型的迭代器
void test_vector3() {
  vector<int> v;
  v.push_back(1);
  v.push_back(7);
  v.push_back(5);
  v.push_back(4);

  //正向可读可写
  vector<int>::iterator it = v.begin();
  while (it != v.end()) {
    *it *= 2;
    cout << *it << " ";
    ++it;
  }
  cout << endl;
  
  //逆向可读可写
  vector<int>::reverse_iterator rit = v.rbegin();
  while (rit != v.rend()) {
    cout << *rit << " ";
    ++rit;
  }
  cout << endl;
  }


//reverse和resize 的比较


void test_vector4() {
  vector<int> v;
  v.push_back(1);
  v.push_back(1);
  v.push_back(1);
  v.push_back(1);
  v.push_back(1);
  v.push_back(1);
  cout << v.size() << endl;
  cout << v.capacity() << endl;

  size_t sz;
  vector<int> foo;
 // foo.reserve(1067);
  foo.resize(1067);
  sz = foo.capacity();
  std::cout << "grow!!!\n";
  for (int i = 0; i < 1067; ++i) {
    //foo.push_back(i);
    foo[i] = i;
    if (sz != foo.capacity()) {
      sz = foo.capacity();
      cout << " capacity change:" << sz << '\n';
    }
  }
}

//体会insert 与 earse
void test_vector5() {
  vector<int> v;
  v.push_back(1);
  v.push_back(1);
  v.push_back(1);
  v.push_back(1);

  v.insert(v.begin(), 0);
  v.insert(v.begin(), -1);

 // for (auto e : v) {
  //  cout << e << " ";
 // }
 // cout << endl;

  v.erase(v.begin());
 // for (auto e : v) {
  //  cout << e << " ";
 // }
 // cout << endl;

  v.erase(v.begin());
}

void test_vector6() {
  
  vector<int> v;
  v.push_back(1);
  v.push_back(1);
  v.push_back(1);
  v.push_back(5);
  v.push_back(5);
  v.push_back(10);

  vector<int>::iterator pos = find(v.begin(), v.end(), 5);//找到5 
  if (pos != v.end()) {
    v.erase(pos);
  }
  sort(v.begin(),v.end());//排序
  
 // for (auto e : v) {
  //  cout << e << " ";
 // }
 // cout << endl;

}

int main () {
 // test_vector1();
 // test_vector2();
 test_vector4();
  return 0;
}
