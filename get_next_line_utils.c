/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:23:34 by chanhpar          #+#    #+#             */
/*   Updated: 2023/03/06 13:02:49 by chanhpar         ###   ########.fr       */
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
	free((*node)->saved_string);
	free(*node);
	*node = tmp;
	return (NULL);
}
