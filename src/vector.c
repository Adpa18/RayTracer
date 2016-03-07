/*
** vector.c for vector in /home/wery_a/rendu/MUL/RayTracer/MUL_2014_rtracer/src_new
** 
** Made by Adrien WERY
** Login   <wery_a@epitech.net>
** 
** Started on  Thu May 14 21:23:13 2015 Adrien WERY
** Last update Sun Jun  7 19:55:34 2015 Matthieu Tavernier
*/

#include "system.h"

t_vector3		unitaire(t_vector3 v)
{
  double	norm;
  t_vector3	uni;

  norm = norme(v);
  if (norm)
    {
      uni.x = v.x / norm;
      uni.y = v.y / norm;
      uni.z = v.z / norm;
    }
  return (uni);
}

double		scalaire(t_vector3 v1, t_vector3 v2)
{
  return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double		norme(t_vector3 v)
{
  return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector3		add_sub_vector(t_vector3 v1, t_vector3 v2, double mode)
{
  t_vector3	res;

  res.x = v1.x + mode * v2.x;
  res.y = v1.y + mode * v2.y;
  res.z = v1.z + mode * v2.z;
  return (res);
}
