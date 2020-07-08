#pragma once
#include "HashTable.hpp"
using namespace OPEN_HASH;
using namespace std;

namespace mytest2 {
	template <class K, class Hash = OPEN_HASH::_Hash<K>>
	class unordered_set {
		struct SetKofT 
		{
			const K& operator()(const K& k) {
				return k;
			}
		};
	public:
		typedef typename HashTable<K, K, SetKeyOfT, Hash>::iterator iterator;
		iterator begin() {
			return _ht.begin();
		}
		iterator end() {
			return _ht.end();
		}
		pair<iterator, bool> insert(const K& k) {
			return _ht.insert(k);
		}
	private:
		HashTable<K, K, SetKeyOfT, Hash> _ht;
	};
};
