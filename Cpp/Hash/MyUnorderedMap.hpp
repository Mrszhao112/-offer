#pragma once
#include "HashTable.hpp"
#include <iostream>
#include <string>
using namespace OPEN_HASH;
using namespace std;

namespace mytest1 {
	template<class K, class V, class Hash=OPEN_HASH::_Hash<K>>
	class unordered_map {
		struct MapKOfT
		{
			const K& operator()(const pair<K, V>& kv) {
				return kv.first;
			}
		};
	public:
		typedef typename HashTable<K, pair<K, V>, MapKOfT, Hash>::iterator iterator;
		iterator begin() {
			return _ht.begin();
		}
		iterator end() {
			return _ht.end();
		}

		pair<iterator, bool> insert(const pair<K, V>& kv) {
			return _ht.insert(kv);
		}
		V& operator[](const K& key) {
			pair<iterator, bool> ret = _ht.insert(make_pair(key, V()));
			return ret.first->second;
		}
	private:
		HashTable<K, pair<K, V>, MapKOfT, Hash> _ht;
	};
	void test() {
		unordered_map<string, string> dic;
		dic.insert(make_pair("aaaa", "AAAA"));
		dic.insert(make_pair("bbbb", "BBBB"));
		dic.insert(make_pair("cccc", "CCCC"));
		dic.insert(make_pair("dddd", "DDDD"));
		auto it = dic.begin();
		while (it != dic.end()) {
			cout <<it->first << endl;
			++it;
		}
	}
}
