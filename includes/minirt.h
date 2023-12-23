/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:33:22 by haekang           #+#    #+#             */
/*   Updated: 2023/12/23 20:33:21 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "mlx/mlx.h"

# define BUFFER_SIZE 42
# define AMBIENT_IDX 0
# define CAMERA_IDX 1
# define LIGHT_IDX 2

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

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

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
}	t_light;

typedef struct s_camera
{
	t_point	point;
	t_point	vector;
	double	fov;
}	t_camera;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_info
{
	void		*mlx;
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_list		*sphere;
	t_list		*plane;
	t_list		*cylinder;
}	t_info;

//mrt_parse
t_info	*mrt_parse(char *file_name);
char	*mrt_parse_return_file_path(char *file_name);
t_info	*mrt_parse_load_file(char *file_path);
t_info	*mrt_parse_init_info(t_info *info);
void	mrt_parse_insert_sphere(char **line_info, t_info *info);
void	mrt_parse_insert_plane(char **line_info, t_info *info);
void	mrt_parse_insert_light(char **line_info, t_info *info, int *flags);
void	mrt_parse_insert_cylinder(char **line_info, t_info *info);
void	mrt_parse_insert_camera(char **line_info, t_info *info, int *flags);
void	mrt_parse_insert_ambient(char **line_info, t_info *info, int *flags);

//mrt_util
void	mrt_print_err(char *str);
int		mrt_strlen(char *str);
void	mrt_lst_add_back(t_list **lst, t_list *new);
t_list	*mrt_lst_new_node(void *content);
char	*mrt_get_next_line(int fd);
char	*mrt_strchr(const char *s, int c);
char	*mrt_strdup(const char *s1);
char	*mrt_substr(char const *s, unsigned int start, size_t len);
char	*mrt_strjoin(char *s1, char *s2);
int		mrt_strcmp(char *s1, char *s2);
size_t	mrt_strlcpy(char *dst, char *src, size_t dstsize);
char	**mrt_split(char *s, char c);
int		mrt_bit_get(int bit_set, int bit_index);
int		mrt_bit_increase(int bit_set, int bit_index);

#endif