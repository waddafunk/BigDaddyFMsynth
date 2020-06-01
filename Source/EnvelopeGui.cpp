/*
  ==============================================================================

    EnvelopeGui.cpp
    Created: 23 May 2020 4:13:15pm
    Author:  daveg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EnvelopeGui.h"
#include "Converter.h"

//==============================================================================
EnvelopeGui::EnvelopeGui()
{
    isForMatrix = false;
    height = 300;
    width = 300;
    currentPoint = nullptr;
    sender = new MySender(tSection::envelope);
    env[envelope::attack]->setCoordinates(width / 4, height / 4);
    env[envelope::decay]->setCoordinates(width * 2 / 4, height * 2 / 4);
    env[envelope::sustain]->setCoordinates(width * 3 / 4, height * 2 / 4);
    env[envelope::release]->setCoordinates(width, height);
    id = 0;
    computeValuesAndTimes();

    sendAllData();
    pointSize = 6;
}


EnvelopeGui::EnvelopeGui(int x, int y, int width, int height,int id )
{
    isForMatrix = false;
    this->xPos = x;
    this->yPos = y;
    this->width = width;
    this->height = height;
    currentPoint = nullptr;
    sender = new MySender(tSection::envelope);
    env[envelope::attack]->setCoordinates(width/4,height/4);
    env[envelope::decay]->setCoordinates(width *2 /4,height* 2 / 4);
    env[envelope::sustain]->setCoordinates(width * 3 / 4,height * 2 / 4);
    env[envelope::release]->setCoordinates(width,height);
    computeValuesAndTimes();
    this->id = id;

    sendAllData();
    pointSize = 6;
}

EnvelopeGui::EnvelopeGui(int x, int y, int width, int height,int id, bool negativeRelease)
{
    isForMatrix = negativeRelease;
    this->xPos = x;
    this->yPos = y;
    this->width = width;
    this->height = height;
    currentPoint = nullptr;
    sender = new MySender(tSection::envelope);
    env[envelope::attack]->setCoordinates(width / 4, height / 4);
    env[envelope::decay]->setCoordinates(width * 2 / 4, height * 2 / 4);
    env[envelope::sustain]->setCoordinates(width * 3 / 4, height * 2 / 4);
    env[envelope::release]->setCoordinates(width, height);
//    counter++;
    this->id = id;

    computeValuesAndTimes();
    sendAllData();
    pointSize = 6;
}


EnvelopeGui::~EnvelopeGui()
{
    delete sender;
}

void EnvelopeGui::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(Colours::grey.darker(0.8));
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component


    //g.setColour(getLookAndFeel().findColour(Slider::thumbColourId));
    g.setColour(Colour::fromRGB(230,80,129));

    Path envelopePath;

    Point<float> start((float)0, (float)(height));
    envelopePath.startNewSubPath(start);  // if this is the first point, start a new path..

   
    for (std::map<envelope, Coordinate *>::const_iterator it = env.begin(); it != env.end(); ++it){
        Point<float> p(it->second->getX(), it->second->getY());
        g.fillEllipse(p.x- pointSize / 2, p.y-pointSize/2 , pointSize, pointSize);
        envelopePath.lineTo(p);
    }
  
    

    // draw an outline around the path that we have created
    g.strokePath(envelopePath, PathStrokeType(2.0f)); // [4]
    envelopePath.lineTo(start);
    //g.setColour(Colour::fromRGBA(83, 203, 230, 0.6));
    //g.setColour((getLookAndFeel().findColour(Slider::thumbColourId)).withMultipliedAlpha(0.3));

    g.setColour(Colour::fromRGB(230, 80, 129).withMultipliedAlpha(0.3));
    g.fillPath(envelopePath);

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
    bool illegalRight = false; //used to understand if i exit the area on the right or on the left
    bool isLegalY = true;
    bool illegalDown = false;
    mousePos.setCoordinates(event.getPosition().getX(), event.getPosition().getY());

    envelope a;

    if (currentPoint != nullptr) {
        isLegalX = true;
        isLegalY = true;
        illegalRight = false;
        illegalDown = false;
        switch (currentEnv)
        {
        case attack:
            if (mousePos.hasHigherXThan(*env[envelope::decay])) {
                isLegalX = false;
                illegalRight = true;
            }
            if (mousePos.getX() < 0) {
                isLegalX = false;
            }

            if (mousePos.hasHigherYThan(*env[envelope::decay])) { //remember that Y works the opposite way... it grows when going down
                isLegalY = false;
                illegalDown = true;
            }

            if (mousePos.getY()<0) { //remember that Y works the opposite way... it grows when going down
                isLegalY = false;
            }

            break;

        case decay:
            if (mousePos.hasLowerYThan(*env[envelope::attack])) { //remember that Y works the opposite way... it grows when going down
                isLegalY = false;
            }
            
            if (mousePos.hasHigherYThan(*env[envelope::release])) {
                isLegalY = false;
                illegalDown = true;
            }

            if (mousePos.hasLowerXThan(*env[envelope::attack])) {
                isLegalX = false;
            }

            if (mousePos.hasHigherXThan(*env[envelope::sustain])) {
                isLegalX = false;
                illegalRight = true;
            }
            break;

        case sustain:

            if (mousePos.hasLowerYThan(*env[envelope::attack])) {
                isLegalY = false;
            }

            if (mousePos.hasHigherYThan(*env[envelope::release])) {
                isLegalY = false;
                illegalDown = true;
            }

            if (mousePos.hasLowerXThan(*env[envelope::decay])) {
                isLegalX = false;
            }
            if(! isForMatrix){
                if (mousePos.hasHigherXThan(*env[envelope::release])) {
                    isLegalX = false;
                    illegalRight = true;
                }
            }


            break;

        case release:
            isLegalY = false; // so that we don't change the y of the release
            if (!isForMatrix) {
                if (mousePos.hasLowerXThan(*env[envelope::sustain])) {
                    isLegalX = false;
                }
            }
            if (mousePos.getX() > width) {
                isLegalX = false;
                illegalRight = true;
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
            case envelope::attack:
                if (illegalRight) {
                    currentPoint->setX(env[envelope::decay]->getX());
                }
                else {
                    currentPoint->setX(0);
                }
                break;
            case envelope::decay:
                if (illegalRight) {
                    currentPoint->setX(env[envelope::sustain]->getX());
                }
                else {
                    currentPoint->setX(env[envelope::attack]->getX());
                }
                break;
            case envelope::sustain: 
                if (illegalRight) {
                    currentPoint->setX(env[envelope::release]->getX());
                }
                else {
                    currentPoint->setX(env[envelope::decay]->getX());
                }
                break;
            case envelope::release:
                if (illegalRight) {
                    currentPoint->setX(width);
                }
                else {
                    currentPoint->setX(env[envelope::sustain]->getX());
                }
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
        else {
            switch (currentEnv)
            {
            case envelope::attack:
                if (illegalDown) {
                    currentPoint->setY(env[envelope::decay]->getY());
                }
                else {
                    currentPoint->setY(0);
                }
                break;
            case envelope::decay:
                if (illegalDown) {
                    currentPoint->setY(env[envelope::release]->getY());
                }
                else {
                    currentPoint->setY(env[envelope::attack]->getY());
                }
                env[envelope::sustain]->setY(currentPoint->getY()); //in both cases we have to update the value of the sustain
                break;
            case envelope::sustain:
                if (illegalDown) {
                    currentPoint->setY(env[envelope::release]->getY());
                }
                else {
                    currentPoint->setY(env[envelope::attack]->getY());
                }
                env[envelope::decay]->setY(currentPoint->getY()); //in both cases we have to update the value of the decay
                break;

            default:
                break;
            }
        }

        //sets all envelope times and values
        switch (currentEnv)
        {
        case envelope::attack: 
            attackTime = computeAttackTime();
            decayTime = computeDecayTime();
            attackValue = computeAttackValue();
            break;
        case envelope::decay:
            decayTime = computeDecayTime();
            sustainTime = computeSustainTime();
            decayValue = computeDecayValue();
            sustainValue = decayValue;
            break;
        case envelope::sustain:
            sustainTime = computeSustainTime();
            releaseTime = computeReleaseTime();
            sustainValue = computeSustainValue();
            decayValue = sustainValue;
            break;
        case envelope::release:
            releaseTime = computeReleaseTime();
            releaseValue = computeReleaseValue();
            break;
        default:
            break;
        }

        sendData(); // sends the data to the server
   
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

void EnvelopeGui::sendData()
{
    //se invece vuole un messaggio solo per il movimento di un singolo punto
    switch (currentEnv)
    {
    case envelope::attack: sender->send(sender->getSocketName() << "/Attack", id, attackValue, attackTime , decayTime);
        break;
    case envelope::decay: sender->send(sender->getSocketName() << "/Decay", id, decayValue, decayTime, sustainTime);
        break;
    case envelope::sustain: sender->send(sender->getSocketName() << "/Sustain", id, sustainValue, sustainTime, releaseTime );
        break;
    case envelope::release: sender->send(sender->getSocketName() << "/Release", id, releaseValue, releaseTime);
        break;
    default:
        break;
    }
}

void EnvelopeGui::sendAllData()
{
    sender->send(sender->getSocketName() << "/Attack", id, attackValue, attackTime, decayTime);
    sender->send(sender->getSocketName() << "/Decay", id, decayValue, decayTime, sustainTime);
    sender->send(sender->getSocketName() << "/Sustain", id, sustainValue, sustainTime, releaseTime);
    sender->send(sender->getSocketName() << "/Release", id, releaseValue, releaseTime);
}

float EnvelopeGui::computeAttackTime()
{
    float currentTime = env[envelope::attack]->getX();
    return Converter::map(currentTime, 0, width, 0, 4);
}

float EnvelopeGui::computeAttackValue()
{
    float currentLev = height - env[envelope::attack]->getY();
    return Converter::map(currentLev, 0,height, 0, 1);
}

float EnvelopeGui::computeDecayTime()
{
    float currentTime = env[envelope::decay]->getX() - env[envelope::attack]->getX();
    return Converter::map(currentTime, 0, width, 0, 4);
}

float EnvelopeGui::computeDecayValue()
{
    float currentLev = height - env[envelope::decay]->getY();
    return Converter::map(currentLev, 0, height, 0, 1);
}

float EnvelopeGui::computeSustainTime()
{
    float currentTime = env[envelope::sustain]->getX() - env[envelope::decay]->getX();
    return  Converter::map(currentTime, 0, width, 0, 20);
}

float EnvelopeGui::computeSustainValue()
{
    float currentLev = height - env[envelope::sustain]->getY();
    return Converter::map(currentLev, 0, height, 0, 1);
}

float EnvelopeGui::computeReleaseTime()
{
    float currentTime = env[envelope::release]->getX() - env[envelope::sustain]->getX();
    if (!isForMatrix)
        return Converter::map(currentTime, 0, width, 0, 8);
    else 
        return Converter::map(currentTime, -width, width, -10, 10);
}

float EnvelopeGui::computeReleaseValue()
{
    float currentLev = height - env[envelope::release]->getY();
    return Converter::map(currentLev, 0, height, 0, 1);
}

void EnvelopeGui::computeValuesAndTimes()
{
    attackTime = computeAttackTime();
    decayTime = computeDecayTime();
    sustainTime = computeSustainTime();
    releaseTime = computeReleaseTime();
    attackValue = computeAttackValue();
    decayValue = computeDecayValue();
    sustainValue = computeSustainValue();
    releaseValue = computeReleaseValue();
}


