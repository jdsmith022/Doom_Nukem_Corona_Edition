#include "../../includes/doom.h"
#include "../../includes/audio.h"

void	play_music(Mix_Music *music)
{
	if (!Mix_PlayingMusic())
		Mix_PlayMusic(music, -1);
}

void	resume_music(void)
{
	if (Mix_PausedMusic())
		Mix_ResumeMusic();
}

void	play_sound(Mix_Chunk *sample, int channel)
{
	Mix_PlayChannel(channel, sample, 0);
	SDL_Log("Played channel %d\n", channel);
}

void	loop_sound(Mix_Chunk *sample, int channel)
{
	if (!Mix_Playing(channel))
		Mix_PlayChannel(channel, sample, -1);
	else if (Mix_Paused(channel))
		Mix_Resume(channel);
}

void	pause_sound(Mix_Chunk *sample, int channel)
{
	if (!Mix_Playing(channel))
		return ;
	else if (!Mix_Paused(channel))
		Mix_Pause(channel);
}
