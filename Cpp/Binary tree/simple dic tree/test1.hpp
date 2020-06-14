#include <iostream>
#include <string>
using namespace std;
template<class T, class V>
struct BSTNode {
	BSTNode<T, V>* _left;
	BSTNode<T, V>* _right;
	T _key;
	V _value;

	BSTNode(const T& key, const V& value)
		:_left(nullptr)
		, _right(nullptr)
		, _key(key)
		, _value(value)
	{}
};

template<class T, class V>
class BST {
	typedef BSTNode<T, V> Node;
public:
	bool Insert(const T& key, const V& value) {
		if (_root == nullptr) {
			_root = new Node(key, value);
			return true;
		}
		else {
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur) {
				if (cur->_key < key) {
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_key > key) {
					parent = cur;
					cur = cur->_left;
				}
				else {
					return false;
				}
			}
			cur = new Node(key, value);
			if (parent->_key > key) {
				parent->_left = cur;
			}
			else {
				parent->_right = cur;
			}
		}
		return true;
	}
	Node* Find(const T& key) {
		if (_root == nullptr) {
			return nullptr;
		}
		else {
			while (_root) {
				if (_root->_key > key) {
					_root = _root->_left;
				}
				else if (_root->_key < key) {
					_root = _root->_right;
				}
				else {
					return _root;
				}
			}
		}
		return nullptr;
	}
	bool Earse(const T& key) {
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur) {
			if (cur->_key < key) {
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key) {
				parent = cur;
				cur = cur->_left;
			}
			else {
				//find it
				if (cur->_left == nullptr) {
					if (cur == _root) {
						_root = _root->_right;
					}
					else if (parent->_key > cur->_key) {
						parent->_left = cur->_right;
					}
					else {
						parent->_right = cur->_right;
					}
					delete cur;
					cur = nullptr;
				}
				else if (cur->_right == nullptr) {
					if (cur == _root) {
						_root = _root->_left;
					}
					else if (parent->_key > cur->_key) {
						parent->_left = cur->_left;
					}
					else {
						parent->_right = cur->_left;
					}
					delete cur;
					cur = nullptr;
				}
				else {
					//is not empty
					//rightMin	
					Node* rightMin = _root->_right;
					Node* rightMinParent = _root;
					while (rightMin->_left) {
						rightMinParent = rightMin;
						rightMin = rightMin->_left;
					}//
					cur->_key = rightMin->_key;
					cur->_value = rightMin->_value;

					if (rightMinParent->_key > rightMin->_key) {
						rightMinParent->_left = rightMin->_right;
					}
					else {
						rightMinParent->_right = rightMin->_right;
					}
					delete rightMin;
					rightMin = nullptr;
				}
				return true;
			}
		}
		return false;
	}
	void InOrder(const Node* root) {
		if (root == nullptr) {
			return;
		}
		InOrder(root->_left);
		std::cout << root->_key << " " << root->_value << std::endl;
		InOrder(root->_right);
	}
	void _InOrder() {
		InOrder(_root);
		std::cout << std::endl;
	}
private:
	Node* _root =nullptr;
};
void mytest() {
	BST<string , string> dic;
	dic.Insert("zhaoyang", "110");
	dic.Insert("zhangdada", "119");
	dic.Insert("zhangda", "114");
	dic.Insert("zhang", "113");
	dic._InOrder();
	
}
