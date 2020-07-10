#pragma once
#include "bites.hpp"
#include <string>
using namespace bit;
using namespace std;
//布隆过滤器 处理多个字符串查询与存储问题 一般没有删除如果要删除需要加上计数器 缺点是不够精确
//精确的可以使用 哈希切割 分块存储存储

namespace Bloom {
	//将字符串特殊化成整形 进行位图映射
	struct HashStr1 {
		size_t operator()(const string& str) {
			size_t hash = 0;
			for (size_t i = 0; i < str.size(); i++) {
				hash *= 131;
				hash += str[i];
			}
			return hash;
		}
	};
	struct HashStr2	{
		size_t operator()(const string& str) {
			size_t hash = 0;
			size_t magic = 63689;
			for (size_t i = 0; i < str.size(); i++) {
				hash *= magic;
				hash += str[i];
				magic *= 378551;
			}
			return hash;
		}
	};
	struct HashStr3 {
		size_t operator()(const string& str) {
			size_t hash = 0;
			for (size_t i = 0; i < str.size(); i++) {
				hash *= 65599;
				hash += str[i];
			}
			return hash;
		}
	};
	template<class K = string, class Hash1 = HashStr1, class Hash2 = HashStr2, class Hash3 = HashStr3 >
	class bloomfilter {
	public:
		bloomfilter(size_t num)
			:_bs(5*num)
			,_N(5*num)
		{}

		void set(const K& key) {
			size_t index1 = Hash1()(key) % _N;
			size_t index2 = Hash2()(key) % _N;
			size_t index3 = Hash3()(key) % _N;
			_bs.set(index1);
			_bs.set(index2);
			_bs.set(index3);
		}
		bool test(const K& key) {
			size_t index1 = Hash1()(key) % _N;
			size_t index2 = Hash2()(key) % _N;
			size_t index3 = Hash3()(key) % _N;
			return _bs.test(index1) && _bs.test(index2) && _bs.test(index3);
		}
	private:
		bitset _bs;
		size_t _N;
	};
	void mytest() {
		bloomfilter<string> bf(100);
		bf.set("12345");
		bf.set("123");
		bf.set("145");
		printf("%d\n", bf.test("123"));
		printf("%d\n", bf.test("12345"));
	}
};
