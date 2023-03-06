/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:23:34 by chanhpar          #+#    #+#             */
/*   Updated: 2023/03/06 12:16:28 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_memcpy_recur(char *dst, char const *src, size_t const len)
{
	if (len != 0)
	{
		*dst = *src;
		return (ft_memcpy_recur(dst + 1, src + 1, len - 1));
	}
	return (dst);
}
