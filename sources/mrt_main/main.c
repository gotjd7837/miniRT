/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:38:41 by haekang           #+#    #+#             */
/*   Updated: 2024/01/10 07:45:19 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	main(int ac, char *av[])
{
	t_info	*info;

	if (ac != 2)
		mrt_print_err("Invalid arguments\n");
	info = mrt_parse(av[1]);
	mrt_render(info);
	return (0);
}
