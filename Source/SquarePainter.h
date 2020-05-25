/*
  ==============================================================================

    SquarePainter.h
    Created: 25 May 2020 5:56:18pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include"WavePainter.h"

//==============================================================================
/*
*/
class SquarePainter    : public WavePainter
{
public:
    SquarePainter();
    SquarePainter(int x, int y);
    SquarePainter(int x, int y, int width, int height);
    SquarePainter(int x, int y, int width, int height, float dutyCycle);
    ~SquarePainter();

    void setDutyCycle(float dutyCycle);
    float getDutyCycle() { return this->dutyCycle; };

    void paint(Graphics&) override;
    void resized() override;

private:
    float dutyCycle = 0.5f;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SquarePainter)
};
