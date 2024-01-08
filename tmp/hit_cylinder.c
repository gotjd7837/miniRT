#include "./includes/structures.h"
#include "./includes/utils.h"
#include "./includes/trace.h"
#include <stdio.h>
t_point3	get_axis(t_cylinder cy)
{
	return(vmult(cy.n, cy.height));
}

t_bool      hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_point3	n_axis; // axis : 중심선
	t_point3	w;
	double	roots[2];
	t_cylinder	*cy;
	double a;
	double b;
	double c;
    double  discriminant; //판별식

	cy = cy_obj->element;
	n_axis = cy->n;
	w = vminus(ray->orig, cy->center); //카메라와의 거리(방향벡터로 나타낸 원기둥의 중심) CO벡터
	a = vdot(ray->dir, ray->dir) - pow(vdot(ray->dir, n_axis), 2);
	b = 2.0 * (vdot(ray->dir, w) - vdot(ray->dir, n_axis) * vdot(w, n_axis));
	c =  vdot(w, w) - pow(vdot(w, n_axis), 2) - pow(cy->diameter/2, 2);
	discriminant = pow(b, 2) - (4.0 * a * c);
	if(discriminant < 0)
		return FALSE;
	roots[0] = (-b - sqrt(discriminant)) / (2.0 * a);
	roots[1] = (-b + sqrt(discriminant)) / (2.0 * a);
	rec->p = ray_at(ray, roots[0]);
	double cal_len = vdot(vminus(rec->p, vminus(cy->center, vmult(cy->n,0.5 * cy->height))), n_axis); //광선과 교차점의 직교 높이
	// double cal_len = vdot(vminus(rec->p, cy->center), n_axis); //광선과 교차점의 직교 높이
	if (cal_len >= 0 && cal_len <= vlength(get_axis(*cy)))
		rec->t = roots[0];
	else
	{
		rec->p = ray_at(ray, roots[1]);
		// cal_len = vdot(vminus(rec->p, cy->center), n_axis);
		if (cal_len >= 0 && cal_len <= vlength(get_axis(*cy)))
			rec->t = roots[1];
		else
			return FALSE;
	}
	if(rec->t < rec->tmin || rec->t > rec->tmax)
		return FALSE;
	// printf("%lf\n",vlength(get_axis(*cy)));
	t_vec3 cp = vminus(rec->p, cy->center);
	t_vec3 qp = vminus(cp, vmult(n_axis, vdot(cp, n_axis)));
	rec->normal = vunit(qp);
	// rec->normal = cy->n; // 왜 이걸로 하면 또 틀리는거지?
	rec->albedo = cy_obj->albedo;
	set_face_normal(ray, rec);
	return TRUE;
}

// //center를 밑면의 중심으로 본 공식.
// t_bool      hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
// {
// 	t_point3	n_axis; // axis : 중심선
// 	t_point3	w;
// 	double	roots[2];
// 	t_cylinder	*cy;
// 	double a;
// 	double b;
// 	double c;
//     double  discriminant; //판별식

// 	cy = cy_obj->element;
// 	n_axis = cy->n;
// 	w = vminus(ray->orig, cy->center); //카메라와의 거리(방향벡터로 나타낸 원기둥의 중심) CO벡터
// 	a = vdot(ray->dir, ray->dir) - pow(vdot(ray->dir, n_axis), 2);
// 	b = 2.0 * (vdot(ray->dir, w) - vdot(ray->dir, n_axis) * vdot(w, n_axis));
// 	c =  vdot(w, w) - pow(vdot(w, n_axis), 2) - pow(cy->diameter/2, 2);
// 	discriminant = pow(b, 2) - (4.0 * a * c);
// 	if(discriminant < 0)
// 		return FALSE;
// 	roots[0] = (-b - sqrt(discriminant)) / (2.0 * a);
// 	roots[1] = (-b + sqrt(discriminant)) / (2.0 * a);
// 	rec->p = ray_at(ray, roots[0]);
// 	// double cal_len = vdot(vminus(rec->p, vminus(cy->center, vmult(cy->n,0.5 * cy->height))), n_axis); //광선과 교차점의 직교 높이
// 	double cal_len = vdot(vminus(rec->p, cy->center), n_axis); //광선과 교차점의 직교 높이
// 	if (cal_len >= 0 && cal_len <= vlength(get_axis(*cy)))
// 		rec->t = roots[0];
// 	else
// 	{
// 		rec->p = ray_at(ray, roots[1]);
// 		// cal_len = vdot(vminus(rec->p, cy->center), n_axis);
// 		if (cal_len >= 0 && cal_len <= vlength(get_axis(*cy)))
// 			rec->t = roots[1];
// 		else
// 			return FALSE;
// 	}
// 	if(rec->t < rec->tmin || rec->t > rec->tmax)
// 		return FALSE;
// 	// printf("%lf\n",vlength(get_axis(*cy)));
// 	t_vec3 cp = vminus(rec->p, cy->center);
// 	t_vec3 qp = vminus(cp, vmult(n_axis, vdot(cp, n_axis)));
// 	rec->normal = vunit(qp);
// 	// rec->normal = cy->n; // 왜 이걸로 하면 또 틀리는거지?
// 	rec->albedo = cy_obj->albedo;
// 	set_face_normal(ray, rec);
// 	return TRUE;
// }
