/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_insert_camera.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:14:52 by haekang           #+#    #+#             */
/*   Updated: 2023/12/23 22:27:39 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	mrt_parse_insert_camera(char **line_info, t_info *info, int *flags)
{
	*flags = mrt_bit_increase(*flags, CAMERA_IDX);
	if (line_info[1] == NULL)
		mrt_print_err("Do not input ratio for Ambient\n");
	else
		mrt_parse_insert_ambient_ratio();
	if (line_info[2] == NULL)
		mrt_print_err("Do not input RGB for Ambient\n");
	else
		mrt_parse_insert_ambient_color();
	if (line_info[3] == NULL)
		return ;
	else
		mrt_print_err("Incorrect information for Ambient\n");
}