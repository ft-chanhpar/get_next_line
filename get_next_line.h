/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:27:50 by chanhpar          #+#    #+#             */
/*   Updated: 2023/02/23 17:37:17 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stddef.h>

typedef enum e_state
{
	EMPTY,
	VALID,
	HAS_LINE,
	FILE_END
}	t_state;

typedef struct s_node
{
	struct s_node	*next;
	int				fd;
	t_state			state;
	char			*saved_string;
	size_t			begin;
	size_t			end;
	size_t			cap;
	size_t			newline_pos[BUFFER_SIZE];
	size_t			newline_idx;
	size_t			newline_count;
	ssize_t			read_len;
}	t_node;


size_t	ft_strlen_recur(char const *str, size_t const acc);

char	*ft_memcpy_recur(char *dst, char const *src, size_t const len, size_t const acc);

char	*ft_slice(char const *src, size_t const begin, size_t const end);


#endif /* GET_NEXT_LINE_H */
