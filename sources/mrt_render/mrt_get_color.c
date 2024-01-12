/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_get_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:07:24 by haekang           #+#    #+#             */
/*   Updated: 2024/01/12 21:50:39 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// int	mrt_is_shadow(t_info *info, t_ray *ray, t_point light_vec,
// 		double light_len)
// {
// 	t_ray	shadow_ray;
// 	t_object	*obj;

// 	shadow_ray.point = ray->hit_point;
// 	shadow_ray.vector = light_vec;
// 	shadow_ray.t = light_len;
// 	obj = mrt_get_closest_object(info, &shadow_ray);
// 	if (obj != NULL)
// 		return (1);
// 	return (0);
// }

void	mrt_color_overflow(t_color *color)
{
	if (color->x > 255)
		color->x = 255;
	if (color->y > 255)
		color->y = 255;
	if (color->z > 255)
		color->z = 255;
}

t_color	mrt_get_ambient(t_info *info, t_ray *ray)
{
	t_color	ambient;

	(void)ray;
	info->ambient->color.x /= 255;
	info->ambient->color.y /= 255;
	info->ambient->color.z /= 255;
	ambient = vmult(info->ambient->color, info->ambient->ratio);
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
	// if (mrt_is_shadow(info, ray, light_vec, light_len))
	// 	return (specular);
	reflect_vec = vminus(vmult(ray->obj_normal,
				2 * vdot(ray->obj_normal, light_vec)), light_vec);
	specular = vplus(specular, vmult(light->color,
				pow(fmax(vdot(reflect_vec, ray->vector), 0), 100)));
	return (specular);
}

t_color	mrt_get_diffuse(t_info *info, t_ray *ray)
{
	t_light		*light;
	t_color		diffuse;
	t_point		light_vec;
	double		light_len;

	diffuse = color3(0, 0, 0);
	light = info->light;
	light_vec = vminus(light->point, ray->hit_point);
	light_len = vlength(light_vec);
	light_vec = vunit(light_vec);
	// if (mrt_is_shadow(info, ray, light_vec, light_len))
	// 	return (diffuse);
	diffuse = vplus(diffuse, vmult(light->color,
				fmax(0, vdot(ray->obj_normal, light_vec))));
return (diffuse);
}

t_color	mrt_get_color(t_info *info, t_ray *ray)
{
	t_color	light_color;

	light_color = color3(0, 0, 0);
	light_color = vplus(light_color, mrt_get_diffuse(info, ray));
	light_color = vplus(light_color, mrt_get_specular(info, ray));
	light_color = vplus(light_color, mrt_get_ambient(info, ray));
	light_color = vplus(light_color, ray->color);
	mrt_color_overflow(&light_color);
	return (light_color);
}
