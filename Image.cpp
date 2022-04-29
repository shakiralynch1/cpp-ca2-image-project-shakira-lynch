#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <valarray>
#include "Image.h"



bool Image::load(string filename)
{

    std::ifstream ifs;
    ifs.open(filename, std::ios::binary);
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
    if (w == 0 || h == 0) { fprintf(stderr, "Can't save an empty image\n"); return false; }
    std::ofstream ofs;
    try {
        ofs.open(filename, std::ios::binary);
        if (ofs.fail()) throw("Can't open output file");
        ofs << "P6\n" << w << " " << h << "\n255\n";
        unsigned char r, g, b;

        for (int i = 0; i < w * h; ++i) {
            r = (pixels[i].r);
            g = (pixels[i].g);
            b = (pixels[i].b);
            ofs << r << g << b;
        }
        ofs.close();
    }
    catch (const char *err) {
        fprintf(stderr, "%s\n", err);
        ofs.close();
        return false;
    }
    return true;

}



void Image::filterRed()
{
    for(int c = 0; c< w*h; ++c)
    {
        this->pixels[c].g = 0;
        this->pixels[c].b = 0;

    }

}
void Image::filterGreen()
{
    for(int c = 0; c< w*h; ++c)
    {
        this->pixels[c].r = 0;
        this->pixels[c].b = 0;

    }


}
void Image::filterBlue()
{
    for(int c = 0; c< w*h; ++c)
    {
        this->pixels[c].r = 0;
        this->pixels[c].g = 0;

    }


}
void Image::greyScale()
{

    for(int c = 0; c< w*h; c++)
    {

        int greyscale = (this->pixels[c].r  +this->pixels[c].g) /3;

        this->pixels[c].b = greyscale;
        this->pixels[c].g = greyscale;
        this->pixels[c].r = greyscale;

    }



}
void Image::flipHorizontal()
{

    int pixels[3];
    unsigned int tempPixel;
    unsigned int tempPixel1;


    for(int y= 0; y < h; y++)
    {
        for(int x =0; x <w/2; x++)
        {
            tempPixel = x + y * w;
            tempPixel1 = (w - 1 - x) + y * w;

            pixels[0] = this->pixels[tempPixel].r;
            pixels[1] = this->pixels[tempPixel].g;
            pixels[2] = this->pixels[tempPixel].b;

            this->pixels[tempPixel].r = this->pixels[tempPixel1].r;
            this->pixels[tempPixel].g = this->pixels[tempPixel1].g;
            this->pixels[tempPixel].b = this->pixels[tempPixel1].b;

            this->pixels[tempPixel1].r = pixels[0];
            this->pixels[tempPixel1].g = pixels[1];
            this->pixels[tempPixel1].b = pixels[2];
        }
    }

}
void Image::flipVertically()
{
    int pixels[3];
    unsigned int tempPixel;
    unsigned int tempPixel1;


    for(int x= 0; x < w; x++)
    {
        for(int y =0; y <h/2; y++)
        {
            tempPixel = x + y * w;
            tempPixel1 = x +  (h - 1 - y)  * w;


            pixels[0] = this->pixels[tempPixel].r;
            pixels[1] = this->pixels[tempPixel].g;
            pixels[2] = this->pixels[tempPixel].b;

            this->pixels[tempPixel].r = this->pixels[tempPixel1].r;
            this->pixels[tempPixel].g = this->pixels[tempPixel1].g;
            this->pixels[tempPixel].b = this->pixels[tempPixel1].b;

            this->pixels[tempPixel1].r = pixels[0];
            this->pixels[tempPixel1].g = pixels[1];
            this->pixels[tempPixel1].b = pixels[2];
        }
    }


}
//inverting image
void Image::AdditionalFunction2()
{
    for(int c = 0; c< w*h; c++)
    {


        this->pixels[c].b = 255-this->pixels[c].b ;
        this->pixels[c].g = 255-this->pixels[c].g;
        this->pixels[c].r = 255-this->pixels[c].r;

    }

}
void Image::AdditionalFunction3()
{
    for(int c = 0; c< w*h; c++)
    {
        if (this->pixels[c].b > 0.7) this->pixels[c].b *= 3;
        if (this->pixels[c].g> 0.7) this->pixels[c].g *= 3;
        if (this->pixels[c].r > 0.7) this->pixels[c].r *= 3;
    }

}
void Image::AdditionalFunction1()
{
   Image temp(h, w);

    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) {
            unsigned int dest = (c * h) + (h - r - 1);


            temp.pixels[dest] = pixels[(r * w) + c];

        }
    }
    *this = temp;

}
void Image::AdvancedFeature() {

    int pixels[3];
    unsigned int tempPixel;
    unsigned int tempPixel1;

    for(int c = 0; c< w*h; c++)
    {
        if (this->pixels[c].b > 0.7) this->pixels[c].b *= 3;
        if (this->pixels[c].g> 0.7) this->pixels[c].g *= 3;
        if (this->pixels[c].r > 0.7) this->pixels[c].r *= 3;
    }


    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h / 4; y++) {
            tempPixel = x + y * w;
            tempPixel1 = x + (h - 2 - y) * w;


            float gamma=2/4.4f;




            pixels[0] = this->pixels[tempPixel].r;
            pixels[1] = this->pixels[tempPixel].g;
            pixels[2] = this->pixels[tempPixel].b;

            this->pixels[tempPixel].r = this->pixels[tempPixel1].r;
            this->pixels[tempPixel].g = this->pixels[tempPixel1].g;
            this->pixels[tempPixel].b = this->pixels[tempPixel1].b;

            this->pixels[tempPixel1].r = pixels[0];
            this->pixels[tempPixel1].g = pixels[1];
            this->pixels[tempPixel1].b = pixels[2];


        }
    }

}
void Image::Gamma()
{
    for(int c = 0; c< w*h; c++)
    {
        float gamma=1/2.2f;

        pixels[c].r = pow(pixels[c].r /255.0f, gamma) * 255;
        pixels[c].g = pow(pixels[c].g /255.0f, gamma) * 255;
        pixels[c].b = pow(pixels[c].b /255.0f, gamma) * 255;
    }
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