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
	audio->music = Mix_LoadMUS(ft_strjoin(AUDIO_PATH, MU_1));
}

void	movement_sounds(t_audio audio, t_event *event)
{
	if (event->jump == false)
		event->s_jump_started = false;
	if (event->cam_move_f || event->cam_move_b)
		loop_sound(audio.sounds[0], 1);
	else if (!event->cam_move_f && !event->cam_move_b)
		pause_sound(audio.sounds[0], 1);
	else if (event->cam_move_l || event->cam_move_r)
		loop_sound(audio.sounds[0], 1);
	if (event->jump && !event->s_jump_started){
		pause_sound(audio.sounds[0], 1);
		play_sound(audio.sounds[2], 2);
		event->s_jump_started = true;
	}
}

void	audio(t_audio audio, t_event *event)
{
	play_music(audio.music);
	movement_sounds(audio, event);
	return;
}
