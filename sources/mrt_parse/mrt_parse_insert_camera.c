/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_insert_camera.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:14:52 by haekang           #+#    #+#             */
/*   Updated: 2024/01/04 20:54:02 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	mrt_parse_insert_camera_fov(char *line_info, double *fov)
{
	char	**fov_info;
	int		i;

	i = 0;
	fov_info = mrt_split(line_info, ',');
	if (fov_info == NULL)
		mrt_print_err("malloc failed\n");
	if (mrt_split_size(fov_info) != 1)
		mrt_print_err("Incorrect information for fov\n");
	*fov = mrt_atoi(line_info);
	while (i < 1)
		free(fov_info[i++]);
	free(fov_info);
}

void	mrt_parse_insert_camera(char **line_info, t_info *info, int *flags)
{
	t_camera	*camera;

	*flags = mrt_bit_increase(*flags, CAMERA_IDX);
	camera = (t_camera *)malloc(sizeof(t_camera));
	if (camera == NULL)
		mrt_print_err("malloc failed\n");
	if (line_info[1] == NULL)
		mrt_print_err("Do not input point for Camera\n");
	else
		mrt_parse_insert_point(line_info[1], &(camera->point));
	if (line_info[2] == NULL)
		mrt_print_err("Do not input vector for Camera\n");
	else
		mrt_parse_insert_vector(line_info[2], &(camera->vector));
	if (line_info[3] == NULL)
		mrt_print_err("Do not input fov for Camera\n");
	else
		mrt_parse_insert_camera_fov(line_info[3], &(camera->fov));
	if (line_info[4] == NULL)
		return ;
	else
		mrt_print_err("Incorrect information for Camera\n");
	info->camera = camera;
}
