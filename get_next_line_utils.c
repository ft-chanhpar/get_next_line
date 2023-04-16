/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:23:34 by chanhpar          #+#    #+#             */
/*   Updated: 2023/04/16 22:17:18 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

char	*ft_mempcpy(char *const dst, char const *const src, size_t const len)
{
	if (len == 0)
		return (dst);
	*dst = *src;
	return (ft_mempcpy(dst + 1, src + 1, len - 1));
}

void	*clear_node(t_gnl_node **const node)
{
	t_gnl_node	*tmp;

	tmp = (*node)->next;
	free((*node)->saved);
	free(*node);
	*node = tmp;
	return (NULL);
}
