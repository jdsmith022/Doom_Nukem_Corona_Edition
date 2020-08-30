#include "../../includes/doom.h"
#include "../../includes/audio.h"

void	stop_sounds(void)
{
	Mix_HaltChannel(-1);
	Mix_HaltMusic();
}
