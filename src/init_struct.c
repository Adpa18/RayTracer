/*
** init_struct.c for init_struct in /home/wery_a/rendu/MUL/RayTracer/MUL_2014_rtracer/v13
**
** Made by Adrien WERY
** Login   <wery_a@epitech.net>
**
** Started on  Fri Jun  5 01:32:38 2015 Adrien WERY
** Last update Tue Jun  9 19:46:35 2015 Nicolas Constanty
*/

#include "system.h"

void	init_objs(t_obj *obj)
{
  obj->id = 0;
  obj->id_grp = 0;
  obj->type = -2;
  obj->p = gen_vector(0, 0, 0);
  obj->r = gen_vector(0, 0, 0);
  obj->s = gen_vector(1, 1, 1);
  obj->min_x = -1;
  obj->max_x = -1;
  obj->min_y = -1;
  obj->max_y = -1;
  obj->min_z = -1;
  obj->max_z = -1;
  obj->ra = 30;
  obj->rb = 0;
  obj->sp = 0;
  obj->br = 0;
  obj->kd = 0;
  obj->ks = 0;
  obj->kr = 0;
  obj->color = 0xFFFFFF00;
  obj->color_in = 0;
  obj->color_sp = 0xFFFFFF00;
  obj->tex.file = NULL;
  obj->tex.texture.data = NULL;
  obj->damier = 0;
}

void	init_lights(t_light *light)
{
  light->name = NULL;
  light->p = gen_vector(0, 0, 0);
  light->r = gen_vector(0, 0, 0);
  light->intensity = 0;
  light->color = 0;
}

void	init_cams(t_cam *cam)
{
  cam->name = NULL;
  cam->p = gen_vector(0, 0, 0);
  cam->r = gen_vector(0, 0, 0);
  cam->range_mssp = 0.0;
  cam->pass_mssp = 0;
  cam->dof = 0;
  cam->shading_border = 0;
  cam->border_color = 0;
  cam->ia = 0.5;
  cam->ssp = 0;
  cam->thread = 1;
  cam->width = 1000;
  cam->height = 1000;
  cam->mode = 0;
}

void	init_struct(t_system *sys, short nb_obj, short nb_light)
{
  short	i;

  i = -1;
  init_vecs_best(&(sys->vecs), &(sys->best));
  init_cams(&(sys->cam));
  while (++i < nb_obj)
    init_objs(&(sys->obj[i]));
  while (++i < nb_light)
    init_lights(&(sys->light[i]));
}

void	init_vecs_best(t_vecs *vecs, t_best *best)
{
  vecs->vector = gen_vector(0, 0, 0);
  vecs->eye = gen_vector(0, 0, 0);
  vecs->eye_r = gen_vector(0, 0, 0);
  init_cams(&(best->cam));
  init_objs(&(best->obj));
  best->color = 0;
  best->i = 0;
  best->rgb = 0;
  best->rgb_sp = 0;
  best->rgb_re = 0;
  best->k = 0;
  best->id = 0;
  best->normal = gen_vector(0, 0, 0);
  best->inter = gen_vector(0, 0, 0);
}
