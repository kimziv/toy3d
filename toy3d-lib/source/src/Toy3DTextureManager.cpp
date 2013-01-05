#include "Toy3DTextureManager.h"
#include "Toy3DImage.h"

TOY3D_BEGIN_NAMESPACE


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

    Texture* TextureManager::createTexture(unsigned char *pImageData, Uint width, Uint height, Uint bpp)
    {
        Bool rvb;
        Texture *texture = new Texture();
        if( !texture )
            return NULL;

        rvb = texture->genTexture(pImageData, width, height, bpp);
        if( rvb != TRUE )
            return NULL;

        return texture;
    }

    Texture* TextureManager::createTexture(ImageInfo *pImageInfo)
    {
        Bool rvb;
        Texture *texture = new Texture();
        if( !texture )
            return NULL;
        
        rvb = texture->genTexture(pImageInfo->pImageData,
            pImageInfo->width, pImageInfo->height, pImageInfo->bpp);
        if( rvb != TRUE )
            return NULL;
        
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

        rvb = texture->genTexture(image);
        if( rvb != TRUE )
            return NULL;

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
