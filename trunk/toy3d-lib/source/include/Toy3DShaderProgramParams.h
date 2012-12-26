
#ifndef _TOY3D_SHADER_PROGRAM_PARAMS_H
#define _TOY3D_SHADER_PROGRAM_PARAMS_H


#include <stdio.h>
#include <stdlib.h>


#include "Toy3DCommon.h"
#include "Toy3DAutoParamDataSource.h"

TOY3D_BEGIN_NAMESPACE


    class AutoConstEntry
    {
    public:
        AutoConstantType type;
        char name[MAX_NAME_LEN];
        Uint  index;
        
        //AutoConstEntry(AutoConstantType theType, Uchar *theName, Uint theIndex);
        AutoConstEntry(AutoConstantType theType, char *theName );
    };

    class AttrConstEntry
    {
    public:
        AttrConstantType type;
        char name[MAX_NAME_LEN];
        Uint  index;
        
        //AutoConstEntry(AutoConstantType theType, Uchar *theName, Uint theIndex);
        AttrConstEntry(AttrConstantType theType, char *theName );
    };

    class ShaderProgramParams
    {
        protected:
            AutoConstEntry* mAutoConstEntries[MAX_AUTOENTRY_COUNT];
            AttrConstEntry* mAttrConstEntries[MAX_AUTOENTRY_COUNT];
            Uint mAutoCount;
            Uint mAttrCount;

        private:
            //Search the name of the designated variables, if exist, get its position in the name list.
            Bool searchNamedAutoConst( const char *name, Uint *index );
            Bool searchNamedAttrConst( const char *name, Uint *index );
            Bool searchCustomAttrConst( const char *name, Uint *index );

        public:
            ShaderProgramParams();
            ~ShaderProgramParams();

            //////////////////////////////////////////////////////////////////////////
            //Auto Constant Methods
            void setAutoConstValue( Uint index, const Real value[MATRIX_4x4_SIZE] );
            void setAutoConstValue( Uint index, const Uint texUnit );
            void setNamedAutoConstant ( AutoConstantType type, char *name );
            void updateAutoConstParams ( AutoParamDataSource *source );
            void updateAutoConstIndex ( const char *name, Uint index );

            Uint getAutoEntryCount();
            const char* getAutoParamName( Uint index );

            //////////////////////////////////////////////////////////////////////////
            //Attribute Constant Method
            void setNamedAttrConstant ( AttrConstantType type, char *name );
            void updateAttrConstIndex ( const char *name, Uint index );

            Uint getAttrEntryCount();
            const char* getAttrParamName( Uint index );
            Uint getAttrConstIndex( AttrConstantType type );

            //void ShaderProgramParams::updateAutoConstIndex_2 ( const Uchar *name, Uint shaderProgID );
#if 0
            //////////////////////////////////////////////////////////////////////////
            //Customed Constant Methods
            void setNamedCustomConstant ( AttrConstantType type, char *name );
            void updateCustomConstIndex ( const char *name, Uint index );
            
            Uint getCustomEntryCount();
            const char* getCustomParamName( Uint index );
            Uint getCustomConstIndex( AttrConstantType type );
#endif
    };


TOY3D_END_NAMESPACE

#endif 
