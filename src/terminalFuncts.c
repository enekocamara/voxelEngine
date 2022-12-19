/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminalFuncts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:02:47 by ecamara           #+#    #+#             */
/*   Updated: 2022/12/10 15:47:49 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sim.h"

void	closeProgram(t_data *data)
{
	if (data->input.tempFileName)
		free (data->input.tempFileName);
	if (data->input.tempFileList)
		ft_lstclear(&data->input.tempFileList, freeParticule);
	exit (0);
}

void	runSimulation(t_data *data)
{
	if (data->input.finalArray == NULL)
	{
		printf("\tNo final input set. Do you want to countinue?(yes)(no)\n");
		if (yesNoQuestion())
			startSimulation(data);
	}
	else
		startSimulation(data);
}

void	showConfig(t_data *data)
{
	(void)data;
	printf("Current config:\n");
}

void	showTempInput(t_data *data)
{
	(void)data;
	t_list	*temp;

	printf("   Current temporal input:\n");
	printf("\tFile name: %s\n\tNumber of particules: %d\n", data->input.tempFileName, data->input.tempMax);
	printf("\tDo you want to see the particules values?(yes)(no)\n");
	if (yesNoQuestion())
	{
		temp = data->input.tempFileList;
		while(temp != NULL)
		{
			printf("\t\t");
			printParticule(temp->content);
			temp = temp->next;
		}
	}
}

void	showFinalInput(t_data *data)
{
	int	i;

	printf("   Current final input:\n");
	printf("\tFile name: %s\n\tNumber of particules: %d\n", data->input.finalFileName, data->input.finalMax);
	printf("\tDo you want to see the particules values?(yes)(no)\n");
	if (yesNoQuestion())
	{
		i = 0;
		while (i < data->input.finalMax)
		{
			printf("\t\t");
			printParticule(&data->input.finalArray[i]);
			i++;
		}
	}
}

void	changeConfig(t_data *data)
{
	char *str;
	
	printf("\tType %sshow config keywords%s for all conmands\n", BLUE, RESET);
	do
	{
		str = getLine(1);
		if (ft_strcmp(str, "finish config"))
		{
			free (str);
			break ;
		}
		else
			checkConfig(data, str);
		free (str);
	}while (1);
}

void	changeTempInput(t_data *data)
{
	char	*temp;
	int		fd;

	(void)data;
	printf("	Write path to input file:\n");
	do{
		temp = getLine(1);
		if (ft_strcmp("continue", temp))
		{
			break ;
		}
		fd = open (temp, O_RDONLY);
		if (fd < 0)
		{
			printf("	%sERROR%s input file doesn't exist. Try again or write %scontinue%s to cancel %schangeInput%s\n", RED, RESET, BLUE, RESET, BLUE, RESET);
		}
		else
		{
			printf("	%sSUCCESS%s, reading file...\n", GREEN, RESET);
			readFile(data, fd, temp);
			dup2(STDIN_FILENO, 1);
			break ;
		}
	}while (1);
}

void transferParticule(t_particule *particule1, t_particule *particule2)
{
	particule1->id = particule2->id;
	particule1->pos = particule2->pos;
	particule1->u = point(0,0,0);
}

void	setAxisCam(t_data *data)
{
	t_couple	temp_up;

	if (data->input.cam.direction.y == 1
		&& data->input.cam.direction.x == 0
		&& data->input.cam.direction.z == 0)
		temp_up = vector(0, 0, -1);
	else if (data->input.cam.direction.y == -1
		&& data->input.cam.direction.x == 0
		&& data->input.cam.direction.z == 0)
		temp_up = vector(0, 0, 1);
	else
		temp_up = vector(0, 1, 0);
	data->input.cam.right = c_mul(normalized(cross(
					data->input.cam.direction, temp_up)), -1);
	data->input.cam.up = c_mul(normalized(cross(
					data->input.cam.right,
					data->input.cam.direction)), -1);
}
/*
void	set_camera(t_data *data, char *line)
{
	char		**values;
	static int	i;
	t_cam	*temp;

	temp = (t_cam *)malloc(sizeof(t_cam));
	if (!i)
		i = 0;
	values = ft_split_str(line, " 	");
	data->shapes.cam[i] = temp;
	data->shapes.cam[i]->origin = get_couple(values[1]);
	data->shapes.cam[i]->direction = normalized(get_couple(values[2]));
	data->shapes.cam[i]->fov = ft_atoi_double(values[3]);
	data->shapes.cam[i]->ratio = WIDTH / (double)HEIGH;
	data->shapes.cam[i]->w = tan((data->shapes.cam[i]->fov * M_PI / 360));
	data->shapes.cam[i]->h = data->shapes.cam[i]->w / WIDTH * HEIGH;
	set_axis_cam(data, i);
	i++;
}*/

void	setCam(t_data *data)
{
	char *temp;
	do{
		printf("Introuduce initial position: ");
		temp = getLine(1);
		data->input.cam.origin = get_couple(temp);
		printf("\tCurrent camera position: ");
		c_print(data->input.cam.origin);
		printf(	"\tContinue with camera customization or retry?(Yes)continue(no)retry?\n");
		if (yesNoQuestion())
		{
			break ;
		}
	}while(1);
	do{
		printf("Introuduce where the cam is pointing: ");
		temp = getLine(1);
		data->input.cam.direction = normalized(c_res(get_couple(temp), data->input.cam.origin));
		printf("\tCurrent camera direction: ");
		c_print(data->input.cam.direction);
		printf("\tcontinue with camera customization or retry?(Yes)continue(no)retry?\n");
		if (yesNoQuestion())
		{
			setAxisCam(data);
			data->input.cam.fov = tan(90 / 2);
			data->input.cam.ratio = WIDTH / (double)HEIGHT;
			data->input.cam.w = tan((data->input.cam.fov * M_PI / 360));
			data->input.cam.h = data->input.cam.w / WIDTH * HEIGHT;
			break ;
		}
	}while(1);
}

void	transferFinalInput(t_data *data)
{
	int	i;
	t_list *temp;

	if (data->input.finalArray)
		free(data->input.finalArray);
	data->input.finalMax = data->input.tempMax;
	data->input.finalFileName = ft_strdup(data->input.tempFileName);
	data->input.finalArray = malloc(sizeof(t_particule) * data->input.finalMax);
	if (!data->input.finalArray)
	{
		printf("%s ERROR%s Final array malloc couldn't be reserved", RED, RESET);
		free (data->input.finalFileName);
		data->input.finalFileName = NULL;
		data->input.finalMax = 0;
		return ;
	}
	i = 0;
	temp = data->input.tempFileList->next;
	while(i < data->input.finalMax && temp != NULL)
	{
		transferParticule(&data->input.finalArray[i], temp->content);
		i++;
		temp = temp->next;
		printf("%d particules changed\r", i);
	}
	printf("\n");
}

void	changeFinalInput(t_data *data)
{
	if (data->input.tempFileName == NULL)
	{
		printf("%sERROR%s Set a temporal input first\n", RED, RESET);
		return ;
	}
	printf("Set camera?(yes)(no)\n");
	if (yesNoQuestion())
		setCam(data);
	printf("\tTransfer temp input to final input. Final input will be lost forever. Do you want to transfer?(yes)(no)\n");
	if (yesNoQuestion())
	{
		transferFinalInput(data);
	}
}

void	quickStart(t_data *data)
{
	changeTempInput(data);
	transferFinalInput(data);
	runSimulation(data);
}

void	nullSpeed(t_data *data)
{
	int	i = 0;

	while (i < data->input.finalMax - 1)
	{
		data->input.finalArray[i].u = vector(0,0,0);
		i++;
	}
}