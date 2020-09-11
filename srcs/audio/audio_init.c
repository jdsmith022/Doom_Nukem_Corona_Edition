/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   audio_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:44:35 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/11 14:57:09 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/audio.h"

static void			init_paths(t_doom *doom)
{
	char			path_buff[PATH_MAX];

	getcwd(path_buff, sizeof(path_buff));
	if (!ft_strlen(path_buff))
		exit_error(doom, "Cannot find working directory\n");
	doom->audio->path = ft_strjoin(path_buff, "/sounds");
	if (doom->audio->path == NULL)
		doom_exit_failure(doom, "error: audio path malloc");
}

static void			load_rogue_audio(t_doom *doom, t_audio *audio)
{
	char			*path;

	path = ft_strjoin(audio->path, MU_1);
	audio->music[0] = Mix_LoadMUS(path);
	free(path);
	path = ft_strjoin(audio->path, MU_2);
	audio->music[1] = Mix_LoadMUS(path);
	free(path);
	if (audio->music[0] == NULL || audio->music[1] == NULL)
		doom_exit_failure(doom, "error: audio music malloc");
	Mix_PlayMusic(audio->music[0], -1);
}

static void			load_audio(t_doom *doom, t_audio *audio)
{
	uint8_t			i;
	char			*path;
	const char		*str;

	i = 0;
	while (i < NUM_OF_SOUNDS)
	{
		path = ft_strjoin(audio->path, g_audio_paths[i]);
		audio->sounds[i] =
			Mix_LoadWAV(path);
		free(path);
		i++;
	}
	load_rogue_audio(doom, audio);
	while (i < NUM_OF_SOUNDS)
	{
		if (!audio->sounds[i])
			doom_exit_failure(doom, "Audio file not found\n");
		i++;
	}
}

static void			set_audio_event(t_doom *doom)
{
	t_audio_event	*event;

	event = (t_audio_event *)ft_memalloc(sizeof(t_audio_event));
	if (event == NULL)
		doom_exit_failure(doom, "error: audio event malloc");
	doom->audio->event = event;
	doom->audio->music_vol = TRUE;
	doom->audio->sound_vol = TRUE;
	doom->audio->event->groc_pickup = FALSE;
	doom->audio->event->prev_scissor_state = FALSE;
}

void				init_audio(t_doom *doom)
{
	doom->audio = (t_audio *)ft_memalloc(sizeof(t_audio));
	if (doom->audio == NULL)
		doom_exit_failure(doom, "error: audio malloc");
	doom->audio->engine = ON;
	if (!doom->audio || doom->audio->engine == OFF)
		return ;
	set_audio_event(doom);
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
	MIX_DEFAULT_CHANNELS, AUDIO_BUFF) == -1)
		exit_error(doom, Mix_GetError());
	Mix_QuerySpec(&doom->audio->sample_rate, &doom->audio->format,
		&doom->audio->channels);
	Mix_AllocateChannels(CHANNELS);
	Mix_Volume(4, MIX_MAX_VOLUME / 9);
	Mix_Volume(5, MIX_MAX_VOLUME / 4);
	Mix_Volume(6, MIX_MAX_VOLUME / 4);
	Mix_Volume(7, MIX_MAX_VOLUME / 4);
	Mix_Volume(8, MIX_MAX_VOLUME / 4);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
	init_paths(doom);
	load_audio(doom, doom->audio);
}
