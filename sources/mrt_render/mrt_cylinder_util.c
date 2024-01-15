/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_cylinder_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inlim <inlim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 19:55:57 by inlim             #+#    #+#             */
/*   Updated: 2024/01/15 14:49:02 by inlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	choice_pillar_root(t_ray *ray, t_cylinder *cy, double roots[])
{
	t_point	p;
	t_point	n_axis;
	double	cal_len;

	p = mrt_ray_at(ray, roots[0]);
	n_axis = cy->vector;
	cal_len = vdot(vminus(p, vminus(cy->point, \
	vmult(cy->vector, 0.5 * cy->height))), n_axis);
	if (cal_len >= 0 && cal_len <= vlength(vmult(cy->vector, cy->height)))
		return (roots[0]);
	else
	{
		p = mrt_ray_at(ray, roots[1]);
		cal_len = vdot(vminus(p, vminus(cy->point, \
		vmult(cy->vector, 0.5 * cy->height))), n_axis);
		if (cal_len >= 0 && cal_len <= vlength(vmult(cy->vector, cy->height)))
			return (roots[1]);
		else
			return (FALSE);
	}
}

void	init_pillar_dis(t_ray *ray, t_cylinder *cy, t_discrimination *dis)
{
	t_point	n_axis;
	t_point	cr;

	cr = vminus(ray->point, cy->point);
	n_axis = cy->vector;
	dis->a = vdot(ray->vector, ray->vector) - pow(vdot(ray->vector, n_axis), 2);
	dis->b = 2.0 * \
	(vdot(ray->vector, cr) - vdot(ray->vector, n_axis) * vdot(cr, n_axis));
	dis->c = vdot(cr, cr) - pow(vdot(cr, n_axis), 2) - pow(cy->diameter / 2, 2);
	dis->expression = pow(dis->b, 2) - (4.0 * dis->a * dis->c);
}

void	renew_t_pillar(t_ray *ray, t_cylinder *cy, double hit_t)
{
	t_point	cp;
	t_point	qp;

	if (hit_t > EPSILON && hit_t < INF && hit_t < ray->hit_t)
	{
		ray->hit_t = hit_t;
		ray->color = cy->color;
		ray->hit_point = mrt_ray_at(ray, hit_t);
		ray->hit_obj = cy;
		cp = vminus(ray->hit_point, cy->point);
		qp = (vminus(cp, vmult(cy->vector, vdot(cp, cy->vector))));
		ray->obj_normal = vunit(qp);
		set_face_normal(ray, &(ray->obj_normal));	//구가 카메라 감쌀때 처리
	}
}

void	renew_t_disk(t_ray *ray, t_cylinder *cy, double hit_t, int sign)
{
	if (hit_t > EPSILON && hit_t < INF && hit_t < ray->hit_t)
	{
		ray->hit_t = hit_t;
		ray->color = cy->color;
		ray->hit_point = mrt_ray_at(ray, hit_t);
		ray->hit_obj = cy;
		ray->obj_normal = vmult(cy->vector, sign);
		set_face_normal(ray, &(ray->obj_normal));	//구가 카메라 감쌀때 처리
	}
}
