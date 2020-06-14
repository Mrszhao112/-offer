#pragma once
#include <iostream>
namespace test1 {
	template<class K>
	struct BSTreeNode {
		BSTreeNode* _left;
		BSTreeNode* _right;
		K _key;//存的数据 用模板提高复用性

		BSTreeNode(const K& key)
			:_left(nullptr)
			, _right(nullptr)
			, _key(key)
		{}
	};

	template<class K>
	class BSTree {
		typedef BSTreeNode<K> Node;
	public:
		bool Insert(const K& key) {
			if (_root == nullptr) {
				_root = new Node(key);
				return true;
			}
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
				cur = new Node(key);//找到尾节点 创建新节点 进行链接 
				if (parent->_key < key) {
					parent->_right = cur;
				}
				else {
					parent->_left = cur;
				}
				return true;
			}
		bool Find(const K& key) {
			while(_root) {
				if (_root->_key > key) {
					_root = _root->_left;
				}
				else if (_root->_key < key){
					_root = _root->_right;
				}
				else {
					return true;
				}
			}
			return false;
		}
		//二叉搜索树的删除
		//找到节点 判断节点位置分情况删除
		bool Erase(const K& key) {
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur) {
				if (cur->_key > key) {
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key) {
					parent = cur;
					cur = cur->_right;
				}
				else { //找到
					//删除的是尾节点 无依无靠 直接删除 
					if (cur->_left == nullptr) {//左子树为空
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
					else if (cur->_right == nullptr) {//右子树为空
						if (cur == _root) {
							_root = _root->_left;
							delete cur;
						}
						else if (parent->_key > cur->_key) {
							parent->_left = cur->_left;
							delete cur;
						}
						else {
							parent->_right = cur->_left;
							delete cur;
						}
					}
					else {
						Node* rightMinPartent = cur;
						Node* rightMin = cur->_right;
						while (rightMin->_left) {//找右子树最小的节点， 最左
							rightMinPartent = rightMin;
							rightMin = rightMin->_left;
						}
						cur->_key = rightMin->_key;//替换删除
						//删除右子树最左节点
						if (rightMin == rightMinPartent->_left) {
							rightMinPartent->_left = rightMin->_right;
						}
						else {
							rightMinPartent->_right = rightMin->_right;

							delete rightMin;
						}
					}
					return true;
				}
			}
			return false; //没找到跳出
		}
		void _InOrder(Node* root) {
			if (root == nullptr) {
				return;
			}
			_InOrder(root->_left);
			std::cout << root->_key << " ";
			_InOrder(root->_right);
		}
		void InOder() {
			_InOrder(_root);
			std::cout << std::endl;
		}
	private:
		Node* _root = nullptr;
	};
	void mytest() {
		BSTree<int> t;
		int a[] = { 1,2,3,4,2,3,5,2,9 };
		for (auto e : a) {
			t.Insert(e);
		}
		t.InOder();
		std::cout << t.Find(1) <<std::endl;
		t.Erase(1);
		t.Erase(5);
		t.Erase(4);
		t.Erase(2);
		t.Erase(4);
		t.Erase(3);
		t.Erase(9);
		t.InOder();
	}
};
