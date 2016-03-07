/*
** render.c for render in /home/wery_a/rendu/MUL/RayTracer/MUL_2014_rtracer
**
** Made by Adrien WERY
** Login   <wery_a@epitech.net>
**
** Started on  Sat Jun  6 12:16:48 2015 Adrien WERY
** Last update Tue Jun  9 23:31:58 2015 Nicolas Constanty
*/

#include "system.h"

void		div_xy_mode(int **xy, int *xy_f, int nb_thread, uint wh)
{
  cpt		i;
  cpt		j;
  cpt		ra;

  i = 0;
  ra = 0;
  j = 0;
  while (i < wh)
    {
      xy[ra][j] = xy_f[i];
      if (++j == wh / nb_thread)
	{
	  ++ra;
	  j = 0;
	}
      ++i;
    }
}

void		div_xy_normal(int **xy, int nb_thread, uint wh)
{
  cpt		i;
  cpt		j;
  cpt		ra;

  i = 0;
  ra = 0;
  j = 0;
  while (i < wh)
    {
      xy[ra][j] = i;
      if (++j == wh / nb_thread)
	{
	  ++ra;
	  j = 0;
	}
      ++i;
    }
}

char		gen_xy(int **xy, uint wh, char mode, int nb_thread)
{
  cpt          i;
  cpt          ra;
  int		*xy_f;

  i = 0;
  if (!(xy_f = malloc(sizeof(int) * wh + 1)))
    return (1);
  while (i < wh)
    {
      xy_f[i] = -1;
      ++i;
    }
  i = 0;
  while (i < wh)
    {
      ra = rand() % wh;
      while (xy_f[ra] != -1)
	ra = rand() % (wh);
      xy_f[ra] = i;
      ++i;
    }
  if (mode == 1)
    div_xy_mode(xy, xy_f, nb_thread, wh);
  else
    div_xy_normal(xy, nb_thread, wh);
  free(xy_f);
  return (0);
}

int		get_x_y(t_system *sys, int width, int height, int *xy)
{
  static int	per = 0;

  sys->th_x = xy[sys->pos_thread] % height;
  sys->th_y = xy[sys->pos_thread] / height;
  if (++(sys->pos_thread) >= width * height / sys->cam.thread - sys->limit)
    return (0);
  if (sys->pos_thread / sys->cam.thread % 100 == 0)
    mlx_put_image_to_window(sys->mlx, sys->win, sys->image.img, 0, 0);
  if (sys->pos_thread * sys->cam.thread * 100 / (width * height) > per)
    loading(per += 2, 1, "");
  return (1);
}
