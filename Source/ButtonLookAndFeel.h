/*
  ==============================================================================

    ButtonLookAndFeel.h
    Created: 23 May 2020 4:15:22pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ButtonLookAndFeel : public LookAndFeel_V4
{
public:

    ButtonLookAndFeel();
    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
        bool isMouseOverButton, bool isButtonDown) override;

    void drawTickBox(Graphics& g, Component& component, float x, float y, float w, float h,
        bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown) override;
    
private:
    Image img1;

};
