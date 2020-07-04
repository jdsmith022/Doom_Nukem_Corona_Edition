#include "audio.h"

void				exit_error(const char *message)
{
	ft_putstr_fd(message, 2);
	exit(1);
}
