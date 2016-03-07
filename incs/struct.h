/*
** struct.h for struct in /home/wery_a/rendu/RayTracer/rtv1/v1
**
** Made by adrien wery
** Login   <wery_a@epitech.net>
**
** Started on  Thu Feb  5 04:17:30 2015 adrien wery
** Last update Tue Jun  9 23:37:58 2015 Nicolas Constanty
*/

typedef struct  s_image
{
  void          *img;
  char          *data;
  int           bpp;
  int           sizeline;
  int           endian;
}               t_image;

typedef struct	s_vector3
{
  double	x;
  double	y;
  double	z;
}		t_vector3;

typedef struct  s_cols
{
  short         mx;
  short         my;
  double        color[3];
  double        *x_tab;
  double        *y_tab;
}               t_cols;

typedef struct	s_texture
{
  char		*file;
  int		w;
  int		h;
  t_image	texture;
}		t_texture;

typedef struct	s_cam
{
  char		*name;
  t_vector3	p;
  t_vector3	r;
  double	range_mssp;
  int		pass_mssp;
  int		dof;
  int		shading_border;
  int		border_color;
  float		ia;
  short		b_a_w;
  int		ssp;
  char		thread;
  int		width;
  int		height;
  char		mode;
}		t_cam;

typedef struct	s_light
{
  char		*name;
  t_vector3	p;
  t_vector3	r;
  float		intensity;
  unsigned int	color;
}		t_light;

typedef struct	s_obj
{
  int		id;
  int		id_grp;
  char		type;
  t_vector3	p;
  t_vector3	r;
  t_vector3	s;
  short		min_x;
  short		max_x;
  short		min_y;
  short		max_y;
  short		min_z;
  short		max_z;
  short		ra;
  short		rb;
  short		sp;
  float		br;
  float		kd;
  float		ks;
  float		kr;
  unsigned int	color;
  unsigned int	color_in;
  unsigned int	color_sp;
  t_texture	tex;
  short         damier;
}		t_obj;

typedef struct  s_vecs
{
  t_vector3	vector;
  t_vector3	eye;
  t_vector3	eye_r;
}               t_vecs;

typedef struct	s_best
{
  t_cam		cam;
  t_obj		obj;
  int		color;
  short		i;
  double	rgb;
  double	rgb_sp;
  double	rgb_re;
  double        k;
  t_vector3	normal;
  t_vector3	inter;
  int		id;
}		t_best;

typedef struct  s_blur
{
  double        y1;
  double        x1;
  int           pos1;
  int           pos2;
  short         i;
}               t_blur;

typedef struct  s_system
{
  void          *mlx;
  void          *win;
  int		*outlines;
  unsigned int	*color;
  t_image       image;
  t_vecs        vecs;
  t_obj		*obj;
  t_light	*light;
  t_cam		cam;
  t_best	best;
  int		th_x;
  int		th_y;
  double	**mxyz;
  int		*xy;
  int           pos_thread;
  int           is_active;
  int		limit;
  int		can_end;
  void          (*fptr[10])(t_vector3 eye, t_vector3 cam,
			    t_obj obj, t_best *best);
}               t_system;

typedef struct  s_thread
{
  pthread_t	*th;
  void		*ret;
}               t_thread;
