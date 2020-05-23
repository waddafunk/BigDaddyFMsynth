/*
  ==============================================================================

    ModuleGui.h
    Created: 23 May 2020 4:12:42pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MyAnime.h"

//==============================================================================
/*
*/
class ModuleGui    : public MyAnime
{
public:
    ModuleGui();
    ~ModuleGui();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModuleGui)
};
