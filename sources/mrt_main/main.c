/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:38:41 by haekang           #+#    #+#             */
/*   Updated: 2024/01/06 20:32:57 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"


#include "stdio.h"
#include "stdlib.h"
#include "math.h"

typedef struct s_vec3 t_vec3;
typedef struct s_vec3 t_point3;
typedef struct s_vec3 t_color3;
typedef int             t_bool;
typedef int             t_object_type;
# define SP 0
# define LIGHT_POINT 1
# define EPSILON 1e-6 // 0.000001
# define FALSE 0
# define TRUE 1
# define LUMEN 3  // 이 값을 조절하여 장면의 밝기를 조절할 수 있다.

struct s_vec3
{
    double x;
    double y;
    double z;
};

typedef struct  s_ray
{
    t_point3    orig;
    t_vec3      dir;
}   t_ray;


typedef struct  s_canvas
{
    int     width; //canvas width
    int     height; //canvas height;
    double  aspect_ratio; //종횡비
}           t_canvas;

typedef struct  s_camera_2
{
    t_point3    orig;  // 카메라 원점(위치)
    double      viewport_h; // 뷰포트 세로길이
    double      viewport_w; // 뷰포트 가로길이
    t_vec3      horizontal; // 수평길이 벡터
    t_vec3      vertical; // 수직길이 벡터
    double      focal_len; // focal length
    t_point3    left_bottom; // 왼쪽 아래 코너점
}   t_camera_2;

typedef struct  s_sphere_2
{
   t_point3    center;
    double      radius;
    double      radius2;
} t_sphere_2;

typedef struct      s_light_2
{
    t_point3    origin;
    t_color3    light_color;
    double      bright_ratio;
} t_light_2;

typedef struct s_hit_record
{
    t_point3    p;
    t_vec3      normal;
    double      tmin;
    double      tmax;
    double      t;
    t_bool      front_face;
    t_color3    albedo;
} t_hit_record;

typedef struct                      s_object
{
    t_object_type   type;
    void            *element;
    void            *next;
    t_color3        albedo;
} t_object;

typedef struct  s_scene
{
    t_canvas        canvas;
    t_camera_2        camera;
    t_object        *world;
    t_object        *light;
    t_color3         ambient; // 8.4에서 설명할 요소
    t_ray           ray;
    t_hit_record    rec;
} t_scene;



//구조체 모둠






//벡터3 생성자
t_vec3      vec3(double x, double y, double z)
{
    t_vec3 vec;

    vec.x = x;
    vec.y = y;
    vec.z = z;
    return (vec);
}

//포인트3 생성자
t_point3    point3(double x, double y, double z)
{
    t_point3 point;

    point.x = x;
    point.y = y;
    point.z = z;
    return (point);
}

//색상3 생성자
t_color3    color3(double r, double g, double b)
{
    t_color3 color;

    color.x = r;
    color.y = g;
    color.z = b;
    return (color);
}

// 벡터 값 설정
void        vset(t_vec3 *vec, double x, double y, double z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

// 벡터 길이 제곱
double      vlength2(t_vec3 vec)
{
    return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

// 벡터 길이
double      vlength(t_vec3 vec)
{
    return (sqrt(vlength2(vec)));
}

// 벡터합
t_vec3      vplus(t_vec3 vec, t_vec3 vec2)
{
    vec.x += vec2.x;
    vec.y += vec2.y;
    vec.z += vec2.z;
    return (vec);
}

// 벡터합2
t_vec3      vplus_(t_vec3 vec, double x, double y, double z)
{
    vec.x += x;
    vec.y += y;
    vec.z += z;
    return (vec);
}

// 벡터차
t_vec3      vminus(t_vec3 vec, t_vec3 vec2)
{
    vec.x -= vec2.x;
    vec.y -= vec2.y;
    vec.z -= vec2.z;
    return (vec);
}

t_vec3      vminus_(t_vec3 vec, double x, double y, double z)
{
    vec.x -= x;
    vec.y -= y;
    vec.z -= z;
    return (vec);
}

// 벡터 * 스칼라 곱연산
t_vec3      vmult(t_vec3 vec, double t)
{
    vec.x *= t;
    vec.y *= t;
    vec.z *= t;
    return (vec);
}

// 벡터 축 값끼리 곱연산
t_vec3      vmult_(t_vec3 vec, t_vec3 vec2)
{
    vec.x *= vec2.x;
    vec.y *= vec2.y;
    vec.z *= vec2.z;
    return (vec);
}

// 벡터 스칼라 나누기
t_vec3      vdivide(t_vec3 vec, double t)
{
    vec.x *= 1 / t;
    vec.y *= 1 / t;
    vec.z *= 1 / t;

    return vec;
}

// 벡터 내적
double      vdot(t_vec3 vec, t_vec3 vec2)
{
    return (vec.x * vec2.x + vec.y * vec2.y + vec.z * vec2.z);
}

// 벡터 외적
t_vec3      vcross(t_vec3 vec, t_vec3 vec2)
{
    t_vec3 new;

    new.x = vec.y * vec2.z - vec.z * vec2.y;
    new.y = vec.z * vec2.x - vec.x * vec2.z;
    new.z = vec.x * vec2.y - vec.y * vec2.x;
    return (new);
}

// 단위 벡터
t_vec3      vunit(t_vec3 vec)
{
    double len = vlength(vec);
    if (len == 0)
    {
        printf("Error\n:Devider is 0");
        exit(0);
    }
    vec.x /= len;
    vec.y /= len;
    vec.z /= len;
    return (vec);
}

// 두 벡터의 원소를 비교하여 작은 값들만 반환
t_vec3  vmin(t_vec3 vec1, t_vec3 vec2)
{
    if (vec1.x > vec2.x)
        vec1.x = vec2.x;
    if (vec1.y > vec2.y)
        vec1.y = vec2.y;
    if (vec1.z > vec2.z)
        vec1.z = vec2.z;
    return (vec1);
}



//벡터 연산 모둠













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

t_canvas    canvas(int  width, int height)
{
    t_canvas canvas;

    canvas.width = width;
    canvas.height = height;
    canvas.aspect_ratio = (double)width / (double)height;
    return (canvas);
}

t_camera_2    camera_2(t_canvas *canvas, t_point3 orig)
{
    t_camera_2    cam;
    double      focal_len;
    double      viewport_height;

    viewport_height = 2.0;
    focal_len = 1.0;
    cam.orig = orig;
    cam.viewport_h = viewport_height;
    cam.viewport_w = viewport_height * canvas->aspect_ratio;
    cam.focal_len = focal_len;
    cam.horizontal = vec3(cam.viewport_w, 0, 0);
    cam.vertical = vec3(0, cam.viewport_h, 0);
    // 왼쪽 아래 코너점 좌표, origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length)
    cam.left_bottom = vminus(vminus(vminus(cam.orig, vdivide(cam.horizontal, 2)),
                                vdivide(cam.vertical, 2)), vec3(0, 0, focal_len));
    return (cam);
}

//primary_ray 생성자
t_ray       ray_primary(t_camera_2 *cam, double u, double v)
{
    t_ray   ray;

    ray.orig = cam->orig;
    // left_bottom + u * horizontal + v * vertical - origin 의 단위 벡터.
    ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom, vmult(cam->horizontal, u)), vmult(cam->vertical, v)), cam->orig));
    return (ray);
}

t_object    *object(t_object_type type, void *element, t_color3 albedo)
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

t_sphere_2    *sphere(t_point3 center, double radius)
{
    t_sphere_2 *sp;

    if(!(sp = (t_sphere_2 *)malloc(sizeof(t_sphere_2))))
        return (NULL);
    sp->center = center;
    sp->radius = radius;
    sp->radius2 = radius * radius;
    return (sp);
}

t_light_2     *light_point(t_point3 light_origin, t_color3 light_color, double bright_ratio)
{
    t_light_2 *light;

    if(!(light = (t_light_2 *)malloc(sizeof(t_light_2))))
        return (NULL);
    light->origin = light_origin;
    light->light_color = light_color;
    light->bright_ratio = bright_ratio;
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

t_bool      hit_sphere(t_object *sp, t_ray *ray, t_hit_record *rec)
{
    t_vec3  oc;
    double  a;
   //b를 half_b로 변경
    double  half_b;
    double  c;
    double  discriminant; //판별식
   /* * * * 추가 * * * */
    double  sqrtd;
    double  root;
    t_sphere_2 *sp2;
    
    sp2 = sp->element;
    oc = vminus(ray->orig, sp2->center);
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
    rec->normal = vdivide(vminus(rec->p, sp2->center), sp2->radius); // 정규화된 법선 벡터.
    set_face_normal(ray, rec); // rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 t_bool 값으로 저장.
    rec->albedo = sp->albedo;
    return (TRUE);
    /* * * * 수정 끝 * * * */
}

// hit_obj는 오브젝트 타입에 맞는 hit함수로 연결해주는 관문
t_bool      hit_obj(t_object *world, t_ray *ray, t_hit_record *rec)
{
    t_bool  hit_result;

    hit_result = FALSE;
    if (world->type == SP)
        hit_result = hit_sphere(world, ray, rec); //hit_sphere의 첫번째 인자도 t_sphere *에서 t_object *로 수정해주자.
    return (hit_result);
}

t_bool      hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
    t_bool          hit_anything;
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

// [0,1] 로 되어있는 rgb 값을 각각 [0,255]에 맵핑 해서 출력.
void    write_color(t_color3 pixel_color)
{
    printf("%d %d %d\n", (int)(255.999 * pixel_color.x),
                        (int)(255.999 * pixel_color.y),
                        (int)(255.999 * pixel_color.z));
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
    scene->canvas = canvas(400, 300);
    scene->camera = camera_2(&scene->canvas, point3(0, 0, 0));
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

t_vec3          reflect(t_vec3 v, t_vec3 n)
{
    //v - 2 * dot(v, n) * n;
    return (vminus(v, vmult(n, vdot(v, n) * 2)));
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

t_color3        point_light_get(t_scene *scene, t_light_2 *light)
{
    t_color3    diffuse;
    t_vec3      light_dir;
    double      kd; // diffuse의 강도
     /* * * * 추가 * * * */
    t_color3    specular;
    t_vec3      view_dir;
    t_vec3      reflect_dir;
    double      spec;
    double      ksn;
    double      ks;
    /* * * * 추가 끝 * * * */
    double      brightness;
    /* * * * 추가 * * * */
    double      light_len;
    t_ray       light_ray;
    /* * * * 추가 끝 * * * */

    /* * * * 수정 * * * */
    light_dir = vminus(light->origin, scene->rec.p);
    light_len = vlength(light_dir);
    light_ray = ray(vplus(scene->rec.p, vmult(scene->rec.normal, EPSILON)), light_dir);
    if (in_shadow(scene->world, light_ray, light_len))
        return (color3(0,0,0));
    light_dir = vunit(light_dir);
    /* * * * 수정 끝 * * * */
    
    light_dir = vunit(vminus(light->origin, scene->rec.p)); //교점에서 출발하여 광원을 향하는 벡터(정규화 됨)
    // cosΘ는 Θ 값이 90도 일 때 0이고 Θ가 둔각이 되면 음수가 되므로 0.0보다 작은 경우는 0.0으로 대체한다.
    kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);// (교점에서 출발하여 광원을 향하는 벡터)와 (교점에서의 법선벡터)의 내적값.
    diffuse = vmult(light->light_color, kd);
    /* * * * 추가 * * * */
    view_dir = vunit(vmult(scene->ray.dir, -1));
    reflect_dir = reflect(vmult(light_dir, -1), scene->rec.normal);
    ksn = 64; // shininess value
    ks = 0.5; // specular strength
    spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
    specular = vmult(vmult(light->light_color, ks), spec);
    brightness = light->bright_ratio * LUMEN; // 기준 광속/광량을 정의한 매크로
    return (vmult(vplus(vplus(scene->ambient, diffuse), specular), brightness));
    /* * * * 추가 끝 * * * */

    return (diffuse);
}

t_color3        phong_lighting(t_scene *scene)
{
    t_color3    light_color;
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
t_color3    ray_color(t_scene *scene)
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

int main(void)
{
    int         i;
    int         j;
    /* * * * 추가 * * * */
    double      u;
    double      v;
    /* * * * 추가 끝 * * * */

    t_color3    pixel_color;
    /* * * * 수정 * * * */
    // t_sphere_2    sp;
    t_scene     *scene;

    scene = scene_init();

    // 랜더링
    // P3 는 색상값이 아스키코드라는 뜻, 그리고 다음 줄은 캔버스의 가로, 세로 픽셀 수, 마지막은 사용할 색상값
    /* * * * 수정 * * * */
    printf("P3\n%d %d\n255\n", scene->canvas.width, scene->canvas.height);
    j = scene->canvas.height - 1;
    /* * * * 수정 끝 * * * */
    while (j >= 0)
    {
        i = 0;
        /* * * * 수정 * * * */
        while (i < scene->canvas.width)
        {
            u = (double)i / (scene->canvas.width - 1);
            v = (double)j / (scene->canvas.width - 1);
            //ray from camera_2 origin to pixel
            scene->ray = ray_primary(&scene->camera, u, v);
            pixel_color = ray_color(scene);
            // ray_color함수의 인자도 ray, world를 모두 담고 있는 scene으로 바꿨다.
        /* * * * 수정 끝 * * * */
            write_color(pixel_color);
            ++i;
        }
        --j;
    }
}

