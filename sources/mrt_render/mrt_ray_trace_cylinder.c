/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_ray_trace_cylinder.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 10:25:49 by haekang           #+#    #+#             */
/*   Updated: 2024/01/13 10:25:55 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_point	get_axis(t_cylinder cy)
{
	return(vmult(cy.vector, cy.height));
}

double	mrt_hit_upper_disk(t_ray *ray, t_cylinder *cy)
{
	double denominator; // 분모
	double nom; // 분자
	double t; // 스칼라
    t_point    center;

    center = vplus(cy->point, vmult(cy->vector, 0.5 * cy->height));//
	denominator = vdot(ray->vector, cy->vector); // 광선벡터와 평면법선의 내적
	if(denominator == 0) // 광선벡터와 법선이 직교하면 표시하지 않음
		return FALSE;
	nom = vdot(vminus(center, ray->point), cy->vector); // 방향벡터로 나타낸 평면의 중심과 법선의 내적
	t = nom / denominator;
	if(vlength(vminus(vmult(ray->vector, t), center)) > cy->diameter / 2)
		return (FALSE);
	return t;
}

// double	mrt_hit_down_disk(t_ray *ray, t_cylinder *cy)
// {
// 	double denominator; // 분모
// 	double nom; // 분자
// 	double t; // 스칼라
//     t_point    center;

// 	center = vminus(cy->point, vmult(cy->vector, 0.5 * cy->height));//원기둥의 중심
// 	t_point n = vunit(vmult(cy->vector, -1));//원기둥의 아래면의 법선벡터
// 	denominator = vdot(ray->vector, n); // 광선벡터와 평면법선의 내적
// 	if(denominator == 0) // 광선벡터와 법선이 직교하면 표시하지 않음
// 		return FALSE;
// 	nom = vdot(vminus(center, ray->point), n); // 방향벡터로 나타낸 평면의 중심과 법선의 내적
// 	t = nom / denominator;
// 	if(vlength(vminus(vmult(ray->vector, t), center)) > cy->diameter / 2)
// 		return (FALSE);
// 	return t;
// }

double mrt_hit_down_disk(t_ray *ray, t_cylinder *cy)
{
    double denominator; // 분모
    double nom;        // 분자
    double t;          // 스칼라
    t_point center;

    center = vminus(cy->point, vmult(cy->vector, 0.5 * cy->height));
    t_point n = vunit(vmult(cy->vector, -1));

    denominator = vdot(ray->vector, n);
    if (denominator == 0)
        return FALSE;

    nom = vdot(vminus(center, ray->point), n);
    t = nom / denominator;

    t_point hit_point = vplus(ray->point, vmult(ray->vector, t));
    double distance_to_center = vlength(vminus(hit_point, center));

    if (distance_to_center > cy->diameter / 2)
        return FALSE;

    return t;
}
  
double	mrt_hit_pillar(t_ray *ray, t_cylinder *cy)
{
	t_point	n_axis; // axis : 중심선
	t_point	w;
	double	roots[2];
	double a;
	double b;
	double c;
    double  discriminant; //판별식

	n_axis = cy->vector;
	w = vminus(ray->point, cy->point); //카메라와의 거리(방향벡터로 나타낸 원기둥의 중심) CO벡터
	a = vdot(ray->vector, ray->vector) - pow(vdot(ray->vector, n_axis), 2);
	b = 2.0 * (vdot(ray->vector, w) - vdot(ray->vector, n_axis) * vdot(w, n_axis));
	c =  vdot(w, w) - pow(vdot(w, n_axis), 2) - pow(cy->diameter/2, 2);
	discriminant = pow(b, 2) - (4.0 * a * c);
	if(discriminant < 0)
		return FALSE; // 반환값이 hit_t로 기록되는데 FALSE(0)을 return 해도 되나...
	roots[0] = (-b - sqrt(discriminant)) / (2.0 * a);
	roots[1] = (-b + sqrt(discriminant)) / (2.0 * a);
	t_point p = mrt_ray_at(ray, roots[0]);
	double cal_len = vdot(vminus(p, vminus(cy->point, vmult(cy->vector,0.5 * cy->height))), n_axis); //광선과 교차점의 직교 높이
	if (cal_len >= 0 && cal_len <= vlength(get_axis(*cy)))
		return roots[0];
	else
	{
		p = mrt_ray_at(ray, roots[1]);
		cal_len = vdot(vminus(p, vminus(cy->point, vmult(cy->vector,0.5 * cy->height))), n_axis);
		if (cal_len >= 0 && cal_len <= vlength(get_axis(*cy)))
			return roots[1];
		else
			return FALSE;
	}
}

void mrt_ray_trace_cylinder(t_info *info, t_ray *ray)
{
	t_list		*list;
	t_cylinder	*cy;
	double		hit_t;

	list = info->cylinder;
	while (list)
	{
		cy = list->content;

		hit_t = mrt_hit_pillar(ray, cy);
		if (hit_t > EPSILON && hit_t < INF && hit_t < ray->hit_t)
		{
			ray->hit_t = hit_t;
			ray->color = cy->color;
			ray->hit_point = mrt_ray_at(ray, hit_t);
			ray->hit_obj = cy;
			t_point cp = vminus(ray->hit_point, cy->point);
			t_point qp = (vminus(cp, vmult(cy->vector, vdot(cp, cy->vector))));
			ray->obj_normal = vunit(qp);
		}
		hit_t = mrt_hit_upper_disk(ray, cy);
		if (hit_t > EPSILON && hit_t < INF && hit_t < ray->hit_t)
		{
			ray->hit_t = hit_t;
			ray->color = cy->color;
			ray->hit_point = mrt_ray_at(ray, hit_t);
			ray->hit_obj = cy;
			ray->obj_normal = cy->vector;
		}

		hit_t = mrt_hit_down_disk(ray, cy);
		if (hit_t > EPSILON && hit_t < INF && hit_t < ray->hit_t)
		{
			ray->hit_t = hit_t;
			ray->color = cy->color;
			ray->hit_point = mrt_ray_at(ray, hit_t);
			ray->hit_obj = cy;
			ray->obj_normal = vmult(cy->vector, -1);
		}
		list = list->next;
	}
}
