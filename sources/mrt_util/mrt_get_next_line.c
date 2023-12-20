/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:07:31 by haekang           #+#    #+#             */
/*   Updated: 2023/12/20 20:08:49 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static char	*save_update(char *save, char *buf)
{
	char	*tmp;

	tmp = save;
	save = mrt_strjoin(save, buf);
	free(tmp);
	return (save);
}

static char	*get_next_save(char *save)
{
	char	*new_save;
	int		i;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	new_save = mrt_substr(save, i + 1, (mrt_strlen(save) - (i + 1)));
	free(save);
	return (new_save);
}

static char	*get_line(char *save)
{
	char	*line;
	int		i;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
		line = mrt_strdup(save);
	else
		line = mrt_substr(save, 0, (i + 1));
	return (line);
}

static char	*get_save(int fd, char *save)
{
	char	*buf;
	int		read_len;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	read_len = 1;
	while (read_len > 0)
	{
		read_len = read(fd, buf, BUFFER_SIZE);
		if (read_len < 0)
		{
			free(buf);
			free(save);
			return (NULL);
		}
		buf[read_len] = '\0';
		if (!save)
			save = mrt_strdup("");
		save = save_update(save, buf);
		if (mrt_strchr(save, '\n'))
			break ;
	}
	free(buf);
	return (save);
}

char	*mrt_get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = get_save(fd, save);
	if (!save)
		return (NULL);
	line = get_line(save);
	save = get_next_save(save);
	return (line);
}
