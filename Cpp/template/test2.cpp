#include <iostream>
//非类型模板参数
using namespace std;
namespace test1 {
	//template<class T, size_t N = 10>//N一般要求是int short char 
	//class array {
	//public:
	//	//重载[]
	//	T& operator[](size_t index) {
	//		return _array[index];
	//	}
	//	const T& operator[](size_t index) const{
	//		return _array[index];
	//	}
	//	//数组长度接口
	//	size_t size()const {
	//		return _size;
	//	}
	//private:
	//	T _array[N];
	//	size_t _size;
	//};

	////函数模板的特化
	//template<>
	//bool IsEq<char*>(char*& left, char*& right) {
	//	if (strcmp(left, right) > 0)
	//		return true;

	//	return false;
	//}
	//bool Isequal(char* left, char* right) {
	//	if (strcmp(left, right) > 0)
	//		return true;

	//	return false;
	//}
	//类模板的特化 全特化与偏特化
	//全特化

	template<class T1, class T2>//normal
	class Data {
	public:
		Data() {
			std::cout << "normal" << std::endl;
		}
	private:
		T1 _d1;
		T2 _d2;
	};

	template<>
	class Data<int,char> {
	public:
		Data() {
			std::cout << "all" << std::endl;
		}
	private:
		int _d1;
		char _d2;
	};

	//偏特化 部分特化 类型限制
	template<class T2>
	class Data<int, T2> {
	public:
		Data() {
			std::cout << "Data<T1, int>" << std::endl;
		}
	private:
		int a;
		T2 b;
	};

	template<class T1, class T2>
	class Data<T1*, T2*> {
	public:
		Data() {
			std::cout << "Data<T1*, T2*>" << std::endl;
		}
	private:
		T1 a;
		T2 b;
	};

	template<class T1, class T2>
	class Data<T1&, T2&> {
	public:
		Data() {
	std::cout<< "Data<T1&, T2&>" << std::endl;
		}
	private:
		T1 a;
		T2 b;
	};
};

int main() {
	test1::Data<int, int> d1;
	test1::Data<char, char> d2;
	test1::Data<int*, int*> d3;
	test1::Data<int&, int&> d4;


	system("pause");
	return 0;
} 
