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
    anime.mod.addListener(this);
    anime.setComponentz();
    addAndMakeVisible(&anime.mod);

    jassert(sender.connect("127.0.0.1", 9001)); //not finding IP address

    modules.push_back(new ModuleGui(100,150)); //to be modified
    modules.push_back(new ModuleGui(200, 450)); //to be modified
    modules.push_back(new ModuleGui(400, 150)); //to be modified

    for (auto& module : modules) {
        addAndMakeVisible(module);
    }
}

Fm_synthAudioProcessorEditor::~Fm_synthAudioProcessorEditor()
{
    for (auto& module : modules) {
        delete module;
    }
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
    anime.setComponentz();
    addAndMakeVisible(&anime.mod);
    

    for (auto &module : modules) {
        module->setBounds(module->getX(), module->getY(), module->getWidth(), module->getHeight());
        addAndMakeVisible(module);
    }
    
}

void Fm_synthAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    anime.amount = (float)(slider->getValue() / 2 + 0.5f);
    repaint();
    sender.send("/juce/anime.mod", (float)anime.mod.getValue());
}