#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

class Fichero{
    public:
    void escribirFichero(string nombreArchivo, string nombrePersona, string nombreUsuario, const vector<double> & transaccionesCredito, const vector<double> & transaccionesAhorro, const vector<double> & transaccionesNomina){
        ofstream fichero(nombreArchivo);

        if (!fichero.is_open()){
            cerr<<"Error al abrir el archivo del estado de cuenta."<<endl;
            return;
        }

        time_t ahora = time(0);
        char* tiempo = ctime(&ahora);

        fichero<<"---* ESTADO DE CUENTA *---"<<endl;
        fichero<<"De: "<<nombrePersona<<" (@"<<nombreUsuario<<")"<<endl;
        fichero<<tiempo<<endl;

        fichero<<"\n-- Transacciones de cuenta credito --"<<endl;
        for (double i : transaccionesCredito){
            fichero<<" $"<<i<<endl;
        }

        fichero<<"\n-- Transacciones de cuenta ahorro --"<<endl;
        for (double i : transaccionesAhorro){
            fichero<<" $"<<i<<endl;
        }

        fichero<<"\n-- Transacciones de cuenta nomina --"<<endl;
        for (double i : transaccionesNomina){
            fichero<<" $"<<i<<endl;
        }

        fichero.close();
    }
};