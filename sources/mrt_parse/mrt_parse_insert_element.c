/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_insert_element.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:36:26 by haekang           #+#    #+#             */
/*   Updated: 2024/01/15 17:09:48 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	mrt_parse_insert_element(char **line_info, t_info *info)
{
	static int	flags;

	if (!mrt_strcmp(line_info[0], "A") && !mrt_bit_get(flags, AMBIENT_IDX))
		mrt_parse_insert_ambient(line_info, info, &flags);
	else if (!mrt_strcmp(line_info[0], "C") && !mrt_bit_get(flags, CAMERA_IDX))
		mrt_parse_insert_camera(line_info, info, &flags);
	else if (!mrt_strcmp(line_info[0], "L") && !mrt_bit_get(flags, LIGHT_IDX))
		mrt_parse_insert_light(line_info, info, &flags);
	else if (!(mrt_strcmp(line_info[0], "sp")))
		mrt_parse_insert_sphere(line_info, info);
	else if (!(mrt_strcmp(line_info[0], "pl")))
		mrt_parse_insert_plane(line_info, info);
	else if (!(mrt_strcmp(line_info[0], "cy")))
		mrt_parse_insert_cylinder(line_info, info);
	else
		mrt_print_err("Invalid identifier\n");
}
