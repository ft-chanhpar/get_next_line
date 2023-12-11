# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 17:24:07 by chanhpar          #+#    #+#              #
#    Updated: 2023/03/30 12:51:51 by chanhpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL	:= all

CC				:= cc
RM				:= rm -f
MKDIR			:= mkdir -p

CFLAGS			:= -Wall -Wextra -Werror -std=c89 -pedantic
CFLAGS			+= -MMD -MP

ifdef DEBUG
	CFLAGS += -fsanitize=address,undefined -g
endif

OBJ_DIR			:= obj/

SRCS			:= test.c get_next_line.c get_next_line_utils.c
OBJS			:= $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
DEPS			:= $(OBJS:.o=.d)
-include $(DEPS)

INCS			:= get_next_line.h

INCS_DIR		:= .

CPPFLAGS		:= -I$(INCS_DIR)

NAME			:= test.out

.PHONY: all
all: $(NAME)

$(OBJ_DIR):
	$(MKDIR) $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	$(RM) -r $(OBJ_DIR)
	@echo "clean done!"

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)
	@echo "fclean done!"

.PHONY: re
re: fclean
	$(MAKE) all
