/*
  ==============================================================================

    EqGui.h
    Created: 23 May 2020 4:14:32pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ModuleGui.h"

//==============================================================================
/*
*/
class EqGui    : public ModuleGui
{
public:
    EqGui();
    ~EqGui();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqGui)
};
