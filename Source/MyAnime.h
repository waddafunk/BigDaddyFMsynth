/*
  ==============================================================================

    MyAnime.h
    Created: 23 May 2020 10:17:20pm
    Author:  jacop

  ==============================================================================
*/

#pragma once

class MyAnime : public AnimatedAppComponent {
public:
    //==============================================================================
    MyAnime()
    {
    }



    void update() override
    {
        // This function is called at the frequency specified by the setFramesPerSecond() call
        // in the constructor. You can use it to update counters, animate values, etc.

    }



    void paint(Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
    }


    void setComponentz() {}
    void incrementFrame(int frames){
        this->myframesPassed += frames;
    };


//---------------Getters----------------

    float getSaturation(){return mysaturation;}
    float getOpacity (){return myopacity;}
    float getBrightness(){return mybrightness;}
    float getContrast (){return mycontrast;}
    float getAlpha (){return myalpha;}
    float getHue (){return myhue;}
    float getInterpolated (){return myinterpolated;}
    float getOverlaid (){return myoverlaid;}
    int getFramesPassed (){return myframesPassed;}
    Colour getBaseColour(){return mybaseColour;}
    Colour getInterpolateColour(){return myinterpolateColour;}
    Colour getOverlayColour(){return myoverlayColour;}


//--------------Setters---------------
    void setSaturation(float sat){this->mysaturation = sat;}
    void setOpacity (float opacity){this->myopacity = opacity;}
    void setBrightness(float brightness){this->mybrightness = brightness;}
    void setContrast (float contrast){this->mycontrast = contrast;}
    void setAlpha (float alpha){this->myalpha = alpha;}
    void setHue (float hue){this->myhue = hue;}
    void setInterpolated(float inter){this->myinterpolated = inter;}
    void setOverlaid (float overlaid){this->myoverlaid = overlaid;}
    void setFramesPassed (int frames){this->myframesPassed = frames;}
    void setBaseColour (Colour baseColour){this->mybaseColour = baseColour;}
    void setInterpolateColour (Colour interpolateColour){this->myinterpolateColour = interpolateColour;}
    void setOverlayColour (Colour overlayColour){this->myoverlayColour = overlayColour;}



private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyAnime)

    float mysaturation = 1.0f;
    float myopacity = 1.0f;
    float mybrightness = 1.0f;
    float mycontrast = 1.0f;
    float myalpha = 1.0f;
    float myhue = 1.0f;
    float myinterpolated = 0.0f;
    float myoverlaid = 0.0f;
    int myframesPassed = 0;
    Colour mybaseColour;
    Colour myinterpolateColour;
    Colour myoverlayColour;
};
