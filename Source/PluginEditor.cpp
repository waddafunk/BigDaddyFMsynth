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
    sender.connect("127.0.0.1", 9001); //not finding IP address

    //sets windows attributes
   // setResizable(true, false);
   // setResizeLimits(300, 250, 10000, 10000);
    setSize (960, 540);


    //anime shit
    anime.setFramesPerSecond(60);
    anime.mod.addListener(this);
    anime.setComponentz();
    addAndMakeVisible(&anime.mod);

    


    //modules initialization
   // modules.push_back(new SinePainter(0,0)); //to be modified
    modules.push_back(new ModuleGui(20,20));
    modules.push_back(new FilterGui(60, 20));
    modules.push_back(new SinePainter(0, getHeight()/2,getWidth(),getHeight()/2));

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

   // anime.paint(g);
    //repaint();
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
       // module->setBounds(module->getX(), module->getY(), module->getWidth(), module->getHeight());
        module->setMyBounds();
        addAndMakeVisible(module);
    }
    
}

void Fm_synthAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    anime.amount = (float)(slider->getValue() / 2 + 0.5f);
    repaint();
    //sender.send("/juce/anime.mod", (float)anime.mod.getValue());
}