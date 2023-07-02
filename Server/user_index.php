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
    $link = mysqli_connect('localhost', $pos_user, $pos_pass, $pos_datb); // Connect to MySQL
    // --------------------------------
    if(!$link){
        die('couldn\'t connect to mysql');
    }
    // --------------------------------
    $mode = $_GET['dmode'];                  // THIS IS THE MODE 1 - INPUT, 2 - OUTPUT
    $pox = $_GET['infputx'];                // IF THE MODE IS INPUT THEN, IT WILL ADD A MESSAGE TO DB
    $poy = $_GET['infputy'];                // THESE INPUTS ARE THE PLAYER POSITIONS
    $rop = $_GET['infputr'];                // THAT MUST BE REGISTERED FOR THE DATABASE
    $uname= $_GET['unamed'];                 // AS WELL AS THE USERNAME
    // --------------------------------
    //echo 'passed parameter getchM\n';
    $pox = clean($pox);
    $poy = clean($poy);
    $rop = clean($rop);
    $uname= clean($uname);
    //echo 'passed clean\n';
    if($mode == 1) {
        //echo 'output mode enabled\n';
        $uname = clean($uname);
        $mansw = mysqli_query($link, 'SELECT * FROM positions WHERE username <> \''.$uname.'\';');   //
        echo '$';
        if (mysqli_num_rows($mansw) > 0) {      
            // echo 'fetched many rows: ';                                                  // these are the
            while($row = mysqli_fetch_assoc($mansw)) {                                       // parts
                echo 'k ' . $row["username"] . ' ' . $row["Pos_x"] . ' ' . $row["Pos_y"] . ' ' . $row["Rot_p"] . " $";             // that fetch the message
            }                                                                               // from our database
        }                                                                                   //       
        mysqli_free_result($mansw);
    }else{
        $uname = clean($uname);
        $kansw = mysqli_query($link, 'SELECT * FROM positions WHERE username = \''.$uname.'\';');   
        //echo 'num rows: ' . mysqli_num_rows($kansw) . ' query: ' . 'SELECT * FROM positions WHERE username = \''.$uname.'\';'; 
        if(mysqli_num_rows($kansw) <= 0){
            mysqli_free_result($kansw);
            $uname= clean($uname);
            $query= 'INSERT INTO positions (username, Pos_x,Pos_y,Rot_p) VALUES (\'' .$uname.'\','.$pox.','.$poy.','.$rop.');'; 
            $answ = mysqli_query($link, $query);
        }else{
            mysqli_free_result($kansw);
            $uname= clean($uname);
            $query= 'UPDATE positions SET Pos_x = '.$pox.', Pos_y = '.$poy.', Rot_p = '.$rop.' WHERE username = \''.$uname.'\';'; 
            $answ = mysqli_query($link, $query);
        }
    }
    mysqli_free_result($answ);
    mysqli_close($link);
?>