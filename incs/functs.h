/*
** functs.h for functs in /home/wery_a/rendu/RayTracer/rtv1/v1
**
** Made by adrien wery
** Login   <wery_a@epitech.net>
**
** Started on  Thu Feb  5 04:14:01 2015 adrien wery
** Last update Tue Jun  9 21:41:54 2015 Nicolas Constanty
*/

#ifndef FUNCTS_H_
# define FUNCTS_H_

/* STR_WRITE FUNCTIONS */
void		my_putchar(char c);
void		my_putstr(char *s);
int		my_strlen(char *s);
void		my_putnbr(int nb);
int		my_error(char *s, char error);

/* STR_OP FUNCTIONS */
int		my_strcmp(char *s1, char *s2);
int		my_strncmp(char *s1, char *s2, int nb);
char		*my_strncpy(char *s, int start, int end);
void		my_memset(char *s, char c, int size);
char		*epur_str(char *s);

/* GET_NEXT_LINE */
char		*get_next_line(int fd);

/* GET_NBR FUNCTIONS */
short		get_data_short(char *cmp, char *s, short nb);
float		get_data_float(char *cmp, char *s, float nb);
long		my_getnbr_base(char *s, char *base);
double		my_getnbr_float(char *s);

/* MLX FUNCTIONS */
int		init_mlx(t_system *sys);
void		my_pixel_put_to_image(char *data, unsigned int pos, int color);
int		expose(t_system *sys);
void		hooks(t_system *sys);
int		key_hook(int keycode, t_system *sys);

/* PARSING FUNCTIONS */
int		parsing(char *file, t_system *sys);
void		init_struct(t_system *sys, short nb_obj, short nb_light);
void		init_vecs_best(t_vecs *vecs, t_best *best);
void		init_cams(t_cam *cam);
void		init_objs(t_obj *obj);
void		init_lights(t_light *light);
void		get_light_params(t_light *light, char *s, short *nb_light);
void		get_obj_params(t_obj *obj, char *s, short *nb_obj);
void		limits(t_system *sys);

/* MAIN FUNCTIONS */
int		main(int argc, char **argv);
void		loading(unsigned short per, unsigned short mode, char *txt);
void		init_eye(t_system *sys, double x, double y);
char		remp_img(t_system **multi_th);
void		*get_color_sampling(void *sys);
t_system	**set_multi_struct(t_system *sys, char *str);
int		get_x_y(t_system *sys, int width, int height, int *xy);
char		gen_xy(int **xy, uint wh, char mode, int nb_thread);
char		create_thread(t_system **multi_th, pthread_attr_t *attr,
			      int nb, t_thread *thread);
char		rand_mode(t_system **multi_th, t_thread *thread, int nb_thread);

/* OBJ FUNCTIONS */
void		translate(t_vector3 *vecs, t_vector3 p, char mode);
void		scale(t_vector3 *vecs, t_vector3 s);
void		rot(t_vector3 *vecs, t_vector3 r);
void		rot_inv(t_vector3 *vecs, t_vector3 r);
void		get_cam(t_system *sys);
int		free_conf(t_system *sys, int i);

/* INTER FUNCTIONS */
void		inter_sphere(t_vector3 eye, t_vector3 cam,
			     t_obj obj, t_best *best);
void		inter_cylinder(t_vector3 eye, t_vector3 cam,
			       t_obj obj, t_best *best);
void		inter_cone(t_vector3 eye, t_vector3 cam,
			   t_obj obj, t_best *best);
void		inter_plan(t_vector3 eye, t_vector3 cam,
			   t_obj obj, t_best *best);
void		delta(const t_vector3 *eye, const t_vector3 *cam,
		      double *a, t_obj obj, t_best *best);
int		check_limit(const t_vector3 *eye, const t_vector3 *cam,
			    t_obj obj, double x);

/* LIGHT FUNCTIONS */
t_best		calc_color(t_system *sys, t_vector3 eye, t_vector3 cam,
			   t_best best);
int		light_color(t_system *sys, t_vector3 eye, t_vector3 cam,
			    t_best best);
double		shadow(t_system *sys, t_best best, t_vector3 light);

/* VECTOR FUNCTIONS */
double		norme(t_vector3 v);
double		scalaire(t_vector3 v1, t_vector3 v2);
t_vector3      	unitaire(t_vector3 v);
t_vector3      	add_sub_vector(t_vector3 v1, t_vector3 v2, double mode);

/* GET_VECTOR FUNCTIONS */
t_vector3      	get_normal(t_vector3 vecs, t_vector3 eye, t_best best);
t_vector3      	get_vector(t_vector3 v, t_vector3 eye, double k);
t_vector3	multi_vector(t_vector3 v, double coef);
t_vector3	gen_vector(double x, double y, double z);

/* DOF FUNCTIONS */
int		is_dof(short x, short y, t_system *sys);
int		blur(t_system *sys, short y, short x, unsigned int *pixels);
void		dof(t_system *sys);
int		my_get_1(t_system *sys, unsigned char **hexa,
			 unsigned char *head);
void            suite_export(t_system *sys, unsigned char **head, int fd);

/* AA FUNCTIONS */
int		color_interpolation(unsigned int *pixels, short ssp);
int		supersampling(t_system *sys, short y, short x, unsigned int
			      *pixels);
int		is_contrast(unsigned int color, unsigned int color2);
int		need_aa(t_system *sys, short y, short x, short len);
int		need_aa_outlines(t_system *sys, short y, short x, short len);
void		anti_aliasing(t_system *sys, int aa_type);

/* SHADING FUNCTIONS */
int		get_color(char *data, int pos);
void		shading(t_system *sys);
void		black_and_white(t_system *sys);

/* TEXTURES FUNCTIONS */
int		damier(t_vector3 eye, t_vector3 cam, t_best best);
int		texture(t_vector3 eye, t_vector3 cam, t_best best);
void		load_texture(t_system *sys);

/* EXPORT FUNCTIONS */
int		export(t_system *sys);
unsigned char	value(unsigned char *str, char *base);
unsigned char	**convert_hexa(int nbr, int octet);

void		init_mat(t_system *sys);

#endif /* !FUNCTS_H_ */
