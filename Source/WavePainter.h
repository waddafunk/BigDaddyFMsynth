/*
  ==============================================================================

    WavePainter.h
    Created: 25 May 2020 2:21:53pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ModuleGui.h"

//==============================================================================
/*
*/
class WavePainter    : public ModuleGui
{
public:

//--------------------constructors and distructor
    WavePainter();
    WavePainter(int x, int y);
    ~WavePainter();


//----------------paint and shit
    void paint (Graphics&) override;
    void resized() override;
    //void my_setBounds();


//--------------------Setters And Getters-----------
    float getFreq() const;
    void setFreq(float freq);



protected:
    float freq =0.02f;
    float height = 300;
    float width = 300;


private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WavePainter)

};
