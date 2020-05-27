/*
  ==============================================================================

    MyLowPass.h
    Created: 27 May 2020 8:51:40pm
    Author:  jacop

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include"ModuleGui.h"

//==============================================================================
/*
*/
class MyLowPass    : public ModuleGui
{
public:
    MyLowPass();
    MyLowPass(int x, int y, int w, int h);
    ~MyLowPass();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyLowPass)
};
