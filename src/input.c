/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:38:03 by ecamara           #+#    #+#             */
/*   Updated: 2022/12/09 15:31:49 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sim.h"

void	setParticule(t_particule *particule, char *str, int id)
{
	particule->pos = get_couple(str);
	particule->id = id;
}

void readFile(t_data *data, int fd, char *fileName)
{
	t_list *list;
	t_list *temp;
	char	*str;
	int		i;
	t_particule *particule;

	list = ft_lstnew(NULL);
	i = 0;
	do{
		str = getCleanLine(fd);
		if (str == NULL)
			break ;
		particule = malloc(sizeof(t_particule));
		setParticule(particule, str, i);
		temp = ft_lstnew(particule);
		if (temp == NULL)
		{
			printf("%sERROR%s malloc error when saving all data\n", RED, RESET);
			break ;
		}
		ft_lstadd_back(&list, temp);
		i++;
		printf("	%d particules set\r", i);
		free (str);
	}while(1);
	close (fd);
	if (data->input.tempFileList != NULL)
		ft_lstclear(&data->input.tempFileList, freeParticule);
	data->input.tempFileList = list;
	data->input.tempMax = ft_lstsize(data->input.tempFileList);
	if (data->input.tempFileName != NULL)
		free (data->input.tempFileName);
	data->input.tempFileName = fileName;
	printf("\n");
}

void	setInput(t_data *data)
{
	data->input.tempFileName = NULL;
	data->input.tempMax = 0;
	data->input.tempFileList = NULL;
	data->input.finalArray = NULL;
	data->input.finalMax = 0;
	data->input.cam.origin = point(10000,0,0);
	data->input.cam.direction = normalized(c_res(point(0,0,0), data->input.cam.origin));
	setAxisCam(data);
	data->input.cam.fov = tan(90 / 2);
	data->input.cam.ratio = WIDTH / (double)HEIGHT;
	data->input.cam.w = tan((data->input.cam.fov * M_PI / 360));
	data->input.cam.h = data->input.cam.w / WIDTH * HEIGHT;
}