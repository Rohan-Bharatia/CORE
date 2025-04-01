#pragma region LICENSE

// MIT License
//
// Copyright (c) 2025 Rohan Bharatia
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma endregion LICENSE

#ifndef _CORE_CONTROLLER_STATE_MACHINE_C_
    #define _CORE_CONTROLLER_STATE_MACHINE_C_

#include "StateMachine.h"

StateMachine* stateMachineInitialize(void)
{
    StateMachine* sm;

    sm->currentState    = 0;
    sm->stateCount      = 0;
    sm->transitionCount = 0;
    for(int i = 0; i < MAX_STATES; ++i)
        for(int j = 0; j < MAX_STATES; ++j)
            sm->transitionMap[i][j] = 0xFF;

    return sm;
}
void stateMachineAddState(StateMachine* sm, StateFunction state)
{
    if(sm->stateCount >= MAX_STATES)
        return;
    sm->states[sm->stateCount++] = state;
}

void stateMachineAddTransition(StateMachine* sm, uint8 fromState, uint8 toState, TransitionFunction condition)
{
    if(sm->transitionCount >= MAX_TRANSITIONS)
        return;
    sm->transitions[sm->transitionCount++] = condition;
    sm->transitionMap[fromState][toState]  = sm->transitionCount++;
}
void stateMachineUpdate(StateMachine* sm)
{
    // Execute current state
    if(sm->states[sm->currentState])
        sm->states[sm->currentState]();

    // Check transitions
    for(uint8 next = 0; next < sm->stateCount; ++next)
    {
        uint8 transitionIndex = sm->transitionMap[sm->currentState][next];
        if(transitionIndex != 0xFF && sm->transitions[transitionIndex]())
        {
            sm->currentState = next;
            break;
        }
    }
}

#endif // _CORE_CONTROLLER_STATE_MACHINE_C_
