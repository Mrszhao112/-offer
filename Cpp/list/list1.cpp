#include <iostream>
#include <list>

//list 的五种构造函数
	void test1() {
	std::list<int> l1; //构造空的list
	std::list<int> l2(3, 1);//构造一个存储3个值为1的list
	std::list<int> l3(l2);//拷贝构造
	std::list<int> l4(l2.begin(), l2.end());//以12的区间构造l4 【） 左闭右开
	
	int arr[] = { 1,2,3,4 };
	std::list<int> l5(arr, arr + sizeof(arr) / sizeof(int));//数组首地址加数组长度 遍历构造链表
	std::list<int>::iterator it;
	it = l2.begin();
	while (it != l2.end()) {
		std::cout << *it;
		it++;
	}
	std::cout << std::endl;
	it = l5.begin();
	while (it != l5.end()) {
		std::cout << *it;
		it++;
	}
	std::cout << std::endl;
	for (auto e : l5) {
		std::cout << e;
	}
}
	//正向迭代器与反向迭代器的使用
	void print_list(const std::list<int>& l1) {//打印链表 正向迭代器
		for (std::list<int>::const_iterator it = l1.begin(); it != l1.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}
	void print_rlist(const std::list<int>& l1) {//反向迭代器
		for (std::list<int>::const_reverse_iterator it = l1.rbegin(); it != l1.rend(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}
	void test2() {//测试正向反向迭代器 注意const
		int arr[] = { 1,2,3,4,5 };
		std::list<int> l1(arr, arr + sizeof(arr) / sizeof(int));
		print_list(l1);
		print_rlist(l1);
	}
	void test3() {
		int arr[] = { 1,2,3,4,5,6,7 };
		std::list<int> l1(arr, arr + sizeof(arr) / sizeof(int));
		print_list(l1);
		if (l1.empty()) {//判空
			std::cout << "over" << std::endl;
		}
		else {
			std::cout << "its ok" << std::endl;
		}
		std::cout << l1.size() << std::endl;//list长度
		std::cout << l1.front() << std::endl;//头
		std::cout << l1.back() << std::endl;//尾
		l1.push_front(0);//头插尾插
		l1.push_back(-1);
		print_list(l1);
		l1.pop_back();//头删尾删
		l1.pop_front();
		print_list(l1);
		std::list<int>::const_iterator it = l1.begin();
		++it;
		l1.insert(it, 100);//插入
		print_list(l1);
		it = l1.erase(it);//删除 防止迭代器失效重新给迭代器赋值
		print_list(l1);
		std::cout << *it << std::endl;
		l1.clear();//清空
		print_list(l1);
	}
		int main() {
		system("pause");
		return 0;
	}
