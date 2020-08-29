/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_texture.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:02:42 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/29 14:02:49 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"


void		add_tint_to_color(Uint32 *color, int tint, int mask)
{
	Uint8	r;
	Uint8	g;
	Uint8	b;

	r = ((*color >> 16) & mask);
	g = ((*color >> 8) & mask);
	b = (*color & mask);
	if (tint == BLUE)
		b += 30;
	else if (tint == RED)
		r += 30;
	else
		g += 30;
	*color = (r << 16 | g << 8 | b);
}

static void	light_correct(double *r, double *g, double *b, double light)
{
	if (*r < 0.0)
		*r += 255.0;
	if (*g < 0.0)
		*g += 255.0;
	if (*b < 0.0)
		*b += 255.0;
	*r *= light;
	*g *= light;
	*b *= light;
}

void		add_saturation(Uint8 *r, Uint8 *g, Uint8 *b, double light)
{
	double r1;
	double g1;
	double b1;

	r1 = (double)*r;
	g1 = (double)*g;
	b1 = (double)*b;
	light_correct(&r1, &g1, &b1, light);
	if (r1 < 0.0)
		r1 = 0;
	if (g1 < 0.0)
		g1 = 0;
	if (b1 < 0.0)
		b1 = 0;
	if (r1 > 255.0)
		r1 = 255.0;
	if (g1 > 255.0)
		g1 = 255.0;
	if (b1 > 255.0)
		b1 = 255.0;
	*r = r1;
	*g = g1;
	*b = b1;
}

void		put_texture(t_doom *doom, Uint32 tex_dex, Uint32 index,
					Uint32 pixel_dex)
{
	char	*pixels;
	char	*texture;
	Uint8	r;
	Uint8	g;
	Uint8	b;

	pixels = doom->surface->pixels;
	texture = doom->lib.tex_lib[tex_dex]->pixels;
	r = texture[pixel_dex];
	g = texture[pixel_dex + 1];
	b = texture[pixel_dex + 2];
	if (texture[pixel_dex] == (char)255 && \
	texture[pixel_dex + 1] == (char)255 && \
	texture[pixel_dex + 2] == (char)255)
		return ;
	else
	{
		add_saturation(&r, &g, &b, doom->distance);
		pixels[index] = r;
		index++;
		pixels[index] = g;
		index++;
		pixels[index] = b;
	}
}
