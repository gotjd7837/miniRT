/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeseong <haeseong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:38:41 by haekang           #+#    #+#             */
/*   Updated: 2024/01/02 16:13:14 by haeseong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	main(int ac, char *av[])
{
	t_info	*info;

	if (ac != 2)
		mrt_print_err("Invalid arguments\n");
	info = mrt_parse(av[1]);
}
