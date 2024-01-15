/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 07:41:48 by haekang           #+#    #+#             */
/*   Updated: 2024/01/15 16:22:26 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_point	mrt_get_ray_vector(t_info *info, int x, int y)
{
	t_point		tmp;

	tmp = vplus(info->camera->left_bottom,
			vmult(info->camera->horizontal, x));
	tmp = vplus(tmp, vmult(info->camera->vertical, y));
	tmp = vminus(tmp, info->camera->point);
	return (vunit(tmp));
}

void	mrt_render(t_info *info)
{
	t_ray		ray;
	t_color		color_pixel;
	int			x;
	int			y;

	mrt_get_camera_info(info->camera);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray.point = info->camera->point;
			ray.vector = mrt_get_ray_vector(info, x, y);
			color_pixel = mrt_ray_trace(info, &ray);
			mrt_put_pixel(info, WIDTH - x, y, color_pixel);
			x++;
		}
		y++;
	}
	mrt_mlx_loop(info);
}
