//mpicc -o conex conexion_mpi.c -I /usr/include/postgresql/ -lpq

#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <libpq-fe.h>
#include<fcntl.h>
#include <stdio_ext.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFSIZE 128
#define TAG 0
char tab[50], cad[100];
double inicio =0.0; /*TIEMPO INICIO DE LA EJECUCION*/
double fin ; /*TIEMPO FINAL DE LA EJECUCION*/
int opc, i, j;
PGconn *conn;
PGresult *resultado;
PGresult *ress;
char consulta_insert[600];

//Datos almacen
char id_alm[20];
//direccion
//numcel

//Reutilizables
char numcel[10]; //se reutiliza con tienda.telefono, camionero.numcel
char curp_emp[18]; //se reutiliza con camiones.matricula
char direccion[40]; //Se reutiliza en tienda.direccion, almacen.direccion
char matricula[7]; //se reutiliza en camiones.matricula y viaje.matricula
char num_rastreo[10]; //se reutiliza en envio.num_rastreo, viaje.num_rastreo

//Datos camionero
//curp_emp
char nombre[50];
int edad;
char tarjeta_cir[17];


//Datos camiones
//matricula
 int cap_peso;
//curp_emp

//Datos tienda
char id_tienda[40];
//numcel
//direccion

//Datos envio
//num_rastreo
char origen[40];
char destino[40];

//Datos viaje
int num_viaje;
char estado[40];




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

        menu();





    }//TERMINA ENTORNO PARALELO
      else
          printf("La tabla esta vacia");

    MPI_Finalize();
	 return 0;
}
void menu(){//Empieza men�?- principal y conexion a la base

	conn = PQsetdbLogin("localhost","5432",NULL,NULL,"proyecto","postgres","toor055");
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

  printf("1.-Camioneros \n");
	printf("2.-Camiones \n");
	printf("3.-Almacen \n");
	printf("4.-Tienda \n");
	printf("5.-Envios \n");
	printf("6.-Viaje  \n \n");



	printf("Selecciona una opcion: \n");
	scanf("%d",&opc);


	switch(opc){
		case 1:
    inicio=MPI_Wtime();
    printf("Haremos una impresion de prueba para ver cuánto tarda\n" );
    resultado = PQexec(conn, "select * from camionero");
  	printf("Filas:%d, Columnas:%d \n",PQntuples(resultado),PQnfields(resultado));
  	if(resultado != NULL){//Empieza ejecucion consulta
  		printf("Imprimiendo los valores de la tabla camionero \n");
  		for (i = 0; i < PQntuples(resultado); i++){ //filas
  					 for (j = 0; j < PQnfields(resultado); j++){//columnas
  								printf("%s\t",PQgetvalue(resultado,i,j));
  					 }//columnas
  							printf("\n");
  	  }//filas
    }//Termina ejecucion consulta


    fin=MPI_Wtime();
    printf("Tiempo Procesamiento: %f\n\n",fin-inicio);



    break;
		case 2:
    inicio=MPI_Wtime();
    printf("Haremos una impresion de prueba para ver cuánto tarda\n" );
    resultado = PQexec(conn, "select * from camiones");
  	printf("Filas:%d, Columnas:%d \n",PQntuples(resultado),PQnfields(resultado));
  	if(resultado != NULL){//Empieza ejecucion consulta
  		printf("Imprimiendo los valores de la tabla camiones \n");
  		for (i = 0; i < PQntuples(resultado); i++){ //filas
  					 for (j = 0; j < PQnfields(resultado); j++){//columnas
  								printf("%s\t",PQgetvalue(resultado,i,j));
  					 }//columnas
  							printf("\n");
  	  }//filas
    }//Termina ejecucion consulta


    fin=MPI_Wtime();
    printf("Tiempo Procesamiento: %f\n\n",fin-inicio);

    break;
		case 3:
    inicio=MPI_Wtime();
    printf("Haremos una impresion de prueba para ver cuánto tarda\n" );
    resultado = PQexec(conn, "select * from almacen");
  	printf("Filas:%d, Columnas:%d \n",PQntuples(resultado),PQnfields(resultado));
  	if(resultado != NULL){//Empieza ejecucion consulta
  		printf("Imprimiendo los valores de la tabla almacen \n");
  		for (i = 0; i < PQntuples(resultado); i++){ //filas
  					 for (j = 0; j < PQnfields(resultado); j++){//columnas
  								printf("%s\t",PQgetvalue(resultado,i,j));
  					 }//columnas
  							printf("\n");
  	  }//filas
    }//Termina ejecucion consulta


    fin=MPI_Wtime();
    printf("Tiempo Procesamiento: %f\n\n",fin-inicio);
    break;
		case 4:
    inicio=MPI_Wtime();
    printf("Haremos una impresion de prueba para ver cuánto tarda\n" );
    resultado = PQexec(conn, "select * from tienda");
  	printf("Filas:%d, Columnas:%d \n",PQntuples(resultado),PQnfields(resultado));
  	if(resultado != NULL){//Empieza ejecucion consulta
  		printf("Imprimiendo los valores de la tabla tienda \n");
  		for (i = 0; i < PQntuples(resultado); i++){ //filas
  					 for (j = 0; j < PQnfields(resultado); j++){//columnas
  								printf("%s\t",PQgetvalue(resultado,i,j));
  					 }//columnas
  							printf("\n");
  	  }//filas
    }//Termina ejecucion consulta


    fin=MPI_Wtime();
    printf("Tiempo Procesamiento: %f\n\n",fin-inicio);
    break;
		case 5:
    inicio=MPI_Wtime();
    printf("Haremos una impresion de prueba para ver cuánto tarda\n" );
    resultado = PQexec(conn, "select * from envio");
  	printf("Filas:%d, Columnas:%d \n",PQntuples(resultado),PQnfields(resultado));
  	if(resultado != NULL){//Empieza ejecucion consulta
  		printf("Imprimiendo los valores de la tabla Envio \n");
  		for (i = 0; i < PQntuples(resultado); i++){ //filas
  					 for (j = 0; j < PQnfields(resultado); j++){//columnas
  								printf("%s\t",PQgetvalue(resultado,i,j));
  					 }//columnas
  							printf("\n");
  	  }//filas
    }//Termina ejecucion consulta


    fin=MPI_Wtime();
    printf("Tiempo Procesamiento: %f\n\n",fin-inicio);
    break;
    case 6:
    inicio=MPI_Wtime();
    printf("Haremos una impresion de prueba para ver cuánto tarda\n" );
    resultado = PQexec(conn, "select * from viaje");
  	printf("Filas:%d, Columnas:%d \n",PQntuples(resultado),PQnfields(resultado));
  	if(resultado != NULL){//Empieza ejecucion consulta
  		printf("Imprimiendo los valores de la tabla viaje \n");
  		for (i = 0; i < PQntuples(resultado); i++){ //filas
  					 for (j = 0; j < PQnfields(resultado); j++){//columnas
  								printf("%s\t",PQgetvalue(resultado,i,j));
  					 }//columnas
  							printf("\n");
  	  }//filas
    }//Termina ejecucion consulta


    fin=MPI_Wtime();
    printf("Tiempo Procesamiento: %f\n\n",fin-inicio);

    break;



        default: menureg();
         break;

	}//termina switch
  menureg();
}
void menuinsertar(){//Empieza insertar

	printf("***************************** \n");
	printf("***********HOLA************** \n");
	printf("***************************** \n");

  printf("1.-Camioneros \n");
	printf("2.-Camiones \n");
	printf("3.-Almacen \n");
	printf("4.-Tienda \n");
	printf("5.-Envios \n");
	printf("6.-Viaje  \n \n");



	printf("Selecciona una opcion: \n");
	scanf("%d",&opc);


	switch(opc){
			case 1:
      __fpurge(stdin);
  		printf("Inserte CURP de camionero (18 caracteres maximo): ");
  		fgets(curp_emp,sizeof(curp_emp),stdin);

  		printf("­\n");
  		printf("Inserte nombre (50 caracteres maximo): ");
      __fpurge(stdin);
  		fgets(nombre,sizeof(nombre),stdin);

  		printf("­\n");

  		printf("Edad: ");
  		scanf("%d", &edad);


  		printf("­\n");
      __fpurge(stdin);
  		printf("Tarjeta de circulacion (17 caracteres maximo): ");
  		fgets(tarjeta_cir,sizeof(tarjeta_cir),stdin);

      printf("­\n");
      printf("Inserte telefono (10 caracteres maximo): ");
      __fpurge(stdin);//BORRA EL CONTENIDO DEL BUFFER DE STDIN*/
      fgets(numcel,sizeof(numcel),stdin);

  		printf("­\n");


  		printf("%s", nombre);


  	  sprintf(consulta_insert,"insert into camionero values('%s','%s','%d','%s','%s')", curp_emp, nombre, edad, tarjeta_cir, numcel);


  		printf("%s", consulta_insert );

      resultado = PQexec(conn,consulta_insert);
      if(resultado != NULL){//Evalúa si resultado cambia de estado
  			printf("Se ha insertado correctamente\n");

  	  }//termina evaluación de resultado


      break;
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
