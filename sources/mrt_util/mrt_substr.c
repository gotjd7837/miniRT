/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_substr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:02:29 by haekang           #+#    #+#             */
/*   Updated: 2024/01/04 20:46:12 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

char	*mrt_substr(char *s, int start, int len)
{
	int		i;
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
