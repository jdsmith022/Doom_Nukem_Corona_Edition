#include "../../includes/doom.h"
#include "../../includes/audio.h"

static void	init_paths(t_doom *doom){
	char			path_buff[PATH_MAX];

	getcwd(path_buff, sizeof(path_buff));
	if (!ft_strlen(path_buff))
		exit_error(doom, "Cannot find working directory\n");
	doom->audio->path = ft_strjoin(path_buff, "/sounds");
	if (doom->audio->path == NULL)
		doom_exit_failure(doom, "error: audio path malloc");
}

static void	load_audio(t_doom *doom, t_audio *audio)
{
	uint8_t i;

	i = 0;
	while (i < NUM_OF_SOUNDS)
	{
		audio->sounds[i] = \
			Mix_LoadWAV(ft_strjoin(AUDIO_PATH, AUDIO_PATHS[i]));
		i++;
	}
	audio->music[0] = Mix_LoadMUS(ft_strjoin(AUDIO_PATH, MU_1));
	audio->music[1] = Mix_LoadMUS(ft_strjoin(AUDIO_PATH, MU_2));
	if (audio->music[0] == NULL || audio->music[1] == NULL)
		doom_exit_failure(doom, "error: audio music malloc");
	Mix_PlayMusic(audio->music[0], -1);
	while (i < NUM_OF_SOUNDS)
	{
		if (!audio->sounds[i])
			printf("Mix_LoadWAV: %s\n", Mix_GetError());
		i++;
	}
}

void	init_audio(t_doom *doom)
{
	t_audio_event	*event;

	doom->audio = (t_audio *)ft_memalloc(sizeof(t_audio));
	if (doom->audio == NULL)
		doom_exit_failure(doom, "error: audio malloc");
	doom->audio->engine = ON;
	if (!doom->audio || doom->audio->engine == OFF)
		return ;
	event = (t_audio_event *)ft_memalloc(sizeof(t_audio_event));
	if (event == NULL)
		doom_exit_failure(doom, "error: audio event malloc");
	doom->audio->event = event;
	doom->audio->music_vol = TRUE;
	doom->audio->sound_vol = TRUE;
	doom->audio->event->groc_pickup = FALSE;
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, \
	MIX_DEFAULT_CHANNELS, AUDIO_BUFF) == -1)
		exit_error(doom, Mix_GetError());
	Mix_QuerySpec(&doom->audio->sample_rate, &doom->audio->format, \
		&doom->audio->channels);
	Mix_AllocateChannels(3);
	Mix_Volume(-1, MIX_MAX_VOLUME / 2);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
	init_paths(doom);
	load_audio(doom, doom->audio);
}
