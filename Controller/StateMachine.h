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

#pragma once

#ifndef _CORE_CONTROLLER_STATE_MACHINE_H_
    #define _CORE_CONTROLLER_STATE_MACHINE_H_

#include "../Base/Types.h"

#define MAX_STATES 32
#define MAX_TRANSITIONS 64

typedef void(*StateFunction)(void);
typedef bool(*TransitionFunction)(void);

typedef struct
{
    uint8 currentState;
    uint8 stateCount;
    uint8 transitionCount;
    StateFunction states[MAX_STATES];
    TransitionFunction transitions[MAX_TRANSITIONS];
    uint8 transitionMap[MAX_STATES][MAX_STATES];
} StateMachine;

StateMachine* stateMachineInitialize(void);
void stateMachineAddState(StateMachine* sm, StateFunction state);
void stateMachineAddTransition(StateMachine* sm, uint8 fromState, uint8 toState, TransitionFunction condition);
void stateMachineUpdate(StateMachine* sm);

#endif // _CORE_CONTROLLER_STATE_MACHINE_H_
