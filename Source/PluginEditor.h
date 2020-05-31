/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
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
#include "MasterGui.h"
#include "ButtonLookAndFeel.h"


enum class tabName { matrix, oscillators };

//==============================================================================
/**
*/
class Fm_synthAudioProcessorEditor : public AudioProcessorEditor, public Button::Listener
{
public:
    Fm_synthAudioProcessorEditor(Fm_synthAudioProcessor&);
    ~Fm_synthAudioProcessorEditor();

    //==============================================================================
    void paint(Graphics&) override;
    void resized() override;

    String tabNameToString(tabName tabname);

    tabName stringToTabName(String tabname);



    void buttonStateChanged(Button* button) override;
    void buttonClicked(Button* button) override;

    void changeView(tabName tabname);


private:

    Fm_synthAudioProcessor& processor;
    ButtonLookAndFeel buttonLAF;
    std::vector<Label*> elementLabels;
    std::vector<Label*> matrixLabels;
    std::vector<std::vector<ModuleGui*>> modules;
    std::vector<TextButton*> textButtons;
    tabName currentView;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Fm_synthAudioProcessorEditor)
};
