/*
  ==============================================================================

    MyLowPass.cpp
    Created: 27 May 2020 8:51:40pm
    Author:  jacop

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MyLowPass.h"
#include "Coordinate.h"

//==============================================================================
MyLowPass::MyLowPass()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

MyLowPass::MyLowPass(int x, int y, int w, int h)
{
    xPos = x;
    yPos = y;
    this->width = w;
    this->height = h;
    setGain(0.5);
    setResonance(0.4);
    setCutoffFromHz(6000);
    type = filterType::lowpass;
    cutoffSendValue = convertExp(cutoff);
    sender = new MySender(tSection::filter);
    sendAllFilterData();
    setMyState(true);
    pointSize = 6;
}

MyLowPass::~MyLowPass()
{
   // delete sender;
}



// --------------------------PAINT COLLAB 1-----------------------------------------------

void MyLowPass::paint(Graphics& g) {

    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(Colours::grey.darker(0.8));
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    Path filterPath;
    Point<float> cutPoint(cutoff, height - Converter::map(gain, 0, 1, 0, height));

    //if resonance is 0 then 45 degrees .. else idk
    //Point <float> startingPoint(computeStartingPointX(cutPoint), height);
    Point <float> startingPoint(0, cutPoint.getY());
    Point <float> preCut(cutPoint.getX() - (cutPoint.getX()/2)*resonance, cutPoint.getY());
    Point <float> resCut(cutPoint.getX(), cutPoint.getY()  - (resonance * height / 2) );
    Point <float> preCut2(cutPoint.getX() - (width / 40), resCut.getY() *(1 + resonance * 0.3));
    Point <float> endQuadratic(preCut.getX() + (preCut2.getX() - preCut.getX()) * 2 / 3 , preCut.getY() - height * resonance / 4);
    Point <float> posCut(cutPoint.getX() + (width / 20), cutPoint.getY() + (1 - resonance)*height/10 );
    Point <float> endPoint(computeZeroCrossingPointX(cutPoint, type), height);

    filterPath.startNewSubPath(startingPoint);
    filterPath.quadraticTo(preCut,endQuadratic);
    filterPath.cubicTo(preCut2, resCut, endPoint);
    //filterPath.lineTo(endPoint);
 
    g.setColour(getLookAndFeel().findColour(Slider::thumbColourId));

    g.strokePath(filterPath, PathStrokeType(2.0f));

    g.fillEllipse(cutPoint.getX() - pointSize / 2, height * (1.0f - gain) - pointSize / 2, pointSize, pointSize);

    Point<float> end(0, height);
    filterPath.lineTo(end);
    filterPath.lineTo(startingPoint);

    ColourGradient* gradient = new ColourGradient(Colours::grey.brighter(0.2), cutPoint.getX()+100, cutPoint.getY(), Colours::aliceblue, -150+cutPoint.getX(), 50+cutPoint.getY(), false);
    gradient->clearColours();
    gradient->addColour(0, Colours::pink.withMultipliedAlpha(0.4));
    gradient->addColour(0.2, Colours::cadetblue.darker(0.4).withMultipliedAlpha(0.4));
    gradient->addColour(0.5, Colours::deepskyblue.withMultipliedAlpha(0.4));
    g.setGradientFill(*gradient);
    g.fillPath(filterPath);

    delete gradient;
}


void MyLowPass::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}




