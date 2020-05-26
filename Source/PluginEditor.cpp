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

    //sets sender
    sender.connect("127.0.0.1", 9001);

    //sets windows attributes
   // setResizable(true, false);
   // setResizeLimits(300, 250, 10000, 10000);
    setSize (960, 540);

    //modules initialization
    modules.push_back(new OscillatorGui(0, getHeight()/2,getWidth(),getHeight()/2));
    modules.push_back(new EnvelopeGui(0, 0, getWidth() / 2, getHeight() / 2));
    modules.push_back(new FilterGui(getWidth() / 2, 0, getWidth() / 4, getHeight() / 4));
    modules.push_back(new EnvelopeGui(getWidth() / 2, getHeight() / 4, getWidth() / 4, getHeight() / 4));
    modules.push_back(new EnvelopeGui(getWidth() * 3 / 4, 0, getWidth() / 4, getHeight() / 4));
    modules.push_back(new EnvelopeGui(getWidth() * 3 / 4, getHeight() / 4, getWidth() / 4, getHeight() / 4));
    //adds and makes visible all the created modules 
    for (auto& module : modules) {
        module->setFramesPerSecond(60);
        module->setMyBounds();
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

}

void Fm_synthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    /**setResizable(true, true);
    

    for (auto &module : modules) {
       // module->setBounds(module->getX(), module->getY(), module->getWidth(), module->getHeight());
        module->setMyBounds();
        addAndMakeVisible(module);
    } */
    
}

void Fm_synthAudioProcessorEditor::sliderValueChanged(Slider* slider) {

    sender.send("/juce/testsend", 1.0f);
}