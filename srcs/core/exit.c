#include "../../includes/doom.h"
#include "../../includes/menu.h"

void			doom_exit_lib_failure(t_bmp *bmp, const char *exit_meassge)
{
	ft_putendl(exit_meassge);
	ft_bzero(bmp, sizeof(bmp));
	free(bmp);
}

static void		sdl_window_screen_free(t_doom *doom)
{
	if (doom->window)
	{
		ft_bzero(doom->window, sizeof(doom->window));
		free(doom->window);
	}
	if (doom->surface)
	{
		ft_bzero(doom->window, sizeof(doom->surface));
		free(doom->surface);
	}
}

void			doom_exit_failure(t_doom *doom, const char *exit_message)
{
	ft_putendl(exit_message);
	sdl_window_screen_free(doom);
	free_sdl_lib(doom);
	free_struct_lib(doom);
	ft_bzero(doom, sizeof(doom));
	exit(EXIT_FAILURE);
}

void			doom_retry(t_doom *doom)
{
	// free_sdl_lib(doom);
	// free_struct_lib(doom);
	// ft_bzero(doom, sizeof(doom));
	ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
}

void			doom_exit_success(t_doom *doom)
{
	free_sdl_lib(doom);
	free_struct_lib(doom);
	ft_bzero(doom, sizeof(doom));
	sdl_window_screen_free(doom);
	SDL_DestroyWindow(doom->window);  // Closes and destroys the window and image
	exit(EXIT_SUCCESS);
}
