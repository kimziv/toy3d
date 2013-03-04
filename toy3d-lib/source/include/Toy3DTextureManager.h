
#ifndef _TOY3D_TEXTURE_MANAGER_H
#define _TOY3D_TEXTURE_MANAGER_H

#include "Toy3DCommon.h"
#include "Toy3DTexture.h"
#include "Toy3DPtrArray.h"


TOY3D_BEGIN_NAMESPACE

#if 0
class TextureManager
{

    enum TextureManageRule
    {
        T3D_LRU,
        T3D_FIFO
    };

    private:
        TextureManager();
        static TextureManager* mInstance;
        
        TPtrArray *mPtrArray;

        Uint mMemory;        /* the budget of memory */
        Uint mVMemory;       /* the budget of memory on vedio card */
        Uint mMemoryRest;    /* the rest of usable memory */
        Uint mVMemoryRest;   /* the rest of usable vedio card memory */

        char mDirName[MAX_NAME_LEN_BIG+1]; /* used for the files created by the constructor.*/

        //TextureManageRule mTMRule;

        /*
         * Fixme: Maybe the function should be privided in class Texture.
         */
        void deleteTextureFromGpu(Uint *texids, Uint count);

    protected:

    public:
        ~TextureManager();
        static TextureManager* getInstance();

        void setMemoryBudget(Uint value);  /* memory budget, unit MB */
        void setVMemoryBudget(Uint value); /* video card memory budget, unit MB */

        void setDirtory(char *pDirName);

        //void setTextureManagerRule(TextureManageRule rule = T3D_LRU);

        void create(char *pName);
        void create(char *pName, char *pResFileName, Bool isResident = FALSE);

        /*
         * Create a texture with tht state TOY3D_LOADED.
         * Attentions:
         * The information will be saved as *.tex in the directory mDirName.
         * So if you use the interface,
         * you should have the permissions to read and right the hardware.
         */
        const char* create(unsigned char *pImageData,Uint width, Uint height, Uint bytesPerPixel);

        Bool load(char *pName);
        //Bool load(Texture *pTexture);
        /* Reload all the textures which have been loaded. */
        Bool reload();

        Bool unload(char *pName);
        //Bool unload(Texture *pTexture);
        Bool unload(Uint idleLevel); /* It works, when the idleLevel is greater than 0 only. */

        Bool generate(char *pName);
        //Bool generate(Texture *pTexture);

        Bool degenerate(char *pName);
        //Bool degenerate(Texture *pTexture);
        Bool degenerate(Uint idleLevel); /* It works, when the idleLevel is greater than 0 only. */

        /* If the texture which you want to remove is being used, it will return false. */
        Bool remove(char *pName);
        //Bool remove(Texture *pTexture);
        /* If some of the texturesis being used, it will return false. */
        Bool removeAll();

        Bool removeFiles();

        const Uint getRestOfMemory() const;
        const Uint getRestOfVMemory() const;
};

#endif

    class TextureManager
    {
    private:
        TextureManager();
        static TextureManager* mInstance;

        TPtrArray *mPtrArray;

        void deleteTextureFromGpu(Uint *texids, Uint count);

    public:
        ~TextureManager();
        static TextureManager* getInstance();

        /*
         * function : createTexture
         * parameter:
         *     pImageData : color data of image
         *     width : width of image
         *     height : height of image
         *     bpp : bytes per pixel
         * warning : the memory of pImageData be released.
         */
        Texture* createTexture(unsigned char *pImageData, Uint width, Uint height, Uint bpp);

        Texture* createTexture(ImageInfo *pImageInfo);
        Texture* createTextureByFile( const char* fileName );

        //void destroyTexture(Texture *tex);
        void destroyTexture(Texture *tex);
        void destroyAllTextures();
    };


TOY3D_END_NAMESPACE

#endif
