template<class T>
struct AVLTreeNode {
	AVLTreeNode(const T& k) 
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_data(k)
		,_bf(0)
	{}
	AVLTreeNode<T>* _left;
	AVLTreeNode<T>* _right;
	AVLTreeNode<T>* _parent;
	T _data;
	int _bf;
};
template<class T>
class AVLTree {
	typedef AVLTreeNode<T> Node;
public:
	bool Insert(const T& k) {
		if (_root == nullptr) {//空树直接创建
			_root = new Node(k);
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur) {
			if (cur->_data > k) {
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_data < k) {
				parent = cur;
				cur = cur->_right;
			}
			else {//相等不插入
				return false;
			}
		}
		//找到空位置 创建节点进行插入
		cur = new Node(k);
		if (parent->_data > k) {
			parent->_left = cur;
		}
		else {
			parent->_right = cur;
		}
		cur->_parent = parent;//三叉链还得更新父亲
		while (parent) {
			if (cur == parent->_left) {
				parent->_bf--;
			}
			else {
				parent->_bf++;
			}
			if (parent->_bf == 0) {//说明平衡因子只对当前parent造成改变，并不影响上层
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1) {//从0到-1 1 因此改变了该路径上的平衡因子 
				//向上迭代及进行平衡因子的更新
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2){//不平衡出现了需要进行旋转
				if (parent->_bf == 2) {
					if (cur->_bf == 1) {
						RotateL(parent);
					}
					else if (cur->_bf == -1) {
						RotateRL(parent);
					}
				}
				else if (parent->_bf == -2) {
					if (cur->_bf == -1) {
						RotateR(parent);
					}
					else if (cur->_bf == 1) {
						RotateLR(parent);
					}
				}
			}
		}
	}
	void RotateL(Node* parent) {//左单旋针对的是最最最右边不平衡
		//需要将父节点的右子树更新成根节点
		//并将该右子树的左子树成为父节点新的右子树
		//跟新其余相关节点即可
		Node* subL = parent->_left;
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* pparent = parent->_parent;

		subR->_left = parent;
		parent->_parent = subR;

		parent->_right = subRL;
		if (subRL) {
			subRL->_parent = parent;
		}

		subR->_parent = pparent;
		if (pparent == nullptr) {
			_root = subR;
		}else if (pparent->_left == parent) {
			pparent->_left = subR;
		}
		else {
			pparent->_right = subR;
		}
		parent->_bf = subR->_bf = 0;
	}
	void RotateR(Node* parent) {//右单旋 针对的是最最最左边不平衡
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* pparent = parent->_parent;

		parent->_parent = subL ;
		subL->_left = parent;

		parent->_left = subLR;
		if (subLR != nullptr) {
			subLR->_parent = parent;
		}
		subL->_parent = pparent;
		if (pparent == nullptr) {//根节点
			_root = subL;
		}
		if (pparent->_left == parent) {
			pparent->_left = subL;
		}
		else {
			pparent->_right = subL;
		}
		subL->_bf = parent->_bf = 0;//更新平衡因子
	}
	void RotateLR(Node* parent) {
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;
		RotateL(subL);
		RotateR(parent);

		if (bf == 1) {
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else if (bf == -1) {
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else {
			parent->_bf = 0;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
	}
	void RotateRL(Node* parent) {

	}
private:
	Node* _root = nullptr;
};
int main() {
	return 0;
}

