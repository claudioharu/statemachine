//---------------------------------------------------------------------------

#ifndef FiniteStateMachineH
#define FiniteStateMachineH
//---------------------------------------------------------------------------
#include "State.h"
#include <vector>

class FiniteStateMachine
{
private:
    State* current;
public:
    string previousType;
    vector<string> values;
    vector<string> tags;

    FiniteStateMachine(State* initial);

	/**
	 * Follow a transition, switch the state of the machine.
	 *
	 * @param c Char.
	 * @return A new finite state machine with the new state.
	 */
	void switchState(char c, string& value);

	/**
	 * Is the current state a final one?
	 *
	 * @return true or false.
	 */
	bool canStop();

    void reset(State* initial);
};
#endif
 