#include <iostream>
#include <string>
#include <stdio.h>
namespace test1 {
	class Person {
	public:
		void Print() {
			std::cout << "name:" << _name << std::endl;
			std::cout << "age:" << _age << std::endl;
		}
	private:
		std::string _name = "Adam";
		int _age = 20;
	};
	//teacher 和 student 分别继承person
	class Student : public Person {
	protected:
		int _schoolID;
	};
	class Teacher : public Person {
	private:
		int _jobID;
	};

	void mytest() {
		Student s1;
		Teacher s2;
		s1.Print();
		s2.Print();
	}
};
namespace test2 {
	class Person {
	public:
		void Print() {
			std::cout << "name:" << _name << std::endl;
			std::cout << "age:" << _age << std::endl;
		}
	protected:
		std::string _name = "Adam";
	private:
		int _age = 20;
	};
	//teacher 和 student 分别继承person
	class Student : protected Person {
	protected:
		int _schoolID;
	};
	class Teacher : private Person {
	private:
		int _iobID;
	};
	void mytest() {
		Student s1;
		//s1.Print();  错误使用无权限
	}
};
namespace test3 {
	class Person {
	protected:
		std::string _name;
		std::string _grand;
		int _age;
	};
	class Student : public Person {
	public:
		int _ID;
	};
	void mytest() {
		Student s1;//子类
		//派生类可以给基类的对象 指针 引用赋值 叫做切片
		Person p1 = s1;
		Person* p2 = &s1;
		Person& p3 = s1;
		//基类对象一般不可以给派生类对象赋值 下面两种情况除外
		Person* p4 = &s1;
		Student* s2 = (Student*)p4;//对基类进行强制类型转换
		s2->_ID = 100;

		Person* p5 = &p1;//p1实际是存储的派生类 但是切片了 因此当作基类对象指针使用
		Student* s3 = (Student*)p5;
		s3->_ID = 100;

	}
};
//作用域
namespace test4 {
	class Person {
	public:
		Person() {
			std::cout << "Person Base" << std::endl;
		}
	protected:
		std::string _name = "Adam";
	};

	class Student : public Person {
	public:
		void Print() {
			std::cout << "name" << _name << std::endl;
		}
	protected:
		std::string _name = "adam";//构成隐藏或者叫重定义
	};
	void mytest() {
		Student s1;
		s1.Print();
	}
};
namespace test5 {
	class Person {
	public:
		Person(const char* name = "Adam")
			:_name(name)
		{
			std::cout << "Person()" << std::endl;
		}
		Person(const Person& p)
			:_name(p._name)
		{
			std::cout << "Person(&p)" << std::endl;
		}
		Person& operator=(const Person& p) {
			std::cout << "operator" << std::endl;
			if (this != &p) {
				_name = p._name;
			}
			return *this;
		}
		~Person() {
			std::cout << "~person()" << std::endl;
		}
	protected:
		std::string _name;
	};

		class Student : public Person
		{
		public:
			Student(const char* name, int num)
				: Person(name)
				, _num(num)
			{
				std::cout << "Student()" << std::endl;
			}

			Student(const Student& s)
				: Person(s)
				, _num(s._num)
			{
				std::cout << "Student(const Student& s)" << std::endl;
			}

			Student& operator = (const Student& s)
			{
				std::cout << "Student& operator= (const Student& s)" << std::endl;
				if (this != &s)
				{
					Person::operator =(s);
					_num = s._num;
				}
				return *this;
			}

			~Student()
			{
				std::cout << "~Student()" << std::endl;
			}
		protected:
		int _num;
	};
		void mytest() {
			Student s1("Adam", 20);
			Student s2(s1);
			//Student s3("vive", 20);
			//s1 = s3;
		}
};
//菱形继承 多继承
namespace test6 {
	class A {
	public:
		int a;
	};
	class B : virtual public A {
	public:
		int b;
	};
	class C : virtual public A {
	public:
		int c;
	};
	class D : public B, public C {
	public :
		int d;
	};
	void mytest() {
		D d;
		d.B::a = 0;
		d.C::a = 1;
		d.b = 2;
		d.c = 3;
		d.d = 4;
		printf("B->a: %p\n", &(d.B::a));
		printf("C->a: %p\n\n", &(d.C::a));
		printf("D->a: %p\n", &(d.a));
		printf("D->b: %p\n", &(d.b));
		printf("D->c: %p\n", &(d.c));
		printf("D->d: %p\n", &(d.d));
	}
};
namespace test7 {
	class A {
	public:
		int a;
	};
	class B : public A {
	public:
		int b;
	};
	class C : public A {
	public:
		int c;
	};
	class D : public B, public C {
	public:
		int d;
	};
	void mytest() {
		D d;
		d.B::a = 0;
		d.C::a = 1;
		d.b = 2;
		d.c = 3;
		d.d = 4;
		printf("B->a: %p\n", &(d.B::a));
		printf("C->a: %p\n\n", &(d.C::a));
		printf("D->b: %p\n", &(d.b));
		printf("D->c: %p\n", &(d.c));
		printf("D->d: %p\n", &(d.d));
	}
};
using namespace test7;
int main() {
	mytest();
	system("pause");
	return 0;
}
