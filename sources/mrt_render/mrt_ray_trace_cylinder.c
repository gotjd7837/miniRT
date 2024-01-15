/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_ray_trace_cylinder.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inlim <inlim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 10:25:49 by haekang           #+#    #+#             */
/*   Updated: 2024/01/14 19:55:21 by inlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	mrt_hit_pillar(t_ray *ray, t_cylinder *cy)
{
	double				roots[2];
	t_discrimination	dis;

	init_pillar_dis(ray, cy, &dis);
	if (dis.expression < 0)
		return (FALSE);
	roots[0] = (-dis.b - sqrt(dis.expression)) / (2.0 * dis.a);
	roots[1] = (-dis.b + sqrt(dis.expression)) / (2.0 * dis.a);
	return (choice_pillar_root(ray, cy, roots));
}

double	mrt_hit_disk(t_ray *ray, t_cylinder *cy, int sign)
{
	t_plane	disk;
	double	denominator;
	double	nom;
	double	t;
	t_point	hit_point;

	if (sign == UP)
		disk.point = vplus(cy->point, vmult(cy->vector, 0.5 * cy->height));
	else if (sign == DOWN)
		disk.point = vminus(cy->point, vmult(cy->vector, 0.5 * cy->height));
	disk.vector = vunit(vmult(cy->vector, sign));
	denominator = vdot(ray->vector, disk.vector);
	if (denominator == 0)
		return (FALSE);
	nom = vdot(vminus(disk.point, ray->point), disk.vector);
	t = nom / denominator;
	hit_point = vplus(ray->point, vmult(ray->vector, t));
	if (vlength(vminus(hit_point, disk.point)) > cy->diameter / 2)
		return (FALSE);
	return (t);
}

void	mrt_ray_trace_cylinder(t_info *info, t_ray *ray)
{
	t_list		*list;
	t_cylinder	*cy;
	double		hit_t;

	list = info->cylinder;
	while (list)
	{
		cy = list->content;
		hit_t = mrt_hit_pillar(ray, cy);
		renew_t_pillar(ray, cy, hit_t);
		hit_t = mrt_hit_disk(ray, cy, UP);
		renew_t_disk(ray, cy, hit_t, UP);
		hit_t = mrt_hit_disk(ray, cy, DOWN);
		renew_t_disk(ray, cy, hit_t, DOWN);
		list = list->next;
	}
}
