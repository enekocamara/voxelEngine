/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubism.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:04:23 by ecamara           #+#    #+#             */
/*   Updated: 2022/12/10 16:48:16 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sim.h"

int	selectCube(t_node *node, t_particule *particule)
{
	if (particule->pos.x >= node->center.x && particule->pos.x < node->maxXYZ.x)
	{
		if (particule->pos.y >= node->center.y && particule->pos.y < node->maxXYZ.y)
		{
			if (particule->pos.z >= node->center.z && particule->pos.z < node->maxXYZ.z)
				return (0);
			else if (particule->pos.z < node->center.z && particule->pos.z >= node->minXYZ.z)
				return (1);
		}
		else if (particule->pos.y < node->center.y && particule->pos.y >= node->minXYZ.y)
		{
			if (particule->pos.z >= node->center.z && particule->pos.z < node->maxXYZ.z)
				return (4);
			else if (particule->pos.z < node->center.z && particule->pos.z >= node->minXYZ.z)
				return (5);
		}
	}
	else if (particule->pos.x < node->center.x && particule->pos.x >= node->minXYZ.x)
	{
		if (particule->pos.y >= node->center.y && particule->pos.y < node->maxXYZ.y)
		{
			if (particule->pos.z >= node->center.z && particule->pos.z < node->maxXYZ.z)
				return (2);
			else if (particule->pos.z < node->center.z && particule->pos.z >= node->minXYZ.z)
				return (3);
		}
		else if (particule->pos.y < node->center.y && particule->pos.y >= node->minXYZ.y)
		{
			if (particule->pos.z >= node->center.z && particule->pos.z < node->maxXYZ.z)
				return (6);
			else if (particule->pos.z < node->center.z && particule->pos.z >= node->minXYZ.z)
				return (7);
		}
	}
	return (-1);
}

t_node *placeNode(t_node *node, t_particule *particule)
{
	int	nodeId;

	nodeId = selectCube(node, particule);
	if (nodeId != -1)
	{
		node->last = 0;
		if (node->next[nodeId] != NULL)
			return (node->next[nodeId]);
		if (nodeId == 0)
			node->next[nodeId] = newNode(node->maxXYZ, node->center);
		else if(nodeId == 1)
			node->next[nodeId] = newNode(point(node->maxXYZ.x, node->maxXYZ.y, node->center.z), point(node->center.x, node->center.y, node->minXYZ.z));
		else if (nodeId == 2)
			node->next[nodeId] = newNode(point(node->center.x, node->maxXYZ.y, node->maxXYZ.z), point(node->minXYZ.x, node->center.y, node->center.z));
		else if (nodeId == 3)
			node->next[nodeId] = newNode(node->center, point(node->minXYZ.x, node->center.y, node->minXYZ.z));
		else if (nodeId == 4)
			node->next[nodeId] = newNode(point(node->maxXYZ.x, node->center.y, node->maxXYZ.z), point(node->center.x, node->minXYZ.y, node->center.z));
		else if (nodeId == 5)
			node->next[nodeId] = newNode(point(node->maxXYZ.x, node->center.y, node->center.z), point(node->center.x, node->minXYZ.y, node->minXYZ.z));
		else if (nodeId == 6)
			node->next[nodeId] = newNode(point(node->center.x, node->center.y, node->maxXYZ.z), point(node->minXYZ.x, node->minXYZ.y, node->center.z));
		else if (nodeId == 7)
			node->next[nodeId] = newNode(node->center, node->minXYZ);
		return (node->next[nodeId]);
	}
	return (NULL);
}

void	placeParticule(t_data *data, t_node *node, t_particule *particule, int level)
{
	
	if (node == NULL)
		return ;
	node->level = level;
	if (!node->last)
	{
		node->mass++;
		placeParticule(data, placeNode(node, particule), particule, level * 2);
	}
	else if (node->last && node->mass != 0 && node->level <= 10000)
	{
		node->mass++;
		//newBranch(node);
		t_list *temp = node->particule;
		while (temp != NULL)
		{
			placeParticule(data, placeNode(node, temp->content), temp->content, 2 * level);
			temp = temp->next;
		}
		freeList(node->particule);
		node->particule = NULL;
		placeParticule(data, placeNode(node,particule), particule, level * 2);
		node->id = -1;
	}
	else if(node->last && (node->mass == 0 || node->level > 10000))
	{
		node->mass++;
		if (node->particule->content == NULL)
			node->particule->content = particule;
		else
			ft_lstadd_back(&node->particule, ft_lstnew(particule));
	}
}

void	cubism(t_data *data)
{
	int	i;

	data->tree = newTree();
	i = 0;
	data->tree->level = 2;
	//printf("[%d]\n", data->input.finalMax);
	while (i < data->input.finalMax - 1)
	{
		placeParticule(data, data->tree, &data->input.finalArray[i], 2);
		i++;
	}
}