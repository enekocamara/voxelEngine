/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:55:22 by ecamara           #+#    #+#             */
/*   Updated: 2022/12/09 12:51:04 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sim.h"

t_node	*newNode(t_couple maxXYZ, t_couple minXYZ)
{
	t_node *new;
	//static int i;


	//if (!i)
	//	i = 0;
	//i++;
	//printf("node = [%d]\n", i);
	new = malloc(sizeof(t_node));
	new->last = 1;
	new->particule = ft_lstnew(NULL);
	new->mass = 0;
	new->id	= -1;
	new->level = -1;
	new->maxXYZ = maxXYZ;
	new->minXYZ =  minXYZ;
	new->center = point((maxXYZ.x + minXYZ.x) / 2, (maxXYZ.y + minXYZ.y) / 2, (maxXYZ.z + minXYZ.z) / 2);
	new->next[0] = NULL;
	new->next[1] = NULL;
	new->next[2] = NULL;
	new->next[3] = NULL;
	new->next[4] = NULL;
	new->next[5] = NULL;
	new->next[6] = NULL;
	new->next[7] = NULL;
	return (new);
}
/*
void	newBranch(t_node *node)
{
	node->last = 0;
	node->next[0] = newNode(uv(node->center.x, node->topRight.y), uv(node->botLeft.x, node->center.y));
	node->next[1] = newNode(node->topRight, node->center);
	node->next[2] = newNode(node->center, node->botLeft);
	node->next[3] = newNode(uv(node->topRight.x, node->center.y), uv(node->center.x, node->botLeft.y));
}*/

t_node *newTree(void)
{
	t_node *new;

	new = newNode(point(MAX_X, MAX_Y, MAX_Z), point(MIN_X, MIN_Y, MIN_Z));
	//newBranch(new);
	return (new);
}

void	destoyNode(t_node *node)
{
	if (!node->last)
	{
		free(node->next[0]);
		free(node->next[1]);
		free(node->next[2]);
		free(node->next[3]);
	}
	free(node);
}

void	destroyTree(t_node *node)
{
	if (!node->last)
	{
		if (node->next[0])
			destroyTree(node->next[0]);
		if (node->next[1])
			destroyTree(node->next[1]);
		if (node->next[2])
			destroyTree(node->next[2]);
		if (node->next[3])
			destroyTree(node->next[3]);
		if (node->next[4])
			destroyTree(node->next[4]);
		if (node->next[5])
			destroyTree(node->next[5]);
		if (node->next[6])
			destroyTree(node->next[6]);
		if (node->next[7])
			destroyTree(node->next[7]);
	}
	free(node);
}

void	*multiDestroyTree(void	*temp)
{
	t_node *node;
	node = temp;
	destroyTree(node);
	return (NULL);
}
/*
void	multiDestroyTreeLaunch(t_data *data)
{
	int	i;

	i = 0;
	g_ids = 0;
	while (i < 4)
	{
		if (pthread_create(&data->mutex[i], NULL, &multiDestroyTree,
				data->tree->next[i]) != 0)
			return ;
		i++;
	}
	i = -1;
	while (++i < 4)
		pthread_join(data->mutex[i], NULL);
	g_ids = 0;
}*/

void	freeList(t_list *list)
{
	t_list *temp;

	if (list == NULL)
		return ;
	temp = list->next;
	if (list != NULL)
	free(list);
	while (temp != NULL)
	{
		list = temp->next;
		free(temp);
		temp = list;
	}
}