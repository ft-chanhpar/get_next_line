/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:28:27 by chanhpar          #+#    #+#             */
/*   Updated: 2023/02/22 17:08:02 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static t_node	**append_data(t_node **node, char *buffer)
{
	if ((*node)->read_len == 0)
		return (node);
	(*node)->saved_string[
}

static char	*parse_line(t_node *node)
{
	char	*string;

	string = malloc(sizeof(char) * (node->newline_pos[node->newline_idx] + 1));
	if (string == NULL)
		return (NULL);
	return (node->saved_string);
}

static char	*process(t_node **node)
{
	char	buffer[BUFFER_SIZE];
	t_node	*tmp;

	if ((*node)->newline_count != 0)
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
		(*node)->state = FILE_END;
	if (append_data(node, buffer))
		return (process(node));
	return (NULL);
}

static char	*gnl(t_node *node, int fd)
{
	if (node->fd == fd)
		return (process(&node->next));
	if (node->next != NULL)
		return (gnl(node->next, fd));
	node->next = malloc(sizeof(t_node));
	if (node->next == NULL)
		return (NULL);
	node->next->fd = fd;
	node->next->state = EMPTY;
	node->next->saved_string = NULL;
	node->next->begin = 0;
	node->next->end = 0;
	node->next->cap = 0;
	node->next->newline_idx = 0;
	node->next->newline_count = 0;
	return (gnl(node->next, fd));
}

char	*get_next_line(int fd)
{
	static t_node	head;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (gnl(&head, fd));
}
