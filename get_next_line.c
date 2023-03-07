/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:28:27 by chanhpar          #+#    #+#             */
/*   Updated: 2023/03/07 18:39:24 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static t_node	*reserve_node(t_node *node)
{
	char	*copy;

	copy = malloc(sizeof(char) * ((node->cap << 1) + node->read_len));
	if (copy == NULL)
		return (NULL);
	if (node->saved)
		ft_memcopy(copy, node->saved + node->begin, node->end - node->begin);
	free(node->saved);
	node->saved = copy;
	node->end = node->end - node->begin;
	node->cap += node->cap + node->read_len;
	node->begin = 0;
	return (node);
}

static char	*process(t_node **node, char *buffer)
{
	if ((*node)->lf_idx < (*node)->lf_count || (*node)->is_eof)
		return (parse_line(node));
	(*node)->read_len = read((*node)->fd, buffer, BUFFER_SIZE);
	if ((*node)->read_len < 0)
		return ((char *)clear_node(node));
	(*node)->is_eof = ((*node)->read_len == 0);
	if ((*node)->cap - (*node)->end < (size_t)(*node)->read_len)
	{
		if (reserve_node(*node) == NULL)
			return ((char *)clear_node(node));
	}
	(*node)->lf_idx = 0;
	append_data(node, buffer);
	(*node)->lf_idx = 0;
	return (process(node, buffer));
}

static char	*gnl(t_node **node, char *buffer, int fd)
{
	if (*node != NULL)
	{
		if ((*node)->fd == fd)
			return (process(node, buffer));
		return (gnl(&(*node)->next, buffer, fd));
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
	(*node)->lf_idx = 0;
	(*node)->lf_count = 0;
	return (gnl(node, buffer, fd));
}

char	*get_next_line(int fd)
{
	static t_head_node	head;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (gnl(&head.next, head.buffer, fd));
}
