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
    env[envelope::attack]->setCoordinates(width / 4, height / 4);
    env[envelope::decay]->setCoordinates(width * 2 / 4, height * 2 / 4);
    env[envelope::sustain]->setCoordinates(width * 3 / 4, height * 2 / 4);
    env[envelope::release]->setCoordinates(width, height);
}


EnvelopeGui::EnvelopeGui(int x, int y, int width, int height )
{
    this->xPos = x;
    this->yPos = y;
    this->width = width;
    this->height = height;
    currentPoint = nullptr;
    env[envelope::attack]->setCoordinates(width/4,height/4);
    env[envelope::decay]->setCoordinates(width *2 /4,height* 2 / 4);
    env[envelope::sustain]->setCoordinates(width * 3 / 4,height * 2 / 4);
    env[envelope::release]->setCoordinates(width,height);
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

    Point<float> start((float)0, (float)(height));
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
//decay cannot be higher in value than attack
//sustain cannot be higher in value than decay
//release has the same height as sustan but can be moved in the x axis


void EnvelopeGui::mouseDown(const MouseEvent& event){
    triggerDistance = 50;
    Coordinate mousePos;
    Coordinate *closestPoint = nullptr;
    float minDistance = 0;
    float currentDistance = 0;
    mousePos.setCoordinates(event.getMouseDownX(), event.getMouseDownY());
    bool dontChange = false;

    //finds the closest point
    for (std::map<envelope, Coordinate*>::const_iterator it = env.begin(); it != env.end(); ++it) {
        Point<float> p(it->second->getX(), it->second->getY());
        
        currentDistance = mousePos.computeDistanceFrom(*it->second);


        if (it == env.begin()) {
            minDistance = currentDistance;
            closestPoint = it->second;
            currentEnv = it->first;
        } else {
            if (minDistance >= currentDistance) {
                if (minDistance > currentDistance) {
                    minDistance = currentDistance;
                    dontChange = false;
                }else { //if minDistance == currentDistance
                    if (mousePos.getX() < it->second->getX()) { //
                        dontChange = true;
                    }else {
                        dontChange = false;
                    }
                }
                
                if (!dontChange) {
                    closestPoint = it->second;
                    currentEnv = it->first;
                }
                
            }
        }
        
    }

    if (minDistance < triggerDistance) {
       // closestPoint->setCoordinates(mousePos);
        currentPoint = closestPoint;
        //repaint();
    }
    else {
        currentPoint = nullptr;
    }

}

void EnvelopeGui::mouseDrag(const MouseEvent& event)
{
    Coordinate mousePos;
    bool isLegalX = true;
    bool isLegalY = true;
    mousePos.setCoordinates(event.getPosition().getX(), event.getPosition().getY());

    envelope a;

    if (currentPoint != nullptr) {
        switch (currentEnv)
        {
        case attack : 
            if (mousePos.hasHigherXThan(*env[envelope::decay])) {
                isLegalX = false;
            }
            else {
                isLegalX = true;
            }

            if (mousePos.hasHigherYThan(*env[envelope::decay])) { //remember that Y works the opposite way... it grows when going down
                isLegalY = false;
            }
            else {
                isLegalY = true;
            }
            break;

        case decay:
            if (mousePos.hasLowerYThan(*env[envelope::attack])) { //remember that Y works the opposite way... it grows when going down
                isLegalY = false;
            }else {
                isLegalY = true;
            }

            if (mousePos.hasLowerXThan(*env[envelope::attack]) || mousePos.hasHigherXThan(*env[envelope::sustain])) {
                isLegalX = false;
            }
            else {
                isLegalX = true;
            }
            break;

        case sustain:

            if (mousePos.hasLowerYThan(*env[envelope::attack])) {
                isLegalY = false;
            }
            else {
                isLegalY = true;
            }
            if (mousePos.hasLowerXThan(*env[envelope::decay]) || mousePos.hasHigherXThan(*env[envelope::release])) {
                isLegalX = false;
            }
            else {
                isLegalX = true;
            }

            break;

        case release:
            isLegalY = false;
            if (mousePos.hasLowerXThan(*env[envelope::sustain]) || mousePos.getX() >  width) {
                isLegalX = false;
            }
            break;

        default:
            break;
        }

        if (isLegalX) {
            if (mousePos.getX() > 0) {
                currentPoint->setX(mousePos.getX());
            }
        }
        else {
            switch (currentEnv)
            {
            case envelope::attack : currentPoint->setX(env[envelope::decay]->getX());
                break;
            default:
                break;
            }
        }
        
        if (isLegalY) {
            if (mousePos.getY() < height) {
                currentPoint->setY(mousePos.getY());
                if (currentEnv == envelope::decay) {
                    env[envelope::sustain]->setY(currentPoint->getY());
                }
                else {
                    if (currentEnv == envelope::sustain) {
                        env[envelope::decay]->setY(currentPoint->getY());
                    }
                }
            }
        }
           
    }

}


int envToInt(envelope enve) {
    if (enve == envelope::attack) {
        return 0;
    }else {
        if (enve == envelope::decay) {
            return 1;
        }else {
            if (enve == envelope::sustain) {
                return 2;
            }else {
                if (enve == envelope::release) {
                    return 3;
                }
            }
        }
    }
    return 0;
}

void EnvelopeGui::mouseUp(const MouseEvent& event)
{
    currentPoint = nullptr;
}
