/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:31:19 by chanhpar          #+#    #+#             */
/*   Updated: 2022/03/22 02:58:27 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}

int	ft_strchr(char *str, char c, size_t len)
{
	size_t	idx;

	idx = 0;
	while (idx < len)
	{
		if (str[idx] == c)
			return (idx + 1);
		idx++;
	}
	return (0);
}

void	ft_strcat(char *dst, char *src, size_t len)
{
	size_t	idx_dst;
	size_t	idx_src;

	idx_dst = 0;
	idx_src = 0;
	while (dst[idx_dst])
		idx_dst++;
	while (idx_src < len)
		dst[idx_dst++] = src[idx_src++];
	dst[idx_dst] = '\0';
}

char	*ft_substr(char *s1, size_t len)
{
	char	*ret;

	ret = malloc(sizeof(char) * (len + 1));
	if (!s1 || !ret || !(*s1))
		return (NULL);
	ret[len] = '\0';
	while (len--)
		ret[len] = s1[len];
	return (ret);
}

char	*ft_strjoin_free(char *s1, char *s2, size_t len)
{
	size_t	len1;
	size_t	len2;
	size_t	idx;
	char	*ret;

	if (!s1)
		return (ft_substr(s2, ft_strlen(s2)));
	if (!s2)
		return (s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	idx = 0;
	ret = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!ret)
		return (NULL);
	ret[idx] = '\0';
	ft_strcat(ret, s1, ft_strlen(s1));
	ft_strcat(ret, s2, len);
	free(s1);
	return (ret);
}
