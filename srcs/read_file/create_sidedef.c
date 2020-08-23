#include "../../includes/doom.h"
#include "../../includes/read.h"

static void		moving_sidedef(t_doom *doom, t_sidedef *sidedef, int k, int i)
{
	create_mv_sidedef(doom, doom->lib.sidedef, k);
	doom->lib.len_sidedef++;
	doom->lib.sector[i].n_sidedefs++;
}

static void		set_col_lib(t_doom *doom, int *k, int *wall_int, int i)
{
	if (!*k)
	{
		*k = 0;
		*wall_int = 0;
	}
	else
		*wall_int = *wall_int + doom->lib.sector[i].i_sidedefs;
	doom->lib.sector[i].i_sidedefs = *wall_int;
}

static void	set_sidedef_slope(t_doom *doom, int k, int i)
{
	if (doom->lib.sidedef[k].action == 3 || doom->lib.sidedef[k].action == 5)
		doom->lib.sector[i].slope_floor_id = doom->lib.sidedef[k].id;
	if (doom->lib.sidedef[k].action == 4 || doom->lib.sidedef[k].action == 5)
		doom->lib.sector[i].slope_ceiling_id = doom->lib.sidedef[k].id;
}

void		create_sidedef(t_doom *doom, int fd, int len,
					int i)
{
	static int	k;
	static int	wall_int;
	static int	total_sd_index = 0;
	int			j;

	doom->lib.sector[i] = sector_inf(fd, doom->lib.len_tex_lib);
	set_col_lib(doom, &k, &wall_int, i);
	j = 0;
	while (j < doom->lib.sector[i].n_sidedefs)
	{
		doom->lib.sidedef[k] = wall_inf(fd, i, doom->lib.len_tex_lib, len);
		doom->lib.sidedef[k].id = total_sd_index;
		set_sidedef_slope(doom, k, i);
		if (doom->lib.sidedef[k].action == 2 && \
		doom->lib.sidedef[k].opp_sector != -1)
		{
			k++;
			moving_sidedef(doom, doom->lib.sidedef, k, i);
			total_sd_index++;
			j++;
		}
		k++;
		j++;
		total_sd_index++;
	}
	wall_int = wall_int + doom->lib.sector[i].n_sidedefs;
}