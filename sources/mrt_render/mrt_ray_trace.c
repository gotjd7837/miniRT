/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_ray_trace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeseong <haeseong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 07:43:44 by haekang           #+#    #+#             */
/*   Updated: 2024/06/21 17:42:40 by haeseong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * @ray: 추적할 레이 구조체 포인터
 *
 * 이 함수는 레이가 씬의 객체들과 교차하는지 확인하고, 교차하는 경우
 * 해당 지점의 색상을 계산하여 반환합니다. 교차하는 객체가 없는 경우,
 * 기본 색상 (검정색)을 반환합니다.
 *
 * 반환값: 계산된 색상 (t_color 구조체)
 */
t_color	mrt_ray_trace(t_info *info, t_ray *ray)
{
	t_color	color;

	ray->hit_t = INF;
	mrt_ray_trace_sphere(info, ray); // 구체와의 교점 검사
	mrt_ray_trace_plane(info, ray); // 평면과의 교점 검사
	mrt_ray_trace_cylinder(info, ray); // 원통과의 교점 검사
	if (ray->hit_t == INF || ray->hit_t == 0)
		color = color3(0, 0, 0);
	else
		color = mrt_get_color(info, ray);
	return (color);
}
