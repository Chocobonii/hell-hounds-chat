<?php
    function clean($string) {
        $string = str_replace(' ', '-', $string);                 // Replaces all spaces with hyphens.
        $string = preg_replace('/[^A-Za-z0-9$\/=]/', '', $string);// Removes special chars.
        $string = str_replace('$', '', $string);
        $string = str_replace('\'', '', $string);
        $string = str_replace('\"', '', $string);
        return preg_replace('/-+/', '-', $string);               // Replaces multiple hyphens with single one.
    }     
    // --------------------------------
    require ('credentials.php');                                             // CREDENTIALS FOR THE DATABASES
    // -------------------------------- 
    $link = mysqli_connect('localhost', $chat_user, $chat_pass, $chat_datb); // Connect to MySQL
    // --------------------------------
    if(!$link){
        die('couldn\'t connect to mysql');
    }
    // --------------------------------
    $mode = $_GET['dmode'];                  // THIS IS THE MODE 1 - INPUT, 2 - OUTPUT
    $mesg = $_GET['infput'];                 // IF THE MODE IS INPUT THEN, IT WILL ADD A MESSAGE TO DB
    $uname= $_GET['unamed'];                 // 
    // --------------------------------
    //echo 'passed parameter getchM\n';
    $mesg = clean($mesg);
    $uname= clean($uname);
    //echo 'passed clean\n';
    if($mode == 1) {
        //echo 'output mode enabled\n';
        $answ = mysqli_query($link, "SELECT * FROM messages ORDER BY Id DESC LIMIT 7;");   //
        echo '$';
        if (mysqli_num_rows($answ) > 0) {      
            // echo 'fetched many rows: ';                                                  // these are the
            while($row = mysqli_fetch_assoc($answ)) {                                       // parts
                echo 'k ' . $row["username"] . ' ' . $row["dmessage"] . " $";             // that fetch the message
            }                                                                               // from our database
        }                                                                                   //       
    }else{
        //echo 'input mode enabled\n';
        $dmes = clean($mesg);                  // double check for special characters
        $uname= clean($uname);
        $query= 'INSERT INTO messages (username, dmessage) VALUES (\'' .$uname.'\',\''.$dmes.'\');'; 
        //echo $query . '\n';
        $answ = mysqli_query($link, $query);    // and the final insert of our data to the db
    }                                          // expected data must be base64
    //echo 'finished..\n';
    mysqli_free_result($answ);
    mysqli_close($link);
?>