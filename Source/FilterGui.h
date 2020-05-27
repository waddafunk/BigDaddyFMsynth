/*
  ==============================================================================

    FilterGui.h
    Created: 23 May 2020 4:13:23pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ModuleGui.h"
#include "KnobSection.h"
#include "FilterGraph.h"

//==============================================================================
/*
*/
class FilterGui    : public ModuleGui
{
public:
    FilterGui();
    FilterGui(int x, int y);
    FilterGui(int x, int y, int w, int h);
    ~FilterGui();

    void paint (Graphics&) override;
    void resized() override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterGui)
};
