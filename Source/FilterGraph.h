/*
  ==============================================================================

    FilterGraph.h
    Created: 27 May 2020 11:14:05am
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ModuleGui.h"

//==============================================================================
/*
*/
class FilterGraph    : public ModuleGui
{
public:
    FilterGraph();
    ~FilterGraph();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterGraph)
};
