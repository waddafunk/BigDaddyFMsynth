/*
  ==============================================================================

    KnobLookAndFeel.h
    Created: 23 May 2020 4:14:57pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class KnobLookAndFeel : public LookAndFeel_V4
{
public:

    KnobLookAndFeel();

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;

    Label* createSliderTextBox(Slider& slider) override;

private:
    Image img1;
    Font daFont;
};
