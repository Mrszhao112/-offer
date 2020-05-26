	#include <iostream>
#include <vector>
//#include "vector(1).h"
//using namespace my_vector;
using namespace std;
void testn() {
	vector<int> v;
	v.push_back(1);
	v.push_back(3);
	v.push_back(1);
	v.push_back(4);
	v.push_back(4);
	v.push_back(4);

	vector<int>::iterator it = v.begin(); 

	//v.push_back(6); 失效 当迭代器涉及增容删除迭代器等操作  程序崩溃
	//v.push_back(7); 解决办法 重新赋值

	while (it != v.end()) {
		if (*it % 2 == 0) {
			it = v.erase(it);
		}
		else {
			++it;
		}
	}
	for (auto e : v) {
		cout << e << " ";
	}
	cout << endl;
}
int main()
{
	//test1();
	testn();
	system("pause");
	return 0;
}
