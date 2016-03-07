/*
** export_suite.c for export_suite in /home/mollon_m/rendu/MUL_2014_rtracer/v15/src
**
** Made by maxime mollonguet
** Login   <mollon_m@epitech.net>
**
** Started on  Sun Jun  7 18:17:48 2015 maxime mollonguet
** Last update Sun Jun  7 19:39:34 2015 guillaume wilmot
*/

#include <system.h>

int	my_get_1(t_system *sys,
		 unsigned char **hexa, unsigned char *head)
{
  if (!(hexa = convert_hexa(sys->cam.width, 4)))
    return (-1);
  head[4] = value(hexa[3], "0123456789abcdef");
  head[5] = value(hexa[2], "0123456789abcdef");
  head[6] = value(hexa[1], "0123456789abcdef");
  head[7] = value(hexa[0], "0123456789abcdef");
  if (!(hexa = convert_hexa(sys->cam.height, 4)))
    return (-1);
  head[8] = value(hexa[3], "0123456789abcdef");
  head[9] = value(hexa[2], "0123456789abcdef");
  head[10] = value(hexa[1], "0123456789abcdef");
  head[11] = value(hexa[0], "0123456789abcdef");
  head[12] = 1;
  head[13] = 0;
  head[14] = 24;
  return (0);
}

void	suite_export(t_system *sys, unsigned char **head, int fd)
{
  int	i;

  i = 0;
  while (i < 14)
    write(fd, &head[0][i++], 1);
  i = 0;
  while (i < 40)
    write(fd, &head[1][i++], 1);
  i = 0;
  while (i < sys->cam.width * sys->cam.height * 3)
    write(fd, &head[2][i++], 1);
}
