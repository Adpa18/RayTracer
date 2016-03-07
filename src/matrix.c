/*
** rotate.c for rotate in /home/wery_a/rendu/RayTracer/rtv1/v6
** 
** Made by adrien wery
** Login   <wery_a@epitech.net>
** 
** Started on  Wed Mar 11 19:49:57 2015 adrien wery
** Last update Sun Jun  7 20:57:34 2015 Adrien WERY
*/

#include "system.h"

void		rotate_x(t_vector3 *vecs, double cosx, double sinx)
{
  double	y;
  double	z;

  y = vecs->y * cosx - vecs->z * sinx;
  z = vecs->y * sinx + vecs->z * cosx;
  vecs->y = y;
  vecs->z = z;
}

void		rotate_y(t_vector3 *vecs, double cosy, double siny)
{
  double	x;
  double	z;

  x = vecs->z * siny + vecs->x * cosy;
  z = vecs->x * (-siny) + vecs->z * cosy;
  vecs->x = x;
  vecs->z = z;
}

void		rotate_z(t_vector3 *vecs, double cosz, double sinz)
{
  double	x;
  double	y;

  x = vecs->x * cosz + vecs->y * sinz;
  y = vecs->x * -sinz + vecs->y * cosz;
  vecs->x = x;
  vecs->y = y;
}

void		rot(t_vector3 *vecs, t_vector3 r)
{
  double	x;
  double	y;
  double	z;

  if (r.x == 0 && r.y == 0 && r.z == 0)
    return;
  x = RADIAN(r.x);
  y = RADIAN(r.y);
  z = RADIAN(r.z);
  if (x != 0)
    rotate_x(vecs, cos(x), sin(x));
  if (y != 0)
    rotate_y(vecs, cos(y), sin(y));
  if (z != 0)
    rotate_z(vecs, cos(z), sin(z));
}

void		rot_inv(t_vector3 *vecs, t_vector3 r)
{
  double	x;
  double	y;
  double	z;

  if (r.x == 0 && r.y == 0 && r.z == 0)
    return;
  x = RADIAN(r.x);
  y = RADIAN(r.y);
  z = RADIAN(r.z);
  if (z != 0)
    rotate_z(vecs, cos(-z), sin(-z));
  if (y != 0)
    rotate_y(vecs, cos(-y), sin(-y));
  if (x != 0)
    rotate_x(vecs, cos(-x), sin(-x));
}
