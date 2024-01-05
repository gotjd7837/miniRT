/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_bit_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 19:05:27 by haekang           #+#    #+#             */
/*   Updated: 2024/01/05 16:30:21 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	mrt_bit_get(int bit_set, int bit_index)
{
	bit_set >>= bit_index;
	if ((bit_set & 1) == 1)
		mrt_print_err("Duplicated identifier\n");
	return (bit_set & 1);
}
