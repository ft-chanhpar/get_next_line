/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:27:50 by chanhpar          #+#    #+#             */
/*   Updated: 2023/04/02 23:24:56 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# if BUFFER_SIZE == 0

static const int	g_error[-1];

# endif

# define TABLE_SIZE 20

# define LEAF_LEVEL 1

typedef enum e_direction
{
	LEFT,
	RIGHT
}	t_direction;

typedef enum e_oper
{
	SPLIT,
	SKEW
}	t_oper;

/* rename variables: begin, end, que_head, que_tail? */

typedef struct s_node
{
	struct s_node	**root_addr;
	struct s_node	*childs[2];
	struct s_node	*parent;
	unsigned int	level;
	int				fd;
	int				is_eof;
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
	t_node	*next[TABLE_SIZE];
	char	buffer[BUFFER_SIZE];
}	t_head_node;

char	*get_next_line(int fd);

#endif /* GET_NEXT_LINE_H */
