/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:23:34 by chanhpar          #+#    #+#             */
/*   Updated: 2023/03/29 22:00:00 by chanhpar         ###   ########.fr       */
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

static void	rotate_tree(t_node *node, t_direction const dir)
{
	t_node	*successor;

	successor = node->child[dir ^ 1];
	if (successor != NULL)
	{
		node->child[dir ^ 1] = successor->child[dir];
		if (successor->child[dir] != NULL)
			successor->child[dir]->parent = node;
		successor->parent = node->parent;
		successor->child[dir] = node;
	}
	if (node->parent != NULL)
		node->parent->child[node == node->parent->child[RIGHT]] = successor;
	node->parent = successor;
}

static t_node	*get_rightmost(t_node *node)
{
	if (node->child[RIGHT] != NULL)
	{
		return (get_rightmost(node->child[RIGHT]));
	}
	else
	{
		return (node);
	}
}

t_node	*splay_tree(t_node *node)
{
	t_direction	dir;

	if (node->parent == NULL)
		return (node);
	dir = (node == node->parent->child[RIGHT]);
	if (node->parent->parent == NULL)
	{
		rotate_tree(node->parent, dir ^ 1);
	}
	else if (dir == (node->parent == node->parent->parent->child[RIGHT]))
	{
		rotate_tree(node->parent->parent, dir ^ 1);
		rotate_tree(node->parent, dir ^ 1);
	}
	else
	{
		rotate_tree(node->parent, dir ^ 1);
		rotate_tree(node->parent, dir);
	}
	return (splay_tree(node));
}

void	*clear_node(t_node **node)
{
	t_node	*root;
	t_node	*childs[2];
	t_node	*successor;

	root = splay_tree(*node);
	childs[LEFT] = root->child[LEFT];
	childs[RIGHT] = root->child[RIGHT];
	successor = NULL;
	if (childs[LEFT] != NULL)
	{
		childs[LEFT]->parent = NULL;
		successor = get_rightmost(childs[LEFT]);
		splay_tree(successor);
		if (childs[RIGHT] != NULL)
			successor->child[RIGHT] = childs[RIGHT];
	}
	if (childs[RIGHT] != NULL)
	{
		childs[RIGHT]->parent = successor;
	}
	free(root->saved);
	free(root);
	return (NULL);
}
