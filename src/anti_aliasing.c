/*
** anti_alliasing.c for anti_alliasing in /home/wery_a/rendu/MUL/RayTracer/MUL_2014_rtracer/New_light
**
** Made by Adrien WERY
** Login   <wery_a@epitech.net>
**
** Started on  Mon May 18 19:30:34 2015 Adrien WERY
** Last update Sun Jun  7 22:16:13 2015 Adrien WERY
*/

#include "system.h"

int			color_interpolation(unsigned int *pixels, short ssp)
{
  short			i;
  double		color[3];
  unsigned char		final[3];
  unsigned int		mix;

  i = 0;
  color[0] = 0;
  color[1] = 0;
  color[2] = 0;
  while (i < ssp)
    {
      color[0] += ((double)((pixels[i] >> 8) & 255) / (ssp));
      color[1] += ((double)((pixels[i] >> 16) & 255) / (ssp));
      color[2] += ((double)((pixels[i] >> 24) & 255) / (ssp));
      ++i;
    }
  final[0] = color[0];
  final[1] = color[1];
  final[2] = color[2];
  mix = 0;
  mix |= final[0] << 8;
  mix |= final[1] << 16;
  mix |= final[2] << 24;
  return (mix);
}

int			supersampling(t_system *sys, short y, short x,
				      unsigned int *pixels)
{
  double		y1;
  double		x1;
  int			pos;
  short			i;

  i = 0;
  y1 = (y - 16 / 8 < 0) ? 0 : y - (16 / 8);
  pos = y * sys->image.sizeline + x * sys->image.bpp / 8;
  while (i < 16)
    pixels[i++] = sys->color[pos / 4];
  i = 0;
  while (i < 16 && y1 < y + (16 / 8) && y1 < sys->cam.height)
    {
      x1 = (x - 16 / 8) < 0 ? 0 : x - (16 / 8);
      while (i < 16 && x1 < x + (16 / 8)
	     && x1 < sys->cam.width)
	{
	  pos = y1 * sys->image.sizeline + x1 * sys->image.bpp / 8;
          pixels[i] = sys->color[pos / 4];
	  ++x1;
	  ++i;
	}
      ++y1;
    }
  return (color_interpolation(pixels, 16));
}

int			init_aa(unsigned int **pixels, short *per,
				short *coord, int aa)
{
  write(1, "\n", 1);
  if ((*pixels = malloc(sizeof(int) * aa)) == NULL)
    return (-1);
  *per = 0;
  loading(2, 0, "Generate AntiAlliasing ...");
  *coord = -1;
  return (0);
}

void			anti_aliasing(t_system *sys, int aa)
{
  short			xy[3];
  int			pos;
  unsigned int		*pixels;

  pos = 0;
  if (init_aa(&pixels, &xy[2], &(xy[1]), 16) == -1)
    return;
  while (++xy[1] < sys->cam.height)
    {
      xy[0] = -1;
      while (++xy[0] < sys->cam.width)
	{
	  pos = xy[1] * sys->image.sizeline + xy[0] * sys->image.bpp / 8;
	  if (((aa == 1) ? !need_aa_outlines(sys, xy[1], xy[0],
					     64) :
	       need_aa(sys, xy[1], xy[0], 64) == 0))
	    my_pixel_put_to_image(sys->image.data, pos, supersampling
				  (sys, xy[1], xy[0], pixels));
	}
      if (pos * 100 / (sys->cam.height * sys->image.sizeline) > xy[2])
	loading(xy[2] += 2, 1, "");
      mlx_put_image_to_window(sys->mlx, sys->win, sys->image.img, 0, 0);
    }
  free(pixels);
  write(1, "\n", 1);
}
