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
class MySender : public OSCSender
{
public:
    MySender();
    ~MySender();


private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MySender)
};
