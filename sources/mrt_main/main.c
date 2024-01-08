/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:38:41 by haekang           #+#    #+#             */
/*   Updated: 2024/01/08 22:05:03 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

//ray 생성자(정규화 된 ray)
t_ray       ray(t_point orig, t_point dir)
{
    t_ray ray;

    ray.orig = orig;
    ray.dir = vunit(dir);
    return (ray);
}

//ray origin point 부터 방향벡터 ray dir * t 만큼 떨어진 점.
t_point    ray_at(t_ray *ray, double t)
{
    t_point at;

    at = vplus(ray->orig, vmult(ray->dir, t));
    return (at);
}

t_canvas    canvas(int  width, int height)
{
    t_canvas canvas;

    canvas.width = width;
    canvas.height = height;
    canvas.aspect_ratio = (double)width / (double)height;
    return (canvas);
}

t_camera    camera(t_canvas *canvas, t_point orig)
{
    t_camera    cam;
    double      focal_len;
    double      viewport_height;

    viewport_height = 2.0;
    focal_len = 1.0;
    cam.point = orig;
    cam.horizontal = vec3(viewport_height * canvas->aspect_ratio, 0, 0);
    cam.vertical = vec3(0, viewport_height, 0);
    // 왼쪽 아래 코너점 좌표, origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length)
    cam.left_bottom = vminus(vminus(vminus(cam.point, vdivide(cam.horizontal, 2)),
                                vdivide(cam.vertical, 2)), vec3(0, 0, focal_len));
    return (cam);
}

//primary_ray 생성자
t_ray       ray_primary(t_camera *cam, double u, double v)
{
    t_ray   ray;

    ray.orig = cam->point;
    // left_bottom + u * horizontal + v * vertical - origin 의 단위 벡터.
    ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom, vmult(cam->horizontal, u)), vmult(cam->vertical, v)), cam->point));
    return (ray);
}

t_object    *object(int type, void *element, t_color albedo)
{
    t_object    *new;

    if (!(new = (t_object *)malloc(sizeof(t_object))))
        return (NULL);
    new->type = type;
    new->element = element;
    new->next = NULL;
    new->albedo = albedo;
    return (new);
}

t_sphere    *sphere(t_point center, double radius)
{
    t_sphere *sp;

    if(!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
        return (NULL);
    sp->point = center;
    sp->radius = radius;
    sp->radius2 = radius * radius;
    return (sp);
}

t_light     *light_point(t_point light_origin, t_color light_color, double bright_ratio)
{
    t_light *light;

    if(!(light = (t_light *)malloc(sizeof(t_light))))
        return (NULL);
    light->point = light_origin;
    light->color = light_color;
    light->ratio = bright_ratio;
    return (light);
}











//생성자 모둠





void        oadd(t_object **list, t_object *new)
{
    t_object    *cur;

    if (*list == NULL)
    {
        *list = new;
        return ;
    }
    cur = *list;
    while (cur->next)
        cur = cur->next;
    cur->next = new;
}

t_object    *olast(t_object *list)
{
    if (list == NULL)
        return (NULL);
    while (list->next)
        list = list->next;
    return (list);
}

void    set_face_normal(t_ray *r, t_hit_record *rec)
{
    // 광선의 방향벡터와 교점의 법선벡터의 내적이 음수이면 광선은 앞면(객체의)에 hit 한 것이다
    rec->front_face = vdot(r->dir, rec->normal) < 0;
    // 광선의 앞면에 hit 면 그대로 아니면 법선을 반대로 뒤집는다. (항상 광선 방향벡터와 법선 벡터를 반대인 상태로 사용하기위해)
    rec->normal = (rec->front_face) ? rec->normal : vmult(rec->normal, -1);
}

int      hit_sphere(t_object *sp, t_ray *ray, t_hit_record *rec)
{
    t_point  oc;
    double  a;
   //b를 half_b로 변경
    double  half_b;
    double  c;
    double  discriminant; //판별식
   /* * * * 추가 * * * */
    double  sqrtd;
    double  root;
    t_sphere *sp2;
    
    sp2 = sp->element;
    oc = vminus(ray->orig, sp2->point);
    a = vlength2(ray->dir);
    half_b = vdot(oc, ray->dir);
    c = vlength2(oc) - sp2->radius2;
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
    rec->normal = vdivide(vminus(rec->p, sp2->point), sp2->radius); // 정규화된 법선 벡터.
    set_face_normal(ray, rec); // rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 int 값으로 저장.
    rec->albedo = sp->albedo;
    return (TRUE);
    /* * * * 수정 끝 * * * */
}

// hit_obj는 오브젝트 타입에 맞는 hit함수로 연결해주는 관문
int      hit_obj(t_object *world, t_ray *ray, t_hit_record *rec)
{
    int  hit_result;

    hit_result = FALSE;
    if (world->type == SP)
        hit_result = hit_sphere(world, ray, rec); //hit_sphere의 첫번째 인자도 t_sphere *에서 t_object *로 수정해주자.
    return (hit_result);
}

int      hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
    int          hit_anything;
    t_hit_record    temp_rec;

    temp_rec = *rec; // temp_rec의 tmin, tmax 값 초기화를 위해.
    hit_anything = FALSE;
    while(world)
    {
        if (hit_obj(world, ray, &temp_rec))
        {
            hit_anything = TRUE;
            temp_rec.tmax = temp_rec.t;
            *rec = temp_rec;
        }
        world = world->next;
    }
    return (hit_anything);
}

t_scene *scene_init(void)
{
    t_scene     *scene;
    t_object    *world;
    t_object    *lights;
    double      ka; // 8.4 에서 설명

    // malloc 할당 실패 시, 실습에서는 return NULL로 해두었지만, 적절한 에러 처리가 필요하다.
    if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
        return (NULL);
    scene->canvas = canvas(1920, 1080);
    scene->camera = camera(&scene->canvas, point3(0, 0, 0));
    world = object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0)); // world 에 구1 추가
    oadd(&world, object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0))); // world 에 구2 추가
    oadd(&world, object(SP, sphere(point3(0, -1000, 0), 995), color3(1, 1, 1))); // world 에 구3 추가
    scene->world = world;
    lights = object(LIGHT_POINT, light_point(point3(0, 20, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0)); // 더미 albedo
    scene->light = lights;
    ka = 0.1; // 8.4 에서 설명
    scene->ambient = vmult(color3(1,1,1), ka); // 8.4 에서 설명
    return (scene);
}

t_hit_record record_init(void)
{
    t_hit_record    record;

    record.tmin = EPSILON;
    record.tmax = INFINITY;
    return (record);
}

t_point          reflect(t_point v, t_point n)
{
    //v - 2 * dot(v, n) * n;
    return (vminus(v, vmult(n, vdot(v, n) * 2)));
}

int          in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
    t_hit_record rec;

    rec.tmin = 0;
    rec.tmax = light_len;
    if (hit(objs, &light_ray, &rec))
        return (TRUE);
    return (FALSE);
}

t_color        point_light_get(t_scene *scene, t_light *light)
{
    t_color    diffuse;
    t_point      light_dir;
    double      kd; // diffuse의 강도
    t_color    specular;
    t_point      view_dir;
    t_point      reflect_dir;
    double      spec;
    double      ksn;
    double      ks;
    double      brightness;
    double      light_len;
    t_ray       light_ray;

    light_dir = vminus(light->point, scene->rec.p);
    light_len = vlength(light_dir);
    light_ray = ray(vplus(scene->rec.p, vmult(scene->rec.normal, EPSILON)), light_dir);
    if (in_shadow(scene->world, light_ray, light_len))
        return (color3(0,0,0));
    light_dir = vunit(light_dir);
    
    light_dir = vunit(vminus(light->point, scene->rec.p)); //교점에서 출발하여 광원을 향하는 벡터(정규화 됨)
    // cosΘ는 Θ 값이 90도 일 때 0이고 Θ가 둔각이 되면 음수가 되므로 0.0보다 작은 경우는 0.0으로 대체한다.
    kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);// (교점에서 출발하여 광원을 향하는 벡터)와 (교점에서의 법선벡터)의 내적값.
    diffuse = vmult(light->color, kd);
    view_dir = vunit(vmult(scene->ray.dir, -1));
    reflect_dir = reflect(vmult(light_dir, -1), scene->rec.normal);
    ksn = 64; // shininess value
    ks = 0.5; // specular strength
    spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
    specular = vmult(vmult(light->color, ks), spec);
    brightness = light->ratio * LUMEN; // 기준 광속/광량을 정의한 매크로
    return (vmult(vplus(vplus(scene->ambient, diffuse), specular), brightness));
}

t_color        phong_lighting(t_scene *scene)
{
    t_color    light_color;
    t_object    *lights;

    light_color = color3(0, 0, 0); //광원이 하나도 없다면, 빛의 양은 (0, 0, 0)일 것이다.
    lights = scene->light;
    while (lights) //여러 광원에서 나오는 모든 빛에 대해 각각 diffuse, specular 값을 모두 구해줘야 한다
    {
        if(lights->type == LIGHT_POINT)
            light_color = vplus(light_color, point_light_get(scene, lights->element));
        lights = lights->next;
    }
    light_color = vplus(light_color, scene->ambient);
    return (vmin(vmult_(light_color, scene->rec.albedo), color3(1, 1, 1)));
    //모든 광원에 의한 빛의 양을 구한 후, 오브젝트의 반사율과 곱해준다. 그 값이 (1, 1, 1)을 넘으면 (1, 1, 1)을 반환한다.
}

//광선이 최종적으로 얻게된 픽셀의 색상 값을 리턴.
t_color    ray_color(t_scene *scene)
{
    double          t;

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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void    mrt_rendering(t_info *info)
{
    int         i;
    int         j;
    double      u;
    double      v;
    t_color    pixel_color;
    t_scene     *scene;
    int	color;
	double	r;
	double	g;
	double	b;

    scene = scene_init();
    j = scene->canvas.height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < scene->canvas.width)
        {
            u = (double)i / (scene->canvas.width - 1);
            v = (double)j / (scene->canvas.height - 1);
            scene->ray = ray_primary(&scene->camera, u, v);
            pixel_color = ray_color(scene);
            r = pixel_color.x;
            g = pixel_color.y;
            b = pixel_color.z;
            color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8) + ((int)(255.999 * b));
            my_mlx_pixel_put(&info->img, i, 1080 - j, color);
            ++i;
        }
        --j;
    }
    mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
	mlx_loop(info->mlx);
}

int main(void)
{
    t_info      *info;

    info = malloc(sizeof(t_info));
    info->mlx = mlx_init();
    info->win = mlx_new_window(info->mlx, 1920, 1080, "miniRT");
    info->img.img = mlx_new_image(info->mlx, 1920, 1080);
    info->img.addr = mlx_get_data_addr(info->img.img, &info->img.bits_per_pixel, &info->img.line_length, &info->img.endian);


    mrt_rendering(info);
	return (0);
}


