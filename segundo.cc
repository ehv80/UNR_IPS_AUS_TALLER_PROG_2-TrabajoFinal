#include <iostream>

struct S{
	int i;
	S(int i) { S::i=i;}
	int f(){return i;}
};

int main(){
	S a(10),b=10;
	std::cout<<a.f()<<
	' '<< b.f() <<"\n";
return 0;
}
