/*
  ==============================================================================

    SquarePainter.h
    Created: 25 May 2020 5:56:18pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SquarePainter    : public Component
{
public:
    SquarePainter();
    ~SquarePainter();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SquarePainter)
};
