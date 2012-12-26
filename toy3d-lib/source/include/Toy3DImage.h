
#ifndef _TOY3D_IMAGE_H
#define _TOY3D_IMAGE_H

#include "Toy3DCommon.h"


TOY3D_BEGIN_NAMESPACE

//bytes per pixel
#define BPP_3 3
#define BPP_4 4

//suffix of image file
#define SEPERATER  '.'
#define TGA_SUFFIX ".tga"
#define BMP_SUFFIX ".bmp"


    class Image
    {
    public:
        //Uint mType;         // may be unused
        Uint mWidth;        // width of image
        Uint mHeight;       // height of image
        Uint mBpp;          // bytes per pixel
        char *mImageData;   // image data

    public:
        Image();
        ~Image();

        virtual Bool decode( const char* fileName ) = 0;
    };


//////////////////////////////////////////////////////////////////////////
//TGA
#define TGA_FILE_HEAD_LEN 12
static Uchar mUTGAcompare[TGA_FILE_HEAD_LEN] = {0,0,2, 0,0,0,0,0,0,0,0,0}; /* Uncompressed TGA Header */
static Uchar mCTGAcompare[TGA_FILE_HEAD_LEN] = {0,0,10,0,0,0,0,0,0,0,0,0}; /* Compressed TGA Header */

    class TGAImage : public Image
    {
    private:
        Uchar mTgaHeader[TGA_FILE_HEAD_LEN];     /* TGA File Header */
        Uchar mHeader6[6];                       /* First 6 Useful Bytes From The Header */

        Bool LoadUncompressedTGA(FILE *fTGA);    /* Load an Uncompressed file */
        Bool LoadCompressedTGA(FILE *fTGA);      /* Load a Compressed file */

    public:
        TGAImage();
        ~TGAImage();

        Bool decode( const char* fileName );

    };


//////////////////////////////////////////////////////////////////////////
//BMP
    class BMPImage : public Image
    {
    public:
        Bool decode( const char* fileName );
    };


TOY3D_END_NAMESPACE

#endif
