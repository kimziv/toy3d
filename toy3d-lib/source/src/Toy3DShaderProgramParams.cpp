
#include "Toy3DShaderProgramParams.h"


TOY3D_BEGIN_NAMESPACE

//////////////////////////////////////////////////////////////////////////
//AutoConstEntry
AutoParamEntry::AutoParamEntry(AutoConstanType theType, char *theName )
{
    type = theType;
    index = 0;
    strncpy( (char *)name, (char *)theName, MAX_NAME_LEN);
}

//////////////////////////////////////////////////////////////////////////
//AttrConstEntry
AttrParamEntry::AttrParamEntry(AttrConstantType theType, char *theName )
{
    type = theType;
    index = 0;
    strncpy( (char *)name, (char *)theName, MAX_NAME_LEN);
}


//////////////////////////////////////////////////////////////////////////
//Custom Constant Entry
IntParamEntry::IntParamEntry(CustUniformConstanType theType, char *theName, int theVal)
{
    type = theType;
    strncpy( (char *)name, (char *)theName, MAX_NAME_LEN);
    value = theVal;
    index = 0;
}

RealParamEntry::RealParamEntry(CustUniformConstanType theType, char *theName, Real theVal)
{
    type = theType;
    strncpy( (char *)name, (char *)theName, MAX_NAME_LEN);
    value = theVal;
    index = 0;
}


//////////////////////////////////////////////////////////////////////////
//ShaderProgramParams

ShaderProgramParams::ShaderProgramParams()
{
    int i;
    mAutoUniformCount = 0;
    mAttrCount = 0;
    mIntUniformCount  = 0;
    mRealUniformCount = 0;

    for(i=0; i<MAX_AUTOENTRY_COUNT; i++)
        mAutoUniformEntries[i] = 0;

    for(i=0; i<MAX_ATTRENTRY_COUNT; i++)
        mAttrEntries[i] = 0;

    for(i=0; i<MAX_CUSTENTRY_COUNT; i++)
        mIntUniformEntries[i] = 0;

    for(i=0; i<MAX_CUSTENTRY_COUNT; i++)
        mRealUniformEntries[i] = 0;
}

ShaderProgramParams::~ShaderProgramParams()
{
    AutoParamEntry *temp1;
    while( mAutoUniformCount )
    {
        temp1 = mAutoUniformEntries[--mAutoUniformCount];
        DELETEANDNULL( temp1 );
        mAutoUniformEntries[mAutoUniformCount] = 0;
    }

    AttrParamEntry *temp2;
    while( mAttrCount )
    {
        temp2 = mAttrEntries[--mAttrCount];
        DELETEANDNULL( temp2 );
        mAttrEntries[mAttrCount] = 0;
    }

    IntParamEntry *temp3;
    while( mIntUniformCount )
    {
        temp3 = mIntUniformEntries[--mIntUniformCount];
        DELETEANDNULL( temp3 );
        mIntUniformEntries[mIntUniformCount] = 0;
    }

    RealParamEntry *temp4;
    while( mRealUniformCount )
    {
        temp4 = mRealUniformEntries[--mRealUniformCount];
        DELETEANDNULL( temp4 );
        mRealUniformEntries[mRealUniformCount] = 0;
    }
}

/* Auto Uniform Parameter Methods -------------------------------start */
void ShaderProgramParams::setAutoUniformConstant( Uint index, const Real value[MATRIX_4x4_SIZE] )
{
    glUniformMatrix4fv( index, 1, 0, value );
    return;
}

void ShaderProgramParams::setAutoUniformConstant( Uint index, const Uint texUnit )
{
    glUniform1i( index, texUnit );
    return;
}

Bool ShaderProgramParams::searchNamedAutoConstant( const char *name, Uint* position )
{
    int i = mAutoUniformCount;
    while( i )
    {
        i--;
        if( !strncmp((const char *)mAutoUniformEntries[i]->name, name, MAX_NAME_LEN) )
        {
            if( position )
                *position = i;
            return true;
        }
    }
    
    if( position )
        *position = 0;
    return false;
}

void ShaderProgramParams::setNamedAutoConstant ( AutoConstanType type, char *name )
{
    if( searchNamedAutoConstant(name, 0) )
    {
        TOY3D_PRINT("setNamedAutoConstant failed. AutoConst name exist.", __FILE__, __LINE__);
        return;
    }

    AutoParamEntry *entry = new AutoParamEntry(type, name );
    mAutoUniformEntries[mAutoUniformCount++] = entry;

    return;
}

void ShaderProgramParams::updateAutoConstIndex ( const char *name, Uint index )
{
    Uint position = 0;
    if( !searchNamedAutoConstant(name, &position) )
    {
        TOY3D_PRINT("updateAutoConstIndex failed. AutoConst name doesn't exist.", __FILE__, __LINE__);
        return;
    }

    mAutoUniformEntries[position]->index = index;
    
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

void ShaderProgramParams::updateAutoUniformConst ( AutoParamDataSource *source )
{
    Uint i;
    AutoParamEntry *tempACE;
    for ( i=0; i<mAutoUniformCount; i++ )
    {
        tempACE = mAutoUniformEntries[i];
        switch( mAutoUniformEntries[i]->type )
        {
        case TOY3D_ACT_WORLD_MATRIX:
            setAutoUniformConstant( mAutoUniformEntries[i]->index, source->getWorldMatrix() );
            break;

        case TOY3D_ACT_PROJECTION_MATRIX:
            setAutoUniformConstant( mAutoUniformEntries[i]->index, source->getProjectionMatrix() );
            break;

        case TOY3D_ACT_VIEW_MATRIX:
            setAutoUniformConstant( mAutoUniformEntries[i]->index, source->getViewMatrix() );
            break;

        //case TOY3D_ACT_SAMPLER2D:
        //    setAutoUniformConstant( mAutoUniformEntries[i]->index, source->getTextureUnit());
        //    break;

        default:
            break;
        }
    }
    return;
}

Uint ShaderProgramParams::getAutoConstCount()
{
    return mAutoUniformCount;
}

const char* ShaderProgramParams::getAutoConstName( Uint position )
{
    return (const char *)mAutoUniformEntries[position]->name;
}
/* Auto Uniform Parameter Methods -------------------------------end   */

/* Attribution Parameter Methods -------------------------------start */
Bool ShaderProgramParams::searchNamedAttrConstant( const char *name, Uint* position )
{
    int i = mAttrCount;
    while( i )
    {
        i--;
        if( !strncmp((const char *)mAttrEntries[i]->name, name, MAX_NAME_LEN) )
        {
            if( position )
                *position = i;
            return true;
        }
    }
    
    if( position )
        *position = 0;
    return false;
}

void ShaderProgramParams::setNamedAttrConstant ( AttrConstantType type, char *name )
{
    if( searchNamedAttrConstant(name, 0) )
    {
        TOY3D_PRINT("setNamedAttrConstant failed. Auto Constant name exist.", __FILE__, __LINE__);
        return;
    }

    AttrParamEntry *entry = new AttrParamEntry(type, name );
    mAttrEntries[mAttrCount++] = entry;

    return;
}

void ShaderProgramParams::updateAttrConstIndex ( const char *name, Uint index )
{
    Uint position = 0;
    if( !searchNamedAttrConstant(name, &position) )
    {
        TOY3D_PRINT("updateAttrConstIndex failed. Attribution Constant name doesn't exist.", __FILE__, __LINE__);
        return;
    }
    
    mAttrEntries[position]->index = index;
    
    return;
}

Uint ShaderProgramParams::getAttrConstCount()
{
    return mAttrCount;
}

const char* ShaderProgramParams::getAttrConstName( Uint position )
{
    return (const char*)mAttrEntries[position]->name;
}

//-1->no constant exist
int ShaderProgramParams::getAttrConstIndex( AttrConstantType type )
{
    for (Uint i=0; i<mAttrCount; i++)
    {
        if( mAttrEntries[i]->type == type)
            return mAttrEntries[i]->index;
    }

    return TOY3D_ERROR;
}
/* Attribution Parameter Methods -------------------------------end   */

/* Custom Uniform Parameter Methods -------------------------------start */

/* flag : true->search int entries, false->search real entries. */
Bool ShaderProgramParams::searchNamedCustConstant(Bool flag, const char *name, Uint *position )
{
    int i;

    if( TRUE == flag )
    {
        i = mIntUniformCount;
        while( i )
        {
            i--;
            if( !strncmp((const char *)mIntUniformEntries[i]->name, name, MAX_NAME_LEN) )
            {
                if( position )
                    *position = i;
                return true;
            }
        }
    }
    else
    {
        i = mRealUniformCount;
        while( i )
        {
            i--;
            if( !strncmp((const char *)mRealUniformEntries[i]->name, name, MAX_NAME_LEN) )
            {
                if( position )
                    *position = i;
                return true;
            }
        }
    }

    if( position )
        *position = 0;

    return false;
}

void ShaderProgramParams::setNamedCustUniformConstant(CustUniformConstanType type, char *name , int value)
{
    if( searchNamedCustConstant( TRUE, name, 0) )
    {
        TOY3D_PRINT("setNamedAutoConstant failed. Custom constant name exist.", __FILE__, __LINE__);
        return;
    }

    IntParamEntry *entry = new IntParamEntry(type, name, value);
    mIntUniformEntries[mIntUniformCount++] = entry;

    return;
}

void ShaderProgramParams::setNamedCustUniformConstant( CustUniformConstanType type, char *name , Real value)
{
    if( searchNamedCustConstant( FALSE, name, 0) )
    {
        TOY3D_PRINT("setNamedAutoConstant failed. Custom constant name exist.", __FILE__, __LINE__);
        return;
    }

    RealParamEntry *entry = new RealParamEntry(type, name, value);
    mRealUniformEntries[mRealUniformCount++] = entry;

    return;
}

/*
void ShaderProgramParams::updateCustUniformIndex ( const char *name, Uint index )
{
    Uint position = 0;
    if( searchNamedCustConstant(TRUE, name, &position) )
    {
        mIntUniformEntries[position]->index = index;
        return;
    }
    else if( searchNamedCustConstant(FALSE, name, &position) )
    {
        mRealUniformEntries[position]->index = index;
        return;
    }

    TOY3D_PRINT("updateCustUniformIndex failed. Custom Constant name doesn't exist.", __FILE__, __LINE__);
    return;
}
*/

void ShaderProgramParams::updateCustIntUniformIndex ( const char *name, Uint index )
{
    Uint position = 0;

    if( searchNamedCustConstant(TRUE, name, &position) )
    {
        mIntUniformEntries[position]->index = index;
        return;
    }
    
    TOY3D_PRINT("updateCustUniformIndex failed. Custom Constant name doesn't exist.", __FILE__, __LINE__);
    return;
}

void ShaderProgramParams::updateCustRealUniformIndex ( const char *name, Uint index )
{
    Uint position = 0;
    
    if( searchNamedCustConstant(FALSE, name, &position) )
    {
        mRealUniformEntries[position]->index = index;
        return;
    }
    
    TOY3D_PRINT("updateCustUniformIndex failed. Custom Constant name doesn't exist.", __FILE__, __LINE__);
    return;
}

void ShaderProgramParams::updateCustUniformConst()
{
    Uint i;

    for ( i=0; i<mIntUniformCount; i++ )
    {
        switch( mIntUniformEntries[i]->type )
        {
        case TOY3D_CUST_INT1:
        case TOY3D_CUST_SAMPLER1D:
        case TOY3D_CUST_SAMPLER2D:
        case TOY3D_CUST_SAMPLER3D:
            glUniform1i(mIntUniformEntries[i]->index, mIntUniformEntries[i]->value);
            break;

        case TOY3D_CUST_INT2:
        case TOY3D_CUST_INT3:
        case TOY3D_CUST_INT4:
        case TOY3D_CUST_MATRIX_2:
        case TOY3D_CUST_MATRIX_3:
        case TOY3D_CUST_MATRIX_4:
        case TOY3D_CUST_VEC_2:
        case TOY3D_CUST_VEC_3:
        case TOY3D_CUST_VEC_4:
        case TOY3D_CUST_UNKNOWN:
            TOY3D_TIPS("Warning: It could do nothing now.\n");
            break;

        default:
            break;
        }
    }

    for ( i=0; i<mRealUniformCount; i++ )
    {
        switch( mRealUniformEntries[i]->type )
        {
        case TOY3D_CUST_REAL1:
            glUniform1f(mRealUniformEntries[i]->index, mRealUniformEntries[i]->value);
            break;

        case TOY3D_CUST_REAL2:
        case TOY3D_CUST_REAL3:
        case TOY3D_CUST_REAL4:
        case TOY3D_CUST_MATRIX_2:
        case TOY3D_CUST_MATRIX_3:
        case TOY3D_CUST_MATRIX_4:
        case TOY3D_CUST_VEC_2:
        case TOY3D_CUST_VEC_3:
        case TOY3D_CUST_VEC_4:
        case TOY3D_CUST_UNKNOWN:
            TOY3D_TIPS("Warning: It could do nothing now.\n");
            break;

        default:
            break;
        }
    }

    return;
}

Uint ShaderProgramParams::getCustIntCount()
{
    return mIntUniformCount;
}

Uint ShaderProgramParams::getCustRealCount()
{
    return mRealUniformCount;
}

const char* ShaderProgramParams::getCustIntConstName( Uint position )
{
    return (const char *)mIntUniformEntries[position]->name;
}

const char* ShaderProgramParams::getCustRealConstName( Uint position )
{
    return (const char *)mRealUniformEntries[position]->name;
}

//-1->no constant exist
int ShaderProgramParams::getSampler2DValue()
{
    for (Uint i=0; i<mIntUniformCount; i++)
    {
        if( mIntUniformEntries[i]->type == TOY3D_CUST_SAMPLER2D)
            return mIntUniformEntries[i]->value;
    }

    return TOY3D_ERROR;
}
/* Custom Uniform Parameter Methods -------------------------------end   */



TOY3D_END_NAMESPACE

