/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_get_camera_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeseong <haeseong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 10:27:27 by haekang           #+#    #+#             */
/*   Updated: 2024/06/21 17:06:33 by haeseong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float	get_tan(float degree)
{
	static const float	radian = M_PI / 180;

	return (tan(degree * radian));
}

/**
 * 이 함수는 카메라의 수평, 수직 벡터 및 기타 정보를 계산하여 설정합니다.
 * 카메라의 수평 벡터는 카메라의 방향 벡터와 (0, -1, 0) 벡터의 외적을 통해 구하며,
 * 이 값이 0일 경우 (카메라의 방향 벡터가 수직인 경우) (1, 0, 0) 벡터와의 외적을 통해 구합니다.
 * 그런 다음, 카메라의 수직 벡터와 초점 거리를 계산하고,
 * 카메라의 왼쪽 아래 지점을 설정합니다.
 */
void	mrt_get_camera_info(t_camera *camera)
{
	t_point		tmp;

	camera->horizontal = vunit(vcross(camera->vector, vec3(0, -1, 0))); // 수평 벡터 계산
	if (vlength(camera->horizontal) == 0)
		camera->horizontal = vunit(vcross(camera->vector, vec3(-1, 0, 0)));
	
	camera->vertical = vunit(vcross(camera->horizontal, camera->vector)); // 수직 벡터 계산
	
	camera->focal_len = ((float)WIDTH / 2) / get_tan(camera->fov / 2); // 카메라의 초점 거리 계산
	
	tmp = vplus(camera->point, vmult(camera->vector, camera->focal_len));
	tmp = vminus(tmp, vmult(camera->horizontal, (float)(WIDTH - 1) / 2));
	tmp = vminus(tmp, vmult(camera->vertical, (float)(HEIGHT - 1) / 2));
	camera->left_bottom = tmp; // window의 왼쪽 아래 지점 좌표
}
