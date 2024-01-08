#include "./includes/structures.h"
#include "./includes/utils.h"
#include "./includes/trace.h"
#include <stdio.h>

t_bool      hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
    t_sphere    *sp;
    t_vec3  oc; //방향벡터로 나타낸 구의 중심.
    //a, b, c는 각각 t에 관한 2차 방정식의 계수
    double  a;
    double  half_b;
    double  c;
    double  discriminant; //판별식

    /* * * * 추가 * * * */
    double  sqrtd;
    double  root;

    sp = sp_obj->element;
    oc = vminus(ray->orig, sp->center);
    // printf("%lf, %lf, %lf\n",ray->orig.x,ray->orig.y,ray->orig.z);
    /* 수정 전
    a = vdot(ray->dir, ray->dir);
    b = 2.0 * vdot(oc, ray->dir);
    c = vdot(oc, oc) - sp->radius2;
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0) // 판별식이 0보다 작을 때 : 실근 없을 때,
        return (-1.0);
    else
        return ((-b - sqrt(discriminant)) / (2.0 * a)); // 두 근 중 작은 근
    수정 전 끝 */
    /* * * * 수정 * * * */
    a = vlength2(ray->dir);
    half_b = vdot(oc, ray->dir);
    c = vlength2(oc) - sp->radius2;
    discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
        return (FALSE);
    sqrtd = sqrt(discriminant);
    //두 실근(t) 중 tmin과 tmax 사이에 있는 근이 있는지 체크, 작은 근부터 체크.
    root = (-half_b - sqrtd) / a;
    if (root < rec->tmin || rec->tmax < root)
    {
        root = (-half_b + sqrtd) / a;
        if (root < rec->tmin || rec->tmax < root)
            return (FALSE);
    }
    rec->t = root;
    rec->p = ray_at(ray, root);
    rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius); // 정규화된 법선 벡터.
    rec->albedo = sp_obj->albedo;
    set_face_normal(ray, rec); // rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 t_bool 값으로 저장.
    return (TRUE);
    /* * * * 수정 끝 * * * */
}
