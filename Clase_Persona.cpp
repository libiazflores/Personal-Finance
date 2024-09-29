#include <string>
#include <iostream>
using namespace std;

class Persona {
    protected:
    string nombrePersona;
    string nombreUsuario;

    public:
    Persona(string persona, string usuario){
        nombrePersona = persona;
        nombreUsuario = usuario;
    }
};