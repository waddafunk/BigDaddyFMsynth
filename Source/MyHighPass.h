/*
  ==============================================================================

    MyHighPass.h
    Created: 27 May 2020 8:52:08pm
    Author:  jacop

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include"ModuleGui.h"

//==============================================================================
/*
*/
class MyHighPass    : public ModuleGui
{
public:
    MyHighPass();
    MyHighPass(int x, int y, int w, int h);
    ~MyHighPass();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyHighPass)
};
