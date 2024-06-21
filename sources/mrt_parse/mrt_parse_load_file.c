/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_load_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeseong <haeseong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:20:18 by haekang           #+#    #+#             */
/*   Updated: 2024/06/20 10:47:39 by haeseong         ###   ########.fr       */
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
		line = mrt_get_next_line(fd); // 파일에서 한줄 읽기
		if (line == NULL)
			break ;
		if (!(mrt_strcmp(line, "\n"))) // 빈줄(개행 문자)일 경우
			continue ;
		line_info = mrt_split(line, ' '); // 공백을 기준으로 문자열 나누기
		if (line_info == NULL)
			mrt_print_err("Malloc failed\n");
		mrt_parse_insert_element(line_info, info); // line의 데이터 분석 및 info에 적재
		mrt_parse_free_line(line, line_info);
	}
	mrt_parse_check_element(info);
	close(fd);
	return (info);
}
