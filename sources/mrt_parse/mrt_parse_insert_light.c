/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_insert_light.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeseong <haeseong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:14:57 by haekang           #+#    #+#             */
/*   Updated: 2024/01/02 17:31:30 by haeseong         ###   ########.fr       */
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
		mrt_parse_insert_point();
	if (line_info[2] == NULL)
		mrt_print_err("Do not input ratio for Light\n");
	else
		mrt_parse_insert_ratio();
	if (line_info[3] == NULL)
		mrt_print_err("Do not input color for Light\n");
	else
		mrt_parse_insert_color();
	if (line_info[4] == NULL)
		return ;
	else
		mrt_print_err("Incorrect information for Light\n");
	info->light = light;
}
