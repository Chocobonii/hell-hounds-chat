// ---------------------------------------------------------------
// - THIS IS THE NETWORK SERVICE LOOP WHICH WILL PERFORM UPDATES -
// ---------------------------------------------------------------
void Network_service(int _t){
    //  ----------------------------------------
    //  - REQUEST THE MESSAGES FROM THE SERVER - 
    std::cout<<"net service has started. . . "<<std::endl;
    //  ----------------------------------------
    while (!started){}
    while(1){
        std::cout<<"net loop working...."<<std::endl;
        multiplayer_ng->recv_chat();
        std::cout<<"message fetched!"<<std::endl;
        if(strlen(message2_send.c_str()) > 1){
            multiplayer_ng->send_chat(message2_send);
        }
        std::cout<<"net loop ended..."<<std::endl;
        std::cout<<"player engine running . . . "<<std::endl;
        player_engine->Player_fetch_coords();
        manager_usr->Players_Update();
        if(has_clicked == true){
            player_engine->Player_post_position();
            has_clicked = false;
        }
        sleep(1);
    }
    std::cout<<"net service has died...."<<std::endl;
}
// this is basically the core of the multiplayer engine
// as it is in charge of controlling the different classes
// and sockets to perform the communication
// towards the website uwu