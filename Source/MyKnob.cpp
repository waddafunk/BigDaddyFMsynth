/*
  ==============================================================================

    MyKnob.cpp
    Created: 31 May 2020 4:18:23pm
    Author:  daveg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MyKnob.h"

//==============================================================================

MyKnob::~MyKnob()
{
}


knobType MyKnob::getType() const
{
    return type;
}

void MyKnob::setType(knobType type)
{
    this->type = type;
}

int MyKnob::getRow() const
{
    return row;
}

void MyKnob::setRow(int row)
{
    this->row = row;
}

