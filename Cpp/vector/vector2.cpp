#pragma once
#include <assert.h>
#include <iostream>
namespace my_vector {

	//模板的使用示例
//	template<class T>
//	class vector{
//public:
//
//private:
//	T* _a;
//	size_t _size;
//	size_t _capacity;
//	};

	template<class T>
	class vector{
public:
	typedef T* iterator; // 对模板进行重命名
	typedef const T* const_iterator;

	vector() //初始化列表 初始化迭代器指针
		:_start(nullptr)
		,_finish(nullptr)
		,_endofstorage(nullptr)
	{}

	//构造
	////v2(v1) 
	//vector(const vector<T>& v) { //直接 构造出一个想要的空间 然后逐一赋值 
	//	_start = new T[v.capacity()]; //指向空间首地址
	//	_finish = _start;
	//	_endofstorage = _start + v.capacity(); //指向最大容量处

	//	for (size_t i = 0; i < v.size(); i++) { //循环赋值
	//		*_finish = v[i];
	//		++_finish;
	//	}
	//}
	//v2(v1)
	vector(const vector<T>& v)//先初始化 然后reverse开空间 逐一赋值
		:_start(nullptr)
		, _finish(nullptr)
		, _endofstorage(nullptr)
		{
			reverse(v.capacity());
			for (const auto& e : v) {
				push_back(e);
			}
		}
		

	//赋值运算符重载 现代写法 
	//vector<T>& operator=(vector<T> v) { //进来的系统自动拷贝一份v
	//	swap(v); //其实是交换 this 和 v
	//	return *this;
	//}
	///////////////////////////////////////////////////////////////////////////////////
	vector<T>& operator=(vector<T>& v) {
		//释放原来的空间
		delete[] _start;
		_start = _finish = _endofstorage = nullptr;
		//开辟新空间
		T* tmp = new T[v.capacity()];
		//赋值
		for (size_t i = 0; i < v.size(); i++) {
			tmp[i] = v[i];
		}
		//结束
		_start = tmp;
		_finish = tmp + v.size();
		_endofstorage = tmp + v.capacity();
		return *this;
	}
	//////////////////////////////////////////////////////////////////////////////////////
	void swap(vector<T>& v) { 
		::swap(_start, v._start);
		::swap(_finish, v._finish);
		::swap(_endofstorage, v._endofstorage);
	}

	~vector() { //析构
		delete[] _start;
		_start = _finish = _endofstorage = nullptr;
	}
	iterator begin() {
		return _start;
	}
	iterator end() { //_finish 指向的是末尾位置
		return _finish;
	}
	const_iterator begin() const{ //只读迭代器重载
		return _start;
	}
	const_iterator end() const{
		return _finish;
	}
	void reverse(size_t n) {
		if (n >capacity()) {
			size_t sz = size();
			T* tmp = new T[n];
			if (_start) { //判断是不是空 如果为空则只需要进行指针的大小变化 无需进行值拷贝
				//memcpy(tmp, _start, sizeof(T)*sz);浅拷贝 
				for (size_t i = 0; i < sz; ++i) {
					tmp[i] = _start[i];
				}
				delete[] _start;//赋值结束后删除原来的数据 
			}
			_start = tmp;//更新指针位置
			_finish = tmp + sz;
			_endofstorage = tmp + n;
		}
	}

	void resize(size_t n, const T& val = T()) { //此处为缺省参数
		if (n < size()) {
			_finish = _start + n;
		}
		else {
			if (n > capacity()) {
				reverse(n);
			}
			while (_finish != _start + n) {
				*_finish = val;
				++_finish;
			}
		}
	}

	void push_back(const T& x) {
		if (_finish == _endofstorage) {
			size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
			reverse(newcapacity);
		}
		/////////////////////////////////////
		*_finish = x;
		_finish++;
		//insert(_finish, x);
	}

	void pop_back() {
		assert(_start < _finish);
		--_finish;
	}
	void insert(iterator pos, const T& x) {
		assert(pos <= _finish);
		if (_finish == _endofstorage) {
			size_t n = pos - _start;//扩容时保存相对位置
			size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
			reverse(newcapacity);
			pos = _start + n;
		}
		iterator end = _finish - 1;
		while (end >= pos) {
			*(end + 1) = *end;
			--end;
		}
		*pos = x;
		++_finish;
	}

	iterator erase(iterator pos) {
		assert(pos >= _start && pos < _finish);
		iterator it = pos;
		while (it < _finish) {
			*it = *(it + 1);
			it++;
		}
		--_finish;
		return pos;
	}
	T& operator[](size_t i) {
		assert(i < size());
		return _start[i];
	}
	const T& operator[](size_t i) const{ 
		assert(i < size());
		return _start[i];
	}
	size_t size() const {
		return _finish - _start;
	}
	size_t capacity() const {
		return _endofstorage - _start;
	}
private:
	iterator _start;
	iterator _finish;
	iterator _endofstorage;
	};

	//测试
	//迭代器失效问题

	void print_vector(const vector<int>& v) {
		vector<int>::const_iterator it = v.begin();
		while (it != v.end()) {
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;
	}
	void test1() {
		vector<int> v;
		v.push_back(1);
		v.push_back(3);
		v.push_back(2);
		print_vector(v);

		//std::cout << v.size() << std::endl;
		//std::cout << v.capacity() << std::endl;
		//print_vector(v);

		vector<int> x;
		x.push_back(100);
		print_vector(x);
		x = v;
		print_vector(x);
		print_vector(v);

	}
}
