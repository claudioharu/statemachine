//---------------------------------------------------------------------------
#pragma hdrstop
#include "State.h"
                                                                             
State::State()
{
    this->hasValue = false;
    State(false);
}
    
State::State(bool final)
{
    this->final = final;
}

State* State::transit(char c, string& value)
{
    //TODO - remove null and throw the appropriate exception
    if(transitions[c] != NULL)
    {
        if(this->hasValue)
        {
            value.push_back(c);
        }

        return transitions[c]->state();
    }
    return  NULL;
}

bool State::isFinal()
{
    return this->final;
}

State* State::with(char c, Transition* tr)
{
    this->transitions[c] = tr;
    return this;
}

#pragma package(smart_init)
