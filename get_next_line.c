/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 03:25:35 by chanhpar          #+#    #+#             */
/*   Updated: 2021/12/25 17:08:40 by chanhpar         ###   ########.fr       */
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
	char	*temp;
	char	*join;

	temp = ft_substr(str, 0, len);
	join = ft_strjoin(*rst, temp);
	free(*rst);
	*rst = join;
	free(temp);
	temp = NULL;
}

static int	ft_check(char *str, char **rst, ssize_t *cnt)
{
	ssize_t	len;

	len = 0;
	while (str[len] != '\n' && len < *cnt)
		len++;
	if (len != *cnt)
	{
		len++;
		ft_join_swap(str, rst, len);
		ft_memmove(str, str + len, *cnt - len + 1);
		*cnt -= len;
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
	static char		str[BUFFER_SIZE + 1];
	char			*rst;
	static ssize_t	cnt;

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
