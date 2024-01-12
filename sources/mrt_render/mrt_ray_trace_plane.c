/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_ray_trace_plane.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:04:02 by haekang           #+#    #+#             */
/*   Updated: 2024/01/12 15:04:36 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	mrt_hit_plane(t_ray *ray, t_plane *plane)
{
	double	denominator;
	double	nom;
	double	t;

	denominator = vdot(ray->vector, plane->vector);
	nom = vdot(vminus(plane->point, ray->point), plane->vector);
	if (denominator == 0)
		return (FALSE);
	t = nom / denominator;
	if (t < EPSILON || t > INF)
		return (FALSE);
	return (t);
}

void	mrt_ray_trace_plane(t_info *info, t_ray *ray)
{
	t_list	*list;
	t_plane	*plane;
	double	hit_t;

	list = info->plane;
	while (list)
	{
		plane = list->content;
		hit_t = mrt_hit_plane(ray, plane);
		if (hit_t > EPSILON && hit_t < INF && hit_t < ray->hit_t)
		{
			ray->hit_t = hit_t;
			ray->color = plane->color;
			ray->hit_point = mrt_ray_at(ray, hit_t);
			ray->hit_obj = plane;
			ray->obj_normal = plane->vector;
		}
		list = list->next;
	}
}
