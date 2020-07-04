#include "audio.h"

// DONE
// Background music plays
// Sound triggers on key input

// TODO
// Prevent Sound from repeating when holding a key
// 

// FUNCTIONS
// play_sound --> triggers a sound once
// loop_sound --> loops a sound infinitely, until paused/stopped
// stop_sound --> stops a sound
// play_music --> plays a track
// pause_music --> yep
// stop_music --> yep
// fade_out --> fades out a sound
// fade_in  --> fades in a sound
// get_volume --> decides volume for a sound (based on distance to an object)
// pause_sound --> pauses all sounds (when opening a menu for example)
// play_sound_rr --> plays a sound in round robin (footsteps, gunshots etc.)
// 

// Channels
// 1 2 3 4

void	play_music(Mix_Music *music){
	if (!Mix_PlayingMusic())
		Mix_PlayMusic(music, 1);
}

void	play_sound(Mix_Chunk *sample, int channel){
	if (!Mix_Playing(channel))
		Mix_PlayChannel(channel, sample, 0);
}

void	loop_sound(Mix_Chunk *sample, int channel){
	if (!Mix_Playing(channel)){
		Mix_PlayChannel(channel, sample, -1);
	}
	else if (Mix_Paused(channel)){
		Mix_Resume(channel);
		SDL_Log("Resumed channel %d", channel);
	}
}

void	pause_sound(Mix_Chunk *sample, int channel){
	if (!Mix_Paused(channel)){
		Mix_Pause(channel);
		SDL_Log("Paused channel %d", channel);
	}
}

void	init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO))
    	exit_error(SDL_GetError());
	sdl->window = SDL_CreateWindow("SDL_AUDIO",
									SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED,
									640, 480, 0);
	sdl->renderer = SDL_CreateRenderer(sdl->window, -1, 0);
}

void	init_audio(t_audio *audio)
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, AUDIO_BUFF) == -1)
    	exit_error(Mix_GetError());
	Mix_QuerySpec(&audio->sample_rate, &audio->format, &audio->channels);
	SDL_Log("%dHz %dbit %d %d buff\n", audio->sample_rate, (audio->format&0xFF), audio->channels, AUDIO_BUFF);
}

void	load_audio(t_audio *audio)
{
	uint8_t i;

	i = 0;
	audio->sounds[0] = Mix_LoadWAV(ft_strjoin(AUDIO_PATH, S_FOOTSTEPS));
	audio->sounds[1] = Mix_LoadWAV(ft_strjoin(AUDIO_PATH, S_UI_1));
	while (i < NUM_OF_SOUNDS){
		if (!audio->sounds[i])
			ft_printf("Mix_LoadWAV: %s %s\n", Mix_GetError());
		i++;
	}
	Mix_AllocateChannels(2);
	Mix_Volume(-1, MIX_MAX_VOLUME / 2);
	audio->music = Mix_LoadMUS(MU_1);
}

void		load_image(t_sdl *sdl)
{
	int			fd;
	t_bmp		bmp;
	SDL_Surface *surface;

	fd = open(BMP_7X7, O_RDONLY);
	bmp = read_bmp(fd);
	surface = SDL_LoadBMP(BMP_7X7);
	surface->pixels = bmp.pixels;
	sdl->texture = SDL_CreateTextureFromSurface(sdl->renderer, surface);
}

void	draw_image(t_sdl sdl)
{
	sdl.rect.x = 50;
    sdl.rect.y = 50;
    sdl.rect.w = 100;
    sdl.rect.h = 100;
	// Set the color to cornflower blue and clear
	SDL_SetRenderDrawColor(sdl.renderer, 0, 0, 0, 255);
	SDL_RenderClear(sdl.renderer);
	SDL_RenderCopy(sdl.renderer, sdl.texture, NULL, &sdl.rect);
	// Show the renderer contents
	SDL_RenderPresent(sdl.renderer);
}

int		main(void)
{
	t_sdl		sdl;
	t_audio		audio;
	SDL_Event	event;

	init_sdl(&sdl);
	init_audio(&audio);
	load_audio(&audio);
	load_image(&sdl);

	sdl.quit = false;
	const uint8_t *keys;
	// bool key_changed = false;
	keys = SDL_GetKeyboardState(NULL);
	while (!sdl.quit)
	{
		// play_music(audio.music);
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN){
			keys = SDL_GetKeyboardState(NULL);
			if (keys[SDL_SCANCODE_W]){
				loop_sound(audio.sounds[0], 1);
			} 
			else if (keys[SDL_SCANCODE_SPACE]){
				play_sound(audio.sounds[1], 0);
			}
		}
		else if (event.type == SDL_KEYUP){
			keys = SDL_GetKeyboardState(NULL);
			if (!keys[SDL_SCANCODE_W]){
				pause_sound(audio.sounds[0], 1);
			}
		}
		draw_image(sdl);
		if (event.type == SDL_QUIT)
			sdl.quit = true;
	}
	Mix_CloseAudio();
	SDL_DestroyRenderer(sdl.renderer);
	SDL_DestroyWindow(sdl.window);
	SDL_Quit();
	return (0);
}
