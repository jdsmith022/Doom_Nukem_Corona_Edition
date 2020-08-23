#include "../../includes/doom.h"
#include "../../includes/audio.h"

static void		void_free_lib(void *lib)
{
	ft_bzero(lib, sizeof(lib));
	free(lib);
}

static void	free_audio_lib(t_doom *doom)
{
	if (doom->audio->event)
		void_free_lib(doom->audio->event);
	if (doom->audio->path)
		void_free_lib(doom->audio->path);
	while (*doom->audio->sounds)
	{
		void_free_lib(*doom->audio->sounds);
		(*doom->audio->sounds)++;
	}
	if (doom->audio)
		void_free_lib(doom->audio);
}

static void	free_font_lib(t_doom *doom)
{
	if (doom->lib.font_lib.game_editor_font)
		void_free_lib(doom->lib.font_lib.game_editor_font);
	if (doom->lib.font_lib.hud_font)
		void_free_lib(doom->lib.font_lib.hud_font);
	if (doom->lib.font_lib.start_menu_font)
		void_free_lib(doom->lib.font_lib.start_menu_font);
	if (doom->lib.font_lib.setting_menu_font)
		void_free_lib(doom->lib.font_lib.setting_menu_font);
	if (doom->lib.font_lib.game_over_font)
		void_free_lib(doom->lib.font_lib.game_over_font);
	if (doom->lib.font_lib.instruction_font)
		void_free_lib(doom->lib.font_lib.instruction_font);
}

static void	free_game_design_lib(t_doom *doom)
{
	if (doom->game_design.sector)
		void_free_lib(doom->game_design.sector);
	if (doom->game_design.sidedef)
		void_free_lib(doom->game_design.sidedef);
}

void		free_struct_lib(t_doom *doom)
{
	if (doom->lib.sector)
		void_free_lib(doom->lib.sector);
	if (doom->lib.sidedef)
		void_free_lib(doom->lib.sidedef);
	if (doom->lib.sprites)
		void_free_lib(doom->lib.sprites);
	if (doom->groceries)
		void_free_lib(doom->groceries);
	if (doom->hud)
		void_free_lib(doom->hud);
	if (doom->menu)
		void_free_lib(doom->menu);
	free_font_lib(doom);
	free_audio_lib(doom);
}

static void		free_sld_libs(SDL_Surface **lib, int len)
{
	size_t index;

	index = 0;
	while (index < len)
	{
		ft_bzero(lib[index], sizeof(lib[index]));
		free(lib[index]);
		index++;
	}
	free(lib);
}

void		free_sdl_lib(t_doom *doom)
{
	SDL_Surface	**lib;
	int			len;

	if (doom->lib.tex_lib)
	{
		lib = doom->lib.tex_lib;
		len = doom->lib.len_tex_lib;
		free_sld_libs(lib, len);
	}
	if (doom->lib.obj_lib)
	{
		lib = doom->lib.obj_lib;
		len = doom->lib.len_obj_lib;
		free_sld_libs(lib, len);
	}
	if (doom->lib.sky_lib)
	{
		lib = doom->lib.sky_lib;
		len = doom->lib.len_sky_lib;
		free_sld_libs(lib, len);
	}
}
