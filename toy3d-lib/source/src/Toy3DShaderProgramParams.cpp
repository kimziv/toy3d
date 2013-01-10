
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
    /*
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
    */

    mPtrAryAutoUnif = new TPtrArray();
    mPtrAryAttr     = new TPtrArray();
    mPtrAryIntUnif  = new TPtrArray();
    mPtrAryRealUnif = new TPtrArray();

    mPtrAryAutoUnif->create();
    mPtrAryAttr->create();
    mPtrAryIntUnif->create();
    mPtrAryRealUnif->create();
}

ShaderProgramParams::~ShaderProgramParams()
{
    Uint length;

    AutoParamEntry *pTemp1;
    length = mPtrAryAutoUnif->getLength();
    while(length--)
    {
        pTemp1 = (AutoParamEntry *)mPtrAryAutoUnif->getElement(length);
        DELETEANDNULL(pTemp1);
        //mPtrArray->setElement(NULL, length);
    }
    mPtrAryAutoUnif->destroy();
    delete mPtrAryAutoUnif;

    AttrParamEntry *pTemp2;
    length = mPtrAryAttr->getLength();
    while(length--)
    {
        pTemp2 = (AttrParamEntry *)mPtrAryAttr->getElement(length);
        DELETEANDNULL(pTemp2);
        //mPtrArray->setElement(NULL, length);
    }
    mPtrAryAttr->destroy();
    delete mPtrAryAttr;

    IntParamEntry *pTemp3;
    length = mPtrAryIntUnif->getLength();
    while(length--)
    {
        pTemp3 = (IntParamEntry *)mPtrAryIntUnif->getElement(length);
        DELETEANDNULL(pTemp3);
        //mPtrArray->setElement(NULL, length);
    }
    mPtrAryIntUnif->destroy();
    delete mPtrAryIntUnif;

    RealParamEntry *pTemp4;
    length = mPtrAryRealUnif->getLength();
    while(length--)
    {
        pTemp4 = (RealParamEntry *)mPtrAryRealUnif->getElement(length);
        DELETEANDNULL(pTemp4);
        //mPtrArray->setElement(NULL, length);
    }
    mPtrAryRealUnif->destroy();
    delete mPtrAryRealUnif;
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
    int i = mPtrAryAutoUnif->getLength();
    AutoParamEntry *pTemp;
    while( i )
    {
        i--;
        pTemp = (AutoParamEntry *)mPtrAryAutoUnif->getElement(i);
        if( pTemp )
        {
            if( !strncmp((const char *)pTemp->name, name, MAX_NAME_LEN) )
            {
                if( position )
                    *position = i;
                return TRUE;
            }
        }
    }
    
    if( position )
        *position = 0;
    return FALSE;
}

void ShaderProgramParams::setNamedAutoConstant ( AutoConstanType type, char *name )
{
    Bool rv;
    rv = searchNamedAutoConstant(name, 0);
    if( TRUE==rv )
    {
        TOY3D_PRINT("setNamedAutoConstant failed. AutoConst name exist.", __FILE__, __LINE__);
        return;
    }

    AutoParamEntry *entry = new AutoParamEntry(type, name );
    rv = mPtrAryAutoUnif->append( (TPointer)entry );
    if(TRUE!=rv)
    {
        TOY3D_TIPS("Error: Failed to store the pointer.\n");
        return;
    }

    return;
}

void ShaderProgramParams::updateAutoConstIndex ( const char *name, Uint index )
{
    Bool rv;
    Uint position = 0;
    AutoParamEntry *pTemp;

    rv = searchNamedAutoConstant(name, &position);
    if( TRUE!=rv )
    {
        TOY3D_PRINT("updateAutoConstIndex failed. AutoConst name doesn't exist.", __FILE__, __LINE__);
        return;
    }

    pTemp = (AutoParamEntry *)mPtrAryAutoUnif->getElement(position);
    /*
     * Though it can't be NULL, when you get TRUE from searchNamedAutoConstant,
     * it is suggested to finish the assignment as follows.
     */
    if( pTemp )
    {
        pTemp->index = index;
    }

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
    AutoParamEntry *pTemp;
    Uint length = mPtrAryAutoUnif->getLength();

    for ( i=0; i<length; i++ )
    {
        pTemp = (AutoParamEntry *)mPtrAryAutoUnif->getElement(i);
        if( pTemp )
        {
            switch( pTemp->type )
            {
            case TOY3D_ACT_WORLD_MATRIX:
                setAutoUniformConstant( pTemp->index, source->getWorldMatrix() );
                break;

            case TOY3D_ACT_PROJECTION_MATRIX:
                setAutoUniformConstant( pTemp->index, source->getProjectionMatrix() );
                break;

            case TOY3D_ACT_VIEW_MATRIX:
                setAutoUniformConstant( pTemp->index, source->getViewMatrix() );
                break;

                //case TOY3D_ACT_SAMPLER2D:
                //    setAutoUniformConstant( mAutoUniformEntries[i]->index, source->getTextureUnit());
                //    break;
                
            default:
                break;
            }
        }
    }
    return;
}

Uint ShaderProgramParams::getAutoConstCount()
{
    return mPtrAryAutoUnif->getLength();
}

const char* ShaderProgramParams::getAutoConstName( Uint position )
{
    AutoParamEntry *pTemp = (AutoParamEntry *)(*mPtrAryAutoUnif)[position];
    return (const char *)pTemp->name;
}
/* Auto Uniform Parameter Methods -------------------------------end   */

/* Attribution Parameter Methods -------------------------------start */
Bool ShaderProgramParams::searchNamedAttrConstant( const char *name, Uint* position )
{
    int i = mPtrAryAttr->getLength();
    AttrParamEntry *pTemp;

    while( i )
    {
        i--;

        pTemp = (AttrParamEntry *)mPtrAryAttr->getElement(i);
        if( pTemp )
        {
            if( !strncmp((const char *)pTemp->name, name, MAX_NAME_LEN) )
            {
                if( position )
                    *position = i;
                return TRUE;
            }
        }
    }
    
    if( position )
        *position = 0;
    return false;
}

void ShaderProgramParams::setNamedAttrConstant ( AttrConstantType type, char *name )
{
    Bool rv;

    rv = searchNamedAttrConstant(name, 0);
    if( TRUE==rv )
    {
        TOY3D_PRINT("setNamedAttrConstant failed. Auto Constant name exist.", __FILE__, __LINE__);
        return;
    }

    AttrParamEntry *entry = new AttrParamEntry(type, name );
    rv = mPtrAryAttr->append( (TPointer)entry );
    if(TRUE!=rv)
    {
        TOY3D_TIPS("Error: Failed to store the pointer.\n");
        return;
    }

    return;
}

void ShaderProgramParams::updateAttrConstIndex ( const char *name, Uint index )
{
    Bool rv;
    Uint position = 0;
    AttrParamEntry *pTemp;

    rv = searchNamedAttrConstant(name, &position);
    if( TRUE!=rv )
    {
        TOY3D_PRINT("updateAttrConstIndex failed. Attribution Constant name doesn't exist.", __FILE__, __LINE__);
        return;
    }

    pTemp = (AttrParamEntry *)mPtrAryAttr->getElement(position);
    if( pTemp )
    {
        pTemp->index = index;
    }
    
    return;
}

Uint ShaderProgramParams::getAttrConstCount()
{
    return mPtrAryAttr->getLength();
}

const char* ShaderProgramParams::getAttrConstName( Uint position )
{
    AttrParamEntry *pTemp = (AttrParamEntry *)(*mPtrAryAttr)[position];
    return (const char *)pTemp->name;
}

//-1->no constant exist
int ShaderProgramParams::getAttrConstIndex( AttrConstantType type )
{
    Uint i;
    Uint length = mPtrAryAttr->getLength();
    AttrParamEntry *pTemp;

    for(i=0; i<length; i++)
    {
        pTemp = (AttrParamEntry *)(*mPtrAryAttr)[i];
        if( pTemp->type == type)
            return pTemp->index;
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
        IntParamEntry *pTemp;
        i = mPtrAryIntUnif->getLength();
        while( i-- )
        {
            pTemp = (IntParamEntry *)mPtrAryIntUnif->getElement(i);
            if( pTemp )
            {
                if( !strncmp((const char *)pTemp->name, name, MAX_NAME_LEN) )
                {
                    if( position )
                        *position = i;
                    return TRUE;
                }
            }
        }
    }
    else
    {
        RealParamEntry *pTemp;
        i = mPtrAryRealUnif->getLength();
        while( i-- )
        {
            pTemp = (RealParamEntry *)mPtrAryRealUnif->getElement(i);
            if( pTemp )
            {
                if( !strncmp((const char *)pTemp->name, name, MAX_NAME_LEN) )
                {
                    if( position )
                        *position = i;
                    return TRUE;
                }
            }
        }
    }

    if( position )
        *position = 0;

    return FALSE;
}

void ShaderProgramParams::setNamedCustUniformConstant(CustUniformConstanType type, char *name , int value)
{
    Bool rv;

    rv = searchNamedCustConstant( TRUE, name, 0);
    if( TRUE==rv )
    {
        TOY3D_PRINT("setNamedAutoConstant failed. Custom constant name exist.", __FILE__, __LINE__);
        return;
    }

    IntParamEntry *entry = new IntParamEntry(type, name, value);
    rv = mPtrAryIntUnif->append( (TPointer)entry );
    if(TRUE!=rv)
    {
        TOY3D_TIPS("Error: Failed to store the pointer.\n");
        return;
    }

    return;
}

void ShaderProgramParams::setNamedCustUniformConstant( CustUniformConstanType type, char *name , Real value)
{
    Bool rv;
    
    rv = searchNamedCustConstant( FALSE, name, 0);
    if( TRUE==rv )
    {
        TOY3D_PRINT("setNamedAutoConstant failed. Custom constant name exist.", __FILE__, __LINE__);
        return;
    }
    
    RealParamEntry *entry = new RealParamEntry(type, name, value);
    rv = mPtrAryRealUnif->append( (TPointer)entry );
    if(TRUE!=rv)
    {
        TOY3D_TIPS("Error: Failed to store the pointer.\n");
        return;
    }

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
    Bool rv;
    Uint position = 0;
    IntParamEntry *pTemp;

    rv = searchNamedCustConstant(TRUE, name, &position);
    if( TRUE!=rv )
    {
        //printf("name = %s.\n", name );
        TOY3D_PRINT("updateCustIntUniformIndex failed. Custom Constant name doesn't exist.", __FILE__, __LINE__);
        return;
    }

    pTemp = (IntParamEntry *)mPtrAryIntUnif->getElement(position);
    if( pTemp )
    {
        pTemp->index = index;
    }

    return;
}

void ShaderProgramParams::updateCustRealUniformIndex ( const char *name, Uint index )
{
    Bool rv;
    Uint position = 0;
    RealParamEntry *pTemp;
    
    rv = searchNamedCustConstant(FALSE, name, &position);
    if( TRUE!=rv )
    {
        //printf("name = %s.\n", name );
        TOY3D_PRINT("updateCustRealUniformIndex failed. Custom Constant name doesn't exist.", __FILE__, __LINE__);
        return;
    }

    pTemp = (RealParamEntry *)mPtrAryRealUnif->getElement(position);
    if( pTemp )
    {
        pTemp->index = index;
    }

    return;
}

void ShaderProgramParams::updateCustUniformConst()
{
    Uint i, length;
    IntParamEntry  *pTempi;
    RealParamEntry *pTempr;

    length = mPtrAryIntUnif->getLength();
    for ( i=0; i<length; i++ )
    {
        pTempi = (IntParamEntry  *)mPtrAryIntUnif->getElement(i);
        switch( pTempi->type )
        {
        case TOY3D_CUST_INT1:
        case TOY3D_CUST_SAMPLER1D:
        case TOY3D_CUST_SAMPLER2D:
        case TOY3D_CUST_SAMPLER3D:
            glUniform1i(pTempi->index, pTempi->value);
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
            TOY3D_TIPS("Warning: It does nothing now.\n");
            break;

        default:
            break;
        }
    }

    length = mPtrAryRealUnif->getLength();
    for ( i=0; i<length; i++ )
    {
        pTempr = (RealParamEntry*)mPtrAryRealUnif->getElement(i);
        switch( pTempr->type )
        {
        case TOY3D_CUST_REAL1:
            glUniform1f(pTempr->index, pTempr->value);
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
            TOY3D_TIPS("Warning: It does nothing now.\n");
            break;

        default:
            break;
        }
    }

    return;
}

Uint ShaderProgramParams::getCustIntCount()
{
    return mPtrAryIntUnif->getLength();
}

Uint ShaderProgramParams::getCustRealCount()
{
    return mPtrAryRealUnif->getLength();
}

const char* ShaderProgramParams::getCustIntConstName( Uint position )
{
    IntParamEntry *pTemp = (IntParamEntry *)(*mPtrAryIntUnif)[position];
    return (const char *)pTemp->name;
}

const char* ShaderProgramParams::getCustRealConstName( Uint position )
{
    RealParamEntry *pTemp = (RealParamEntry *)(*mPtrAryRealUnif)[position];
    return (const char *)pTemp->name;
}

//-1->no constant exist
int ShaderProgramParams::getSampler2DValue()
{
    Uint i, length;
    IntParamEntry *pTemp;

    length = mPtrAryIntUnif->getLength();
    for (i=0; i<length; i++)
    {
        pTemp = (IntParamEntry *)(*mPtrAryIntUnif)[i];
        if(pTemp->type == TOY3D_CUST_SAMPLER2D)
            return pTemp->value;
    }

    return TOY3D_ERROR;
}
/* Custom Uniform Parameter Methods -------------------------------end   */



TOY3D_END_NAMESPACE

