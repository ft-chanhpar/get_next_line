/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:28:27 by chanhpar          #+#    #+#             */
/*   Updated: 2023/02/20 00:49:14 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static t_node	**append_data(t_node **node, char *buffer, ssize_t read_len)
{
	return (node);
}

static char	*parse_line(t_node *node)
{
	return (node->data);
}

static char	*line(t_node **node)
{
	ssize_t	read_len;
	char	buffer[BUFFER_SIZE];
	t_node	*tmp;

	if ((*node)->state == HAS_LINE)
		return (parse_line(*node));
	read_len = read((*node)->fd, buffer, BUFFER_SIZE);
	if (read_len < 0)
	{
		tmp = (*node)->next;
		free((*node)->data);
		free(*node);
		*node = tmp;
		return (NULL);
	}
	return (line(append_data(node, buffer, read_len)));
}

static char	*gnl(t_node *node, int fd)
{
	if (node->fd == fd)
		return (line(&node->next, fd));
	if (node->next)
		return (gnl(node->next, fd));
	node->next = malloc(sizeof(t_node));
	if (node->next == NULL)
		return (NULL);
	node->next->fd = fd;
	node->next->state = EMPTY;
	return (gnl(node->next, fd));
}

char	*get_next_line(int fd)
{
	static t_node	head;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (gnl(&head, fd));
}
