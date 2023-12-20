/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:33:22 by haekang           #+#    #+#             */
/*   Updated: 2023/12/20 15:01:44 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "mlx/mlx.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_info
{
	int	tmp;
}	t_info;

//mrt_parse
t_info	*mrt_parse(char *file_name);
char	*mrt_parse_return_file_path(char *file_name);
t_info	*mrt_parse_load_file(char *file_path);

//mrt_util
void	mrt_print_err(char *str);
char	*cub_strjoin(char *s1, char *s2);
int		mrt_strlen(char *str);
void	mrt_lst_add_back(t_list **lst, t_list *new);
t_list	*mrt_lst_new_node(void *content);

#endif