#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
using namespace std;
//Constants
#define N_leagues 2
#define N_fixtures 18
#define N_matches 5
#define N_quiniela 10

void LeerPartidos(string, int, string[N_leagues][N_fixtures][N_matches]);
void MakeFix(string, string);
string delSpaces(string &str) 
{
   while(str.find(" ") != string::npos)
   {
   		str.replace(str.find(" "), 1, "_");
   }
   return str;
}
void MakeFix(string inname, string outname)
{
	ofstream output;
	ifstream input;
	string basura;
	output.open(outname.c_str());
	input.open(inname.c_str());
	//Formato es: linea de jornada
	//siguiente linea(cambiar espacios) - caca - siguiente linea(cambiar espacios) cacax3 y repetir para partidos
	for(int i=0;i<N_fixtures;i++)
	{
		getline(input, basura); //Jornada
		output << basura << endl;
		output << "--------------------------------------" << endl;
		for(int j=0;j<N_matches;j++)
		{
			getline(input, basura); //Local
			output << delSpaces(basura) << " - ";
			getline(input, basura); //En blanco
			getline(input, basura); //Visitante
			output << delSpaces(basura) << endl;
			getline(input, basura);
			getline(input, basura);
			getline(input, basura); //Basura
		}
		output << endl;
	}
	input.close();
}


void LeerPartidos(string filename, int leagueindex, string matches[N_leagues][N_fixtures][N_matches])
{
	string basura;
	ifstream input;
	
	input.open(filename.c_str());
	for(int i=0;i<N_fixtures;i++)
	{
		getline(input, basura);
		getline(input, basura);
		for(int j=0;j<N_matches;j++)
		{
			getline(input, matches[leagueindex][i][j]);
		}
		getline(input, basura);
	}
	input.close();
}

int main()
{
	srand (time(NULL));
	string matches[N_leagues][N_fixtures][N_matches]; //Nº de ligas, nº de jornadas, nº de partidos
	string quiniela[N_fixtures][N_quiniela]; //Nº de jornadas, nº de partidos/quiniela
	int Npartido;
	
	MakeFix("Athenafix_gesliga.txt", "Athenafix.txt");
	MakeFix("Hadesfix_gesliga.txt", "Hadesfix.txt");
	LeerPartidos("Hadesfix.txt", 0, matches);
	LeerPartidos("Athenafix.txt", 1, matches);
	for(int i=0;i<N_fixtures;i++)
	{
		Npartido = 0;
		//Selecciono al azar qué liga tendrá 7 partidos en vez de 8 en la quiniela
		int league7 = rand() % N_leagues;
		for(int j=0;j<N_leagues;j++)
		{
			int Npartidosliga;
			if(j==league7)
			{
				Npartidosliga = 5;
			}
			else
			{
				Npartidosliga = 5;
			}
			for(int k=0;k<Npartidosliga;k++)
			{
				int nrandom = rand() % (N_matches-k);
				quiniela[i][Npartido] = matches[j][i][nrandom];
				matches[j][i][nrandom] = matches[j][i][N_matches-1-k];
				Npartido++;
			}
		}
	}
	
	//Output
	for(int i=0;i<N_fixtures;i++)
	{
		ofstream output;
		string filename;
		ostringstream ss;
		ss << i+1;
		filename = "Jornada " + ss.str() + ".txt";
		ss.str("");
		
		output.open(filename.c_str());
		output << "Leeros las normas de como participar http://www.ligamanagervirtual.com/t19433-reglas-quiniela-lmv#218161 y sobre todo los nuevos, fijaos en como hacemos la quiniela los demás (creo que ver un ejemplo es mas facil que leerse las normas Very Happy)" << endl << endl;
		output << "QuinielaLMV.txt" << endl;
		output << "[Introduce_Nombre]" << endl;
		for(int j=0;j<N_quiniela;j++)
		{
			if(j % 5 == 0)
			{
				output << endl;
			}
			output << quiniela[i][j] << endl;
		}
		output.close();
	}
	return 0;
}
