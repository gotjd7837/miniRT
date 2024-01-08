#include <stdio.h>
/* * * * 추가 * * * */
#include "./includes/structures.h"
#include "./includes/utils.h"
#include "./includes/print.h"
/* * * * 추가 끝 * * * */

/* * * * 추가 * * * */
#include "./includes/scene.h"
#include "./includes/trace.h"
#include "./includes/mlx/mlx.h"

t_scene *scene_init(void)
{
    t_scene     *scene;
    t_object    *world;
    t_object    *lights;
    double      ka; // diffuse의 강도 계수

    // malloc 할당 실패 시, 실습에서는 return NULL로 해두었지만, 적절한 에러 처리가 필요하다.
    if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
        return (NULL);
    scene->canvas = canvas(1920, 1080);
    scene->camera = camera(&scene->canvas, point3(0, 0, 0));
	world = object(CY, cylinder(point3(0.0, 0.0, -2), vec3(0.5,0.5,0), 0.2, 0.42), color3(0, 0.3, 0.3)); // world에 원기둥1 추가
    // oadd(&world, object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0))); // world 에 구1 추가
    // oadd(&world, object(SP, sphere(point3(0, -1000, 0), 995), color3(1, 1, 1))); // world 에 구3 추가
    // oadd(&world, object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0))); // world 에 구2 추가
    oadd(&world, object(PL, plane(point3(0, 0, -10), vec3(0.5,0.5,0.2)), color3(0.3, 0.3, 0)));

    scene->world = world;
    lights = object(LIGHT_POINT, light_point(point3(0, 5, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0)); // 더미 albedo
    scene->light = lights;
    ka = 0.1; //ambient lighting의 강도(ambient strength) 계수
    scene->ambient = vmult(color3(1,1,1), ka); // 8.4 에서 설명
    return (scene);
}


// mlx 구조체
typedef struct	s_vars {
	void		*mlx;
	void		*win;
}				t_vars;

// image data 구조체
typedef struct s_data
{
	void 	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

//함수 선언부
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
int prtimage();
int exit_hook();
int	key_hook(int keycode, t_vars *vars);

// main function!
int main()
{
	prtimage();
	return (0);
}

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int prtimage()
{
	int		color;
	t_vars vars;
	t_data image;
	int         i;
    int         j;
	double      u;
    double      v;
    t_color3    pixel_color;
    t_scene     *scene;

    scene = scene_init();

	int img_width = scene->canvas.width;
	int img_height = scene->canvas.height;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, img_width, img_height, "Hellow World!");
	image.img = mlx_new_image(vars.mlx, img_width, img_height); // 이미지 객체 생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian); // 이미지 주소 할당

    j = scene->canvas.height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < scene->canvas.width)
        {
			u = (double)i / (scene->canvas.width - 1);
            v = (double)j / (scene->canvas.height - 1);
			scene->ray = ray_primary(&scene->camera, u, v); //광원의 원점과 광선의 단위벡터 설정.
            pixel_color = ray_color(scene);

			double r = pixel_color.x;
			double g = pixel_color.y;
			double b = pixel_color.z;
			// printf("%lf %lf %lf\n",pixel_color.x,pixel_color.y,pixel_color.z );
			color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8) + ((int)(255.999 * b));
			my_mlx_pixel_put(&image, i, 1080-j, color);
			++i;
        }
    	--j;
    }
	//////////////////////////////////////////////// 가운데 점
	double r = 1;
	double g = 1;
	double b = 1;
	color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8) + ((int)(255.999 * b));
	my_mlx_pixel_put(&image, 960, 540, color);
	/////////////////////////////////////////////////
	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars); // esc key press event
	mlx_hook(vars.win, 17, 0, exit_hook, 0); // close button press event
	mlx_loop(vars.mlx);
	return (0);
}


// esc key press event
int	key_hook(int keycode, t_vars *vars)
{
	if(keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

// close button press event
int exit_hook()
{
	exit(0);
}


// int	main(void)
// {
//     int         i;
//     int         j;
//     double      u;
//     double      v;
//     t_color3    pixel_color;
//     /* * * * 수정 * * * */
//     t_scene     *scene;

//     scene = scene_init();
//     // 랜더링
//     // P3 는 색상값이 아스키코드라는 뜻, 그리고 다음 줄은 캔버스의 가로, 세로 픽셀 수, 마지막은 사용할 색상값
//     /* * * * 수정 * * * */
//     printf("P3\n%d %d\n255\n", scene->canvas.width, scene->canvas.height);
//     j = scene->canvas.height - 1;
//     while (j >= 0)
//     {
//         i = 0;
//         while (i < scene->canvas.width)
//         {
//             u = (double)i / (scene->canvas.width - 1);
//             v = (double)j / (scene->canvas.height - 1);
//             //ray from camera origin to pixel
//             scene->ray = ray_primary(&scene->camera, u, v); //광원의 원점과 광선의 단위벡터 설정.
//             /* * * * 수정 * * * */
//             pixel_color = ray_color(scene); // ray color에서 t(크기, 방향(+,-)) 정해짐.
//             // ray_color함수의 인자도 ray, world를 모두 담고 있는 scene으로 바꿨다.
//             /* * * * 수정 끝 * * * */
//             write_color(pixel_color);
//             ++i;
//         }
//     --j;
//     }
//     return (0);
// }
