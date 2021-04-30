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
void menu();
void conexion();
void menuconsulta();
void menuinsertar();
void menumodificar();
void menueliminar();
void reporte();


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
void menu(){//Empieza men�?- principal y conexion a la base

	conn = PQsetdbLogin("localhost","5432",NULL,NULL,"camioneros","postgres","toor055");
	//puts("Hola Mexico");

	if(PQstatus(conn) != CONNECTION_BAD){
		printf("***************************** \n");
		printf("**HOLA, ESTAMOS CONECTADOS*** \n");
		printf("***************************** \n");

	}else
	 printf("error al conectar a la base de datos");



	printf("1.-Consultar datos \n");
	printf("2.-Insertar datos \n");
	printf("3.-Modificar datos \n \n");
	printf("4.-Eliminar datos \n \n");
	printf("5.-Reporte \n \n");

	printf("Selecciona una opcion: \n");
	scanf("%d",&opc);


	switch(opc){
		case 1: menuconsulta(); break;
		case 2: menuinsertar(); break;
		case 3: menumodificar(); break;
		case 4: menueliminar(); break;
		case 5: reporte();
        default: break;

	}

}
void menureg(){//Empieza men�?- de regreso

	printf("\n \n ");
	printf("***************************** \n");
	printf("****�Que deesas hacer?******* \n");
	printf("***************************** \n");

	printf("1.-Regresar al menu \n");
	printf("2.-Salir \n ");
	printf("Seleccciona una opcion: \n");
	scanf("%d",&opc);

	switch(opc){
		case 1: menu(); break;
		case 2: printf("vuelve pronto"); break;
	}
}//Termina men�?- de regreso

void conexion(){//Empieza conexion

	conn = PQsetdbLogin("localhost","5432",NULL,NULL,"proyecto","postgres","toor055");
	//puts("Hola Mexico");

	if(PQstatus(conn) != CONNECTION_BAD){
				printf("Hola Estamos conectados\n");

	}else
	 printf("error al conectar a la base de datos");


 }//Termina conexion
void menuconsulta(){//Empieza men�?- principal

	printf("***************************** \n");
	printf("***********HOLA************** \n");
	printf("***************************** \n");

	printf("1.-Camiones \n");
	printf("2.-Viajes \n");
	printf("3.-Almacen\n \n");
	printf("4.-Envío \n \n");
	printf("5.-Tienda \n \n");



	printf("Selecciona una opcion: \n");
	scanf("%d",&opc);


	switch(opc){
		case 1: break;
		case 2:  break;
		case 3: break;
		case 4: break;
		case 5: break;



        default: break;

	}

}
void menuinsertar(){//Empieza insertar

	printf("***************************** \n");
	printf("***********HOLA************** \n");
	printf("***************************** \n");

	printf("1.-Camiones \n");
	printf("2.-Viajes \n");
	printf("3.-Almacen\n \n");
	printf("4.-Envío \n \n");
	printf("5.-Tienda \n \n");



	printf("Selecciona una opcion: \n");
	scanf("%d",&opc);


	switch(opc){
			case 1: break;
			case 2:  break;
			case 3: break;
			case 4: break;
			case 5: break;
      default: break;

	}

}//termina insertar
void menumodificar(){//Empieza modificar

	printf("***************************** \n");
	printf("***********HOLA************** \n");
	printf("***************************** \n");

	printf("1.-Camiones \n");
	printf("2.-Viajes \n");
	printf("3.-Almacen\n \n");
	printf("4.-Envío \n \n");
	printf("5.-Tienda \n \n");



	printf("Selecciona una opcion: \n");
	scanf("%d",&opc);


	switch(opc){
		case 1: break;
		case 2:  break;
		case 3: break;
		case 4: break;
		case 5: break;



        default: break;

	}

}//termina modificar
void menueliminar(){//Empieza menu eliminar

	printf("***************************** \n");
	printf("***********HOLA************** \n");
	printf("***************************** \n");

	printf("1.-Camiones \n");
	printf("2.-Viajes \n");
	printf("3.-Almacen\n \n");
	printf("4.-Envío \n \n");
	printf("5.-Tienda \n \n");



	printf("Selecciona una opcion: \n");
	scanf("%d",&opc);


	switch(opc){
		case 1: break;
		case 2:  break;
		case 3: break;
		case 4: break;
		case 5: break;



        default: break;

	}

}//termina menu eliminar
void reporte(){//Empieza reporte

	printf("***************************** \n");
	printf("***********HOLA************** \n");
	printf("***************************** \n");



}//termina reporte
