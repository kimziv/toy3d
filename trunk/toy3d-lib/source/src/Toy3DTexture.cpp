#include "Toy3DTexture.h"

TOY3D_BEGIN_NAMESPACE



    Texture::Texture()
    {
        mTextureID = 0;
    }

    Texture::~Texture()
    {
    }

    //void Texture::loadImage(Image* image)
    //{
    //}

    void Texture::genTexture(Image* image)
    {
        glGenTextures(1, &mTextureID);

        //must
        glBindTexture(GL_TEXTURE_2D, mTextureID );

        // Create Nearest Filtered Texture
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        //for OpenGL ES 2.0 and above.
        if( image->mBpp == BPP_3 )
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->mWidth,
                image->mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image->mImageData );
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->mWidth,
                image->mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->mImageData );
        }

        return;
    }

    const Uint Texture::getTextureID() const
    {
        return (const int)mTextureID;
    }



TOY3D_END_NAMESPACE