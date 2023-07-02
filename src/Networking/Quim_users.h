
// ------------------------------------------------------
class Player_controller{                               // 
    public:                                            // THIS CLASS AIMS TO MANAGE PLAYERS
        Player_controller();                            // BY FETCHING A LIST AND AUTOMATICALLY
        void Player_fetch_coords();                    // DUMP PLAYERS WHO MAY HAVE LEFT THE GAME 
        void Player_post_position();                   // AND CHANGE EACH USER TARGET POSITION
};                                                     // SO THE USERS CAN MOVE ALONG THE MAP
// ------------------------------------------------------
Player_controller::Player_controller(){}    // THIS IS THE CONSTRUCTOR (NOT USEFUL)
// -------------------------------------------------------
void Player_controller::Player_fetch_coords(){
 //------------------------------------------------    
 int socket_desc;                                   // 
 struct sockaddr_in serv_addr;                      // THESE ARE THE LOCAL VARIABLES
 struct hostent *server;                            // TEMPORARY VARIABLES TO MAKE THE LINK
 char buffer[4096];                                 // CONNECTION
 // -----------------------------------------------
 std::string url = "www.pbonyxapi.slpmx.com";       // THIS IS THE LINK TO OUR API

 socket_desc = socket(AF_INET, SOCK_STREAM, 0);     // WE DEFINE SOCKSTREAM FOR HTTP (TCP)
 if(socket_desc < 0){                               // NOW WE TEST IF THE SOCKET WAS CREATED
  std::cout<<"failed to create socket"<<std::endl;
 }
 // ------------------------------------------------------------------------------
 server = gethostbyname(url.c_str());                                       //
 if(server==NULL){std::cout<<"could Not resolve hostname :("<<std::endl;}   // NOW THIS PART IS A BIT COMPLEX, WE WILL BE CONFIGURING
 bzero((char *) &serv_addr, sizeof(serv_addr));                             // OUR SOCKET TO WORK, AND ALSO WE RESOLVE THE HOST
 serv_addr.sin_family = AF_INET;                                            // AS, WE WILL GIVE OUR SOCKET A URL INSTEAD OF AN IP ADDRESS
 serv_addr.sin_port = htons(80);                                            // WE NEED TO RESOLVE THE HOSTNAME, ALSO IT IS WORTH TO MENTION
 bcopy((char *)server->h_addr,                                              // THAT THE FUNCTION HTONS HAS THE DEFAULT VALUE (AND ALSO FORCED)
         (char *)&serv_addr.sin_addr.s_addr,                                // AS 80 AS IT IS THE COMMON PORT TO USE ON WEB SERVERS
         server->h_length);                                                 // 
 // --------------------------------------------------------------------------------
 if(connect(socket_desc, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
   std::cout<<"connection failed :("<<std::endl;                            // AND THIS PART CONNECTS OUR SOCKET TO THE SERVER (IF FAILED SEND AN ERROR MESSAGE)
 }
 // ----------------------------------------------------------------------------------------
 std::string request = "GET /user_index.php?infputx="+std::to_string((int)self_x)+"&infputy="+std::to_string((int)self_y)+"&infputr="+std::to_string((int)self_a)+"&unamed="+_self_name+"&dmode=1 HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";  // NOW THIS IS THE HTTP PROTOCOL STRING USING A GET REQUEST TO FETCH OUR DATA FROM THE WEBSITE
 // ----------------------------------------------------------------------------------------
 if(send(socket_desc, request.c_str(), strlen(request.c_str())+1, 0) < 0){                  // AND INSIDE THIS SEGMENT OF CODE WE ARE GOING TO SEND THE REQUEST TO THE SERVER
  std::cout<<"failed to send request..."<<std::endl;                                        // BASICALLY WE ARE ASKING THE SERVER TO GIVE THE DATA FROM THE MYSQL DATABSE USING THE PHP API
 }                                                                                          //
 int n; 
 std::string raw_site;                                                                      //  THIS PART BASICALLY TELLS OUR SOCKET TO LISTEN
 while((n = recv(socket_desc, buffer, sizeof(buffer)+1, 0)) > 0){                           //  AND THE RECV (RECEIVED) DATA IS ORGANIZED INTO A STRING
  int i = 0;                                                                                //  SO IN THAT WAY WE ARE GOING TO GET THE RESPONSE FROM THE SERVER
        while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r'){                  //

            raw_site+=buffer[i];                                                            //   WHICH WILL CONTAIN THE INFORMATION REQUIRED TO 
            i += 1;                                                                         //   REASSEMBLE THE LAST SENT MESSAGES ON THE CHAT
        }
 }
 std::replace( raw_site.begin(), raw_site.end(), '$', '\n');  
 std::cout<<raw_site<<std::endl;                                                            //   AND WE PRINT OUR STRING
 // -----------------------------------------------------------------------------------------
 // - THIS PART CONTAINS THE ENTIRE PARSING FOR OUR STRING, WE MUST PARSE IT AND DECRYPT IT -
 // ----------------------------------------------------------------------------------------
 char usname[100], ux[10],uy[10],ur[10], cmd[100];
 int pointer = 0;
 std::string _rm_non_instr = "";                            // 
 std::istringstream _buf(raw_site);                         // This removes the header
 std::string cmd_line;                                      // of the response
 while (std::getline(_buf, cmd_line)) {                     // looking for just parts of the file
    if(cmd_line[0] == 'k'){    
        char temporal[1228];                                // usados para el scanf general
        strcpy(temporal, cmd_line.c_str());                 // with this now im able to parse
        _rm_non_instr += cmd_line + '\n';                   // 
        sscanf(temporal, "%s %s %s %s %s\n", &cmd, &usname, &ux, &uy, &ur);
        
        g_users_online_[pointer] = usname;
        g_upositions_x_[pointer] = atoi(ux);
        g_upositions_y_[pointer] = atoi(uy);
        g_upositions_r_[pointer] = atoi(ur);
        std::cout<<"PARSER: "<<g_users_online_[pointer]<<" "<<g_upositions_x_[pointer]<<" "<<g_upositions_y_[pointer]<<" "<<g_upositions_r_[pointer]<<std::endl;
        pointer++;
    }
 }
 online_u = pointer;
 std::cout<<"----------------------\n"<<"Parsing: \n"<<_rm_non_instr<<std::endl;
 // -----------------------------------------------------------------------------------------
 close(socket_desc);
}
// ******************************************************************************
// * THIS ROUTINE UPDATES THE PLAYER POSITION AND ALSO WORKS AS A LOGIN ROUTINE *
// ******************************************************************************
void Player_controller::Player_post_position(){
 //------------------------------------------------    
 int socket_desc;                                   // 
 struct sockaddr_in serv_addr;                      // THESE ARE THE LOCAL VARIABLES
 struct hostent *server;                            // TEMPORARY VARIABLES TO MAKE THE LINK
 char buffer[4096];                                 // CONNECTION
 // -----------------------------------------------
 std::string url = "www.pbonyxapi.slpmx.com";       // THIS IS THE LINK TO OUR API

 socket_desc = socket(AF_INET, SOCK_STREAM, 0);     // WE DEFINE SOCKSTREAM FOR HTTP (TCP)
 if(socket_desc < 0){                               // NOW WE TEST IF THE SOCKET WAS CREATED
  std::cout<<"failed to create socket"<<std::endl;
 }
 // ------------------------------------------------------------------------------
 server = gethostbyname(url.c_str());                                       //
 if(server==NULL){std::cout<<"could Not resolve hostname :("<<std::endl;}   // NOW THIS PART IS A BIT COMPLEX, WE WILL BE CONFIGURING
 bzero((char *) &serv_addr, sizeof(serv_addr));                             // OUR SOCKET TO WORK, AND ALSO WE RESOLVE THE HOST
 serv_addr.sin_family = AF_INET;                                            // AS, WE WILL GIVE OUR SOCKET A URL INSTEAD OF AN IP ADDRESS
 serv_addr.sin_port = htons(80);                                            // WE NEED TO RESOLVE THE HOSTNAME, ALSO IT IS WORTH TO MENTION
 bcopy((char *)server->h_addr,                                              // THAT THE FUNCTION HTONS HAS THE DEFAULT VALUE (AND ALSO FORCED)
         (char *)&serv_addr.sin_addr.s_addr,                                // AS 80 AS IT IS THE COMMON PORT TO USE ON WEB SERVERS
         server->h_length);                                                 // 
 // --------------------------------------------------------------------------------
 if(connect(socket_desc, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
   std::cout<<"connection failed :("<<std::endl;                            // AND THIS PART CONNECTS OUR SOCKET TO THE SERVER (IF FAILED SEND AN ERROR MESSAGE)
 }
 // ----------------------------------------------------------------------------------------
 std::string request = "GET /user_index.php?infputx="+std::to_string((int)self_x)+"&infputy="+std::to_string((int)self_y)+"&infputr="+std::to_string((int)self_a)+"&unamed="+_self_name+"&dmode=2 HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\nContent-Length: "+std::to_string((strlen(_self_name.c_str())))+"\r\n\r\n";  // NOW THIS IS THE HTTP PROTOCOL STRING USING A GET REQUEST TO FETCH OUR DATA FROM THE WEBSITE
 //std::string request = "GET /chat_index.php?unamed="+_self_name+"&dmode=2&infput="+_encoded_message+" HTTP/1.1"
 //                      "\r\nHost: www.pbonyxapi.slpmx.com"
 //                      "\r\nConnection: close";

 std::cout<<request<<std::endl;
 // ----------------------------------------------------------------------------------------
 if(send(socket_desc, request.c_str(), strlen(request.c_str())+1, 0) < 0){                  // AND INSIDE THIS SEGMENT OF CODE WE ARE GOING TO SEND THE REQUEST TO THE SERVER
  std::cout<<"failed to send request..."<<std::endl;                                        // BASICALLY WE ARE ASKING THE SERVER TO GIVE THE DATA FROM THE MYSQL DATABSE USING THE PHP API
 }                                                                                          //
 int n; 
 std::string raw_site;                                                                      //  THIS PART BASICALLY TELLS OUR SOCKET TO LISTEN
 while((n = recv(socket_desc, buffer, sizeof(buffer)+1, 0)) > 0){                           //  AND THE RECV (RECEIVED) DATA IS ORGANIZED INTO A STRING
  int i = 0;                                                                                //  SO IN THAT WAY WE ARE GOING TO GET THE RESPONSE FROM THE SERVER
        while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r'){                  //

            raw_site+=buffer[i];                                                            //   WHICH WILL CONTAIN THE INFORMATION REQUIRED TO 
            i += 1;                                                                         //   REASSEMBLE THE LAST SENT MESSAGES ON THE CHAT
        }
 }
 close(socket_desc);
}
// -------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------
Player_controller *player_engine = new Player_controller();
// -------------------------------------------------------------------------------------------