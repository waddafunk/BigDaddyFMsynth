/*
  ==============================================================================

    ModuleGui.h
    Created: 23 May 2020 4:12:42pm
    Author:  daveg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MyAnime.h"
#include "MyMouseListener.h"
#include "KnobSection.h"

//==============================================================================
/*
*/
class ModuleGui    : public MyAnime, public MyMouseListener
{
public:
    ModuleGui();
    ModuleGui(int x, int y, int width, int height);
    ModuleGui(int x, int y);
    ~ModuleGui();

    void paint (Graphics&) override;
    void resized() override;

    void setMyBounds();

    void connectModules(ModuleGui module); //connects this module to another one using drag and drop and sets the current state in the matrix

    void addKnobSection(int x, int y, int w, int h);
    void addKnobSection(int x, int y, int w, int h, int nKnob);
    void addKnobSection(int x, int y, int w, int h, int nKnob, tSection type);
    void addKnobSection(int x, int y, int w, int h, int nKnob, tSection type, int row);




    //getters and setters
    int getXPos() const;
    void setXPos(int xPos);

    int getYPos() const;
    void setYPos(int yPos);

    int getHeight() const;
    void setHeight(int height);

    int getWidth() const;
    void setWidth(int width);

protected:
    int xPos;
    int yPos;
    int height;
    int width;
    std::vector<KnobSection*> knobSections;


private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModuleGui)
};
