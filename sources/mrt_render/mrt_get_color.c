/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_get_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeseong <haeseong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:07:24 by haekang           #+#    #+#             */
/*   Updated: 2024/06/21 18:17:22 by haeseong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color	mrt_get_ambient(t_info *info, t_ray *ray)
{
	t_color	ambient;

	(void)ray;
	ambient = vmult(info->ambient->color, info->ambient->ratio);
	mrt_rescale_color(&ambient);
	return (ambient);
}

t_color	mrt_get_specular(t_info *info, t_ray *ray)
{
	t_light		*light;
	t_color		specular;
	t_point		light_vec;
	double		light_len;
	t_point		reflect_vec;

	specular = color3(0, 0, 0);
	light = info->light;
	light_vec = vminus(ray->hit_point, light->point);
	light_len = vlength(light_vec);
	light_vec = vunit(light_vec);
	if (mrt_shadow(info, ray, vmult(light_vec, -1), light_len))
		return (color3(0, 0, 0));
	reflect_vec = vminus(vmult(ray->obj_normal,
				2 * vdot(ray->obj_normal, light_vec)), light_vec);
	specular = vplus(specular, vmult(light->color,
				pow(fmax(vdot(reflect_vec, ray->vector), 0), 42)));
	mrt_rescale_color(&specular);
	return (specular);
}

t_color	mrt_get_diffuse(t_info *info, t_ray *ray)
{
	t_light	*light;
	t_color	diffuse;
	t_point	light_vec;
	double	light_len;

	diffuse = color3(0, 0, 0);
	light = info->light;
	light_vec = vminus(light->point, ray->hit_point);
	light_len = vlength(light_vec);
	light_vec = vunit(light_vec);
	if (mrt_shadow(info, ray, light_vec, light_len))
		return (color3(0, 0, 0));
	diffuse = vplus(diffuse, vmult(light->color,
				fmax(0, vdot(ray->obj_normal, light_vec))));
	mrt_rescale_color(&diffuse);
	return (diffuse);
}

/**
 * ray의 교점의 최종 color을 계산하여 반환합니다.
 * phong reflection model (난반사, 정반사, Ambient)을 적용합니다.
 * 반사된 빛(specular), 난반사 광(diffuse), Ambient 광을 계산하고, 이들을 합하여 최종적인 color를 계산합니다.
 * 색상의 범위를 조정하기 위해 mrt_rescale_color 함수가 호출되고, 색상이 오버플로우되지 않도록 mrt_color_overflow 함수가 호출됩니다.
 *
 * return: t_color
 */
t_color	mrt_get_color(t_info *info, t_ray *ray)
{
	t_color	light_color;

	light_color = color3(0, 0, 0);
	light_color = vplus(light_color, mrt_get_diffuse(info, ray)); // 난반사 plus
	light_color = vplus(light_color, mrt_get_ambient(info, ray)); // ambient plus
	mrt_rescale_color(&ray->color);
	light_color = vmult_(light_color, ray->color);
	light_color = vplus(light_color, mrt_get_specular(info, ray)); // 정반사 plus
	mrt_color_overflow(&light_color);
	return (light_color);
}
