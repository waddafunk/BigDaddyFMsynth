/*
  ==============================================================================

    TrianglePainter.h
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
class TrianglePainter : public WavePainter
{
public:
    TrianglePainter();
    TrianglePainter(int x, int y);
    TrianglePainter(int x, int y, int width, int height);
    ~TrianglePainter();


    void paint(Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrianglePainter)
};