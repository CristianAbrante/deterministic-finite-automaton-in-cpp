

    // Prática 3: Computabilidad y algoritmia
    // Curso: Segundo
    // Alumno: Cristian Abrante Dorta

    // Implementación de la clase State
    
#include "State.hpp"
    
    State:: State (void):
    transitions(),
    identifier(-1){}
    
    State:: State (int stateID):
    transitions(),
    identifier(stateID){}
    
    State:: State (const State& newState)
    {
        transitions = newState.transitions;
        identifier = newState.identifier;
    }
    
    State:: ~State(void)
    {
        clear();
    }
    
    void State:: clear (void)
    {
        transitions.clear();
        identifier = -1;
    }
    
    void State:: setNextState (int nextStateID, char symbol)
    {
        
        Transition newTransition(nextStateID, symbol);
        
        transitions.insert(newTransition);
        
    }
    
    int State:: getNextStateID (char symbol) const
    {
        if (symbol == '&') return identifier;
        
        bool found = false;
        int result;
        set<Transition>::iterator it = transitions.begin();
        
        while ((it!=transitions.end())&& !found)
        {
            if ((*it).symbol == symbol) { result = (*it).nextStateID; found =true;}
            else{ it++; }
        }
        
        return result;
    }
    
    ostream& operator<< (ostream& os, const State& rhsState)
    {
        os << rhsState.identifier;
        return os;
    }
    
    State& State:: operator= (const State& rhs)
    {
        this->transitions = rhs.transitions;
        this->identifier = rhs.identifier;
        
        return *this;
    }
        
    bool State:: operator== (const State& rhs) const
    {
        
        if ((this->identifier == rhs.identifier) && ((this->transitions).size() == rhs.transitions.size()))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
        
    bool State:: operator< (const State& rhs) const
    {
        if (this->identifier < rhs.identifier) return true;
        return false;
    }