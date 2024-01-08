#include "./includes/trace.h"

//ray 생성자(정규화 된 ray)
t_ray       ray(t_point3 orig, t_vec3 dir)
{
    t_ray ray;

    ray.orig = orig;
    ray.dir = vunit(dir);
    return (ray);
}

//ray origin point 부터 방향벡터 ray dir * t 만큼 떨어진 점.
t_point3    ray_at(t_ray *ray, double t)
{
    t_point3 at;

    at = vplus(ray->orig, vmult(ray->dir, t));
    return (at);
}

#include <stdio.h>
// primary_ray 생성자
// 왜 굳이 단위벡터를 구하나 했는데 viewport를 향해 쏘는 광선일 뿐이라 물체와의 거리는 알 수 없다...맞나?
t_ray       ray_primary(t_camera *cam, double u, double v)
{
    t_ray   ray;

    ray.orig = cam->orig;
    // printf("x: %lf y: %lf z: %lf\n",ray.orig.x,ray.orig.y,ray.orig.z);
    // left_bottom + u * horizontal + v * vertical - origin 의 단위 벡터.
    // horizontal, vertical (0~1)은 왜 곱하는 거지? - horizontal, vertical은 viewport의 가로. 세로 길이이기 때문에 비율에 쏴준다!
    ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom, vmult(cam->horizontal, u)), vmult(cam->vertical, v)), cam->orig));
    return (ray);
}

t_hit_record record_init(void)
{
    t_hit_record    record;

    record.tmin = EPSILON;
    record.tmax = INFINITY;
    return (record);
}

//광선이 최종적으로 얻게된 픽셀의 색상 값을 리턴.
/* * * * 수정 * * * */
t_color3    ray_color(t_scene *scene)
{
    double          t;
    // t_vec3          n;

    //광선이 구에 적중하면(광선과 구가 교점이 있고, 교점이 카메라 앞쪽이라면!)
    scene->rec = record_init();
    if (hit(scene->world, &scene->ray, &scene->rec))
        return (phong_lighting(scene)); //phong_lighting 함수는 8.4에서 설명한다. 이제 법선 벡터를 매핑해서 얻은 색이 아닌, 앞으로 작성할 phong_lighting 함수의 결과값을 반환한다!
    else
    {
        //ray의 방향벡터의 y 값을 기준으로 그라데이션을 주기 위한 계수.
        t = 0.5 * (scene->ray.dir.y + 1.0);
        // (1-t) * 흰색 + t * 하늘색
        return (vplus(vmult(color3(1, 1, 1), 1.0 - t), vmult(color3(0.5, 0.7, 1.0), t)));
    }
}
/* * * * 수정 끝 * * * */