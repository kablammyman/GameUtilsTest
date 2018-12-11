#include "SDL.h"

//#include "SDL_ttf.h"
#include "SDL_syswm.h"
//#include <SDL_image.h>

#include <stdio.h>
#include <string>

#include "lodepng.h"

#include "TileImage.h"
#include "BitmapFont.h"


// prototype for our audio callback
// see the implementation for more information
void my_audio_callback(void *userdata, Uint8 *stream, int len);

// variable declarations
static Uint8 *audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play

//https://gist.github.com/armornick/3447121

// audio callback function
// here you have to copy the data of your audio buffer into the
// requesting audio buffer (stream)
// you should only copy as much as the requested length (len)
void my_audio_callback(void *userdata, Uint8 *stream, int len) {

	if (audio_len == 0)
		return;

	len = (len > audio_len ? audio_len : len);
	//SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

	audio_pos += len;
	audio_len -= len;
}

int main(int argc, char ** argv)
{
	bool leftMouseButtonDown = false;
	bool quit = false;
	SDL_Event event;
	int screenW = 800, screenH = 600;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Init(SDL_INIT_AUDIO);

	// local variables
	static Uint32 wav_length; // length of our sample
	static Uint8 *wav_buffer; // buffer containing our audio file
	static SDL_AudioSpec wav_spec; // the specs of our piece of music


	SDL_Window * window = SDL_CreateWindow("SDL2 Pixel Drawing",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenW, screenH, 0);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	//SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, screenW, screenH); 
	SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, screenW, screenH);
	
	PIXMAP *clippedImg = new PIXMAP(100, 100);
	PIXMAP *img2 = new PIXMAP(10, 10);
	PIXMAP *photo;

	//we can load 8 or 16 bit pngs
	//int iBitDepth = 8, iWidth = 256, iHeight = 128;
	//unsigned char *pix;
	//int error = lodepng_decode_file(&pix,(unsigned int*)&iWidth, (unsigned int*)&iHeight,"D:\\source\\GameUtilsTest\\allegFont2.png",LCT_RGBA, iBitDepth);
	

	RGBA color1(255,0,0,255);
	RGBA color2( 0,255,0,255 );
	clippedImg->Fill(color1);
	img2->Fill(color2);
	
	Uint32 * rawPixels = new Uint32[screenW * screenH];
	memset(rawPixels, 100, screenW * 240 * sizeof(Uint32));
	memset(&rawPixels[153600], 200, screenW * 240 * sizeof(Uint32));

	PIXMAP *screen = new PIXMAP(rawPixels, screenW, screenH);
	clippedImg->Blit(screen,750,550);

			
	if (SDL_LoadWAV("D:\\source\\GameUtilsTest\\sounds\\snd.wav", &wav_spec, &wav_buffer, &wav_length) == NULL) {
		return 1;
	}
	// set the callback function
	wav_spec.callback = my_audio_callback;
	wav_spec.userdata = NULL;
	// set our global static variables
	audio_pos = wav_buffer; // copy sound buffer
	audio_len = wav_length; // copy file length

							/* Open the audio device */
	if (SDL_OpenAudio(&wav_spec, NULL) < 0) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		exit(-1);
	}

	



	


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
			{
				leftMouseButtonDown = false;
				/* Start playing */
				SDL_PauseAudio(0);
				// wait until we're don't playing
				while (audio_len > 0) {
					SDL_Delay(100);
				}
				SDL_PauseAudio(true);
				audio_pos = wav_buffer;
				audio_len = wav_length;
			}
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
	
	SDL_CloseAudio();
	SDL_FreeWAV(wav_buffer);

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
