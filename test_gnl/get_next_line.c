/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:05:43 by chanhpar          #+#    #+#             */
/*   Updated: 2022/03/22 14:41:53 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*err_or_eof(char **rst, ssize_t count)
{
	if (count < 0)
	{
		free(*rst);
		*rst = NULL;
	}
	return (*rst);
}

void	ft_join_free(char **rst, char *buff, ssize_t len)
{
	char	*join;

	join = ft_strjoin(*rst, buff, len);
	free(*rst);
	*rst = join;
}

int	find_newline(char **rst, t_file *file)
{
	ssize_t	len;
	int		flag;

	len = 0;
	while (len < file->count && (file->buff)[len] != '\n')
		len++;
	flag = (len != file->count);
	if (flag)
		len++;
	ft_join_free(rst, file->buff, len);
	file->count -= len;
	ft_memmove(file->buff, (file->buff) + len, file->count);
	return (flag);
}

char	*get_next_line(int fd)
{
	static t_file	file;
	char			*rst;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	rst = NULL;
	while (1)
	{
		if (file.count == 0 && file.is_end == 0)
		{
			file.count = read(fd, file.buff, BUFFER_SIZE);
			if (file.count < BUFFER_SIZE)
				file.is_end = 1;
		}
		if (file.count <= 0)
			return (err_or_eof(&rst, file.count));
		if (find_newline(&rst, &file))
			break ;
	}
	return (rst);
}
