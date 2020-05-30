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


/*
void MyLowPass::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(getLookAndFeel().findColour(Slider::thumbColourId));

    Path filterPath;
    Point<float> start((float)0, (float)(height / 2)), cutX(getCutoff(), (float)-getResonance() * 2.0f * height * 0.7f + height * 0.5f),
        preCutX(cutX.getX() * 99.0f / 100.0f, height / 2.0f),
        endLinear(preCutX.getX() * 95.0f / 100.0f, (float)(height / 2)), endp(cutX.getX() + width / 10, (float)height);

    if (endp.getX() > width)
        endp.setX(width);

    filterPath.startNewSubPath(start);  // if this is the first point, start a new path..
    filterPath.lineTo(endLinear);
    filterPath.cubicTo(preCutX, cutX, endp);


    // draw an outline around the path that we have created
    g.strokePath(filterPath, PathStrokeType(2.0f)); // [4]
    g.fillEllipse(cutX.getX(), height * (1.0f - getResonance()) - 10.0f, 10.0f, 10.0f);

    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
}
*/

void MyLowPass::paint(Graphics& g) {

    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(getLookAndFeel().findColour(Slider::thumbColourId));

    Path filterPath;
    Point<float> cutPoint(cutoff, height - Converter::map(gain, 0, 1, 0, height));

    //if resonance is 0 then 45 degrees .. else idk
    //Point <float> startingPoint(computeStartingPointX(cutPoint), height);
    Point <float> startingPoint(0, cutPoint.getY());
    Point <float> preCut(cutPoint.getX() - (width - cutPoint.getX()) / 2 * (1 - resonance * gain), cutPoint.getY() - resonance / 4 * height * gain);
    Point <float> resCut(cutPoint.getX(), cutPoint.getY() - (resonance * height / 2) * gain);
    Point <float> posCut(cutPoint.getX() + resonance * (width / 20) * gain, cutPoint.getY() - (resonance / 4 * height) * gain);
    Point <float> endPoint(computeZeroCrossingPointX(cutPoint,type), height);

    filterPath.startNewSubPath(startingPoint);
    filterPath.quadraticTo(preCut, resCut);
    filterPath.quadraticTo(posCut, endPoint);
    //filterPath.lineTo(cutPoint);
    //filterPath.lineTo(width, cutPoint.getY());

    // draw an outline around the path that we have created
    g.strokePath(filterPath, PathStrokeType(2.0f)); // [4]
    g.fillEllipse(cutPoint.getX() - 5, height * (1.0f - gain) - 5.0f, 10.0f, 10.0f);

    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

}


void MyLowPass::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}



