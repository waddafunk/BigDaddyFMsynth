/*
  ==============================================================================

    SpectrogramGui.h
    Created: 27 May 2020 3:41:44pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SpectrogramGui    : public Component
{
public:
    SpectrogramGui();
    ~SpectrogramGui();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrogramGui)
};
