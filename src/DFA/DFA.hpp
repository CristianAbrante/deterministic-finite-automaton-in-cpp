    
    // Prática 3: Computabilidad y algoritmia
    // Curso: Segundo
    // Alumno: Cristian Abrante Dorta
    
    // Definición de la clase DFA
    
#pragma once

#include "../State/State.hpp"
#include "../Transition/Transition.hpp"
#include "../Alphabet/Alphabet.hpp"

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <set>

using namespace std;

class DFA
{
    private:
        
        // Atributo que representa al conjunto de estados 
        set<State>      setOfStates;
        
        // Atributo que representa el estado de partida.
        State           startState;
        
        // Atributo que representa el conjunto de estados aceptados.
        set<State>     acceptedStates;
        
        // Atributo que representa al alfabeto de entrada del DFA.
        Alphabet        sigma;
        
    public:
        
        // Constructor por defecto del autómata.
        DFA(void);
        
        // Constructor al que se le pasa un string con el nombre del fichero.
        DFA(string fileName, bool& openingFault);
        
        // Destructor de la clase.
        ~DFA (void);
        
        // Sobrecarga del operador que permite mostrar el autómata por pantalla con el formato definido.
        friend ostream& operator<< (ostream& os, const DFA& rhsDFA);
        
        // Método que escribe por pantalla el alfabeto que sigue el DFA.
        ostream& writeAlphabet (ostream& os);
        
        // Función que muestra por pantalla la lista de los estados de muerte.
        ostream& determinateDeadStates(ostream& os);
        
        // Método que carga un DFA desde un fichero.
        void refresh (string fileName, bool& openingFault);
        
        // Metodo que devuelve si una cadena es correcta segun el afabeto.
        bool stringIsCorrect(string languageString);
        
        // Método que evalua si una cadena se encuentra en el lenguaje.
        ostream& evaluateString (ostream& os, string userLanguageString);
        
    private:
        
        // Método que limpia el DFA.
        void clear (void);
        
        // Método que crea un DFA desde un fichero.
        void createDFA (string fileName, bool& openingFault);
        
        // Método que devuelve el estado dado un identificador.
        State getState (int ID) const;
        
        // Método que devuelve si un estado es o no de muerte.
        bool isADeadState (const State& possibleState) const;
        
        ostream& writeLines(ostream& os, int size) const;
        
        int getNextStateID(int currentID, string userLanguage);
        
        // Método que devuelve si un estado está o no aceptado.
        bool isAnAcceptedState (const State& userState) const;
        
        // Método que devuelve si existe un error en la creación del DFA.
        bool DFAIsCorrect (void);

};