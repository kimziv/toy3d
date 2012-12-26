#include "Toy3DTexture.h"

TOY3D_BEGIN_NAMESPACE



    Texture::Texture()
    {
        mTextureID = 0;
    }

    Texture::~Texture()
    {
    }

    Bool Texture::genTexture(Image* image)
    {
        glGenTextures(1, &mTextureID);
        glBindTexture(GL_TEXTURE_2D, mTextureID );

        //set parameter
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

        if(image->mBpp==BPP_3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->mWidth,
                image->mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image->mImageData );
        }
        else if(image->mBpp==BPP_4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->mWidth,
                image->mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->mImageData );
        }
        else
        {
            TOY3D_TIPS("Generate texture error : unrecognized Bpp.\n");
            return FALSE;
        }

        return TRUE;
    }

    Bool Texture::genTexture(unsigned char *pImageData, Uint width, Uint height, Uint bpp)
    {
        glGenTextures(1, &mTextureID);
        glBindTexture(GL_TEXTURE_2D, mTextureID );
        
        //set parameter
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

        if(bpp==BPP_3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width,
                height, 0, GL_RGB, GL_UNSIGNED_BYTE, pImageData );
        }
        else if(bpp==BPP_4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,
                height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pImageData );
        }
        else
        {
            TOY3D_TIPS("Generate texture error : unrecognized Bpp.\n");
            return FALSE;
        }
        
        return TRUE;
    }

    const Uint Texture::getTextureID() const
    {
        return (const int)mTextureID;
    }



TOY3D_END_NAMESPACE