/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_sidedef.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 10:43:52 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/06 19:32:04 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/read.h"

static void		moving_sidedef(t_doom *doom, t_sidedef *sidedef, int k, int i)
{
	create_mv_sidedef(doom, doom->lib.sidedef, k);
	doom->lib.len_sidedef++;
	doom->lib.sector[i].n_sidedefs++;
}

static void		set_col_lib(t_doom *doom, int k, int *total_sd_index, int i)
{

	if (k != 0)
		*total_sd_index += doom->lib.sector[i].i_sidedefs;
	doom->lib.sector[i].i_sidedefs = k;
}

static void		set_sidedef_slope(t_doom *doom, int k, int i)
{
	if (doom->lib.sidedef[k].action == 3 || doom->lib.sidedef[k].action == 5)
		doom->lib.sector[i].slope_floor_id = doom->lib.sidedef[k].id;
	if (doom->lib.sidedef[k].action == 4 || doom->lib.sidedef[k].action == 5)
		doom->lib.sector[i].slope_ceiling_id = doom->lib.sidedef[k].id;
}

void			create_sidedef(t_doom *doom, int fd, int len,
					int i)
{
	static int	k;
	static int	total_sd_index;
	int			sidedef_in_sector;

	if (!k)
	{
		k = 0;
		total_sd_index = 0;
	}
	doom->lib.sector[i] = sector_inf(doom, fd, doom->lib.len_tex_lib);
	set_col_lib(doom, k, &total_sd_index, i);
	sidedef_in_sector = 0;
	while (sidedef_in_sector < doom->lib.sector[i].n_sidedefs)
	{
		doom->lib.sidedef[k] = wall_inf(doom, fd, i, len);
		doom->lib.sidedef[k].id = total_sd_index;
		set_sidedef_slope(doom, k, i);
		if (doom->lib.sidedef[k].action == 2 && \
		doom->lib.sidedef[k].opp_sector != -1)
		{
			k++;
			moving_sidedef(doom, doom->lib.sidedef, k, i);
			total_sd_index++;
			sidedef_in_sector++;
		}
		k++;
		sidedef_in_sector++;
		total_sd_index++;
	}
}
