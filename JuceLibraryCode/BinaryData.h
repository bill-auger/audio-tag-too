/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   accessoriestexteditor_png;
    const int            accessoriestexteditor_pngSize = 1029;

    extern const char*   audioxgeneric_png;
    const int            audioxgeneric_pngSize = 2060;

    extern const char*   listadd_png;
    const int            listadd_pngSize = 528;

    extern const char*   mediaplaybackstart_png;
    const int            mediaplaybackstart_pngSize = 1170;

    extern const char*   processstop_png;
    const int            processstop_pngSize = 1399;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 5;

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
