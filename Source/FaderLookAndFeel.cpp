/*
  ==============================================================================

    FaderLookAndFeel.cpp
    Created: 23 May 2020 4:15:12pm
    Author:  daveg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FaderLookAndFeel.h"

//==============================================================================
FaderLookAndFeel::FaderLookAndFeel()
{
}

void FaderLookAndFeel::drawRoundThumb(Graphics& g, float x, float y, float diameter, Colour colour, float outlineThickness)
{
    auto halfThickness = outlineThickness * 0.5f;

    Path p;
    juce::Rectangle<int> thumb;
    thumb.setBounds(x*0.99,y,diameter*1.2, diameter*1.2/2);
    p.addRoundedRectangle(thumb, 3);

    DropShadow(Colours::black, 1, {}).drawForPath(g, p);

    g.setColour(Colours::darkred.darker(0.5));
    g.fillPath(p);
    g.setColour(Colours::darkred.darker(0.9));
    g.strokePath(p, PathStrokeType(outlineThickness));
}

void FaderLookAndFeel::drawLinearSliderThumb(Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider)
{
    auto sliderRadius = (float)(getSliderThumbRadius(slider) - 2);

    auto isDownOrDragging = slider.isEnabled() && (slider.isMouseOverOrDragging() || slider.isMouseButtonDown());

    auto knobColour = slider.findColour(Slider::thumbColourId)
        .withMultipliedSaturation((slider.hasKeyboardFocus(false) || isDownOrDragging) ? 1.3f : 0.9f)
        .withMultipliedAlpha(slider.isEnabled() ? 1.0f : 0.7f);

    if (style == Slider::LinearHorizontal || style == Slider::LinearVertical)
    {
        float kx, ky;

        if (style == Slider::LinearVertical)
        {
            kx = x + width * 0.5f;
            ky = sliderPos;
        }
        else
        {
            kx = sliderPos;
            ky = y + height * 0.5f;
        }

        auto outlineThickness = slider.isEnabled() ? 0.8f : 0.3f;

       drawRoundThumb(g,
            kx - sliderRadius,
            ky - sliderRadius,
            sliderRadius * 2.0f,
            knobColour, outlineThickness);
    }
    else
    {
        // Just call the base class for the demo
        LookAndFeel_V2::drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
    }
}


void FaderLookAndFeel::drawLinearSliderBackground(Graphics& g, int x, int y, int width, int height,
    float sliderPos, float minSliderPos, float maxSliderPos , const Slider::SliderStyle, Slider& slider)
{
    auto sliderRadius = getSliderThumbRadius(slider) - 5.0f;
    Path on, off;

    if (slider.isHorizontal())
    {
        auto iy = y + height * 0.5f - sliderRadius * 0.5f;
        Rectangle<float> r(x - sliderRadius * 0.5f, iy, width + sliderRadius, sliderRadius);
        auto onW = r.getWidth() * ((float)slider.valueToProportionOfLength(slider.getValue()));

        on.addRectangle(r.removeFromLeft(onW));
        off.addRectangle(r);
    }
    else
    {
        auto ix = x + width * 0.5f - sliderRadius * 0.5f;
        Rectangle<float> r(ix, y - sliderRadius * 0.5f, sliderRadius, height + sliderRadius);
        auto onH = r.getHeight() * ((float)slider.valueToProportionOfLength(slider.getValue()));

        on.addRectangle(r.removeFromBottom(onH));
        off.addRectangle(r);
    }


    ColourGradient* gradient = new ColourGradient(Colours::grey.brighter(0.2),x,slider.getBottom(), Colours::aliceblue, x, y,false);
    gradient->clearColours();
    gradient->addColour(0, Colours::brown);
    gradient->addColour(0.3, getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId).darker(0.9));
    gradient->addColour(0.5, Colours::deepskyblue.darker(0.8));
    gradient->addColour(0.9, Colours::indianred.darker(0.4));

    g.setGradientFill(*gradient);
    
    g.fillPath(on);

    g.setColour(Colours::black);
    g.fillPath(off);

    delete gradient;
 }



void FaderLookAndFeel::drawLinearSlider(Graphics& g, int x, int y, int width, int height,
    float sliderPos, float minSliderPos, float maxSliderPos,
    const Slider::SliderStyle style, Slider& slider)
{
        drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
}