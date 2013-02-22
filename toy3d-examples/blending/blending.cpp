
#include <toy3d/Toy3DCommon.h>
#include <toy3d/Toy3DWorld.h>
#include <toy3d/Toy3DEntity.h>
#include <toy3d/Toy3DMesh.h>
#include <toy3d/Toy3DMaterial.h>
#include <toy3d/Toy3DShaderProgramParams.h>
#include <toy3d/Toy3DShaderProgramManager.h>
#include <toy3d/Toy3DMeshManager.h>
#include <toy3d/Toy3DMaterialManager.h>


#define WINDOW_W    600 
#define WINDOW_H    600 


#ifdef VC6
#define SHADER_VERT_FILE "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/blending/blending.glslv"
#define SHADER_FRAG_FILE "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/blending/blending.glslf"
#else 
#define SHADER_VERT_FILE "/usr/local/share/toy3d/blending/blending.glslv"
#define SHADER_FRAG_FILE "/usr/local/share/toy3d/blending/blending.glslf"
#endif


using namespace TOY3D;

#define VERTEX_COUNT 3


//global
World *world = NULL;
Bool blendingFlag = TRUE;
Material *mat, *mat1, *mat2;



Real vertices[VERTEX_COUNT * 3] = {
    0.0f,  0.5f, 0.0f,
    -0.5f,-0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

Real color[VERTEX_COUNT * 4] = {
    1.0f, 0.0f, 0.0f, 0.6f,
    1.0f, 0.0f, 0.0f, 0.6f,
    1.0f, 0.0f, 0.0f, 0.6f
};

Real vertices1[VERTEX_COUNT * 3] = {
    0.3f,  0.8f, 0.0f,
    -0.2f,-0.2f, 0.0f,
    0.8f, -0.2f, 0.0f
};

Real color1[VERTEX_COUNT * 4] = {
    0.0f, 1.0f, 0.0f, 0.6f,
    0.0f, 1.0f, 0.0f, 0.6f,
    0.0f, 1.0f, 0.0f, 0.6f
};

Real vertices2[VERTEX_COUNT * 3] = {
    0.0f, -1.5f, 0.0f,
    -0.5f,-0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

Real color2[VERTEX_COUNT * 4] = {
    1.0f, 0.0f, 0.0f, 0.6f,
    1.0f, 0.0f, 0.0f, 0.6f,
    1.0f, 0.0f, 0.0f, 0.6f
};

void display()
{
    Bool flag = FALSE;

#if 1
    //glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    //glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    //glEnable(GL_POLYGON_SMOOTH);
    //glHint( GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST);
    //glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //glLineWidth(1.5);

#endif

    //Anti-aliasing
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    

#if 0
    GLint bufs, samples;

    glGetIntegerv(GL_SAMPLE_BUFFERS, &bufs);
    glGetIntegerv(GL_SAMPLES, &samples);
    if( (1==bufs) && (1<samples) )
    {
        flag = TRUE;
        glEnable(GL_MULTISAMPLE);
        glSampleCoverage(GL_SAMPLE_ALPHA_TO_COVERAGE, GL_FALSE);
    }
    else
    {
        printf("Multi-sample is   forbidded.\n");
    }
    //glSampleCoverage(1.0f, GL_TRUE);
    //glLineWidth(1.3f);
#endif

    world->startRendering (); 

    //if(flag)
    //    glDisable(GL_MULTISAMPLE);

	glFlush();
    glutSwapBuffers ();
}

void init()
{

    world = new World ();
    world->setSize(WINDOW_W, WINDOW_H);
    world->setBackColor (1.0, 1.0, 1.0, 1.0);  //white back color

    ShaderProgram *shaderProgram = ShaderProgramManager::getInstance()->createShaderProgram();
    shaderProgram->loadShaderSource (SHADER_VERT_FILE, SHADER_FRAG_FILE);

    ShaderProgramParams *params = ShaderProgramManager::getInstance()->createShaderProgramParams();

    //no shader uniforms ...

    //shader attributes
    params->setNamedAttrConstant (TOY3D_ATTR_VERTEX, "vPosition");
    params->setNamedAttrConstant (TOY3D_ATTR_COLOR, "vColor");

    shaderProgram->bindShaderParameters(params);

    Mesh* mesh = MeshManager::getInstance()->createMesh();
    mesh->setVertices (vertices, VERTEX_COUNT);
    mesh->setColors(color, VERTEX_COUNT);
    mesh->setRenderMode (TOY3D_TRIANGLE_STRIP);

    Mesh* mesh1 = MeshManager::getInstance()->createMesh();
    mesh1->setVertices (vertices1, VERTEX_COUNT);
    mesh1->setColors(color1, VERTEX_COUNT);
    mesh1->setRenderMode (TOY3D_TRIANGLE_STRIP);

    Mesh* mesh2 = MeshManager::getInstance()->createMesh();
    mesh2->setVertices (vertices2, VERTEX_COUNT);
    mesh2->setColors(color2, VERTEX_COUNT);
    mesh2->setRenderMode (TOY3D_TRIANGLE_STRIP);


    mat = MaterialManager::getInstance()->createMaterial();
    mat->setShaderProgram (shaderProgram);
    //mat->setSceneBlending(T3D_ONE_MINUS_SRC_COLOR, T3D_ZERO);// Front color would be black, with back white.
    //mat->setSceneBlending(T3D_SRC_ALPHA, T3D_ONE_MINUS_SRC_ALPHA);// Front color would be red ,with back white.
    //mat->setSceneBlending(T3D_DST_COLOR, T3D_SRC_COLOR); //Error?
    //mat->setSceneBlending(T3D_ONE, T3D_ZERO);
    //mat->enableBlending(TRUE);
    mat->setSceneBlending(T3D_SRC_ALPHA, T3D_ONE_MINUS_SRC_ALPHA);

    mat1 = MaterialManager::getInstance()->createMaterial();
    mat1->setShaderProgram (shaderProgram);
    mat1->setSceneBlending(T3D_SRC_ALPHA, T3D_ONE_MINUS_SRC_ALPHA);

    mat2 = MaterialManager::getInstance()->createMaterial();
    mat2->setShaderProgram (shaderProgram);
    mat2->setSceneBlending(T3D_SRC_ALPHA, T3D_ONE_MINUS_SRC_ALPHA);


    Entity *entity = world->createEntity();
    entity->setMesh (mesh);
    entity->setMaterial (mat);

    Entity *entity1 = world->createEntity();
    entity1->setMesh (mesh1);
    entity1->setMaterial (mat1);

    Entity *entity2 = world->createEntity();
    entity2->setMesh (mesh2);
    entity2->setMaterial (mat2);

    return;
}

void cleanup()
{

    ShaderProgramManager::getInstance()->destroyAllShaderProgramParams();
    ShaderProgramManager::getInstance()->destroyAllShaderPrograms();
    MeshManager::getInstance()->destroyAllMeshes();
    MaterialManager::getInstance()->destroyAllMaterials();

    world->destroyAllEntities();
}


void keyboard(unsigned char key, int x, int y){
    switch(key)
    {
    case 'q':
    case 'Q':
    case 27:
        cleanup();
        exit(0);

    //blending flag
    case 'B':
    case 'b':
        blendingFlag = !blendingFlag;
        mat->enableBlending(blendingFlag);
        mat2->enableBlending(blendingFlag);
        mat2->enableBlending(blendingFlag);
        break;

    //blending factor setting, s/S for src factor, and d/D for dst factor
    case 'S':
    case 's':
        return;

    case 'D':
    case 'd':
        return;
    }
    
    return;
}

int main(int argc, char** argv){

	glutInit(&argc, argv);
    //glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_MULTISAMPLE);
  	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  	glutInitWindowSize(WINDOW_W, WINDOW_H);
  	glutInitWindowPosition(0,0);
  	glutCreateWindow("blending");
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
    cleanup();

  	return 0;
}


