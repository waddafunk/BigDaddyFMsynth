/*
  ==============================================================================

    SinePainter.h
    Created: 25 May 2020 5:56:54pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WavePainter.h"
//==============================================================================
/*
*/
class SinePainter    : public WavePainter
{
public:
    SinePainter();
    SinePainter(int x, int y);
    ~SinePainter();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SinePainter)
};
