#include "../../includes/doom.h" 
#include "../../includes/audio.h"

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

// Channels
// 1 2 3 4

void	init_audio(t_doom *doom)
{
	t_audio_event	*event;
	char			path_buff[PATH_MAX];

	event = (t_audio_event *)ft_memalloc(sizeof(t_audio_event)); // NOTE: FREE
	doom->audio = (t_audio *)ft_memalloc(sizeof(t_audio)); // NOTE: FREE
	doom->audio->event = event;
	doom->audio->music_vol = FALSE;
	doom->audio->sound_vol = TRUE;
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, AUDIO_BUFF) == -1)
    	exit_error(Mix_GetError());
	Mix_QuerySpec(&doom->audio->sample_rate, &doom->audio->format, &doom->audio->channels);
	Mix_AllocateChannels(3);
	Mix_Volume(-1, MIX_MAX_VOLUME / 2);
	SDL_Log("%dHz %dbit %d %d buff\n", doom->audio->sample_rate, (doom->audio->format&0xFF), doom->audio->channels, AUDIO_BUFF);
	getcwd(path_buff, sizeof(path_buff));
	doom->audio->path = ft_strjoin(path_buff, "/sounds"); // NOTE: FREE
	if (!ft_strlen(doom->audio->path))
		exit_error("Cannot find working directory\n");
}

void	load_audio(t_audio *audio)
{
	uint8_t i;

	i = 0;
	printf("Loading audio...\n");
	audio->sounds[0] = Mix_LoadWAV(ft_strjoin(AUDIO_PATH, S_FOOTSTEPS));
	audio->sounds[1] = Mix_LoadWAV(ft_strjoin(AUDIO_PATH, S_UI_1));
	audio->sounds[2] = Mix_LoadWAV(ft_strjoin(AUDIO_PATH, S_JUMP));
	audio->music = Mix_LoadMUS(ft_strjoin(AUDIO_PATH, MU_1));
	printf("%s\n", audio->path);
	while (i < NUM_OF_SOUNDS){
		if (!audio->sounds[i])
			printf("Mix_LoadWAV: %s\n", Mix_GetError());
		i++;
	}
	printf("Loading audio completed\n");
}

void	play_movement_sounds(t_audio *audio, t_event *event)
{
	if (event->jump == FALSE)
		audio->event->jump_toggled = FALSE;
	if (event->cam_move_f || event->cam_move_b)
		loop_sound(audio->sounds[0], 1);
	else
		pause_sound(audio->sounds[0], 1);
	if (event->cam_move_l || event->cam_move_r)
		loop_sound(audio->sounds[0], 1);
	if (event->jump && !audio->event->jump_toggled){
		pause_sound(audio->sounds[0], 1);
		play_sound(audio->sounds[2], 2);
		audio->event->jump_toggled = TRUE;
	}
}

void	audio(t_audio *audio, t_event *event)
{
	if (audio->engine == OFF)
		return ;
	if (audio->music_vol)
		play_music(audio->music);
	if (audio->sound_vol)
		play_movement_sounds(audio, event);
}
