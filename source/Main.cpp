#include "SDL.h"
#include "SDL_syswm.h"


#include <stdio.h>
#include <string>

#include "lodepng.h"

#include "TileImage.h"
#include "BitmapFont.h"
#include "SoundUtils.h"



// variable declarations
static Uint8 *audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play
char slash = '/';



// audio callback function
// here you have to copy the data of your audio buffer into the
// requesting audio buffer (stream)
// you should only copy as much as the requested length (len)
void my_audio_callback(void *userdata, Uint8 *stream, int len) {

	if (audio_len == 0)
		return;

	len = (len > audio_len ? audio_len : len);
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
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		return 1;

#ifdef WIN32
	slash = '\\';
#endif
	std::string exePath = argv[0];
	//std::size_t found = exePath.find_last_of("/\\");
	//std::string path = exePath.substr(0, found);

	//find the project folder
	std::string baseFolderName = "GameUtilsTest";
	size_t found = exePath.find(baseFolderName);
	size_t folderNameLength = found + baseFolderName.size();

	std::string path = exePath.substr(0, folderNameLength);
	

	std::string soundPath = path + slash + "sounds" + slash + "snd.wav";
	std::string imgPath =  path + slash + "images" + slash + "img.png";
	static SDL_AudioSpec wav_spec; // the specs of our piece of music
	SDL_AudioFormat x;

	/*SoundUtils *sound = new SoundUtils(soundPath.c_str());
		
	static Uint32 wav_length; // length of our sample
	static Uint8 *wav_buffer; // buffer containing our audio file
	//if (SDL_LoadWAV(soundPath.c_str(), &wav_spec, &wav_buffer, &wav_length) == NULL) {
	//	return 1;
	//}
	wav_spec.freq = sound->avg_bytes_sec;                   //< DSP frequency -- samples per second 
	wav_spec.format = 32784;     //< Audio data format 
	wav_spec.channels = sound->channels;             //< Number of channels: 1 mono, 2 stereo 
	wav_spec.silence = 0;              //< Audio buffer silence value (calculated) 
	wav_spec.samples = BIG_SOUND_BUFFER;             //< Audio buffer size in samples (power of 2) 
	wav_spec.padding = 0;             //< Necessary for some compile environments 
	wav_spec.size = sound->data_size;                //< Audio buffer size in bytes (calculated) 
	
	// set the callback function
	wav_spec.callback = my_audio_callback;
	wav_spec.userdata = NULL;
	*/

	// Open the audio device 
	if (SDL_OpenAudio(&wav_spec, NULL) < 0) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		exit(-1);
	}

	SDL_Window * window = SDL_CreateWindow("SDL2 Pixel Drawing",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenW, screenH, 0);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, screenW, screenH);
	
	PIXMAP *clippedImg = new PIXMAP(100, 100);
	PIXMAP *img2 = new PIXMAP(10, 10);
	PIXMAP *photo;

	//we can load 8 or 16 bit pngs
	int iBitDepth = 8, iWidth = 256, iHeight = 128;
	unsigned char *pix;
	int error = lodepng_decode_file(&pix,(unsigned int*)&iWidth, (unsigned int*)&iHeight, imgPath.c_str(),LCT_RGBA, iBitDepth);
	if (error != 0)
	{
		printf("lodepng error: %d\ncouldt open a file\n%s\n", error,imgPath.c_str() );
		exit(1);
	}
	photo = new PIXMAP(pix, iWidth, iHeight, true);


	RGBA color1(255,0,0,255);
	RGBA color2( 0,255,0,255 );
	clippedImg->Fill(color1);
	img2->Fill(color2);
	
	Uint32 * rawPixels = new Uint32[screenW * screenH];
	memset(rawPixels, 100, screenW * 240 * sizeof(Uint32));
	memset(&rawPixels[153600], 200, screenW * 240 * sizeof(Uint32));

	PIXMAP *screen = new PIXMAP(rawPixels, screenW, screenH);
	clippedImg->Blit(screen,750,550);
	photo->Blit(screen, 100, 100);
	

	
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
				SDL_PauseAudio(1);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				leftMouseButtonDown = true;

				/*audio_pos = sound->GetSoundBuffer();
				audio_len = sound->GetSoundSize(); // copy file length

				SDL_PauseAudio(0);//unpause

				// wait until we're don't playing
				while (audio_len > 0) {
					SDL_Delay(100);
				}*/
			}
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
	SDL_CloseAudio();
	//SDL_FreeWAV(wav_buffer);
	SDL_Quit();

	return 0;
}