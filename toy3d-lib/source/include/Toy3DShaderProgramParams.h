
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
            //����ָ�����ֵı����Ƿ���ڣ���ȡ�������б��е�λ��
            Bool searchNamedAutoConst( const char *name, Uint* index );
            Bool searchNamedAttrConst( const char *name, Uint* index );

        public:
            ShaderProgramParams();
            ~ShaderProgramParams();

            void setAutoConstValue( Uint index, const Real value[MATRIX_4x4_SIZE] );
            void setNamedAutoConstant ( AutoConstantType type, char *name );
            void updateAutoConstParams ( AutoParamDataSource *source );
            //�ɵ��������ñ�������
            void updateAutoConstIndex ( const char *name, Uint index );

            Uint getAutoEntryCount();
            const char* getAutoParamName( Uint index );

            void setNamedAttrConstant ( AttrConstantType type, char *name );
            void updateAttrConstIndex ( const char *name, Uint index );

            Uint getAttrEntryCount();
            const char* getAttrParamName( Uint index );
            Uint getAttrConstIndex( AttrConstantType type );

            //ͨ��shader program id ��ȡ��������
            //void ShaderProgramParams::updateAutoConstIndex_2 ( const Uchar *name, Uint shaderProgID );
    };


TOY3D_END_NAMESPACE

#endif 
