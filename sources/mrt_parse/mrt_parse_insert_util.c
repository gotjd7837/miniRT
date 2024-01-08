/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_insert_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:46:33 by haeseong          #+#    #+#             */
/*   Updated: 2024/01/08 20:14:33 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	mrt_parse_insert_diameter(char *line_info, double *diameter)
{
	char	**diameter_info;
	int		i;

	i = 0;
	diameter_info = mrt_split(line_info, ',');
	if (diameter_info == NULL)
		mrt_print_err("malloc failed\n");
	if (mrt_split_size(diameter_info) != 1)
		mrt_print_err("Incorrect information for diameter\n");
	*diameter = mrt_atod(line_info);
	while (i < 1)
		free(diameter_info[i++]);
	free(diameter_info);
}

void	mrt_parse_insert_vector(char *line_info, t_point *vector)
{
	char	**xyz;
	int		i;

	i = 0;
	xyz = mrt_split(line_info, ',');
	if (xyz == NULL)
		mrt_print_err("malloc failed\n");
	if (mrt_split_size(xyz) != 3)
		mrt_print_err("Incorrect information for vector\n");
	vector->x = mrt_atod(xyz[0]);
	vector->y = mrt_atod(xyz[1]);
	vector->z = mrt_atod(xyz[2]);
	while (i < 3)
		free(xyz[i++]);
	free(xyz);
}

void	mrt_parse_insert_point(char *line_info, t_point *point)
{
	char	**xyz;
	int		i;

	i = 0;
	xyz = mrt_split(line_info, ',');
	if (xyz == NULL)
		mrt_print_err("malloc failed\n");
	if (mrt_split_size(xyz) != 3)
		mrt_print_err("Incorrect information for point\n");
	point->x = mrt_atod(xyz[0]);
	point->y = mrt_atod(xyz[1]);
	point->z = mrt_atod(xyz[2]);
	while (i < 3)
		free(xyz[i++]);
	free(xyz);
}

void	mrt_parse_insert_color(char *line_info, t_color *color)
{
	char	**rgb;
	int		i;

	i = 0;
	rgb = mrt_split(line_info, ',');
	if (rgb == NULL)
		mrt_print_err("malloc failed\n");
	if (mrt_split_size(rgb) != 3)
		mrt_print_err("Incorrect information for color\n");
	color->x = mrt_atod(rgb[0]);
	color->y = mrt_atod(rgb[1]);
	color->z = mrt_atod(rgb[2]);
	while (i < 3)
		free(rgb[i++]);
	free(rgb);
}

void	mrt_parse_insert_ratio(char *line_info, double *ratio)
{
	char	**ratio_info;
	int		i;

	i = 0;
	ratio_info = mrt_split(line_info, ',');
	if (ratio_info == NULL)
		mrt_print_err("malloc failed\n");
	if (mrt_split_size(ratio_info) != 1)
		mrt_print_err("Incorrect information for ratio\n");
	*ratio = mrt_atod(ratio_info[0]);
	while (i < 1)
		free(ratio_info[i++]);
	free(ratio_info);
}
