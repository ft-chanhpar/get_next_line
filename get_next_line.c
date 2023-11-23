/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:28:27 by chanhpar          #+#    #+#             */
/*   Updated: 2023/03/29 21:59:52 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

extern char		*ft_mempcpy(char *dst, char const *src, size_t const len);
extern void		*clear_node(t_node **node);
extern t_node	*splay_tree(t_node *node, t_node **root_address);

static t_node	**append_data(t_node **node, char *buffer)
{
	if ((*node)->read_len == 0)
	{
		return (node);
	}
	--(*node)->read_len;
	if (*buffer == '\n')
	{
		(*node)->line_que[(*node)->que_tail++] = (*node)->end;
		(*node)->que_tail %= QUE_SIZE;
	}
	(*node)->saved[(*node)->end++] = *buffer;
	return (append_data(node, buffer + 1));
}

static char	*parse_line(t_node **node)
{
	char	*string;
	size_t	len;

	if ((*node)->is_eof)
	{
		len = (*node)->end - (*node)->begin;
		if (len == 0)
		{
			return (clear_node(node));
		}
	}
	else
	{
		len = (*node)->line_que[(*node)->que_head++] - (*node)->begin + 1;
		(*node)->que_head %= QUE_SIZE;
	}
	string = malloc(sizeof(char) * (len + 1));
	if (string == NULL)
	{
		return (clear_node(node));
	}
	*ft_mempcpy(string, (*node)->saved + (*node)->begin, len) = '\0';
	(*node)->begin += len;
	return (string);
}

static char	*process(t_node **node, char *buffer)
{
	char	*copy;

	if (*node == NULL)
		return (NULL);
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

static char	*gnl(t_node **node, t_node *parent, t_head_node *head, int const fd)
{
	if (*node == NULL)
	{
		*node = malloc(sizeof(t_node));
		if (*node == NULL)
			return (NULL);
		(*node)->parent = parent;
		(*node)->root_address = &head->next[fd % TABLE_SIZE];
		(*node)->child[LEFT] = NULL;
		(*node)->child[RIGHT] = NULL;
		(*node)->fd = fd;
		(*node)->is_eof = 0;
		(*node)->saved = NULL;
		(*node)->begin = 0;
		(*node)->end = 0;
		(*node)->cap = 0;
		(*node)->que_head = 0;
		(*node)->que_tail = 0;
		splay_tree(*node, (*node)->root_address);
		return (get_next_line(fd));
	}
	if ((*node)->fd == fd)
		return (process(node, head->buffer));
	return (gnl(&(*node)->child[(*node)->fd < fd], *node, head, fd));
}

char	*get_next_line(int fd)
{
	static t_head_node	head;

	if (fd < 0)
		return (NULL);
	return (gnl(&head.next[fd % TABLE_SIZE], NULL, &head, fd));
}
