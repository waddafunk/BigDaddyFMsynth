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
        this->framesPassed += frames;
    };


//---------------Getters----------------

    float getSaturation(){return saturation;}
    float getOpacity (){return opacity;}
    float getBrightness(){return brightness;}
    float getContrast (){return contrast;}
    float getAlpha (){return alpha;}
    float getHue (){return hue;}
    float getInterpolated (){return interpolated;}
    float getOverlaid (){return overlaid;}
    int getFramesPassed (){return framesPassed;}
    Colour getBaseColour(){return baseColour;}
    Colour getInterpolateColour(){return interpolateColour;}
    Colour getOverlayColour(){return overlayColour;}


//--------------Setters---------------
    void setSaturation(float sat){this->saturation = sat;}
    void setOpacity (float opacity){this->opacity = opacity;}
    void setBrightness(float brightness){this->brightness = brightness;}
    void setContrast (float contrast){this->contrast = contrast;}
    void setAlpha (float alpha){this->alpha = alpha;}
    void setHue (float hue){this->hue = hue;}
    void setInterpolated(float inter){this->interpolated = inter;}
    void setOverlaid (float overlaid){this->overlaid = overlaid;}
    void setFramesPassed (int frames){this->framesPassed = frames;}
    void setBaseColour (Colour baseColour){this->baseColour = baseColour;}
    void setInterpolateColour (Colour interpolateColour){this->interpolateColour = interpolateColour;}
    void setOverlayColour (Colour overlayColour){this->overlayColour = overlayColour;}



private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyAnime)

    float saturation = 1.0f;
    float opacity = 1.0f;
    float brightness = 1.0f;
    float contrast = 1.0f;
    float alpha = 1.0f;
    float hue = 1.0f;
    float interpolated = 0.0f;
    float overlaid = 0.0f;
    int framesPassed = 0;
    Colour baseColour;
    Colour interpolateColour;
    Colour overlayColour;

};
