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
char id_alm[21];
//direccion
//numcel

//Reutilizables
char numcel[11]; //se reutiliza con tienda.telefono, camionero.numcel
char curp_emp[19]; //se reutiliza con camiones.matricula
char direccion[41]; //Se reutiliza en tienda.direccion, almacen.direccion
char matricula[8]; //se reutiliza en camiones.matricula y viaje.matricula
char num_rastreo[11]; //se reutiliza en envio.num_rastreo, viaje.num_rastreo

//Datos camionero
//curp_emp
char nombre[51];
int edad;
char tarjeta_cir[18];


//Datos camiones
//matricula
 int cap_peso;
//curp_emp

//Datos tienda
char id_tienda[41];
//numcel
//direccion

//Datos envio
//num_rastreo
int volumen;
char origen[41];
char destino[41];

//Datos viaje
int num_viaje;
char estado[41];




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
	printf("******HOLA MENU INSERTA****** \n");
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
      __fpurge(stdin);
  		printf("Inserte CURP de camionero (18 caracteres maximo): ");
  		fgets(curp_emp,sizeof(curp_emp),stdin);
      curp_emp[strlen(curp_emp)-1]='\0'; //Limpia el buffer del enter

  		printf("­\n");
  		printf("Inserte nombre (50 caracteres maximo): ");
      __fpurge(stdin);
  		fgets(nombre,sizeof(nombre),stdin);
      nombre[strlen(nombre)-1]='\0'; //Limpia el buffer del enter

  		printf("­\n");

  		printf("Edad: ");
  		scanf("%d", &edad);


  		printf("­\n");
      __fpurge(stdin);
  		printf("Tarjeta de circulacion (17 caracteres maximo): ");
  		fgets(tarjeta_cir,sizeof(tarjeta_cir),stdin);
      tarjeta_cir[strlen(tarjeta_cir)-1]='\0'; //Limpia el buffer del enter

      printf("­\n");
      printf("Inserte telefono (10 caracteres maximo): ");
      __fpurge(stdin);//BORRA EL CONTENIDO DEL BUFFER DE STDIN*/
      fgets(numcel,sizeof(numcel),stdin);
      numcel[strlen(numcel)-1]='\0'; //Limpia el buffer del enter

  		printf("­\n");


  		printf("%s", nombre);


  	  sprintf(consulta_insert,"insert into camionero values('%s','%s','%d','%s','%s')", curp_emp, nombre, edad, tarjeta_cir, numcel);


  		printf("%s", consulta_insert );

      resultado = PQexec(conn,consulta_insert);
      if(resultado != NULL){//Evalúa si resultado cambia de estado
  			printf("Se ha insertado correctamente\n");

  	  }//termina evaluación de resultado

      fin=MPI_Wtime();
      printf("Tiempo Procesamiento: %f\n\n",fin-inicio);
      break;
			case 2:
      inicio=MPI_Wtime();
      __fpurge(stdin);
  		printf("Inserte matricula de camion (7 caracteres maximo): ");
  		fgets(matricula,sizeof(matricula),stdin);
      matricula[strlen(matricula)-1]='\0'; //Limpia el buffer del enter

  		printf("­\n");
  		printf("Inserte CURP de camionero (50 caracteres maximo): ");
      __fpurge(stdin);
  		fgets(curp_emp,sizeof(curp_emp),stdin);
      curp_emp[strlen(curp_emp)-1]='\0'; //Limpia el buffer del enter

  		printf("­\n");

  		printf("Capacidad de peso de camion: ");
  		scanf("%d", &cap_peso);



  		printf("­\n");


  		printf("%s", nombre);


  	  sprintf(consulta_insert,"insert into camiones(matricula, curp_emp, cap_peso) values('%s','%s','%d')", matricula, curp_emp, cap_peso);


  		printf("%s", consulta_insert );

      resultado = PQexec(conn,consulta_insert);
      if(resultado != NULL){//Evalúa si resultado cambia de estado
  			printf("Se ha insertado correctamente\n");

  	  }//termina evaluación de resultado
      fin=MPI_Wtime();
      printf("Tiempo Procesamiento: %f\n\n",fin-inicio);
      break;


			case 3:
      inicio=MPI_Wtime();
      __fpurge(stdin);
  		printf("Inserte el id del almacen (20 caracteres maximo): ");
  		fgets(id_alm,sizeof(id_alm),stdin);
      id_alm[strlen(id_alm)-1]='\0'; //Limpia el buffer del enter

  		printf("­\n");
  		printf("Inserte direccion de almacen(40 caracteres maximo): ");
      __fpurge(stdin);
  		fgets(direccion,sizeof(direccion),stdin);
      direccion[strlen(direccion)-1]='\0'; //Limpia el buffer del enter

  		printf("­\n");

      printf("Inserte numero de telefono de almacen(10 caracteres maximo): ");
      __fpurge(stdin);
  		fgets(numcel,sizeof(numcel),stdin);
      numcel[strlen(numcel)-1]='\0'; //Limpia el buffer del enter
  		printf("­\n");


  	  sprintf(consulta_insert,"insert into almacen values('%s','%s','%s')", id_alm, direccion, numcel);
  		printf("%s", consulta_insert );

      resultado = PQexec(conn,consulta_insert);
      if(resultado != NULL){//Evalúa si resultado cambia de estado
  			printf("Se ha insertado correctamente\n");

  	  }//termina evaluación de resultado

      fin=MPI_Wtime();
      printf("Tiempo Procesamiento: %f\n\n",fin-inicio);
      break;


			case 4:
      inicio=MPI_Wtime();
      __fpurge(stdin);
  		printf("Inserte el id de la tienda (20 caracteres maximo): ");
  		fgets(id_tienda,sizeof(id_tienda),stdin);
      id_tienda[strlen(id_tienda)-1]='\0'; //Limpia el buffer del enter

  		printf("­\n");
  		printf("Inserte direccion de almacen(40 caracteres maximo): ");
      __fpurge(stdin);
  		fgets(direccion,sizeof(direccion),stdin);
      direccion[strlen(direccion)-1]='\0'; //Limpia el buffer del enter

  		printf("­\n");

      printf("Inserte numero de telefono de tienda(10 caracteres maximo): ");
      __fpurge(stdin);
  		fgets(numcel,sizeof(numcel),stdin);
      numcel[strlen(numcel)-1]='\0'; //Limpia el buffer del enter

  		printf("­\n");
  	  sprintf(consulta_insert,"insert into tienda values('%s','%s','%s')", id_tienda, direccion, numcel);
  		printf("%s", consulta_insert );

      resultado = PQexec(conn,consulta_insert);
      if(resultado != NULL){//Evalúa si resultado cambia de estado
  			printf(" \n Se ha insertado correctamente\n");

  	  }//termina evaluación de resultado
      fin=MPI_Wtime();
      printf("Tiempo Procesamiento: %f\n\n",fin-inicio);

      break;
			case 5:
      inicio=MPI_Wtime();
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
      __fpurge(stdin);
  		printf("Inserte el numero de rastreo (10 caracteres maximo): ");
  		fgets(num_rastreo,sizeof(num_rastreo),stdin);
      num_rastreo[strlen(num_rastreo)-1]='\0'; //Limpia el buffer del enter


  		printf("­\n");
  		printf("Inserte origen(40 caracteres maximo y debe ser almacen): ");
      __fpurge(stdin);
  		fgets(origen,sizeof(origen),stdin);
      origen[strlen(origen)-1]='\0'; //Limpia el buffer del enter

  		printf("­\n");

      printf("Inserte destino y debe ser tienda(40 caracteres maximo): ");
      __fpurge(stdin);
  		fgets(destino,sizeof(destino),stdin);
      destino[strlen(destino)-1]='\0'; //Limpia el buffer del enter
  		printf("­\n");

      printf("Cantidad de articulos de envio: ");
  		scanf("%d", &volumen);

  	  sprintf(consulta_insert,"insert into envio values('%s','%s','%s', '%d')", num_rastreo, origen, destino, volumen);
  		printf("%s", consulta_insert );

      resultado = PQexec(conn,consulta_insert);
      if(resultado != NULL){//Evalúa si resultado cambia de estado
  			printf(" \n Se ha insertado correctamente\n");

  	  }//termina evaluación de resultado


      fin=MPI_Wtime();
      printf("Tiempo Procesamiento: %f\n\n",fin-inicio);

      break;

      case 6:

      inicio=MPI_Wtime();

      //Se imprime tabla camiones para saber matricula
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

      //Se imprime tabla envio para saber el num_rastreo
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

  		printf("­\n");
  		printf("Inserte situacion del viaje (Donde se encuentra y la circunstancia en general):");
      __fpurge(stdin);
  		fgets(estado,sizeof(estado),stdin);
      estado[strlen(estado)-1]='\0'; //Limpia el buffer del enter

  		printf("­\n");

      printf("Inserte matricula de camion que lo lleva: ");
      __fpurge(stdin);
  		fgets(matricula,sizeof(matricula),stdin);
      matricula[strlen(matricula)-1]='\0'; //Limpia el buffer del enter
  		printf("­\n");

      printf("Inserte numero de rastreo del paquete: ");
      __fpurge(stdin);
      fgets(num_rastreo,sizeof(num_rastreo),stdin);
      num_rastreo[strlen(num_rastreo)-1]='\0'; //Limpia el buffer del enter
      printf("­\n");



  	  sprintf(consulta_insert,"insert into viaje(estado, matricula, num_rastreo) values('%s','%s', '%s')", estado, matricula, num_rastreo);
  		printf("%s", consulta_insert );

      resultado = PQexec(conn,consulta_insert);
      if(resultado != NULL){//Evalúa si resultado cambia de estado
  			printf(" \n Se ha insertado correctamente\n");

  	  }//termina evaluación de resultado

      fin=MPI_Wtime();
      printf("Tiempo Procesamiento: %f\n\n",fin-inicio);
      break;
      default: break;

	}
  menureg();

}//termina insertar
void menumodificar(){//Empieza modificar
char curp_empnew[19];
char matriculanew[8];
char id_almnew[21];
char id_tiendanew[41];
char num_rastreonew[11];


	printf("***************************** \n");
	printf("*****HOLA MENU MODIFICAR***** \n");
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
    __fpurge(stdin);
    printf("Inserte CURP de camionero que desea modificar (18 caracteres maximo): ");
    fgets(curp_emp,sizeof(curp_emp),stdin);
    curp_emp[strlen(curp_emp)-1]='\0'; //Limpia el buffer del enter

    __fpurge(stdin);
    printf("Inserte CURP nueva de camionero (18 caracteres maximo): ");
    fgets(curp_empnew,sizeof(curp_empnew),stdin);
    curp_empnew[strlen(curp_empnew)-1]='\0'; //Limpia el buffer del enter

    printf("­\n");
    printf("Inserte nombre (50 caracteres maximo): ");
    __fpurge(stdin);
    fgets(nombre,sizeof(nombre),stdin);
    nombre[strlen(nombre)-1]='\0'; //Limpia el buffer del enter

    printf("­\n");

    printf("Edad: ");
    scanf("%d", &edad);


    printf("­\n");
    __fpurge(stdin);
    printf("Tarjeta de circulacion (17 caracteres maximo): ");
    fgets(tarjeta_cir,sizeof(tarjeta_cir),stdin);
    tarjeta_cir[strlen(tarjeta_cir)-1]='\0'; //Limpia el buffer del enter

    printf("­\n");
    printf("Inserte telefono (10 caracteres maximo): ");
    __fpurge(stdin);//BORRA EL CONTENIDO DEL BUFFER DE STDIN*/
    fgets(numcel,sizeof(numcel),stdin);
    numcel[strlen(numcel)-1]='\0'; //Limpia el buffer del enter

    printf("­\n");


    printf("%s", nombre);

    __fpurge(stdin);
    sprintf(consulta_insert,"UPDATE camionero SET curp_emp='%s', nombre='%s', edad='%d', tarjeta_cir='%s', numcel='%s' WHERE curp_emp= '%s';", curp_empnew, nombre, edad, tarjeta_cir, numcel, curp_emp);


    printf("%s", consulta_insert );

    resultado = PQexec(conn,consulta_insert);
    if(resultado != NULL){//Evalúa si resultado cambia de estado
      printf("Se ha insertado correctamente\n");

    }//termina evaluación de resultado

    fin=MPI_Wtime();
    printf("Tiempo Procesamiento: %f\n\n",fin-inicio);
    break;


		case 2:
    inicio=MPI_Wtime();
    __fpurge(stdin);
    printf("Inserte matricula de camion que desea modificar(7 caracteres maximo): ");
    fgets(matricula,sizeof(matricula),stdin);
    matricula[strlen(matricula)-1]='\0'; //Limpia el buffer del enter

    __fpurge(stdin);
    printf("Inserte nueva matricula de camion (7 caracteres maximo): ");
    fgets(matriculanew,sizeof(matriculanew),stdin);
    matriculanew[strlen(matriculanew)-1]='\0'; //Limpia el buffer del enter

    printf("­\n");
    printf("Inserte CURP de camionero (50 caracteres maximo): ");
    __fpurge(stdin);
    fgets(curp_emp,sizeof(curp_emp),stdin);
    curp_emp[strlen(curp_emp)-1]='\0'; //Limpia el buffer del enter

    printf("­\n");

    printf("Capacidad de peso de camion: ");
    scanf("%d", &cap_peso);



    printf("­\n");


    printf("%s", nombre);


    sprintf(consulta_insert,"UPDATE camiones SET matricula='%s', curp_emp='%s', cap_peso='%d'  WHERE matricula='%s';", matriculanew, curp_emp, cap_peso, matricula);


    printf("%s", consulta_insert );

    resultado = PQexec(conn,consulta_insert);
    if(resultado != NULL){//Evalúa si resultado cambia de estado
      printf("Se ha insertado correctamente\n");

    }//termina evaluación de resultado
    fin=MPI_Wtime();
    printf("Tiempo Procesamiento: %f\n\n",fin-inicio);


    break;
		case 3:
    inicio=MPI_Wtime();
    __fpurge(stdin);
    printf("Inserte el id del almacen que desea modificar(20 caracteres maximo): ");
    fgets(id_alm,sizeof(id_alm),stdin);
    id_alm[strlen(id_alm)-1]='\0'; //Limpia el buffer del enter

    __fpurge(stdin);
    printf("Inserte el id nuevo del almacen (20 caracteres maximo): ");
    fgets(id_almnew,sizeof(id_almnew),stdin);
    id_almnew[strlen(id_almnew)-1]='\0'; //Limpia el buffer del enter

    printf("­\n");
    printf("Inserte direccion de almacen(40 caracteres maximo): ");
    __fpurge(stdin);
    fgets(direccion,sizeof(direccion),stdin);
    direccion[strlen(direccion)-1]='\0'; //Limpia el buffer del enter

    printf("­\n");

    printf("Inserte numero de telefono de almacen(10 caracteres maximo): ");
    __fpurge(stdin);
    fgets(numcel,sizeof(numcel),stdin);
    numcel[strlen(numcel)-1]='\0'; //Limpia el buffer del enter

    printf("­\n");
    sprintf(consulta_insert,"UPDATE almacen SET id_alm='%s', direccion='%s', telefono='%s' WHERE id_alm= '%s';", id_almnew, direccion, numcel, id_alm);
    printf("%s", consulta_insert );

    resultado = PQexec(conn,consulta_insert);
    if(resultado != NULL){//Evalúa si resultado cambia de estado
      printf("Se ha insertado correctamente\n");

    }//termina evaluación de resultado

    fin=MPI_Wtime();
    printf("Tiempo Procesamiento: %f\n\n",fin-inicio);


    break;
    case 4:
    inicio=MPI_Wtime();
    __fpurge(stdin);
    printf("Inserte el id de la tienda que desea modificar (20 caracteres maximo): ");
    fgets(id_tienda,sizeof(id_tienda),stdin);
    id_tienda[strlen(id_tienda)-1]='\0'; //Limpia el buffer del enter

    __fpurge(stdin);
    printf("Inserte el id nuevo de la tienda (20 caracteres maximo): ");
    fgets(id_tiendanew,sizeof(id_tiendanew),stdin);
    id_tiendanew[strlen(id_tiendanew)-1]='\0'; //Limpia el buffer del enter

    printf("­\n");
    printf("Inserte direccion de almacen(40 caracteres maximo): ");
    __fpurge(stdin);
    fgets(direccion,sizeof(direccion),stdin);
    direccion[strlen(direccion)-1]='\0'; //Limpia el buffer del enter

    printf("­\n");

    printf("Inserte numero de telefono de tienda(10 caracteres maximo): ");
    __fpurge(stdin);
    fgets(numcel,sizeof(numcel),stdin);
    numcel[strlen(numcel)-1]='\0'; //Limpia el buffer del enter


    printf("­\n");
    sprintf(consulta_insert,"UPDATE tienda SET id_tienda='%s', direccion='%s', telefono='%s' WHERE id_tienda=     '%s'; ", id_tiendanew, direccion, numcel, id_tienda);
    printf("%s", consulta_insert );

    resultado = PQexec(conn,consulta_insert);
    if(resultado != NULL){//Evalúa si resultado cambia de estado
      printf(" \n Se ha insertado correctamente\n");

    }//termina evaluación de resultado
    fin=MPI_Wtime();
    printf("Tiempo Procesamiento: %f\n\n",fin-inicio);

    break;



    case 5:
    inicio=MPI_Wtime();
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

    __fpurge(stdin);
    printf("Inserte el numero de rastreo que desea modificar (10 caracteres maximo): ");
    fgets(num_rastreo,sizeof(num_rastreo),stdin);
    num_rastreo[strlen(num_rastreo)-1]='\0'; //Limpia el buffer del enter

    __fpurge(stdin);
    printf("Inserte el nuevo numero de rastreo (10 caracteres maximo): ");
    fgets(num_rastreonew,sizeof(num_rastreonew),stdin);
    num_rastreonew[strlen(num_rastreonew)-1]='\0'; //Limpia el buffer del enter

    printf("­\n");
    printf("Inserte origen(40 caracteres maximo y debe ser almacen): ");
    __fpurge(stdin);
    fgets(origen,sizeof(origen),stdin);
    origen[strlen(origen)-1]='\0'; //Limpia el buffer del enter

    printf("­\n");

    printf("Inserte destino y debe ser tienda(40 caracteres maximo): ");
    __fpurge(stdin);
    fgets(destino,sizeof(destino),stdin);
    destino[strlen(destino)-1]='\0'; //Limpia el buffer del enter
    printf("­\n");

    printf("Cantidad de articulos de envio: ");
    scanf("%d", &volumen);

    sprintf(consulta_insert,"UPDATE envio SET num_rastreo= '%s', origen= '%s' ,\t   destino= '%s', \t  volumen='%d' WHERE num_rastreo= '%s'; ", num_rastreonew, origen, destino, volumen, num_rastreo);
    printf("%s", consulta_insert );

    resultado = PQexec(conn,consulta_insert);
    if(resultado != NULL){//Evalúa si resultado cambia de estado
      printf(" \n Se ha insertado correctamente\n");

    }//termina evaluación de resultado


    fin=MPI_Wtime();
    printf("Tiempo Procesamiento: %f\n\n",fin-inicio);

    break;

    case 6:

    inicio=MPI_Wtime();
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


    printf("Inserte numero del viaje que desea modificar: ");
    scanf("%d", &num_viaje);


    printf("­\n");
    printf("Inserte nueva situacion del viaje (Donde se encuentra y la circunstancia en general): ");
    __fpurge(stdin);
    fgets(estado,sizeof(estado),stdin);
    estado[strlen(estado)-1]='\0'; //Limpia el buffer del enter

    printf("­\n");

    printf("Inserte matricula de camion que lo lleva: ");
    __fpurge(stdin);
    fgets(matricula,sizeof(matricula),stdin);
    matricula[strlen(matricula)-1]='\0'; //Limpia el buffer del enter
    printf("­\n");

    printf("Inserte numero de rastreo del paquete: ");
    __fpurge(stdin);
    fgets(num_rastreo,sizeof(num_rastreo),stdin);
    num_rastreo[strlen(num_rastreo)-1]='\0'; //Limpia el buffer del enter
    printf("­\n");



    sprintf(consulta_insert,"UPDATE viaje SET estado='%s', matricula='%s', num_rastreo='%s' WHERE num_viaje= '%d';", estado, matricula, num_rastreo, num_viaje);
    printf("%s", consulta_insert );

    resultado = PQexec(conn,consulta_insert);
    if(resultado != NULL){//Evalúa si resultado cambia de estado
      printf(" \n Se ha insertado correctamente\n");

    }//termina evaluación de resultado

    fin=MPI_Wtime();
    printf("Tiempo Procesamiento: %f\n\n",fin-inicio);
    break;



        default: menureg(); break;

	}

menureg();
}//termina modificar
void menueliminar(){//Empieza menu eliminar

  printf("***************************** \n");
	printf("*****HOLA MENU ELIMINAR****** \n");
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
    __fpurge(stdin);
		printf("CURP de camionero que desea eliminar(18 caracteres maximo): ");
		fgets(curp_emp,sizeof(curp_emp),stdin);
    curp_emp[strlen(curp_emp)-1]='\0';



		__fpurge(stdin);
	  sprintf(consulta_insert,"delete from camionero where curp_emp =  '%s'; ", curp_emp);


		printf("%s", consulta_insert );

	//	Empiezo administración de sql



		 resultado = PQexec(conn,consulta_insert);

		if(resultado != NULL){//Empieza ejecucion consulta
			printf("Se ha eliminado correctamente");
						 }//columnas
		printf("\n");
    fin=MPI_Wtime();
    printf("Tiempo Procesamiento: %f\n\n",fin-inicio);
    break;


		case 2:
    inicio=MPI_Wtime();
    __fpurge(stdin);
		printf("Matricula de camion que desea eliminar(7 caracteres maximo): ");
		fgets(matricula,sizeof(matricula),stdin);
    matricula[strlen(matricula)-1]='\0';



		__fpurge(stdin);
	  sprintf(consulta_insert,"delete from camiones where matricula =  '%s'; ", matricula);


		printf("%s", consulta_insert );

	//	Empiezo administración de sql



		 resultado = PQexec(conn,consulta_insert);

		if(resultado != NULL){//Empieza ejecucion consulta
			printf("Se ha eliminado correctamente");
						 }
		printf("\n");

    fin=MPI_Wtime();
    printf("Tiempo Procesamiento: %f\n\n",fin-inicio);
    break;




		case 3:
    inicio=MPI_Wtime();
    __fpurge(stdin);
		printf("Id de almacen que desea eliminar(20 caracteres maximo): ");
		fgets(id_alm,sizeof(id_alm),stdin);
    id_alm[strlen(id_alm)-1]='\0'; //ELIMINA EL BUFFER DE ENTER



		__fpurge(stdin);
	  sprintf(consulta_insert,"delete from almacen \n where id_alm = '%s'; ", id_alm);


		printf("%s", consulta_insert );

	//	Empiezo administración de sql



		 resultado = PQexec(conn,consulta_insert);

		if(resultado != NULL){//Empieza ejecucion consulta
			printf("Se ha eliminado correctamente");
						 }//columnas

    printf("\n");
    fin=MPI_Wtime();
    printf("Tiempo Procesamiento: %f\n\n",fin-inicio);


    break;

		case 4:
    inicio=MPI_Wtime();
    __fpurge(stdin);
		printf("Id de tienda que desea eliminar(40 caracteres maximo): ");
		fgets(id_tienda,sizeof(id_tienda),stdin);
    id_tienda[strlen(id_tienda)-1]='\0'; //ELIMINA EL BUFFER DE ENTER



		__fpurge(stdin);
	  sprintf(consulta_insert,"delete from tienda where id_tienda = '%s';", id_tienda);


		printf("%s", consulta_insert );

	//	Empiezo administración de sql



		 resultado = PQexec(conn,consulta_insert);

		if(resultado != NULL){//Empieza ejecucion consulta
			printf("Se ha eliminado correctamente");
						 }//columnas

    printf("\n");
    fin=MPI_Wtime();
    printf("Tiempo Procesamiento: %f\n\n",fin-inicio);

    break;



		case 5:
    inicio=MPI_Wtime();
    __fpurge(stdin);
		printf("Guia de rastreo que desea eliminar(10 caracteres maximo): ");
		fgets(num_rastreo,sizeof(num_rastreo),stdin);
    num_rastreo[strlen(num_rastreo)-1]='\0'; //ELIMINA EL BUFFER DE ENTER



		__fpurge(stdin);
	  sprintf(consulta_insert,"delete from envio where num_rastreo = '%s';", num_rastreo);


		printf("%s", consulta_insert );

	//	Empiezo administración de sql



		 resultado = PQexec(conn,consulta_insert);

		if(resultado != NULL){//Empieza ejecucion consulta
			printf("Se ha eliminado correctamente");
						 }//columnas

    printf("\n");
    fin=MPI_Wtime();
    printf("Tiempo Procesamiento: %f\n\n",fin-inicio);
    break;


    case 6:

    inicio=MPI_Wtime();
    __fpurge(stdin);
		printf("Numero de viaje que desea eliminar: ");
		scanf("%d",&num_viaje );



		__fpurge(stdin);
	  sprintf(consulta_insert,"delete from envio where num_rastreo = '%d';", num_viaje);


		printf("%s", consulta_insert );

	//	Empiezo administración de sql



		 resultado = PQexec(conn,consulta_insert);

		if(resultado != NULL){//Empieza ejecucion consulta
			printf("Se ha eliminado correctamente");
						 }//columnas

    printf("\n");
    fin=MPI_Wtime();
    printf("Tiempo Procesamiento: %f\n\n",fin-inicio);








    break;



        default: menureg();
        break;

	}
  menureg();

}//termina menu eliminar
void reporte(){//Empieza reporte

	printf("***************************** \n");
	printf("***********HOLA************** \n");
	printf("***************************** \n");



}//termina reporte
