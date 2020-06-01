/*
  ==============================================================================

    FilterGui.cpp
    Created: 23 May 2020 4:13:23pm
    Author:  daveg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterGui.h"

//==============================================================================
FilterGui::FilterGui()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    xPos = 0;
    yPos = 0;
    height = 0;
    width = 0;
  //  addKnobSection(xPos, yPos, width, height, 2, tSection::filter);
}

FilterGui::FilterGui(int x, int y)
{
    xPos = x;
    yPos = y;
    height = 40;
    width = 40;
 //   addKnobSection(xPos, yPos, width, height, 2);
}

FilterGui::FilterGui(int x, int y, int w, int h)
{
    xPos = x;
    yPos = y;
    height = h;
    width = w;

    addMyFilters(2);
  //  addKnobSection(0, 3 * height / 4, width, height/4, 2);

}

FilterGui::FilterGui(int x, int y, int w, int h, int n)
{
    xPos = x;
    yPos = y;
    height = h;
    width = w;

    addMyFilters(n);

}

FilterGui::~FilterGui()
{
    for (auto& knobSection : knobSections) {
        delete knobSection;
    }

    for (auto& filter : myFilters) {
        delete filter;
    }

    for(auto& button : buttons )
    {
        LookAndFeel* temp = &button->getLookAndFeel();
        delete button;
        delete temp;
    }
}

void FilterGui::paint (Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey.darker(0.8));
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component


}

void FilterGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void FilterGui::addMyFilters(int n) {
    
    float div = 1.0f / (3 * n);
    ToggleButton *button = nullptr;
    MyFilter *filter = nullptr;
    for (size_t i = 0; i < n; ++i) {
        button = new ToggleButton();
        button->setName(std::to_string(i));
        button->setToggleState(false,false);
        button->setLookAndFeel(new ToggleButtonLookAndFeel());
        button->addListener(this);
        button->setBounds(i * 3 * div * width , height / 4, width * 1 * div , height / 2);
        buttons.push_back(button);

        if (i == 0) {
            filter = new MyHighPass((i + 1 + i * 2) * div * width, 0, width * 2 * div, height);
        }
        else {            
            filter = new MyLowPass((i + 1 + i * 2) * div * width, 0, width * 2 * div, height);
        }
        
        filter -> setMyBounds();
        myFilters.push_back(filter);

        addAndMakeVisible(button);
        addAndMakeVisible(filter);
    }
    
}

void FilterGui::buttonStateChanged(Button* button)
{
   
}

void FilterGui::buttonClicked(Button* button)
{
    int index = std::stoi(button->getName().toStdString());
    if (index < myFilters.size()) {
        myFilters[index]->toggle();
    }
}

/*
void FilterGui::addMyFilter(FilterGraph* painter) {
    myFilters.push_back(painter);
}
*/


