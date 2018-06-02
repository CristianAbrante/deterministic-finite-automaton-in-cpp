
    // Prática 3: Computabilidad y algoritmia
    // Curso: Segundo
    // Alumno: Cristian Abrante Dorta
    
    // Implementación de la clase DFA
    
#include "DFA.hpp"
    
        
    DFA:: DFA (void):
    sigma(),
    setOfStates(),
    startState(),
    acceptedStates()
    {}
    
    DFA:: DFA (string fileName, bool& openingFault):
    sigma(),
    setOfStates(),
    startState(),
    acceptedStates()
    {
        createDFA(fileName, openingFault);
    }
    
    DFA:: ~DFA (void)
    {
        clear();
    }
    
    ostream& operator<< (ostream& os, const DFA& rhsDFA)
    {
        os << " ➝ Número de nodos: " <<  rhsDFA.setOfStates.size() << endl;
        os << " ➝ Estado de partida: q" << rhsDFA.startState << endl;
        os << endl;
        
        os << "     Est. siguiente" << endl;
        
        rhsDFA.writeLines(os,8);
        
        os << "|Estado| ";
        
        for (int i=0; i<rhsDFA.sigma.size(); i++)
        {
            os << rhsDFA.sigma.getSymbol(i) << "  | ";
        }
        os << endl;
        
        rhsDFA.writeLines(os,8);
        
        for (int i=0; i<rhsDFA.setOfStates.size(); i++)
        {
            os << "|  q" << rhsDFA.getState(i) << "  | ";
            
            for (int j=0; j<rhsDFA.sigma.size(); j++)
            {
                os << "q" << rhsDFA.getState(i).getNextStateID(rhsDFA.sigma.getSymbol(j)) << " | ";
            }
            
            os << endl;
        }
        
        rhsDFA.writeLines(os,8);
    }
    
    ostream& DFA:: writeAlphabet (ostream& os)
    {
        os << sigma;
        
        return os;
    }
    
    ostream& DFA:: determinateDeadStates(ostream& os)
    {
        
        bool hasDeadStates = false;
        
        for (int i=0; i<setOfStates.size(); i++)
        {
            if (isADeadState(getState(i)))
            {
                hasDeadStates = true;
            }
        }
        
        if (hasDeadStates)
        {
            os << "Los estados de muerte son los siguientes:" << endl;
            cout << endl;
            
            writeLines(os, 18);
            
            os << "|Estado de muerte| ";
        
            for (int i=0; i<sigma.size(); i++)
            {
                os << sigma.getSymbol(i) << "  | ";
            }
            os << endl;
            
            writeLines(os, 18);
            
            for (int i=0; i<setOfStates.size(); i++)
            {
                if (isADeadState(getState(i)))
                {
                    os << "|        q" << getState(i) << "      | ";
                    
                    for (int j=0; j<sigma.size(); j++)
                    {
                        os << "q" << getState(i).getNextStateID(sigma.getSymbol(j)) << " | ";
                    }
                    
                    os << endl;
                }
            }
            
            writeLines(os, 18);
        }
        else
        {
            os << "El DFA no tiene estados de muerte." << endl;
        }
        
        return os;
    }
    
    void DFA:: refresh (string fileName, bool& openingFault)
    {
        createDFA(fileName,openingFault);
    }
    
    bool DFA:: stringIsCorrect(string languageString)
    {
        return sigma.stringIsCorrect(languageString);
    }
    
    ostream& DFA:: evaluateString (ostream& os, string userLanguageString)
    {
        os << "Cadena de entrada: " << userLanguageString << endl;
        os << endl;
        os << " Estado de entrada   Entrada   Estado siguiente" << endl;
        int result = getNextStateID(startState.identifier, userLanguageString);
        os << endl;
        os << "La cadena de entrada es: ";
        
        if (isAnAcceptedState(getState(result)))
        {
            os << "ACEPTADA." << endl;
        }
        else os << " NO ACEPTADA." << endl;
        
        os << endl;
        
        return os;
    }
    
    
    // MÉTODOS PRIVADOS.
    
    void DFA:: clear (void)
    {
        sigma.clear();
        setOfStates.clear();
        startState.clear();
        acceptedStates.clear();
    }
    
    void DFA:: createDFA(string fileName, bool& openingFault)
    {
        clear();
        
        ifstream DFADefinition;
        DFADefinition.open(fileName.c_str());
        
        if (DFADefinition.is_open())
        {
            
            openingFault = false;
            int numberOfStates, startStateID;
            
            DFADefinition >> numberOfStates;
            DFADefinition >> startStateID;
            
            State tmpState;
            
            int stateID, numberOfTransitions, nextStateID;
            bool isAnAcceptedState;
            
            char symbol; 
            
            for (int i=0; i<numberOfStates; i++)
            {
                
                
                DFADefinition >> stateID;
                
                if (stateID == startStateID) startState.identifier = startStateID;
                else tmpState.identifier = stateID;
                
                DFADefinition >> isAnAcceptedState;
                DFADefinition >> numberOfTransitions;
                
                for (int j=0; j<numberOfTransitions; j++)
                {
                    DFADefinition >> symbol;
                    if (i==0) sigma.insert(symbol);
                    
                    DFADefinition >> nextStateID;
                    
                    if ((stateID == startStateID))
                    {
                        if (symbol != '&') startState.setNextState(nextStateID,symbol);
                        else  startState.setNextState(stateID,symbol);
                    }
                    else
                    {
                        if (symbol != '&') tmpState.setNextState(nextStateID,symbol);
                        else tmpState.setNextState(stateID,symbol); 
                    }
                }
                
                if (stateID == startStateID) setOfStates.insert(startState);
                else {setOfStates.insert(tmpState);}
                
                if(isAnAcceptedState&&(stateID == startStateID)) acceptedStates.insert(startState);
                if(isAnAcceptedState&&!(stateID == startStateID)) acceptedStates.insert(tmpState);
                
                tmpState.clear();
            }
        }
        else
        {
            openingFault = true;
        }
        
        if (!DFAIsCorrect()) { cerr << "Error creando el DFA, este no coentiene el número de transiciones para cada símbolo del alfabeto." << endl; openingFault = true;}
    }
    
    State DFA:: getState(int ID) const
    {
        State resultState;
        
        bool found = false;
        set<State>::iterator it = setOfStates.begin();
        
        while ((it!=setOfStates.end())&&!found)
        {
            if ((*it).identifier == ID) 
            {
                found = true; resultState = *it;
            }
            else it++;
        }
        
        return resultState;
    }
    
    bool DFA:: isADeadState(const State& possibleState) const
    {
        
        if(!isAnAcceptedState(possibleState))
        {
            int currentID = possibleState.identifier;
            bool deadState = true;
            int i=0;
                
            set<Transition>::iterator beg = possibleState.transitions.begin();
            
            while ((beg !=  possibleState.transitions.end())&&(i<sigma.size())&&deadState)
            {
                
                if (currentID != possibleState.getNextStateID(sigma.getSymbol(i))) deadState = false;
                else {beg++; i++; }
                
            }
            
            return deadState;
        }
        else return false;
    }
    
    ostream& DFA:: writeLines(ostream& os, int size) const
    {
        for (int i=0; i<size; i++) os << "-";
        
        for (int i=0; i<sigma.size(); i++)
        {
            os << "-----";
        }
        os << endl;
        
        return os;
    }
    
    int DFA:: getNextStateID(int currentID, string userLanguage)
    {
        if (userLanguage.size() == 1)
        {
            int next = startState.getNextStateID(userLanguage[0]);
            
            cout << " " << startState << "                  " << userLanguage[0] << "         " << next << endl;
            return next;
        }
        else
        {
            char lastElement = userLanguage.back();
            userLanguage.pop_back();
            
            int nextID = getNextStateID(currentID,userLanguage);
            int next = getState(nextID).getNextStateID(lastElement);
            
            cout << " " << nextID << "                  " << lastElement << "         " << next << endl;
            return next;
        }
    }
    
    bool DFA:: isAnAcceptedState (const State& userState) const
    {
        set<State>::iterator it = acceptedStates.find(userState);
        
        if (it == acceptedStates.end())
        {
            if ((*it) == userState) return true;
            else return false;
        }
        else return true;
    }
    
    bool DFA:: DFAIsCorrect (void)
    {
        bool correct = true;
        
        set<State>::iterator it = setOfStates.begin();
        
        while ((it!=setOfStates.end())&&correct)
        {
            if ((*it).transitions.size()!=sigma.size()) correct = false;
            else it++;
        }
        
        return correct;
    }