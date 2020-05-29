/*
  ==============================================================================

    MySender.h
    Created: 27 May 2020 3:42:22pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Myanime.h"

//==============================================================================
/*
*/


enum class tSection { filter, matrix, oscillator, lfo, master };

class MySender : public OSCSender
{
public:
    MySender();
    MySender(tSection type);
    ~MySender();

    void mySend(String name, float value);
    String getSocketName();

    std::string tSectionToString(tSection section);
    tSection stringToTSection(String section);

private:
    tSection type = tSection::matrix;





    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MySender)
};

