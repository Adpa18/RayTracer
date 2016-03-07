/*
** get_obj.c for get_obj in /home/wery_a/rendu/MUL/RayTracer/MUL_2014_rtracer/v12
**
** Made by Adrien WERY
** Login   <wery_a@epitech.net>
**
** Started on  Wed Jun  3 13:13:40 2015 Adrien WERY
** Last update Sun Jun  7 19:16:06 2015 guillaume wilmot
*/

#include "system.h"

char	get_type(char *str)
{
  if (!my_strncmp(&str[1], "SPHERE", 6))
    return (0);
  else if (!my_strncmp(&str[1], "CYLINDER", 8))
    return (1);
  else if (!my_strncmp(&str[1], "CONE", 4))
    return (2);
  else if (!my_strncmp(&str[1], "PLAN", 4))
    return (3);
  else
    return (-1);
}

void	get_prs_params(t_obj *obj, char *s)
{
  obj->p.x = get_data_float("PX = ", s, obj->p.x);
  obj->p.y = get_data_float("PY = ", s, obj->p.y);
  obj->p.z = get_data_float("PZ = ", s, obj->p.z);
  obj->r.x = get_data_float("RX = ", s, obj->r.x);
  obj->r.y = get_data_float("RY = ", s, obj->r.y);
  obj->r.z = get_data_float("RZ = ", s, obj->r.z);
  obj->s.x = get_data_float("SX = ", s, obj->s.x);
  obj->s.y = get_data_float("SY = ", s, obj->s.y);
  obj->s.z = get_data_float("SZ = ", s, obj->s.z);
  obj->min_x = get_data_short("MIN_X = ", s, obj->min_x);
  obj->max_x = get_data_short("MAX_X = ", s, obj->max_x);
  obj->min_y = get_data_short("MIN_Y = ", s, obj->min_y);
  obj->max_y = get_data_short("MAX_Y = ", s, obj->max_y);
  obj->min_z = get_data_short("MIN_Z = ", s, obj->min_z);
  obj->max_z = get_data_short("MAX_Z = ", s, obj->max_z);
}

void	get_obj_params(t_obj *obj, char *s, short *nb_obj)
{
  if (s[0] == '<' && s[1] != '/')
    obj->type = get_type(s);
  get_prs_params(obj, s);
  obj->id_grp = get_data_short("ID_GRP = ", s, obj->id_grp);
  obj->ra = get_data_short("RA = ", s, obj->ra);
  obj->rb = get_data_float("RB = ", s, obj->rb);
  obj->sp = get_data_short("SP = ", s, obj->sp);
  obj->br = get_data_float("BR = ", s, obj->br);
  obj->kd = get_data_float("Kd = ", s, obj->kd);
  obj->ks = get_data_float("Ks = ", s, obj->ks);
  obj->kr = get_data_float("Kr = ", s, obj->kr);
  obj->damier = get_data_short("DAMIER = ", s, obj->damier);
  if (my_strncmp("COLOR = ", s, 8) == 0)
    obj->color = (int)my_getnbr_base(&s[8], "0123456789ABCDEF");
  else if (my_strncmp("COLOR_IN = ", s, 11) == 0)
    obj->color_in = (int)my_getnbr_base(&s[11], "0123456789ABCDEF");
  else if (my_strncmp("COLOR_SP = ", s, 11) == 0)
    obj->color_sp = (int)my_getnbr_base(&s[11], "0123456789ABCDEF");
  else if (my_strncmp("TEXTURE = ", s, 10) == 0)
    obj->tex.file = my_strncpy(&s[10], 0, my_strlen(&s[9]));
  else if (my_strncmp("</", s, 2) == 0)
    obj->id = (*nb_obj)++;
}

void	get_light_params(t_light *light, char *s, short *nb_light)
{
  if (s[0] == '<' && s[1] != '/')
    light->name = my_strncpy(s, 1, my_strlen(s) - 1);
  light->p.x = get_data_short("PX = ", s, light->p.x);
  light->p.y = get_data_short("PY = ", s, light->p.y);
  light->p.z = get_data_short("PZ = ", s, light->p.z);
  light->r.x = get_data_float("RX = ", s, light->r.x);
  light->r.y = get_data_float("RY = ", s, light->r.y);
  light->r.z = get_data_float("RZ = ", s, light->r.z);
  light->intensity = get_data_float("INTENSITY = ", s, light->intensity);
  if (my_strncmp("COLOR = ", s, 8) == 0)
    light->color = (int)my_getnbr_base(&s[8], "0123456789ABCDEF");
  if (my_strncmp("</", s, 2) == 0)
    ++(*nb_light);
}
