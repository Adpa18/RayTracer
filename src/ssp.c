/*
** ssp.c for  in /home/consta_n/Documents/tests/MUL_2014_rtracer/NICO/v14
**
** Made by consta_n
** Login   <consta_n@epitech.net>
**
** Started on  Fri Jun  5 22:51:28 2015 consta_n
** Last update Wed Jun 10 00:26:17 2015 Nicolas Constanty
*/

#include "system.h"

void			init_mat_ssp(t_system *sys, t_cols *cols, int ssp)
{
  short			i;
  double		mx;
  double		my;
  double		inc;

  i = -1;
  inc = 0.50 / (sys->cam.ssp + 1);
  mx = -0.25;
  my = 0.25;
  while (++i < ssp)
    {
      cols->x_tab[i] = mx;
      cols->y_tab[i] = my;
      mx += inc;
      my -= inc;
    }
}

char			init_col_sampling(t_system *sys, t_cols *cols)
{
  short			ssp;

  cols->mx = 0;
  cols->my = 0;
  cols->color[0] = 0;
  cols->color[1] = 0;
  cols->color[2] = 0;
  ssp = 1 + 2 * sys->cam.ssp;
  if (!(cols->x_tab = malloc(sizeof(double) * ssp)))
    return (1);
  if (!(cols->y_tab = malloc(sizeof(double) * ssp)))
    return (1);
  init_mat_ssp(sys, cols, ssp);
  return (0);
}

void			set_color_tab(t_system *sys, t_cols *cols, int ssp)
{
  short			j;

  j = -1;
  while (++j < ssp)
    {
      init_eye(sys, (double)sys->th_x
	       + cols->x_tab[cols->mx], (double)sys->th_y
	       + cols->y_tab[cols->my]);
      sys->best = calc_color(sys, sys->vecs.eye, sys->vecs.vector, sys->best);
      cols->color[0] += ((sys->best.color >> 8) & 255);
      cols->color[1] += ((sys->best.color >> 16) & 255);
      cols->color[2] += ((sys->best.color >> 24) & 255);
      ++(cols->mx);
      if (cols->mx == 1 + 2 * sys->cam.ssp)
	{
	  cols->mx = 0;
	  ++(cols->my);
	}
    }
  cols->color[0] /= ssp;
  cols->color[1] /= ssp;
  cols->color[2] /= ssp;
}

void			*get_color_sampling(void *args)
{
  t_cols		cols;
  t_system		*sys;
  long			pos;
  int			ssp;

  pos = 0;
  sys = (t_system *)args;
  ssp = pow(1 + 2 * sys->cam.ssp, 2);
  if (init_col_sampling(sys, &cols))
    return (NULL);  
  while (get_x_y(sys, sys->cam.height, sys->cam.width, sys->xy))
    {
      sys->best.id = -1;
      sys->best.color = 0;
      set_color_tab(sys, &cols, ssp);
      sys->best.color = 0 | ((int)cols.color[0]) << 8
	| ((int)cols.color[1]) << 16 | ((int)cols.color[2]) << 24;
      pos = sys->th_y * sys->image.sizeline + sys->th_x * sys->image.bpp / 8;
      sys->outlines[pos / 4] = sys->best.obj.id_grp;
      sys->color[pos / 4] = sys->best.color;
      my_pixel_put_to_image(sys->image.data, pos, sys->best.color);
      cols.color[0] = 0;
      cols.color[1] = 0;
      cols.color[2] = 0;
      cols.mx = 0;
      cols.my = 0;
    }
  sys->is_active = 0;
  free(cols.x_tab);
  free(cols.y_tab);
  while (sys->can_end != 1)
    {
      if (sys->can_end == 2)
	get_color_sampling(sys);
      usleep(20);
    }
  return (args);
}
