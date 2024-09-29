#include <string>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Plan de pago de credito
class Credito : public CuentaBancaria{
    protected:
    double prestamo;
    int plazo;
    double tasaInteresAnual;
    char tipoInteres;
    double saldoPago;
    vector < double > transaccionesCredito;

    public:
    Credito(string _nombre, string _usuario, double _prestamo, int _plazo, double tasa, char _tipoInteres) : CuentaBancaria(_nombre, _usuario){
        prestamo = _prestamo; // nomas valor de prestamo
        plazo = _plazo;
        tasaInteresAnual = tasa/100;
        tipoInteres = _tipoInteres;
        saldoPago = _prestamo; // tu saldo movible
    }

    void setAtributos(string _nombre, string _usuario, double _prestamo, int _plazo, double tasa, char _tipoInteres){
        prestamo = _prestamo; // nomas valor de prestamo
        plazo = _plazo;
        tasaInteresAnual = tasa/100;
        tipoInteres = _tipoInteres;
        saldoPago = _prestamo; // tu saldo movible
    }

    void interes_simple(){
        cout<<"--- INTERES SIMPLE ---\n\n";
        cout<<"Prestamo: $"<<fixed<<prestamo<<endl;
        cout<<"Tasa de interes anual: "<<tasaInteresAnual*100<<"%"<<endl;
        cout<<"Plazo: "<<plazo<<" meses\n\n";

        double tasaInteresMensual = tasaInteresAnual/plazo;

        // MENSUALIDAD
        double mensualidad = prestamo*(1+tasaInteresAnual)/plazo;
        cout<<"Mensualidad con interes: $"<<mensualidad<<endl;

        // INTERES
        double interes = prestamo*tasaInteresMensual;
        cout<<"Interes por mes: $"<<interes<<endl;

        // AMORTIZACION
        double amortizacion = mensualidad-interes;
        cout<<"Amortizacion mensual (Mensualidad sin interes): $"<<amortizacion<<endl;

        // SALDO FINAL
        vector <double> saldo_final{prestamo};
        
        cout<<"Deuda total restante por mes:"<<endl;
        for (int i=0; i<plazo+1; i++){
            double saldo_calculado = saldo_final[i]-amortizacion;
            saldo_final.push_back(saldo_calculado);
            cout<<"   Mes "<<i<<": $"<<saldo_final[i]<<endl;
        }

        // INTERES TOTAL // DEUDA FINAL
        double interes_total = interes*plazo;
        double deuda_final = mensualidad*plazo;

        cout<<"Interes total: $"<<fixed<<interes_total<<endl;
        cout<<"DEUDA FINAL: $"<<fixed<<deuda_final<<"\n\n";

        saldoPago = deuda_final;
    }

    void interes_compuesto(){
        cout<<"--- INTERES COMPUESTO ---\n\n";
        cout<<"Prestamo: $"<<fixed<<prestamo<<endl;
        cout<<"Tasa de interes anual: "<<tasaInteresAnual*100<<"%"<<endl;
        cout<<"Plazo: "<<plazo<<" meses\n\n";

        double tasaInteresMensual = tasaInteresAnual/plazo;

        // MENSUALIDAD
        double mensualidad = prestamo*((pow(1+tasaInteresMensual,plazo))*tasaInteresMensual)/(pow(1+tasaInteresMensual,plazo)-1);
        cout<<"Mensualidad con interes: $"<<mensualidad<<endl;

        // INTERES // AMORTIZACION // SALDO FINAL
        vector <double> lista_interes;
        vector <double> lista_amortizacion;
        vector <double> lista_saldo_final{prestamo};


        for (int i=0; i<plazo; i++){
            double interes = lista_saldo_final[i] * tasaInteresMensual; 
            lista_interes.push_back(interes);
            
            double amortizacion = mensualidad - lista_interes[i];
            lista_amortizacion.push_back(amortizacion);

            double saldo_final = lista_saldo_final[i] - lista_amortizacion[i];
            lista_saldo_final.push_back(saldo_final);
        }

        // INTERES MENSUAL // INTERES TOTAL
        double suma_interes = 0;
        cout<<"\nInteres por mes:"<<endl;
        for (int i=0; i<plazo; i++){
            cout<<"Mes "<<i+1<<": $"<<lista_interes[i]<<endl;
            
            suma_interes += lista_interes[i];
        }

        cout<<"\nAmortizacion mensual (Mensualidad sin interes):"<<endl;
        for (int i=0; i<plazo; i++){
            cout<<"Mes "<<i+1<<": $"<<lista_amortizacion[i]<<endl;
        }

        cout<<"\nDeuda total restante por mes:"<<endl;
        for (int i=0; i<plazo+1; i++){
            cout<<"Mes "<<i<<": $"<<lista_saldo_final[i]<<endl;
        }

        // INTERES TOTAL // DEUDA FINAL
        double interes_total = suma_interes;
        double deuda_final = mensualidad*plazo;

        cout<<"\nInteres total: $"<<fixed<<interes_total<<endl;
        cout<<"DEUDA FINAL: $"<<fixed<<deuda_final<<"\n\n";

        saldoPago = deuda_final;
    }

    void agregar(double cantidad) override{
        saldoPago -= cantidad;
        cout<<"\nPagaste $"<<cantidad<<" de tu prestamo."<<endl;
        cout<<"Tu credito restante a pagar es de $"<<fixed<<saldoPago<<"\n\n";

        transaccionesCredito.push_back(+cantidad);
    }

    void retirar(double cantidad) override{
        saldoPago += cantidad + (cantidad*0.05);
        cout<<"\nRetiraste $"<<cantidad<<" de tu saldo de credito."<<endl;
        cout<<"* Se te penalizo con el 5% de tu monto retirado ($"<<cantidad*0.05<<")"<<endl;
        cout<<"Tu credito restante a pagar es de $"<<fixed<<saldoPago<<"\n\n";

        transaccionesCredito.push_back(-cantidad);
    }

    vector<double> getTransaccionesCredito(){
        return transaccionesCredito;
    }

    char getTipoInteres(){
        return tipoInteres;
    }

    float getSaldoPago(){
        return saldoPago;
    }
};
