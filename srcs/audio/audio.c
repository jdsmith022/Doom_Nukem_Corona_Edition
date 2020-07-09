#include "../../includes/doom.h"

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

void	init_audio(t_audio *audio)
{
	if (!audio)
		return ;
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, AUDIO_BUFF) == -1)
    	exit_error(Mix_GetError());
	Mix_QuerySpec(&audio->sample_rate, &audio->format, &audio->channels);
	SDL_Log("%dHz %dbit %d %d buff\n", audio->sample_rate, (audio->format&0xFF), audio->channels, AUDIO_BUFF);
}

void	load_audio(t_audio *audio)
{
	uint8_t i;

	i = 0;
	printf("Loading audio...\n");
	audio->sounds[0] = Mix_LoadWAV(ft_strjoin(AUDIO_PATH, S_FOOTSTEPS));
	audio->sounds[1] = Mix_LoadWAV(ft_strjoin(AUDIO_PATH, S_UI_1));
	audio->sounds[2] = Mix_LoadWAV(ft_strjoin(AUDIO_PATH, S_JUMP));
	while (i < NUM_OF_SOUNDS){
		if (!audio->sounds[i])
			printf("Mix_LoadWAV: %s\n", Mix_GetError());
		i++;
	}
	printf("Loading audio complete\n");
	Mix_AllocateChannels(3);
	Mix_Volume(-1, MIX_MAX_VOLUME / 2);
	audio->music = Mix_LoadMUS(MU_1);
}

void	audio(t_audio audio, t_event event)
{
	if (event.cam_move_f || event.cam_move_b)
		loop_sound(audio.sounds[0], 1);
	else if (!event.cam_move_f && !event.cam_move_b)
		pause_sound(audio.sounds[0], 1);
	if (event.jump){
		pause_sound(audio.sounds[0], 1);
		play_sound(audio.sounds[2], 2);
	}
	return;
}

	// sdl.quit = false;
	// const uint8_t *keys;
	// // bool key_changed = false;
	// keys = SDL_GetKeyboardState(NULL);
	// while (!sdl.quit)
	// {
	// 	// play_music(audio.music);
	// 	SDL_PollEvent(&event);
	// 	if (event.type == SDL_KEYDOWN){
	// 		keys = SDL_GetKeyboardState(NULL);
	// 		if (keys[SDL_SCANCODE_W]){
	// 			loop_sound(audio.sounds[0], 1);
	// 		} 
	// 		else if (keys[SDL_SCANCODE_SPACE]){
	// 			play_sound(audio.sounds[1], 0);
	// 		}
	// 	}
	// 	else if (event.type == SDL_KEYUP){
	// 		keys = SDL_GetKeyboardState(NULL);
	// 		if (!keys[SDL_SCANCODE_W]){
	// 			pause_sound(audio.sounds[0], 1);
	// 		}
	// 	}
	// 	draw_image(sdl);
	// 	if (event.type == SDL_QUIT)
	// 		sdl.quit = true;
	// }
	// Mix_CloseAudio();
	// SDL_DestroyRenderer(sdl.renderer);
	// SDL_DestroyWindow(sdl.window);
	// SDL_Quit();
	// return (0);