

#include <toy3d/Toy3DCommon.h>
#include <toy3d/Toy3DWorld.h>
#include <toy3d/Toy3DTexture.h>
#include <toy3d/Toy3DTextureManager.h>
#include <toy3d/Toy3DEntity.h>
#include <toy3d/Toy3DMesh.h>
#include <toy3d/Toy3DMaterial.h>
#include <toy3d/Toy3DShaderProgramParams.h>
#include <toy3d/Toy3DShaderProgramManager.h>
#include <toy3d/Toy3DMeshManager.h>
#include <toy3d/Toy3DMaterialManager.h>




#define WINDOW_W    500
#define WINDOW_H    500


#ifdef VC6
#define SHADER_VERT_FILE   "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/multi_texture/multi_texture.glslv"
#define SHADER_FRAG_FILE   "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/multi_texture/multi_texture.glslf"
#define TEXTURE_FILE_BACK  "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/multi_texture/back.tga"
#define TEXTURE_FILE_LIGHT "C:/Program Files (x86)/TOY3D-EXAMPLES/share/toy3d/multi_texture/light.tga"
#else 
#define SHADER_VERT_FILE   "/usr/local/share/toy3d/multi_texture/multi_texture.glslv"
#define SHADER_FRAG_FILE   "/usr/local/share/toy3d/multi_texture/multi_texture.glslf"
#define TEXTURE_FILE_BACK  "/usr/local/share/toy3d/multi_texture/back.tga"
#define TEXTURE_FILE_LIGHT "/usr/local/share/toy3d/multi_texture/light.tga"
#endif


using namespace TOY3D;

#define VERTEX_COUNT 6


//global
World *world = NULL;
Camera *camera = NULL;


Real vertices[VERTEX_COUNT * 3] = {
    -1.0f, -1.0f, 0.0f,
    1.0f,  -1.0f, 0.0f,
    -1.0f, 1.0f,  0.0f,

    1.0f,  1.0f,  0.0f,
    1.0f,  -1.0f, 0.0f,
    -1.0f, 1.0f,  0.0f
};

Real uvs[VERTEX_COUNT * 2] = {
    0.0f,0.0f, 1.0f,0.0f, 0.0f,1.0f,
    1.0f,1.0f, 1.0f,0.0f, 0.0f,1.0f
};


void display()
{

    world->startRendering (); 

	glFlush();
    glutSwapBuffers();
}

void changeSize( int w, int h ) 
{
    Real aspect, fovy;
    Real nearz  = 1.0f;//5.0f;
    Real farz   = 1000.0f;//60.0f;
    
    world->setSize(w, h);

    camera->lookAt (0.0, 0.0, -5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    aspect = 1.0 * w / h;
    fovy = 60;
    camera->perspective (fovy, aspect, nearz, farz);
    
    return;
}


Bool init()
{
    int   width = WINDOW_W, height = WINDOW_H;
    //int   texid;
    Entity *entity;
    int texUnitId1 = 0;
    int texUnitId2 = 1;

    world = new World ();
    printf("pointer world: %d.\n", world);
    world->setSize(width, height);
    world->setBackColor (1.0, 1.0, 1.0, 1.0);

    camera = world->createCamera ("camera1");

    //shader
    ShaderProgram *shaderProgram = ShaderProgramManager::getInstance()->createShaderProgram();
    if( !shaderProgram->loadShaderSource (SHADER_VERT_FILE, SHADER_FRAG_FILE) )
    {
        TOY3D_TIPS("Error: loadShaderSource failed.\n");
        return FALSE;
    }
    //printf("shaderProgram id: %d\n", shaderProgram->getShaderProgramID());


    ShaderProgramParams *params = ShaderProgramManager::getInstance()->createShaderProgramParams();

    //shader auto constant
    params->setNamedAutoConstant (TOY3D_ACT_PROJECTION_MATRIX, "proj_mat");
    params->setNamedAutoConstant (TOY3D_ACT_VIEW_MATRIX, "view_mat");
    params->setNamedAutoConstant (TOY3D_ACT_WORLD_MATRIX, "world_mat");

    //shader attributes
    params->setNamedAttrConstant(TOY3D_ATTR_VERTEX, "a_position");
    params->setNamedAttrConstant(TOY3D_ATTR_UV, "a_texCoord");

    //shader custom constant
    params->setNamedCustUniformConstant(TOY3D_CUST_SAMPLER2D, "s_baseMap", texUnitId1);
    params->setNamedCustUniformConstant(TOY3D_CUST_SAMPLER2D, "s_lightMap", texUnitId2);

    shaderProgram->bindShaderParameters(params);

    Texture *tex_back = TextureManager::getInstance()->createTextureByFile(TEXTURE_FILE_BACK);
    Texture *tex_light = TextureManager::getInstance()->createTextureByFile(TEXTURE_FILE_LIGHT);

    Material *mat = MaterialManager::getInstance()->createMaterial();
    mat->setShaderProgram (shaderProgram);
    //mat->setSceneBlending(T3D_SRC_ALPHA, T3D_ONE_MINUS_SRC_ALPHA, T3D_ADD);

    //create tex unit 1 for back.tga
    TextureUnitState *texUS_back;
    texUS_back = mat->createTextureUnitState("TexUnit_back");
    if(!texUS_back)
    {
        TOY3D_TIPS("Error: createTextureUnitState failed.\n");
        return FALSE;
    }

    texUS_back->setID (texUnitId1);
    texUS_back->setTexture(tex_back);
    texUS_back->setTextureType(T3D_TEXTURE_2D);
    texUS_back->setTextureParameter(T3D_LINEAR, T3D_LINEAR, T3D_CLAMP_TO_EDGE, T3D_CLAMP_TO_EDGE);


    //create tex unit 2 for light.tga

    TextureUnitState *texUS_light;
    texUS_light = mat->createTextureUnitState("TexUnit_light");
    if(!texUS_light)
    {
        TOY3D_TIPS("Error: createTextureUnitState failed.\n");
        return FALSE;
    }

    texUS_light->setID (texUnitId2);
    texUS_light->setTexture(tex_light);
    texUS_light->setTextureType(T3D_TEXTURE_2D);
    texUS_light->setTextureParameter(T3D_LINEAR, T3D_LINEAR, T3D_CLAMP_TO_EDGE, T3D_CLAMP_TO_EDGE);

    //mat->addTextureUnitState (texUS_back);
    //mat->addTextureUnitState (texUS_light);

    Mesh* mesh = MeshManager::getInstance()->createMesh();
    mesh->setRenderMode (TOY3D_TRIANGLE_STRIP);
    mesh->setVertices (vertices, VERTEX_COUNT);
    mesh->setUVs( uvs, VERTEX_COUNT);

    entity = world->createEntity();
    entity->setMesh(mesh);
    entity->setMaterial (mat);

    return true;
}


void cleanup ()
{

    ShaderProgramManager::getInstance()->destroyAllShaderProgramParams();
    ShaderProgramManager::getInstance()->destroyAllShaderPrograms();

    TextureManager::getInstance()->destroyAllTextures();

    MeshManager::getInstance()->destroyAllMeshes();
    MaterialManager::getInstance()->destroyAllMaterials();

    world->destroyAllEntities();

    //Fixme:
//    world->destroyAllCameras();


}

Real angle_y = 0.0f;

void keyboard(unsigned char key, int x, int y){
    switch(key)
    {
    case 'q':
    case 'Q':
    case 27:
        cleanup ();
        exit(0);

    case 'p':
    case 'P':
    case 26:
        world->rotate (0.0f, angle_y, 0.0f);
        angle_y += 10;
        break;

    }
}

int main(int argc, char** argv){

	glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  	glutInitWindowSize(WINDOW_W, WINDOW_H);
  	glutInitWindowPosition(0,0);
  	glutCreateWindow("multi_texture");
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

    Bool rv;
  	rv = init();
    if(rv==FALSE)
        return 0;

  	glutMainLoop();

    cleanup();

  	return 0;
}


