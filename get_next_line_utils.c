/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:23:34 by chanhpar          #+#    #+#             */
/*   Updated: 2023/03/06 16:30:41 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

char	*ft_memcopy(char *dst, char const *src, size_t const len)
{
	if (len != 0)
	{
		*dst = *src;
		return (ft_memcopy(dst + 1, src + 1, len - 1));
	}
	return (dst);
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
		(*node)->lf_pos[(*node)->lf_idx++] = (*node)->end;
		++(*node)->lf_count;
	}
	(*node)->saved[(*node)->end++] = *buffer;
	return (append_data(node, buffer + 1));
}

char	*parse_line(t_node **node)
{
	char	*string;
	size_t	len;

	if ((*node)->is_eof == FILE_END)
	{
		len = (*node)->end - (*node)->begin;
		if (len == 0)
			return ((char *)clear_node(node));
	}
	else
	{
		len = (*node)->lf_pos[(*node)->lf_idx++] - (*node)->begin + 1;
		if ((*node)->lf_idx == (*node)->lf_count)
		{
			(*node)->lf_idx = 0;
			(*node)->lf_count = 0;
		}
	}
	string = malloc(sizeof(char) * (len + 1));
	if (string == NULL)
		return (NULL);
	*ft_memcopy(string, (*node)->saved + (*node)->begin, len) = '\0';
	(*node)->begin += len;
	return (string);
}
