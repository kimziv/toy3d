
#include "Toy3DShaderProgramParams.h"


TOY3D_BEGIN_NAMESPACE

//AutoConstEntry::AutoConstEntry(AutoConstantType theType, Uchar *theName, Uint theIndex)
AutoConstEntry::AutoConstEntry(AutoConstantType theType, char *theName )
{
    type = theType;
    index = 0;

    strncpy( (char *)name, (char *)theName, MAX_NAME_LEN);
}

AttrConstEntry::AttrConstEntry(AttrConstantType theType, char *theName )
{
    type = theType;
    index = 0;
    
    strncpy( (char *)name, (char *)theName, MAX_NAME_LEN);
}

ShaderProgramParams::ShaderProgramParams()
{
    mAutoCount = 0;
    mAttrCount = 0;
}

ShaderProgramParams::~ShaderProgramParams()
{
    while( mAutoCount )
    {
        DELETEANDNULL( mAutoConstEntries[--mAutoCount] );
    }

    while( mAttrCount )
    {
        DELETEANDNULL( mAttrConstEntries[--mAttrCount] );
    }
}

void ShaderProgramParams::setAutoConstValue( Uint index, const Real value[MATRIX_4x4_SIZE] )
{
    glUniformMatrix4fv( index, 1, 0, value );
    return;
}

void ShaderProgramParams::setAutoConstValue( Uint index, const Uint texUnit )
{
    glUniform1i( index, texUnit );
    return;
}

void ShaderProgramParams::setNamedAutoConstant ( AutoConstantType type, char *name )
{
    if( searchNamedAutoConst(name, 0) )
    {
        TOY3D_PRINT("setNamedAutoConstant failed. AutoConst name exist.", __FILE__, __LINE__);
        return;
    }

    AutoConstEntry *entry = new AutoConstEntry(type, name );
    mAutoConstEntries[mAutoCount++] = entry;

    return;
}

Uint ShaderProgramParams::getAutoEntryCount()
{
    return mAutoCount;
}

const char* ShaderProgramParams::getAutoParamName( Uint index )
{
    return (const char *)mAutoConstEntries[index]->name;
}

void ShaderProgramParams::updateAutoConstIndex ( const char *name, Uint index )
{
    Uint position = 0;
    if( !searchNamedAutoConst(name, &position) )
    {
        TOY3D_PRINT("updateAutoConstIndex failed. AutoConst name doesn't exist.", __FILE__, __LINE__);
        return;
    }

    mAutoConstEntries[position]->index = index;
    
    return;
}

/*
void ShaderProgramParams::updateAutoConstIndex_2 ( const Uchar *name, Uint shaderProgID )
{
    Uint position = 0;
    if( !searchNamedConst(name, &position) )
    {
        PRINT("updateAutoConstIndex failed. AutoConst name doesn't exist.\n");
        return;
    }

    mAutoConstEntries[position]->index = glGetUniformLocation( shaderProgID, (const char *)name );
    
    return;
}
*/

void ShaderProgramParams::updateAutoConstParams ( AutoParamDataSource *source )
{
    Uint i;
    AutoConstEntry *tempACE;
    for ( i=0; i<mAutoCount; i++ )
    {
        tempACE = mAutoConstEntries[i];
        switch( mAutoConstEntries[i]->type )
        {
        case TOY3D_ACT_WORLD_MATRIX:
            setAutoConstValue( mAutoConstEntries[i]->index, source->getWorldMatrix() );
            break;

        case TOY3D_ACT_PROJECTION_MATRIX:
            setAutoConstValue( mAutoConstEntries[i]->index, source->getProjectionMatrix() );
            break;

        case TOY3D_ACT_VIEW_MATRIX:
            setAutoConstValue( mAutoConstEntries[i]->index, source->getViewMatrix() );
            break;

            //transfer to the custom types
        case TOY3D_ACT_SAMPLER2D:
            setAutoConstValue( mAutoConstEntries[i]->index, source->getTextureUnit());

        default:
            break;
        }
    }
    return;
}

Bool ShaderProgramParams::searchNamedAutoConst( const char *name, Uint* index )
{
    int i = mAutoCount;
    while( i )
    {
        i--;
        if( !strncmp((const char *)mAutoConstEntries[i]->name, (const char *)name, MAX_NAME_LEN) )
        {
            if( index )
                *index = i;
            return true;
        }
    }

    if( index )
        *index = 0;
    return false;
}

//////////////////////////////////////////////////////////////////////////
//Attribute variable

Bool ShaderProgramParams::searchNamedAttrConst( const char *name, Uint* index )
{
    int i = mAttrCount;
    while( i )
    {
        i--;
        if( !strncmp((const char *)mAttrConstEntries[i]->name, (const char *)name, MAX_NAME_LEN) )
        {
            if( index )
                *index = i;
            return true;
        }
    }
    
    if( index )
        *index = 0;
    return false;
}

void ShaderProgramParams::setNamedAttrConstant ( AttrConstantType type, char *name )
{
    if( searchNamedAttrConst(name, 0) )
    {
        TOY3D_PRINT("setNamedAutoConstant failed. AutoConst name exist.", __FILE__, __LINE__);
        return;
    }
   
 
    AttrConstEntry *entry = new AttrConstEntry(type, name );
    mAttrConstEntries[mAttrCount++] = entry;

    return;
}

void ShaderProgramParams::updateAttrConstIndex ( const char *name, Uint index )
{
    Uint position = 0;
    if( !searchNamedAttrConst(name, &position) )
    {
        TOY3D_PRINT("updateAutoConstIndex failed. AutoConst name doesn't exist.", __FILE__, __LINE__);
        return;
    }
    
    mAttrConstEntries[position]->index = index;
    
    return;
}

Uint ShaderProgramParams::getAttrEntryCount()
{
    return mAttrCount;
}

const char* ShaderProgramParams::getAttrParamName( Uint index )
{
    return (const char*)mAttrConstEntries[index]->name;
}

Uint ShaderProgramParams::getAttrConstIndex( AttrConstantType type )
{
    for (Uint i=0; i<mAttrCount; i++)
    {
        if( mAttrConstEntries[i]->type == type)
            return mAttrConstEntries[i]->index;
    }

    return 0;
}




TOY3D_END_NAMESPACE

