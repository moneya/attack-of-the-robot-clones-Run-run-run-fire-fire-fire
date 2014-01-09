#include <allegro.h>
#include <time.h>
#include <stdlib.h>
#include "game.h"
#include <string>
using namespace std;

Game::Game( )
{
     buffer = NULL;
     screen_Y = 480;
     screen_X = 640;
     level=1;
     score = 0;
     lives = 3;
     status = 1;
     
}

Game::~Game()
{
	destroy_bitmap(buffer); 
} 

void Game::SetUpGame()
{
    int depth, res;
	
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, screen_X,screen_Y, 0, 0);
	
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
}
void Game::CloseGame()
{
     
     clear_keybuf();
}

void Game::InitScreen()
{
     buffer = create_bitmap(screen_X,screen_Y);
}

void Game::DrawPicturetoBuffer(BITMAP *drawThis, int x, int y)
{
     draw_sprite(buffer, drawThis, x, y);
     //destroy_bitmap(imgToDraw);
}

void Game::EraseFromBuffer(int objx, int objy, int widthx, int widthy)
{
     rectfill( buffer, objx, objy, objx + widthx, objy + widthy, makecol ( 0, 0, 0)); 
   // destroy_bitmap(objectToDraw); 
    // textout_ex( screen, font, "in func", 320, 240, makecol( 255, 0, 0), makecol( 0, 0, 0));    
}

void Game::DrawBuffertoScreen()
{
     blit(buffer, screen, 0,0,0,0,screen_X,screen_Y); // Draw the buffer to the screen 
     clear_bitmap(buffer); // Clear the contents of the buffer bitmap 
     //destroy_bitmap(buffer);
}


void Game::SetLevel(int l)
{
    level = l;
} 


void Game::SetScore(int s)
{
    score += s;
} 

void Game::LoseLives()
{
   lives -= 1;
} 


void Game::IngameText()
{
      textprintf_ex(buffer, font, 10, 10, makecol(255, 100, 200), -1, "Robot Attack... of the clones... Episode 23... RUN RUN RUN... FIRE FIRE FIRE!", level);    
      textprintf_ex(buffer, font, 500, 470, makecol(255, 100, 200), -1, "Score: %d", score);
      textprintf_ex(buffer, font, 420, 470, makecol(255, 100, 200), -1, "Level: %d", level);
      textprintf_ex(buffer, font, 340, 470, makecol(255, 100, 200), -1, "Lives: %d", lives);
}
