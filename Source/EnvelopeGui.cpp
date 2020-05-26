/*
  ==============================================================================

    EnvelopeGui.cpp
    Created: 23 May 2020 4:13:15pm
    Author:  daveg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EnvelopeGui.h"

//==============================================================================
EnvelopeGui::EnvelopeGui()
{

    height = 300;
    width = 300;
    currentPoint = nullptr;
    env[envelope::attack]->setCoordinates(xPos, yPos + height * 3 / 4);
    env[envelope::decay]->setCoordinates(xPos + width/3, yPos + height/4);
    env[envelope::sustain]->setCoordinates(xPos + width*2/3, yPos +  height* 2 / 4);
    env[envelope::release]->setCoordinates(xPos + width, yPos + height);
}


EnvelopeGui::EnvelopeGui(int x, int y, int width, int height )
{
    this->xPos = x;
    this->yPos = y;
    this->width = width;
    this->height = height;
    currentPoint = nullptr;
    env[envelope::attack]->setCoordinates(xPos+ width/4, yPos + height/4);
    env[envelope::decay]->setCoordinates(xPos + width *2 /4, yPos + height* 2 / 4);
    env[envelope::sustain]->setCoordinates(xPos + width * 3 / 4, yPos + height * 2 / 4);
    env[envelope::release]->setCoordinates(xPos + width, yPos + height);
}


EnvelopeGui::~EnvelopeGui()
{
}

void EnvelopeGui::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(Colours::white);

    g.setColour(getLookAndFeel().findColour(Slider::thumbColourId));

    Path envelopePath;

    Point<float> start((float)xPos, (float)(yPos + height));
    envelopePath.startNewSubPath(start);  // if this is the first point, start a new path..

   
    for (std::map<envelope, Coordinate *>::const_iterator it = env.begin(); it != env.end(); ++it){
        Point<float> p(it->second->getX(), it->second->getY());
        g.fillEllipse(p.x-5 , p.y-5 , 10.0f, 10.0f);
        envelopePath.lineTo(p);
    }
  


    // draw an outline around the path that we have created
    g.strokePath(envelopePath, PathStrokeType(4.0f)); // [4]


}

void EnvelopeGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}


//if mouse down is close to one of the points of the envelope the magnet that point to the mouse pointer
//if 2 points or more points are close enought to the mouse pointer magnat the closest
//if 2 points or more points are close enought have the same distance from the mouse pointer then magnet the first one
//TODO decay cannot be higher in value than attack
//TODO sustain cannot be higher in value than decay
//TODO release has the same height as sustan but can be moved in the x axis
void EnvelopeGui::mouseDown(const MouseEvent& event){
    triggerDistance = 50;
    Coordinate mousePos;
    Coordinate *closestPoint = nullptr;
    float minDistance = 0;
    float currentDistance = 0;
    mousePos.setCoordinates(event.getMouseDownX(), event.getMouseDownY());

    //finds the closest point
    for (std::map<envelope, Coordinate*>::const_iterator it = env.begin(); it != env.end(); ++it) {
        Point<float> p(it->second->getX(), it->second->getY());
        
        currentDistance = mousePos.computeDistanceFrom(*it->second);


        if (it == env.begin()) {
            minDistance = currentDistance;
            closestPoint = it->second;
        }
        else {
            if (minDistance > currentDistance) {
                minDistance = currentDistance;
                closestPoint = it->second;
            }
        }
        
    }

    if (minDistance < triggerDistance) {
        closestPoint->setCoordinates(mousePos);
        currentPoint = closestPoint;
        repaint();
    }
    else {
        currentPoint = nullptr;
    }

}

void EnvelopeGui::mouseDrag(const MouseEvent& event)
{
    Coordinate mousePos;
    mousePos.setCoordinates(event.getPosition().getX(), event.getPosition().getY());

    if (currentPoint != nullptr) {
        currentPoint->setCoordinates(mousePos);
    }

}

void EnvelopeGui::mouseUp(const MouseEvent& event)
{
    currentPoint = nullptr;
}
