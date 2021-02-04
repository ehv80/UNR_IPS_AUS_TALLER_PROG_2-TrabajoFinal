#include <iostream>

using namespace std;

enum modo { __Fork, __Exec };

/* CLASE ABSTRACTA */
class Accion {
	public: 
		virtual ~Accion(){ }	/* destructor */
		virtual int exec( enum modo) = 0;
};

// concretas que heredan de Accion

class Cd : public Accion {
 	char * camino;
 	public:
 		Cd( char * camino ): camino(camino) {}	/* constructor */
 		~Cd() { delete camino; }	/* destructor */
 		int exec( enum modo ); 		/*{ chdir( path ); }*/
};

class Pwd : public Accion {
	public:
		int exec( enum modo ) { cout << get_current_dir_name << '\n' ; return 0; }
};

class Exit : public Accion {
	public:
		int exec(enum modo) { exit(0); return 0; }
};

class Comando : public Accion {
		char *programa ,  **argumentos;
 		static char * path( char * );
public:
	Comando( char * programa , char ** argumentos) : programa(programa), argumentos(argumentos) {}	/* constructor */
 	~Comando();  			/* destructor */
	int exec( enum modo );	/*{ excecl( path( prog ) , args );*/
};

class And: public Accion {
	        Accion * izquierda, * derecha;
	public:
		And(Accion * izquierda, Accion * derecha) : izquierda(izquierda), derecha(derecha) {}
		~And() { delete izquierda; delete derecha; }
		int exec(enum modo);
};

class Or : public Accion {
		Accion *izquierda, *derecha;
	public:
	        Or(Accion * izquierda, Accion *derecha) : izquierda(izquierda), derecha(derecha) {}
		~Or() { delete izquierda; delete derecha; }
	        int exec(enum modo);
};

class Pipe: public Accion {
		Accion * izquierda, * derecha;
	public:
		Pipe(Accion * izquierda, Accion * derecha): izquierda(izquierda), derecha(derecha) {}
		~Pipe() { delete izquierda; delete derecha; }
		int exec(enum modo);
};

class RedireccionEntrada : public Accion {
		Accion * paccion;
		char * parchivo;
	public:
		RedireccionEntrada( Accion * paccion , char * parchivo) : paccion(paccion), parchivo(parchivo) {}
		~RedireccionEntrada() { delete paccion; delete parchivo; }
		int exec(enum modo);
};

class RedireccionSalida : public Accion {
	Accion * paccion;
	char * parchivo;
	bool append;
public:
RedireccionSalida(Accion * paccion, char * parchivo, bool append) : paccion(paccion), parchivo(parchivo), append(append) {}
	~RedireccionSalida() { delete paccion; delete parchivo; }
	int exec(enum modo);
};

class Secuencia : public Accion {
	        Accion * izquierda, * derecha;
	public:
		Secuencia(Accion * izquierda, Accion * derecha ) : izquierda(izquierda), derecha(derecha) {}
		~Secuencia() { delete izquierda; delete derecha; }
		int exec(enum modo);
};

class SubShell: public Accion {
		Accion * accion;
	public:
	        SubShell(Accion * accion): accion(accion) {}
	        ~Subshell() { delete accion; }
	        int exec(enum modo);
};

