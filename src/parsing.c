/*
** parsing.c for parsing in /home/wery_a/rendu/RayTracer/rtv1/v2/parsing
**
** Made by adrien wery
** Login   <wery_a@epitech.net>
**
** Started on  Thu Feb  5 18:47:47 2015 adrien wery
** Last update Tue Jun  9 19:45:15 2015 Nicolas Constanty
*/

#include "system.h"

int	get_nb_objs(char *file, short *nb_obj, short *nb_light)
{
  char	*s;
  int	fd;

  *(nb_obj) = 0;
  *(nb_light) = 0;
  if ((fd = open(file, O_RDONLY)) == -1)
    return (my_error("Can't open the file", -1));
  if ((s = get_next_line(fd)) == NULL)
    return (my_error("file is empty", -1));
  while ((s = get_next_line(fd)))
    {
      if (my_strncmp("<LIGHT", s, 6) == 0)
	++(*nb_light);
      else if (s[0] == '<' && s[1] != '/')
	++(*nb_obj);
      free(s);
    }
  free(s);
  close(fd);
  if (*nb_obj <= 0)
    return (my_error("Can't get how many objects", -1));
  return (0);
}

void	get_cam_params(t_cam *cam, char *s)
{
  if (s[0] == '<' && s[1] != '/')
    cam->name = my_strncpy(s, 1, my_strlen(s) - 1);
  cam->width = get_data_short("WIDTH = ", s, cam->width);
  cam->height = get_data_short("HEIGHT = ", s, cam->height);
  cam->p.x = get_data_short("PX = ", s, cam->p.x);
  cam->p.y = get_data_short("PY = ", s, cam->p.y);
  cam->p.z = get_data_short("PZ = ", s, cam->p.z);
  cam->r.x = get_data_float("RX = ", s, cam->r.x);
  cam->r.y = get_data_float("RY = ", s, cam->r.y);
  cam->r.z = get_data_float("RZ = ", s, cam->r.z);
  cam->ia = get_data_float("IA = ", s, cam->ia);
  cam->range_mssp = get_data_float("RANGE_MSSP = ", s, cam->range_mssp);
  cam->pass_mssp = get_data_float("PASS_MSSP = ", s, cam->pass_mssp);
  cam->dof = get_data_short("DOF = ", s, cam->dof);
  cam->mode = get_data_short("RENDU_MODE = ", s, cam->mode);
  cam->b_a_w = get_data_short("BLACK_AND_WHITE = ", s, cam->b_a_w);
  cam->ssp = get_data_short("SSP = ", s, cam->ssp);
  cam->thread = get_data_short("THREAD = ", s, cam->thread);
  cam->shading_border = get_data_short("SHADING_BORDER = ",
				       s, cam->shading_border);
  if (my_strncmp("BORDER_COLOR = ", s, 15) == 0)
    cam->border_color = (int)my_getnbr_base(&s[15], "0123456789ABCDEF");
}

void	get_params(t_system *sys, short *nb_obj, short *nb_light, int fd)
{
  char	*s;
  char	mode;

  *nb_obj = 0;
  *nb_light = 0;
  mode = 0;
  while ((s = get_next_line(fd)))
    {
      if (my_strncmp("<LIGHT", s, 6) == 0)
      	mode = 1;
      else if (my_strncmp("<CAM", s, 4) == 0)
      	mode = 2;
      else if (s[0] == '<' && s[1] != '/')
      	mode = 0;
      if (mode == 0)
  	get_obj_params(&(sys->obj[*nb_obj]), s, nb_obj);
      else if (mode == 1)
  	get_light_params(&(sys->light[*nb_light]), s, nb_light);
      else if (mode == 2)
      	get_cam_params(&(sys->cam), s);
      free(s);
    }
  free(s);
}

void	assign(t_system *sys)
{
  sys->fptr[0] = &inter_sphere;
  sys->fptr[1] = &inter_cylinder;
  sys->fptr[2] = &inter_cone;
  sys->fptr[3] = &inter_plan;
}

int	parsing(char *file, t_system *sys)
{
  int	fd;
  short	nb_obj;
  short	nb_light;

  if ((get_nb_objs(file, &nb_obj, &nb_light)) == -1)
    return (-1);
  if ((sys->obj = malloc(sizeof(t_obj) * (nb_obj + 1))) == NULL ||
      (sys->light = malloc(sizeof(t_light) * (nb_light + 1))) == NULL)
    return (my_error("Malloc Error on obj", -1));
  if ((fd = open(file, O_RDONLY)) == -1)
    return (my_error("Can't open the file", -1));
  init_struct(sys, nb_obj, nb_light);
  get_params(sys, &nb_obj, &nb_light, fd);
  sys->obj[nb_obj].type = -2;
  sys->light[nb_light].name = NULL;
  /* sys->cams[1].name = NULL; */
  limits(sys);
  close(fd);
  assign(sys);
  return (0);
}
