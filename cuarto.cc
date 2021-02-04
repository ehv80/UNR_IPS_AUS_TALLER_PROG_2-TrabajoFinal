#include <iostream>
class Q{
	int i;
	static int j;
	public:
		// constructor
		Q(int i){ j++; this -> i=i; std::cout << "nace" << i << '\n';}

		//destructor
		~Q(){ --j; std::cout << "crepa" << i << '\n'; }

		static int ctos(){ return j; }
	};
int Q::j;
Q a(1), b(2);
int main()
{
	Q *p1, *p2, *p3;
	std::cout << Q::ctos() << '\n'; p1 = new Q(3);
	std::cout << Q::ctos() << '\n'; p1 = new Q(4);
	std::cout << Q::ctos() << '\n'; p1 = new Q(5);
	std::cout << Q::ctos() << '\n';
	std::cout << Q::ctos() << '\n'; delete p1;
	std::cout << Q::ctos() << '\n'; delete p2;
	std::cout << Q::ctos() << '\n'; delete p3,
	return 0;
}
