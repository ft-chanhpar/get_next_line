/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:27:50 by chanhpar          #+#    #+#             */
/*   Updated: 2023/03/24 17:50:31 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define HASH_SIZE 10

# include <sys/types.h>

typedef enum e_state
{
	EMPTY,
	FILE_END
}	t_state;

typedef struct s_node
{
	struct s_node	*left;
	struct s_node	*right;
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
	t_node	*next[HASH_SIZE];
	char	buffer[BUFFER_SIZE];
}	t_head_node;

char	*ft_memcopy(char *dst, char const *src, size_t const len);

void	*clear_node(t_node **node);

char	*parse_line(t_node **node);

t_node	**append_data(t_node **node, char *buffer);

char	*get_next_line(int fd);

#endif /* GET_NEXT_LINE_H */
