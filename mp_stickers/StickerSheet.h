/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

 class StickerSheet{
    public:
        Image** img_array;
        unsigned * x_coord;
        unsigned * y_coord;
        Image base_picture;
        unsigned max_;
        unsigned stickerCount;
        
        StickerSheet(const Image &picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet &other); 
        const StickerSheet & operator=(const StickerSheet &other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image *getSticker(unsigned index) const;
        Image render() const;
        void clear(); //helper:memory cleanup
 };
