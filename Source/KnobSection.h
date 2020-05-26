/*
  ==============================================================================

    KnobSection.h
    Created: 26 May 2020 1:58:38pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class KnobSection    : public Component
{
public:
    KnobSection();
    ~KnobSection();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KnobSection)
};
