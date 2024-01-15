/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_render_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 07:45:08 by haekang           #+#    #+#             */
/*   Updated: 2024/01/15 20:22:43 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	mrt_color_overflow(t_color *color)
{
	if (color->x > 1)
		color->x = 1;
	if (color->y > 1)
		color->y = 1;
	if (color->z > 1)
		color->z = 1;
}

void	mrt_rescale_color(t_color *color)
{
	color->x = color->x / 255;
	color->y = color->y / 255;
	color->z = color->z / 255;
}

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
	rgb = ((int)(r * 255.999) << 16) + ((int)(g * 255.999) << 8)
		+ (int)(b * 255.999);
	dst = info->img.addr + (y * info->img.line_length + x
			* (info->img.bits_per_pixel / 8));
	*(unsigned int *)dst = rgb;
}

void	set_face_normal(t_ray *r, t_point *obj_n)
{
	if (vdot(r->vector, *obj_n) < 0)
		return ;
	else
		*obj_n = vmult(*obj_n, -1);
}
