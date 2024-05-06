/*
Creates a .bmp image from scratch.
Creates a copy of a .bmp image.
*/

#include "image.h"

int main() {

    /* Image Creation */

    const int width = 16;
    const int height = 12;

    Image image(width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            image.SetColor(Color((float)x / (float)width, 1.0f - ((float)x / (float)width), (float)y / (float)height), x, y);
        }
    }

    image.Export("image.bmp");


    /* Image Reading */

    Image copy(0, 0);

    copy.Read("image2copy.bmp");

    //Printing
    copy.ReadAndPrintHex("image2copy.bmp");

    copy.Export("copy.bmp");

    /* Image to Hex */

    copy.SaveHexToFile("image2copy.bmp", "simics_buffer_fill.txt");

}

