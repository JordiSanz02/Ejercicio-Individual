#include <stdio.h>
//programa en C para consultar los datos de la base de datos
//Incluir esta libreria para poder hacer las llamadas en shiva2.upc.es
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[]) {
	
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int idPuntos;
	char Nombre[80];
	//char idPartidas [2];
	char consulta [80];
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	
	if (conn==NULL) {
		printf ("Error 0 al crear la conexi??n: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "JUGADOR_BD",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error 1 al inicializar la conexi??n: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	// consulta SQL para obtener una tabla con todos los datos
	// de la base de datos
	err=mysql_query (conn, "SELECT * FROM Jugadores,PARTIDAS,RELACION");
	if (err!=0) {
		printf ("Error 2 al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	resultado = mysql_store_result (conn);
	//Vamos a buscarLos gandores de cada partida jugada	
	// construimos la consulta SQL
	printf ("Dame el nombre del jugador y te daré sus puntos : \n"); 
	scanf ("%s", Nombre);
	
	
	//strcpy (consulta, "SELECT Relacion.PUNTOS FROM (Jugadores,PARTIDAS,RELACION) WHERE Jugadores.NOMBRE = '%s' AND RELACION.iDJ = Jugadores.id");
	sprintf(consulta, "SELECT RELACION.PUNTOS FROM (Jugadores,PARTIDAS,RELACION) WHERE Jugadores.NOMBRE = '%s' AND RELACION.iDJ = Jugadores.id", Nombre);
	//sprintf(idPuntos, "%d", idPuntos);
	//strcat (consulta, idPuntos);
	//strcat (consulta, " AND Relacion.idPartida = Partida.Identificador;");
	// hacemos la consulta 
	err=mysql_query (conn, consulta); 
	if (err!=0) {
		printf ("Error 3 al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//recogemos el resultado de la consulta 
	resultado = mysql_store_result (conn); 
	row = mysql_fetch_row (resultado);
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		// El resultado debe ser una matriz con una sola fila
		// y una columna que contiene el nombre
		printf ("Puntos: %s\n", row[0]);
	// cerrar la conexion con el servidor MYSQL 
	mysql_close (conn);
	exit(0);
}

