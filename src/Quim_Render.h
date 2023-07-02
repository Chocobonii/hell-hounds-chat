#include "../lib/style.h"
/*
---------------------------------------------
- MENU AND INTERFACE REDNERDING USING IMGUI -
---------------------------------------------
*/
void Quim_ImGui_Render(){
      started = true;
      ImGui::SetNextWindowPos(ImVec2(0,0));                     // 
      ImGui::SetNextWindowSize(ImVec2(Quim_winx,128));          // THIS IS THE MANAGEMENT OF IMGUI LIBRARY
      ImGui::SetupImGuiStyle(true,0.9);                         // THE PART WHERE THE TERMINAL IS DRAWN
      ImGui::Begin(".: Network Terminal:.");                    // AND THE PART WHERE THE MESSAGES MUST BE PUSHED
     // ImGui::SetupImGuiStyle(true,0.5);                       // FOR THE GAME TO WORK PROPERLY
       ImGui::TextColored(ImVec4(1,1,0,1), "Console output:");  // BASICALLY, WORKS AS IF IT WAS GLUT BY GIVING INSTRUCTIONS
       ImGui::BeginChild("Scrolling");                          // AND IT WILL DISPLAY STUFF ON THE SCREEN
        cmd->Show_messages();                                   // 
        ImGui::SetScrollHereY(0.0f);
       ImGui::EndChild();
      ImGui::End();
      //-----------------------------------------------------------------------------------------------------------------
      ImGui::SetNextWindowPos(ImVec2(2,( Quim_winy- (Quim_winy/5) -48 ) ));                                             //
      ImGui::SetNextWindowSize(ImVec2(Quim_winx/5,(Quim_winy/5)+16));                                                   // START A NEW WINDOW FOR CHATTING
      ImGui::Begin("Chat window");                                                                                      //

      ImGui::TextColored(ImVec4(1,1,0,1), "Encrypted chat :");                                                          // 
      //ImGui::BeginChild("Scrolling", ImVec2(ImGui::GetContentRegionAvail().x, (Quim_winy/5)-64), false);                // IN THIS SEGMENT WE MAY FIND 
        for(int i = 7; i > 0; i--){
          std::string tmp_msg_d = "{"+_users_inside[i-1]+"} says: " + _messages_snt[i-1];                               // THE CONSTRUCTION OF THE CHATBOX
          //ImGui::Text(tmp_msg_d.c_str());
          ImGui::TextColored(ImVec4(1,1,1,1), tmp_msg_d.c_str());
        }
       ImGui::Text("------------------");
       // ImGui::SetScrollHereY(0.0f);                                                                                    // TEXT BOX WHERE THE USER WRITES THE MESSAGE
       //ImGui::EndChild();                                                                                               // 
       ImGui::BeginChild("ChildL");                                                                                     // 
       ImGui::InputText( "Chat", build_message.c_str(), sizeof(build_message) );                                        // 
       ImGui::EndChild();
      ImGui::End();
      // -----------------------------------------------------------------------------------------------------------------
}
/*
----------------------------------------------------------
- THIS IS THE RENDERING OF THE BACKGROUND ELEMENTS IN 2D -
----------------------------------------------------------
*/
void Quim_draw_scenario(){
 glBindTexture(GL_TEXTURE_2D, Q_FLOOR_TEX);                   // 
 glBegin(GL_QUADS);                                           // THIS PART BASICALLY JUST DRAWS THE BACKGROUNDD
   glTexCoord2f(0,0);                                         // IT IS A HUGE SQUARE BEHIND THE PLAYERS
   glVertex3f(0  ,0  , -100);                                 // WHICH SIMULATES TO BE GRASS
   glTexCoord2f(0,Quim_winy/128);                             // AND EACH FRAMES IT RESHAPES ITSELF
   glVertex3f(0  ,Quim_winy-15, -100);                           // TO THE SIZE OF THE SCREEN BUFFER
   glTexCoord2f(Quim_winx/128,Quim_winy/128);                 // TO KEEP THE ASPECT RATIO
   glVertex3f(Quim_winx,Quim_winy-15, -100);                     // OF MY FRAWING FIELD
   glTexCoord2f(Quim_winx/128,0);                             // 
   glVertex3f(Quim_winx,  0, -100);                           // 
 glEnd();
}
/*
----------------------------------------------------
- FISH EYE EFFECT AND ALL PARTICLE STUFF GOES HERE -
----------------------------------------------------
*/
void Quim_draw_effects(){
 glBindTexture(GL_TEXTURE_2D, Q_FISHEYE_F);                 // 
 glBegin(GL_QUADS);                                         // 
   glTexCoord2f(0,0);                                       // THIS BASICALLY TAKES THE TEXTURE OF THE FISH EYE EFFECT
   glVertex3f(0  ,0  , 100);                                // WHICH IS THE DARKNESS ON THE CORNERS OF THE SCREEN
   glTexCoord2f(0,1);                                       // AND DRAWS IT ON TOP
   glVertex3f(0  ,Quim_winy, 100);                          // 
   glTexCoord2f(1,1);                                       // IT'S COMPLETELY USELESS
   glVertex3f(Quim_winx,Quim_winy, 100);                    // JUST A VISUAL TO MAKE THE GAME LOOK MORE PROFESSIONAL
   glTexCoord2f(1,0);                                       // 
   glVertex3f(Quim_winx,  0, 100);                          // 
 glEnd();
}
/*
--------------------------------------------------------------
- THIS IS THE MAIN OPENGL RENDERING LOOP WHERE STUFF HAPPENS -
--------------------------------------------------------------
*/
void Quim_render(){
   ImGui_ImplOpenGL2_NewFrame();                                       // THIS INITIALIZES IMGUI FRAMES
   ImGui_ImplGLUT_NewFrame();                                          // SO IT CAN WORK
   // ----------------------------------------------------------  
   Quim_ImGui_Render();                                                // CALL MY RENDERING STUFF
   // ----------------------------------------------------------
   ImGui::Render();                                                    // THIS ENABLES THE RENDERING
   ImGuiIO& io = ImGui::GetIO();                                       // INPUT/OUTPUT FOR THE IMGUI DETECTION
   Quim_winx = io.DisplaySize.x;                                       // FETCH THE SIZE OF MY DISPLAY TO ADAPT IT
   Quim_winy = io.DisplaySize.y;                                       //
  glViewport(0,0,(GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);// ADJUST VIEWPORT TO WINDOW SIZE
 // ----------------------------------------------------------
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                    // AND THIS CLEARS THE BUFFERS FOR DEPTH AND COLOR
 setOrtho();                                                            // THIS SETS THE VIEW TO ORTHOGONAL VIEW
 Quim_update();                                                         // REFRESH SELF PLAYER POSITION
 manager_usr->Self_update(self_x,self_y,self_a);                        // AND DRAW THE PLAYER
 // ----------------------------------------------------------
 glPushMatrix();                                                        // 
    Quim_draw_scenario();                                               // THIS WILL BEGIN THE DRAWING OF THE SCENE
 glPopMatrix();                                                         // 
 glPushMatrix();    
    manager_usr->Players_Animate();                                                    // 
    manager_usr->Player_drawall(true);                                  // THIS WILL DRAW ALL PLAYERS ON MY PLAYER MANAGER
 glPopMatrix();                                                         // STRUCTURE
 glPushMatrix();                                                        // 
    manager_obj->Draw_object_list();                                    // THIS WILL DRAW ALL OBJECTS DESCRIBED IN ROOM
    Quim_draw_effects();                                                // 
 glPopMatrix();
 // -----------------------------------------------------------
   ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());              // THIS ACTUALLY RENDERS THE DATA
 // -----------------------------------------------------------
 glFlush();                                                             // 
 glutSwapBuffers();                                                     // 
}