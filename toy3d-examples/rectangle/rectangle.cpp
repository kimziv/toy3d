
// #include <GL/glew.h>
// #include <GL/glut.h>


#include <toy3d/Toy3DCommon.h>
#include <toy3d/Toy3DWorld.h>
#include <toy3d/Toy3DShaderProgramParams.h>


#define WINDOW_W    500
#define WINDOW_H    500


#ifdef VC6
#define SHADER_VERT_FILE "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/rectangle/rect.glslv"
#define SHADER_FRAG_FILE "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/rectangle/rect.glslf"
#else
#define SHADER_VERT_FILE "/usr/local/share/toy3d/rectangle/rect.glslv"
#define SHADER_FRAG_FILE "/usr/local/share/toy3d/rectangle/rect.glslf"
#endif


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
Camera *camera = NULL;


void display()
{

    world->startRendering (); 

	glFlush();
    glutSwapBuffers ();
}


void changeSize( int w, int h ) 
{
    Real aspect, fovy;
    Real nearz  = 1.0f;//5.0f;
    Real farz   = 1000.0f;//60.0f;

    world->setSize(w, h);

    aspect = w / h;
    fovy = 60;
    camera->perspective (fovy, aspect, nearz, farz);
    camera->lookAt (0.0, 0.0, -3.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  
    return;
}



void init()
{
    Real aspect, fovy;
    const Real nearz  = 1.0f;//5.0f;
    const Real farz   = 1000.0f;//60.0f;

    world = new World ();
    world->setSize(WINDOW_W, WINDOW_H);
    world->setBackColor (1.0, 1.0, 0.0, 1.0);

//  fix it: Do not needed 
//    world->setWorldDepth(0, 0);

    camera = world->createCamera ("camera1");
/*
    camera->lookAt (0.0, 0.0, -3.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    aspect = WINDOW_W / WINDOW_H;
    fovy = 60;
    camera->perspective (fovy, aspect, nearz, farz);
    //camera->perspective (-1, 1, -1, 1, nearz, farz);
    //camera->ortho2D (-3, 3, -3, 3, nearz, farz);
*/
    ShaderProgram* shaderProgram = world->createShaderProgram();
    shaderProgram->loadShaderSource (SHADER_VERT_FILE, SHADER_FRAG_FILE);


    ShaderProgramParams *params = new ShaderProgramParams ();


    //uniforms
    params->setNamedAutoConstant (TOY3D_ACT_PROJECTION_MATRIX, "proj_mat");
    params->setNamedAutoConstant (TOY3D_ACT_VIEW_MATRIX, "mview_mat");
    params->setNamedAutoConstant (TOY3D_ACT_WORLD_MATRIX, "worldMat");

    //attributes
    params->setNamedAttrConstant (TOY3D_ATTR_VERTEX_INDEX, "vPosition");


    shaderProgram->bindShaderParameters(params);

    Mesh *mesh = world->createMesh();
    mesh->setVertices (vertices, VERTEX_COUNT);
    mesh->setRenderMode (TOY3D_TRIANGLE_STRIP);

    return;
}


void keyboard(unsigned char key, int x, int y){
  switch(key) {
    case 'q': case 'Q': case 27:
      exit(0);
      break;
  }

  return;
}


int main(int argc, char** argv){

	glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  	glutInitWindowSize(WINDOW_W, WINDOW_H);
  	glutInitWindowPosition(0,0);
  	glutCreateWindow("renctangle");
  	glutDisplayFunc(display);
	glutIdleFunc(display);
    glutReshapeFunc(changeSize);
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


