/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:28:27 by chanhpar          #+#    #+#             */
/*   Updated: 2023/03/03 18:08:11 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static t_node	**append_data(t_node **node, char *buffer)
{
	if ((*node)->read_len == 0)
		return (node);
	--(*node)->read_len;
	if (*buffer == '\n')
	{
		(*node)->newline_pos[(*node)->newline_idx++] = (*node)->end;
		++(*node)->newline_count;
	}
	(*node)->saved_string[(*node)->end++] = *buffer;
	return (append_data(node, buffer + 1));
}

static char	*parse_line(t_node *node)
{
	char	*string;

	string = malloc(sizeof(char) * (node->newline_pos[node->newline_idx] + 2));
	if (string == NULL)
		return (NULL);
	ft_memcpy_recur(string, node->saved_string, node->newline_pos[node->newline_idx] + 1, 0);
	string[node->newline_pos[node->newline_idx] + 1] = '\0';
	node->begin = node->newline_pos[node->newline_idx] + 1;
	++node->newline_idx;
	if (node->newline_idx == node->newline_count)
	{
		node->newline_idx = 0;
		node->newline_count = 0;
	}
	return (string);
}

static char	*process(t_node **node)
{
	char	buffer[BUFFER_SIZE];
	char	*new_string;
	t_node	*tmp;

	if ((*node)->newline_count != 0) // XXX
		return (parse_line(*node));
	(*node)->read_len = read((*node)->fd, buffer, BUFFER_SIZE);
	if ((*node)->read_len < 0)
	{
		tmp = (*node)->next;
		free((*node)->saved_string);
		free(*node);
		*node = tmp;
		return (NULL);
	}
	if ((*node)->read_len < BUFFER_SIZE)
		(*node)->state = FILE_END; // XXX
	if ((*node)->state == EMPTY || (*node)->cap - (*node)->end < (size_t)(*node)->read_len)
	{
		new_string = malloc(sizeof(char) * ((*node)->cap + (*node)->read_len + 1));
		if (new_string == NULL)
			return (NULL); // XXX
		ft_memcpy_recur(new_string, (*node)->saved_string, (*node)->end - (*node)->begin, 0);
		ft_memcpy_recur(new_string + (*node)->end - (*node)->begin, (*node)->saved_string, (*node)->read_len, 0);
		new_string[(*node)->end - (*node)->begin + (*node)->read_len + 1] = '\0';
	}
	if (append_data(node, buffer))
		return (process(node));
	return (NULL);
}

static char	*gnl(t_node **node, int fd)
{
	if (*node != NULL)
	{
		if ((*node)->fd == fd)
			return (process(node));
		else
			return (gnl(&(*node)->next, fd));
	}
	else
	{
		*node = malloc(sizeof(t_node));
		if (*node == NULL)
			return (NULL);
		(*node)->fd = fd;
		(*node)->state = EMPTY;
		(*node)->next = NULL;
		return (gnl(node, fd));
	}
}

char	*get_next_line(int fd)
{
	static t_node	head;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (gnl(&head.next, fd));
}
