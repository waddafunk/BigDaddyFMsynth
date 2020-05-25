/*
  ==============================================================================

    SawPainter.h
    Created: 25 May 2020 5:56:41pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SawPainter    : public Component
{
public:
    SawPainter();
    ~SawPainter();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SawPainter)
};
