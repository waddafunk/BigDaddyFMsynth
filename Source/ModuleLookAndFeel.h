/*
  ==============================================================================

    ModuleLookAndFeel.h
    Created: 23 May 2020 4:15:34pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ModuleLookAndFeel    : public Component
{
public:
    ModuleLookAndFeel();
    ~ModuleLookAndFeel();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModuleLookAndFeel)
};
