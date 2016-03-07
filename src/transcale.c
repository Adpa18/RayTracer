/*
** rotate.c for rotate in /home/wery_a/rendu/RayTracer/rtv1/v6
** 
** Made by adrien wery
** Login   <wery_a@epitech.net>
** 
** Started on  Wed Mar 11 19:49:57 2015 adrien wery
** Last update Tue Jun  9 20:28:24 2015 Nicolas Constanty
*/

#include "system.h"

void		translate(t_vector3 *vecs, t_vector3 p, char mode)
{
  vecs->x -= p.x * mode;
  vecs->y -= p.y * mode;
  vecs->z -= p.z * mode;
}

void		scale(t_vector3 *vecs, t_vector3 s)
{
  vecs->x /= s.x;
  vecs->y /= s.y;
  vecs->z /= s.z;
}
