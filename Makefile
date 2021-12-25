# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 02:20:40 by chanhpar          #+#    #+#              #
#    Updated: 2021/12/25 09:14:11 by chanhpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	= get_next_line.c get_next_line_utils.c main.c

BSRC	= 
BSRCDIR	=

OBJ		= $(SRC:.c=.o)
BOBJ	= $(BSRC:.c=.o)

INC		=

NAME	= a.out

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRC)
	$(CC) -g $(CFLAGS) $^ -D BUFFER_SIZE=1000

bonus:
	@make --no-print-directory OBJ="$(OBJ) $(BOBJ)" all

# %.o: %.c
#     $(CC) -g $(CFLAGS) -c $< -o $(<:.c=.o) -D BUFFER_SIZE=42

clean:
	rm -f $(OBJ) $(BOBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re 
