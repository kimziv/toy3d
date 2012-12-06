
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} GLEW32 GLUT32)
#set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY})


add_executable (rectangle rectangle.cpp)
target_link_libraries (rectangle toy3d ${CORELIBS})


install (TARGETS rectangle 
	RUNTIME DESTINATION bin
	)



