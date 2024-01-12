/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 07:41:48 by haekang           #+#    #+#             */
/*   Updated: 2024/01/12 19:52:30 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float	get_tan(float degree)
{
	static const float	radian = M_PI / 180;

	return (tan(degree * radian));
}

t_point	mrt_get_ray_vector(t_info *info, int x, int y)
{
	t_point		tmp;

	tmp = vplus(info->camera->left_bottom,
			vmult(info->camera->horizontal, x));
	tmp = vplus(tmp, vmult(info->camera->vertical, y));
	tmp = vminus(tmp, info->camera->point);
	return (vunit(tmp));
}

void	mrt_get_camera_info(t_camera *camera)
{
	t_point		tmp;

	camera->horizontal = vunit(vcross(camera->vector, vec3(0, -1, 0)));
	if (vlength(camera->horizontal) == 0)
		camera->horizontal = vunit(vcross(camera->vector, vec3(-1, 0, 0)));
	camera->vertical = vunit(vcross(camera->horizontal, camera->vector));
	camera->focal_len = ((float)WIDTH / 2) / get_tan(camera->fov / 2);
	tmp = vplus(camera->point, vmult(camera->vector, camera->focal_len));
	tmp = vminus(tmp, vmult(camera->horizontal, (float)(WIDTH - 1) / 2));
	tmp = vminus(tmp, vmult(camera->vertical, (float)(HEIGHT - 1) / 2));
	camera->left_bottom = tmp;
}








void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	mrt_render(t_info *info)
{
	t_ray		ray;
	t_color		color_pixel;
	int			x;
	int			y;

	mrt_get_camera_info(info->camera);
	y = HEIGHT - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray.point = info->camera->point;
			ray.vector = mrt_get_ray_vector(info, x, y);
			color_pixel = mrt_ray_trace(info, &ray);
			mrt_put_pixel(info, x, y, color_pixel);
			x++;
		}
		y--;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
	mlx_loop(info->mlx);
}
