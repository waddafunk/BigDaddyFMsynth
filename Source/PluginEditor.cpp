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
    daFont = Typeface::createSystemTypefaceFor(BinaryData::Quicksand_Bold_otf, BinaryData::Quicksand_Bold_otfSize);
    
    daFont.setHeight(14);
    int height = 675;
    int width = 900;

    setSize(width, height);

    int barHeight = 20;


    int heightForY = height + barHeight;
    int heightForHeight = height - barHeight;

    int divisor = 5; //used to dra the matrix modules
    int v_divisor = 8; //used to dra the matrix modules
    int molt = 8; //used to dra the matrix modules

    int envelopeBarHeight = (height - 2 * barHeight) / v_divisor;
    currentView = tabName::oscillators;


    //modules initialization
    std::vector<ModuleGui*> oscillatorModules;
    std::vector<ModuleGui*> matrixModules;

    //oscillator module initialization
    oscillatorModules.push_back(new OscillatorGui(0, 2*barHeight, width, height - 2*barHeight));
    modules.push_back(oscillatorModules);


    //matrix module initialization

    for (int i = 0; i < 7; i++) {
        matrixModules.push_back(new EnvelopeGui(width * 3 / divisor + width / (molt / 2 * divisor), 2 * barHeight + i * envelopeBarHeight, width / divisor - width / (molt * divisor), envelopeBarHeight, i, false));
    }
    matrixModules.push_back(new EnvelopeGui(width * 3 / divisor + width / (molt / 2 * divisor), 2 * barHeight + 7 * envelopeBarHeight, width / divisor - width / (molt * divisor), envelopeBarHeight +3, 7, false));
    matrixModules.push_back(new EnvelopeGui(width * 4 / divisor + width / (molt * divisor), 2*barHeight , width / divisor - width / (molt * divisor), envelopeBarHeight,8));
    matrixModules.push_back(new MasterGui(width * 4 / divisor + width / (molt * divisor), 2*barHeight + envelopeBarHeight, width / divisor - width / (molt * divisor), height - 2 * barHeight- envelopeBarHeight));
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
    elementLabels.push_back(new Label("title", "Fratio"));
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
        label->setFont(daFont);
        label->setColour(Label::textColourId, Colour::fromRGB(243, 243, 245).darker(0.3));
        if (i < 4){
            label->setBounds(15 + i * width * 0.7 / elementLabels.size(), barHeight, width * 0.7 / elementLabels.size() + 18, barHeight);
            addAndMakeVisible(label);
        }
        else{
            if (i > 4 && i < 9) {
                label->setBounds(97 + i * width * 0.67 / elementLabels.size(), barHeight, width * 0.67 / elementLabels.size() + 100, barHeight);
                addAndMakeVisible(label);
            }
            else
            {
                if (i == 4) {
                    label->setBounds(i * width * 0.85 / elementLabels.size(), barHeight, width * 0.85 / elementLabels.size(), barHeight);
                    addAndMakeVisible(label);
                }
                else 
                {
                    if (i == 9) {
                        label->setBounds(i * width * 0.91 / elementLabels.size(), barHeight, width * 0.91 / elementLabels.size(), barHeight);
                        addAndMakeVisible(label);
                    }
                    else
                    {
                        label->setBounds(i * width / elementLabels.size(), barHeight, width * 0.95 / elementLabels.size(), barHeight);
                        addAndMakeVisible(label);
                    }
                }
            }
        }
             
        i++;
    }

    Label* label = nullptr;

    for (i = 0; i < 10; ++i) {
        
        if (i < 8) {
            label = new Label("title", "Osc" + std::to_string(i + 1));
            matrixLabels.push_back(label);
            label->setBounds(16 + i * width * 0.895 / elementLabels.size(), barHeight, width * 0.895 / elementLabels.size() + 18, barHeight);
            addAndMakeVisible(label);
            label->setVisible(false);
        }
        else {
            if (i == 8) {
                label = new Label("title", "Index envs");
                matrixLabels.push_back(label);
                label->setBounds(i * 0.96 * width / elementLabels.size(), barHeight, width / elementLabels.size(), barHeight);
                addAndMakeVisible(label);
                label->setVisible(false);
            }
            else {
                label = new Label("title", "Master");
                matrixLabels.push_back(label);
                label->setBounds(i * width * 1.08 / elementLabels.size(), barHeight, 1.08 * width / elementLabels.size(), barHeight);
                addAndMakeVisible(label);
                label->setVisible(false);
            }
        }
        label->setFont(daFont);
        label->setColour(Label::textColourId, Colour::fromRGB(243, 243, 245).darker(0.3));
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
