/*
** str.c for str in /home/wery_a/rendu/Rush_marvin/Test/v9
** 
** Made by adrien wery
** Login   <wery_a@epitech.net>
** 
** Started on  Sun Jan  4 16:46:10 2015 adrien wery
** Last update Tue May 12 14:53:30 2015 Adrien WERY
*/

#include <unistd.h>

void	my_putchar(char c)
{
  write(1, &c, 1);
}

void	my_putstr(char *s)
{
  short	i;

  i = -1;
  while (s[++i])
    write(1, &s[i], 1);
}

int	my_strlen(char *s)
{
  short	i;

  i = -1;
  while (s[++i]);
  return (i);
}

void	my_putnbr(int nb)
{
  if (nb / 10 > 0)
    my_putnbr(nb / 10);
  my_putchar(nb % 10 + 48);
}

int	my_error(char *s, char error)
{
  my_putstr(s);
  write(1, "\n", 1);
  return (error);
}
