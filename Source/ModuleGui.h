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

//==============================================================================
/*
*/
class ModuleGui    : public MyAnime
{
public:
    ModuleGui();
    ModuleGui(int x, int y, int height, int width);
    ModuleGui(int x, int y);
    ~ModuleGui();

    void paint (Graphics&) override;
    void resized() override;

    void setMyBounds();

    void connectModules(ModuleGui module); //connects this module to another one using drag and drop and sets the current state in the matrix


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


private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModuleGui)





};
