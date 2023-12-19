/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_return_file_path.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:10:20 by haekang           #+#    #+#             */
/*   Updated: 2023/12/19 19:29:12 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	mrt_parse_check_filename(char *file_name)
{
	int	len;

	len = mrt_strlen(file_name);
	if (len <= 3)
		mrt_print_err("Invalid file name\n");
	if (file_name[len - 1] != 't' || file_name[len - 2] != 'r'
		|| file_name[len - 3] != '.')
		mrt_print_err("Invalid file name\n");
}

char	*mrt_parse_return_file_path(char *file_name)
{
	char	*file_path;

	mrt_parse_check_filename(file_name);
	file_path = mrt_strjoin("./argfiles/", file_name);
	if (file_path == NULL)
		mrt_print_err("Malloc failed\n");
	return (file_path);
}
