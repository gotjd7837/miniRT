/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:33:22 by haekang           #+#    #+#             */
/*   Updated: 2024/01/08 21:36:31 by haekang          ###   ########.fr       */
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

# define BUFFER_SIZE 42
# define AMBIENT_IDX 1
# define CAMERA_IDX 2
# define LIGHT_IDX 3

# define SP 0
# define LIGHT_POINT 1
# define EPSILON 1e-6 // 0.000001
# define FALSE 0
# define TRUE 1
# define LUMEN 3  // 이 값을 조절하여 장면의 밝기를 조절할 수 있다.

typedef struct s_point t_color;


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
	double      radius;
    double      radius2;
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
	t_point	left_bottom;
}	t_camera;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;














typedef struct	s_object
{
    int				type;
    void            *element;
    void            *next;
    t_color        albedo;
} t_object;

typedef struct  s_ray
{
    t_point    orig;
    t_point      dir;
}   t_ray;

typedef struct  s_canvas
{
    int     width; //canvas width
    int     height; //canvas height;
    double  aspect_ratio; //종횡비
}           t_canvas;

typedef struct s_hit_record
{
    t_point    p;
    t_point      normal;
    double      tmin;
    double      tmax;
    double      t;
    int			front_face;
    t_color    albedo;
} t_hit_record;

typedef struct  s_scene
{
    t_canvas        canvas;
    t_camera        camera;
    t_object        *world;
    t_object        *light;
    t_color         ambient; // 8.4에서 설명할 요소
    t_ray           ray;
    t_hit_record    rec;
} t_scene;














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

//vec_util
t_point	vec3(double x, double y, double z);
t_point	point3(double x, double y, double z);
t_color	color3(double r, double g, double b);
void	vset(t_point *vec, double x, double y, double z);
double	vlength2(t_point vec);
double      vlength(t_point vec);
t_point      vplus(t_point vec, t_point vec2);
t_point      vplus_(t_point vec, double x, double y, double z);
t_point      vminus(t_point vec, t_point vec2);
t_point      vminus_(t_point vec, double x, double y, double z);
t_point      vmult(t_point vec, double t);
t_point      vmult_(t_point vec, t_point vec2);
t_point      vdivide(t_point vec, double t);
double      vdot(t_point vec, t_point vec2);
t_point      vcross(t_point vec, t_point vec2);
t_point      vunit(t_point vec);
t_point  vmin(t_point vec1, t_point vec2);


#endif