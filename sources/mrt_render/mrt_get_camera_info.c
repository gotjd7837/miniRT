/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_get_camera_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 10:27:27 by haekang           #+#    #+#             */
/*   Updated: 2024/01/13 10:28:16 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float	get_tan(float degree)
{
	static const float	radian = M_PI / 180;

	return (tan(degree * radian));
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
