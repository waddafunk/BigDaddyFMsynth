/*
  ==============================================================================

    MyBandPass.h
    Created: 27 May 2020 8:52:33pm
    Author:  jacop

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include"ModuleGui.h"

//==============================================================================
/*
*/
class MyBandPass : public ModuleGui
{
public:
    MyBandPass();
    MyBandPass(int x, int y, int w, int h);
    ~MyBandPass();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyBandPass)
};
