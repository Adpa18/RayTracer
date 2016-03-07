/*
** border_detection.c for border_detection in /home/wilmot_g/.ssh/MUL_2014_rtracer/v12
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Thu Jun  4 13:09:28 2015 guillaume wilmot
** Last update Sun Jun  7 19:00:02 2015 maxime mollonguet
*/

#include "system.h"

int			is_contrast(unsigned int color, unsigned int color2)
{
  if (abs(((color >> 8) & 255) - ((color2 >> 8) & 255)) > 35)
    return (1);
  if (abs(((color >> 16) & 255) - ((color2 >> 16) & 255)) > 35)
    return (1);
  if (abs(((color >> 24) & 255) - ((color2 >> 24) & 255)) > 35)
    return (1);
  return (0);
}

int			need_aa(t_system *sys, short y, short x, short len)
{
  unsigned int		color;
  short			y1;
  short			x1;
  int			width;

  y1 = y + 1;
  width = sys->cam.width;
  color = sys->color[y * width + x];
  while (y1 < y + len && y1 < sys->cam.height)
    {
      x1 = x + 1;
      while (x1 < x + len && x1 < sys->cam.width)
        {
          if (is_contrast(sys->color[y * width + x1], color) ||
              is_contrast(sys->color[y1 * width + x], color) ||
              is_contrast(sys->color[y * width + ((x - (x1 - x) < 0) ?
						  0 : x - (x1 - x))], color) ||
              is_contrast(sys->color[((y - (y1 - y) < 0 ) ?
				      0 : y - (y1 - y)) * width + x], color))
            return (0);
          ++x1;
        }
      ++y1;
    }
  return (1);
}

int			need_aa_outlines(t_system *sys, short y,
                                         short x, short len)
{
  short			y1;
  short			x1;
  int			width;

  y1 = y + 1;
  width = sys->cam.width;
  while (y1 < y + len && y1 < sys->cam.height)
    {
      x1 = x + 1;
      while (x1 < x + len && x1 < width)
        {
          if (sys->outlines[y * width + x] != sys->outlines[y * width + x1] ||
              sys->outlines[y * width + x] != sys->outlines[y1 * width + x] ||
              sys->outlines[y * width + x] !=
              sys->outlines[y * width
			    + ((x - (x1 - x) < 0) ? 0 : x - (x1 - x))]
              || sys->outlines[y * width + x] !=
              sys->outlines[((y - (y1 - y) < 0 ) ? 0 : y - (y1 - y))
                            * width + x])
            return (0);
          ++x1;
        }
      ++y1;
    }
  return (1);
}
