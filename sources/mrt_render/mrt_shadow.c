/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_shadow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 10:29:34 by haekang           #+#    #+#             */
/*   Updated: 2024/01/15 13:53:04 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	mrt_shadow(t_info *info, t_ray *ray, t_point light_vec, double light_len)
{
	t_ray	shadow_ray;

	shadow_ray.hit_t = INF;
	shadow_ray.point = ray->hit_point;
	shadow_ray.vector = light_vec;
	mrt_ray_trace_sphere(info, &shadow_ray);
	mrt_ray_trace_plane(info, &shadow_ray);
	mrt_ray_trace_cylinder(info, &shadow_ray);
	if (shadow_ray.hit_t > EPSILON && shadow_ray.hit_t < light_len)
		return (TRUE);
	return (FALSE);
}
