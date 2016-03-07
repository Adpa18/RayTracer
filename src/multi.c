/*
** multi.c for  in /home/consta_n/Documents/tests/MUL_2014_rtracer/NICO/v14
**
** Made by consta_n
** Login   <consta_n@epitech.net>
**
** Started on  Fri Jun  5 22:51:15 2015 consta_n
** Last update Tue Jun  9 23:40:07 2015 Nicolas Constanty
*/

#include "system.h"

char			create_thread(t_system **multi_th, pthread_attr_t *attr,
				      int nb, t_thread *thread)
{
  multi_th[nb]->is_active = 1;
  if (pthread_create(&(thread->th[nb]), attr,
		     get_color_sampling, multi_th[nb]) < 0)
    return (-1);
  return (0);
}

char			remp_img(t_system **multi_th)
{
  int			i ;
  t_thread		thread;
  int			nb_thread;

  loading(2, 0, "Generate Image ...");
  i = - 1;
  nb_thread = multi_th[0]->cam.thread;
  while (++i < nb_thread)
    get_cam(multi_th[i]);
  if (!(thread.th = malloc(sizeof(pthread_t) * nb_thread)))
    return (1);
  rand_mode(multi_th, &thread, multi_th[0]->cam.thread);
  write(1, "\n", 1);
  free(thread.th);
  return (0);
}

t_system		**set_multi_struct(t_system *sys, char *str)
{
  t_system		**multi_th;
  int			i;

  i = -1;
  if (!(multi_th = malloc(sizeof(t_system *) * sys->cam.thread)))
    return (NULL);
  if (!(sys->outlines = malloc(sys->cam.width *
			       sys->cam.height * sizeof(int)))
      || !(sys->color = malloc(sys->cam.width *
			       sys->cam.height * sizeof(int))))
    return (NULL);
  if (!(sys->mxyz = malloc(sizeof(double *) * 3)))
    return (NULL);
  if (!(sys->mxyz[0] =
	malloc(sizeof(double) * (1 + 2 * sys->cam.pass_mssp))))
    return (NULL);
  if (!(sys->mxyz[1] =
	malloc(sizeof(double) * (1 + 2 * sys->cam.pass_mssp))))
    return (NULL);
  if (!(sys->mxyz[2] =
	malloc(sizeof(double) * (1 + 2 * sys->cam.pass_mssp))))
    return (NULL);
  init_mat(sys);
  load_texture(sys);
  while (++i < sys->cam.thread)
    {
      if (!(multi_th[i] = malloc(sizeof(t_system))))
	return (NULL);
      if (parsing(str, multi_th[i]) == -1)
	return (NULL);
      multi_th[i]->obj = sys->obj;
      multi_th[i]->vecs = sys->vecs;
      multi_th[i]->cam = sys->cam;
      multi_th[i]->mlx = sys->mlx;
      multi_th[i]->win = sys->win;
      multi_th[i]->mxyz = sys->mxyz;
      multi_th[i]->image = sys->image;
      multi_th[i]->outlines = sys->outlines;
      multi_th[i]->color = sys->color;
      multi_th[i]->pos_thread = 0;
      multi_th[i]->limit = 0;
      multi_th[i]->can_end = 0;
    }
  return (multi_th);
}
