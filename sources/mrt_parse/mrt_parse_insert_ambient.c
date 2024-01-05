/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_insert_ambient.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:14:49 by haekang           #+#    #+#             */
/*   Updated: 2024/01/05 16:41:12 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	mrt_parse_insert_ambient(char **line_info, t_info *info, int *flags)
{
	t_ambient	*ambient;

	*flags = mrt_bit_increase(*flags, AMBIENT_IDX);
	ambient = (t_ambient *)malloc(sizeof(t_ambient));
	if (ambient == NULL)
		mrt_print_err("malloc failed\n");
	if (line_info[1] == NULL)
		mrt_print_err("Do not input ratio for Ambient\n");
	else
		mrt_parse_insert_ratio(line_info[1], &(ambient->ratio));
	if (line_info[2] == NULL)
		mrt_print_err("Do not input color for Ambient\n");
	else
		mrt_parse_insert_color(line_info[2], &(ambient->color));
	if (line_info[3] == NULL)
	{
		info->ambient = ambient;
		return ;
	}
	else
		mrt_print_err("Incorrect information for Ambient\n");
}
