/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:28:27 by chanhpar          #+#    #+#             */
/*   Updated: 2023/03/29 03:51:53 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

extern char		*ft_mempcpy(char *dst, char const *src, size_t const len);
extern void		*clear_node(t_node **node);
extern char		*parse_line(t_node **node);
extern t_node	**append_data(t_node **node, char *buffer);

/* check size overflow? change to deque? */
static int	reserve_node(t_node *node)
{
	char	*copy;

	copy = malloc(sizeof(char) * ((node->cap << 1) + node->read_len));
	if (copy == NULL)
		return (-1);
	if (node->saved)
		ft_mempcpy(copy, node->saved + node->begin, node->end - node->begin);
	free(node->saved);
	node->saved = copy;
	node->end -= node->begin;
	node->cap += node->cap + node->read_len;
	node->begin = 0;
	return (0);
}

static char	*process(t_node **node, char *buffer)
{
	if ((*node)->que_head != (*node)->que_tail || (*node)->is_eof)
		return (parse_line(node));
	(*node)->read_len = read((*node)->fd, buffer, BUFFER_SIZE);
	if ((*node)->read_len < 0 || \
		((*node)->cap - (*node)->end < (size_t)(*node)->read_len && \
		reserve_node(*node) < 0))
		return (clear_node(node));
	(*node)->is_eof = ((*node)->read_len == 0);
	return (process(append_data(node, buffer), buffer));
}

static char	*gnl(t_node **node, char *buffer, int fd)
{
	if (*node != NULL)
	{
		if ((*node)->fd == fd)
		{
			return (process(node, buffer));
		}
		else
		{
			return (gnl(&(*node)->next, buffer, fd));
		}
	}
	*node = malloc(sizeof(t_node));
	if (*node == NULL)
		return (NULL);
	(*node)->next = NULL;
	(*node)->fd = fd;
	(*node)->is_eof = 0;
	(*node)->saved = NULL;
	(*node)->begin = 0;
	(*node)->end = 0;
	(*node)->cap = 0;
	(*node)->que_head = 0;
	(*node)->que_tail = 0;
	return (process(node, buffer));
}

char	*get_next_line(int fd)
{
	static t_head_node	head;

	return (gnl(&head.next[fd % TABLE_SIZE], head.buffer, fd));
}
