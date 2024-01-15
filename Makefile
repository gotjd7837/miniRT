# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inlim <inlim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 16:29:11 by haekang           #+#    #+#              #
#    Updated: 2024/01/15 20:09:21 by inlim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
MFLAGS=-framework OpenGL -framework Appkit
NAME = miniRT
HEADERS = ./includes
MLX_DIR = ./includes/mlx
SRCS = ./sources/mrt_main/main.c\
	./sources/mrt_parse/mrt_parse.c\
	./sources/mrt_parse/mrt_parse_init_info.c\
	./sources/mrt_parse/mrt_parse_insert_ambient.c\
	./sources/mrt_parse/mrt_parse_insert_camera.c\
	./sources/mrt_parse/mrt_parse_insert_cylinder.c\
	./sources/mrt_parse/mrt_parse_insert_element.c\
	./sources/mrt_parse/mrt_parse_insert_light.c\
	./sources/mrt_parse/mrt_parse_insert_plane.c\
	./sources/mrt_parse/mrt_parse_insert_sphere.c\
	./sources/mrt_parse/mrt_parse_insert_util.c\
	./sources/mrt_parse/mrt_parse_load_file.c\
	./sources/mrt_parse/mrt_parse_return_file_path.c\
	./sources/mrt_render/mrt_cylinder_util.c\
	./sources/mrt_render/mrt_get_camera_info.c\
	./sources/mrt_render/mrt_get_color.c\
	./sources/mrt_render/mrt_mlx_loop.c\
	./sources/mrt_render/mrt_ray_trace.c\
	./sources/mrt_render/mrt_ray_trace_cylinder.c\
	./sources/mrt_render/mrt_ray_trace_plane.c\
	./sources/mrt_render/mrt_ray_trace_sphere.c\
	./sources/mrt_render/mrt_render.c\
	./sources/mrt_render/mrt_render_util.c\
	./sources/mrt_render/mrt_shadow.c\
	./sources/mrt_util/mrt_atod.c\
	./sources/mrt_util/mrt_atoi.c\
	./sources/mrt_util/mrt_bit_get.c\
	./sources/mrt_util/mrt_bit_increase.c\
	./sources/mrt_util/mrt_get_next_line.c\
	./sources/mrt_util/mrt_lst_add_back.c\
	./sources/mrt_util/mrt_lst_new_node.c\
	./sources/mrt_util/mrt_print_err.c\
	./sources/mrt_util/mrt_split.c\
	./sources/mrt_util/mrt_split_size.c\
	./sources/mrt_util/mrt_strchr.c\
	./sources/mrt_util/mrt_strcmp.c\
	./sources/mrt_util/mrt_strdup.c\
	./sources/mrt_util/mrt_strjoin.c\
	./sources/mrt_util/mrt_strlcpy.c\
	./sources/mrt_util/mrt_strlen.c\
	./sources/mrt_util/mrt_substr.c\
	./sources/mrt_vec_util/mrt_vec_1.c\
	./sources/mrt_vec_util/mrt_vec_2.c\
	./sources/mrt_vec_util/mrt_vec_3.c\
	./sources/mrt_vec_util/mrt_vec_4.c
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	$(CC) $(MFLAGS) $(OBJS) $(MLX_DIR)/libmlx.a -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -Rf $(OBJS)

fclean: clean
	rm -Rf $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
