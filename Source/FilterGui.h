/*
  ==============================================================================

    FilterGui.h
    Created: 23 May 2020 4:13:23pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterGui    : public Component
{
public:
    FilterGui();
    ~FilterGui();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterGui)
};
