/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:31:19 by chanhpar          #+#    #+#             */
/*   Updated: 2022/03/21 17:52:50 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
