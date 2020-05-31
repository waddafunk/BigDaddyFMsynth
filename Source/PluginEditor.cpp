/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Fm_synthAudioProcessorEditor::Fm_synthAudioProcessorEditor(Fm_synthAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{

    //int height = 750;
    //int width = 1000;

    int height = 675;
    int width = 900;

    setSize(width, height);

    int barHeight = 20;
    int envelopeBarHeight = height * 2 / 12;

    int heightForY = height + barHeight;
    int heightForHeight = height - barHeight;

    int divisor = 5; //used to dra the matrix modules
    int v_divisor = 8; //used to dra the matrix modules
    int molt = 8; //used to dra the matrix modules

    currentView = tabName::oscillators;


    //modules initialization
    std::vector<ModuleGui*> oscillatorModules;
    std::vector<ModuleGui*> matrixModules;

    //oscillator module initialization
    oscillatorModules.push_back(new OscillatorGui(0, 2*barHeight, width, height - 2*barHeight));
    modules.push_back(oscillatorModules);


    //matrix module initialization

    matrixModules.push_back(new EnvelopeGui(width * 3 / divisor + width / (molt / 2 * divisor), 2*barHeight + 0 * (height - 2*barHeight) / v_divisor, width / divisor - width / (molt * divisor), (height - 2*barHeight) / v_divisor, 0,true));
    matrixModules.push_back(new EnvelopeGui(width * 3 / divisor + width / (molt / 2 * divisor), 2*barHeight + 1 * (height - 2*barHeight) / v_divisor, width / divisor - width / (molt * divisor), (height - 2*barHeight) / v_divisor, 1, true));
    matrixModules.push_back(new EnvelopeGui(width * 3 / divisor + width / (molt / 2 * divisor), 2*barHeight + 2 * (height - 2*barHeight) / v_divisor, width / divisor - width / (molt * divisor), (height - 2*barHeight) / v_divisor, 2, true));
    matrixModules.push_back(new EnvelopeGui(width * 3 / divisor + width / (molt / 2 * divisor), 2*barHeight + 3 * (height - 2*barHeight) / v_divisor, width / divisor - width / (molt * divisor), (height - 2*barHeight) / v_divisor, 3, true));
    matrixModules.push_back(new EnvelopeGui(width * 3 / divisor + width / (molt / 2 * divisor), 2*barHeight + 4 * (height - 2*barHeight) / v_divisor, width / divisor - width / (molt * divisor), (height - 2*barHeight) / v_divisor, 4, true));
    matrixModules.push_back(new EnvelopeGui(width * 3 / divisor + width / (molt / 2 * divisor), 2*barHeight + 5 * (height - 2*barHeight) / v_divisor, width / divisor - width / (molt * divisor), (height - 2*barHeight) / v_divisor, 5, true));
    matrixModules.push_back(new EnvelopeGui(width * 3 / divisor + width / (molt / 2 * divisor), 2*barHeight + 6 * (height - 2*barHeight) / v_divisor, width / divisor - width / (molt * divisor), (height - 2*barHeight) / v_divisor, 6, true));
    matrixModules.push_back(new EnvelopeGui(width * 3 / divisor + width / (molt / 2 * divisor), 2*barHeight + 7 * (height - 2*barHeight) / v_divisor, width / divisor - width / (molt * divisor), (height - 2*barHeight) / v_divisor, 7, true));
    matrixModules.push_back(new EnvelopeGui(width * 4 / divisor + width / (molt * divisor), 2*barHeight , width / divisor - width / (molt * divisor), envelopeBarHeight,8));
    matrixModules.push_back(new MasterGui(width * 4 / divisor + width / (molt * divisor), 2*barHeight + envelopeBarHeight, width / divisor - width / (molt * divisor), height -barHeight- envelopeBarHeight));
    matrixModules.push_back(new MatrixGui(0, 2*barHeight, width * 3 / divisor + width / (4 * divisor), height - 2*barHeight));

    modules.push_back(matrixModules);


    //adds and makes visible all the created modules 
    size_t  i = 0;
    for (auto& moduleType : modules) {
        for (auto& module : moduleType) {
            module->setFramesPerSecond(60);
            module->setMyBounds();
            addAndMakeVisible(module);
            if (i == 1) {
                module->setVisible(false);
            }
        }
        i++;
    }


    //textButtons initialization
    TextButton* tempButton = new TextButton(tabNameToString(tabName::oscillators));
    tempButton->setState(Button::ButtonState::buttonDown);
    textButtons.push_back(tempButton);
    tempButton = new TextButton(tabNameToString(tabName::matrix));
    tempButton->setState(Button::ButtonState::buttonNormal);
    textButtons.push_back(tempButton);

    i = 0;
    for (auto& button : textButtons) {
        button->setBounds(i * width / textButtons.size(), 0, width / textButtons.size(), barHeight);
        addAndMakeVisible(button);
        button->setLookAndFeel(&buttonLAF);
        button->addListener(this);
        i++;
    }

    //elementLabels initialization

    elementLabels.push_back(new Label("title", "Amp"));
    elementLabels.push_back(new Label("title", "Freq"));
    elementLabels.push_back(new Label("title", "Phase"));
    elementLabels.push_back(new Label("title", "Trigger"));
    elementLabels.push_back(new Label("title", "Wave"));
    elementLabels.push_back(new Label("title", "LfoA"));
    elementLabels.push_back(new Label("title", "LfoFr"));
    elementLabels.push_back(new Label("title", "LfoRate"));
    elementLabels.push_back(new Label("title", "LfoPhase"));
    elementLabels.push_back(new Label("title", "Highpass"));
    elementLabels.push_back(new Label("title", "Lowpass"));
    
    i = 0;
    for (auto& label : elementLabels) {
        if (i < 4){
            label->setBounds(15 + i * width * 0.7 / elementLabels.size(), barHeight, width * 0.7 / elementLabels.size() + 18, barHeight);
            addAndMakeVisible(label);
        }
        else if (i > 4 && i < 9){
            label->setBounds( 97 +i * width * 0.67 / elementLabels.size(), barHeight, width * 0.67/ elementLabels.size() +100, barHeight);
            addAndMakeVisible(label);
        }
        else
        {
            label->setBounds(i * width * 0.85 / elementLabels.size(), barHeight, width * 0.85 / elementLabels.size() , barHeight);
            addAndMakeVisible(label);
        }
        if (i == 10) {
            label->setBounds(i * width * 0.95  / elementLabels.size(), barHeight, width * 0.95 / elementLabels.size(), barHeight);
            addAndMakeVisible(label);
        }
        i++;
    }

    matrixLabels.push_back(new Label("title", "Osc0"));
    matrixLabels.push_back(new Label("title", "Osc1"));
    matrixLabels.push_back(new Label("title", "Osc2"));
    matrixLabels.push_back(new Label("title", "Osc3"));
    matrixLabels.push_back(new Label("title", "Osc4"));
    matrixLabels.push_back(new Label("title", "Osc5"));
    matrixLabels.push_back(new Label("title", "Osc6"));
    matrixLabels.push_back(new Label("title", "Osc7"));
    matrixLabels.push_back(new Label("title", "Mod. index envs"));
    matrixLabels.push_back(new Label("title", "Master"));

    i = 0;
    for (auto& label : matrixLabels) {
        if (i < 8) {
            label->setBounds(15 + i * width * 0.895 / elementLabels.size(), barHeight, width * 0.895 / elementLabels.size() + 18, barHeight);
            addAndMakeVisible(label);
            label->setVisible(false);
        }

        else if (i == 8) {
            label->setBounds( i *0.95* width  / elementLabels.size(), barHeight, width / elementLabels.size() , barHeight);
            addAndMakeVisible(label);
            label->setVisible(false);
        }

        else {
            label->setBounds( i * width*1.08 / elementLabels.size(), barHeight, 1.08 * width / elementLabels.size() , barHeight);
            addAndMakeVisible(label);
            label->setVisible(false);
        }
        
        i++;
    }
}

Fm_synthAudioProcessorEditor::~Fm_synthAudioProcessorEditor()
{
    for (auto& moduleType : modules) {
        for (auto& module : moduleType) {
            if (module != nullptr) {
                delete module;
            }
        }
    }
    for (auto& button : textButtons) {
        if (button != nullptr) {
            delete button;
        }
    }
    for (auto& label : elementLabels) {
        if (label != nullptr) {
            delete label;
        }
    }
    for (auto& label : matrixLabels) {
        if (label != nullptr) {
            delete label;
        }
    }
}

//==============================================================================
void Fm_synthAudioProcessorEditor::paint(Graphics& g)
{

}

void Fm_synthAudioProcessorEditor::resized()
{
  
}


String Fm_synthAudioProcessorEditor::tabNameToString(tabName tabname)
{
    switch (tabname)
    {
    case tabName::matrix: return "Matrix";
    case tabName::oscillators: return "Oscillators";
    default: return "Matrix";
    }
}

tabName Fm_synthAudioProcessorEditor::stringToTabName(String tabname)
{
    if (tabname == "Matrix") {
        return tabName::matrix;
    }
    if (tabname == "Oscillators") {
        return tabName::oscillators;
    }

    return tabName::oscillators;
}




void Fm_synthAudioProcessorEditor::buttonStateChanged(Button* button)
{
}

void Fm_synthAudioProcessorEditor::buttonClicked(Button* button) {
    if (stringToTabName(button->getButtonText()) != currentView) {
        changeView(stringToTabName(button->getButtonText()));
    } 
}


//the function used to actually change the tab view
void Fm_synthAudioProcessorEditor::changeView(tabName tabname) {
    switch (tabname) {
    case tabName::matrix:
        for (auto& module : modules[0]) {
            module->setVisible(false);
        }
        for (auto& module : modules[1]) {
            module->setVisible(true);
        }
        for (auto& label : elementLabels){
            label->setVisible(false);
        }
        for (auto& label : matrixLabels){
            label->setVisible(true);
        }

        break;
    case tabName::oscillators:
        for (auto& module : modules[1]) {
            module->setVisible(false);
        }
        for (auto& module : modules[0]) {
            module->setVisible(true);
        }
        for (auto& label : elementLabels){
            label->setVisible(true);
        }
        for (auto& label : matrixLabels) {
            label->setVisible(false);
        }
        break;
    default:
        break;
    }
    currentView = tabname;
//    repaint();
}
