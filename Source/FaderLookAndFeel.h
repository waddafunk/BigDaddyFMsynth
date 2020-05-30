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
class FaderLookAndFeel    : public LookAndFeel_V2
{
public:
    FaderLookAndFeel();


    void drawRoundThumb(Graphics& g, float x, float y, float diameter, Colour colour, float outlineThickness);

    void drawLinearSliderThumb(Graphics& g, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        const Slider::SliderStyle style, Slider& slider) override;
    
    void drawLinearSliderBackground(Graphics& g, int x, int y, int width, int height,
        float sliderPos,
        float minSliderPos,
        float maxSliderPos,
        const Slider::SliderStyle style, Slider& slider) override;

    void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        const Slider::SliderStyle style, Slider& slider) override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaderLookAndFeel)
};
