/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:33:22 by haekang           #+#    #+#             */
/*   Updated: 2024/01/15 20:16:34 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <float.h>
# include <string.h>
# include "mlx/mlx.h"

# define WIDTH 1920
# define HEIGHT 1080
# define INF 1000000000
# define EPSILON 1e-10
# define TRUE 1
# define FALSE 0
# define BUFFER_SIZE 42
# define AMBIENT_IDX 1
# define CAMERA_IDX 2
# define LIGHT_IDX 3
# define UP 1
# define DOWN -1

typedef struct s_point	t_color;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef struct s_cylinder
{
	t_point	point;
	t_point	vector;
	double	diameter;
	double	height;
	t_color	color;
}	t_cylinder;

typedef struct s_plane
{
	t_point	point;
	t_point	vector;
	t_color	color;
}	t_plane;

typedef struct s_sphere
{
	t_point	point;
	double	diameter;
	t_color	color;
}	t_sphere;

typedef struct s_light
{
	t_point	point;
	double	ratio;
	t_color	color;
}	t_light;

typedef struct s_camera
{
	t_point	point;
	t_point	vector;
	double	fov;
	t_point	horizontal;
	t_point	vertical;
	double	focal_len;
	t_point	left_bottom;
}	t_camera;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_ray
{
	t_point	point;
	t_point	vector;
	double	hit_t;
	t_color	color;
	t_point	hit_point;
	void	*hit_obj;
	t_point	obj_normal;
}	t_ray;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_info
{
	void		*mlx;
	void		*win;
	t_data		img;
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_list		*sphere;
	t_list		*plane;
	t_list		*cylinder;
}	t_info;

typedef struct s_discrimination
{
	double	a;
	double	b;
	double	c;
	double	expression;
}	t_discrimination;

//mrt_parse
t_info	*mrt_parse(char *file_name);
char	*mrt_parse_return_file_path(char *file_name);
void	*mrt_parse_load_file(char *file_path, t_info *info);
t_info	*mrt_parse_init_info(void);
void	mrt_parse_insert_sphere(char **line_info, t_info *info);
void	mrt_parse_insert_plane(char **line_info, t_info *info);
void	mrt_parse_insert_light(char **line_info, t_info *info, int *flags);
void	mrt_parse_insert_cylinder(char **line_info, t_info *info);
void	mrt_parse_insert_camera(char **line_info, t_info *info, int *flags);
void	mrt_parse_insert_ambient(char **line_info, t_info *info, int *flags);
void	mrt_parse_insert_ratio(char *line_info, double *ratio);
void	mrt_parse_insert_color(char *line_info, t_color *color);
void	mrt_parse_insert_point(char *line_info, t_point *point);
void	mrt_parse_insert_vector(char *line_info, t_point *vector);
void	mrt_parse_insert_diameter(char *line_info, double *diameter);
void	mrt_parse_insert_element(char **line_info, t_info *info);

//mrt_util
void	mrt_print_err(char *str);
int		mrt_strlen(char *str);
void	mrt_lst_add_back(t_list **lst, t_list *new);
t_list	*mrt_lst_new_node(void *content);
char	*mrt_get_next_line(int fd);
char	*mrt_strchr(const char *s, int c);
char	*mrt_strdup(char *s1);
char	*mrt_substr(char *s, int start, int len);
char	*mrt_strjoin(char *s1, char *s2);
int		mrt_strcmp(char *s1, char *s2);
size_t	mrt_strlcpy(char *dst, char *src, size_t dstsize);
char	**mrt_split(char *s, char c);
int		mrt_bit_get(int bit_set, int bit_index);
int		mrt_bit_increase(int bit_set, int bit_index);
int		mrt_atoi(char *str);
double	mrt_atod(char *str);
int		mrt_split_size(char **split);

//mrt_render
void	mrt_render(t_info *info);
t_color	mrt_ray_trace(t_info *info, t_ray *ray);
void	mrt_put_pixel(t_info *info, int x, int y, t_color color);
t_point	mrt_ray_at(t_ray *ray, double t);
t_color	mrt_get_color(t_info *info, t_ray *ray);
void	mrt_ray_trace_sphere(t_info *info, t_ray *ray);
void	mrt_ray_trace_plane(t_info *info, t_ray *ray);
void	mrt_ray_trace_cylinder(t_info *info, t_ray *ray);
void	mrt_rescale_color(t_color *color);
void	mrt_color_overflow(t_color *color);
void	mrt_get_camera_info(t_camera *camera);
void	set_face_normal(t_ray *r, t_point *obj_n);
void	mrt_mlx_loop(t_info *info);

// mrt_shadow
int		mrt_shadow(t_info *info, t_ray *ray, t_point light_vec, double light_l);
double	mrt_hit_sphere(t_ray *ray, t_sphere *sphere);
double	mrt_hit_plane(t_ray *ray, t_plane *plane);
double	mrt_hit_cylinder(t_ray *ray, t_cylinder *cy);
double	mrt_hit_pillar(t_ray *ray, t_cylinder *cy);
double	mrt_hit_disk(t_ray *ray, t_cylinder *cy, int sign);
double	choice_pillar_root(t_ray *ray, t_cylinder *cy, double roots[]);
void	init_pillar_dis(t_ray *ray, t_cylinder *cy, t_discrimination *dis);
void	renew_t_pillar(t_ray *ray, t_cylinder *cy, double hit_t);
void	renew_t_disk(t_ray *ray, t_cylinder *cy, double hit_t, int sign);

//vec_util
t_point	vec3(double x, double y, double z);
t_point	point3(double x, double y, double z);
t_color	color3(double r, double g, double b);
void	vset(t_point *vec, double x, double y, double z);
double	vlength2(t_point vec);
double	vlength(t_point vec);
t_point	vplus(t_point vec, t_point vec2);
t_point	vplus_(t_point vec, double x, double y, double z);
t_point	vminus(t_point vec, t_point vec2);
t_point	vminus_(t_point vec, double x, double y, double z);
t_point	vmult(t_point vec, double t);
t_point	vmult_(t_point vec, t_point vec2);
t_point	vdivide(t_point vec, double t);
double	vdot(t_point vec, t_point vec2);
t_point	vcross(t_point vec, t_point vec2);
t_point	vunit(t_point vec);
t_point	vmin(t_point vec1, t_point vec2);
#endif
