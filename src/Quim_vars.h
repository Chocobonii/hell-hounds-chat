// --------------------------------
// - THESE ARE THE MAIN VARIABLES -
// --------------------------------
int debug = 1; // is debug mode enabled?
// WINDOWS SIZE VARIABLES FOR RENDERING AND CONTROLS
int Quim_winx = 640; // window resolution
int Quim_winy = 480; //
// ----- IMPLEMENT MATH CONSTANTS --
#define Quim_PI 3.14159
// -------------------------------------
// - DEFAULT INFORMATION FOR THE MODEL -
// -------------------------------------
char *DEF_MDL = "./assets/models/generic.obj";
char *DEF_TEX = "assets/textures/chars.bmp";
// ---------------------------------
int mouse_x = 0; // save the mouse position
int mouse_y = 0; // ---------------------- 
float self_x  = Quim_winx>>1; // save the player positon
float self_y  = Quim_winy>>1; // ----------------------
int self_a  = 0; // save the player angle
float targ_p[2] = {self_x, self_y};   // ----------------------
// ---------------------------------
 time_t currentTime;
 struct tm *localTime;
// ---------------------------------
GLuint Q_FLOOR_TEX; // this is the floor texture  
GLuint Q_FISHEYE_F; // this is the fish eye effect
// ---------------------------------
std::string message2_send; // this is the message to send
std::string build_message = ""; // this is the building message
// ---------------------------------
std::thread _Networking; // This is the other thread of networking
// ---------------------------------
std::string _self_name = "dummy";   //THE DEFAULT USERNAME
bool started = false;               // TRIGGER FOR LOOP
// ---------------------------------
std::string _users_inside[100];     // LIST THE MESSAGES
std::string _messages_snt[100];     //
// ---------------------------------
std::string g_users_online_ [1000]; //
int         g_upositions_x_ [1000]; // THESE ARE THE USERS PARSED
int         g_upositions_y_ [1000]; // FROM THE SERVER
int         g_upositions_r_ [1000]; // 
// ---------------------------------
int online_u = 0; // THESE ARE THE ONLINE USERS CURRENTLY ON THE DATABASE
// ---------------------------------
GLuint JUSTAFOX;
bool has_clicked = false;