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

    void drawToggleButton(Graphics&, ToggleButton&,
                          bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:
    Image img1;

};
