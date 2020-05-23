/*
  ==============================================================================

    FaderLookAndFeel.h
    Created: 23 May 2020 4:15:12pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FaderLookAndFeel    : public Component
{
public:
    FaderLookAndFeel();
    ~FaderLookAndFeel();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaderLookAndFeel)
};
