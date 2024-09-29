#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Ahorro : public CuentaBancaria{
    protected:
    double tasaInteresAnual;
    int plazo;
    double saldoAhorro;
    vector < double > transaccionesAhorro;

    public:
    Ahorro(string _nombre, string _usuario, double _tasaInteresAnual, int _plazo, double _saldoAhorro): CuentaBancaria(_nombre, _usuario){
        tasaInteresAnual = _tasaInteresAnual;
        plazo = _plazo;
        saldoAhorro = _saldoAhorro;
    }

    void setAtributos(string _nombre, string _usuario, double _tasaInteresAnual, int _plazo, double _saldoAhorro){
        tasaInteresAnual = _tasaInteresAnual;
        plazo = _plazo;
        saldoAhorro = _saldoAhorro;
    }

    void interes_ganado(){
        cout<<"\nSaldo Ahorro: "<<saldoAhorro<<endl;
        cout<<"Tasa de interes anual: "<<tasaInteresAnual<<"%"<<endl;
        cout<<"Plazo : "<<plazo<<endl;

        double ganancia = ((saldoAhorro*(tasaInteresAnual/100))/12)*plazo;
        saldoAhorro += ganancia;
        cout<<"\nInteres TOTAL ganado: $"<<ganancia<<endl;
        cout<<"Saldo ahorro: $"<<saldoAhorro<<"\n\n";
    }

    void agregar(double cantidad) override{
        saldoAhorro += cantidad;
        cout<<"\nAgregaste $"<<cantidad<<" a tu saldo de ahorro."<<endl;
        cout<<"Saldo ahorro: $"<<saldoAhorro<<"\n\n";

        transaccionesAhorro.push_back(+cantidad);
    }

    void retirar(double cantidad) override{
        saldoAhorro -= cantidad;
        cout<<"\nRetiraste $"<<cantidad<<" de tu saldo de ahorro."<<endl;
        cout<<"Saldo ahorro: $"<<saldoAhorro<<"\n\n";

        transaccionesAhorro.push_back(-cantidad);
    }

    vector<double> getTransaccionesAhorro(){
        return transaccionesAhorro;
    }

    double getSaldoAhorro(){
        return saldoAhorro;
    }
};
