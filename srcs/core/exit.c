#include "../../includes/doom.h"

void        doom_exit_lib_failure(t_bmp *bmp, const char *exit_meassge)
{
    ft_putendl(exit_meassge);
    ft_bzero(bmp, sizeof(bmp));
    free(bmp);
}

static void sdl_free(t_doom *doom)
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

void        doom_exit_failure(t_doom *doom, const char *exit_message)
{
    ft_putendl(exit_message);
    sdl_free(doom);
    ft_bzero(doom, sizeof(doom));
    exit(EXIT_FAILURE);
}

void        doom_exit_success(t_doom *doom)
{
    sdl_free(doom);
    ft_bzero(doom, sizeof(doom));
   // SDL_DestroyWindow(doom->window);  // Closes and destroys the window and image
   // SDL_DestroyRenderer(doom.surface);  // Cleans up and exits all SDL processes
    SDL_Quit();
    exit(EXIT_SUCCESS);
}