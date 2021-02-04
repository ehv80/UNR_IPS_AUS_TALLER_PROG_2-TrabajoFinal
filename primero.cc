#include <iostream>

struct S{
	int i;
	void f(){ std::cout<<i<<"\n";}
};
int main()
{
	S a,b; a.i=10; b.i=20;
	a.f(); b.f();
	return 0;
}
