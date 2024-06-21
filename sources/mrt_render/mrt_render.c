/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeseong <haeseong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 07:41:48 by haekang           #+#    #+#             */
/*   Updated: 2024/06/21 17:18:13 by haeseong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * @x: 현재 픽셀의 x 좌표
 * @y: 현재 픽셀의 y 좌표
 *
 * 이 함수는 카메라의 왼쪽 아래 지점에서 시작하여 수평 및 수직 벡터를 곱하여
 * 주어진 x, y 좌표에 해당하는 지점의 레이 벡터를 계산합니다.
 * 계산된 레이 벡터는 단위 벡터로 반환됩니다.
 */
t_point	mrt_get_ray_vector(t_info *info, int x, int y)
{
	t_point		tmp;

	tmp = vplus(info->camera->left_bottom,
			vmult(info->camera->horizontal, x));
	tmp = vplus(tmp, vmult(info->camera->vertical, y));
	tmp = vminus(tmp, info->camera->point); // (window의 좌표 - 카메라 좌표)
	return (vunit(tmp));
}

void	mrt_render(t_info *info)
{
	t_ray		ray;
	t_color		color_pixel;
	int			x;
	int			y;

	mrt_get_camera_info(info->camera); // 카메라 정보 설정
	y = 0;
	while (y < HEIGHT) // window의 모든 좌표에 반복
	{
		x = 0;
		while (x < WIDTH)
		{
			ray.point = info->camera->point;
			ray.vector = mrt_get_ray_vector(info, x, y); // ray의 방향 벡터
			color_pixel = mrt_ray_trace(info, &ray); // 레이를 추적해서 해당 픽셀의 color 계산
			mrt_put_pixel(info, WIDTH - x, y, color_pixel);
			x++;
		}
		y++;
	}
	mrt_mlx_loop(info);
}
