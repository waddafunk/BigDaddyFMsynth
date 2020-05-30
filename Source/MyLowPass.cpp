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
    setResonance(0);
    setCutoffFromHz(4000);
    type = filterType::lowpass;
}

MyLowPass::~MyLowPass()
{
}



// --------------------------PAINT COLLAB 1-----------------------------------------------

void MyLowPass::paint(Graphics& g) {

    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(getLookAndFeel().findColour(Slider::thumbColourId));

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
    g.strokePath(filterPath, PathStrokeType(1.0f)); // [4]

    // draw an outline around the path that we have created
    g.fillEllipse(cutPoint.getX() - 5, height * (1.0f - gain) - 5.0f, 10.0f, 10.0f);


    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

}





void MyLowPass::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}




