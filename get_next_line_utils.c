/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:23:34 by chanhpar          #+#    #+#             */
/*   Updated: 2023/03/30 12:58:52 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

char	*ft_mempcpy(char *dst, char const *src, size_t const len)
{
	if (len != 0)
	{
		*dst = *src;
		return (ft_mempcpy(dst + 1, src + 1, len - 1));
	}
	else
	{
		return (dst);
	}
}

void	*clear_node(t_node **node)
{
	t_node	*tmp;

	tmp = (*node)->next;
	free((*node)->saved);
	free(*node);
	*node = tmp;
	return (NULL);
}

t_node	**append_data(t_node **node, char *buffer)
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

char	*parse_line(t_node **node)
{
	char	*string;
	size_t	len;

	if ((*node)->is_eof)
	{
		len = (*node)->end - (*node)->begin;
		if (len == 0)
			return (clear_node(node));
	}
	else
	{
		len = (*node)->line_que[(*node)->que_head++] - (*node)->begin + 1;
		(*node)->que_head %= QUE_SIZE;
	}
	string = malloc(sizeof(char) * (len + 1));
	if (string == NULL)
		return (clear_node(node));
	*ft_mempcpy(string, (*node)->saved + (*node)->begin, len) = '\0';
	(*node)->begin += len;
	return (string);
}
