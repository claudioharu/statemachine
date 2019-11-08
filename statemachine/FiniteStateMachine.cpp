//---------------------------------------------------------------------------


#pragma hdrstop

#include "FiniteStateMachine.h"

//---------------------------------------------------------------------------

/**
 * Ctor.
 * @param initial Initial state of this machine.
 */
FiniteStateMachine::FiniteStateMachine(State* initial)
{
    this->current = initial;
}

void FiniteStateMachine::switchState(char c, string& value)
{
    if(!this->current->hasValue && value.length() > 0)
    {
        if(this->previousType.compare("T") == 0)
        {
            value.pop_back();
            tags.push_back(value);
        }
        else if (this->previousType.compare("V") == 0)
        {
            value.pop_back();
            values.push_back(value);
        }
        value = "";
    }
    this->previousType = this->current->type;
    this->current = this->current->transit(c, value);
    
}

bool FiniteStateMachine::canStop()
{
    return this->current->isFinal();
}

void FiniteStateMachine::reset(State* initial)
{
    this->values.clear();
    this->tags.clear();
    this->current = initial;
}

#pragma package(smart_init)
