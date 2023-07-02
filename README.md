Hell hounds, is a small chatroom proyect which encrypts the chat using AES in order to prevent
intruders from spying on your messages, this complete software is developed by Pentabonyx Labs

to assemble the program it is required to execute the command as: 
```
 ./compile.sh --client-audio
```
RUN AS SUDO!!!!

this program should try to setup the development environtent for the proyect
* Steps to compile the program:
	The program includes a custom script for building itself, this script basically will be in charge of assembling the entire program, and setting up the environment for development, but if we manually wanted to build the program, after we have the code, we will install the packages: krb5, libgcrypt, nettle, openssl, crypto++, freeglut, git and g++.To install these packages you are going to use your packet manager (this program was made for linux) In my case it’s PACMAN, as it’s the default packet manager that comes with arch linux.

the command to install the packages is:
```
sudo pacman -Syu krb5 libgcrypt nettle openssl crypto++ freeglut git g++
```
The packet manager should leave the libraries itself automatically in the /usr/include folder.
And then we will run the following command:
```
g++ -fpermissive -w -o chat main.cpp -lGLU -lglut -lGL lib/imgui/backends/imgui_impl_glut.cpp lib/imgui/backends/imgui_impl_opengl2.cpp lib/imgui/imgui*.cpp -pthread -lcryptopp;
```
the first part handles warnings, by using the flags -fpermissive and -w, the second part -o chat main.cpp gives the program to compile, and the output will be set as chat, and finally the linkers for the libraries are included as the backends, thread and -lcryptopp, which will make sure to link the libraries. 
	Otherwise, we do not have the interest to do a manual installation for the program, we can just execute the script compile.sh with the parameter -–client-audio <- to assemble with audio libraries. as shown below:
 ```
./compile.sh --client-audio
```
And this will basically set up the development environment for us, and compile the program.
The program is divided into multiple folders, having a structure, to keep everything organized for the development. The structure can be seen on the following image: 

	On the image we can see several files and folders which are going to be explained now:
 
README.md > It is a document which just has relevant information about the program, it’s used to display this same building instructions on github (as this program is being released as OpenSource)
Server > Contains the different PHP files and the DB (database) script, these files will handle the server and the client connections inside the program, basically consists of all the server side operations required for the program to work. Please notice that to connect to a custom server you must change the domain www.pbonyxapi.slpmx.com on the files: Quim_chat.h and Quim_users.h, so the program connects to your own server. 
assets > this folder will just contain the resources required for the game, basically just the images, and 3D models in .obj format used for the game.
chat > is the output program generated after the compilation, if you are not using arch linux, or build your own program just delete this. 
compile.sh > this is the compilation script mentioned before. 
include > this includes 2 main classes developed for the game, are just included for the game that are not part of the core. 
lib > in this folder you may find all the third party libraries used for the game, this is to keep organization within the program
src > all the source code core files for the essential functionalities of the program go here. The cryptography class has the security and encryption for the game client.  
main.cpp > it’s the main program, basically the important file where the program starts and the one file that will be assembled when we execute the compilation command. 
_______________________________________________________________________
Please make sure to visit my website!!!!
 LINK: http://pentabonyx.slpmx.com/
_______________________________________________________________________ 
 This is the complete code of Firestorm Source Engine written in C++ using OpenGL.
 It should be buildable on Windows and Linux, but it's not tested on windows.

 The code is all licensed under the terms of the GPL (gnu public license).  
 You should read the entire license, but the gist of it is that you can do 
 anything you want with the code, except selling your new version, unless we 
 get to an agreement.  The catch is that if you distribute new binary versions,
 you are required to make the entire source code available for free to everyone.

 The primary intent of this release is for entertainment and educational 
 purposes, but the GPL does allow commercial exploitation if you obey the 
 full license.  If you want to do something commercial and you just can't bear 
 to have your source changes released, we could still negotiate a separate 
 license agreement (for $$$), but I would encourage you to just live with the 
 GPL.
 
 ~ Pentabonyx Software
