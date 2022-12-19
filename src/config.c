/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:15:53 by ecamara           #+#    #+#             */
/*   Updated: 2022/12/10 15:51:36 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sim.h"

void	setBlackHoleForce(t_data *data)
{
	char *str;
	do
	{
		printf("\tIntroduce new value(int): ");
		str = getLine(0);
		printf("\tNew blackhole force = %d. Continue(yes) or change again(no)\n\t", atoi(str));
		if (yesNoQuestion())
		{
			data->config.blackhole.force = atoi(str);
			free (str);
			break ;
		}
		free (str);
	} while (1);
}

void	setBlackHolePos(t_data *data)
{
	char *str;
	t_couple	temp;

	do
	{
		printf("\tIntroduce new value(int): ");
		str = getLine(0);
		printf("\tNew blackhole pos = ");
		temp = get_couple(str);
		c_print(temp);
		printf("\tContinue(yes) or change again(no)\n\t");
		if (yesNoQuestion())
		{
			data->config.blackhole.pos = temp;
			free(str);
			break ;
		}
		free (str);
	} while (1);
}

void	activateDeactivateBlackhole(t_data *data)
{
	if (data->config.blackhole.active)
	{
		printf("\tDo you want to deactivate blackhole?(yes)(no)\n\t");
		if (yesNoQuestion())
			data->config.blackhole.active = 0;
	}
	else
	{
		printf("\tDo you want to activate blackhole?(yes)(no)\n\t");
		if (yesNoQuestion())
			data->config.blackhole.active = 1;
	}
	
}

void	showConfigKeyWords(t_data *data)
{
	int	i;

	i = 0;
	while(i < data->config.max)
	{
		printf("\t*	%s%s%s\n", BLUE, data->config.list[i], RESET);
		i++;
	}
	printf("\n");
}

void	checkConfig(t_data *data, char *str)
{
	int	i;
	int	check;

	i = 0;
	check = 1;
	while (i < data->config.max)
	{
		if (ft_strcmp(data->config.list[i], str))
		{
			check = 0;
			data->config.functs[i](data);
		}
		i++;
	}
	if (check)
	{
		printf("%s is not a keyword. Type %sshow config keywords%s to print a list of the available keywords.\n", str, BLUE, RESET);
	}
}

void	changeGravity(t_data *data)
{
	char *str;
	do
	{
		printf("\tIntroduce new value(double): ");
		str = getLine(0);
		printf("\tNew gravity value = %lf. Continue(yes) or change again(no)\n\t", ft_atoi_double(str));
		if (yesNoQuestion())
		{
			data->config.gravityValue = ft_atoi_double(str);
			free (str);
			break ;
		}
		free (str);
	} while (1);
}