#include <iostream.h>
enum modo { __Fork, __Exec }
class Accion {
	public: 
		virtual ~Accion(){ }
		virtual int exec( enum modo) =0;
};

// concretas

class Cd : public Accion {
 	char * path;
 	public:
 		Cd( char * path ) : path( path ) {}
 		int exec( enum modo ) { chdir( path ); }
 		~Cd() { delete path; }
};

class Pwd : public Accion {
	public:
	int exec( enum modo ) { cout << get_current_dir_name << '\n' ; return 0; }
};


class Comando : public Accion {
		char *prog ,  **args;
 		static char * path( char * );
public:
	Comando( char * p , char ** a) : prog ( path( p ) ), args(a) {}
 	~Comando() { delete prog ; delete args; }
// Ejercicio: acá hay un problema encontrarlo y subsanarlo
	int exec( enum modo);
	
};

