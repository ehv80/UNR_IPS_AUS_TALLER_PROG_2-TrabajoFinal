#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <glob.h>

using namespace std;

#include "clases.hpp"

#define OPC1    (GLOB_TILDE|GLOB_NOCHECK)
#define OPC2    (OPC1|GLOB_APPEND)

#define FORK(x)         ({ int i=fork(); cerr<<x<<" "<<i<<'\n'; i; })

static void error( const char * s , int err )
{
	char b[MAX_CANON];
	strerror_r( err , b , sizeof(b) );
	cerr << s << ": " << b << '\n';
}

static void glob_error( int error )
{
	cerr << "glob: ";
	switch(err) {
		case GLOB_NOSPACE:
			cerr << "nospace!"; break;
		case GLOB_ABORTED:
			cerr << "aborted!"; break;
		case NO_MATCH:
			cerr << "nomatch!"; break;
		default:
			cerr << "oops!";
	}
	cerr << '\n';
}
				
int Cd::exec( enum modo ) {
	glob_t g;
	int r;
	if( ( r = glob( camino, GLOB_NOCHECK|GLOB_TILDE, NULL, &g)))
		glob_error(r);
	if( chdir( g.gl_path[0]) )
		error("cd", errno);
	return 0;
}

char * Comando::path( char * p )
{
	char * tmp = new char[1024];
	if(strchr(p, '/')!=0) {
		strcpy(tmp, p);
		return tmp;
	}
	char env[1024];
	strcpy(env, getenv("PATH"));
	char *pc=strtok(env, ":");
	do {
		strcat(strcat(strcpy(tmp, pc), "/"), p);
		if(access(tmp, X_OK)==0)
			return tmp;
	} while((pc=strtok(0, ":"))!=0);
	return p;
}

Comando::~Comando() {
	delete prog;
	int i;
	for( i=0; args[i]; i++)
		delete args[i];
	delete args;
}

int Comando::exec(enum modo m)
{
	programa = path( programa );
	if(m == __Fork && FORK("Comando") !=0 ) {
		int status;
		wait(&status);
		return status;
	}
	glob_t pg;
	int r;
	if((r=glob(argumentos[0], OPC1, NULL, &pg)))
		glob_error(r);
	int i;
	for( i = 1; argumentos[i]; i++)
		if( ( r = glob( argumentos[i], OPC2, NULL, &pg ) ) )
			glob_error(r);
	execv( programa, pg.gl_pathv );
	exit(-1);
	return 0;
}

int Pipe::exec(enum modo m)
{
	int pip[2];
	if(m == __Fork && fork()!= 0 )
		wait(NULL);
	else {
		if( pipe(pip) ) {
			error( "pipe", errno );
			exit(-1);
		}
		if( FORK( "Pipe 2" ) != 0 ) {
			dup2( pip[1] , 1 );
			close( pip[0] );
			close( pip[1] );
			return i -> exec(__Exec);
		}
		else {
			// completar
			return d -> exec(__Exec);
		}
		exit( -1 );
	}
	return 0;
}

int RedireccionEntrada::exec(enum modo m)
{
	// completar
	return 0;
}
         
int RedireccionSalida::exec(enum modo m)
{
	// completar
	return 0;
}
         
int And::exec(enum modo)
{
	int status;
	if( FORK( "And 1" ) !=0 ) wait(&status);
	else return izquierda -> exec( __Exec );
	if( !WIFEXITED( status ) || WEXITSTATUS( status ) !=0 )
		return -1;
	if( FORK( "And 2" ) !=0 ) wait( &status );
	else return derecha -> exec( __Exec );
	if( WIFEXITED( status ) )
		return WEXITSTATUS( status );
	return -1;
}

int Or::exec(enum modo)
{
	// completar
	return -1;
}


int Secuencia::exec(enum modo m)
{
	// completar
	return -1;
}


int SubShell::exec(enum modo)
{
	// completar
	return status;
}
