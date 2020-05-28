/*
  ==============================================================================

    MyNotchFilter.h
    Created: 27 May 2020 8:53:45pm
    Author:  jacop

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include"MyFilter.h"

//==============================================================================
/*
*/
class MyNotchFilter    : public MyFilter
{
public:
    MyNotchFilter();
    MyNotchFilter(int x, int y, int w, int h);
    ~MyNotchFilter();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyNotchFilter)
};
