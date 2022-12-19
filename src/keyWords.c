/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyWords.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:51:12 by ecamara           #+#    #+#             */
/*   Updated: 2022/12/10 15:53:25 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sim.h"

void	checkKeyWords(t_data *data, char *temp)
{
	int	i;
	int	check;

	i = 0;
	check = 1;
	while (i < data->keyWords.max)
	{
		if (ft_strcmp(data->keyWords.list[i], temp))
		{
			check = 0;
			data->keyWords.functs[i](data);
		}
		i++;
	}
	if (check)
	{
		printf("%s is not a keyword. Type check %sshow keywords%s to print a list of the available keywords.\n", temp, BLUE, RESET);
	}
}

void	showKeyWords(t_data *data)
{
	int	i;

	i = 0;
	while(i < data->keyWords.max)
	{
		printf("*	%s%s%s\n", BLUE, data->keyWords.list[i], RESET);
		i++;
	}
	printf("\n");
}

void	setKeyWords(t_data *data)
{
	data->keyWords.max = 12;
	data->keyWords.list[0] = "exit";
	data->keyWords.list[1] = "run";
	data->keyWords.list[2] = "show keywords";
	data->keyWords.list[3] = "show config";
	data->keyWords.list[4] = "show temp input";
	data->keyWords.list[5] = "show final input";
	data->keyWords.list[6] = "change config";
	data->keyWords.list[7] = "change temp input";
	data->keyWords.list[8] = "change final input";
	data->keyWords.list[9] = "quick start";
	data->keyWords.list[10] = "null speed";
	data->keyWords.list[11] = "close terminal";
	data->keyWords.functs[0] = closeProgram;
	data->keyWords.functs[1] = runSimulation;
	data->keyWords.functs[2] = showKeyWords;
	data->keyWords.functs[3] = showConfig;
	data->keyWords.functs[4] = showTempInput;
	data->keyWords.functs[5] = showFinalInput;
	data->keyWords.functs[6] = changeConfig;
	data->keyWords.functs[7] = changeTempInput;
	data->keyWords.functs[8] = changeFinalInput;
	data->keyWords.functs[9] = quickStart;
	data->keyWords.functs[10] = nullSpeed;
}

void	terminal(t_data *data)
{
	char *temp;
	while (1)
	{
		temp = getLine(0);
		if (ft_strcmp(temp, "close terminal"))
		{
			if (data->running)
			{
				free (temp);
				break ;
			}
			else
				printf("\tOnly when simulator is running\n");
		}
		else
			checkKeyWords(data, temp);
		free(temp);
	}
}
