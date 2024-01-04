/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_insert_cylinder.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeseong <haeseong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:14:54 by haekang           #+#    #+#             */
/*   Updated: 2024/01/02 17:35:08 by haeseong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	mrt_parse_insert_cylinder(char **line_info, t_info *info)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		mrt_print_err("malloc failed\n");
	if (line_info[1] == NULL)
		mrt_print_err("Do not input point for Cylinder\n");
	else
		mrt_parse_insert_point();
	if (line_info[2] == NULL)
		mrt_print_err("Do not input vector for Cylinder\n");
	else
		mrt_parse_insert_vector();
	if (line_info[3] == NULL)
		mrt_print_err("Do not input diameter for Cylinder\n");
	else
		mrt_parse_insert_cylinder_diameter();
	if (line_info[4] == NULL)
		mrt_print_err("Do not input height for Cylinder\n");
	else
		mrt_parse_insert_cylinder_height();
	if (line_info[5] == NULL)
		mrt_print_err("Do not input color for Cylinder\n");
	else
		mrt_parse_insert_color();
	if (line_info[6] == NULL)
		return ;
	else
		mrt_print_err("Incorrect information for Cylinder\n");
	mrt_lst_add_back(&(info->cylinder), mrt_lst_new(cylinder));
}