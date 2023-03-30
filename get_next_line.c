/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:28:27 by chanhpar          #+#    #+#             */
/*   Updated: 2023/03/30 16:06:07 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

extern char		*ft_mempcpy(char *dst, char const *src, size_t const len);
extern void		*clear_node(t_node **node);
extern char		*parse_line(t_node **node);
extern t_node	**append_data(t_node **node, char *buffer);
t_node			*split_or_skew(t_node *node, t_oper oper);

/* check size overflow? change to deque? */
static char	*process(t_node **node, char *buffer)
{
	char	*copy;

	if ((*node)->que_head != (*node)->que_tail || (*node)->is_eof)
		return (parse_line(node));
	(*node)->read_len = read((*node)->fd, buffer, BUFFER_SIZE);
	if ((*node)->read_len < 0)
		return (clear_node(node));
	if ((*node)->cap - (*node)->end < (size_t)(*node)->read_len)
	{
		(*node)->end -= (*node)->begin;
		(*node)->cap += (*node)->cap + (*node)->read_len;
		copy = malloc(sizeof(char) * ((*node)->cap));
		if (copy == NULL)
			return (clear_node(node));
		if ((*node)->saved)
			ft_mempcpy(copy, (*node)->saved + (*node)->begin, (*node)->end);
		free((*node)->saved);
		(*node)->saved = copy;
		(*node)->begin = 0;
	}
	(*node)->is_eof = ((*node)->read_len == 0);
	return (process(append_data(node, buffer), buffer));
}

static char	*gnl(t_node **node, char *buffer, int fd)
{
	if (*node != NULL)
	{
		if ((*node)->fd == fd)
			return (process(node, buffer));
		return (gnl(&(*node)->childs[(*node)->fd < fd], buffer, fd));
	}
	*node = malloc(sizeof(t_node));
	if (*node == NULL)
		return (NULL);
	(*node)->childs[LEFT] = NULL;
	(*node)->childs[RIGHT] = NULL;
	(*node)->level = 1;
	(*node)->fd = fd;
	(*node)->is_eof = 0;
	(*node)->saved = NULL;
	(*node)->begin = 0;
	(*node)->end = 0;
	(*node)->cap = 0;
	(*node)->que_head = 0;
	(*node)->que_tail = 0;
	*node = split_or_skew(split_or_skew(*node, SKEW), SPLIT);
	return (process(node, buffer));
}

char	*get_next_line(int fd)
{
	static t_head_node	head;

	if (fd < 0)
		return (NULL);
	return (gnl(&head.next[fd % TABLE_SIZE], head.buffer, fd));
}
