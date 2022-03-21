/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:31:10 by chanhpar          #+#    #+#             */
/*   Updated: 2022/03/21 18:38:23 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE];
	char		*ret;
	ssize_t		read_return;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	ret = NULL;
	while (!ft_strchr(buff, '\n', ft_strlen(buff)))
	{
		ret = ft_strjoin_free(ret, buff);
		read_return = read(fd, buff, BUFFER_SIZE);
		if (read_return < 0)
			return (NULL);
		buff[read_return] = '\0';
	}
	ret = parse_str(buff);
	return (ret);
}
