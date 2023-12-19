/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_print_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:59:27 by haekang           #+#    #+#             */
/*   Updated: 2023/12/19 19:03:37 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	mrt_print_err(char *str)
{
	write(2, "\033[0;35mError\n", mrt_strlen("\033[0;35mError\n"));
	write(2, str, mrt_strlen(str));
	write(2, "\033[0;0m", mrt_strlen("\033[0;0m"));
	exit(1);
}
