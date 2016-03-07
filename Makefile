##
## Makefile for Makefile in /home/wery_a/rendu/RayTracer/rtv1
##
## Made by adrien wery
## Login   <wery_a@epitech.net>
##
## Started on  Tue Feb  3 16:12:36 2015 adrien wery
## Last update Tue Jun  9 21:39:35 2015 Nicolas Constanty
##

SRCS	= main.c		\
	  black_and_white.c	\
	  mlx.c			\
	  str_write.c		\
	  str_op.c		\
	  strlcpy.c		\
	  parsing.c		\
	  limits.c		\
	  hexa.c		\
	  init_struct.c		\
	  get_params.c		\
	  get_next_line.c	\
	  export.c		\
	  export_suite.c	\
	  get.c			\
	  obj.c			\
	  matrix.c		\
	  inter.c		\
	  delta.c		\
	  light.c		\
	  vector.c		\
	  get_vector.c		\
	  shadow.c		\
          border_detection.c    \
          anti_aliasing.c       \
          dof.c                 \
          shading.c             \
	  ssp.c			\
	  multi.c		\
	  transcale.c		\
	  render.c		\
	  render_mode.c		\
	  texture.c		\

CC	= gcc

RM	= rm -f

LFLAGS  = -L/usr/lib64 -lmlx -L/usr/lib64/X11 -lXext -lX11 -lm -pthread

CFLAGS  += -I./incs

CFLAGS  += -W -Wall -Wextra -O2 -march=native

NAME	= rt

RMDIR   = rm -rf

SDIR    = src

ODIR    = obj

OBJ     = $(addprefix $(ODIR)/, $(SRCS:.c=.o))

$(ODIR)/%.o: $(SDIR)/%.c
	@if [ ! -d $(ODIR) ] ; then mkdir $(ODIR) ; fi
	$(CC) $(CFLAGS) $(INCDIR) -c -o $@ $<


$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ) *~ *#
	@if [ -d $(ODIR) ] ; then $(RMDIR) $(ODIR) ; fi

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
