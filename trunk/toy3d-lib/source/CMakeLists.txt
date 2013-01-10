


	set(HEADER_FILES
		include/Toy3DCommon.h
		include/Toy3DWorld.h
		include/Toy3DCamera.h
		include/Toy3DAutoParamDataSource.h
		include/Toy3DShaderProgramParams.h
		include/Toy3DShaderProgram.h
		include/Toy3DShaderProgramManager.h
		include/Toy3DMesh.h
		include/Toy3DMeshManager.h
		include/Toy3DEntity.h
		include/Toy3DMaterial.h
		include/Toy3DMaterialManager.h
		include/Toy3DRenderer.h
		include/Toy3DRenderOperation.h
		include/Toy3DMath.h
		include/Toy3DImage.h
		include/Toy3DTexture.h
		include/Toy3DTextureManager.h
		include/Toy3DPtrArray.h
	)

	set(SOURCE_FILES
		src/Toy3DWorld.cpp
		src/Toy3DCamera.cpp
		src/Toy3DAutoParamDataSource.cpp
		src/Toy3DShaderProgramParams.cpp
		src/Toy3DShaderProgram.cpp
		src/Toy3DShaderProgramManager.cpp
		src/Toy3DMesh.cpp
		src/Toy3DMeshManager.cpp
		src/Toy3DEntity.cpp
		src/Toy3DMaterial.cpp
		src/Toy3DMaterialManager.cpp
		src/Toy3DRenderer.cpp
		src/Toy3DRenderOperation.cpp
		src/Toy3DMath.c
		src/Toy3DImage.cpp
		src/Toy3DTexture.cpp
		src/Toy3DTextureManager.cpp
		src/Toy3DPtrArray.cpp
	)

	include_directories(
  		${CMAKE_CURRENT_SOURCE_DIR}/include
	)

if (WIN32)
    set(PLATFORM_LIBS GLEW32 GLUT32)
elseif (APPLE)

elseif (UNIX)
    set(PLATFORM_LIBS m GLEW)
endif(WIN32)



#	SET (CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m GLEW)
#	SET (CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} GLEW32 GLUT32)
#	SET (CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} )

	SET (CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${PLATFORM_LIBS})







ADD_LIBRARY (toy3d SHARED ${HEADER_FILES} ${SOURCE_FILES} )
ADD_LIBRARY (toy3d_static STATIC ${SOURCE_FILES} ${HEADER_FILES})
SET_TARGET_PROPERTIES (toy3d PROPERTIES  OUTPUT_NAME "toy3d")
SET_TARGET_PROPERTIES (toy3d_static PROPERTIES OUTPUT_NAME "toy3d")
SET_TARGET_PROPERTIES (toy3d PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES (toy3d_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES (toy3d PROPERTIES VERSION 1.2 SOVERSION 1)

TARGET_LINK_LIBRARIES(toy3d ${CORELIBS})
TARGET_LINK_LIBRARIES(toy3d_static ${CORELIBS})


INSTALL (TARGETS toy3d toy3d_static 
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

INSTALL (FILES ${HEADER_FILES} DESTINATION include/toy3d)

