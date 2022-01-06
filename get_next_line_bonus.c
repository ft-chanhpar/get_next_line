/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 03:25:35 by chanhpar          #+#    #+#             */
/*   Updated: 2022/01/07 02:32:14 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

static int	ft_check(char **rst, t_file *file)
{
	ssize_t	len;
	char	*str;

	str = file->str;
	len = 0;
	while (len < file->cnt && str[len] != '\n')
		len++;
	if (len != file->cnt)
	{
		len++;
		ft_join_swap(str, rst, len);
		file->cnt -= len;
		ft_memmove(str, str + len, file->cnt);
		return (1);
	}
	else
	{
		ft_join_swap(str, rst, len);
		file->cnt = 0;
		return (0);
	}
}

char	*get_next_line(int fd)
{
	char			*rst;
	static t_file	allfile[FD_MAX + 1];
	static t_file	file;

	if (fd < 0 || fd > FD_MAX)
		return (NULL);
	file = allfile[fd];
	rst = NULL;
	while (1)
	{
		if (file.cnt == 0 && file.is_end == 0)
		{
			file.cnt = read(fd, file.str, BUFFER_SIZE);
			if (file.cnt < BUFFER_SIZE)
				file.is_end = 1;
		}
		if (file.cnt <= 0)
			return (ft_err_eof(&rst, file.cnt));
		if (ft_check(&rst, &file))
			break ;
	}
	return (rst);
}
