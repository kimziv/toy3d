
#ifndef _TOY3D_SHADER_PROGRAM_PARAMS_H
#define _TOY3D_SHADER_PROGRAM_PARAMS_H


#include <stdio.h>
#include <stdlib.h>


#include "Toy3DCommon.h"
#include "Toy3DAutoParamDataSource.h"

TOY3D_BEGIN_NAMESPACE


    class AutoParamEntry
    {
    public:
        AutoConstanType type;
        char name[MAX_NAME_LEN];
        Uint  index;
        
        //AutoConstEntry(AutoConstantType theType, Uchar *theName, Uint theIndex);
        AutoParamEntry(AutoConstanType theType, char *theName );
    };


    class AttrParamEntry
    {
    public:
        AttrConstantType type;
        char name[MAX_NAME_LEN];
        Uint  index;
        
        //AutoConstEntry(AutoConstantType theType, Uchar *theName, Uint theIndex);
        AttrParamEntry(AttrConstantType theType, char *theName );
    };

    class IntParamEntry
    {
    public:
        CustUniformConstanType type;
        char name[MAX_NAME_LEN];
        //int  value[CUSTOM_UNIT_SIZE];
        int  value;
        Uint index;
        
        IntParamEntry(CustUniformConstanType theType, char *theName, int theVal);
    };

    class RealParamEntry
    {
    public:
        CustUniformConstanType type;
        char name[MAX_NAME_LEN];
        //Real value[CUSTOM_UNIT_SIZE];
        Real value;
        Uint index;
        
        RealParamEntry(CustUniformConstanType theType, char *theName, Real theVal);
    };

    class ShaderProgramParams
    {
        protected:
            /* auto uniform constant list */
            AutoParamEntry *mAutoUniformEntries[MAX_AUTOENTRY_COUNT];
            /* attribution constant list */
            AttrParamEntry *mAttrEntries[MAX_ATTRENTRY_COUNT];
            /* custom uniform constant list */
            IntParamEntry   *mIntUniformEntries[MAX_CUSTENTRY_COUNT];
            RealParamEntry  *mRealUniformEntries[MAX_CUSTENTRY_COUNT];

            Uint mAutoUniformCount;
            Uint mAttrCount;
            Uint mIntUniformCount;
            Uint mRealUniformCount;

        private:
            /* 
             *  Search the name of the designated variables.
             *  If exist, get its position in the name list.
             */
            Bool searchNamedAutoConstant( const char *name, Uint *position );
            Bool searchNamedAttrConstant( const char *name, Uint *position );
            Bool searchNamedCustConstant( Bool flag, const char *name, Uint *position );

        public:
            ShaderProgramParams();
            ~ShaderProgramParams();

            /* Auto Uniform Parameter Methods -------------------------------start */
            void setAutoUniformConstant( Uint index, const Real value[MATRIX_4x4_SIZE] );
            void setAutoUniformConstant( Uint index, const Uint texUnit );
            void setNamedAutoConstant( AutoConstanType type, char *name );
            void updateAutoUniformConst( AutoParamDataSource *source );
            void updateAutoConstIndex( const char *name, Uint index );

            Uint getAutoConstCount();
            const char* getAutoConstName( Uint position );
            /* Auto Uniform Parameter Methods -------------------------------end   */

            /* Attribution Parameter Methods -------------------------------start */
            void setNamedAttrConstant( AttrConstantType type, char *name );
            void updateAttrConstIndex( const char *name, Uint index );

            Uint getAttrConstCount();
            const char* getAttrConstName( Uint position );
            int getAttrConstIndex( AttrConstantType type );
            /* Attribution Parameter Methods -------------------------------end   */

            /* Custom Parameter Methods -------------------------------start */
            void setNamedCustUniformConstant( CustUniformConstanType type, char *name , int value);
            void setNamedCustUniformConstant( CustUniformConstanType type, char *name , Real value);
            //void updateCustUniformIndex ( const char *name, Uint index );
            void updateCustIntUniformIndex ( const char *name, Uint index );
            void updateCustRealUniformIndex ( const char *name, Uint index );
            void updateCustUniformConst();

            Uint getCustIntCount();
            Uint getCustRealCount();
            const char* getCustIntConstName( Uint position );
            const char* getCustRealConstName( Uint position );
            /* Custom Parameter Methods -------------------------------end   */
    };


TOY3D_END_NAMESPACE

#endif 
