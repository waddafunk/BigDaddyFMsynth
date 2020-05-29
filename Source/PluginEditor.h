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
#include "OscillatorGui.h"
#include "EnvelopeGui.h"
#include "MatrixGui.h"

//==============================================================================
/**
*/
class Fm_synthAudioProcessorEditor  : public AudioProcessorEditor,  public Button::Listener
{
public:
    Fm_synthAudioProcessorEditor (Fm_synthAudioProcessor&);
    ~Fm_synthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;


   
    void buttonStateChanged(Button*) override;
    void buttonClicked(Button*) override;


private:

    Fm_synthAudioProcessor& processor;
    std::vector<ModuleGui *> modules;
    std::vector<TextButton*> textButtons;
    TextButton* currentButton = nullptr;;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Fm_synthAudioProcessorEditor)
};
