/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:28:27 by chanhpar          #+#    #+#             */
/*   Updated: 2023/04/16 21:35:21 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

extern char		*ft_mempcpy(char *dst, char const *src, size_t const len);
extern void		*clear_node(t_gnl_node **node);

static t_gnl_node	**append_data(t_gnl_node **node, char *buffer)
{
	if ((*node)->read_len == 0)
		return (node);
	--(*node)->read_len;
	if (*buffer == '\n')
	{
		(*node)->line_que[(*node)->que_rear++] = (*node)->end;
		(*node)->que_rear %= (BUFFER_SIZE + 1);
	}
	(*node)->saved[(*node)->end++] = *buffer;
	return (append_data(node, buffer + 1));
}

static char	*parse_line(t_gnl_node **node)
{
	char	*string;
	size_t	len;

	if ((*node)->is_eof)
		len = (*node)->end - (*node)->begin;
	else
	{
		len = (*node)->line_que[(*node)->que_front++] - (*node)->begin + 1;
		(*node)->que_front %= (BUFFER_SIZE + 1);
	}
	if (len == 0)
		return (clear_node(node));
	string = malloc(sizeof(char) * (len + 1));
	if (string == NULL)
		return (clear_node(node));
	*ft_mempcpy(string, (*node)->saved + (*node)->begin, len) = '\0';
	(*node)->begin += len;
	return (string);
}

static char	*process(t_gnl_node **node, char *buffer)
{
	char	*copy;

	if ((*node)->que_front != (*node)->que_rear || (*node)->is_eof)
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
		if ((*node)->saved != NULL)
			ft_mempcpy(copy, (*node)->saved + (*node)->begin, (*node)->end);
		free((*node)->saved);
		(*node)->saved = copy;
		(*node)->begin = 0;
	}
	(*node)->is_eof = ((*node)->read_len == 0);
	return (process(append_data(node, buffer), buffer));
}

static char	*gnl(t_gnl_node **node, char *buffer, int fd)
{
	if (*node == NULL)
	{
		*node = malloc(sizeof(t_gnl_node));
		if (*node == NULL)
			return (NULL);
		(*node)->next = NULL;
		(*node)->fd = fd;
		(*node)->is_eof = 0;
		(*node)->saved = NULL;
		(*node)->begin = 0;
		(*node)->end = 0;
		(*node)->cap = 0;
		(*node)->que_front = 0;
		(*node)->que_rear = 0;
	}
	if ((*node)->fd == fd)
		return (process(node, buffer));
	return (gnl(&(*node)->next, buffer, fd));
}

char	*get_next_line(int fd)
{
	static t_head_node	head;

	if (fd < 0)
		return (NULL);
	return (gnl(&head.next[fd % TABLE_SIZE], head.buffer, fd));
}
