/*
  ==============================================================================

    ModuleGui.cpp
    Created: 23 May 2020 4:12:42pm
    Author:  daveg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ModuleGui.h"

//==============================================================================
ModuleGui::ModuleGui()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

ModuleGui::ModuleGui(int x, int y, int width, int height) : xPos(x),yPos(y),width(width), height(height) {}
ModuleGui::ModuleGui(int x, int y) : xPos(x), yPos(y){
    height = 50;
    width = 50;
}

ModuleGui::~ModuleGui()
{
}

void ModuleGui::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("ModuleGui", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void ModuleGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void ModuleGui::setMyBounds(){
    this->setBounds(xPos, yPos, width, height);
}

void ModuleGui::connectModules(ModuleGui module)
{

}

int ModuleGui::getXPos() const
{
    return xPos;
}

void ModuleGui::setXPos(int xPos)
{
    this->xPos = xPos;
}

int ModuleGui::getYPos() const
{
    return yPos;
}

void ModuleGui::setYPos(int yPos)
{
    this->yPos = yPos;
}

int ModuleGui::getHeight() const
{
    return height;
}

void ModuleGui::setHeight(int height)
{
    this->height = height;
}

int ModuleGui::getWidth() const
{
    return width;
}

void ModuleGui::setWidth(int width)
{
    this->width = width;
}

