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


    BOOL TGAImage::LoadCompressedTGA(FILE * fTGA)       /* Load COMPRESSED TGAs */
    {
#if 0
        GLuint pixelcount   = tga.Height * tga.Width;                           /* Nuber of pixels in the image */
        GLuint currentpixel = 0;                                                /* Current pixel being read */
        GLuint currentbyte  = 0;                                                /* Current byte */
        GLubyte * colorbuffer = (GLubyte *)malloc(tga.bytesPerPixel);           /* Storage for 1 pixel */
        
        if(fread(mHeader6, sizeof(mHeader6), 1, fTGA) == 0)             /* Attempt to read header */
        {
            TOY3D_TIPS("could not read info header.\n");                          /* Display Error */
            if(fTGA != NULL)                                                    /* If file is open */
            {
                fclose(fTGA);                                                   /* Close it */
            }
            return False;                                                       /* Return failed */
        }
        
        mWidth  = mHeader6[1] * 256 + mHeader6[0];                  /* Determine The TGA Width  (highbyte*256+lowbyte) */
        mHeight = mHeader6[3] * 256 + mHeader6[2];                  /* Determine The TGA Height (highbyte*256+lowbyte) */
        bpp    = mHeader6[4];                                        /* Determine Bits Per Pixel */
        tga.Width       = mWidth;                                       /* Copy width to local structure */
        tga.Height      = mHeight;                                      /* Copy width to local structure */
        tga.Bpp         = bpp;                                         /* Copy width to local structure */
        
        if((mWidth <= 0) || (mHeight <= 0) || ((bpp != 24) && (bpp !=32)))    /*Make sure all texture info is ok */
        {
            TOY3D_TIPS("Invalid texture information.\n");                     /* If it isnt...Display error */
            if(fTGA != NULL)                                                    /* Check if file is open */
            {
                fclose(fTGA);                                                   /* Ifit is, close it */
            }
            return False;                                                       /* Return failed */
        }
        
        tga.bytesPerPixel   = (tga.Bpp / 8);                                    /* Compute BYTES per pixel */
        imageSize       = (tga.bytesPerPixel * tga.Width * tga.Height);     /* Compute amout of memory needed to store image */
        mImageData  = (GLubyte *)malloc(imageSize);                 /* Allocate that much memory */
        
        if(mImageData == NULL)                                          /* If it wasnt allocated correctly.. */
        {
            TOY3D_TIPS("could not allocate memory for image.\n");             /* Display Error */
            fclose(fTGA);                                                       /* Close file */
            return False;                                                       /* Return failed */
        }
        
        do
        {
            GLubyte chunkheader = 0;                                            /* Storage for "chunk" header */
            
            if(fread(&chunkheader, sizeof(GLubyte), 1, fTGA) == 0)              /* Read in the 1 byte header */
            {
                TOY3D_TIPS("could not read RLE header.\n");                       /*Display Error */
                if(fTGA != NULL)                                                /* If file is open */
                {
                    fclose(fTGA);                                               /* Close file */
                }
                if(mImageData != NULL)                                  /* If there is stored image data */
                {
                    free(mImageData);                                   /* Delete image data */
                }
                return False;                                                   /* Return failed */
            }
            
            if(chunkheader < 128)                                               /* If the ehader is < 128, it means the that is the number of RAW color packets minus 1 */
            {
                short counter;                                                  /* that follow the header */
                chunkheader++;                                                  /* add 1 to get number of following color values */
                for(counter = 0; counter < chunkheader; counter++)              /* Read RAW color values */
                {
                    if(fread(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel) /* Try to read 1 pixel */
                    {
                        TOY3D_TIPS("could not read image data.\n");               /* IF we cant, display an error */
                        
                        if(fTGA != NULL)                                        /* See if file is open */
                        {
                            fclose(fTGA);                                       /* If so, close file */
                        }
                        
                        if(colorbuffer != NULL)                                 /* See if colorbuffer has data in it */
                        {
                            free(colorbuffer);                                  /* If so, delete it */
                        }
                        
                        if(mImageData != NULL)                                      /* See if there is stored Image data */
                        {
                            free(mImageData);                                       /* If so, delete it too */
                        }
                        
                        return False;                                                       /* Return failed */
                    }
                    /* write to memory */
                    mImageData[currentbyte      ] = colorbuffer[2];                 /* Flip R and B vcolor values around in the process */
                    mImageData[currentbyte + 1  ] = colorbuffer[1];
                    mImageData[currentbyte + 2  ] = colorbuffer[0];
                    
                    if(tga.bytesPerPixel == 4)                                              /* if its a 32 bpp image */
                    {
                        mImageData[currentbyte + 3] = colorbuffer[3];               /* copy the 4th byte */
                    }
                    
                    currentbyte += tga.bytesPerPixel;                                       /* Increase thecurrent byte by the number of bytes per pixel */
                    currentpixel++;                                                         /* Increase current pixel by 1 */
                    
                    if(currentpixel > pixelcount)                                           /* Make sure we havent read too many pixels */
                    {
                        TOY3D_TIPS("too many pixels read.\n");                                /* if there is too many... Display an error! */
                        
                        if(fTGA != NULL)                                                    /* If there is a file open */
                        {
                            fclose(fTGA);                                                   /* Close file */
                        }
                        
                        if(colorbuffer != NULL)                                             /* If there is data in colorbuffer */
                        {
                            free(colorbuffer);                                              /* Delete it */
                        }
                        
                        if(mImageData != NULL)                                      /* If there is Image data */
                        {
                            free(mImageData);                                       /* delete it */
                        }
                        
                        return False;                                                       /* Return failed */
                    }
                }
            }
            else                                                                            /* chunkheader > 128 RLE data, next color  reapeated chunkheader - 127 times */
            {
                short counter;
                chunkheader -= 127;                                                         /* Subteact 127 to get rid of the ID bit */
                if(fread(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel)     /* Attempt to read following color values */
                {
                    TOY3D_TIPS("could not read from file.\n");            /* If attempt fails.. Display error (again) */
                    
                    if(fTGA != NULL)                                                        /* If thereis a file open */
                    {
                        fclose(fTGA);                                                       /* Close it */
                    }
                    
                    if(colorbuffer != NULL)                                                 /* If there is data in the colorbuffer */
                    {
                        free(colorbuffer);                                                  /* delete it */
                    }
                    
                    if(mImageData != NULL)                                          /* If thereis image data */
                    {
                        free(mImageData);                                           /* delete it */
                    }
                    
                    return False;                                                           /* return failed */
                }
                
                for(counter = 0; counter < chunkheader; counter++)                  /* copy the color into the image data as many times as dictated */
                {                                                                           /* by the header */
                    mImageData[currentbyte      ] = colorbuffer[2];                 /* switch R and B bytes areound while copying */
                    mImageData[currentbyte + 1  ] = colorbuffer[1];
                    mImageData[currentbyte + 2  ] = colorbuffer[0];
                    
                    if(tga.bytesPerPixel == 4)                                              /* If TGA images is 32 bpp */
                    {
                        mImageData[currentbyte + 3] = colorbuffer[3];               /* Copy 4th byte */
                    }
                    
                    currentbyte += tga.bytesPerPixel;                                       /* Increase current byte by the number of bytes per pixel */
                    currentpixel++;                                                         /* Increase pixel count by 1 */
                    
                    if(currentpixel > pixelcount)                                           /* Make sure we havent written too many pixels */
                    {
                        TOY3D_TIPS("too many pixels read.\n");                                /* if there is too many... Display an error! */
                        
                        if(fTGA != NULL)                                                    /* If there is a file open */
                        {
                            fclose(fTGA);                                                   /* Close file */
                        }
                        
                        if(colorbuffer != NULL)                                             /* If there is data in colorbuffer */
                        {
                            free(colorbuffer);                                              /* Delete it */
                        }
                        
                        if(mImageData != NULL)                                      /* If there is Image data */
                        {
                            free(mImageData);                                       /* delete it */
                        }
                        
                        return False;                                                       /* Return failed */
                    }
                }
            }
        }
        while(currentpixel < pixelcount);                                                   /* Loop while there are still pixels left */
        fclose(fTGA);                                                                       /* Close the file */
#endif
        return TRUE;
    }


//////////////////////////////////////////////////////////////////////////
//BmpImage
    Bool BMPImage::decode( const char* fileName )
    {
        return TRUE;
    }


TOY3D_END_NAMESPACE