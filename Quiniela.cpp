/************************************************/
/* Nombre: Alejandro                            */
/* Apellidos: Alfonso Albero                    */
/* Práctica final: Gestión de un Videoclub      */
/************************************************/

//Librerías que se incluyen
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <math.h>
using namespace std;

//Definición de constantes
#define TAM 100
#define partidos 10

//Declaración de estructuras
struct partido
{
    string Local;
    string Guion;
    string Visit;
    string Res;
};
struct usuario
{
    string nombre;
    int total;
    int part;
    double rate;
};

//Índice de las funciones
void LeerFichero (partido [TAM*partidos], ifstream &,string [TAM], int &, int &);
void Colorear (partido [TAM*partidos], string [TAM*partidos][2], string [TAM], int, int, int [TAM]);
void GuardarFichero(partido [TAM*partidos], int , int , string, string [TAM*partidos][2], string [TAM], int [TAM]);
void GuardarTabla(string, int , usuario [TAM]);
int main ();

//Implementación de funciones
//Función que lee el fichero y carga el contenido en un vector
void LeerFichero (partido match[TAM*partidos], ifstream &fichero,string nombre[TAM], int &N, int &M)
{
    //Declaración de variables
    string basura;
    int i = 0;
    M = 0;
    N = 0;
    bool ex=false; //Para no detectar como quiniela el post de ejemplo
    do //Compruebo que aun no he llegado al final, y luego paso datos al vector
    {
        getline(fichero,basura);
        if (basura == "QuinielaLMV.txt")
	{
        	if (ex)
        	{
	            fichero >> nombre[M];
	            cout << M+1 << ". " << nombre[M] << endl;
	            for(i=0;i<partidos;i++)
	            {
	            	fichero >> match[M*N+i].Local;
		            fichero >> match[M*N+i].Guion;
		            fichero >> match[M*N+i].Visit;
		            fichero >> match[M*N+i].Res;
			}
	            N = i; //N va a ser 15 siempre, pero dejando este sistema se puede cambiar el numero solo tocando el valor "partidos"
	            M++;
        	}
        	else
        	{
        		ex=true;
		}
	}
    }while (fichero.eof( ) == false);
}

//para poner los colorines
void Colorear (partido match[TAM*partidos], string label[TAM*partidos][2], string resultados[TAM], int N, int M, int aciertos[TAM])
{
     int i,j;
     for (j=0;j<M;j++)
     {
         aciertos[j]=0;
         for (i=0;i<N;i++)
         {
             if ((resultados[i] == match[N*j+i].Res && resultados[i] != "0") || (resultados[i] == "X" && match[N*j+i].Res == "x") || (resultados[i] == "x" && match[N*j+i].Res == "X"))
             {
                 label[N*j+i][0] = "[color=#00ff00]";
                 label[N*j+i][1] = "[/color]";
                 aciertos[j]++;
             }
             else if (resultados[i] != "0") //Si el partido no se ha jugado se pone un cero y no se colorea esa linea
             {
                 label[N*j+i][0] = "[color=#ff0000]";
                 label[N*j+i][1] = "[/color]";
             }
         }
     }
}


//Para guardar en el fichero los resultados
void GuardarFichero(partido match[TAM*partidos], int N, int M, string nomFichero, string label[TAM*partidos][2], string nombre[TAM], int aciertos[TAM])
{
    //Inicialización de variables
    ofstream fichero;
    int i, j;
    
    //Apertura del fichero
    fichero.open (nomFichero.c_str());
    
    //Volcado de la información en el fichero
    fichero << "<pre>";
    for (j=0;j<M;j++)
    {
        fichero << nombre[j] << endl;
        for (i=0;i<N;i++)
        {
            fichero << label[N*j+i][0] << match[N*j+i].Local << " " << match[N*j+i].Guion << " " << match[N*j+i].Visit << " " << match[N*j+i].Res << label[N*j+i][1] << endl;
            if ((i+1) % 5 == 0) //Separar los partidos en bloques de 5
            {
                fichero << endl;
            }
        }
        fichero << "--------------------------------------------------" << endl;
        fichero << endl;
    }
    // Ahora pongo los aciertos, ordenados
    for (i=0;i<M;i++)
    {
        for (j=i+1;j<M;j++)
        {
            if (aciertos[j] > aciertos[i]) //Intercambio
            {
                aciertos[M]=aciertos[i];
                aciertos[i]=aciertos[j];
                aciertos[j]=aciertos[M];
                nombre[M]=nombre[i];
                nombre[i]=nombre[j];
                nombre[j]=nombre[M];
            }
        }
    }
    //Escritura en el fichero
    for(i=0;i<M;i++)
    {
        fichero << nombre[i] << ": " << aciertos [i] << endl;
    }
    //Cierre de fichero
    fichero.close ();
}


//Para guardar en el fichero la tabla
void GuardarTabla(string nomFichero,int P,usuario user[TAM])
{
    //Inicialización de variables
    ofstream fichero;
    int i;
    string linea1, linea2;
    linea1 = "Pos   Usuario              QJ Ratio Pts";
    linea2 = "---------------------------------------";
    
    //Apertura del fichero
    fichero.open (nomFichero.c_str());
    
    //Encabezados
    fichero << linea1 << endl;
    fichero << linea2 << endl;
    
    //Volcado de la información en el fichero
    for (i=0;i<P;i++)
    {
        fichero << right << setfill(' ') << setw(3) << i + 1 << "   ";
        fichero << left << setfill(' ') << setw(20) << user[i].nombre << " ";
        fichero << right << setfill(' ') << setw(2) << user[i].part << " ";
        fichero.precision(4);
        fichero << setfill(' ') << setw(5) << user[i].rate << " ";
        fichero << setfill(' ') << setw(3) << user[i].total << endl;;
    }
    //Cierre de fichero
    fichero.close ();
}


//Función principal
int main ()
{
    //Declaración de variables
    int N = 0, M = 0, P = 0, i = 0, j = 0;
    int aciertos[TAM];
    partido match[TAM*partidos];
    usuario user[TAM];
    string nombre[TAM];
    ifstream fichero, ficheroRes, ficheroT;
    string nomFichero = "res.txt";
    string nomPost = "post.txt";
    string Ftabla = "table.txt";
    string label[TAM*partidos][2];
    string resultados[TAM];
    string basura;
    
    //Para rellenar el vector de resultados
    ficheroRes.open (nomFichero.c_str());
    
    //Leo los resultados
    for(i=0;i<partidos;i++)
    {
    	ficheroRes >> resultados[i];
	}
    ficheroRes.close();
    
    //Ahora el otro fichero
    nomFichero = "Quiniela.txt";
    
    //Apertura y lectura de fichero, o mensaje de bienvenida al programa
    fichero.open (nomFichero.c_str());
    if (!fichero)
    {
        cout << "No se ha encontrado el fichero" << endl << endl;
    }
    else
    {
        LeerFichero (match, fichero, nombre, N, M);
        fichero.close ();
        Colorear (match, label, resultados, N, M, aciertos);
        // Guardo los jugadores
        GuardarFichero(match,N,M,nomPost,label, nombre, aciertos);
        
        //Actualizo clasificación
        ficheroT.open (Ftabla.c_str());
        if (!ficheroT) //Tabla nueva
        {
            for(i=0;i<M;i++)
            {
                user[i].nombre = nombre[i];
                user[i].total = aciertos[i];
                user[i].part = 1;
                user[i].rate = double(aciertos[i]);
            }
            P = M; //P es el numero de participantes en la clasificacion. Si la tabla es nueva, coincidira con los que han participado esta jornada
        }
        else //Leer la tabla
        {
            getline(ficheroT,basura);
            getline(ficheroT,basura);
            ficheroT >> basura;
            i=0;
            do
            {
                ficheroT >> user[i].nombre;
                ficheroT >> user[i].part;
                ficheroT >> user[i].rate;
                ficheroT >> user[i].total;
                ficheroT >> basura;
                i++;
            }while(ficheroT.eof() == false);
            ficheroT.close();
            P = i; //Número de participantes hasta la fecha, hay que ver si hay nuevos o repiten
            for(j=0;j<M;j++) //Recorro los que han participado esta jornada
            {
                for(i=0;i<P;i++)//Para cada uno, miro si estan en la tabla
                {
                    if(user[i].nombre == nombre[j]) //Si estan, actualizo sus estadisticas y paso al siguiente participante (break)
                    {
                        user[i].total = user[i].total + aciertos[j];
                        user[i].part++;
                        user[i].rate = double(user[i].total)/double(user[i].part);
                        break;
                    }
                    else if(i == P-1)//Nuevo usuario que ha jugado
                    {
                        user[P].nombre = nombre[j];
                        user[P].total = aciertos[j];
                        user[P].part = 1;
                        user[P].rate = double(aciertos[j]);
                        P++;
                        break; //Necesito el break o el aumentar P me lleva a bucle infinito
                    }
                }
            }
            for (i=0;i<P;i++)
            {
                for (j=i+1;j<P;j++)
                {
                    if (user[j].total > user[i].total || (user[j].total == user[i].total && user[j].rate > user[i].rate)) //Intercambio
                    {
                        user[P]=user[i];
                        user[i]=user[j];
                        user[j]=user[P];
                    }
                }
            }
        }
        cout << P << endl;
        GuardarTabla(Ftabla,P,user);
        cout << "Hecho" << endl;
    }
    //system("pause");
    return 0;
}
