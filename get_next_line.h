/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:27:50 by chanhpar          #+#    #+#             */
/*   Updated: 2023/02/20 22:39:30 by chanhpar         ###   ########.fr       */
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
	HAS_LINE
}	t_state;

typedef struct s_node
{
	struct s_node	*next;
	int				fd;
	t_state			state;
	char			*data;
	size_t			begin;
	size_t			end;
	size_t			cap;
	size_t			newline_pos[BUFFER_SIZE];
	size_t			newline_idx;
	size_t			newline_count;
}	t_node;

#endif /* GET_NEXT_LINE_H */
