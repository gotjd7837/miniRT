/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_init_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 17:17:09 by haekang           #+#    #+#             */
/*   Updated: 2023/12/23 17:17:36 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_info	*mrt_parse_init_info(t_info *info)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (info == NULL)
		mrt_print_err("Malloc failed\n");
	info->mlx = mlx_init();
	info->sphere = NULL;
	info->plane = NULL;
	info->cylinder = NULL;
	return (info);
}
