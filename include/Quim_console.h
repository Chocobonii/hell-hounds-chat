// INCLUDES FOR THE CONSOLE GO HERE

// --------------------------------------------------
// - THIS IS THE MAIN DATA STRUCTURE FOR THE OUTPUT -
// --------------------------------------------------
struct Output_message{
    std::string typef = "*";               // THESE ARE JUST SYMBOLS FOR MESSAGES: * X ! 
    std::string timestmp = "hh:mm";        // THIS IS THE DATE WHEN THE MESSAGE WAS SENT
    std::string guild = "XClient";         // THIS IS JUST WHO SENT THE MESSAGE
    std::string message = "";              // THIS IS THE CONTENT
    Output_message *next = NULL;           // A POINTER TO THE POSITION ON THE ROW
};
// ---------------------------------------------------
class Console{
    public:
      Output_message *list = NULL;                                      // THIS IS THE CONSOLE TO HANDLE THE DEBUG MESSAGES
      Console();                                                        // USUALLY IT'S NOT NECESSARY TO CREATE A CONSOLE CLASS
      void Push_message(std::string _t, std::string _g, std::string _m);// BUT I DO IT TO KEEP STUFF ORGANIZED
      void Show_messages();                                             // AND TO KEEP A GOOD HYGENE ON MY CODE
};
// ----------------------------------------------------
Console::Console(){}
// ----------------------------------------------------
void Console::Push_message(std::string _t, std::string _g, std::string _m){
    Output_message *msg = new Output_message();
    time( &currentTime );                                                // FETCH CURRENT TIME
    localTime = localtime( &currentTime );                               // CONVERT TO LOCAL TIME
    int Hour   = localTime->tm_hour;
    int Min    = localTime->tm_min;
    
    msg->typef = _t;                                                    //
    msg->timestmp = std::to_string(Hour) + ":" + std::to_string(Min);   // THIS IS JUST TO FILL THE PARAMTERS 
    msg->guild = _g;                                                    // REQUIRED BY THE NODE ON OUR CLASS
    msg->message = _m;                                                  //

    msg->next = list;                                                   // INSERT TO LIST
    list = msg;                                                         // 

    if(debug == 1){
        std::cout<<"{x.x} <debug>> "<<_m<<" sent by "<<_g<<std::endl;
    }
}
// ------------------------------------------------------
void Console::Show_messages(){          // 
    Output_message *aux = NULL;         // THIS PART WILL SHOW THE MESSAGES, IT LOOPS ALONG ALL MESSAGES ON THE CONSOLE
    aux = list;                         // AND PRINTS THEM ON THE CONSOLE AND PUSHES THEM TO IMGUI LIBRARY STUFF
    while(aux != NULL){                 // 
        std::string tmp_msg = "{" + aux->typef + "} [" + aux->timestmp + "-" + aux->guild + "]>> " + aux->message + ".";
        ImGui::Text(tmp_msg.c_str());
        aux = aux->next;                // MOVE POINTER TO THE NEXT NODE
    }
}
// --------------------------------------------------------
Console *cmd = new Console();           // CREATE THE CMD OBJECT FOR THE CONSOLE