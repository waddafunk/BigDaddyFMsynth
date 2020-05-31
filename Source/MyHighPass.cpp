/*
  ==============================================================================

    MyHighPass.cpp
    Created: 27 May 2020 8:52:08pm
    Author:  jacop

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MyHighPass.h"

//==============================================================================
MyHighPass::MyHighPass()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

MyHighPass::MyHighPass(int x, int y, int w, int h)
{
    xPos = x;
    yPos = y;
    this->width = w;
    this->height = h;
    setGain(0.5);
    setResonance(0);
    setCutoffFromHz(400);
    type = filterType::highpass;
}

MyHighPass::~MyHighPass()
{
}


/*
void MyHighPass::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(getLookAndFeel().findColour(Slider::thumbColourId));

    Path filterPath;
    Point<float> cutX(cutoff, (float)-resonance * 2.0f * height * 0.7f + height * 0.5f), 
        preCutX(cutX.getX() - width / 50, height / 2.0f), 
        start(preCutX.getX() * 90 / 100, (float)height),
        endLinear(width, (float)(height / 2)),
        endp(cutX.getX() + width / 5, (float)height / 2), 
        smoothingPoint(endp.getX() - width / 10, endp.getY() * 8 / 10),
        smoothingPoint2(smoothingPoint.getX() + width / 80, smoothingPoint.getY() * 120 / 100),
        smoothingPoint3(smoothingPoint.getX() + width / 40 + 10, height / 2);
    
    if (endp.getX() > width)
        endp.setX(width);
    
    filterPath.startNewSubPath(start);  // if this is the first point, start a new path..
    filterPath.cubicTo(preCutX, cutX, smoothingPoint);
    filterPath.quadraticTo(smoothingPoint2, endp);

    filterPath.lineTo(endLinear);


    // draw an outline around the path that we have created
    g.strokePath(filterPath, PathStrokeType(2.0f)); // [4]
    g.fillEllipse(cutX.getX()-5, height * (1.0f - resonance) - 5.0f, 10.0f, 10.0f);

    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
}

*/


void MyHighPass::paint(Graphics& g)
{


    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(getLookAndFeel().findColour(Slider::thumbColourId));

    Path filterPath;
    Point<float> cutPoint(cutoff, height - Converter::map(gain, 0, 1, 0, height));

    //if resonance is 0 then 45 degrees .. else idk
    Point <float> startingPoint(computeZeroCrossingPointX(cutPoint,type), height);
    Point <float> preCut(cutPoint.getX() - resonance * (width/20) * gain,cutPoint.getY() - (resonance / 4 * height)* gain);
    Point <float> resCut(cutPoint.getX(), cutPoint.getY() - (resonance * height/2) * gain);
    Point <float> posCut(cutPoint.getX() + (width - cutPoint.getX()) /2 * (1 - resonance * gain), cutPoint.getY() - resonance / 4 * height * gain);
    Point <float> endPoint(width, cutPoint.getY());

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

void MyHighPass::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}


