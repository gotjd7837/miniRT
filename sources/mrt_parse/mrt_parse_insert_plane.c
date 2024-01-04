/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_insert_plane.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeseong <haeseong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:14:59 by haekang           #+#    #+#             */
/*   Updated: 2024/01/02 17:34:38 by haeseong         ###   ########.fr       */
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
		mrt_parse_insert_point();
	if (line_info[2] == NULL)
		mrt_print_err("Do not input vector for Plane\n");
	else
		mrt_parse_insert_vector();
	if (line_info[3] == NULL)
		mrt_print_err("Do not input color for Plane\n");
	else
		mrt_parse_insert_color();
	if (line_info[4] == NULL)
		return ;
	else
		mrt_print_err("Incorrect information for Plane\n");
	mrt_lst_add_back(&(info->plane), mrt_lst_new(plane));
}
