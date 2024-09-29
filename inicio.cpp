#include <string>
#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

#include "Clase_Persona.cpp"
#include "Clase_Inversion.cpp"
#include "Clase_CuentaBancaria.cpp"
#include "Clase_Credito.cpp"
#include "Clase_Ahorro.cpp"
#include "Clase_Nomina.cpp"
#include "Clase_Fichero.cpp"

void checarError(){
    if (cin.fail()){
        cin.clear(); // limpia el buffer (espacio de almacenamiento)
        cin.ignore(); // ignora lo que se le haya asignado al cin
        throw invalid_argument("El tipo de caracter ingresado es invalido");
    }
}

void checarNegativo(int numero){
    if (numero < 0){
        cin.clear();
        cin.ignore();
        throw invalid_argument("No puede ser negativo.");
    }
}

void checarNegativo(double numero){
    if (numero < 0){
        cin.clear();
        cin.ignore();
        throw invalid_argument("No puede ser negativo.");
    }
}


int main(){
    cout<<"=== Bienvenid@ a tu aplicacion de gestion financiera personal (Simulacion) ===\n\n";
    cout<<"--- Registro de sesion ---"<<endl;

    cout<<"Introduce tu nombre: "<<endl;
    string nombrePersona;
    getline(cin, nombrePersona);
    checarError();

    cout<<"Crea tu Usuario (se aceptan \".\" y \"_\", no espacios): "<<endl; 
    string nombreUsuario;
    getline(cin,nombreUsuario);

    while (true){
        bool correcta=true;
        for (char c: nombreUsuario){
            if ((!(isalnum(c)||c=='.'||c=='_')) || (c==' ')){
                correcta=false;
                break;
            }
        }
        if (correcta==false){
            cout<<"Intente otra vez, Error el usuario solo puede incluir: (letras, numeros y caracteres como (\".\" y \"_\") y sin espacios"<<endl;
            cout<<"Crea tu Usuario"<<endl;
            cin>>nombreUsuario;
        }
        else{
            break;
        }
    }

    cout<<"Crea tu contraseña: (letras, numeros y caracteres como (*/#@&+-) son aceptados)"<<endl;
    string contrasena;
    cin>>contrasena;

    while (true){
        bool correcta=true;
        for (char c: contrasena){
            if (!(isalnum(c)||c=='*'||c=='/'||c=='#'||c=='@'||c=='&'||c=='+'||c=='-')){
                correcta=false;
                break;
            }
        }
        if (correcta==false){
            cout<<"Intente otra vez, Error la contraseña solo puede incluir: (letras, numeros y caracteres como (*/#@&+-)"<<endl;
            cout<<"Crea tu contraseña"<<endl;
            cin>>contrasena;
        }
        else{
            cout<<"Registro exitoso."<<endl;
            break;
        }
    }

    cout<<"\n--- Inicio de sesion ---"<<endl;
    string nombreUsuarioIng;
    string contrasenaIng;
    while (true){
        try{
            cout<<"Usuario: "<<endl;
            cin>>nombreUsuarioIng;

            cout<<"Contraseña: "<<endl;
            cin>>contrasenaIng;

            if (nombreUsuarioIng!=nombreUsuario||contrasenaIng!=contrasena){
                throw invalid_argument("Nombre de usuario o contraseña incorrecta, intenta otra vez");
            }
            else{
                break;
            }

        }
        catch(const invalid_argument & e){
            cout<<"Error: "<<e.what()<<endl;
        }
    }

    // inicializamos con nada (default)
    Credito credito("","",0,0,0,' ');
    Ahorro ahorro("","",0,0,0);
    Nomina nomina("","",0);


    vector <Inversion> listaInversiones;
    int numInversiones = 0;
    int suma = 0;
    
    // indicadores de inilizacion de datos en objetos
    bool creditoInicio = false;
    bool ahorroInicio = false;
    bool nominaInicio = false;
    bool inversionInicio = false;

    while (true){
        try{
            cout<<"\nSeccion que desea acceder: \n  1. Mi Cuenta Bancaria \n  2. Mis Inversiones (Renta fija) \n  3. Salir"<<endl;
            int opcionMenu;
            cin>>opcionMenu;
            checarError();
            checarNegativo(opcionMenu);
            if (opcionMenu == 1){  // TU CUENTA BANCARIA
                cout<<"\n  1. Acceder a cuentas (Credito, Ahorro, Nomina) \n  2. Ver mi saldo total \n  3. Imprimir estado de cuenta"<<endl;
                int opcionBanco;
                cin>>opcionBanco;
                checarError();
                checarNegativo(opcionBanco);
                if (opcionBanco == 1){
                    cout<<"\nSelecciona la cuenta que desea acceder: \n  1. Credito \n  2. Ahorro \n  3. Nomina"<<endl;
                    int opcionCuenta;
                    cin>>opcionCuenta;
                    checarError();
                    checarNegativo(opcionCuenta);
                    if (opcionCuenta == 1){ // CREDITO
                        while (true){
                            if (creditoInicio == false){
                                cout<<"\n\n--- CUENTA DE CREDITO ---\n\n";
                                cout<<"Inicializa tus datos: "<<endl;

                                double prestamo; int plazo; char tipoInteres; double tasaInteres;
                                cout<<"  Prestamo: $";
                                cin>>prestamo;
                                checarError();
                                checarNegativo(prestamo);
                                cout<<"  Plazo de tiempo (en meses): ";
                                cin>>plazo;
                                checarError();
                                checarNegativo(plazo);
                                cout<<"  Tipo de interes\n    S. Simple\n    C. Compuesto"<<endl;
                                cin>>tipoInteres;
                                tipoInteres = toupper(tipoInteres);
                                checarError();
                                cout<<"  Tasa de interes anual (%): ";
                                cin>>tasaInteres;
                                checarError();
                                checarNegativo(tasaInteres);
                                
                                credito.setAtributos(nombrePersona, nombreUsuario, prestamo, plazo, tasaInteres, tipoInteres);

                                if (credito.getTipoInteres() == 'S'){
                                    cout<<"\nDesglose de interes SIMPLE: "<<endl;
                                    credito.interes_simple();
                                }
                                else if (credito.getTipoInteres() == 'C'){
                                    cout<<"\nDesglose de interes COMPUESTO: "<<endl;
                                    credito.interes_compuesto();
                                }

                                creditoInicio = true; // se indica que la inicializacion fue completada
                            }

                            cout<<"\n¿Desea hacer movimientos en su cuenta de credito? \n  1. SI \n  2. NO (regresar el menu principal)"<<endl;
                            int opcion2;
                            cin>>opcion2;
                            checarError();
                            checarNegativo(opcion2);
                            if (opcion2 == 1){
                                cout<<"1. Pagar \n2. Retirar"<<endl;
                                int opcion3;
                                cin>>opcion3;
                                checarError();
                                checarNegativo(opcion3);
                                if (opcion3 == 1){
                                    cout<<"Monto: $";
                                    double cantidadPagarC;
                                    cin>>cantidadPagarC;
                                    checarError();
                                    checarNegativo(cantidadPagarC);
                                    credito.agregar(cantidadPagarC);
                                }
                                else if (opcion3 == 2){
                                    cout<<"\n¿Estas seguro que quieres retirar? \n  1. SI \n  2. NO (regresar al menu) \n*Se te penalizara con el 5% de tu monto retirado"<<endl;
                                    int opcion4;
                                    cin>>opcion4;
                                    checarError();
                                    checarNegativo(opcion4);
                                    if (opcion4 == 1){
                                        cout<<"Monto: $";
                                        double cantidadRetirarC;
                                        cin>>cantidadRetirarC;
                                        checarError();
                                        checarNegativo(cantidadRetirarC);
                                        if (cantidadRetirarC <= credito.getSaldoPago()){
                                            credito.retirar(cantidadRetirarC);
                                        }
                                        else if (cantidadRetirarC > credito.getSaldoPago()){
                                            cout<<"Error. No puedes retirar mas cantidad que tu saldo de credito."<<endl;
                                        }
                                    }
                                    else if (opcion4 == 2){
                                        break;
                                    }
                                }
                            }
                            else if (opcion2 == 2){
                                break;
                            }
                        }
                    }
                    else if (opcionCuenta == 2){
                        while (true){
                            if (ahorroInicio == false){
                                cout<<"\n\n--- CUENTA DE AHORRO ---\n\n";
                                cout<<"Inicializa tus datos: "<<endl;

                                double tasaInteres2; int plazo2; double saldoAhorro;
                                cout<<"  Tasa de interes anual (%): ";
                                cin>>tasaInteres2;
                                checarError();
                                checarNegativo(tasaInteres2);
                                cout<<"  Plazo de tiempo (en meses): ";
                                cin>>plazo2;
                                checarError();
                                checarNegativo(plazo2);
                                cout<<"  Saldo: $";
                                cin>>saldoAhorro;
                                checarError();
                                checarNegativo(saldoAhorro);
                                
                                ahorro.setAtributos(nombrePersona, nombreUsuario, tasaInteres2, plazo2, saldoAhorro);

                                cout<<"\nDesglose de interes: "<<endl;
                                ahorro.interes_ganado();

                                ahorroInicio = true; // se indica que la inicializacion fue completada
                            }

                            cout<<"\n¿Desea hacer movimientos en su cuenta de ahorro? \n  1. SI \n  2. NO (regresar al menu principal)"<<endl;
                            int opcion5;
                            cin>>opcion5;
                            checarError();
                            checarNegativo(opcion5);
                            if (opcion5 == 1){
                                cout<<"1. Agregar \n2. Retirar"<<endl;
                                int opcion6;
                                cin>>opcion6;
                                checarError();
                                checarNegativo(opcion6);
                                if (opcion6 == 1){
                                    cout<<"Monto: $";
                                    double cantidadAgregarA;
                                    cin>>cantidadAgregarA;
                                    checarError();
                                    checarNegativo(cantidadAgregarA);
                                    ahorro.agregar(cantidadAgregarA);
                                }
                                else if (opcion6 == 2){
                                    cout<<"\n¿Estas seguro que quieres retirar? Es tu cuenta de ahorro \n  1. SI \n  2. NO (regresar al menu principal)"<<endl;
                                    int opcion4;
                                    cin>>opcion4;
                                    checarError();
                                    checarNegativo(opcion4);
                                    if (opcion4 == 1){
                                        cout<<"Monto: $";
                                        double cantidadRetirarA;
                                        cin>>cantidadRetirarA;
                                        checarError();
                                        checarNegativo(cantidadRetirarA);
                                        if (cantidadRetirarA <= ahorro.getSaldoAhorro()){
                                            ahorro.retirar(cantidadRetirarA);
                                        }
                                        else if (cantidadRetirarA > ahorro.getSaldoAhorro()){
                                            cout<<"Error. No puedes retirar mas cantidad que tu saldo de ahorro."<<endl;
                                        }
                                    }
                                    else if (opcion4 == 2){
                                        break;
                                    }
                                }
                            }
                            else if (opcion5 == 2){
                                break;
                            }
                        }
                    }
                    else if (opcionCuenta == 3){
                        while (true){
                            if (nominaInicio == false){
                                cout<<"\n\n--- CUENTA DE NOMINA ---\n\n";
                                cout<<"Inicializa tus datos: "<<endl;

                                double saldoNomina;
                                cout<<"  Saldo de nomina: $";
                                cin>>saldoNomina;
                                checarError();
                                checarNegativo(saldoNomina);
                                
                                nomina.setAtributos(nombrePersona, nombreUsuario, saldoNomina);

                                nominaInicio = true;
                            }

                            cout<<"\n¿Desea hacer movimientos en su cuenta de nomina? \n  1. SI \n  2. NO (regresar al menu principal)"<<endl;
                            int opcion6;
                            cin>>opcion6;
                            checarError();
                            checarNegativo(opcion6);
                            if (opcion6 == 1){
                                cout<<"1. Agregar \n2. Retirar"<<endl;
                                int opcion7;
                                cin>>opcion7;
                                checarError();
                                checarNegativo(opcion7);
                                if (opcion7 == 1){
                                    cout<<"Salario: $";
                                    double cantidadAgregarN;
                                    cin>>cantidadAgregarN;
                                    checarError();
                                    checarNegativo(cantidadAgregarN);
                                    nomina.agregar(cantidadAgregarN);
                                }
                                else if (opcion7 == 2){
                                        cout<<"Monto: $";
                                        double cantidadRetirarN;
                                        cin>>cantidadRetirarN;
                                        checarError();
                                        checarNegativo(cantidadRetirarN);
                                        if (cantidadRetirarN <= nomina.getSaldoNomina()){
                                            nomina.retirar(cantidadRetirarN);
                                        }
                                        else if (cantidadRetirarN > nomina.getSaldoNomina()){
                                            cout<<"Error. No puedes retirar mas cantidad que tu saldo de nomina."<<endl;
                                        }
                                }
                            }
                            else if (opcion6 == 2){
                                break;
                            }
                        }
                    }
                }
                else if (opcionBanco == 2){
                    cout<<"\nSaldo total bancario (Ahorro + Nomina): $"<<ahorro.getSaldoAhorro()+nomina.getSaldoNomina()<<endl;
                }
                else if (opcionBanco == 3){
                    Fichero estadoCuenta;
                    string nombreFichero = "EstadoDeCuenta.txt";
                    estadoCuenta.escribirFichero(nombreFichero, nombrePersona, nombreUsuario, credito.getTransaccionesCredito(), ahorro.getTransaccionesAhorro(), nomina.getTransaccionesNomina());
                }
            }
            else if(opcionMenu == 2){
                while (true){
                    if (inversionInicio == false){
                        cout<<"\n\n--- INVERSIONES (RENTA FIJA) ---\n\n";

                        cout<<"Numero de inversiones que cuenta: ";
                        cin>>numInversiones;
                        checarError();
                        checarNegativo(numInversiones);

                        for (int i=0; i<numInversiones; i++){
                            cout<<"\nInicializa los datos de la inversion "<<i+1<<":"<<endl;

                            string nombreFondoInversion; double saldoInvertido; double tasaInteresAnual; int plazo;
                            cout<<"  Nombre de tu fondo de inversion: ";
                            cin>>nombreFondoInversion;
                            checarError();
                            cout<<"  Saldo a invertir: $";
                            cin>>saldoInvertido;
                            checarError();
                            checarNegativo(saldoInvertido);
                            cout<<"  Tasa de interes anual (%): ";
                            cin>>tasaInteresAnual;
                            checarError();
                            checarNegativo(tasaInteresAnual);
                            cout<<"  Plazo de tiempo (en meses): ";
                            cin>>plazo;
                            checarError();
                            checarNegativo(plazo);
                            
                            Inversion inversion(nombrePersona, nombreUsuario, nombreFondoInversion, saldoInvertido, tasaInteresAnual, plazo);

                            listaInversiones.push_back(inversion);

                            listaInversiones[i].calcular_rendimiento();
                        }

                        if (numInversiones == 1){
                            cout<<"Suma TOTAL de rendimientos: $"<<listaInversiones[0].getRendimiento()<<endl;
                        }
                        else{
                            Inversion sumaInversiones = listaInversiones[0];
                            for (int i=1; i<listaInversiones.size(); i++){
                                sumaInversiones = sumaInversiones + listaInversiones[i];
                            }

                            suma = sumaInversiones.getRendimiento();
                        }

                        inversionInicio = true;
                    }

                    cout<<"\n\nSelecciona una opcion: \n  1. Mostrar mis inversiones \n  2. Mostrar rendimiento total \n  3. Regresar al menu principal"<<endl;
                    int opcion8;
                    cin>>opcion8;
                    checarError();
                    checarNegativo(opcion8);
                    if (opcion8 == 1){
                        for (int i=0; i<numInversiones; i++){
                            cout<<"\nInversion "<<i+1<<":"<<endl;
                            listaInversiones[i].mostrarInfo();
                        }
                        break;
                    }
                    else if (opcion8 == 2){
                        cout<<"\nSuma TOTAL de rendimientos: $"<<suma<<endl;
                        break;
                    }
                    else if (opcion8 == 3){
                        break;
                    }
                }
            }
            else if (opcionMenu == 3){
                cout<<"\nHasta luego :)"<<endl;
                return 0;
            }
        }
        catch(const invalid_argument & e){
            cout<<"Error: "<<e.what()<<endl;
        }
    }
    
    return 0;
}