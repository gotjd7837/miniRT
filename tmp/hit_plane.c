#include "./includes/structures.h"
#include "./includes/utils.h"
#include "./includes/trace.h"

// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection.html
t_bool      hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
{
	double denominator; // 분모
	double nom; // 분자
	double t; // 스칼라
	t_plane* pl;

	pl= pl_obj->element;

	denominator = vdot(ray->dir, pl->n); // 광선벡터와 평면법선의 내적
	nom = vdot(vminus(pl->center, ray->orig), pl->n); // 방향벡터로 나타낸 평면의 중심과 법선의 내적
	if(denominator == 0) // 광선벡터와 법선이 직교하면 표시하지 않음
		return FALSE;
	t = nom / denominator;
	if (t < rec->tmin || rec->tmax < t) // 카메라가 뒤에 있거나 너무 멀리 있으면 표시하지 않음.
            return (FALSE);
	rec->t = t;
	rec->p = ray_at(ray,t); // 교점 구하기
	rec->normal = pl->n;
    rec->albedo = pl_obj->albedo;
	set_face_normal(ray,rec);
	return TRUE;
}
