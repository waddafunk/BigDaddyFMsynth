#include <JuceHeader.h>
#include "ButtonLookAndFeel.h"



//==============================================================================
ButtonLookAndFeel::ButtonLookAndFeel()
{
    img1 = ImageCache::getFromMemory(BinaryData::switch_toggle_png, BinaryData::switch_toggle_pngSize);
}

//==============================================================================


void ButtonLookAndFeel::drawToggleButton(Graphics &g, ToggleButton &button,
    bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    /// still to do 
}
