#include <iostream>
namespace mylist {
	template<class T>
	struct __list_node {	//建立一个节点的模板
		__list_node(const T& x = T())
			:_next(nullptr)
			, _prev(nullptr)
			, _data(x)
		{}
		__list_node<T>* _next;
		__list_node<T>* _prev;
		T _data;
	};

	template<class T>		//迭代器的模板
	struct __list_iterator {
		typedef __list_node<T> Node;
		Node* _node;		//成员

		__list_iterator(Node* node)
			:_node(node)
		{}
		T& operator*() {
			return _node->_data;
		}
		T* operator->() {
			return &_node->_data;
		}
		__list_iterator<T>& operator++() {		//前置++
			_node = _node->_next;
			return *this;
		}
		__list_iterator<T> operator++(int) {		//后置++
			__list_iterator<T> tmp(*this);
			++(*this);
			return tmp;
		}
		//前置--后置--类比++即可
		bool operator!=(const __list_iterator<T>& it) {		//重载的是判断当前节点是否为同一个节点 而非是否值相等
			if (_node != it._node) {
				return true;
			}
			return false;
		}
		bool operator==(const __list_iterator<T>& it) {
			if (_node == it._node)
				return true;
			return false;
		}
	};
	template<class T>		//类的模板
	class list {
		typedef __list_node<T> Node;
	public:
		typedef __list_iterator<T> iterator;
		iterator begin() {
			return iterator(_head->_next); //返回值一致
		}
		iterator end() {
			return iterator(_head);
		}

		list()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}
		~list() {
			clear();
			delete _head;
			_head = nullptr;
		}
		void clear() {
			iterator it = begin();
			while (it != end()) {
				//erase(it++);
				it = erase(it);
			}
		}
		iterator erase(iterator it) {
			Node* cur = it._node;
			Node* next = cur->_next;
			Node* prev = cur->_prev;
			delete cur;
			prev->_next = next;
			next->_prev = prev;
		}
		void push_back(const Node& x) {
			Node* tail = _head->_prev;
			Node* newNode = new Node(x);
			tail->_next = newNode;
			newNode->_prev = tail;
			newNode->_next = _head;
			_head->_prev = newNode;
		}
	private:
		Node* _head;
	};
	void test1() {
		list<int> l1;
		l1.push_back(1);
		l1.push_back(2);
		l1.push_back(3);
		l1.push_back(4);
		list<int>::iterator it = l1.begin();
		while (it != l1.end()) {
			std::cout << *it << std::endl;
			it++;
		}
	}
		struct Data {
			int _year = 0;
			int _month = 1;
		};
		void test2() {
			int* p1 = new int;
			*p1;
			Data* p2 = new Data;
			*p2;
			p2->_year;
			list<Data> l1;
			l1.push_back(Data());
			l1.push_back(Data());
			list<Data>::iterator it = l1.begin();
			while (it != l1.end()) {
				std::cout << (*it)._year << (*it)._month << "  ";
				std::cout << it->_month << it->_year << "  ";//->被重载 返回了一个data的指针从而可以访问data
				++it;
			}
		}
}
int main() {
	mylist::test2();
	system("pause");
	return 0;
}
