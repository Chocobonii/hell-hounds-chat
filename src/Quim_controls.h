void Quim_mouse(int x, int y){
   // int aspect_r= (Quim_winx/Quim_winy)*25;
    self_a = 180+(
      (atan2(
        (x-(self_x)),             // THIS IS BASIC MATH IT FETCHES THE MOUSE POSITION
        (y-(self_y))              // AND USES PLAYER AS CENTER, SO WITH ARCTAN WE MANAGE
            )*180)                // TO CALCULATE AN ANGLE FOR THE PLAYER
    // --------------- divided PI        
    /Quim_PI
    );
}
// -------------------------------------------------------
void Quim_move(int button, int state, int x, int y){      // IN THIS CASE 
  targ_p[0] = x;                                          // THIS IS THE MOUSE
  targ_p[1] = y;                                          // MOVEMENT
  has_clicked = true;                                     // 
}                                                         // 
// -------------------------------------------------------
void Quim_update(){                                       // 
  if(((int)targ_p[0] % 2)!=0){targ_p[0]+=1;}              // THIS ROUTINW
  if(((int)targ_p[1] % 2)!=0){targ_p[1]+=1;}              // WILL GET THE MOUSE
  if(self_x < targ_p[0]){self_x+=2;}                      // POSITION AND TEST WHETHER
  if(self_x > targ_p[0]){self_x-=2;}                      // THE TARGET POSITION IS THE SAME
  if(self_y < targ_p[1]){self_y+=2;}                      // AS THE PLAYER POSE
  if(self_y > targ_p[1]){self_y-=2;}                      // AND IF IT IS, THEN START MOVING
}                                                         // IN THIS CASE MOVING 1 BY 1 WAS WAY TOO SLOW    
                                                          // SO I TEST WITH MOD IF ITS AN ODD NUMBER AND 
                                                          // MAKE IT A MULTIPLIER OF 2
                                                          // TO MANAGE TO MOVE 2 BY 2 (FASTER)
// -------------------------------------------------------
void Quim_keyboard(unsigned char key, int x, int y){      // THIS IS THE KEYBOARD INPUT ROUTINE 
    switch (key){                                         // ----------------------------------
      case 13:                                            // IF IT DETECTS ANY KEY PRESSED
        message2_send = build_message;                    // THEN IT WILL ADD IT TO A STRING OF
        build_message = "";                               // WHAT HAS BEEN WRITTEN ALREADY
      break;                                              // AND IF IT DETECTS
      default:                                            // 13 - NEW LINE CHARACTER
        build_message += key;                             // THEN IT SENDS THE MESSAGE TO THE SERVER
      break;                                              // 
    }
}