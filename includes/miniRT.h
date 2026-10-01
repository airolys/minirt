/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharra <acharra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 23:23:39 by dkermia           #+#    #+#             */
/*   Updated: 2023/12/12 16:53:21 by acharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include </usr/include/X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# define SCREEN_WIDTH 900
# define SCREEN_HEIGHT 500
// MATH STRUCTURES
typedef struct s_vect2
{
	int					x;
	int					y;
}						t_vect2;

typedef struct s_vect3
{
	double				x;
	double				y;
	double				z;
}						t_vect3;

typedef struct s_vect4
{
	double				x;
	double				y;
	double				z;
	double				w;
}						t_vect4;

// GEOMETRY STRUCTURES

typedef struct s_ray
{
	t_vect3				pos;
	t_vect3				dir;
}						t_ray;

typedef struct s_generic
{
	int					color;
	t_vect3				pos;
}						t_generic;

typedef struct s_plane
{
	int					color;
	t_vect3				pos;
	t_vect3				normale;
}						t_plane;

typedef struct s_sphere
{
	int					color;
	t_vect3				pos;
	double				radius;
}						t_sphere;

typedef struct s_cylinder
{
	int					color;
	t_vect3				pos;
	t_vect3				dir;
	double				height;
	double				radius;
	t_plane				*disc1;
	t_plane				*disc2;
}						t_cylinder;

typedef struct s_light
{
	int					color;
	t_vect3				pos;
	double				lumio;
}						t_light;

enum					e_axis
{
	X,
	Y,
	Z
};

enum					e_mat
{
	SIMPLE,
	INVERT
};

typedef struct s_camera
{
	t_vect3				pos;
	t_vect3				dir;
	double				mat[2][3][4][4];
	double				vmat[3][3];
	double				fov;
}						t_camera;

enum					e_obj
{
	PLANE,
	SPHERE,
	CYLINDRE,
	LIGHT,
	AMBIANT
};

enum					e_channel
{
	RED,
	GREEN,
	BLUE
};

typedef struct s_obj
{
	enum e_obj			type;
	void				*inf;
	struct s_obj		*next;
}						t_obj;

typedef struct s_inter
{
	t_ray				*ray;
	double				dist;
	t_obj				*hit;
	t_vect3				normale;
}						t_inter;

typedef struct s_scene
{
	int					numobj[3];
	t_obj				*objs;
	t_camera			cam;
	t_obj				*lights;
}						t_scene;

typedef struct s_lights
{
	t_light				*ambiant;
	t_light				*light;
	int					dist;
}						t_lights;

typedef struct s_inter_info
{
	t_inter				primary;
	t_inter				light_inter;
}						t_inter_info;

// MLX IMAGE STRUCTURES
typedef struct s_texture_img
{
	int					width;
	int					height;
	int					bpp;
	int					size;
	int					endian;
	void				*data;
}						t_texture_data;

typedef struct s_imgs
{
	void				*img;
	int					size;
	t_texture_data		addr;
}						t_image_d;

// PROGRAM DATA
typedef struct s_mlx_variables
{
	void				*lib;
	void				*win;
	t_image_d			screen;
	t_scene				scene[1];
	int					pixel;
}						t_vars;

typedef unsigned long	t_ulong;
// bruh functions that we cant go without
int						put_fd_len(int fd, char *s, int l);

// MEMORY
char					*ft_itoa(int nb);
int						ft_numsize(long n);
void					free_str(char **str);
t_ulong					ft_strlen(char *str);
char					*ft_strdup(char *str);
void					ft_bzero(void *b, size_t n);
char					**ft_split(char *s, char c);
void					ft_putnbr_fd(int n, int fd);
void					ft_putchar_fd(char c, int fd);
char					*ft_writenum(char *number, long n);
char					*ft_strjoin(char *s1, char *s2, int upend);
char					*ft_substr(char *s, unsigned int start, size_t len);

// PARSING
char					*get_next_line(int fd);
int						parsing(int argc, char **argv, t_vars *mlx);
void					skip_chars(const char *line, int *i, char c);
int						ft_isspace(char c);
int						parse_vect3(const char *line, int *i, t_vect3 *result);
int						parse_color(const char *line, int *i);
int						parse_double(const char *line, int *i, double *result,
							char end_char);
int						parse_decimal(const char *line, int *i, double *result);
double					parse_ratio(const char *line, int *i, char end_char);
int						parse_ambient_light(const char *line, int *i,
							t_vars *mlx);
int						parse_camera(const char *line, int *i, t_vars *mlx);
int						parse_light(const char *line, int *i, t_vars *mlx);
int						parse_sphere(const char *line, int *i, t_vars *mlx);
int						parse_plane(const char *line, int *i, t_vars *mlx);
int						parse_cylinder(const char *line, int *i, t_vars *mlx);
// HOOKS
enum					e_Keys
{
	Up,
	Down,
	Right,
	Left
};

int						ft_close(t_vars *mlx);
int						press_in(int keypress, t_vars *mlx);

// RENDER
//======================MLX==========================//

void					draw_pixel(t_texture_data *data, int x, int y,
							int color);
void					draw_square(t_image_d screen, t_vect2 pos, int size,
							int color);

//======================INIT==========================//

int						initialisation(t_vars *mlx, int ac, char **av);
int						render_init(t_vars *mlx);
int						destroy_render(t_vars *mlx, int i);

//======================LOGIC==========================//

int						render_scene(t_vars *mlx);
t_inter					trace(t_ray *ray, t_scene *scene, double maxdepth);
t_obj					*new_obj(enum e_obj type, void *info);
t_light					*new_light(t_vect3 pos, double lumio, int color);
t_light					*new_ambiant(double lumio, int color);

// PLANE STUFF
t_plane					*new_plane(t_vect3 pos, t_vect3 normale, int color);
double					does_plane_intersect(t_ray *ray, t_plane *plane,
							t_inter *inter);

// SPHERE STUFF
t_sphere				*new_sphere(t_vect3 pos, double radius, int color);
double					does_sphere_intersect(t_ray *ray, t_sphere *sphere,
							t_inter *inter);

// DISC STUFF
double					does_disc_intersect(t_ray *ray, t_plane *disc,
							double radius, t_inter *inter);

// CYLINDER STUFF
double					does_cylinder_intersect(t_ray *ray, t_cylinder *cyl,
							t_inter *inter);
t_cylinder				*new_cylinder(t_cylinder info);
// more math
double					mag(t_vect3 v);
t_vect3					multvec(t_vect3 a, double d);
t_vect3					normalize(t_vect3 v);
double					dot(t_vect3 a, t_vect3 b);
t_vect3					addvec(t_vect3 a, t_vect3 b);
t_vect3					subvec(t_vect3 a, t_vect3 b);
double					dist_ab(t_vect3 a, t_vect3 b);
double					min_sup_zero(double a, double b);
void					compute_quadratic(double x[2], double a, double b,
							double c);

// CAMERA STUFF

void					cam_rot_mat(t_camera *cam);
t_ray					init_camera_ray(t_vars *mlx, t_vect2 xy);

// matrices
void					transpose_matrix(double matrix[4][4],
							double invert[4][4]);
t_vect4					mult_vec4_matrix(t_vect4 vector, double matrix[4][4]);
void					mmm(double res[4][4], double matrix1[4][4],
							double matrix2[4][4]);
void					new_id_matrix(double matrix[4][4]);
void					new_rot_matrix_x(double matrix[4][4],
							double invert[4][4], double theta);
void					new_rot_matrix_y(double matrix[4][4],
							double invert[4][4], double theta);
void					new_rot_matrix_z(double matrix[4][4],
							double invert[4][4], double theta);
void					get_theta_xyz(double theta[3], t_vect3 normal);
void					get_rotation_matrix(t_camera *cam);

t_light					*get_light(t_scene *scene, int type);
int						get_color(int hit_color, t_lights lights,
							t_inter_info info);
void					transpose_matrix(double matrix[4][4],
							double invert[4][4]);
t_vect4					mult_vec4_matrix(t_vect4 vector, double matrix[4][4]);
void					new_id_matrix(double matrix[4][4]);
void					new_rot_matrix_x(double matrix[4][4],
							double invert[4][4], double theta);
void					new_rot_matrix_y(double matrix[4][4],
							double invert[4][4], double theta);
void					new_rot_matrix_z(double matrix[4][4],
							double invert[4][4], double theta);
void					get_theta_xyz(double theta[3], t_vect3 normal);
void					get_rotation_matrix(t_camera *cam);

#endif
