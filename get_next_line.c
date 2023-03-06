/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:28:27 by chanhpar          #+#    #+#             */
/*   Updated: 2023/03/06 13:14:54 by chanhpar         ###   ########.fr       */
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
		(*node)->lf_pos[(*node)->lf_idx++] = (*node)->end;
		++(*node)->lf_count;
	}
	(*node)->saved_string[(*node)->end++] = *buffer;
	return (append_data(node, buffer + 1));
}

static char	*parse_line(t_node **node)
{
	char	*string;
	size_t	len;

	if ((*node)->state != FILE_END)
	{
		len = (*node)->lf_pos[(*node)->lf_idx] - (*node)->begin + 1;
		++(*node)->lf_idx;
		if ((*node)->lf_idx == (*node)->lf_count)
		{
			(*node)->lf_idx = 0;
			(*node)->lf_count = 0;
		}
	}
	else
	{
		len = (*node)->end - (*node)->begin;
		if (len == 0)
			return ((char *)clear_node(node));
	}
	string = malloc(sizeof(char) * (len + 1));
	if (string == NULL)
		return (NULL);
	*ft_memcopy(string, (*node)->saved_string + (*node)->begin, len) = '\0';
	(*node)->begin += len;
	return (string);
}

static char	*process(t_node **node)
{
	char	buffer[BUFFER_SIZE];
	char	*new_string;

	if ((*node)->lf_idx < (*node)->lf_count || (*node)->state == FILE_END)
		return (parse_line(node));
	(*node)->read_len = read((*node)->fd, buffer, BUFFER_SIZE);
	if ((*node)->read_len < 0)
		return ((char *)clear_node(node));
	if ((*node)->read_len == 0)
		(*node)->state = FILE_END;
	if ((*node)->cap - (*node)->end < (size_t)(*node)->read_len)
	{
		new_string = malloc(sizeof(char) * ((*node)->cap + (*node)->read_len));
		if (new_string == NULL)
			return (NULL);
		if ((*node)->saved_string)
			ft_memcopy(new_string, (*node)->saved_string + (*node)->begin, (*node)->end - (*node)->begin);
		free((*node)->saved_string);
		(*node)->saved_string = new_string;
		(*node)->end = (*node)->end - (*node)->begin;
		(*node)->cap += (*node)->read_len;
		(*node)->begin = 0;
	}
	append_data(node, buffer);
	(*node)->lf_idx = 0;
	return (process(node));
}

static char	*gnl(t_node **node, int fd)
{
	if (*node != NULL)
	{
		if ((*node)->fd == fd)
			return (process(node));
		return (gnl(&(*node)->next, fd));
	}
	*node = malloc(sizeof(t_node));
	if (*node == NULL)
		return (NULL);
	(*node)->next = NULL;
	(*node)->fd = fd;
	(*node)->state = EMPTY;
	(*node)->saved_string = NULL;
	(*node)->begin = 0;
	(*node)->end = 0;
	(*node)->cap = 0;
	(*node)->lf_idx = 0;
	(*node)->lf_count = 0;
	return (gnl(node, fd));
}

char	*get_next_line(int fd)
{
	static t_head_node	head;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (gnl(&head.next, fd));
}
