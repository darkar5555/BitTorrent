#include <fstream>
#include <iostream>


void create_list_peeers()
{
   ofstream fs("list_peers.txt"); 
}

void print_list_peers()
{
    ifstream 
}

char cadena[128];
   // Crea un fichero de salida
   ofstream fs(".txt"); 

   // Enviamos una cadena al fichero de salida:
   fs << "Hola, mundo" << endl;
   // Cerrar el fichero, 
   // para luego poder abrirlo para lectura:
   fs.close();

   // Abre un fichero de entrada
   ifstream fe("nombre.txt"); 

   // Leeremos mediante getline, si lo hiciéramos 
   // mediante el operador << sólo leeríamos 
   // parte de la cadena:
   fe.getline(cadena, 128);

   cout << cadena << endl;