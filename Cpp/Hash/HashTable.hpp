#pragma once
#include <vector>
using namespace std;

template<class K>
struct SetKeyOfT {
	const K& operator()(const K& key) {
		return key;
	}
};
namespace CLOSE_HASH {
	enum State {
		EMPTY,
		EXITS,
		DELETE,
	};

	template<class T>
	struct HashData {
		T _data;
		State _state;
	};

	template<class K, class T, class KeyOfT>
	class HashTable {
		typedef HashData<T> HashData;
	public:
		bool Insert(const T& d) {
			KeyOfT koft;
			if (_nums * 10 / _tables.size() >= 7) {//增容

			}
			size_t index = koft(d) % _tables.size();
			while (_tables[index]._state == EXITS) {
				if (_tables[index]._data == koft(d)) {
					return false;
				}
				++index;
				if (index == _tables.size()) {
					index = 0;
				}
			}
			_tables[index]._data = d;
			_tables[index]._state = EXITS;
			++_nums;
			return true;
		}
		HashData Find(const K& key) {
			KeyOfT koft;
			size_t index = key % _tables.size();
			while (_tables[index]._state != EMPTY) {
				if (_tables[index]._state == EXITS) {
					if (koft(_tables[index]._data) == key) {
						return _tables[index];
					}
					return nullptr;
				}
				++index;
				if (index == _tables.size()) {
					index = 0;
				}
			}
			return nullptr;
		}
		bool Erase(const K& key) {
			HashData mydata = Find(key);
			if (mydata != nullptr) {
				mydata._state = DELETE;
				--_nums;
				return true;
			}

			return false;
		}
	private:
		vector<HashData> _tables;
		size_t _nums = 0;
	};
};
namespace OPEN_HASH {
	template<class T>
	struct HashNode {
		T _data;
		HashNode<T>* _next;

		HashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{}
	};
	template<class K, class T, class KeyOfT, class Hash> 
	class HashTable;//前置声明
	
	template<class K, class T, class KeyOfT, class Hash>
	struct __HashTableIterator {
		typedef __HashTableIterator<K, T, KeyOfT, Hash> Self;
		typedef HashTable<K, T, KeyOfT, Hash> HT;
		typedef HashNode<T> Node;
		Node* _node;
		HT* _pht;

		__HashTableIterator(Node* node, HT* ht)
			:_node(node)
			,_pht(ht)
		{}

		T& operator*() {
			return _node->_data;
		}
		
		T* operator->() {
			return &_node->_data;
		}

		Self operator++() {
			if (_node->_next) {
				_node = _node->_next;
			}
			else {
				//相当于遍历 走到了下一个桶了
				KeyOfT koft;
				size_t i = _pht->HashFunc(koft(_node->_data)) % _pht->_tables.size();
				++i;
				for (; i < _pht->_tables.size(); ++i) {
					Node* cur = _pht->_tables[i];
					if (cur) {
						_node = cur;
						return *this;
					}
				}
				_node = nullptr;
			}
			return *this;
		}
		bool operator!=(const Self& s) {
			return _node != s._node;
		}
	};

	template<class K>
	struct _Hash {
		const K& operator()(const K& key) {
			return key;
		}
	};

	template<>
	struct _Hash<string>
	{
		size_t operator()(const string& key) {
			size_t hash = 0;
			for (size_t i = 0; i < key.size(); ++i) {
				hash *= 131;
				hash += key[i];
			}
			return hash;
		}
	};
	template<class K, class T, class KeyOfT, class Hash> 
	class HashTable {
		typedef HashNode<T> Node;
	public:
		friend struct __HashTableIterator<K, T, KeyOfT, Hash>;
		typedef __HashTableIterator<K, T, KeyOfT, Hash> iterator;

		iterator begin() {
			for (size_t i = 0; i < _tables.size(); ++i) {
				if (_tables[i]) {
					return iterator(_tables[i], this);
				}
			}
			return end();
		}
		iterator end() {
			return iterator(nullptr, this);
		}
		~HashTable() {
			Clear();
		}
		void Clear() {
			for (size_t i = 0; i < _tables.size(); ++i) {
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
		}
		size_t HashFunc(const K& key) {//调用hash仿函数 返回整数
			Hash hash;
			return hash(key);
		}
		pair<iterator, bool> insert(const T& data) {
			KeyOfT koft;
			if (_tables.size() == _nums) {//增容
				vector<Node*> newTables;
				size_t newSize = _tables.size() == 0 ? 10 : 2 * _tables.size();
				newTables.resize(newSize);
				for (size_t i = 0; i < _tables.size(); ++i) {
					Node* cur = _tables[i];
					while (cur) {
						Node* next = cur->_next;
						size_t index = HashFunc(koft(cur->_data)) % newSize;
						cur->_next = newTables[index];
						newTables[index] = cur;

						cur = next;
					}
					_tables[i] = nullptr;
				}
				_tables.swap(newTables);
			}

			size_t index = HashFunc(koft(data)) % _tables.size();
			//还得查找在不在表中
			Node* cur = _tables[index];
			while (cur) {
				if (koft(cur->_data) == koft(data)) {
					return make_pair(iterator(cur, this), false);//有点问题
				}
				else {
					cur = cur->_next;
				}
			}
			Node* NewNode = new Node(data);
			NewNode->_next = _tables[index];
			_tables[index] = NewNode;
			++_nums;
			return make_pair(iterator(NewNode, this), true);//有点问题
		}
		Node* Find(const K& key) {
			KeyOfT koft;
			size_t index = HashFunc(key) % _tables.size();
			Node* cur = _tables[index];
			while (cur) {
				if (koft(cur->_data) == key) {
					return cur;
				}
				cur = cur->_next;
			}
			return nullptr;
		}
		bool Erase(const K& key) {
			KeyOfT koft;
			size_t index = HashFunc(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[index];
			while (cur) {
				if (koft(cur->_data) == key) {
					if (prev == nullptr) {
						_tables[index] = cur->_next;
					}
					else {
						prev->_next = cur->_next;
					}
					delete cur;
					--_nums;
					return true;
				}
				prev = cur;
				cur = cur->_next;
			}
			return false;
		}
	private:
		vector<Node*> _tables;
		size_t _nums = 0;
	};
};

















