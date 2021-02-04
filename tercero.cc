#include <iostream>

struct S{ int i;
	S(int i){S::i=i; std::cout<<i<<"nace\n";}
	~S(){std::cout<<i<<"crepa!\n";}
};
S a(1), b(2);

int main(){
	S c(3), d(4);
	std::cout<<"bloque!\n";
	{
		S e(5);
	}
	std::cout<<"fin bloque!\n";
	return 0;
}
