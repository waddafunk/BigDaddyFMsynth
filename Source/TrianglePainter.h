/*
  ==============================================================================

    TrianglePainter.h
    Created: 25 May 2020 5:56:30pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class TrianglePainter    : public Component
{
public:
    TrianglePainter();
    ~TrianglePainter();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrianglePainter)
};
