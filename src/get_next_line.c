/*
** get_next_line.c for get_next_line in /home/wery_a/rendu/MUL/RayTracer/MUL_2014_rtracer/src_new
**
** Made by Adrien WERY
** Login   <wery_a@epitech.net>
**
** Started on  Wed May 13 01:27:10 2015 Adrien WERY
** Last update Sun Jun  7 19:15:43 2015 guillaume wilmot
*/

#include "system.h"

char	*my_malloc(int len)
{
  char	*str;
  int	i;

  i = 0;
  if ((str = malloc(len)) == NULL)
    my_error("Malloc Failed", -1);
  while (i < len)
    str[i++] = '\0';
  return (str);
}

char	*my_re_alloc(char *s)
{
  char	*s2;
  int	i;

  i = 0;
  s2 = my_malloc((my_strlen(s) + 2) * sizeof(char));
  while (s[i] != '\0')
    {
      s2[i] = s[i];
      i += 1;
    }
  s2[i + 1] = '\0';
  free(s);
  return (s2);
}

char	*get_next_line(int fd)
{
  char	buff[BUFF_SIZE];
  char	*str;
  int	i;
  int	size;

  i = 0;
  size = 0;
  str = my_malloc(sizeof(char));
  str[0] = '\0';
  while ((size = read(fd, buff, BUFF_SIZE)) > 0 && buff[0] != '\n')
    {
      str = my_re_alloc(str);
      str[i] = buff[0];
      ++i;
    }
  if (size == 0 && i == 0)
    return (NULL);
  else
    return (str);
}
