//---------------------------------------------------------------------------


#pragma hdrstop

#include "Transition.h"

//---------------------------------------------------------------------------
/**
* Ctor.
* @param rule Rule that a character has to meet
*  in order to get to the next state.
* @param next Next state.
*/
Transition::Transition (State* next)
{
    this->next = next;
}

State* Transition::state()
{
    return this->next;
}

#pragma package(smart_init)
