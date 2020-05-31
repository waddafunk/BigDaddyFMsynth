/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   min_switch_png;
    const int            min_switch_pngSize = 682;

    extern const char*   Carbon_png;
    const int            Carbon_pngSize = 310955;

    extern const char*   Brotherline_ttf;
    const int            Brotherline_ttfSize = 300196;

    extern const char*   AsgaltRegular_ttf;
    const int            AsgaltRegular_ttfSize = 10656;

    extern const char*   neuropolxrg_ttf;
    const int            neuropolxrg_ttfSize = 149752;

    extern const char*   Quicksand_Bold_otf;
    const int            Quicksand_Bold_otfSize = 37812;

    extern const char*   spaceage_ttf;
    const int            spaceage_ttfSize = 26736;

    extern const char*   UrbanBrushZone_ttf;
    const int            UrbanBrushZone_ttfSize = 84828;

    extern const char*   LaksOner_ttf;
    const int            LaksOner_ttfSize = 85016;

    extern const char*   steelfish_ttf;
    const int            steelfish_ttfSize = 152452;

    extern const char*   neuropol_ttf;
    const int            neuropol_ttfSize = 91532;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 11;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
