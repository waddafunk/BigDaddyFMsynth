/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


class MyAnime : public AnimatedAppComponent {
public:
    //==============================================================================
    MyAnime()
    {
        setSize(800, 600);
        setFramesPerSecond(60);
    }



    void update() override
    {
        // This function is called at the frequency specified by the setFramesPerSecond() call
        // in the constructor. You can use it to update counters, animate values, etc.

    }



    void paint(Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
    }



    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
    }



private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyAnime)
};

//==============================================================================
/**
*/
class Fm_synthAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Fm_synthAudioProcessorEditor (Fm_synthAudioProcessor&);
    ~Fm_synthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Fm_synthAudioProcessor& processor;
    MyAnime anime;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Fm_synthAudioProcessorEditor)
};


