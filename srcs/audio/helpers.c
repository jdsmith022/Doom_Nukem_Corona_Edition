#include "../../includes/doom.h"
#include "../../includes/audio.h"

void				exit_error(t_doom *doom, const char *message)
{
	ft_putstr_fd(message, 2);
	doom_exit_failure(doom, "error: audio lib");
}
