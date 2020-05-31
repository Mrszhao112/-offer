#include <iostream>
namespace mylist {
	//节点模板
	template<class T> 
	struct __list_node {
		__list_node<T>* _next;
		__list_node<T>* _prev;
		T _data;
		
		__list_node(const T& x = T())
			:_next(nullptr)
			, _prev(nullptr)
			, _data(x)
		{}
	};

	//迭代器模板
	template<class T,class Ref, class Ptr>
	struct __list_iterator {
		typedef __list_node<T> Node;
		typedef __list_iterator<T,Ref,Ptr> Self;
		Node* _node;
		__list_iterator(Node* node)
			:_node(node)
		{}
		Ref operator*() {
			return _node->_data;
		}
		Ptr operator->() {
			return &_node->_data;
		}
		Self& operator++() {
			_node = _node->_next;
			return *this;
		}
		Self operator++(int) {
			Self tmp(*this);
			++(*this);
			return tmp;
		}
		Self& operator--() {
			_node = _node->_next;
			return *this;
		}
		Self operator--(int) {
			Self tmp(*this);
			--(*this);
			return tmp;
		}
		bool operator!=(const Self& it) {
			return _node != it._node;
		}
		bool operator==(const Self& it) {
			return _node == it._node;
		}
	};

	//list类模板
	template<class T>
	class list {
		typedef __list_node<T> Node;
	public:
		typedef __list_iterator<T, T&, T*> iterator;//一个const一个非const
		typedef __list_iterator<T, const T&, const T*> const_iterator;

		iterator begin() {
			return iterator(_head->_next);
		}
		iterator end() {
			return iterator(_head);
		}
		const_iterator begin() const {
			return const_iterator(_head->_next);
		}
		const_iterator end() const {
			return const_iterator(_head);
		}
		list() {
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}
		list(const list<T>& l1) {
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			const_iterator it = l1.begin();
			/*while (it != l1.end()) {
				push_back(*it);
				++it;
			}*/
			for (auto e : l1) {
				push_back(e);
			}
		}
		
		//赋值运算符重载的现代写法和传统写法
		/*list<T> operator=(const list<T> l1) {
			if (*this != l1) {
				clear();
				const_iterator it = l1.begin();
				for (auto e : v) {
					push_back(e);
				}
			}
			return *this;
		}*/
		list<T> operator=(const list<T> l1) {
			swap(_head, l1._head);
			return *this;

		}
		void clear() {
			iterator it = begin();
			while (it != end()) {
				//it = erase(it);
				erase(it++);
			}
		}
		iterator erase(iterator pos) {///////////////////////////////到底要不要返回值
			//assert(pos != end());
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;
			delete cur;
			prev->_next = next;
			next->_prev = prev;
			return iterator(next);
		}
		void insert(iterator pos, const T& x) {
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* newNode = new Node(x);

			prev->_next = newNode;
			newNode->_prev = prev;
			newNode->_next = cur;
			cur->_prev = newNode;
		}
		void push_back(const T& x) {
			insert(end(), x);
		}
		void pop_back() {
			erase(--end());
		}
		void push_front(const T& x) {
			insert(begin(), x);
		}
		void pop_front() {
			erase(begin());
		}
		~list() {
			clear();
			delete _head;
			_head = nullptr;
		}
	private:
		Node* _head;
	};
	void print_list(const list<int>& l1) {
		list<int>::const_iterator it = l1.begin();
		while (it != l1.end()) {
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;
	}
}
int main() {
	mylist::list<int> l1;
	l1.push_back(11);
	l1.push_back(12);
	l1.push_back(13);
	l1.push_back(14);
	mylist::print_list(l1);
	l1.clear();
	l1.push_front(1);
	mylist::print_list(l1);

	system("pause");
	return 0;
}
