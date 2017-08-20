
/*
 // Disclaimer:
 // ----------
 //
 // This code will work only if you selected window, graphics and audio.
 //
 // Note that the "Run Script" build phase will copy the required frameworks
 // or dylibs to your application bundle so you can execute it on any OS X
 // computer.
 //
 // Your resource files (images, sounds, fonts, ...) are also copied to your
 // application bundle. To get the path to these resources, use the helper
 // function `resourcePath()` from ResourcePath.hpp
 //
 // Sounds from: http://www.bigsoundbank.com/
 //
 Future:  Randomly Generate Ball position
 Create paddle and ball based on screen size
 Game State MAchine
 Menu System
 Sound
 Difficulty
 CPU player vs Two player
 Splash Screen
 Take button press before starting game
 Pause menu
 
 */




#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
//#include "stdafx.h"
#include "Bat.hpp"
#include "Ball.hpp"
#include <cstdlib>
#include "Globals.h"
#include "Game.hpp"

// File path helper
#include "ResourcePath.hpp"

int main(int, char const**)
{
    Game pongGame;
    pongGame.initialize();
    pongGame.setup();
    pongGame.execute();
    
    return EXIT_SUCCESS;
}
