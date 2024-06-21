/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_ray_trace_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeseong <haeseong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:40:48 by haekang           #+#    #+#             */
/*   Updated: 2024/06/21 17:49:59 by haeseong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// 구체와 ray의 교점의 거리를 반환하는 함수 (판별식)
double	mrt_hit_sphere(t_ray *ray, t_sphere *sphere, double hit_t)
{
	t_point	oc;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;

	oc = vminus(ray->point, sphere->point);
	a = vlength2(ray->vector);
	half_b = vdot(ray->vector, oc);
	c = vlength2(oc) - (sphere->diameter / 2) * (sphere->diameter / 2);
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (FALSE);
	hit_t = (-half_b - sqrt(discriminant)) / a;
	if (hit_t < EPSILON)
		hit_t = (-half_b + sqrt(discriminant)) / a;
	if (hit_t < EPSILON)
		return (FALSE);
	return (hit_t);
}

/**
 * 이 함수는 월드내의 모든 구와 주어진 ray의 교차를 검사하고, 가장 가까운
 * 교차 지점과 교차한 구의 정보를 ray 구조체에 저장합니다.
 */
void	mrt_ray_trace_sphere(t_info *info, t_ray *ray)
{
	t_list		*list;
	t_sphere	*sphere;
	double		hit_t;

	list = info->sphere; // 월드에서 구의 list
	while (list) // 모든 구체와 ray의 교점을 계산
	{
		sphere = list->content;
		hit_t = mrt_hit_sphere(ray, sphere, hit_t);
		if (hit_t > EPSILON && hit_t < INF && hit_t < ray->hit_t) // 교점이 가장 가까울 때
		{
			ray->hit_t = hit_t;
			ray->color = sphere->color;
			ray->hit_point = mrt_ray_at(ray, hit_t);
			ray->hit_obj = sphere;
			ray->obj_normal = vunit(vminus(ray->hit_point, sphere->point));
			set_face_normal(ray, &(ray->obj_normal));
		}
		list = list->next;
	}
}
