#include <string>
#include <iostream>
using namespace std;

class Inversion : public Persona{
    protected:
    string nombreFondoInversion;
    double saldoInvertido;
    double tasaInteresAnual;
    int plazo;

    public:
    double rendimiento;

    public:
    Inversion(string _nombre, string _usuario, string _nombreFondoInversion, double _saldoInvertido, double _tasaInteresAnual, int _plazo) : Persona(_nombre, _usuario){
        nombreFondoInversion = _nombreFondoInversion;
        saldoInvertido = _saldoInvertido;
        tasaInteresAnual = _tasaInteresAnual;
        plazo = _plazo;
        rendimiento = 0;
    }

    double calcular_rendimiento(){
        rendimiento = ((saldoInvertido*(tasaInteresAnual/100))/12)*plazo;
        return rendimiento;
    }

    Inversion operator+(const Inversion & otro) const{
        Inversion objeto_actual = *this;
        objeto_actual.rendimiento+=otro.rendimiento;
        return objeto_actual;
    }

    void mostrarInfo(){
        cout<<"Fondo de Inversion: "<<nombreFondoInversion<<endl;
        cout<<"Saldo invertido: "<<saldoInvertido<<endl;
        cout<<"Tasa de interes anual: "<<tasaInteresAnual<<"%"<<endl;
        cout<<"Plazo : "<<plazo<<endl;
        cout<<"\nRendimiento: $"<<rendimiento<<"\n\n";
    }

    double getRendimiento(){
        return rendimiento;
    }
};