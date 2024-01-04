/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_insert_plane.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:14:59 by haekang           #+#    #+#             */
/*   Updated: 2024/01/04 20:42:08 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	mrt_parse_insert_plane(char **line_info, t_info *info)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (plane == NULL)
		mrt_print_err("malloc failed\n");
	if (line_info[1] == NULL)
		mrt_print_err("Do not input point for Plane\n");
	else
		mrt_parse_insert_point(line_info[1], &(plane->point));
	if (line_info[2] == NULL)
		mrt_print_err("Do not input vector for Plane\n");
	else
		mrt_parse_insert_vector(line_info[2], &(plane->vector));
	if (line_info[3] == NULL)
		mrt_print_err("Do not input color for Plane\n");
	else
		mrt_parse_insert_color(line_info[3], &(plane->color));
	if (line_info[4] == NULL)
		return ;
	else
		mrt_print_err("Incorrect information for Plane\n");
	mrt_lst_add_back(&(info->plane), mrt_lst_new_node(plane));
}
