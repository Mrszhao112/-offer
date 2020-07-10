#pragma once
#include <vector>

using namespace std;
//位图使用
//用于查找100亿个数据中是否存在某个数 
//用于内存不够用的场景

namespace bit {
	class bitset{
	public:
		bitset(size_t N) {
			_bits.resize(N / 32 + 1, 0);
			_num = 0;
		}
		void set(size_t i) {
			size_t index = i / 32;//第几个整形
			size_t pos = i % 32;//整形的第几个位
			_bits[index] |= (1 << pos);//设置
			_num++;
		}
		void reset(size_t i) {
			size_t index = i / 32;//第几个整形
			size_t pos = i % 32;//整形的第几个位

			_bits[index] &= -(1 << pos);
		}
		bool test(size_t i) {
			size_t index = i / 32;//第几个整形
			size_t pos = i % 32;//整形的第几个位
			return _bits[index] & (1 << pos);
		}
		void printt(size_t N) {
			for (size_t i = 0; i < N / 32 + 1; i++) {
				printf("%d\n",_bits[i]);
			}
		}
	private:
		vector<int> _bits;
		size_t _num;
	};
	void mytest() {
		bitset bs(100);
		bs.set(11);
		bs.set(14);
		bs.set(13);
		bs.set(12);
		for (size_t i = 0; i < 100; ++i) {
			printf("%d", bs.test(i));
		}
		printf("\n");
		bs.printt(100);
	}

};
