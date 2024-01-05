/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_insert_sphere.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:15:02 by haekang           #+#    #+#             */
/*   Updated: 2024/01/05 16:43:49 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	mrt_parse_insert_sphere(char **line_info, t_info *info)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (sphere == NULL)
		mrt_print_err("malloc failed\n");
	if (line_info[1] == NULL)
		mrt_print_err("Do not input point for Sphere\n");
	else
		mrt_parse_insert_point(line_info[1], &(sphere->point));
	if (line_info[2] == NULL)
		mrt_print_err("Do not input diameter for Sphere\n");
	else
		mrt_parse_insert_diameter(line_info[2], &(sphere->diameter));
	if (line_info[3] == NULL)
		mrt_print_err("Do not input color for Sphere\n");
	else
		mrt_parse_insert_color(line_info[3], &(sphere->color));
	if (line_info[4] == NULL)
	{
		mrt_lst_add_back(&(info->sphere), mrt_lst_new_node(sphere));
		return ;
	}
	else
		mrt_print_err("Incorrect information for Sphere\n");
}
