/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_atod.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:20:54 by haekang           #+#    #+#             */
/*   Updated: 2024/01/04 21:37:08 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	mrt_atod_loop(char *str, double *res, double decimal_place)
{
	while (*str != '\0' && *str != '\n' && *str != '.')
	{
		if (*str < '0' || *str > '9')
			mrt_print_err("atod error\n");
		*res = *res * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str != '\0' && *str != '\n')
		{
			if (*str < '0' || *str > '9')
				mrt_print_err("atod error\n");
			*res += decimal_place * (*str - '0');
			decimal_place *= 0.1;
			str++;
		}
	}
}

double	mrt_atod(char *str)
{
	double	res;
	int		sign;
	double	decimal_place;

	res = 0;
	sign = 1;
	decimal_place = 0.1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (*str < '0' || *str > '9')
		mrt_print_err("atod error\n");
	mrt_atod_loop(str, &res, decimal_place);
	return (sign * res);
}
