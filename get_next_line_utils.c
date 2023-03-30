/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:23:34 by chanhpar          #+#    #+#             */
/*   Updated: 2023/03/30 16:53:34 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

char	*ft_mempcpy(char *dst, char const *src, size_t const len)
{
	if (len != 0)
	{
		*dst = *src;
		return (ft_mempcpy(dst + 1, src + 1, len - 1));
	}
	else
	{
		return (dst);
	}
}

void	*clear_node(t_node **node)
{
	t_node	*left;
	t_node	*right;
	t_node	*next;

	if (*node == NULL)
		return (NULL);
	left = (*node)->childs[LEFT];
	right = (*node)->childs[RIGHT];
	if (left == NULL && right == NULL)
	{
		free((*node)->saved);
		free(*node);
		*node = NULL;
	}
	else if (left == NULL)
	{
		next = get_leaf_node(right, LEFT);
	}
	return (NULL);
}

t_node	**append_data(t_node **node, char *buffer)
{
	if ((*node)->read_len == 0)
		return (node);
	--(*node)->read_len;
	if (*buffer == '\n')
	{
		(*node)->line_que[(*node)->que_tail++] = (*node)->end;
		(*node)->que_tail %= QUE_SIZE;
	}
	(*node)->saved[(*node)->end++] = *buffer;
	return (append_data(node, buffer + 1));
}

t_node	*split_or_skew(t_node *node, t_oper oper)
{
	t_node	*child;

	if (oper == SPLIT && node->childs[RIGHT] && \
		node->childs[RIGHT]->childs[RIGHT] && \
		node->childs[RIGHT]->childs[RIGHT]->level == node->level)
	{
		child = node->childs[RIGHT];
		node->childs[RIGHT] = child->childs[LEFT];
		child->childs[LEFT] = node;
		++child->level;
	}
	else if (oper == SKEW && \
			node->childs[LEFT] && \
			node->childs[LEFT]->level == node->level)
	{
		child = node->childs[LEFT];
		node->childs[LEFT] = child->childs[RIGHT];
		child->childs[RIGHT] = node;
	}
	else
	{
		return (node);
	}
	return (child);
}

t_node	*get_leaf_node(t_node *node, t_direction dir)
{
	if (node->childs[dir])
	{
		return (get_leaf_node(node->childs[dir], dir));
	}
	else
	{
		return (node);
	}
}

char	*parse_line(t_node **node)
{
	char	*string;
	size_t	len;

	if ((*node)->is_eof)
	{
		len = (*node)->end - (*node)->begin;
		if (len == 0)
			return (clear_node(node));
	}
	else
	{
		len = (*node)->line_que[(*node)->que_head++] - (*node)->begin + 1;
		(*node)->que_head %= QUE_SIZE;
	}
	string = malloc(sizeof(char) * (len + 1));
	if (string == NULL)
		return (clear_node(node));
	*ft_mempcpy(string, (*node)->saved + (*node)->begin, len) = '\0';
	(*node)->begin += len;
	return (string);
}
