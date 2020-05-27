#include <iostream>
#include <string.h>
#include <assert.h>
namespace my_string1 {
	class string {
	public:
		typedef char* iterator;
		iterator begin() {//迭代器
			return _str;
		}
		iterator end() {
			return _str + _size;
		}
		
		string(const char* str = "") { //拷贝构造
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_size + 1];
			strcpy(_str, str);
		}
		~string() {
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
		size_t size() const{
			return _size;
		}
		size_t capacity() const {
			return _capacity;
		}
		char& operator[](size_t i) {
			assert(i < size() && i >= 0);
			return _str[i];
		}
		char& operator[](size_t i) const{
			assert(i < size() && i >= 0);
			return _str[i];
		}
		void reverse(size_t n) {
			if (n > capacity()) {
				char* newchar = new char[n + 1];
				strcpy(newchar, _str);
				delete[] _str;
				_str = newchar;
				_capacity = n;
			}
		}
		void resize(size_t n, char ch = '\0') {
			if (n < _size){
				_str = '\0';
				_size = n;
			}
			else {
				if (n > _capacity) {
					reverse(n);
				}
				for (size_t i = _size; i < n; i++) {
					_str[i] = ch;
				}
				_size = n;
				_str[_size] = '\0';
			}
		}
		void push_back(char ch) {
			if (_size = _capacity) {
				size_t newcapacity = _capacity == 0 ? 2 : 2 * _capacity;
				reverse(newcapacity);
			}
			_str[_size++] = ch;
			_str[_size] = '\0';
		}
		void append(const char* ch) {
			size_t sz = strlen(ch);
			if (_size + sz > _capacity) {
				reverse(_size + sz);
			}
			strcpy(_str + _size, ch);
			_size += sz;
		}
		string& operator+=(char ch) {//加单词
			this->push_back(ch);
			return *this;
		}
		string& operator+=(const char* ch) {//加字符串
			this->append(ch);
			return *this;
		}
		string& insert(size_t pos, char ch) {//插入单词
			assert(pos >= 0 && pos < _size);
			if (_size = _capacity) {
				size_t newcapacity = _capacity == 0 ? 2 : 2 * _capacity;
				reverse(newcapacity);
			}
			size_t end = _size; 
			while (end >= pos) {
				_str[end - 1] = _str[end];
				--end;
			}
			_str[pos] = ch;
			++_size;
			return *this;
		}
		string& insert(size_t pos, const char* str) {//插入字符串
			assert(pos >= 0 && pos < _size);
			size_t len = strlen(str);
			if (_size + len > _capacity) {
				reverse(_size + len);
			}
			size_t end = _size;
			while (end > pos) {
				_str[end + len] = _str[end];
				--end;
			}
			for (int i = 0; i < len; i++) {
				_str[pos++] = str[i];
			}
			//strncpy(_str + pos, str, len);
			_size += len;
			return *this;
		}
		string& erase(size_t pos, size_t len = npos) {//npos为-1
			assert(pos >= 0 && pos < _size);
			if (pos + len >= _size){
				pos = '\0';
				_size = pos;
			}
			else {
				size_t end = _size;
				while (pos + len <= _size) {
					_str[pos] = _str[pos + len];
					pos++;
				}
				_size -= len;
			}
			return *this;
			
		}
		size_t find(char ch, size_t pos = 0) {//从pos位置向后查找
			for (int i = pos; i < _size; ++i) {
				if (_str[i] == ch) {
					return pos;
				}
			}
			return npos;
		}
		size_t find(const char* str, size_t pos = 0) {//strstr找子串
			char* p = strstr(_str, str);
			if (p == nullptr) {
				return npos;
			}
			else {
				return p - _str;
			}
		}
		bool operator==(const string& s) {
			int ret = strcmp(_str, s._str);
			return ret == 0;
		}
		bool operator<(const string& s) {
			int ret = strcmp(_str, s._str);
			return ret < 0;
		}
		//...
	private:
		char* _str;
		size_t _size;
		size_t _capacity;

		static size_t npos;
	};
	size_t string::npos = -1;
	/*istream& operator>>(istream& in, string& s) {
		while (1) {
			char ch;
			ch = in.get();
			if (ch == ' ' || ch == '\n') {
				break;
			}
			else {
				s += ch;
			}
		}
		return in;
	}
	ostream& operator<< (ostream& out, const string& s) {
		for (size_t i = 0; i < s.size(); ++i) {
			std::cout << s[i];
		}
		return out;
	}*/
	
}
