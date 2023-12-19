/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:05:32 by haekang           #+#    #+#             */
/*   Updated: 2023/12/19 19:28:35 by haekang          ###   ########.fr       */
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
