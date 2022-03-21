/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:31:10 by chanhpar          #+#    #+#             */
/*   Updated: 2022/03/22 02:53:07 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*parse_str(char *ret, char *buff)
{
	size_t	find_newline;
	size_t	offset;
	size_t	idx;

	find_newline = ft_strchr(buff, '\n', ft_strlen(buff));
	offset = find_newline;
	if (!find_newline)
		offset = ft_strlen(buff);
	ret = ft_strjoin_free(ret, buff, offset);
	idx = 0;
	while (buff[idx + offset])
	{
		buff[idx] = buff[idx + offset];
		idx++;
	}
	buff[idx] = '\0';
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*ret;
	ssize_t		read_return;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	ret = NULL;
	while (!ft_strchr(buff, '\n', ft_strlen(buff)))
	{
		ret = ft_strjoin_free(ret, buff, ft_strlen(buff));
		read_return = read(fd, buff, BUFFER_SIZE);
		if (read_return < 0)
			return (NULL);
		buff[read_return] = '\0';
		if (read_return < BUFFER_SIZE)
			break ;
	}
	ret = parse_str(ret, buff);
	return (ret);
}
