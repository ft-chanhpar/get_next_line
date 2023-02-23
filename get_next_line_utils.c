/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:23:34 by chanhpar          #+#    #+#             */
/*   Updated: 2023/02/23 17:37:54 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen_recur(char const *str, size_t const acc)
{
	if (*str != '\0')
	{
		return (ft_strlen_recur(str + 1, acc + 1));
	}
	return (acc);
}

char	*ft_memcpy_recur(char *dst, char const *src, size_t const len, size_t const acc)
{
	if (len != 0)
	{
		*dst = *src;
		return (ft_memcpy_recur(dst + 1, src + 1, len - 1, acc + 1));
	}
	return (dst - acc);
}

char	*ft_slice(char const *src, size_t const begin, size_t const end)
{
	char	*dst;

	dst = malloc(sizeof(char) * (end - begin + 1));
	if (dst != NULL)
	{
		ft_memcpy_recur(dst, src + begin, end - begin, 0);
		dst[end - begin] = '\0';
	}
	return (dst);
}
