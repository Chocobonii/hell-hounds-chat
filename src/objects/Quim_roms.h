/*-------------------------------------------------------
 *- THIS IS THE STRUCTURE FOR AN OBJECT INSIDE THE ROOM -
 *-------------------------------------------------------
*/
struct Object{
    int pos_x; // this is the x position of the object
    int pos_y; // this is the y position of the object
    // ----------------------------------------------------
    int wide_x; // this is the wide x from x pos for colide
    int wide_y; //this is the wide y from y pos for colide
    // ----------------------------------------------------
    GLuint texture; // this is the texture of the object
    // ----------------------------------------------------
    Object *parent = NULL;
};
// ---------------------------------------------------------
/* --------------------------------------------------------------
 * - THIS IS THE OBJECT MANAGER WHICH WILL DRAW AND DETECT THEM -
 * --------------------------------------------------------------
*/
class Object_manager{
    public:
        int obj_ptr = 0;
        Object *inrom[200];
        Object *auxrm = NULL;
        Object_manager();
        void Rom_initialize_sv();
        void Push_object_inrom(char *filename, int sx, int sy, int xf, int yf, int xt, int yt);
        void Cast_object_colide();
        void Draw_object_list();
};
// --------------------------------------------------------------
Object_manager::Object_manager(){
    cmd->Push_message("*", "RomSys", "object for rooms created");
}
// --------------------------------------------------------------
void Object_manager::Push_object_inrom(char *filename, int sx, int sy, int xf, int yf, int xt, int yt){
    if (debug == 1){ cmd->Push_message("$", "debug", "object pushed in room"); }
    Object *in_rom = new Object();
    in_rom->texture = manager_usr->Quim_load_texture(filename, sx, sy);
    in_rom->pos_x = xf;                   // 
    in_rom->pos_y = yf;                   // this will create the object in room and assign it's properties
    in_rom->wide_x = xf + xt;             // as well as defining the collision box
    in_rom->wide_y = yf + yt;             // required for collision detection
    inrom[obj_ptr] = in_rom;              // 
    in_rom->parent = inrom[obj_ptr];      // 
    obj_ptr++;
}
// ---------------------------------------------------------------
void Object_manager::Draw_object_list(){
    for(int i = 0; i < obj_ptr; i++){
        auxrm = inrom[i];
        glPushMatrix();
          glBindTexture(GL_TEXTURE_2D, auxrm->texture);
          glBegin(GL_QUADS);
            glTexCoord2f(0,0);
            glVertex3f(auxrm->pos_x  ,auxrm->pos_y  , 90);
            glTexCoord2f(0,1);
            glVertex3f(auxrm->pos_x  ,auxrm->wide_y, 90);
            glTexCoord2f(1,1);
            glVertex3f(auxrm->wide_x ,auxrm->wide_y, 90);
            glTexCoord2f(1,0);
            glVertex3f(auxrm->wide_x,  auxrm->pos_y, 90);
          glEnd();
        glPopMatrix();
    }
}
// ------------------------------------------------------------
// this function is supposed to download the room but for testiing
// purposes it's just a function with objects drawn
// ------------------------------------------------------------
void Object_manager::Rom_initialize_sv(){
    Push_object_inrom("assets/textures/computers.bmp", 128,128,400,500,128,128);
    
    //Push_object_inrom("assets/textures/computers.bmp", 128,128,100,600,128,128);
    Push_object_inrom("assets/textures/cherry_tree.bmp", 128,128,   0,128,192,192);
    Push_object_inrom("assets/textures/cherry_tree.bmp", 128,128,1000,128,192,192);
    Push_object_inrom("assets/textures/cherry_tree.bmp", 128,128,1000,500,192,192);
    Push_object_inrom("assets/textures/cherry_tree.bmp", 128,128,   0,500,192,192);

    Push_object_inrom("assets/textures/computers.bmp", 128,128,1000,350,128,128);
}