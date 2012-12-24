#include "Toy3DImage.h"

TOY3D_BEGIN_NAMESPACE


#define BitsPP_24 24
#define BitsPP_32 32

//////////////////////////////////////////////////////////////////////////
//Image
    Image::Image()
    {
        //mType   = 0;
        mWidth  = 0;
        mHeight = 0;
        mBpp    = 0;
        mImageData = 0;
    }

    Image::~Image()
    {
        FREEANDNULL(mImageData);
    }


//////////////////////////////////////////////////////////////////////////
//TgaImage

    TGAImage::TGAImage()
    {
    }

    TGAImage::~TGAImage()
    {
        ;
    }

    Bool TGAImage::decode( const char* fileName )
    {
        Bool rvb;
        FILE *fTGA;

        if(!fileName)
        {
            TOY3D_PRINT("Null pointer.", __FILE__, __LINE__ );
            return FALSE;
        }

        fTGA = fopen(fileName, "rb");
        if( !fTGA )
        {
            TOY3D_TIPS("could not open texture file.");
            return FALSE;
        }

        if( fread(mTgaHeader, sizeof(mTgaHeader), 1, fTGA) == 0 )
        {
            TOY3D_TIPS("could not read file header.");
            if(fTGA != NULL)
            {
                fclose(fTGA);
            }

            return FALSE;
        }
        
        if(memcmp(mUTGAcompare, &mTgaHeader, sizeof(mTgaHeader)) == 0)
        {
            rvb = LoadUncompressedTGA(fTGA);
        }
        else if(memcmp(mCTGAcompare, &mTgaHeader, sizeof(mTgaHeader)) == 0)
        {
            rvb = LoadCompressedTGA(fTGA);
        }
        else
        {
            TOY3D_TIPS("TGA file mustbe type 2 or type 10.\n");
            fclose(fTGA);
            return FALSE;
        }

        return rvb;
    }

    Bool TGAImage::LoadUncompressedTGA(FILE *fTGA)
    {
        Uint cswap;
        Uint bpp;        /* bits per pixel */
        Uint imageSize;  /* tga image size */

        /* Read TGA header */
        if(fread(mHeader6, sizeof(mHeader6), 1, fTGA) == 0)
        {
            TOY3D_TIPS("could not read info header from file.");
            if(fTGA != NULL)
            {
                fclose(fTGA);
            }
            return FALSE;
        }

        /* Determine The TGA width and height  (highbyte*256+lowbyte) */
        mWidth  = mHeader6[1] * 256 + mHeader6[0];  
        mHeight = mHeader6[3] * 256 + mHeader6[2];
        /* Determine the bits per pixel */
        bpp     = mHeader6[4];

        /* Make sure all information is valid */
        if( (mWidth <= 0) || (mHeight <= 0) || ((bpp != BitsPP_24) && (bpp !=BitsPP_32)) )
        {
            TOY3D_TIPS("invalid texture information.\n");
            if(fTGA != NULL)
            {
                fclose(fTGA);
            }

            return FALSE;
        }

        /* Compute Bpp and image size */
        mBpp = bpp/8;
        imageSize  = (mBpp * mWidth * mHeight);
        /* Allocate memory for image data */
        mImageData = (char *)malloc(imageSize);
        if(mImageData == NULL)
        {
            TOY3D_TIPS("could not allocate memory for image.\n");
            fclose(fTGA);
            return FALSE;
        }
        memset(mImageData, 0, imageSize);

        /* to read image data */
        if(fread(mImageData, 1, imageSize, fTGA) != imageSize)
        {
            TOY3D_TIPS("could not read image data.\n");
            if(mImageData != NULL)
            {
                free(mImageData);
            }
            fclose(fTGA);
            return FALSE;
        }

        /* Byte Swapping Optimized By Steve Thomas */
        for( cswap = 0; cswap < (int)imageSize; cswap += mBpp )
        {
            mImageData[cswap] ^= mImageData[cswap+2] ^=
                mImageData[cswap] ^= mImageData[cswap+2];
        }
        
        fclose(fTGA);
        return TRUE;
    }


    Bool TGAImage::LoadCompressedTGA(FILE * fTGA)       /* Load COMPRESSED TGAs */
    {
        return TRUE;
    }


//////////////////////////////////////////////////////////////////////////
//BmpImage
    Bool BMPImage::decode( const char* fileName )
    {
        return TRUE;
    }


TOY3D_END_NAMESPACE
