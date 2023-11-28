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

char	*ft_mempcpy(
		char *dst,
		char const *src,
		size_t const len
		)
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

static void	rotate_tree(
		t_gnl_node *node,
		t_direction const dir
		)
{
	t_gnl_node	*successor;

	successor = node->child[dir ^ 1];
	if (successor != NULL)
	{
		node->child[dir ^ 1] = successor->child[dir];
		if (successor->child[dir] != NULL)
		{
			successor->child[dir]->parent = node;
		}
		successor->parent = node->parent;
		successor->child[dir] = node;
	}
	if (node->parent != NULL)
	{
		node->parent->child[node == node->parent->child[RIGHT]] = successor;
	}
	node->parent = successor;
}

static t_gnl_node	*get_rightmost(
		t_gnl_node *node
		)
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

t_gnl_node	*splay_tree(
		t_gnl_node *node,
		t_gnl_node **root_address
		)
{
	t_direction	dir;

	if (node->parent == NULL)
	{
		*root_address = node;
		return (node);
	}
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
	return (splay_tree(node, root_address));
}

void	*clear_node(
		t_gnl_node **node
		)
{
	t_gnl_node	**root_address;
	t_gnl_node	*childs[2];
	t_gnl_node	*successor;
	t_gnl_node	*to_delete;

	root_address = (*node)->root_address;
	to_delete = splay_tree(*node, root_address);
	childs[LEFT] = (*root_address)->child[LEFT];
	childs[RIGHT] = (*root_address)->child[RIGHT];
	successor = NULL;
	if (childs[LEFT] != NULL)
	{
		childs[LEFT]->parent = NULL;
		successor = get_rightmost(childs[LEFT]);
		splay_tree(successor, root_address);
		successor->child[RIGHT] = childs[RIGHT];
		*root_address = successor;
	}
	else
		*root_address = childs[RIGHT];
	if (childs[RIGHT] != NULL)
		childs[RIGHT]->parent = successor;
	free(to_delete->saved);
	free(to_delete);
	return (NULL);
}
