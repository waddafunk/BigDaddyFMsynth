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

    void setFreqHz(float freq);

    float getAmp() const;
    void setAmp(float amp);

    float getPhase() const;
    void setPhase(float phase);

    float getHeight() const;
    void setHeight(float height);

    float getWidth() const;
    void setWidth(float width);

    int getXPos() const;
    void setXPos(int xPos);

    int getYPos() const;
    void setYPos(int yPos);

    std::vector<float> getWavePainted() const;
    void setWavePainted(std::vector<float> wavePainted);

    bool getTriggered() const;
    void setTriggered(bool triggered);

    void toggle();

    float getBasefreq();
    void setBaseFreq(float freq);

    float getTraslationalVelocity();
    void setTraslationalVelocity(float velocity);


protected:
    float freq;
    float amp = 1.0f;
    float phase = 0.0f;
    float height = 300;
    float width = 300;
    bool triggered = false;
    int xPos;
    int yPos;
    float baseFreq = 2 * double_Pi / width; //one period 
    float traslationVelocity = 2 * double_Pi;


private:
    std::vector<float> wavePainted;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WavePainter)



};


