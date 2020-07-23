#include "../../includes/doom.h"
#include "../../includes/audio.h"

void	play_music(Mix_Music *music){
	if (!Mix_PlayingMusic()){
		Mix_PlayMusic(music, -1);
		SDL_Log("Playing music");
	}
}

void	play_sound(Mix_Chunk *sample, int channel){
	if (!Mix_Playing(channel)){
		Mix_PlayChannel(channel, sample, 0);
		SDL_Log("Playing channel %d", channel);
	} else {
		SDL_Log("Channel %d is busy", channel);
	}
}

void	loop_sound(Mix_Chunk *sample, int channel){
	if (!Mix_Playing(channel)){
		Mix_PlayChannel(channel, sample, -1);
		SDL_Log("Looping channel %d", channel);
	}
	else if (Mix_Paused(channel)){
		Mix_Resume(channel);
		SDL_Log("Resuming looping channel %d", channel);
	}
}

void	pause_sound(Mix_Chunk *sample, int channel){
	if (!Mix_Playing(channel))
		return ;
	else if (!Mix_Paused(channel)){
		Mix_Pause(channel);
		SDL_Log("Pausing channel %d", channel);
	}
}
