#include "../../includes/doom.h" 
#include "../../includes/audio.h"

static void	init_paths(t_doom *doom){
	char			path_buff[PATH_MAX];

	getcwd(path_buff, sizeof(path_buff));
	if (!ft_strlen(path_buff))
		exit_error("Cannot find working directory\n");
	doom->audio->path = ft_strjoin(path_buff, "/sounds"); // NOTE: FREE
}

void	init_audio(t_doom *doom)
{
	t_audio_event	*event;

	event = (t_audio_event *)ft_memalloc(sizeof(t_audio_event)); // NOTE: FREE
	doom->audio = (t_audio *)ft_memalloc(sizeof(t_audio)); // NOTE: FREE
	doom->audio->event = event;
	doom->audio->music_vol = FALSE;
	doom->audio->sound_vol = TRUE;
	if (Mix_OpenAudio(
			MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 
			MIX_DEFAULT_CHANNELS, AUDIO_BUFF
		) == -1)
    	exit_error(Mix_GetError());
	Mix_QuerySpec(
		&doom->audio->sample_rate, 
		&doom->audio->format, 
		&doom->audio->channels
	);
	Mix_AllocateChannels(3);
	Mix_Volume(-1, MIX_MAX_VOLUME / 2);
	init_paths(doom);
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
	if (event->move_pos_f || event->move_pos_b)
		loop_sound(audio->sounds[0], 1);
	else
		pause_sound(audio->sounds[0], 1);
	if (event->move_pos_l || event->move_pos_r)
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
