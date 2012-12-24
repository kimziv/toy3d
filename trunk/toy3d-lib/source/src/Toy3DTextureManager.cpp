#include "Toy3DTextureManager.h"
#include "Toy3DImage.h"

TOY3D_BEGIN_NAMESPACE

//used for decode image file
#define SEPERATER  '.'
#define TGA_SUFFIX ".tga"
#define BMP_SUFFIX ".bmp"


    TextureManager* TextureManager::mInstance = NULL;

    TextureManager::TextureManager()
    {
    }

    TextureManager::~TextureManager()
    {
    }

    TextureManager* TextureManager::getInstance() 
    {
        if (NULL == mInstance)
            mInstance = new TextureManager();

        return mInstance;
    }

    Texture* TextureManager::createTexture(ImageInfo *pImageInfo)
    {
        Texture *texture = new Texture();
        if( !texture )
            return NULL;

        Image *image = new TGAImage();
        if( !image )
            return NULL;

        image->mBpp = pImageInfo->bpp;
        image->mWidth = pImageInfo->width;
        image->mHeight = pImageInfo->height;
        image->mImageData = (char *)malloc(pImageInfo->size);
        memcpy(image->mImageData, pImageInfo->pImageData, pImageInfo->size);

        texture->genTexture(image);
        delete image;

        return texture;
    }

    Texture* TextureManager::createTextureByFile( const char* fileName )
    {
        Bool rvb;
        char *ptr;
        Image *image;

        Texture *texture = new Texture();
        if( !texture )
            return NULL;

        ptr = strrchr((char*)fileName, SEPERATER);
        if( !ptr )
        {
            TOY3D_TIPS("Image file name error: no effective suffix.\n");
            return NULL;
        }

        if( 0==strncmp(ptr, TGA_SUFFIX, strlen(TGA_SUFFIX)) )
        {
            image = new TGAImage();
        }
        else if( 0==strncmp(ptr, BMP_SUFFIX, strlen(BMP_SUFFIX)) )
        {
            image = new BMPImage();
        }
        else
        {
            TOY3D_TIPS("Image file error: file type isn't supported.\n");
            return NULL;
        }

        if( 0 == image )
            return NULL;

        rvb = image->decode(fileName);
        if( rvb != TRUE )
            return NULL;

        texture->genTexture(image);

        delete image;

        return texture;
    }

    void TextureManager::deleteTexture(Uint *texids, Uint count)
    {
        glDeleteTextures(count, texids);
        return;
    }

    /*
    void TextureManager::useTexture(Uint texid)
    {
        glActiveTexture(GL_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, texid);
        return;
    }
    */



TOY3D_END_NAMESPACE