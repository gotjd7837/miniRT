/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_insert_ambient.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:14:49 by haekang           #+#    #+#             */
/*   Updated: 2023/12/23 20:56:00 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	mrt_parse_insert_ambient(char **line_info, t_info *info, int *flags)
{
	*flags = mrt_bit_increase(*flags, AMBIENT_IDX);
	if (line_info[1] == NULL)
		mrt_print_err("Incorrect information for Ambient");
	else
		mrt_parse_insert_ambient_ratio();
	if (line_info[2] == NULL)
		mrt_print_err("Incorrect information for Ambient");
	else
		mrt_parse_insert_ambient_color();
}
