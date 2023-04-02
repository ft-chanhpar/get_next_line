/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:28:27 by chanhpar          #+#    #+#             */
/*   Updated: 2023/04/02 02:44:54 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

extern t_node	*skew_or_split(t_node *const node, t_oper const oper);
extern void		*clear_node(t_node *node, t_node *parent);
extern char		*ft_mempcpy(char *dst, char const *src, size_t const len);

static t_node	**append_data(t_node **node, char *buffer)
{
	if ((*node)->read_len == 0)
		return (node);
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
			return (clear_node(*node, (*node)->parent));
	}
	else
	{
		len = (*node)->line_que[(*node)->que_head++] - (*node)->begin + 1;
		(*node)->que_head %= QUE_SIZE;
	}
	string = malloc(sizeof(char) * (len + 1));
	if (string == NULL)
		return (clear_node(*node, (*node)->parent));
	*ft_mempcpy(string, (*node)->saved + (*node)->begin, len) = '\0';
	(*node)->begin += len;
	return (string);
}

/* check size overflow? change to deque? */
static char	*process(t_node **node, char *buffer)
{
	char	*copy;

	if ((*node)->que_head != (*node)->que_tail || (*node)->is_eof)
		return (parse_line(node));
	(*node)->read_len = read((*node)->fd, buffer, BUFFER_SIZE);
	if ((*node)->read_len < 0)
		return (clear_node(*node, (*node)->parent));
	if ((*node)->cap - (*node)->end < (size_t)(*node)->read_len)
	{
		(*node)->end -= (*node)->begin;
		(*node)->cap += (*node)->cap + (*node)->read_len;
		copy = malloc(sizeof(char) * ((*node)->cap));
		if (copy == NULL)
			return (clear_node(*node, (*node)->parent));
		if ((*node)->saved)
			ft_mempcpy(copy, (*node)->saved + (*node)->begin, (*node)->end);
		free((*node)->saved);
		(*node)->saved = copy;
		(*node)->begin = 0;
	}
	(*node)->is_eof = ((*node)->read_len == 0);
	return (process(append_data(node, buffer), buffer));
}

static char	*gnl(t_node **node, t_node *parent, char *buffer, int fd)
{
	if (*node == NULL)
	{
		*node = malloc(sizeof(t_node));
		if (*node == NULL)
			return (NULL);
		(*node)->root_addr = node;
		if (parent != NULL)
			(*node)->root_addr = parent->root_addr;
		(*node)->childs[LEFT] = NULL;
		(*node)->childs[RIGHT] = NULL;
		(*node)->parent = parent;
		(*node)->level = LEAF_LEVEL;
		(*node)->fd = fd;
		(*node)->is_eof = 0;
		(*node)->saved = NULL;
		(*node)->begin = 0;
		(*node)->end = 0;
		(*node)->cap = 0;
		(*node)->que_head = 0;
		(*node)->que_tail = 0;
		node = skew_or_split((*node), SKEW)->root_addr;
	}
	if ((*node)->fd == fd)
		return (process(node, buffer));
	return (gnl(&(*node)->childs[(*node)->fd < fd], *node, buffer, fd));
}

char	*get_next_line(int fd)
{
	static t_head_node	head;

	if (fd < 0)
		return (NULL);
	return (gnl(&head.next[fd % TABLE_SIZE], NULL, head.buffer, fd));
}
