/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_ray_trace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 07:43:44 by haekang           #+#    #+#             */
/*   Updated: 2024/01/12 21:12:20 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color	mrt_ray_trace(t_info *info, t_ray *ray)
{
	t_color	color;

	ray->hit_t = INF;
	mrt_ray_trace_sphere(info, ray);
	mrt_ray_trace_plane(info, ray);
	// mrt_ray_trace_cylinder(info, ray);
	if (ray->hit_t == INF || ray->hit_t == 0)
		color = color3(0, 0, 0);
	else
	{
		color = mrt_get_color(info, ray);
		// printf("color: %f %f %f\n", color.x, color.y, color.z);
	}
	return (color);
}
