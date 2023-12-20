/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_load_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:20:18 by haekang           #+#    #+#             */
/*   Updated: 2023/12/20 20:31:09 by haekang          ###   ########.fr       */
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
