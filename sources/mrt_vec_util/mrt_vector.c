/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haekang <haekang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:24:31 by haekang           #+#    #+#             */
/*   Updated: 2024/01/08 20:26:03 by haekang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_point      vec3(double x, double y, double z)
{
    t_point vec;

    vec.x = x;
    vec.y = y;
    vec.z = z;
    return (vec);
}

//포인트3 생성자
t_point    point3(double x, double y, double z)
{
    t_point point;

    point.x = x;
    point.y = y;
    point.z = z;
    return (point);
}

//색상3 생성자
t_color    color3(double r, double g, double b)
{
    t_color color;

    color.x = r;
    color.y = g;
    color.z = b;
    return (color);
}

// 벡터 값 설정
void        vset(t_point *vec, double x, double y, double z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

// 벡터 길이 제곱
double      vlength2(t_point vec)
{
    return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

// 벡터 길이
double      vlength(t_point vec)
{
    return (sqrt(vlength2(vec)));
}

// 벡터합
t_point      vplus(t_point vec, t_point vec2)
{
    vec.x += vec2.x;
    vec.y += vec2.y;
    vec.z += vec2.z;
    return (vec);
}

// 벡터합2
t_point      vplus_(t_point vec, double x, double y, double z)
{
    vec.x += x;
    vec.y += y;
    vec.z += z;
    return (vec);
}

// 벡터차
t_point      vminus(t_point vec, t_point vec2)
{
    vec.x -= vec2.x;
    vec.y -= vec2.y;
    vec.z -= vec2.z;
    return (vec);
}

t_point      vminus_(t_point vec, double x, double y, double z)
{
    vec.x -= x;
    vec.y -= y;
    vec.z -= z;
    return (vec);
}

// 벡터 * 스칼라 곱연산
t_point      vmult(t_point vec, double t)
{
    vec.x *= t;
    vec.y *= t;
    vec.z *= t;
    return (vec);
}

// 벡터 축 값끼리 곱연산
t_point      vmult_(t_point vec, t_point vec2)
{
    vec.x *= vec2.x;
    vec.y *= vec2.y;
    vec.z *= vec2.z;
    return (vec);
}

// 벡터 스칼라 나누기
t_point      vdivide(t_point vec, double t)
{
    vec.x *= 1 / t;
    vec.y *= 1 / t;
    vec.z *= 1 / t;

    return vec;
}

// 벡터 내적
double      vdot(t_point vec, t_point vec2)
{
    return (vec.x * vec2.x + vec.y * vec2.y + vec.z * vec2.z);
}

// 벡터 외적
t_point      vcross(t_point vec, t_point vec2)
{
    t_point new;

    new.x = vec.y * vec2.z - vec.z * vec2.y;
    new.y = vec.z * vec2.x - vec.x * vec2.z;
    new.z = vec.x * vec2.y - vec.y * vec2.x;
    return (new);
}

// 단위 벡터
t_point      vunit(t_point vec)
{
    double len = vlength(vec);
    if (len == 0)
    {
        printf("Error\n:Devider is 0");
        exit(0);
    }
    vec.x /= len;
    vec.y /= len;
    vec.z /= len;
    return (vec);
}

// 두 벡터의 원소를 비교하여 작은 값들만 반환
t_point  vmin(t_point vec1, t_point vec2)
{
    if (vec1.x > vec2.x)
        vec1.x = vec2.x;
    if (vec1.y > vec2.y)
        vec1.y = vec2.y;
    if (vec1.z > vec2.z)
        vec1.z = vec2.z;
    return (vec1);
}