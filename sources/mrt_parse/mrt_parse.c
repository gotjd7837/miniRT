/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeseong <haeseong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:05:32 by haekang           #+#    #+#             */
/*   Updated: 2024/06/20 10:36:58 by haeseong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_info	*mrt_parse(char *file_name)
{
	t_info	*info;
	char	*file_path;

	info = mrt_parse_init_info(); // t_info 구조체 초기화
	file_path = mrt_parse_return_file_path(file_name); // file_name 에러처리 및 file_path 반환
	info = mrt_parse_load_file(file_path, info);
	return (info);
}
