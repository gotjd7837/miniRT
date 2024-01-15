/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_ray_trace_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inlim <inlim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:40:48 by haekang           #+#    #+#             */
/*   Updated: 2024/01/15 14:47:30 by inlim            ###   ########.fr       */
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

	double	root;

	oc = vminus(ray->point, sphere->point);
	a = vlength2(ray->vector);
	half_b = vdot(ray->vector, oc);
	c = vlength2(oc) - (sphere->diameter / 2) * (sphere->diameter / 2);
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (FALSE);
	root = (-half_b - sqrt(discriminant)) / a;
	if (root < EPSILON)
		root = (-half_b + sqrt(discriminant)) / a;
	if (root < EPSILON)
		return (FALSE);
	return (root);
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
			set_face_normal(ray, &(ray->obj_normal));	//구가 카메라 감쌀때 처리
		}
		list = list->next;
	}
}
