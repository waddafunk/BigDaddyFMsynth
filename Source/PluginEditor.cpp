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


    int height = 750;
    int width = 1000;

    setSize(width, height);


    int barHeight = 20;
    int envelopeBarHeight = height * 2 / 12;

    int heightForY = height + barHeight;
    int heightForHeight = height - barHeight;


    currentView = tabName::Matrix;

    TextButton* tempButton = new TextButton(tabNameToString(tabName::Matrix));
    tempButton->setState(Button::ButtonState::buttonDown);
    textButtons.push_back(tempButton);
    int divisor = 5; //used to dra the matrix modules
    int v_divisor = 8; //used to dra the matrix modules
    int molt = 8; //used to dra the matrix modules
    tempButton = new TextButton(tabNameToString(tabName::Fxs));
    tempButton->setState(Button::ButtonState::buttonNormal);
    textButtons.push_back(tempButton);


    //modules initialization
    std::vector<ModuleGui*> fxsModules;
    std::vector<ModuleGui*> matrixModules;


    matrixModules.push_back(new EnvelopeGui(width * 3 / divisor + width / (molt / 2 * divisor), barHeight + 0 * (height - barHeight) / v_divisor, width / divisor - width / (molt * divisor), (height - barHeight) / v_divisor));
    matrixModules.push_back(new EnvelopeGui(width * 3 / divisor + width / (molt / 2 * divisor), barHeight + 1 * (height - barHeight) / v_divisor, width / divisor - width / (molt * divisor), (height - barHeight) / v_divisor));
    matrixModules.push_back(new EnvelopeGui(width * 3 / divisor + width / (molt / 2 * divisor), barHeight + 2 * (height - barHeight) / v_divisor, width / divisor - width / (molt * divisor), (height - barHeight) / v_divisor));
    matrixModules.push_back(new EnvelopeGui(width * 3 / divisor + width / (molt / 2 * divisor), barHeight + 3 * (height - barHeight) / v_divisor, width / divisor - width / (molt * divisor), (height - barHeight) / v_divisor));
    matrixModules.push_back(new EnvelopeGui(width * 3 / divisor + width / (molt / 2 * divisor), barHeight + 4 * (height - barHeight) / v_divisor, width / divisor - width / (molt * divisor), (height - barHeight) / v_divisor));
    matrixModules.push_back(new EnvelopeGui(width * 3 / divisor + width / (molt / 2 * divisor), barHeight + 5 * (height - barHeight) / v_divisor, width / divisor - width / (molt * divisor), (height - barHeight) / v_divisor));
    matrixModules.push_back(new EnvelopeGui(width * 3 / divisor + width / (molt / 2 * divisor), barHeight + 6 * (height - barHeight) / v_divisor, width / divisor - width / (molt * divisor), (height - barHeight) / v_divisor));
    matrixModules.push_back(new EnvelopeGui(width * 3 / divisor + width / (molt / 2 * divisor), barHeight + 7 * (height - barHeight) / v_divisor, width / divisor - width / (molt * divisor), (height - barHeight) / v_divisor));
    matrixModules.push_back(new EnvelopeGui(width * 4 / divisor + width / (molt * divisor), barHeight , width / divisor - width / (molt * divisor), envelopeBarHeight));
    matrixModules.push_back(new MasterGui(width * 4 / divisor + width / (molt * divisor), barHeight + envelopeBarHeight, width / divisor - width / (molt * divisor), height - envelopeBarHeight));
    matrixModules.push_back(new MatrixGui(0, barHeight, width * 3 / divisor + width / (4 * divisor), height - barHeight));

    modules.push_back(matrixModules);




    fxsModules.push_back(new OscillatorGui(0, 0, width * 2 / divisor, height));
   // fxsModules.push_back(new LfoGui(width / 2, height / 2, width / 2, height / 2));
    //fxsModules.push_back(new FilterGui(0, 0, width / 2, height / 2));
    fxsModules.push_back(new EnvelopeGui(width * 3 / 4, height / 4, width / 4, height / 4));

    modules.push_back(fxsModules);



    //adds and makes visible all the created modules 
    int i = 0;
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


    i = 0;
    for (auto& button : textButtons) {
        button->setBounds(i * width / textButtons.size(), 0, width / textButtons.size(), barHeight);
        addAndMakeVisible(button);
        button->addListener(this);
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
    case tabName::Matrix: return "Matrix";
    case tabName::Fxs: return "Fxs";
    default: return "Matrix";
    }
}

tabName Fm_synthAudioProcessorEditor::stringToTabName(String tabname)
{
    if (tabname == "Matrix") {
        return tabName::Matrix;
    }
    if (tabname == "Fxs") {
        return tabName::Fxs;
    }

    return tabName::Matrix;
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
    case tabName::Matrix:
        for (auto& module : modules[1]) {
            module->setVisible(false);
        }
        for (auto& module : modules[0]) {
            module->setVisible(true);
        }

        break;
    case tabName::Fxs:
        for (auto& module : modules[0]) {
            module->setVisible(false);
        }
        for (auto& module : modules[1]) {
            module->setVisible(true);
        }
        break;
    default:
        break;
    }
    currentView = tabname;
//    repaint();
}
