/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_load_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:20:18 by haekang           #+#    #+#             */
/*   Updated: 2023/12/19 19:35:55 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_info	*mrt_parse_read_file(int fd)
{
	t_info	*info;
	char	*line;
	int		gnl;

	info = mrt_parse_init_info();
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		mrt_parse_read_line(info, line);
		free(line);
	}
	if (gnl == -1)
		mrt_print_err("Map file read error\n");
	mrt_parse_read_line(info, line);
	free(line);
	return (info);
}

t_info	*mrt_parse_load_file(char *file_path)
{
	int		fd;
	t_info	*info;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		mrt_print_err("file open error\n");
	info = mrt_parse_read_file(fd);
	close(fd);
	return (info);
}
