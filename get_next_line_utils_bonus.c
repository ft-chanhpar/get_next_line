/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 03:29:02 by chanhpar          #+#    #+#             */
/*   Updated: 2022/01/07 02:23:38 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	if (dest == NULL && src == NULL)
		return (NULL);
	tmp1 = (unsigned char *)dest;
	tmp2 = (unsigned char *)src;
	if (tmp1 > tmp2)
	{
		while (n > 0)
		{
			n--;
			*(tmp1 + n) = *(tmp2 + n);
		}
	}
	else
	{
		while (n > 0)
		{
			n--;
			*(tmp1++) = *(tmp2++);
		}
	}
	return (dest);
}

char	*ft_substr(char const *s, size_t len)
{
	char	*rst;

	rst = (char *)malloc(sizeof(char) * (len + 1));
	if (!rst)
		return (NULL);
	rst = ft_memmove(rst, s, len);
	rst[len] = '\0';
	return (rst);
}

char	*ft_strjoin(char const *s1, char const *s2, size_t len)
{
	size_t	len1;
	size_t	len2;
	char	*rst;
	char	*tmp;

	len2 = ft_strlen(s2);
	if (len > len2)
		len = len2;
	if (s1 == NULL)
		return (ft_substr(s2, len));
	len1 = ft_strlen(s1);
	rst = (char *)malloc(sizeof(char) * (len1 + len + 1));
	if (!rst)
		return (NULL);
	tmp = rst;
	tmp = ft_memmove(tmp, s1, len1);
	tmp += len1;
	tmp = ft_memmove(tmp, s2, len);
	tmp[len] = '\0';
	return (rst);
}