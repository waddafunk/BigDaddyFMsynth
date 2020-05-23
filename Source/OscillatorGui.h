/*
  ==============================================================================

    OscillatorGui.h
    Created: 23 May 2020 4:12:58pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ModuleGui.h"

//==============================================================================
/*
*/
class OscillatorGui    : public ModuleGui
{
public:
    OscillatorGui();
    ~OscillatorGui();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorGui)
};
