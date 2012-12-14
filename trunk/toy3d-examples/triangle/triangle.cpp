
// #include <GL/glew.h>
// #include <GL/glut.h>


#include <toy3d/Toy3DCommon.h>
#include <toy3d/Toy3DWorld.h>
#include <toy3d/Toy3DShaderProgramParams.h>


#define WINDOW_W    500 
#define WINDOW_H    500 


#ifdef VC6
#define SHADER_VERT_FILE "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/triangle/triangle.glslv"
#define SHADER_FRAG_FILE "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/triangle/triangle.glslf"
#else 
#define SHADER_VERT_FILE "/usr/local/share/toy3d/triangle/triangle.glslv"
#define SHADER_FRAG_FILE "/usr/local/share/toy3d/triangle/triangle.glslf"
#endif


using namespace TOY3D;

#define VERTEX_COUNT 3 

Real vertices[VERTEX_COUNT * 3] = {
    0.0f, 0.5f, 0.0f,
    -0.5f,  -0.5f, 0.0f,
    0.5f, -0.5f,  0.0f,
};

World *world = NULL;


void display()
{

    world->startRendering (); 

	glFlush();
    glutSwapBuffers ();
}

void init()
{

    world = new World ();
    world->setSize(WINDOW_W, WINDOW_H);
    world->setBackColor (1.0, 1.0, 1.0, 1.0);  //white back color


    ShaderProgram* shaderProgram = world->createShaderProgram();
    shaderProgram->loadShaderSource (SHADER_VERT_FILE, SHADER_FRAG_FILE);


    ShaderProgramParams *params = new ShaderProgramParams ();
    //no shader uniforms ...
    //shader attributes
    params->setNamedAttrConstant (TOY3D_ATTR_VERTEX_INDEX, "vPosition");
    shaderProgram->bindShaderParameters(params);


    Mesh *mesh = world->createMesh();
    mesh->setVertices (vertices, VERTEX_COUNT);
    mesh->setRenderMode (TOY3D_TRIANGLE_STRIP);


}

void keyboard(unsigned char key, int x, int y){
  switch(key) {
    case 'q': case 'Q': case 27:
      exit(0);
      break;
  }
}

int main(int argc, char** argv){

	glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  	glutInitWindowSize(WINDOW_W, WINDOW_H);
  	glutInitWindowPosition(0,0);
  	glutCreateWindow("triangle");
  	glutDisplayFunc(display);
	glutIdleFunc(display);
  	glutKeyboardFunc(keyboard);



    glewInit();
    if (glewIsSupported("GL_VERSION_2_0"))
        printf("Ready for OpenGL 2.0\n");
    else {
        printf("OpenGL 2.0 not supported\n");
        exit(1);
    }



  	init();
  	glutMainLoop();

  	return 0;
}

