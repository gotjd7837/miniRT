#include "./includes/trace.h"
#include <stdio.h>

t_color3        phong_lighting(t_scene *scene)
{
    t_color3    light_color;
    t_object    *lights;

    light_color = color3(0, 0, 0); //광원이 하나도 없다면, 빛의 양은 (0, 0, 0)일 것이다.
    lights = scene->light;
    while (lights) //여러 광원에서 나오는 모든 빛에 대해 각각 diffuse, specular 값을 모두 구해줘야 한다
    {
        if (lights->type == LIGHT_POINT) // 이거 필요함?
            light_color = vplus(light_color, point_light_get(scene, lights->element));
        lights = lights->next;
    }
    light_color = vplus(light_color, scene->ambient); // while문 없으면 (0+ka, 0+ka, 0+ka)
    // printf("%lf %lf %lf\n",light_color.x,light_color.y,light_color.z);
    return (vmin(vmult_(light_color, scene->rec.albedo), color3(1, 1, 1)));
    //모든 광원에 의한 빛의 양을 구한 후, 오브젝트의 반사율과 곱해준다. 그 값이 (1, 1, 1)을 넘으면 (1, 1, 1)을 반환한다.
}

t_vec3          reflect(t_vec3 v, t_vec3 n)
{
    //v - 2 * dot(v, n) * n;
    return (vminus(v, vmult(n, vdot(v, n) * 2)));
}

t_color3        point_light_get(t_scene *scene, t_light *light)
{
    t_color3    diffuse;
    t_vec3      light_dir;
    double      kd; // diffuse의 강도 계수. cosΘ 값
    t_color3    specular;
    double      light_len;
    t_ray       light_ray;
    t_vec3      view_dir;
    t_vec3      reflect_dir;
    double      spec;
    double      ksn;
    double      ks;
    double      brightness;

    light_dir = vminus(light->origin, scene->rec.p); //교점에서 출발하여 광원을 향하는 벡터
    light_len = vlength(light_dir);
    light_ray = ray(vplus(scene->rec.p, vmult(scene->rec.normal, EPSILON)), light_dir); //vmult로 크기를 엄청 줄이고 vplus로 살짝 바깥쪽으로 좌표조정을 해주는 듯하다.
    if (in_shadow(scene->world, light_ray, light_len))
        return (color3(0,0,0));
    light_dir = vunit(light_dir); //교점에서 출발하여 광원을 향하는 벡터(정규화 됨)
    // cosΘ는 Θ 값이 90도 일 때 0이고 Θ가 둔각이 되면 음수가 되므로 0.0보다 작은 경우는 0.0으로 대체한다.
    kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);// (교점에서 출발하여 광원을 향하는 벡터)와 (교점에서의 법선벡터)의 내적값.
                                                       // cosΘ 값으로 각을 구해서 빛을 얼마나 받는지 계산. 두 벡터의 크기가 1이기 때문에 내적하면 cosΘ 값만 나온다.
    // printf("%lf\n",vdot(scene->rec.normal, light_dir));
    diffuse = vmult(light->light_color, kd); // 해당 점에 도달한 diffuse 광량.
    view_dir = vunit(vmult(scene->ray.dir, -1)); // 교점에서 카메라 원점을 향하는 벡터
    reflect_dir = reflect(vmult(light_dir, -1), scene->rec.normal); // 반사광 벡터
    ksn = 64; // 물체의 반짝거리는 정도를 나타내는 값인 shininess value. ksn 값이 커질 수록 물체의 하이라이팅 범위가 줄어든다
    ks = 0.5; // specular strength. specular 강도
    spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn); //cosΘ ^ ksn 왜 이렇게 계산하는지는 모름;;
    specular = vmult(vmult(light->light_color, ks), spec);
    brightness = light->bright_ratio * LUMEN; // 기준 광속/광량을 정의한 매크로
    return (vmult(vplus(vplus(scene->ambient, diffuse), specular), brightness));
}

t_bool          in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
    t_hit_record rec;

    rec.tmin = 0;
    rec.tmax = light_len;
    if (hit(objs, &light_ray, &rec))
        return (TRUE);
    return (FALSE);
}
