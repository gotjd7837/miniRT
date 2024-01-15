/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:24:31 by haekang           #+#    #+#             */
/*   Updated: 2024/01/15 19:40:19 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_point	vunit(t_point vec)
{
	double	len;

	len = vlength(vec);
	if (len == 0)
		mrt_print_err("zero vector\n");
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}

t_point	vmin(t_point vec1, t_point vec2)
{
	if (vec1.x > vec2.x)
		vec1.x = vec2.x;
	if (vec1.y > vec2.y)
		vec1.y = vec2.y;
	if (vec1.z > vec2.z)
		vec1.z = vec2.z;
	return (vec1);
}
