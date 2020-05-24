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



protected:

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

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyAnime)
};