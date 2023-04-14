/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:23:34 by chanhpar          #+#    #+#             */
/*   Updated: 2023/04/14 16:33:02 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

char	*ft_mempcpy(char *dst, char const *src, size_t const len)
{
	if (len == 0)
		return (dst);
	*dst = *src;
	return (ft_mempcpy(dst + 1, src + 1, len - 1));
}

void	*clear_node(t_gnl_node **node)
{
	t_gnl_node	*tmp;

	tmp = (*node)->next;
	free((*node)->saved);
	free(*node);
	*node = tmp;
	return (NULL);
}
