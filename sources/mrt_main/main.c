/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeseong <haeseong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:38:41 by haekang           #+#    #+#             */
/*   Updated: 2024/06/20 10:29:54 by haeseong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	main(int ac, char *av[])
{
	t_info	*info;

	if (ac != 2)
		mrt_print_err("Invalid arguments\n");
	info = mrt_parse(av[1]); // input file에서 데이터를 파싱해 info 구조체 반환
	mrt_render(info);
	return (0);
}
