#include <string>
#include <iostream>
#include <vector>
using namespace std;

class CuentaBancaria : public Persona{
    public:
    CuentaBancaria(string _nombre, string _usuario) : Persona(_nombre, _usuario){}

    virtual void agregar(double cantidad) = 0; // abstraccion
    
    virtual void retirar(double cantidad) = 0; // abstraccion
};