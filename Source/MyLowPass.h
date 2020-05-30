/*
  ==============================================================================

    MyLowPass.h
    Created: 27 May 2020 8:51:40pm
    Author:  jacop

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MyFilter.h"

//==============================================================================
/*
*/
class MyLowPass    : public MyFilter
{
public:
    MyLowPass();
    MyLowPass(int x, int y, int w, int h);
    ~MyLowPass();

    void paint (Graphics&) override;
    void resized() override;

    //void mouseDrag(const MouseEvent& event) override;
    //void mouseUp(const MouseEvent& event) override;


private:


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyLowPass)
};
