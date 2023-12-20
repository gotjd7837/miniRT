/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 00:41:28 by haekang           #+#    #+#             */
/*   Updated: 2023/12/20 15:00:00 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_list	*mrt_lst_new_node(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	if (content == NULL)
	{
		new_node->content = NULL;
		new_node->next = NULL;
	}
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
