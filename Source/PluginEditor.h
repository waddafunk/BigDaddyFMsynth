/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include"AnimatedEditor.h"

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
    AnimatedEditor anime;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Fm_synthAudioProcessorEditor)
};


