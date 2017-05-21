#include "SDL.h"
//#include "SDL_ttf.h"
#include "SDL_syswm.h"
#include <SDL_image.h>

#include <stdio.h>
#include <string>

#include "lodepng.h"

#include "TileImage.h"
#include "BitmapFont.h"


int main(int argc, char ** argv)
{
	bool leftMouseButtonDown = false;
	bool quit = false;
	SDL_Event event;
	int screenW = 800, screenH = 600;
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window * window = SDL_CreateWindow("SDL2 Pixel Drawing",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenW, screenH, 0);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	//SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, screenW, screenH); 
	SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, screenW, screenH);
	
	PIXMAP *clippedImg = new PIXMAP(100, 100);
	PIXMAP *img2 = new PIXMAP(10, 10);
	PIXMAP *photo;
//	Create1bppBin();
	//we can load 8 or 16 bit pngs
	int iBitDepth = 8, iWidth = 256, iHeight = 128;
	/*unsigned char *pix;
	int error = lodepng_decode_file(&pix,
		(unsigned int*)&iWidth, (unsigned int*)&iHeight,
		"D:\\source\\GameUtilsTest\\allegFont2.png",
		LCT_RGBA, iBitDepth);
		*/


	RGBA color1(255,0,0,255);
	RGBA color2( 0,255,0,255 );
	clippedImg->Fill(color1);
	img2->Fill(color2);
	
	Uint32 * rawPixels = new Uint32[screenW * screenH];
	memset(rawPixels, 100, screenW * 240 * sizeof(Uint32));
	memset(&rawPixels[153600], 200, screenW * 240 * sizeof(Uint32));

	PIXMAP *screen = new PIXMAP(rawPixels, screenW, screenH);
	clippedImg->Blit(screen,750,550);


/*	TileImage tiles((RGBA*)pix, iWidth, iHeight, 8, 8);
	unsigned char* letter = tiles.SaveBlockAsPNG((int)'T');
	//unsigned char* letter = tiles.SaveBlockAsPNG(7,5);

	//PIXMAP*bmpChar = new PIXMAP(letter, tiles.BLOCK_HEIGHT, tiles.BLOCK_HEIGHT);
	screen->CopyPixels(letter, 8, 8, 50, 50);*/
	
	StockBitmapFont testFont;
	testFont.Draw(screen, "abcdefghijklmnopqrstuvwxyz", 2,80);
	testFont.Draw(screen, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 2,90);
	testFont.Draw(screen, "0123456789", 2,100);
	testFont.Draw(screen, "!@#$%^&*()_+<>?:\";'/-=`~{}[]", 2,110);
	
	while (!quit)
	{
		SDL_UpdateTexture(texture, NULL, screen->pixels, screenW * sizeof(Uint32));
		SDL_WaitEvent(&event);

		switch (event.type)
		{
		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_ESCAPE)
				quit = true;
			break;

		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
				leftMouseButtonDown = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
				leftMouseButtonDown = true;
		case SDL_MOUSEMOTION:
			if (leftMouseButtonDown)
			{
				int mouseX = event.motion.x;
				int mouseY = event.motion.y;
				rawPixels[mouseY * 640 + mouseX] = 0;
			}
			break;
		case SDL_QUIT:
			quit = true;
			break;
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	delete[] rawPixels;
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
