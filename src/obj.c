/*
** obj.c for obj in /home/wery_a/rendu/RayTracer/rtv1/v6
**
** Made by adrien wery
** Login   <wery_a@epitech.net>
**
** Started on  Wed Mar 11 04:40:24 2015 adrien wery
** Last update Sat Jun  6 06:04:01 2015 consta_n
*/

#include "system.h"

void	init_eye(t_system *sys, double x, double y)
{
  sys->vecs.vector.x = (sys->cam.width / 2) - x;
  sys->vecs.vector.y = (sys->cam.height / 2) - y;
  sys->vecs.vector.z = sys->cam.height / tan((25 * M_PI) / 180.0);
  rot(&(sys->vecs.vector), sys->vecs.eye_r);
}

void	get_cam(t_system *sys)
{
  sys->best.cam = sys->cam;
  sys->vecs.eye = sys->cam.p;
  sys->vecs.eye_r = sys->cam.r;
}

int	free_conf(t_system *sys, int mode)
{
  int	i;

  i = -1;
  if (sys->light != NULL)
    while (sys->light[++i].name)
      free(sys->light[i].name);
  if (sys->obj)
    free(sys->obj);
  if (sys->light)
    free(sys->light);
  if (sys->mlx && sys->win)
    {
      mlx_clear_window(sys->mlx, sys->win);
      mlx_destroy_window(sys->mlx, sys->win);
    }
  return (mode);
}
