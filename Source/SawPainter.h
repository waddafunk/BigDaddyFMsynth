/*
  ==============================================================================

    SawPainter.h
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
class SawPainter : public WavePainter
{
public:
    SawPainter();
    SawPainter(int x, int y);
    SawPainter(int x, int y, int width, int height);
    ~SawPainter();


    void paint(Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SawPainter)
};
