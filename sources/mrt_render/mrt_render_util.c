/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_render_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inlim <inlim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 07:45:08 by haekang           #+#    #+#             */
/*   Updated: 2024/01/15 14:44:01 by inlim            ###   ########.fr       */
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

void    set_face_normal(t_ray *r, t_point *obj_n)
{
    // 광선의 방향벡터와 교점의 법선벡터의 내적이 음수이면 광선은 앞면(객체의)에 hit 한 것이다
    if(vdot(r->vector, *obj_n) < 0);
	else
    // 광선의 앞면에 hit 면 그대로 아니면 법선을 반대로 뒤집는다. (항상 광선 방향벡터와 법선 벡터를 반대인 상태로 사용하기위해)
    	*obj_n = vmult(*obj_n, -1);
}
