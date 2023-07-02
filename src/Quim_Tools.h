#include "Quim_ld_Tex.h"

void glQuimInit(){
 glClearColor(0.0,0.0,0.0,1.0);
 glEnable(GL_DEPTH_TEST);
 glEnable(GL_BLEND);
 glEnable(GL_TEXTURE_2D);
 glAlphaFunc(GL_GREATER, 0.5);
 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 manager_usr->Player_Init();
 manager_obj->Rom_initialize_sv();
 Quim_ldTextures();
}

void setOrtho(){ 
    glMatrixMode(GL_PROJECTION); 
    glPushMatrix(); 
    glLoadIdentity(); 
    glOrtho(0, Quim_winx, 0, Quim_winy, -1000,1000); 
    glScalef(1, -1, 1);
    glTranslatef(0, -Quim_winy, 0); 
    glMatrixMode(GL_MODELVIEW);
}
/*
 --------------------------------------------------------------------------------------------------------------------
 NOTE: OpenGL and Glut initialization and usage actually won't require any explanation
 on the usage and how it works, as there is documentation that can be found on the original website and 
 inside the different forums, please if you use the engine, be aware that you'll need previous knowledge on the usage
 of OpenGL 2, and GLUT
 --------------------------------------------------------------------------------------------------------------------
*/
void Quim_delay(){usleep(33);glutPostRedisplay();}