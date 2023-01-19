/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:28:27 by chanhpar          #+#    #+#             */
/*   Updated: 2023/01/19 21:39:26 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	*gnl(t_node *node, int fd)
{
	ssize_t	read_len;
	char	buffer[BUFFER_SIZE];

	if (node->fd == fd)
	{
	}
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
	char			*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (gnl(&head, fd));
}
