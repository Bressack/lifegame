# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 23:43:12 by tharchen          #+#    #+#              #
#    Updated: 2019/12/03 08:07:08 by tharchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#                                                                              #
#    Makefile project lifegame by tharchen                                     #
#                                                                              #
#    rules:                                                                    #
#                                                                              #
#    make          : make the project                                          #
#    make all      : make the project                                          #
#    make lifegame : make the project                                          #
#    make norm     : run the norminette of srcs and headers                    #
#    make clean    : clean object files (.o)                                   #
#    make fclean   : clean object files (.o) and remove lifegame bin           #
#    make re       : run rules fclean then all (multi thread compilation)      #
#                                                                              #
# *** NAME - CC - FLAGS ****************************************************** #

NAME				=	lifegame

CC					=	gcc

FLAGS				=	-Wall -Wextra -Werror -O3 -g3 -fsanitize=address

# FLAGS_MLX			=	-L./$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit
FLAGS_MLX			=	-lmlx -framework OpenGL -framework AppKit

# *** HEADER MLX ************************************************************* #

MLX_PATH			=	minilibx_opengl/

HEADER_MLX_DIR		=	$(MLX_PATH)

HEADER_MLX_LIST		=	\
						mlx.h				\

HEADER_MLX			=	$(addprefix $(HEADER_MLX_DIR), $(HEADER_MLX_LIST))

MLX_LIB				=	$(addprefix $(MLX_PATH), libmlx.a)

# *** HEADER LIBFT *********************************************************** #

LIBFT_PATH			=	libft/

HEADER_LIBFT_DIR	=	$(addprefix $(LIBFT_PATH), $(HEADER_DIR)) # CAUTION

HEADER_LIBFT_LIST	=	\
						libft.h	\

HEADER_LIBFT		=	$(addprefix $(HEADER_LIBFT_DIR), $(HEADER_LIBFT_LIST))

LIBFT_LIB			=	$(addprefix $(LIBFT_PATH), libft.a)

# *** PROJECT HEADER ********************************************************* #

HEADER_DIR			=	\
						includes \

HEADER_LIST			=	\
						lg.h \

HEADER				=	$(addprefix $(HEADER_DIR), $(HEADER_LIST))

# *** SRCS ******************************************************************* #

SRCS_LIST			=	\
						main.c \

SRCS_DIR			=	srcs/

SRCS				=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))

# *** OBJS ******************************************************************* #

OBJS_DIR			=	objs/

OBJS_LIST			=	$(patsubst %.c, %.o, $(SRCS_LIST))

OBJS				=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))

# *** RULES ****************************************************************** #

.PHONY: clean fclean all re norm

all: $(NAME)

$(NAME): $(OBJS)
	@ $(CC) $(FLAGS) $(FLAGS_MLX) -I $(HEADER_DIR) $(OBJS) -o $@ $(MLX_LIB) #-I $(HEADER_MLX_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@ mkdir -p $(OBJS_DIR)
	@ $(CC) $(FLAGS) -I $(HEADER_DIR) -c -o $@ $< #-I $(HEADER_MLX_DIR)
	@ echo "\033[31mProgram \033[32m$(NAME) : \033[34mCompilation of \033[36m$(notdir $<)\033[0m"

norm:
	@ norminette $(SRCS) $(HEADER)

clean:
	@ rm -rf $(OBJS_DIR)

fclean: clean
	@ rm -f $(NAME)

re: fclean
	@ make -j

# **************************************************************************** #
