/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:27:50 by chanhpar          #+#    #+#             */
/*   Updated: 2023/03/27 15:05:10 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <sys/types.h>

typedef enum e_state
{
	EMPTY,
	FILE_END
}	t_state;

typedef struct s_node
{
	struct s_node	*next;
	int				fd;
	t_state			is_eof;
	char			*saved;
	size_t			begin;
	size_t			end;
	size_t			cap;
	size_t			line_que[BUFFER_SIZE + 1];
	size_t			que_head;
	size_t			que_tail;
	ssize_t			read_len;
}	t_node;

typedef struct s_head_node
{
	t_node	*next;
	char	buffer[BUFFER_SIZE];
}	t_head_node;

char	*get_next_line(int fd);

#endif /* GET_NEXT_LINE_H */
