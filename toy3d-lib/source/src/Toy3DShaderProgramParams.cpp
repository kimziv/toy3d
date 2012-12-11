
#include "Toy3DShaderProgramParams.h"


TOY3D_BEGIN_NAMESPACE

//AutoConstEntry::AutoConstEntry(AutoConstantType theType, Uchar *theName, Uint theIndex)
AutoConstEntry::AutoConstEntry(AutoConstantType theType, Uchar *theName )
{
    type = theType;
    index = 0;

    strncpy( (char *)name, (char *)theName, MAX_NAME_LEN);
}

AttrConstEntry::AttrConstEntry(AttrConstantType theType, Uchar *theName )
{
    type = theType;
    index = 0;
    
    strncpy( (char *)name, (char *)theName, MAX_NAME_LEN);
}

ShaderProgramParams::ShaderProgramParams()
{
    mAutoCount = 0;
}

ShaderProgramParams::~ShaderProgramParams()
{
    while( mAutoCount )
    {
        FREEANDNULL( mAutoConstEntries[--mAutoCount] );
    }
}

void ShaderProgramParams::setAutoConstValue( Uint index, const Real value[MATRIX_4x4_SIZE] )
{
    glUniformMatrix4fv( index, 1, 0, value );
}

void ShaderProgramParams::setNamedAutoConstant ( AutoConstantType type, Uchar *name )
{
    if( searchNamedConst(name, 0) )
    {
        PRINT("setNamedAutoConstant failed. AutoConst name exist.\n");
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

Uchar* ShaderProgramParams::getAutoParamName( Uint index )
{
    return mAutoConstEntries[index]->name;
}

void ShaderProgramParams::updateAutoConstIndex ( Uchar *name, Uint index )
{
    Uint position = 0;
    if( !searchNamedConst(name, &position) )
    {
        PRINT("updateAutoConstIndex failed. AutoConst name doesn't exist.\n");
        return;
    }

    mAutoConstEntries[position]->index = index;
    
    return;
}

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

        default:
            break;
        }
    }
    return;
}

Bool ShaderProgramParams::searchNamedConst( const Uchar *name, Uint* index )
{
    int i = mAutoCount;
    while( i )
    {
        i--;
        if( !strnicmp((const char *)mAutoConstEntries[i]->name, (const char *)name, MAX_NAME_LEN) )
        {
            if( index )
                *index = i;
            return true;
        }
    }

    if( index )
        *index = -1;
    return false;
}





TOY3D_END_NAMESPACE

