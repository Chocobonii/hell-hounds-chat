CREATE USER 'user_pos'@'' IDENTIFIED BY 'generic123!';  -- WE CREATE OUR USERS FOR THE MANAGEMENT
CREATE USER 'chat_msg'@'' IDENTIFIED BY 'g3n3r1c321!';  -- OF THE TABLES AND API WORKING

CREATE DATABASE hellHounds;                             -- NOW WE CREATE OUR DATABASE

USE hellHounds;                                         -- NOW WE USE THE DATABASE 

CREATE TABLE messages (                                 -- AND WE CREATE 2 NEW TABLES, ONE FOR MESSAGES
    Id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    username TEXT NOT NULL,
    dmessage TEXT NOT NULL
);

CREATE TABLE positions (
    Id       INT NOT NULL AUTO_INCREMENT PRIMARY KEY,   -- AND THIS OTHER TABLE CREATED FOR POSITIONS 
    username TEXT NOT NULL, 
    Pos_x    INT NOT NULL,
    Pos_y    INT NOT NULL,
    Rot_p    INT NOT NULL
);

GRANT SELECT,INSERT,DELETE ON hellHounds.messages TO 'chat_msg'@'localhost';            -- NOW WE ASSIGN SPECIFIC PERMISSIONS 
GRANT SELECT, INSERT, UPDATE, DELETE ON hellHounds.positions TO 'user_pos'@'localhost'; -- TO AVOID DANGERS 
                                                                                        -- THIS IS PART OF ACCESS CONTROL
-- .....................................................................................