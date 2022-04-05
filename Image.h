//
// Created by floodd on 22/03/2022.
//

// Created by floodd on 11/02/2022.
//


#ifndef SDLTEST_TGA_FILEHANDLER_H
#define SDLTEST_TGA_FILEHANDLER_H
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
struct Rgb
{
    Rgb() : r(1), g(1), b(1)  {}
    Rgb(unsigned char rr) : r(rr), g(rr), b(rr) {}
    Rgb(unsigned char rr, unsigned char gg,unsigned char bb) : r(rr), g(gg), b(bb) {}
    unsigned char r, g, b;
};

class Image {



    Image(const unsigned int _w, const unsigned int _h) :
            w(_w), h(_h), pixels(nullptr)
    {
        pixels = new Rgb[w * h];

    }

    unsigned int w, h;
    Rgb *pixels;
public:
    Image() : w(300), h(400){pixels = new Rgb[w * h];}


    bool savePPM(string filename);
    bool load(string filename);
    bool loadRaw(string filename);
    void filterRed();
    void filterGreen();
    void filterBlue();
    void greyScale();
    void flipHorizontal();
    void flipVertically();
    void AdditionalFunction1();
    void AdditionalFunction2();
    void AdditionalFunction3();

    /*Functions used in the GUI - DO NOT MODIFY */
    Rgb* getImage();
    int getWidth();
    int getHeight();
    ~Image() { if (pixels != nullptr) delete [] pixels; }

    Image readPPM(const char *filename)
    {
        std::ifstream ifs;
        ifs.open(filename, std::ios::binary);
        // need to spec. binary mode for Windows users
        Image src;
        try {
            if (ifs.fail()) {
                throw("Can't open input file");
            }
            std::string header;
            int w, h, b;
            ifs >> header;
            if (strcmp(header.c_str(), "P6") != 0) throw("Can't read input file");
            ifs >> w >> h >> b;
            src.w = w;
            src.h = h;
            src.pixels = new Rgb[w * h]; // this is throw an exception if bad_alloc
            ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data
            unsigned char pix[3]; // read each pixel one by one and convert bytes to floats
            for (int i = 0; i < w * h; ++i) {
                ifs.read(reinterpret_cast<char *>(pix), 3);
                src.pixels[i].r = pix[0] / 255.f;
                src.pixels[i].g = pix[1] / 255.f;
                src.pixels[i].b = pix[2] / 255.f;
            }
            ifs.close();
        }
        catch (const char *err) {
            fprintf(stderr, "%s\n", err);
            ifs.close();
        }

        return src;
    }

};




#endif //SDLTEST_TGA_FILEHANDLER_H

