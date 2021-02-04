#include <stdlib.h>
#include <unistd.h>
char * Comando : : path (char * p)
{	
	char * tmp = new char[ 1024 ];
	if( strchr( p , '/' ) != 0 ) {
		strcpy( tmp , p );
		return tmp;
	}
	char env[ 1024 ];
		strcpy( env , getenv("PATH"));
		char * pc = strtok( env , ":");
	do{
		strcat( strcat ( strcpy( tmp , pc ) , "/" ) , p);
		if( acces( tmp, X_OK ) == 0 )
		return tmp;
	} while ( ( pc = strtok( NULL, ":" )) != 0 );
		rerturn p;
};

// hay que agregar a los prototipos
// ver:	 man fun.c
// ver:	 man string.h
// continúa código
int Comando : : exec( enum modo m )
{
	if( m == __Fork && fork() != 0 ) {
	int status;
	wait( &status );
	return status;
}
	glob_k pg;
	int r;
	if( ( r = glob( arg[ 0 ] , GLOB_TILDE | GLOB_NOCHECK , NULL, &pg ) ) )
	glob_error( r );
	for( int i=1 ; arg[ i ] , i++ )
	if(( r = glob( args[i], GLOB_TILDE | GLOB_NOCHECK | GLOB_APPEND ,NULL, &pg) ) )
		glob.error( r );
	execv( prog , pg.gl_pathv );
	exit( -1 );
	return 0;
	
// main de ejemplo

int main()
{
	char ** args = {
		"ls" , "*.c*" , "a*" , NULL
	}
	Comando c("ls" , args );
	c.exec( __Exec );
	return 0;
}
