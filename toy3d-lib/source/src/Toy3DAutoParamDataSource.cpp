#include "Toy3DAutoParamDataSource.h"

TOY3D_BEGIN_NAMESPACE

AutoParamDataSource::AutoParamDataSource()
{
    memset( mWorldMatrix,      0, sizeof(Real)*MATRIX_4x4_SIZE );
    memset( mProjectionMatrix, 0, sizeof(Real)*MATRIX_4x4_SIZE );
    memset( mViewMatrix,       0, sizeof(Real)*MATRIX_4x4_SIZE );
}

AutoParamDataSource::~AutoParamDataSource()
{
}

void AutoParamDataSource::setWorldMatrix( Real matrix[MATRIX_4x4_SIZE] )
{
    memcpy( mWorldMatrix, matrix, MATRIX_4x4_SIZE*sizeof(Real) );
}

void AutoParamDataSource::setProjectionMatrix( Real matrix[MATRIX_4x4_SIZE] )
{
    memcpy( mProjectionMatrix, matrix, MATRIX_4x4_SIZE*sizeof(Real) );

#if 0
    int i = 0;
    printf ("data source projection marix:\n");
    for (i = 0; i < MATRIX_4x4_SIZE; i++)
        printf ("%f,", mProjectionMatrix[i]);
    printf ("\n");
#endif

}

void AutoParamDataSource::setViewMatrix( Real matrix[MATRIX_4x4_SIZE] )
{
    memcpy( mViewMatrix, matrix, MATRIX_4x4_SIZE*sizeof(Real) );
}

/*
void AutoParamDataSource::setTextureUnit(Uint texUnit)
{
    mTextureUnit = texUnit;
    return;
}
*/

const Real* AutoParamDataSource::getWorldMatrix(void) const
{
    return mWorldMatrix;
}

const Real* AutoParamDataSource::getProjectionMatrix(void) const
{
    return mProjectionMatrix;
}

const Real* AutoParamDataSource::getViewMatrix(void) const
{
    return mViewMatrix;
}
/*
const Uint AutoParamDataSource::getTextureUnit() const
{
    return mTextureUnit;
}
*/



TOY3D_END_NAMESPACE
