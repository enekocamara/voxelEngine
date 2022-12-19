/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:40:10 by ecamara           #+#    #+#             */
/*   Updated: 2022/12/08 16:16:10 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sim.h"

void	free2d(char **str, int boo)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	if (boo)
		free(str);
}

int	yesNoQuestion(void)
{
	char	*temp;
	do
	{
		temp = getLine(1);
		if (ft_strcmp(temp, "yes"))
		{
			return (1);
		}
		else if (ft_strcmp(temp, "no"))
			return (0);
		else
			printf("	Not that difficult to answer\n");
		free(temp);
	} while (1);
}

void	printParticule(t_particule *particule)
{
	if (particule == NULL)
	{
		printf("EMPTY\n");
		return ;
	}
	printf("id: %d	pos: ", particule->id);
	c_print(particule->pos);
}

void	freeParticule(void *temp)
{
	free(temp);
}

void	printf_uv(t_uv uv)
{
	printf("[%lf][%lf]\n", uv.x, uv.y);
}