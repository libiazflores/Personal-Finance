#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Nomina : public CuentaBancaria{
    protected:
    double saldoNomina;
    vector < double > transaccionesNomina;

    public:
    Nomina(string _nombre, string _usuario, double _saldoNomina) : CuentaBancaria(_nombre, _usuario){
        saldoNomina = _saldoNomina;
    }

    void setAtributos(string _nombre, string _usuario, double _saldoNomina){
        saldoNomina = _saldoNomina;
    }

    void agregar(double cantidad) override{
        saldoNomina += cantidad;
        cout<<"\nSe te ha depositado $"<<cantidad<<" en tu cuenta"<<endl;
        cout<<"Saldo nomina: $"<<saldoNomina<<"\n\n";

        transaccionesNomina.push_back(+cantidad);
    }

    void retirar(double cantidad) override{
        saldoNomina -= cantidad;
        cout<<"\nHas retirado $"<<cantidad<<" en tu cuenta"<<endl;
        cout<<"Saldo nomina: $"<<saldoNomina<<"\n\n";

        transaccionesNomina.push_back(-cantidad);
    }

    vector<double> getTransaccionesNomina(){
        return transaccionesNomina;
    }

    double getSaldoNomina(){
        return saldoNomina;
    }
};