/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_get_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:07:24 by haekang           #+#    #+#             */
/*   Updated: 2024/01/15 13:45:50 by haekang          ###   ########.fr       */
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
	// if (mrt_shadow(info, ray, light_vec, light_len))
	// 	return (color3(0, 0, 0));
	reflect_vec = vminus(vmult(ray->obj_normal,
				2 * vdot(ray->obj_normal, light_vec)), light_vec);
	specular = vplus(specular, vmult(light->color,
				pow(fmax(vdot(reflect_vec, ray->vector), 0), 100)));
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

t_color	mrt_get_color(t_info *info, t_ray *ray)
{
	t_color	light_color;

	light_color = color3(0, 0, 0);
	light_color = vplus(light_color, mrt_get_diffuse(info, ray));
	light_color = vplus(light_color, mrt_get_specular(info, ray));
	light_color = vplus(light_color, mrt_get_ambient(info, ray));
	mrt_rescale_color(&ray->color);
	light_color = vmult_(light_color, ray->color);
	mrt_color_overflow(&light_color);
	return (light_color);
}
