#include <iostream>
#include <string>
namespace test1 {
	class Person {
	public:
		 void BuyTicket() {
			std::cout << "Person Buy" << std::endl;
		}
	};
	class Student : public Person {
	public:
		 void BuyTicket() {
			std::cout << "Student Buy" << std::endl;
		}
	};
	void Func(Person& p) {
		p.BuyTicket();
	}
	void mytest() {
		Person p;
		Student s;
		Func(p);
		Func(s);
	}
};
namespace test2 {
	class Person {
	public:
		virtual void BuyTicket() {
			std::cout << "Person Buy" << std::endl;
		}
	};
	class Student : public Person {
	public:
		virtual void BuyTicket() {//叫做覆盖或者重写
			std::cout << "Student Buy" << std::endl;
		}
	};
	void Func(Person& p) {//必须通过指针或者引用调用虚函数
		p.BuyTicket();
	}
	void mytest() {
		Person p;
		Student s;
		Func(p);
		Func(s);
	}
};
namespace test3 {
	//协变 允许返回值不同
	class A{};
	class B : public A{};
	class Person {
	public :
		virtual A* f() {
			return new A;
		}
	};
	class Student : public Person {
	public:
		virtual B* f() {
			return new B;
		}
	};
};
namespace test4 {//析构函数的重写
	class Person {
	public:
		virtual ~Person() {
			std::cout << "~Person" << std::endl;
		}
	};
	class Student : public Person {
		virtual ~Student() {//如果不加的话又资源泄漏的危险
			std::cout << "~Student" << std::endl;
		}
	};
	void mytest() {
		Person* p1 = new Person;
		Person* p2 = new Student;
		delete p1;
		delete p2;
	}
};
/*
namespace test5 {
	//final 虚函数不能被继承
	class Car {
	public:
		virtual void Drive() final {}
	};
	class FiveStars : public Car {
	public: 
		virtual void Drive() {//这样会报错
		}
	};
	class House {
	public: 
		virtual void  BigHouse() {}
	};
	class NewHouse : public House{
		virtual void BigHouse() override { //如果不重写会报错 不能放在基类只能放在派生类
		}
	};
	//override 虚函数必须实现重写
}
*/
namespace test6 {//抽象类
	class Car {
	public:
		virtual void Drive() = 0;
	};
	class Benz : public Car {
	public:
		virtual void Drive() {
			std::cout << "This is Benz" << std::endl;
		}
	};
	class BWM : public Car {
	public:
		virtual void Drive() {
			std::cout << "This is BWM" << std::endl;
		}
	};
	//class NoNO : public Car {
	//};
	void mytest() {
		Car* b1 = new Benz;
		Car* b2 = new BWM;
		b1->Drive();
		b2->Drive();
		//Car* c1 = new Car;//不能实现
		//NoNO* n1 = new NoNO;//不能实现
	}
};
namespace test7 {
	//求一个正常的class大小
	class Person {
	public:
		void test() {};
	private:
		int _a;
	};

	class Student {
	public:
		virtual void test() {};
	private:
		int _a;
	};
	void mytest() {
		Person s1;
		Student s2;
		std::cout << sizeof(s1) << std::endl;
		std::cout << sizeof(s2) << std::endl;
	}
	//求一个有虚表的class的大小
};
namespace test8 {
	//student 继承person 打印出指针 深入验证虚表存储的是什么
	class Person {
	public:
		virtual void Example1() {
			std::cout << "pex1" << std::endl;
		}
		virtual void Example2() {
			std::cout << "pex2" << std::endl;
		}
		virtual void Example3() {
			std::cout << "pex3" << std::endl;
		}
		virtual void Example4() {
			std::cout << "pex4" << std::endl;
		}
	private:
		int _a;
	};
	class Student : public Person {
	public:
		virtual void Example1() {
			std::cout << "sex1" << std::endl;
		}
		virtual void Example2() {
			std::cout << "sex2" << std::endl;
		}
		virtual void Example3() {
			std::cout << "sex3" << std::endl;
		}
		virtual void Example5() {
			std::cout << "sex5" << std::endl;
		}
	private:
		int _b;
	};

	typedef void(*VFPTR) ();
	void MyPrint(VFPTR vTable[])
	{
		// 依次取虚表中的虚函数指针打印并调用。调用就可以看出存的是哪个函数
		std::cout << " 虚表地址>" << vTable << std::endl;

		for (int i = 0; vTable[i] != nullptr; ++i)
		{
			printf(" 第%d个虚函数地址 :0X%x,->", i, vTable[i]);
			VFPTR f = vTable[i];
			f();
		}
		std::cout << std::endl;
	}
	int mytest() {
		Person s1;
		Student s2;
		//打印出虚函数表的数值
		VFPTR* vTableb = (VFPTR*)(*(int*)&s1);
		MyPrint(vTableb);
		VFPTR* vTabled = (VFPTR*)(*(int*)&s2);
		MyPrint(vTabled);
		return 0;
	}
};
using namespace std;
namespace test9 {
	class Base1 {
	public:
		virtual void func1() { cout << "Base1::func1" << endl; }
		virtual void func2() { cout << "Base1::func2" << endl; }
	private:
		int b1;
	};
	class Base2 {
	public:
		virtual void func1() { cout << "Base2::func1" << endl; }
		virtual void func2() { cout << "Base2::func2" << endl; }
	private:
		int b2;
	};
	class Derive : public Base1, public Base2 {
	public:
		virtual void func1() { cout << "Derive::func1" << endl; }
		virtual void func3() { cout << "Derive::func3" << endl; }
	private:
		int d1;
	};
	typedef void(*VFPTR) ();
	void PrintVTable(VFPTR vTable[])
	{
		cout << " 虚表地址>" << vTable << endl;
		for (int i = 0; vTable[i] != nullptr; ++i)
		{
			printf(" 第%d个虚函数地址 :0X%x,->", i, vTable[i]);
			VFPTR f = vTable[i];
			f();
		}
		cout << endl;
	}
	void mytest()
	{
		Derive d;
		VFPTR* vTableb1 = (VFPTR*)(*(int*)&d);
		PrintVTable(vTableb1);
		VFPTR* vTableb2 = (VFPTR*)(*(int*)((char*)&d + sizeof(Base1)));
		PrintVTable(vTableb2);
	}
};
using namespace test9;

int main() {
	mytest();
	system("pause");
	return 0;
}
