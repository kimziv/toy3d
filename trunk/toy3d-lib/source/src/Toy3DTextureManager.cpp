#include "Toy3DTextureManager.h"
#include "Toy3DImage.h"

TOY3D_BEGIN_NAMESPACE


    TextureManager* TextureManager::mInstance = NULL;

    TextureManager::TextureManager()
    {
        mPtrArray = new TPtrArray();
        mPtrArray->create();
    }

    TextureManager::~TextureManager()
    {
        mPtrArray->destroy();
        delete mPtrArray;
    }

    TextureManager* TextureManager::getInstance() 
    {
        if(NULL==mInstance)
            mInstance = new TextureManager();

        return mInstance;
    }

    Texture* TextureManager::createTexture(unsigned char *pImageData, Uint width, Uint height, Uint bpp)
    {
        Bool rv;
        Texture *pTexture = new Texture();
        if( !pTexture )
            return NULL;

        rv = pTexture->genTexture(pImageData, width, height, bpp);
        if( rv != TRUE )
        {
            delete pTexture;
            return NULL;
        }

        rv = mPtrArray->append((TPointer)pTexture );
        if(FALSE==rv)
        {
            delete pTexture;
            TOY3D_TIPS("Error: Failed to store the pointer.\n");
            return NULL;
        }

        return pTexture;
    }

    Texture* TextureManager::createTexture(ImageInfo *pImageInfo)
    {
        Bool rv;
        Texture *pTexture = new Texture();
        if( !pTexture )
            return NULL;

        rv = pTexture->genTexture(pImageInfo->pImageData,
            pImageInfo->width, pImageInfo->height, pImageInfo->bpp);
        if( rv != TRUE )
        {
            delete pTexture;
            return NULL;
        }

        rv = mPtrArray->append((TPointer)pTexture );
        if(FALSE==rv)
        {
            delete pTexture;
            TOY3D_TIPS("Error: Failed to store the pointer.\n");
            return NULL;
        }

        return pTexture;
    }

    Texture* TextureManager::createTextureByFile( const char* fileName )
    {
        Bool rv;
        char *ptr;
        Image *pImage;
        Texture *pTexture;

        ptr = strrchr((char*)fileName, SEPERATER);
        if( !ptr )
        {
            TOY3D_TIPS("Image file name error: no effective suffix.\n");
            return NULL;
        }

        if( 0==strncmp(ptr, TGA_SUFFIX, strlen(TGA_SUFFIX)) )
        {
            pImage = new TGAImage();
        }
        else if( 0==strncmp(ptr, BMP_SUFFIX, strlen(BMP_SUFFIX)) )
        {
            pImage = new BMPImage();
        }
        else
        {
            TOY3D_TIPS("Image file error: file type isn't supported.\n");
            return NULL;
        }

        if( 0 == pImage )
            return NULL;

        rv = pImage->decode(fileName);
        if( rv != TRUE )
        {
            delete pImage;
            return NULL;
        }

        pTexture = new Texture();
        if( !pTexture )
        {
            delete pImage;
            return NULL;
        }

        rv = pTexture->genTexture(pImage);
        if( rv != TRUE )
        {
            delete pImage;
            delete pTexture;
            return NULL;
        }

        delete pImage;

        rv = mPtrArray->append((TPointer)pTexture );
        if(FALSE==rv)
        {
            delete pTexture;
            TOY3D_TIPS("Error: Failed to store the pointer.\n");
            return NULL;
        }

        return pTexture;
    }

    void TextureManager::deleteTextureFromGpu(Uint *pTexids, Uint count)
    {
        glDeleteTextures(count, pTexids);
        return;
    }

    void TextureManager::destroyTexture(Texture *tex)
    {
        Uint texid;
        mPtrArray->remove((TPointer)tex);
        texid = tex->getTextureID();
        deleteTextureFromGpu(&texid, 1);
        delete tex;

        return;
    }

    void TextureManager::destroyAllTextures()
    {
        Texture *temp;
        Uint texid;
        Uint length = mPtrArray->getLength();
        
        while(length--)
        {
            temp = (Texture *)mPtrArray->getElement(length);
            texid = temp->getTextureID();
            deleteTextureFromGpu(&texid, 1);
            delete temp;
            //mPtrArray->setElement(NULL, length);
        }
        
        mPtrArray->clearAll();

        return;
    }


TOY3D_END_NAMESPACE
