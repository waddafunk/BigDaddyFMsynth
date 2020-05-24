/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Fm_synthAudioProcessorEditor::Fm_synthAudioProcessorEditor (Fm_synthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    anime.setFramesPerSecond(60);

    modules.push_back(new ModuleGui(100,150)); //to be modified
    modules.push_back(new ModuleGui(200, 450)); //to be modified
    modules.push_back(new ModuleGui(400, 150)); //to be modified

    for (auto& module : modules) {
        addAndMakeVisible(module);
    }
}

Fm_synthAudioProcessorEditor::~Fm_synthAudioProcessorEditor()
{
}

//==============================================================================
void Fm_synthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    anime.paint(g);
    repaint();
}

void Fm_synthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    setResizable(true, true);
    anime.setBounds(0, 0, getWidth(), getHeight());

    for (auto &module : modules) {
        module->setBounds(module->getX(), module->getY(), module->getWidth(), module->getHeight());
        addAndMakeVisible(module);
    }
    
}

void Fm_synthAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    anime.amount = (float)(slider->getValue() / 2 + 0.5f);
    repaint();
}