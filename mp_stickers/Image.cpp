#include "Image.h"
using namespace cs225;


void Image::lighten(){
    for (unsigned int x = 0; x < this->width(); x++){
        for (unsigned int y = 0; y < this->height(); y++){
            HSLAPixel & p = this->getPixel(x, y);
            if (p.l + 0.1 >= 1.0)
                p.l = 1.0;
            else
                p.l += 0.1;
        }
    }
}

void Image::lighten(double amount){
    for (unsigned int x = 0; x < this->width(); x++){
        for (unsigned int y = 0; y < this->height(); y++){
            HSLAPixel & p = this->getPixel(x, y);
            if (p.l + amount >= 1.0)
                p.l = 1.0;
            else
                p.l += amount;
        }
    }
}

void Image::darken(){
    for (unsigned int x = 0; x < this->width(); x++){
        for (unsigned int y = 0; y < this->height(); y++){
            HSLAPixel & p = this->getPixel(x, y);
            if (p.l - 0.1 <= 0)
                p.l = 0;
            else
                p.l -= 0.1;
        }
    }
}

void Image::darken(double amount){
    for (unsigned int x = 0; x < this->width(); x++){
        for (unsigned int y = 0; y < this->height(); y++){
            HSLAPixel & p = this->getPixel(x, y);
            if (p.l - amount <= 0)
                p.l = 0;
            else
                p.l -= amount;
        }
    }
}

void Image::saturate(){
    for (unsigned int x = 0; x < this->width(); x++){
        for (unsigned int y = 0; y < this->height(); y++){
            HSLAPixel & p = this->getPixel(x, y);
            if (p.s + 0.1 >= 1.0)
                p.s = 1.0;
            else
                p.s += 0.1;
        }
    }
}

void Image::saturate(double amount){
    for (unsigned int x = 0; x < this->width(); x++){
        for (unsigned int y = 0; y < this->height(); y++){
            HSLAPixel & p = this->getPixel(x, y);
            if (p.s + amount >= 1.0)
                p.s = 1.0;
            else
                p.s += amount;
        }
    }
}

void Image::desaturate(){
    for (unsigned int x = 0; x < this->width(); x++){
        for (unsigned int y = 0; y < this->height(); y++){
            HSLAPixel & p = this->getPixel(x, y);
            if (p.s - 0.1 <= 0)
                p.s = 0;
            else
                p.s -= 0.1;
        }
    }
}

void Image::desaturate(double amount){
    for (unsigned int x = 0; x < this->width(); x++){
        for (unsigned int y = 0; y < this->height(); y++){
            HSLAPixel & p = this->getPixel(x, y);
            if (p.s - amount <= 0)
                p.s = 0;
            else
                p.s -= amount;
        }
    }
}

void Image::grayscale(){
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.s = 0;
        }
    }
}

void Image::rotateColor(double degrees){
    for (unsigned int x = 0; x < this->width(); x++){
        for (unsigned int y = 0; y < this->height(); y++){
            HSLAPixel & p = this->getPixel(x, y);
            double hue = p.h + degrees;
            if (hue > 360){
                hue -= 360;
            }   
            if (hue + degrees < 0){
                hue += 360;
            }
            p.h = hue;
        }
    }
}

void Image::illinify(){
    for (unsigned x=0; x < this->width(); x++){
        for(unsigned y=0; y < this->height(); y++){
            HSLAPixel & pixel = this->getPixel(x, y);
            if(pixel.h >= 293.5 || pixel.h <= 113.5)
            {
                pixel.h = 11; 
            }
            else
            {
                pixel.h = 216;
            }
        }
    }
}

void Image::scale(double factor){
    int w = (this->width()*factor);
    int h = (this->height()*factor);
    Image *result = new Image();
    *result = *this;
    resize(w,h);
    for (int x=0; x < w; x++){
        for(int y=0; y < h; y++){
            HSLAPixel & p_ = getPixel(x,y);
            HSLAPixel & p = result->getPixel(x / factor, y / factor);
            p_ = p;
        }
    }
    delete result;

}
void Image::scale(unsigned w, unsigned h){
    double x_factor = (double)w / this->width();
    double y_factor = (double)h / this->height();
    if(x_factor > y_factor){
        scale(y_factor);
    }
    else
    {
        scale(x_factor);
    }
}