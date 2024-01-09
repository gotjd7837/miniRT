/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_load_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:20:18 by haekang           #+#    #+#             */
/*   Updated: 2024/01/10 03:56:27 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	mrt_parse_free_line(char *line, char **line_info)
{
	int	i;

	i = 0;
	free(line);
	while (line_info[i])
		free(line_info[i++]);
	free(line_info);
	return ;
}

void	mrt_parse_insert_element(char **line_info, t_info *info)
{
	static int	flags;

	if (!mrt_strcmp(line_info[0], "A") && !mrt_bit_get(flags, AMBIENT_IDX))
		mrt_parse_insert_ambient(line_info, info, &flags);
	else if (!mrt_strcmp(line_info[0], "C") && !mrt_bit_get(flags, CAMERA_IDX))
		mrt_parse_insert_camera(line_info, info, &flags);
	else if (!mrt_strcmp(line_info[0], "L") && !mrt_bit_get(flags, LIGHT_IDX))
		mrt_parse_insert_light(line_info, info, &flags);
	else if (!(mrt_strcmp(line_info[0], "sp")))
		mrt_parse_insert_sphere(line_info, info);
	else if (!(mrt_strcmp(line_info[0], "pl")))
		mrt_parse_insert_plane(line_info, info);
	else if (!(mrt_strcmp(line_info[0], "cy")))
		mrt_parse_insert_cylinder(line_info, info);
	else
		mrt_print_err("Invalid identifier\n");
}

void	*mrt_parse_load_file(char *file_path, t_info *info)
{
	char	*line;
	char	**line_info;
	int		fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		mrt_print_err("file open error\n");
	while (1)
	{
		line = mrt_get_next_line(fd);
		if (line == NULL)
			break ;
		if (!(mrt_strcmp(line, "\n")))
			continue ;
		line_info = mrt_split(line, ' ');
		if (line_info == NULL)
			mrt_print_err("Malloc failed\n");
		mrt_parse_insert_element(line_info, info);
		mrt_parse_free_line(line, line_info);
	}
	close(fd);
	return (info);
}
