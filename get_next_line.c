/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 03:25:35 by chanhpar          #+#    #+#             */
/*   Updated: 2021/12/25 03:48:36 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	str[BUFFER_SIZE];
	char		*temp;
	char		*join;
	char		*rst;
	static ssize_t		cnt;
	ssize_t		len;

	if (fd < 0)
		return (NULL);
	temp = NULL;
	rst = ft_strdup("");
	while (1)
	{
		if (str[0] == '\0')
			cnt = read(fd, str, BUFFER_SIZE);
		if (cnt < 0)
			return (NULL);
		if (cnt == 0)
			return (rst);
		len = 0;
		while (str[len] != '\n' && len < cnt)
			len++;
		if (len++ != cnt)
		{
			temp = ft_substr(str, 0, len);
			join = ft_strjoin(rst, temp);
			free(rst);
			rst = join;
			free(temp);
			temp = NULL;
			cnt -= len;
			ft_memmove(str, str + len, cnt);
			break ;
		}
		else
		{
			temp = ft_substr(str, 0, len);
			join = ft_strjoin(rst, temp);
			free(rst);
			rst = join;
			free(temp);
			temp = NULL;
			str[0] = '\0';
		}
	}
	return (rst);
}
