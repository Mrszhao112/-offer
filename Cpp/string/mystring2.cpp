namespace my_string2 {
	//简易版的string 可以实现构造拷贝析构等基本功能
	class string {
	public:
		string(const char* str = "")
			:_str(new char[strlen(str) + 1]) 
		{
			strcpy(_str, str);
		}
		//深拷贝传统写法与现代写法
		string(const string& s1)
			:_str(new char[strlen(s1._str+1)])
		{
			strcpy(_str, s1._str);
		}


		string(const string& s1)
			:_str(nullptr)
		{
			string tmp(s1._str);//掉用构造函数
			swap(_str, tmp);
		}
		string& operator=(string s) {//赋值操作 利用临时变量
			swap(s, _str);
			return *this;
		}
		~string() {
			delete _str;
			_str = nullptr;
		}
		size_t size() {
			return strlen(_str);
		}
		char& operator[](size_t i) {
			return _str[i];
		}
	private:
		char* _str;
	};
}
