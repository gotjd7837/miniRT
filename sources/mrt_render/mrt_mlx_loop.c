/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_mlx_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:36:52 by haekang           #+#    #+#             */
/*   Updated: 2024/01/15 15:37:13 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	mrt_close(void)
{
	exit(0);
	return (0);
}

int	mrt_key_hook(int keycode, t_info *info)
{
	if (keycode == 53)
	{
		mlx_destroy_window(info->mlx, info->win);
		exit(0);
	}
	return (0);
}

void	mrt_mlx_loop(t_info *info)
{
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
	mlx_key_hook(info->win, mrt_key_hook, info);
	mlx_hook(info->win, 17, 0, mrt_close, NULL);
	mlx_loop(info->mlx);
}
