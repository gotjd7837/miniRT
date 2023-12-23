/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_bit_increase.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 19:06:12 by haekang           #+#    #+#             */
/*   Updated: 2023/12/23 20:21:29 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	mrt_bit_increase(int bit_set, int bit_index)
{
	int	mask;

	mask = 1;
	mask <<= bit_index;
	return (bit_set | mask);
}
