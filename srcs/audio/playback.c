#include "../../includes/doom.h"

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
