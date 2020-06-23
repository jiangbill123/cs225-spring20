#include "Image.h"
#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max){
    max_ = max;
    img_array = new Image* [max];
    base_picture = picture;
    x_coord = new unsigned[max];
    y_coord = new unsigned[max];
    //initialize array of pointers
    for (unsigned i = 0; i < max; i++){
        img_array[i] = NULL;
    }
    stickerCount = 0;

}

StickerSheet::~StickerSheet(){
    clear();//helper
}

//clean up memory
void StickerSheet::clear(){
    delete[] x_coord;
    x_coord = NULL;
    delete[] y_coord;
    y_coord = NULL;
    for(unsigned i = 0; i < stickerCount; i++){
        delete img_array[i];
        img_array[i] = NULL;
    }
    delete[] img_array;
    img_array = NULL;
}

StickerSheet::StickerSheet(const StickerSheet &other){
    base_picture = other.base_picture;
    max_ = other.max_;
    stickerCount = other.stickerCount;
    img_array = new Image* [max_];
    for (unsigned i = 0; i<max_; i++){
        img_array[i] = NULL;
    }
    x_coord = new unsigned[max_];
    y_coord = new unsigned[max_];
    for (unsigned i = 0; i<stickerCount; i++){
        img_array[i] = new Image();
        x_coord[i] = other.x_coord[i];
        y_coord[i] = other.y_coord[i];
        *(img_array[i]) = *(other.img_array[i]);
    }
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
    if(stickerCount < max_){
        img_array[stickerCount] = new Image(sticker);
        x_coord[stickerCount] = x;
        y_coord[stickerCount] = y;
        stickerCount++;
        return int(stickerCount-1); //0 based index of img_array
    }
    return -1; //cannot add
}

void StickerSheet::changeMaxStickers(unsigned new_max){
    if (new_max == stickerCount) {return;}
    Image** new_images = new Image*[new_max];
    unsigned * new_x = new unsigned[new_max];
    unsigned * new_y= new unsigned[new_max];
    
    if (new_max < stickerCount){
        for (unsigned i = new_max; i < stickerCount; i++){
            delete img_array[i];
            img_array[i]=NULL;
        }
        stickerCount=new_max;
    }
    if (new_max > stickerCount){
        //copy first
        for (unsigned j = 0; j<stickerCount; j++){
            new_images[j]=img_array[j];
            new_x[j]=x_coord[j];
            new_y[j]=y_coord[j];
        }
        //delete old pointer arrays
        delete[] img_array;
        delete[] x_coord;
        delete[] y_coord;
        //resize
        img_array = new Image*[new_max];
        x_coord = new unsigned[new_max];
        y_coord = new unsigned[new_max];
        //paste
        for (unsigned k = 0; k<stickerCount; k++){
            img_array[k]=new_images[k];
            x_coord[k]=new_x[k];
            y_coord[k]=new_y[k];
        }
    }
    //update max
    max_ = new_max;
    //clean up memory
    delete[] new_images;
    delete[] new_x;
    delete[] new_y;

    
}

Image* StickerSheet::getSticker(unsigned index) const{
    if (index >= stickerCount)
        return NULL;
    return img_array[index];

}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other){
    clear();
    base_picture = other.base_picture;
    max_ = other.max_;
    stickerCount = other.stickerCount;
    img_array = new Image* [max_];
    for (unsigned i = 0; i<max_; i++){
        img_array[i] = NULL;
    }
    x_coord = new unsigned[max_];
    y_coord = new unsigned[max_];
    for (unsigned i = 0; i<stickerCount; i++){
        img_array[i] = new Image();
        x_coord[i] = other.x_coord[i];
        y_coord[i] = other.y_coord[i];
        *(img_array[i]) = *(other.img_array[i]);
    }

    return *this;
}

void StickerSheet::removeSticker(unsigned index){
    stickerCount -= 1;
    
    for (unsigned i = index; i<stickerCount; i++){
        *(img_array[i]) = *(img_array[i+1]);
        x_coord[i] = x_coord[i+1];
        y_coord[i] = y_coord[i+1];
    }
    delete img_array[stickerCount];
    img_array[stickerCount+1] = NULL;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if (index >= 0 && index < stickerCount){
        x_coord[index] = x;
        y_coord[index] = y;
        return true;
    }
    return false;
}

Image StickerSheet::render() const{
    Image result;
    result = base_picture;
    for (unsigned i = 0; i < stickerCount; i++){
        unsigned stickerWidth = img_array[i]->width();
        unsigned stickerheigt = img_array[i]->height();
        unsigned xpos = x_coord[i];
        unsigned ypos = y_coord[i];
        if ( stickerWidth + xpos > result.width()){
            result.resize(stickerWidth + xpos, result.height());//adjust width
        }
        if ( stickerheigt+ypos > result.height()){
            result.resize(result.width(), stickerheigt+ypos);//adjust height
        }
        //pixels
        for (unsigned x = xpos; x< xpos + stickerWidth; x++){
            for (unsigned y = ypos; y < ypos + stickerheigt; y++){
                //   xpos < x < xpos + stickerWidth ==> looping through stickerWidth
                HSLAPixel & presult = result.getPixel(x, y);
                HSLAPixel & psticker = img_array[i]->getPixel(x-xpos, y-ypos);
                if (psticker.a != 0) {presult = psticker;}
            }
        }
    }
    return result; 
}




