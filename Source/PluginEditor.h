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
#include "ModuleGui.h"
#include "WavePainter.h"
#include "SinePainter.h"
#include "TrianglePainter.h"
#include "SawPainter.h"
#include "SquarePainter.h"
#include "FilterGui.h"

//==============================================================================
/**
*/
class Fm_synthAudioProcessorEditor  : public AudioProcessorEditor, public  Slider::Listener
{
public:
    Fm_synthAudioProcessorEditor (Fm_synthAudioProcessor&);
    ~Fm_synthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider);



private:

    Fm_synthAudioProcessor& processor;
    AnimatedEditor anime;
    std::vector<ModuleGui *> modules;
    OSCSender sender;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Fm_synthAudioProcessorEditor)
};


