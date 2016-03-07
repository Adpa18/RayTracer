/*
** export.c for export in /home/wilmot_g/.ssh/MUL_2014_rtracer/G/v14
**
** Made by guillaume wilmot
** Login   <wilmot_g@epitech.net>
**
** Started on  Sat Jun  6 14:32:16 2015 guillaume wilmot
** Last update Sun Jun  7 22:13:04 2015 Adrien WERY
*/

#include "system.h"

char		*gen_image_name()
{
  char		*name;
  int		len;
  int		i;

  srand(time(NULL));
  len = 5 + rand() % 10;
  i = 0;
  if ((name = malloc((len + 17) * sizeof(char))) == NULL)
    return ("Error.bmp");
  name[i++] = 'r';
  name[i++] = 'e';
  name[i++] = 'n';
  name[i++] = 'd';
  name[i++] = 'u';
  name[i++] = 's';
  name[i++] = '/';
  while (i < 12 + len)
    name[i++] = 'a' + rand() % 26;
  name[i++] = '.';
  name[i++] = 'b';
  name[i++] = 'm';
  name[i++] = 'p';
  name[i] = '\0';
  return (name);
}

unsigned char	*get_head_f(t_system *sys)
{
  unsigned char	**hexa;
  unsigned char	*head;

  if ((head = malloc(14 * sizeof(char))) == NULL ||
      !(hexa = convert_hexa(54 + sys->cam.width * sys->cam.height * 3, 4)))
    return (NULL);
  head[0] = 66;
  head[1] = 77;
  head[2] = value(hexa[3], "0123456789abcdef");
  head[3] = value(hexa[2], "0123456789abcdef");
  head[4] = value(hexa[1], "0123456789abcdef");
  head[5] = value(hexa[0], "0123456789abcdef");
  head[6] = 0;
  head[7] = 0;
  head[8] = 0;
  head[9] = 0;
  head[10] = 54;
  head[11] = 0;
  head[12] = 0;
  head[13] = 0;
  return (head);
}

unsigned char	*get_head_i(t_system *sys)
{
  unsigned char	**hexa;
  unsigned char	*head;
  int	i;

  if ((hexa = NULL) == NULL && (head = malloc(40 * sizeof(char))) == NULL)
    return (NULL);
  head[0] = 40;
  head[1] = 0;
  head[2] = 0;
  head[3] = 0;
  if (my_get_1(sys, hexa, head) == -1)
    return (NULL);
  i = 15;
  while (i < 20)
    head[i++] = 0;
  if (!(hexa = convert_hexa(sys->cam.width * sys->cam.height * 3, 4)))
    return (NULL);
  head[20] = value(hexa[3], "0123456789abcdef");
  head[21] = value(hexa[2], "0123456789abcdef");
  head[22] = value(hexa[1], "0123456789abcdef");
  head[23] = value(hexa[0], "0123456789abcdef");
  i = 24;
  while (i < 40)
    head[i++] = 0;
  return (head);
}

unsigned char	*get_body(t_system *sys)
{
  unsigned char	*body;
  int		pos;
  int		i;
  int		j;
  int		k;

  k = 0;
  if ((body = malloc((sys->cam.height * sys->cam.width * 3 + 100) *
		     sizeof(char))) == NULL)
    return (NULL);
  j = sys->cam.height;
  while (j > 0)
    {
      i = 0;
      while (i < sys->cam.width)
        {
	  pos = j * sys->image.sizeline + i * sys->image.bpp / 8;
	  body[k++] = sys->image.data[pos++];
	  body[k++] = sys->image.data[pos++];
	  body[k++] = sys->image.data[pos++];
          i++;
        }
      j--;
    }
  return (body);
}

int		export(t_system *sys)
{
  int		fd;
  unsigned char *head[3];
  char		*name;

  name = gen_image_name();
  if ((fd = open(name, O_RDWR | O_TRUNC | O_CREAT, 0666)) == -1)
    {
      if (my_strcmp("Error.bmp", name))
	free(name);
      return (-1);
    }
  if (!(head[0] = get_head_f(sys)) || !(head[1] = get_head_i(sys)) ||
      !(head[2] = get_body(sys)))
    return (-1);
  my_putstr("Generating .bmp image...\n");
  suite_export(sys, head, fd);
  close(fd);
  free(head[0]);
  free(head[1]);
  free(head[2]);
  my_putstr("Image was generated\n");
  return (0);
}
