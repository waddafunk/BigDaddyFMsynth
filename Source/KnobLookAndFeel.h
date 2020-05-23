/*
  ==============================================================================

    KnobLookAndFeel.h
    Created: 23 May 2020 4:14:57pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class KnobLookAndFeel    : public Component
{
public:
    KnobLookAndFeel();
    ~KnobLookAndFeel();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KnobLookAndFeel)
};
