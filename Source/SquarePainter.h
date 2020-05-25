/*
  ==============================================================================

    SquarePainter.h
    Created: 25 May 2020 5:56:18pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include"ModuleGui.h"

//==============================================================================
/*
*/
class SquarePainter    : public ModuleGui
{
public:
    SquarePainter();
    SquarePainter(int x, int y);
    SquarePainter(int x, int y, int width, int height);
    ~SquarePainter();

    void paint(Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SquarePainter)
};
