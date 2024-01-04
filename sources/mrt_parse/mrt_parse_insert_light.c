/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_insert_light.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:14:57 by haekang           #+#    #+#             */
/*   Updated: 2024/01/04 19:02:21 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	mrt_parse_insert_light(char **line_info, t_info *info, int *flags)
{
	t_light	*light;

	*flags = mrt_bit_increase(*flags, LIGHT_IDX);
	light = (t_light *)malloc(sizeof(t_light));
	if (light == NULL)
		mrt_print_err("malloc failed\n");
	if (line_info[1] == NULL)
		mrt_print_err("Do not input point for Light\n");
	else
		mrt_parse_insert_point(line_info[1], &(light->point));
	if (line_info[2] == NULL)
		mrt_print_err("Do not input ratio for Light\n");
	else
		mrt_parse_insert_ratio(line_info[2], &(light->ratio));
	if (line_info[3] == NULL)
		mrt_print_err("Do not input color for Light\n");
	else
		mrt_parse_insert_color(line_info[3], &(light->color));
	if (line_info[4] == NULL)
		return ;
	else
		mrt_print_err("Incorrect information for Light\n");
	info->light = light;
}
