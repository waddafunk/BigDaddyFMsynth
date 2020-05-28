/*
  ==============================================================================

    FilterGraph.cpp
    Created: 27 May 2020 11:14:05am
    Author:  daveg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterGraph.h"
#include "MyLowPass.h"
#include "MyHighPass.h"
#include "MyBandPass.h"
#include "MyNotchFilter.h"


FilterGraph::FilterGraph() {

}
//==============================================================================
FilterGraph::FilterGraph(int x, int y, int width, int height)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    xPos = x;
    yPos = y;
    this->height = height;
    this->width = width;

    addGraphs();
}

FilterGraph::~FilterGraph()
{
    for (int i = 0; i < 4; i++)
        delete myGraphs[i];


}

void FilterGraph::paint (Graphics& g)
{
  
}

void FilterGraph::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void FilterGraph::setMyBounds()
{
    this->setBounds(xPos, yPos, width, height);

}

void FilterGraph::addGraphs()
{
    this->myGraphs.push_back(new MyLowPass(xPos, yPos, width, height));
    this->myGraphs.push_back(new MyHighPass(xPos, yPos, width, height));
    this->myGraphs.push_back(new MyBandPass(xPos, yPos, width, height));
    this->myGraphs.push_back(new MyNotchFilter(xPos, yPos, width, height));

    for (int i = 0; i < 4; i++) {
        myGraphs[i]->setMyBounds();
        myGraphs[i]->setCutoff(1000);
        myGraphs[i]->setResonance(0.7f);
    }

    this->setCutoff(100);   
    this->setResonance(0.7f);

    addAndMakeVisible(myGraphs[1]);


}

void FilterGraph::setCutoff(float cutoff)
{
    this->cutoff = cutoff;
}

void FilterGraph::setResonance(float resonance)
{
    this->resonance = resonance;
}

void FilterGraph::mouseDown(const MouseEvent& event) {
    triggerDistance = 50;
    float minDistance = 0;

    Point<float> mousePos(event.getMouseDownX(), event.getMouseDownY()), cutoffDrag(cutoff, resonance / 2);
    float currentDistance = mousePos.getDistanceFrom(cutoffDrag);
    if (currentDistance < triggerDistance) {
        cutoff = mousePos.getX();
        resonance = mousePos.getY() * 2;
        myGraphs[selectedGraph]->setCutoff(cutoff);
        myGraphs[selectedGraph]->setResonance(resonance);
    }


}
