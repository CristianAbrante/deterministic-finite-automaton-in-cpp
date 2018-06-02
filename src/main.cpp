
    // Prática 3: Computabilidad y algoritmia
    // Curso: Segundo
    // Alumno: Cristian Abrante Dorta

    // Implementación del main.

#include "./DFA/DFA.hpp"
#include "./State/State.hpp"
#include "./Transition/Transition.hpp"

#include <cstdio>
#include <cstdlib>

void menu (DFA& userDFA);

int main (int argc, char* argv[])
{
    
    bool fileFault = false;
    
    system ("clear");
    cout << "-------------------------------------------------------------------" << endl;
    cout << "\tPráctica 3 : Simulación de Autómatas finitos deterministas." << endl;
    cout << "-------------------------------------------------------------------" << endl;
    
    if (argc == 1)
    {
        
        char fileName[100];
        cout << "Introduzca un fichero que contenga los datos del DFA (.dfa) > ";
        cin >> fileName;
        
        DFA userDFA(fileName, fileFault);
        
        if (!fileFault)
        {
            cout << "Fichero cargado correctamente ✓" << endl;
            menu(userDFA);
        }
        else
        {
            cout << "Error de apertura del fichero: Nombre o formato incorrecto" << endl;
            cerr << "Fin del programa" << endl;
            cout << endl;
        }
    }
    
    if (argc == 2)
    {
        DFA userDFA(argv[1], fileFault);
        
        if (!fileFault)
        {
            cout << "Fichero cargado correctamente ✓" << endl;
            menu(userDFA);
        }
        else
        {
            cout << "Error de apertura del fichero: Nombre o formato incorrecto" << endl;
            cerr << "Fin del programa" << endl;
            cout << endl;
        }
    }
    
    if (argc >2)
    {
        cout << "Número incorrecto de argumentos" << endl;
        cerr << "Fin del programa" << endl;
        cout << endl;
    }
    
    
    cout << "\nHecho por: Cristian Abrante Dorta." << endl;
    cout << endl;
    
}

void menu (DFA& userDFA)
{
    char option;
    cout << endl;
    
    do
    {
        
        cout << "Introduzca la operación que desea hacer con lenguajes."            << endl;
        cout << endl;
        
        cout << "\t\t---- MENÚ ----"                << endl;
        cout << " a. Leer DFA desde un fichero."    << endl;
        cout << " b. Mostrar el DFA."               << endl;
        cout << " c. Identificar estados de muerte."<< endl;
        cout << " d. Analizar una cadena."          << endl;
        cout << " e. Finalizar programa."           << endl;
        
        cout << endl;
        cout << "Introduzca la letra de la opción a ejecutar > ";
        cin  >> option;
        
        switch (option)
        {
            case 'a': 
            {
                system ("clear");
                cout << " a. Leer DFA desde un fichero."    << endl;
                char fileName[100]; bool fileFault;
                
                cout << "Introduzca un fichero que contenga los datos del DFA (.dfa) > ";
                cin >> fileName;
                
                userDFA.refresh(fileName,fileFault);
                
                if (!fileFault)
                {
                    cout << "Fichero cargado correctamente ✓" << endl;
                }
                else
                {
                    cout << "Error de apertura del fichero: Nombre o formato incorrecto" << endl;
                    cerr << "Fin del programa" << endl;
                    option = 'e';
                    cout << endl;
                }
                
                break;
            }
            case 'b': 
            {
                system ("clear");
                cout << " b. Mostrar el DFA."               << endl;
                cout << "El DFA cargado desde el fichero es el siguiente: " << endl;
                cout << endl;
                
                cout << userDFA << endl;
                
                break;
            }
            case 'c': 
            {
                system ("clear");
                cout << " c. Identificar estados de muerte."<< endl;
                
                userDFA.determinateDeadStates(cout);
                
                cout << endl;
                break;
            }
            case 'd': 
            {
                system ("clear");
                string userLanguageString;
                
                cout << " d. Analizar una cadena."          << endl;
                
                cout << "Introduzca una cadena perteneciente al alfabeto Σ = ";
                userDFA.writeAlphabet(cout);
                cout << " > ";
                cin >> userLanguageString;
                
                if (userDFA.stringIsCorrect(userLanguageString))
                {
                    userDFA.evaluateString(cout, userLanguageString);
                }
                else
                {
                    do
                    {
                        
                        cout << "La cadena contiene símbolos que no pertenecen al alfabeto, introdúzcala de nuevo > ";
                        cin >> userLanguageString;
                        
                    }while(!userDFA.stringIsCorrect(userLanguageString));
                    
                    userDFA.evaluateString(cout, userLanguageString);
                }
                
                break;
            }
            case 'e': 
            {
                system ("clear");
                cerr << "Fin del Programa." << endl;
                
                break;
            }
            default:
            {
                do
                {
                    cout << "Opción incorrecta, introduzca de nuevo la opción que desea > ";
                    cin >> option;
                } while (!((option>='a')&&(option<='e')));
            }
        }
    } while(option != 'e');
}