/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_insert_element.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeseong <haeseong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:36:26 by haekang           #+#    #+#             */
/*   Updated: 2024/06/20 10:46:45 by haeseong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * mrt_parse_insert_element - 문자열 배열을 분석하여 t_info 구조체에 요소를 삽입하는 함수
 * @line_info: 분석할 문자열 배열
 * @info: 요소를 삽입할 t_info 구조체
 *
 * 이 함수는 입력된 문자열 배열의 첫 번째 요소를 확인하여,
 * 해당 배열이 어떤 요소(Ambient, Camera, Light, Sphere, Plane, Cylinder)를 나타내는지 판별합니다.
 * 판별된 요소에 따라 적절한 처리 함수(mrt_parse_insert_ambient, mrt_parse_insert_camera, mrt_parse_insert_light,
 * mrt_parse_insert_sphere, mrt_parse_insert_plane, mrt_parse_insert_cylinder)를 호출하여
 * t_info 구조체에 해당 요소를 삽입합니다.
 * Ambient, Camera, Light 요소는 각각 하나씩만 존재해야 하므로,
 * 이미 해당 요소가 삽입된 경우 상태 플래그(flags)를 사용하여 중복 삽입을 방지합니다.
 */
void	mrt_parse_insert_element(char **line_info, t_info *info)
{
	static int	flags;

	if (!mrt_strcmp(line_info[0], "A") && !mrt_bit_get(flags, AMBIENT_IDX))
		mrt_parse_insert_ambient(line_info, info, &flags);
	else if (!mrt_strcmp(line_info[0], "C") && !mrt_bit_get(flags, CAMERA_IDX))
		mrt_parse_insert_camera(line_info, info, &flags);
	else if (!mrt_strcmp(line_info[0], "L") && !mrt_bit_get(flags, LIGHT_IDX))
		mrt_parse_insert_light(line_info, info, &flags);
	else if (!(mrt_strcmp(line_info[0], "sp")))
		mrt_parse_insert_sphere(line_info, info);
	else if (!(mrt_strcmp(line_info[0], "pl")))
		mrt_parse_insert_plane(line_info, info);
	else if (!(mrt_strcmp(line_info[0], "cy")))
		mrt_parse_insert_cylinder(line_info, info);
	else
		mrt_print_err("Invalid identifier\n");
}
