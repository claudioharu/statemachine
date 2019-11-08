//---------------------------------------------------------------------------

#ifndef StateH
#define StateH
//---------------------------------------------------------------------------

#include "Transition.h"
#include <map.h>
#include <string>
using namespace std;

class Transition;

class State
{

private:

    bool final;
    map<char, Transition*> transitions;

public:
    bool hasValue;
    string type;

    State();
    State(bool);
     /**
     * Add a Transition to this state.
     * @param tr Given transition.
     * @return Modified State.
     */
    State* with(char c, Transition* tr);

    /**
     * Follow one of the transitions, to get 
     * to the next state.
     * @param c Character.
     * @return State.
     */
    State* transit(char c, string& value);
    
    /**
     * Can the automaton stop on this state?
     * @return true or false
     */
    bool isFinal();
};
#endif
