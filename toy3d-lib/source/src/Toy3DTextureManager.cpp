#include "Toy3DTextureManager.h"
#include "Toy3DImage.h"

TOY3D_BEGIN_NAMESPACE


    TextureManager* TextureManager::mInstance = NULL;

    TextureManager::TextureManager()
    {
        mTextureCount = 0;
        for(int i=0; i<MAX_TEXTURE_COUNT; i++)
        {
            mTextures[i] = 0;
        }
    }

    TextureManager::~TextureManager()
    {
    }

    TextureManager* TextureManager::getInstance() 
    {
        if(NULL==mInstance)
            mInstance = new TextureManager();

        return mInstance;
    }

    Texture* TextureManager::createTexture(unsigned char *pImageData, Uint width, Uint height, Uint bpp)
    {
        Bool rvb;
        Texture *pTexture = new Texture();
        if( !pTexture )
            return NULL;

        rvb = pTexture->genTexture(pImageData, width, height, bpp);
        if( rvb != TRUE )
            return NULL;

        mTextures[mTextureCount++] = pTexture;

        return pTexture;
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

        mTextures[mTextureCount++] = texture;
        
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
        mTextures[mTextureCount++] = texture;

        return texture;
    }

    void TextureManager::deleteTextureFromGpu(Uint *pTexids, Uint count)
    {
        glDeleteTextures(count, pTexids);
        return;
    }

    /*
    void TextureManager::destroyTexture(Texture *tex)
    {
        return;
    }
    */

    void TextureManager::destroyAllTextures()
    {
        Texture *temp;
        Uint texid;

        while(mTextureCount--)
        {
            temp = mTextures[mTextureCount];
            texid = temp->getTextureID();
            deleteTextureFromGpu(&texid, 1);
            delete temp;
            mTextures[mTextureCount] = 0;
        }

        return;
    }


TOY3D_END_NAMESPACE
