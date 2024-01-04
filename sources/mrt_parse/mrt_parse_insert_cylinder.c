/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_insert_cylinder.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:14:54 by haekang           #+#    #+#             */
/*   Updated: 2024/01/04 20:41:55 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	mrt_parse_insert_cylinder_height(char *line_info, double *height)
{
	char	**height_info;
	int		i;

	i = 0;
	height_info = mrt_split(line_info, ',');
	if (height_info == NULL)
		mrt_print_err("malloc failed\n");
	if (mrt_split_size(height_info) != 1)
		mrt_print_err("Incorrect information for height\n");
	*height = mrt_atod(line_info);
	while (i < 1)
		free(height_info[i++]);
	free(height_info);
}

void	mrt_parse_insert_cylinder(char **line_info, t_info *info)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		mrt_print_err("malloc failed\n");
	if (line_info[1] == NULL)
		mrt_print_err("Do not input point for Cylinder\n");
	else
		mrt_parse_insert_point(line_info[1], &(cylinder->point));
	if (line_info[2] == NULL)
		mrt_print_err("Do not input vector for Cylinder\n");
	else
		mrt_parse_insert_vector(line_info[2], &(cylinder->vector));
	if (line_info[3] == NULL)
		mrt_print_err("Do not input diameter for Cylinder\n");
	else
		mrt_parse_insert_diameter(line_info[3], &(cylinder->diameter));
	if (line_info[4] == NULL)
		mrt_print_err("Do not input height for Cylinder\n");
	else
		mrt_parse_insert_cylinder_height(line_info[4], &(cylinder->height));
	if (line_info[5] == NULL)
		mrt_print_err("Do not input color for Cylinder\n");
	else
		mrt_parse_insert_color(line_info[5], &(cylinder->color));
	if (line_info[6] == NULL)
		return ;
	else
		mrt_print_err("Incorrect information for Cylinder\n");
	mrt_lst_add_back(&(info->cylinder), mrt_lst_new_node(cylinder));
}
