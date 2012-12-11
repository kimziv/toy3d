
#ifndef _TOY3D_SHADER_PROGRAM_PARAMS_H
#define _TOY3D_SHADER_PROGRAM_PARAMS_H


#include <stdio.h>
#include <stdlib.h>


#include "Toy3DCommon.h"
#include "Toy3DAutoParamDataSource.h"

TOY3D_BEGIN_NAMESPACE

    enum AutoConstantType
    {
        TOY3D_ACT_WORLD_MATRIX,
        TOY3D_ACT_VIEW_MATRIX, 
        TOY3D_ACT_PROJECTION_MATRIX
    };

    enum AttrConstantType
    {
        TOY3D_ATTR_VERTEX_INDEX,
        TOY3D_ATTR_COLOR_INDEX, 
        TOY3D_ATTR_UV_INDEX,
        TOY3D_ATTR_NORMAL_INDEX
    };

    class AutoConstEntry
    {
    public:
        AutoConstantType type;
        Uchar name[MAX_NAME_LEN];
        Uint  index;
        
        //AutoConstEntry(AutoConstantType theType, Uchar *theName, Uint theIndex);
        AutoConstEntry(AutoConstantType theType, Uchar *theName );
    };

    class AttrConstEntry
    {
    public:
        AttrConstantType type;
        Uchar name[MAX_NAME_LEN];
        Uint  index;
        
        //AutoConstEntry(AutoConstantType theType, Uchar *theName, Uint theIndex);
        AttrConstEntry(AttrConstantType theType, Uchar *theName );
    };

    class ShaderProgramParams
    {
        protected:
            AutoConstEntry* mAutoConstEntries[MAX_AUTOENTRY_COUNT];
            AttrConstEntry* mAttrConstEntries[MAX_AUTOENTRY_COUNT];
            Uint mAutoCount;
            Uint mAttrCount;

        private:
            //查找指定名字的变量是否存在，并取得其在列表中的位置
            Bool searchNamedConst( const Uchar *name, Uint* index );

        public:
            ShaderProgramParams();
            ~ShaderProgramParams();

            void setAutoConstValue( Uint index, const Real value[MATRIX_4x4_SIZE] );
            void setNamedAutoConstant ( AutoConstantType type, Uchar *name );
            void updateAutoConstParams ( AutoParamDataSource *source );
            Uint getAutoEntryCount();
            Uchar* getAutoParamName( Uint index );

            void setNamedAttrConstant ( AttrConstantType type, Uchar *name );
            Uint getAttrEntryCount();
            Uchar* getAttrParamName( Uint index );
            Uint getAttrConstIndex( AttrConstantType type );

            //由调用者设置变量索引
            void updateAutoConstIndex ( Uchar *name, Uint index );
            //通过shader program id 获取变量索引
            //void ShaderProgramParams::updateAutoConstIndex_2 ( const Uchar *name, Uint shaderProgID );
    };


TOY3D_END_NAMESPACE

#endif 
