/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 03:25:35 by chanhpar          #+#    #+#             */
/*   Updated: 2021/12/24 16:47:32 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int	main(void)
{
	static char	*str;
	int	i = 0;
	int	fd;

	fd = open("sample", O_RDONLY);
	while (i < 2)
	{
		str = get_next_line(fd);
		write(1, str, ft_strlen(str));
		i++;
	}
	free(str);	
	return (0);
}
