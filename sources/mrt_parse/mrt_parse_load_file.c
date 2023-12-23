/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_load_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:20:18 by haekang           #+#    #+#             */
/*   Updated: 2023/12/23 20:31:39 by haekang          ###   ########.fr       */
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

void	mrt_parse_read_file(int fd, t_info *info)
{
	char	*line;
	char	**line_info;

	while (1)
	{
		line = mrt_get_next_line(fd);
		if (line == NULL)
			break ;
		line_info = mrt_split(line, " ");
		if (line_info == NULL)
			mrt_print_err("Malloc failed\n");
		else if (!(mrt_strcmp(line, "\n")))
			continue ;
		else
			mrt_parse_insert_element(line_info, info);
		mrt_parse_free_line(line, line_info);
	}
}

t_info	*mrt_parse_load_file(char *file_path)
{
	int		fd;
	t_info	*info;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		mrt_print_err("file open error\n");
	info = mrt_parse_init_info();
	mrt_parse_read_file(fd, info);
	/*반복문 돌면서 identifier에 따라서 각각의 함수를 호출
	그 함수에서는 이미 할당된 identifier인지 아닌지 구분을 해주고
	할당이 안되어있으면 파싱을 값을 할당을 해준다.
	모든 identifier가 들어오지 않으면 에러처리를 해줘야한다.
	*/
	close(fd);
	return (info);
}
