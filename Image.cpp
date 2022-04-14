#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Image.h"



bool Image::load(string filename)
{

    std::ifstream ifs;
    ifs.open(filename, std::ios::binary);
    // need to spec. binary mode for Windows users
    try {
        if (ifs.fail())
        {
            throw("Can't open input file");
        }
        std::string header;
        int w, h, b;
        ifs >> header;
        if (strcmp(header.c_str(), "P6") != 0) throw("Can't read input file");
        ifs >> w >> h >> b;
        this->w = w;
        this->h = h;
        this->pixels = new Rgb[w * h]; // this is throw an exception if bad_alloc
        ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data
        unsigned char pix[3]; // read each pixel one by one and convert bytes to floats
        for (int i = 0; i < w * h; ++i)
        {
            ifs.read(reinterpret_cast<char *>(pix), 3);
            this->pixels[i].r = pix[0] ;
            this->pixels[i].g = pix[1] ;
            this->pixels[i].b = pix[2] ;
        }
        ifs.close();
    }
    catch (const char *err)
    {
        fprintf(stderr, "%s\n", err);
        ifs.close();
        return false;
    }

    return true;

}
bool Image::loadRaw(string filename)
{
    return false;
}
bool Image::savePPM(string filename)
{

    if (this->w == 0 || this->h == 0) {return false; }
    std::ofstream ofs;
    try {
        ofs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users
        if (ofs.fail()) throw("Can't open output file");
        ofs << "P6\n" << this->w << " " << this->h << "\n255\n";
        unsigned char r, g, b;
        // loop over each pixel in the image, clamp and convert to byte format
        for (int i = 0; i < this->w * this->h; ++i) {
            this->pixels[i].r;
            this->pixels[i].g;
            this->pixels[i].b;
            ofs << r << g << b;
        }
        ofs.close();
    }
    catch (const char *err) {
        fprintf(stderr, "%s\n", err);
        ofs.close();
    }
    return false;
}


void Image::filterRed()
{
    for(int c = 0; c< w*h; ++c)
    {
        this->pixels[c].r = 1;
        this->pixels[c].g = 0;
        this->pixels[c].b = 0;

    }

}
void Image::filterGreen()
{
    for(int c = 0; c< w*h; ++c)
    {
        this->pixels[c].r = 0;
        this->pixels[c].g = 1;
        this->pixels[c].b = 0;

    }


}
void Image::filterBlue()
{
    for(int c = 0; c< w*h; ++c)
    {
        this->pixels[c].r = 0;
        this->pixels[c].g = 0;
        this->pixels[c].b = 1;

    }


}
void Image::greyScale()
{

    for(int c = 0; c< w*h; ++c)
    {
        this->pixels[c].r = 0.5;
        this->pixels[c].g = 0.5;
        this->pixels[c].b = 0.5;

    }




}
void Image::flipHorizontal()
{


}
void Image::flipVertically()
{


}
void Image::AdditionalFunction2()
{

}
void Image::AdditionalFunction3()
{

}
void Image::AdditionalFunction1()
{

}

/* Functions used by the GUI - DO NOT MODIFY */
int Image::getWidth()
{
    return w;
}

int Image::getHeight()
{
    return h;
}

Rgb* Image::getImage()
{
    return pixels;
}