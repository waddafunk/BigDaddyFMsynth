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

    void mouseDown(const MouseEvent& event) override;
    //void mouseDrag(const MouseEvent& event) override;
    //void mouseUp(const MouseEvent& event) override;

    void setCutoff(float cutOff);
    float getCutoff() { return this->cutoff; }

    void setResonance(float resonance);
    float getResonance() { return this->resonance; }

private:
    float triggerDistance = 0;
    bool moving = false;

    float cutoff = 440 * width / 10000;
    float resonance = 0.7 * height;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyLowPass)
};
