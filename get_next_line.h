/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:27:50 by chanhpar          #+#    #+#             */
/*   Updated: 2023/04/14 17:00:53 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# if BUFFER_SIZE <= 0

static const int	g_error[-1];

# endif

# define TABLE_SIZE 20

typedef struct s_gnl_node
{
	struct s_gnl_node	*next;
	int					fd;
	int					is_eof;
	char				*saved;
	size_t				begin;
	size_t				end;
	size_t				cap;
	size_t				line_que[BUFFER_SIZE + 1];
	size_t				que_front;
	size_t				que_rear;
	ssize_t				read_len;
}	t_gnl_node;

typedef struct s_head_node
{
	t_gnl_node	*next[TABLE_SIZE];
	char		buffer[BUFFER_SIZE];
}	t_head_node;

char	*get_next_line(int fd);

#endif /* GET_NEXT_LINE_H */
