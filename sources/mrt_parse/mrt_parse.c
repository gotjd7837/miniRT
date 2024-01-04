/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:05:32 by haekang           #+#    #+#             */
/*   Updated: 2024/01/04 21:39:24 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_info	*mrt_parse(char *file_name)
{
	t_info	*info;
	char	*file_path;

	file_path = mrt_parse_return_file_path(file_name);
	info = mrt_parse_load_file(file_path);
	return (info);
}
//모든 identifier를 파싱했는지 확인해주는 기능 구현필요