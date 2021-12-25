/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 03:26:09 by chanhpar          #+#    #+#             */
/*   Updated: 2021/12/25 17:34:12 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_static
{
	char	str[BUFFER_SIZE + 1];
	ssize_t	cnt;
}	t_static;

size_t	ft_strlen(const char *str);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, size_t len);
char	*ft_strjoin(char const *s1, char const *s2, size_t len);

char	*get_next_line(int fd);

void	get_next_line_utils(void);

#endif
