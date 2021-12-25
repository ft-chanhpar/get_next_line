/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 03:25:35 by chanhpar          #+#    #+#             */
/*   Updated: 2021/12/26 01:28:27 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_err_eof(char **rst, ssize_t cnt)
{
	if (cnt < 0)
	{
		free(*rst);
		*rst = NULL;
	}
	return (*rst);
}

static void	ft_join_swap(char *str, char **rst, ssize_t len)
{
	char	*join;

	join = ft_strjoin(*rst, str, len);
	free(*rst);
	*rst = join;
}

static int	ft_check(char *str, char **rst, ssize_t *cnt)
{
	ssize_t	len;

	len = 0;
	while (len < *cnt && str[len] != '\n')
		len++;
	if (len != *cnt)
	{
		len++;
		ft_join_swap(str, rst, len);
		*cnt -= len;
		ft_memmove(str, str + len, *cnt);
		return (1);
	}
	else
	{
		ft_join_swap(str, rst, len);
		*cnt = 0;
		return (0);
	}
}

char	*get_next_line(int fd)
{
	char			*rst;
	static ssize_t	cnt;
	static char		str[BUFFER_SIZE + 1];

	if (fd < 0)
		return (NULL);
	rst = NULL;
	while (1)
	{
		if (cnt == 0)
			cnt = read(fd, str, BUFFER_SIZE);
		if (cnt <= 0)
			return (ft_err_eof(&rst, cnt));
		if (ft_check(str, &rst, &cnt))
			break ;
	}
	return (rst);
}
