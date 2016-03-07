/*
** limits.c for limits in /home/wery_a/rendu/MUL/RayTracer/MUL_2014_rtracer/v15/src
**
** Made by Adrien WERY
** Login   <wery_a@epitech.net>
**
** Started on  Sun Jun  7 17:07:20 2015 Adrien WERY
** Last update Wed Jun 10 00:31:50 2015 Nicolas Constanty
*/

#include "system.h"

void	limits_cam(t_cam *cam)
{
  cam->width = MAX(cam->width, 500, 4096);
  cam->height = MAX(cam->height, 500, 4096);
  cam->ia = MAX(cam->ia, 0, 1);
  cam->range_mssp = MAX(cam->range_mssp, 0, 256);
  cam->pass_mssp = MAX(cam->pass_mssp, 0, 256);
  cam->ssp = MAX(cam->ssp, 0, 256);
  if (cam->thread % 2 == 1 && cam->thread > 1)
    cam->thread -= 1;
  cam->thread = MAX(cam->thread, 1, 18);
  cam->mode = MAX(cam->mode, 0, 18);
}

void	limits_obj(t_obj *obj)
{
  obj->id_grp = MAX(obj->id_grp, 0, 256);
  obj->br = MAX(obj->br, 0, 1);
  obj->kd = MAX(obj->kd, 0, 1);
  obj->ks = MAX(obj->ks, 0, 1);
  obj->kr = MAX(obj->kr, 0, 1);
}

void	limits(t_system *sys)
{
  int	i;

  limits_cam(&(sys->cam));
  i = -1;
  while (sys->obj[++i].type != -2)
    limits_obj(&(sys->obj[i]));
}
