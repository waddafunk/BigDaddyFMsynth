/*
  ==============================================================================

    KnobLookAndFeel.cpp
    Created: 23 May 2020 4:14:57pm
    Author:  daveg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "KnobLookAndFeel.h"



//==============================================================================
KnobLookAndFeel::KnobLookAndFeel()
{
    img1 = ImageCache::getFromMemory(BinaryData::Carbon_png, BinaryData::Carbon_pngSize);
}

//==============================================================================


void KnobLookAndFeel::drawRotarySlider(Graphics& g,
    int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{

    if (img1.isValid())
    {
        const double rotation = (slider.getValue()
            - slider.getMinimum())
            / (slider.getMaximum()
                - slider.getMinimum());

        const int frames = img1.getHeight() / img1.getWidth();
        const int frameId = (int)ceil(rotation * ((double)frames - 1.0));
        const float radius = jmin(width / 2.0f, height / 2.0f) - 10;
        const float centerX = x + width * 0.5f;
        const float centerY = y + height * 0.5f;
        const float rx = centerX - radius - 1.0f;
        const float ry = centerY - radius;

        g.drawImage(img1,
            (int)rx,
            (int)ry,
            2 * (int)radius,
            2 * (int)radius,
            0,
            frameId * img1.getWidth(),
            img1.getWidth(),
            img1.getWidth());
    }
    else
    {
        static const float textPpercent = 0.35f;
        Rectangle<float> text_bounds(1.0f + width * (1.0f - textPpercent) / 2.0f,
            0.5f * height, width * textPpercent, 0.5f * height);

        g.setColour(Colours::white);

        g.drawFittedText(String("No Image"), text_bounds.getSmallestIntegerContainer(),
            Justification::horizontallyCentred | Justification::centred, 1);


    }
}



Label* KnobLookAndFeel::createSliderTextBox(Slider& slider)
{
    Label* l = LookAndFeel_V3::createSliderTextBox(slider);
 //   l->setBorderSize(BorderSize<int>(2, 2, 40, 2));
    l->setColour(Label::outlineColourId, Colours::transparentWhite);
    l->setColour(Label::outlineWhenEditingColourId, Colours::transparentWhite);
    return l;
}