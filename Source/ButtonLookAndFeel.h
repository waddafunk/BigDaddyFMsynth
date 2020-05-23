/*
  ==============================================================================

    ButtonLookAndFeel.h
    Created: 23 May 2020 4:15:22pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ButtonLookAndFeel    : public Component
{
public:
    ButtonLookAndFeel();
    ~ButtonLookAndFeel();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ButtonLookAndFeel)
};
