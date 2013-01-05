
#ifndef _TOY3D_AUTO_PARAM_DATA_SOURCE_H
#define _TOY3D_AUTO_PARAM_DATA_SOURCE_H


#include <stdio.h>
#include <stdlib.h>


#include "Toy3DCommon.h"

TOY3D_BEGIN_NAMESPACE

    class AutoParamDataSource
    {
    protected:
        mutable Real mWorldMatrix[MATRIX_4x4_SIZE];
        mutable Real mProjectionMatrix[MATRIX_4x4_SIZE];
        mutable Real mViewMatrix[MATRIX_4x4_SIZE];
        mutable Uint mTextureUnit;
        
    public:
        AutoParamDataSource();
        ~AutoParamDataSource();

        void setWorldMatrix( Real matrix[MATRIX_4x4_SIZE] );
        void setProjectionMatrix( Real matrix[MATRIX_4x4_SIZE] );
        void setViewMatrix( Real matrix[MATRIX_4x4_SIZE] );
        //void setTextureUnit(Uint texUnit);

        const Real* getWorldMatrix(void) const;
        const Real* getProjectionMatrix(void) const;
        const Real* getViewMatrix(void) const;
        //const Uint getTextureUnit() const;
    };


TOY3D_END_NAMESPACE

#endif 
