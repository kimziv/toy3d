
if (WIN32)
    set(PLATFORM_LIBS GLEW32 GLUT32)
elseif (APPLE)

elseif (UNIX)
    set(PLATFORM_LIBS m GLEW)
endif(WIN32)


set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${PLATFORM_LIBS})


add_executable (fbo_map fbo_map.cpp myapp.cpp)
target_link_libraries (fbo_map toy3d ${CORELIBS})


install (TARGETS fbo_map
	RUNTIME DESTINATION bin
	)

install (DIRECTORY res/ DESTINATION share/toy3d/fbo_map)

