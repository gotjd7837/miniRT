/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_insert_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeseong <haeseong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:46:33 by haeseong          #+#    #+#             */
/*   Updated: 2024/01/02 18:08:47 by haeseong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	mrt_parse_insert_point(char *line_info, t_point *point)
{
	
}

void	mrt_parse_insert_color(char *line_info, t_color *color)
{
	int		tmp[3];
	int		i;

	i = 0;
	while (i < 3)
	{
		tmp[i] = mrt_atoi(line_info);
		if (tmp[i] < 0 || tmp[i] > 255)
			mrt_print_err("color value err\n");
		while (*line_info != '\0' && *line_info != ',')
			line_info++;
		if (*line_info == ',')
			line_info++;
		i++;
	}
	color->r = tmp[0];
	color->g = tmp[1];
	color->b = tmp[2];
}

void	mrt_parse_insert_ratio(char *line_info, double *ratio)
{
	double	tmp;

	tmp = mrt_atod(line_info);
	if (tmp < 0 || tmp > 1)
		mrt_print_err("ratio value err\n");
	*ratio = tmp;
}
