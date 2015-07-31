# Introduction #

增加 alpha 混合支持


# 使用样例 #

```

    Material *mat = MaterialManager::getInstance()->createMaterial();
    ...
    mat->setSceneBlending(T3D_BLEND_SRC_ALPHA, BLEND_ONE_MINUS_SRC_ALPHA);

```

# 设计 #

```
    enum BlendingFactor
    {
        /* Blending Factor Dest */
        T3D_ZERO,
        T3D_ONE,
        T3D_SRC_COLOR,
        T3D_ONE_MINUS_SRC_COLOR,
        T3D_SRC_ALPHA,
        T3D_ONE_MINUS_SRC_ALPHA,
        T3D_DST_ALPHA,
        T3D_ONE_MINUS_DST_ALPHA,

        /* Blending Factor Src */
        /* T3D_ZERO */
        /* T3D_ONE */
        T3D_DST_COLOR,
        T3D_ONE_MINUS_DST_COLOR,
        T3D_SRC_ALPHA_SATURATE,
        /* T3D_SRC_ALPHA */
        /* T3D_ONE_MINUS_SRC_ALPHA */
        /* T3D_DST_ALPHA */
        /* T3D_ONE_MINUS_DST_ALPHA */
    };
    
    enum BlendingMode
    {
        T3D_ADD,
        T3D_SUBTRACT,
        T3D_SUBTRACT_REVERSE,
        T3D_MIN,
        T3D_MAX
    };


class Material {
    Material()
    {
        ...
        mAlphaBlending = FALSE;
    }

    bool mAlphaBlending;     /* default value : false */
    BlendingFactor mSrcFactor;
    BlendingFactor mDestFactor;
    BlendingMode   mMode;


    void setSceneBlending(BlendingFactor srcFactor, BlendingFactor destFactor, BlendingMode mode = T3D_ADD);
    const BlendingFactor getSrcBlendFactor() const;
    const BlendingFactor getDestBlendFactor() const;
    const BlendingMode getBlendMode() const;
};

void Material::void setSceneBlending(BlendingFactor srcFactor, BlendingFactor destFactor, BlendingMode mode)
{
    mSrcFactor = srcFactor;
    mDestFactor = destFactor;
    mMode = mode;

    mAlphaBlending = TRUE;

    return;
}

const Bool Material::hasAlphaBlending() const
{
    return (const Bool)mAlphaBlending;
}

const BlendingFactor Material::getSrcBlendFactor() const
{
    return (const BlendingFactor)mSrcFactor;
}

const BlendingFactor Material::getDestBlendFactor() const
{
    return (const BlendingFactor)mDestFactor;
}

const BlendingMode Material::getBlendMode() const
{
    return (const BlendingMode)mMode;
}


class Renderer
{
    void enableBlending (bool flag);
    void setSceneBlending(BlendingFactor srcFactor,BlendingFactor destFactor, BlendingMode mode);

    /* convert blenging factor to the value which the hardware support. */
    Uint getBlendFactor(BlendingFactor srcFactor);

    /* convert blenging mode to the value which the hardware support. */
    Uint getBlendMode(BlendingMode mode);
}

void Renderer::enableBlending (bool flag)
{
    if(flag)
        glEnable(GL_BLEND);
    else
        glDisable(GL_BLEND);

    return;
}

void Renderer::setSceneBlending(BlendingFactor srcFactor,BlendingFactor destFactor, BlendingMode mode)
{
    glBlendFunc(getBlendFactor(srcFactor), getBlendFactor(destFactor));
    glBlendEquation(getBlendMode(mode));

    return;
}

Uint Renderer::getBlendFactor(BlendingFactor factor)
{
    switch(factor)
    {
    case T3D_ONE:
        return GL_ONE;
    case T3D_ZERO:
        return GL_ZERO;
    case T3D_DST_COLOR:
        return GL_DST_COLOR;
    case T3D_SRC_COLOR:
        return GL_SRC_COLOR;
    case T3D_ONE_MINUS_DST_COLOR:
        return GL_ONE_MINUS_DST_COLOR;
    case T3D_ONE_MINUS_SRC_COLOR:
        return GL_ONE_MINUS_SRC_COLOR;
    case T3D_DST_ALPHA:
        return GL_DST_ALPHA;
    case T3D_SRC_ALPHA:
        return GL_SRC_ALPHA;
    case T3D_ONE_MINUS_DST_ALPHA:
        return GL_ONE_MINUS_DST_ALPHA;
    case T3D_ONE_MINUS_SRC_ALPHA:
        return GL_ONE_MINUS_SRC_ALPHA;
    case T3D_SRC_ALPHA_SATURATE:
        return GL_SRC_ALPHA_SATURATE;
    }

    return GL_ONE;
}

Uint Renderer::getBlendMode(BlendingMode mode)
{
    switch(mode)
    {
    case T3D_ADD:
        return GL_FUNC_ADD;
    case T3D_SUBTRACT:
        return GL_FUNC_SUBTRACT;
    case T3D_REVERSE_SUBTRACT:
        return GL_FUNC_REVERSE_SUBTRACT;
    case T3D_MIN:
        return GL_MIN_EXT;
    case T3D_MAX:
        return GL_MAX;
    }

    return GL_FUNC_ADD;
}

void World::renderSingleObject (RenderOperation *ro, Material *mat, Real worldMatrix[16], Real viewMatrix[16], Real projMatrix[16])
{
    if (mat->hasAlphaBlending()){
        mRenderer.enableBlending(TRUE);
        mRenderer.setSceneBlending(mat->getSourceBlendFactor(),
                                   mat->getDestBlendFactor(),
                                   mat->getBlendMode()
                                   );
    }

    mRenderer.render(op);

    if (mat->hasAlphaBlending())
        mRenderer.enableBlending(FALSE);
}




```

# Reference #

  * [OGRE Texture Blending 纹理混合](http://www.cnitblog.com/buf/archive/2011/07/27/74877.html)  3张图3个 texture unit