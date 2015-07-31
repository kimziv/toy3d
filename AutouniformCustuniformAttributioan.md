# 概念 #

分2类：
  * Attrubiton
  * Uniform
    1. auto uniform:
    1. custom uniform : 需要用户set

# 设计与实现 #


```

class ShaderProgramParams {

    intlist
    realistkkk

    setCustUniform (const char* name, Uint value);

}

void ShaderProgramParams::setCustUniform (const char* name, Uint value)
{
    index = glGetUnifrom (name);
    glSetUniform (index, value);
}

```

# 使用样例 #

```

    ShaderProgramParams *params = new ShaderProgramParams ();


    //uniforms
    params->setNamedAutoConstant (TOY3D_ACT_PROJECTION_MATRIX, "proj_mat");
    params->setNamedAutoConstant (TOY3D_ACT_VIEW_MATRIX, "view_mat");
    params->setNamedAutoConstant (TOY3D_ACT_WORLD_MATRIX, "world_mat");

    params->setCustUnifrom ("sample2d", value);

    //attributes
    params->setNamedAttrConstant (TOY3D_ATTR_VERTEX_INDEX, "vPosition");


    shaderProgram->bindShaderParameters(params);


```