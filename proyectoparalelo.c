//mpicc -o conex conexion_mpi.c -I /usr/include/postgresql/ -lpq

#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <libpq-fe.h>
#include<fcntl.h>
#define BUFSIZE 128
#define TAG 0
char tab[50], cad[100];
int opc;
PGconn *conn;
PGresult *resultado;
PGresult *ress;

int main(int argc, char *argv[]){
  // int id; /*IDENTIFICADOR DEL PROCESO*/
  // int numNucleos; /*NUMERO DE PROCESOS*/
  // char nombreproc [MPI_MAX_PROCESSOR_NAME]; /*NOMBRE PROCESADOR*/
  // int lnombreproc; /*LONGITUD NOMBRE PROCESADOR*/
  // double tmpinic =0.0; /*TIEMPO INICIO DE LA EJECUCION*/
  // double tmpfin ; /*TIEMPO FINAL DE LA EJECUCION*/
  // PGconn *bd;  //crear que almacena la conexion con una BDs en postgres
  // PGresult *resultado;
  // int i,j,fila,columna,edad;
  //
  // MPI_Init(&argc,&argv);
  // MPI_Comm_rank (MPI_COMM_WORLD,&id) ;
  // MPI_Comm_size(MPI_COMM_WORLD, &numNucleos) ;
  // MPI_Get_processor_name ( nombreproc,& lnombreproc ) ;
  int id,x; /*IDENTIFICADOR DEL PROCESO*/
int numNucleos; /*NUMERO DE PROCESOS*/
char nombreproc [MPI_MAX_PROCESSOR_NAME]; /*NOMBRE PROCESADOR*/
int lnombreproc; /*LONGITUD NOMBRE PROCESADOR*/
double tmpinic =0.0; /*TIEMPO INICIO DE LA EJECUCION*/
double tmpfin ; /*TIEMPO FINAL DE LA EJECUCION*/

/*INICIALIZAMOS EL ENTORNO DE EJECUCION MPI en paralelo*/
MPI_Init(&argc,&argv); //MPI_Init es una función que viene en la libreria mpi.h

/*ALMACENAMOS EL IDENTIFICADOR DEL PROCESO*/
MPI_Comm_rank (MPI_COMM_WORLD,&id) ;

/*ALMACENAMOS EL NUMERO DE PROCESOS*/
MPI_Comm_size(MPI_COMM_WORLD, &numNucleos) ;

/*E/S:NOMBRE DEL PROCESADOR,PROCESO 0*/
MPI_Get_processor_name ( nombreproc,& lnombreproc ) ;

    if(id==0){//EMPIEZA ENTORNO PARALELO
        fprintf(stdout,"\nProceso %d en el procesador: %s --->Encargado de la E/S\n", id , nombreproc) ;
        printf("Numero Procesos: %d\n",numNucleos);
	      conn=PQsetdbLogin("localhost","5432",NULL,NULL,"proyecto","postgres","toor055");

        if(PQstatus(conn) != CONNECTION_BAD){
      				printf("Hola Estamos conectados\n");

      	}else{
          printf("error al conectar a la base de datos");
        }




    }//TERMINA ENTORNO PARALELO
      else
          printf("La tabla esta vacia");

    MPI_Finalize();
	 return 0;
}
