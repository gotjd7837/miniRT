#include "./includes/structures.h"
#include "./includes/utils.h"
#include "./includes/trace.h"

t_bool	hit_disk_1(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	double denominator; // 분모
	double nom; // 분자
	double t; // 스칼라
	t_cylinder	*cy;
    t_point3    center;

	cy= cy_obj->element;
    center = vminus(cy->center, vmult(cy->n, 0.5 * cy->height));

	denominator = vdot(ray->dir, cy->n); // 광선벡터와 평면법선의 내적
	nom = vdot(vminus(center, ray->orig), cy->n); // 방향벡터로 나타낸 평면의 중심과 법선의 내적
	if(denominator == 0) // 광선벡터와 법선이 직교하면 표시하지 않음
		return FALSE;
	t = nom / denominator;
	if (t < rec->tmin || rec->tmax < t) // 카메라가 뒤에 있거나 너무 멀리 있으면 표시하지 않음.
            return (FALSE);
	if(vlength(vminus(vmult(ray->dir, t), center)) > cy->diameter / 2)
		return (FALSE);
	// 여기에서 기둥 거리랑 비교하자.
	rec->t = t;
	rec->p = ray_at(ray,t); // 교점 구하기
	rec->normal = cy->n;
    rec->albedo = cy_obj->albedo;
	set_face_normal(ray,rec);
	return TRUE;
}

t_bool	hit_disk_2(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	double denominator; // 분모
	double nom; // 분자
	double t; // 스칼라
	t_cylinder	*cy;
    t_point3    center;

	cy= cy_obj->element;
    center = vplus(cy->center, vmult(cy->n, 0.5 * cy->height));

	denominator = vdot(ray->dir, cy->n); // 광선벡터와 평면법선의 내적
	nom = vdot(vminus(center, ray->orig), cy->n); // 방향벡터로 나타낸 평면의 중심과 법선의 내적
	if(denominator == 0) // 광선벡터와 법선이 직교하면 표시하지 않음
		return FALSE;
	t = nom / denominator;
	if (t < rec->tmin || rec->tmax < t) // 카메라가 뒤에 있거나 너무 멀리 있으면 표시하지 않음.
            return (FALSE);
	if(vlength(vminus(vmult(ray->dir, t), center)) > cy->diameter / 2)
		return (FALSE);
	rec->t = t;
	rec->p = ray_at(ray,t); // 교점 구하기
	rec->normal = cy->n;
    rec->albedo = cy_obj->albedo;
	set_face_normal(ray,rec);
	return TRUE;
}
