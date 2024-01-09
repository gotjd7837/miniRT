/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_ray_trace_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 07:44:18 by haekang           #+#    #+#             */
/*   Updated: 2024/01/10 08:33:23 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	mrt_hit_sphere(t_ray *ray, t_sphere *sphere)
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
	//구가 카메라 감쌀때 에러처리
	return ((-half_b - sqrt(discriminant)) / a);
}

void	mrt_ray_trace_sphere(t_info *info, t_ray *ray)
{
	t_list		*list;
	t_sphere	*sphere;
	double		hit_t;

	list = info->sphere;
	while (list)
	{
		sphere = list->content;
		hit_t = mrt_hit_sphere(ray, sphere);
		if (hit_t > EPSILON && hit_t < INF && hit_t < ray->hit_t)
		{
			ray->hit_t = hit_t;
			ray->color = sphere->color;
			ray->hit_point = mrt_ray_at(ray, hit_t);
			ray->hit_obj = sphere;
			ray->obj_normal = vunit(vminus(ray->hit_point, sphere->point));
		}
		list = list->next;
	}
}
