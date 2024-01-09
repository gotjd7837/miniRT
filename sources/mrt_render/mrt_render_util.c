/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_render_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 07:45:08 by haekang           #+#    #+#             */
/*   Updated: 2024/01/10 07:45:21 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_point	mrt_ray_at(t_ray *ray, double t)
{
	t_point	at;

	at = vplus(ray->point, vmult(ray->vector, t));
	return (at);
}

void	mrt_put_pixel(t_info *info, int x, int y, t_color color)
{
	char	*dst;
	double	r;
	double	g;
	double	b;
	int		rgb;

	r = color.x;
	g = color.y;
	b = color.z;
	rgb = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8)
		+ ((int)(255.999 * b));
	dst = info->img.addr + (y * info->img.line_length + x
			* (info->img.bits_per_pixel / 8));
	*(unsigned int *)dst = rgb;
}
