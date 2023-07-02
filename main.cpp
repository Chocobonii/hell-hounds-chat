// -----------------------------------------------
// - THESE ARE THE MAIN INCLUDES FOR SYSTEM LIBS -
// -----------------------------------------------
#include <GL/glut.h> // OpenGL library to use
#include <iostream>  // 
#include <stdlib.h>  // main C++ libraries
#include <fstream>   //
#include <sstream>   //
#include <math.h>    //
#include <unistd.h>  //
#include <ctime>
#include <stdio.h>
#include <algorithm>
#include <pthread.h>
#include <thread>
#include <string.h>
#include <future>
// ---------------------------------
// - NETWORKING LIBRARIES REQUIRED -
// ---------------------------------
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
// ----------------------------------
// - 
// ----------------------------------
#include <cryptopp/aes.h>    // THIS IMPORTS THE AES FOR CRYPTOPP
#include <cryptopp/modes.h>  // THIS IMPORTS MODES FOR AES
#include <cryptopp/osrng.h>  // USED TO PROVIDE RANDOMNESS TO THE ALGORITHM
#include <cryptopp/base64.h> // USED TO FORMAT THE TEXT TO SOMETHING READABLE
#include <cryptopp/hkdf.h>   // TO EXPAND AND DERIVATE THE KEYS SECURELY
// -------------------------------
// - EXTERNAL LIBRARY DEFINITION -
// -------------------------------
#define STB_IMAGE_IMPLEMENTATION"
#include "lib/stb_image.h"
#include "lib/imgui/imgui.h"
#include "lib/imgui/backends/imgui_impl_opengl2.h"
#include "lib/imgui/backends/imgui_impl_glut.h"
// -----------------------------
// - GLOBAL VARIABLES ASSIGNED -
// -----------------------------
#include "src/Quim_vars.h" 
// --------------------------------
// - MODULES TO IMPLEMENT IN GAME -
// --------------------------------
#include "include/Quim_console.h"
#include "src/Security/Quim_crypto.h"
#include "src/Networking/Quim_chat.h" // This is the chat client class
#include "include/Quim_player.h"
#include "src/Networking/Quim_users.h"
// --- USER MANAGEMENT GOES HERE ---
Player_manager *manager_usr = new Player_manager();
#include "src/Networking/Quim_netservice.h"
// --- OBJECT AND ROM MANAGER GO HERE ---
#include "src/objects/Quim_roms.h"
Object_manager *manager_obj = new Object_manager();
// ---------------------------------
#include "src/Quim_Tools.h"
#include "src/Quim_controls.h"
#include "src/Quim_Render.h"
// -------------------------------
// - MAIN FUNCTION FOR ALL STUFF -
// -------------------------------
int main(int argc, char **argv){
    std::cout<<"PLEASE INPUT YOUR USERNAME: "<<std::endl;
    std::cin>>_self_name;
    // ---------------------------------------------------------
     IMGUI_CHECKVERSION();   // TEST VERSION OF IMGUI
     ImGui::CreateContext(); // CREATE AN IMGUI CONTEXT
     std::cout<<"Connecting to world.. .. . ."<<std::endl;
     player_engine->Player_post_position();
    // ---------------------------------------------------------
    glutInit(&argc, argv);                                      
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(Quim_winx, Quim_winy);                     //  
    glutCreateWindow("Hell hounds - FirestormPlayer");            // this part initializes the opengl stuff
    // ---------------------------------------------------------
    ImGuiIO &io = ImGui::GetIO(); (void) io;    // initialize input/output of the imgui API
    ImGui::StyleColorsDark();                   // define dark color for the im gui api
    ImGui_ImplGLUT_Init();                      // start the GLUT version of imgui
    ImGui_ImplGLUT_InstallFuncs();              // install functions of imgui
    ImGui_ImplOpenGL2_Init();                   // use opengl 2 on imgui (to avoid pipewire)
    // ---------------------------------------------------------
    glClearDepth(1.0f);                                          // and the ImGui things in order to make
    glDepthFunc(GL_LEQUAL);                                      // the rendering function
    glQuimInit();                                                // 
    // -----------------------------------------------------------
    // small interruption to the process to start other threads
    // _Networking = std::thread(Network_service,0);
    // _Networking.join();
    auto ma = std::async(Network_service,0);
    // -----------------------------------------------------------
    glutIgnoreKeyRepeat(1);                                      // this is the main structure
    glutDisplayFunc(Quim_render);                                // that will contain all things of the manager
    glutIdleFunc(Quim_delay);                                    // and enable the different threads
    glutPassiveMotionFunc(Quim_mouse);                           // 
    glutMouseFunc(Quim_move);
    glutKeyboardFunc(Quim_keyboard);
    glutMainLoop();
    // ----------------------------------------------------------
      ImGui_ImplOpenGL2_Shutdown();               // end the OpenGL2 of ImGui
      ImGui_ImplGLUT_Shutdown();                  // shut down glut of imgui
      ImGui::DestroyContext();                    // destroy the context
    // ----------------------------------------------------------
    return 0;
}