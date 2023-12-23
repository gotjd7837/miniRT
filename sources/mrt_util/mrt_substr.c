/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_substr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:02:29 by haekang           #+#    #+#             */
/*   Updated: 2023/12/23 16:52:08 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

char	*mrt_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*arr;

	i = 0;
	if (mrt_strlen(s) < len + start)
		len = mrt_strlen(s) - start;
	if (mrt_strlen(s) > start)
	{
		arr = (char *)malloc(sizeof(char) * (len + 1));
		if (arr == NULL)
			return (NULL);
		while (s[start + i] && i < len)
		{
			arr[i] = s[start + i];
			i++;
		}
	}
	else
	{
		arr = (char *)malloc(sizeof(char));
		if (arr == NULL)
			return (NULL);
	}
	arr[i] = '\0';
	return (arr);
}
