/*
  ==============================================================================

    WavePainter.h
    Created: 25 May 2020 2:21:53pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MyAnime.h"

//==============================================================================
/*
*/
class WavePainter    : public MyAnime
{
public:

//--------------------constructors and distructor
    WavePainter();
    WavePainter(int x, int y);
    WavePainter(int x, int y, int height, int width);
    ~WavePainter();

    void setMyBounds();


//----------------paint and shit
    void paint (Graphics&) override;
    void resized() override;
    //void my_setBounds();


//--------------------Setters And Getters-----------
    float getFreq() const;
    void setFreq(float freq);
    float getHeight() const;
    void setHeight(float height);

    float getWidth() const;
    void setWidth(float width);

    int getXPos() const;
    void setXPos(int xPos);

    int getYPos() const;
    void setYPos(int yPos);

    void setTriggered(bool isTriggered);
    bool getTriggered() { return triggered; }
    bool toggleTriggered() { this->triggered = !this->triggered; }



protected:
    float freq =0.02f;
    float height = 300;
    float width = 300;
    int xPos;
    int yPos;


private:
    bool triggered = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WavePainter)

public:


};


