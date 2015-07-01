#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>
#include <syslog.h>
#include <signal.h>
 
#define FICHERO_PID "/var/run/Tarea3SO2.pid"
 
volatile char bandera_ejecucion = 0;

char response[] = "HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html><HTML><HEAD>"
"<TITLE>Hola mundo</TITLE>"
"</HEAD>"
"<BODY>"
"<P>Hola Mundo</P>"
"</BODY></HTML>\r\n";

void salir( int signum )
{
    bandera_ejecucion = 1;
}
 
int main( void )
{
    struct stat st;
    FILE *fichero_pid;
    pid_t pid;
    pid_t sid;
    if( stat( FICHERO_PID, &st ) == 0 )
    {
        exit( EXIT_FAILURE );
    }
    fichero_pid = fopen( FICHERO_PID, "w" );
    pid = fork();

 if( pid > 0 )
    {
        fprintf( fichero_pid , "%d\n", pid );
        fclose( fichero_pid );
        exit( EXIT_SUCCESS );
    }
    umask( 0 );
    sid = setsid();
int cambio_directorio=chdir( "/" );
    close( STDIN_FILENO );
    close( STDOUT_FILENO );
    close( STDERR_FILENO );

    signal( SIGTERM, salir );



 int entero = 1, cliente;
  struct sockaddr_in direccion_servidor, direccion_cliente;
  socklen_t sin_len = sizeof(direccion_cliente);
 
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    err(1, "No se pudo abrir");
 
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &entero, sizeof(int));
 
  int port = 8080;
  direccion_servidor.sin_family = AF_INET;
  direccion_servidor.sin_addr.s_addr = INADDR_ANY;
  direccion_servidor.sin_port = htons(port);
 
  if (bind(sock, (struct sockaddr *) &direccion_servidor, sizeof(direccion_servidor)) == -1) {
    close(sock);
    err(1, "No se pudo unir");
  }
 
  listen(sock, 5);




    while ( bandera_ejecucion == 0 )
    {
 cliente = accept(sock, (struct sockaddr *) &direccion_cliente, &sin_len);
    if (cliente == -1) {
      perror("No se acepto");
      continue;
    }
 
    write(cliente, response, sizeof(response) - 1); 
    close(cliente);
}


    unlink( FICHERO_PID );
}
