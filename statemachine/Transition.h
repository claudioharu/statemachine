//---------------------------------------------------------------------------

#ifndef TransitionH
#define TransitionH
//---------------------------------------------------------------------------
#include "State.h"
#include <string>
using namespace std;

class State;
class Transition
{
private:
     State* next;
public:
    Transition(State* next);

    /**
     * The state to which this transition leads.
     * @return State.
     */
    State* state();
};
#endif
