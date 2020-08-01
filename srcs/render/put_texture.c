#include "../../includes/doom.h"

double		cmin(double a, double b, double c)
{
	if (a >= b && c >= b)
		return (b);
	if (b >= a && c >= a)
		return (a);
	else
		return (c);
}

double		cmax(double a, double b, double c)
{
	if (a <= b && c <= b)
		return (b);
	if (b <= a && c <= a)
		return (a);
	else
		return (c);
}

t_hsv	rgb_to_hsv(double r, double g, double b)
{
	t_hsv	hsv;
	double	min;
	double	max;
	double	diff;

	if (r < 0.0)
		r += 255.0;
	if (g < 0.0)
		g += 255.0;
	if (b < 0.0)
		b += 255.0;
	min = cmin(r, g, b);
	max = cmax(r, g, b);
	diff = max - min;
	hsv.b = max;
	if (max == min)
	{
		hsv.r = 0;
		hsv.g = 0;
		return(hsv);
	}
	if (diff != 0)
	{
		if (max == r)
			hsv.r = (g - b) / diff;
		else if (max == g)
			hsv.r = (b - r) / diff + 2.0;
		else if (max == b)
			hsv.r = (r - g) / diff + 4.0;
		hsv.r *= 60.0;
		if (hsv.r < 0.0)
			hsv.r += 360.0;
		if (max != 0)
			hsv.g = diff / max;
		else
		{
			hsv.g = diff;
			hsv.b = diff;
		}
	}
	return (hsv);
}

void		hsv_to_rgb(	t_hsv hsv, char *r, char *g, char *b)
{
	double C; 
	double X;
	double m;
	double Rs;
	double Gs;
	double Bs;
	
	C = hsv.b * hsv.g;
	X =  C * (1 - fabs(fmod(hsv.r/ 60.0, 2) - 1));
	m = hsv.b - C;
	if(hsv.r >= 0.0 && hsv.r < 60.0) 
	{
		Rs = C + m;
		Gs = X + m;
		Bs = m;	
	}
	else if (hsv.r >= 60.0 && hsv.r < 120.0) 
	{	
		Rs = X + m;
		Gs = C + m;
		Bs = m;	
	}
	else if (hsv.r >= 120.0 && hsv.r < 180.0) 
	{
		Rs = m;
		Gs = C + m;
		Bs = X + m;	
	}
	else if (hsv.r >= 180.0 && hsv.r < 240.0) 
	{
		Rs = m;
		Gs = X + m;
		Bs = C + m;	
	}
	else if (hsv.r >= 240.0 && hsv.r < 300.0) 
	{
		Rs = X + m;
		Gs = m;
		Bs = C + m;	
	}
	else if (hsv.r >= 300.0 && hsv.r < 360.0)
	{
		Rs = C + m;
		Gs = m;
		Bs = X + m;	
	}
	else
	{
		Rs = m;
		Gs = m;
		Bs = m;
	}
	if (Rs > 255)
		Rs = 255;
	if (Gs > 255)
		Gs = 255;
	if (Bs > 255)
		Bs = 255;
	if (Rs < 0)
		Rs = 0;
	if (Gs < 0)
		Gs = 0;
	if (Bs < 0)
		Bs = 0;
	*r = Rs;
	*g = Gs;
	*b = Bs;
}

void		add_saturation(char *r, char *g, char *b, double light)
{
	// t_hsv	hsv;
	double R;
	double G;
	double B;

	R = (double)*r;
	G = (double)*g;
	B = (double)*b;
	// hsv = rgb_to_hsv((double)*r, (double)*g, (double)*b);
	// hsv.b *= light;
	// hsv_to_rgb(hsv, r, g, b);
	if (R < 0.0)
		R += 255.0;
	if (G < 0.0)
		G += 255.0;
	if (B < 0.0)
		B += 255.0;

	 R *= light;
	 G *= light;
	 B *= light;
	if (R < 0.0)
		R = 0;
	if (G < 0.0)
		G = 0;
	if (B < 0.0)
		B = 0;
	if (R > 255.0)
		R = 255.0;
	if (G > 255.0)
		G = 255.0;
	if (B > 255.0)
		B = 255.0;
	*r = R;
	*g = G;
	*b = B;
}

void		put_texture(t_doom *doom, Uint32 tex_dex, Uint32 index,
					Uint32 pixel_dex)
{
	char	*pixels;
	char	*texture;
	char	R;
	char	G;
	char	B;

	pixels = doom->surface->pixels;
	texture = doom->lib.tex_lib[tex_dex]->pixels;
	R = texture[pixel_dex];
	G = texture[pixel_dex + 1];
	B = texture[pixel_dex + 2];
	add_saturation(&R, &G, &B, doom->distance);
	pixels[index] = R;
	index++;
	pixels[index] = G;
	index++;
	pixels[index] = B;
}
