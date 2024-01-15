/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_load_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:20:18 by haekang           #+#    #+#             */
/*   Updated: 2024/01/15 16:41:05 by haekang          ###   ########.fr       */
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

void	mrt_parse_check_element(t_info *info)
{
	if (info->ambient == NULL)
		mrt_print_err("Ambient light is not exist\n");
	if (info->camera == NULL)
		mrt_print_err("Camera is not exist\n");
	if (info->light == NULL)
		mrt_print_err("Light is not exist\n");
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
	mrt_parse_check_element(info);
	close(fd);
	return (info);
}
