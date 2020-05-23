/*
  ==============================================================================

    LfoGui.h
    Created: 23 May 2020 4:14:44pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LfoGui    : public Component
{
public:
    LfoGui();
    ~LfoGui();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LfoGui)
};
