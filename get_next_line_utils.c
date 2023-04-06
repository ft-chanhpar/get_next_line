/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:23:34 by chanhpar          #+#    #+#             */
/*   Updated: 2023/04/06 14:54:33 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

t_node		*skew_or_split(t_node *const node, t_oper const oper);
void		*clear_node(t_node *node, t_node *parent);
char		*ft_mempcpy(char *dst, char const *src, size_t const len);

static t_node	*get_leaf_addr(t_node *const node, t_direction const dir)
{
	if (node->childs[dir] != NULL)
	{
		return (get_leaf_addr(node->childs[dir], dir));
	}
	else
	{
		return (node);
	}
}

t_node	*skew_or_split(t_node *const node, t_oper const oper)
{
	t_direction const	dir = (oper == SPLIT);
	t_node *const		child = node->childs[dir];
	int const			flag = (oper == SPLIT) \
								&& child != NULL \
								&& child->childs[RIGHT] != NULL \
								&& child->childs[RIGHT]->level == node->level;

	if (flag)
		++child->level;
	if (flag || (oper == SKEW && child != NULL && child->level == node->level))
	{
		node->childs[dir] = child->childs[dir ^ 1];
		if (child->childs[dir ^ 1])
			child->childs[dir ^ 1]->parent = node;
		child->childs[dir ^ 1] = node;
		child->parent = node->parent;
		node->parent = child;
	}
	if (oper == SKEW)
		return (skew_or_split(child, SPLIT));
	if (child->parent != NULL)
		return (skew_or_split(child->parent, SKEW));
	return (child);
}

/* next = get_leaf_addr(&(*node)->childs[(*node)->childs[LEFT] == NULL], \
 * LEFT); */

void	*clear_node(t_node *node, t_node *parent)
{
	t_node	*tmp;
	t_node	*next;
	t_node	*next_parent;

	if (node->childs[LEFT] == NULL) // leaf case
	{
		if (parent == NULL)
			*(node->root_addr) = node->childs[RIGHT];
		else
			parent->childs[node == parent->childs[RIGHT]] = node->childs[RIGHT];
		if (node->childs[RIGHT] != NULL)
			node->childs[RIGHT]->parent = parent;
		free(node->saved);
		free(node);
		/* decrease_level(); */
		return (NULL);
	}
	/* next->childs[RIGHT] == NULL, next->childs[LEFT] == NULL */
	next = get_leaf_addr(node->childs[LEFT], RIGHT);
	next_parent = next->parent;
	if (next_parent == node)
	{
		if (parent == NULL)
			*(node->root_addr) = next;
		else
			parent->childs[node == parent->childs[RIGHT]] = next;
		next->parent = parent;
		next->childs[RIGHT] = node->childs[RIGHT];
		if (node->childs[RIGHT] != NULL)
			node->childs[RIGHT]->parent = next;
		free(node->saved);
		free(node);
		/* decrease_level(); */
		return (NULL);
	}
	else
	{
		if (parent == NULL)
			*(node->root_addr) = next;
		else
			parent->childs[node == parent->childs[RIGHT]] = next;
		next->parent = parent;
		next->childs[RIGHT] = node->childs[RIGHT];
		if (node->childs[RIGHT] != NULL)
			node->childs[RIGHT]->parent = next;
		next->childs[LEFT] = node->childs[LEFT];
		if (node->childs[LEFT] != NULL)
			node->childs[LEFT]->parent = next;
		next_parent->childs[RIGHT] = NULL;
		free(node->saved);
		free(node);
		/* decrease_level(); */
		return (NULL);
	}
}

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
