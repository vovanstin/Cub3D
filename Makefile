# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/27 19:32:48 by nomargen          #+#    #+#              #
#    Updated: 2022/10/21 21:02:41 by nomargen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cub3d

CC				=	cc

CFLAGS			=	-Wall -Werror -Wextra -O0 -g

SRC_DIR			=	src/

INC_DIR			=	inc/

SRC_BONUS_DIR	=	src/bonus/

INC_BONUS_DIR	=	inc/bonus/

SRC				=	$(addprefix $(SRC_DIR), $(SRC_FILES))

INC				=	$(addprefix $(INC_DIR), $(INC_FILES))

SRC_BONUS		=	$(addprefix $(SRC_BONUS_DIR), $(SRC_FILES_BONUS))

INC_BONUS		=	$(addprefix $(INC_BONUS_DIR), $(INC_FILES_BONUS))

SRC_FILES_BONUS	=	main_bonus.c parser_1_bonus.c parser_2_bonus.c parser_3_bonus.c parcer_4_bonus.c parcer_5_bonus.c parser_utils_1_bonus.c parser_utils_2_bonus.c get_next_line_utils_bonus.c get_next_line_bonus.c draw_map_bonus.c handler_func_bonus.c utils1_bonus.c utils2_bonus.c utils3_bonus.c

INC_FILES_BONUS	=	main_bonus.h parser_bonus.h get_next_line_bonus.h draw_map_bonus.h

SRC_FILES		=	main.c parser_1.c parser_2.c parser_3.c parcer_4.c parcer_5.c parser_utils_1.c parser_utils_2.c get_next_line_utils.c get_next_line.c draw_map.c handler_func.c utils1.c utils2.c utils3.c

INC_FILES		=	main.h parser.h get_next_line.h draw_map.h

OBJ_BONUS 		=	$(SRC_BONUS:.c=.o)

OBJ				=	$(SRC:.c=.o)

LIBFT_DIR		=	lib/libft

LIBFT			=	$(addsuffix .a, $(LIBFT_DIR))

RM				=	rm -rf

LDLIBS			=	-lft -Lminilibx -lmlx -framework OpenGL -framework AppKit -Lmlx -lXext -lX11 -lm


%.o: %.с  
	$(CC) $(CFLAGS) -c -o $@ $<

all:	$(NAME)

bonus: $(NAME)

$(NAME): $(if $(findstring bonus, $(MAKECMDGOALS)), tmp_b, tmp_m)
	cp $(if $(findstring bonus, $(MAKECMDGOALS)), tmp_b, tmp_m) $(NAME)

tmp_b:  $(INC_BONUS)  $(OBJ_BONUS) $(LIBFT)
	$(CC) $(OBJ_BONUS) -Llib $(LDLIBS) -o tmp_b
	$(RM) tmp_m

tmp_m: $(INC) $(OBJ) $(LIBFT)
	$(CC) $(OBJ) -Llib $(LDLIBS) -o tmp_m
	$(RM) tmp_b

$(LIBFT): $(LIBFT_DIR)/libft.a
	cp $(LIBFT_DIR)/libft.a $(LIBFT)

$(LIBFT_DIR)/libft.a:
	make --directory=$(LIBFT_DIR) bonus

lib_clean:
	make --directory=$(LIBFT_DIR) fclean
	$(RM) lib/libft.a

fclean: clean
	$(RM) $(NAME)
	$(RM) tmp_m
	$(RM) tmp_b

clean: lib_clean
	$(RM) $(OBJ)
	$(RM) $(OBJ_BONUS)

re: fclean all

.PHONY: all clean fclean lib_clean re
