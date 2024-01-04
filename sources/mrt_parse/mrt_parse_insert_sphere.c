/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_insert_sphere.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeseong <haeseong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:15:02 by haekang           #+#    #+#             */
/*   Updated: 2024/01/02 17:11:11 by haeseong         ###   ########.fr       */
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
		mrt_parse_insert_point();
	if (line_info[2] == NULL)
		mrt_print_err("Do not input diameter for Sphere\n");
	else
		mrt_parse_insert_sphere_diameter();
	if (line_info[3] == NULL)
		mrt_print_err("Do not input color for Sphere\n");
	else
		mrt_parse_insert_color();
	if (line_info[4] == NULL)
		return ;
	else
		mrt_print_err("Incorrect information for Sphere\n");
	mrt_lst_add_back(&(info->sphere), mrt_lst_new(sphere));
}
