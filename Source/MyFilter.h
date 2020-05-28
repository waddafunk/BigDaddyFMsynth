/*
  ==============================================================================

    MyFilter.h
    Created: 28 May 2020 12:15:15pm
    Author:  jacop

  ==============================================================================
*/

#pragma once
#include "ModuleGui.h"

class MyFilter : public ModuleGui {
public:
    //==============================================================================
    MyFilter()
    {
    }



    void paint(Graphics& g) override
    {
        
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
    }

    void setCutoff(float cutOff)    //float cutOff: cutoff frequency value in hertz
    {
        if(cutOff >= 20.0f && cutOff <= 10000.0f)   //unnecessary check?
            this->cutoff = cutOff * width / 10000.0f;   //adjust to component dimensions
    }

    void setResonance(float resonance)  //float resonance: range in [0, 1]
    {
    
        this->resonance = std::min(std::max(resonance, 0.0f), 1.0f); //noice
    }


    float getCutoff() 
    {
        return this->cutoff;
    }

    float getResonance() {
        return this->resonance;
    }



private:

    float cutoff = 440 * width / 10000.0f;
    float resonance = 0.7f * height;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyFilter)
};