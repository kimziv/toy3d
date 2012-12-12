
#include <GL/glew.h>
#include <GL/glut.h>


#include <toy3d/Toy3DCommon.h>
#include <toy3d/Toy3DWorld.h>
#include <toy3d/Toy3DShaderProgramParams.h>
#include "data.h"


#define WINDOW_W    500
#define WINDOW_H    500

using namespace TOY3D;

#define VERTEX_COUNT  6

Real vertices[VERTEX_COUNT * 3] = {
    -1.0f, -1.0f, 0.0f,
    1.0f,  -1.0f, 0.0f,
    -1.0f, 1.0f,  0.0f,
    
    1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f
};

World *world = NULL;


void display()
{

    world->startRendering (); 

	glFlush();
}

void init()
{
    world = new World ();
    Real aspect;
    const Real nearz  = 1.0f;//5.0f;
    const Real farz   = 1000.0f;//60.0f;

    Camera *camera = world->createCamera ("camera1");
    camera->lookAt (0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    aspect = WINDOW_W / WINDOW_H;
    camera->perspective (-WINDOW_W/256.0f/aspect,
        WINDOW_W/256.0f/aspect, -WINDOW_H/256.0f, WINDOW_H/256.0f, nearz, farz);

    ShaderProgram* shaderProgram = world->createShaderProgram();
    shaderProgram->loadShaderSource ("f:\\vert.glslv", "f:\\frag.glslf");


    ShaderProgramParams *params = new ShaderProgramParams ();


    //uniforms
    params->setNamedAutoConstant (TOY3D_ACT_PROJECTION_MATRIX, "proj_mat");
    params->setNamedAutoConstant (TOY3D_ACT_VIEW_MATRIX, "mview_mat");
    //params->setNamedAutoConstant (TOY3D_ACT_WORLD_MATRIX, "worldMat");

    //attributes
    params->setNamedAttrConstant (TOY3D_ATTR_VERTEX_INDEX, "pos_attr");


    shaderProgram->bindShaderParameters(params);

    Mesh *mesh = world->createMesh();
    mesh->setVertices (vertices, VERTEX_COUNT);


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
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize(WINDOW_W, WINDOW_H);
  	glutInitWindowPosition(0,0);
  	glutCreateWindow("renctangle");
  	glutDisplayFunc(display);
	glutIdleFunc(display);
  	glutKeyboardFunc(keyboard);
  	init();
  	glutMainLoop();

  	return 0;
}


