#include <iostream>
class A{
	public:
		virtual void f(){ std::cout << "A!\n";}
};

class B:public A{
	public:
		void f(){ std::cout << "B!\n";}
};

void f(A *pa)
{
	pa -> f();
}
int main()
{
	A *pa;
	pa = new A;
	B *pb;
	pb = new B;
	f(pa);
	f(pb);
	return 0;
}
