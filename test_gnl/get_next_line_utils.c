/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:07:36 by chanhpar          #+#    #+#             */
/*   Updated: 2022/03/22 14:28:46 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_memmove(char *dst, char *src, size_t len)
{
	size_t	idx;

	if (!dst && !src)
		return (NULL);
	idx = 0;
	while (idx < len)
	{
		dst[idx] = src[idx];
		idx++;
	}
	return (dst);
}

char	*ft_substr(char *s1, size_t len)
{
	char	*ret;

	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ret = ft_memmove(ret, s1, len);
	ret[len] = '\0';
	return (ret);
}

char	*ft_strjoin(char *s1, char *s2, size_t len)
{
	size_t	len1;
	size_t	len2;
	char	*ret;
	char	*tmp;

	len2 = ft_strlen(s2);
	if (len > len2)
		len = len2;
	if (!s1)
		return (ft_substr(s2, len));
	len1 = ft_strlen(s1);
	ret = malloc(sizeof(char) * (len1 + len + 1));
	if (!ret)
		return (NULL);
	tmp = ret;
	tmp = ft_memmove(tmp, s1, len1);
	tmp += len1;
	tmp = ft_memmove(tmp, s2, len);
	tmp[len] = '\0';
	return (ret);
}
