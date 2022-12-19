/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:25:06 by ecamara           #+#    #+#             */
/*   Updated: 2022/12/16 14:25:37 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sim.h"

void	*renderer()
{
	return (NULL);
}

void	render(t_data *data)
{
	int	i;

	i = 0;
	g_ids = 0;
	cubism(data);
	proyect(data);
	mlx_put_image_to_window(data->mlx.mlx,data->mlx.win, data->bakery.frames[data->bakery.index].img, 0, 0);
	//c_print(data->input.cam.origin);
	//c_print(data->input.cam.direction);
	if (!data->pause)
	{
		while (i < THREADS)
		{
			if (pthread_create(&data->mutex[i], NULL, &gravity,
					data) != 0)
				return ;
			i++;
		}
		i = -1;
		while (++i < THREADS)
			pthread_join(data->mutex[i], NULL);
	}
	//c_print(data->input.finalArray[0].pos);
	//destroyTree(data->tree);
}
/*
int	ft_eventspress(int keycode, t_data *data)
{
	//printf("[%d]\n", keycode);
	if (keycode == 36)
		terminal(data);
	else if (keycode == 125)
		data->framerate.slow = 1;
	else if (keycode == 126)
		data->framerate.fast = 1;
	else if (keycode == 49)
		data->bakery.index = 0;
	return (0);
}*//*

int	ft_eventsrealese(int keycode, t_data *data)
{
	if (keycode == 125)
		data->framerate.slow = 0;
	else if (keycode == 126)
		data->framerate.fast = 0;
	return (0);
}*/

void	cleanImg(t_img *img)
{
	int	i;
	int	j;

	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			img->add[(int)j * WIDTH + (int)i] = 0;
			i++;
		}
		j++;
	}
}

int	cycle(t_data *data)
{
	//printf("cycle\n");
	//c_print(data->input.cam.origin);
	//c_print(data->input.cam.direction);
	//c_print(data->input.cam.direction);
	//c_print(data->input.cam.origin);
	if (data->mov.f)
		data->input.cam.origin = c_sum(data->input.cam.origin,
				c_mul(data->input.cam.direction, data->mov.speed));
	if (data->mov.b)
		data->input.cam.origin = c_res(data->input.cam.origin,
				c_mul(data->input.cam.direction, data->mov.speed));
	if (data->mov.r)
		data->input.cam.origin = c_sum(data->input.cam.origin,
				c_mul(data->input.cam.right, data->mov.speed));
	if (data->mov.l)
		data->input.cam.origin = c_res(data->input.cam.origin,
				c_mul(data->input.cam.right, data->mov.speed));
	if (data->mov.d)
		data->input.cam.origin = c_res(data->input.cam.origin,
				c_mul(data->input.cam.up, data->mov.speed));
	if (data->mov.u)
		data->input.cam.origin = c_sum(data->input.cam.origin,
				c_mul(data->input.cam.up, data->mov.speed));
	if (data->mov.ll)
		data->input.cam.direction = normalized(c_sum(
					c_mul(c_mul(data->input.cam.right, -1), 0.01),
					data->input.cam.direction));
	if (data->mov.lr)
		data->input.cam.direction = normalized(c_sum(
					c_mul(data->input.cam.right, 0.01),
					data->input.cam.direction));
	if (data->mov.ld)
		data->input.cam.direction = normalized(c_sum(
					c_mul(c_mul(data->input.cam.up, -1), 0.01),
					data->input.cam.direction));
	if (data->mov.lu)
		data->input.cam.direction = normalized(c_sum(
					c_mul(data->input.cam.up, 0.01),
					data->input.cam.direction));
	if (data->mov.ll || data->mov.ld || data->mov.lu || data->mov.lr)
		setAxisCam(data);
	if (data->framerate.fast)
		data->framerate.usleep += 1000;
	if (data->framerate.slow)
		data->framerate.usleep -= 1000;
	if (data->mov.slow && data->mov.speed > 5)
		data->mov.speed -= 5;
	if (data->mov.fast)
		data->mov.speed += 5;
	/*if (BAKED)
	{
		data->bakery.index++;
		if (data->bakery.index == FRAMES)
			data->bakery.backed = 1;
		if (!data->bakery.backed && data->bakery.index < FRAMES)
		{
			system("clear");
			printf("[%lf]\n", data->bakery.index / (double)FRAMES);
			render(data);
		//	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->bakery.frames[data->bakery.index].img,0,0);
		}
		else
		{
			if (data->time)
			{
				gettimeofday(&data->later, NULL);
				printf("[%lf]\n", ft_to_sec(data->later) - ft_to_sec(data->now));
				data->time = 0;
			}
			if (data->bakery.index >= FRAMES)
				data->bakery.index = 0;
			if (data->framerate.fast)
				data->framerate.usleep += 1000;
			if (data->framerate.slow)
				data->framerate.usleep -= 1000;
			mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->bakery.frames[data->bakery.index].img,0,0);
			usleep(data->framerate.usleep);
			data->bakery.index++;
		}
	}
	*/
	render(data);
	//bloom(&data->bakery.frames[data->bakery.index], &data->bakery.bloom);
	//conbineTwoImages(&data->bakery.frames[data->bakery.index], &data->bakery.bloom, 0.1);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->bakery.frames[data->bakery.index].img, 0,0);
	cleanImg(&data->bakery.frames[data->bakery.index]);
	//cleanImg(&data->bakery.bloom);
	destroyTree(data->tree);
	return (0);
}


int	ft_eventspress(int keycode, void *temp)
{
	t_data *data = temp;
	printf("[%d]\n", keycode);
	if (keycode == 13)
		data->mov.f = 1;
	else if (keycode == 1)
		data->mov.b = 1;
	else if (keycode == 2)
		data->mov.r = 1;
	else if (keycode == 0)
		data->mov.l = 1;
	else if (keycode == 9)
		data->mov.d = 1;
	else if (keycode == 49)
		data->mov.u = 1;
	else if (keycode == 49)
		data->mov.u = 1;
	else if (keycode == 123)
		data->mov.ll = 1;
	else if (keycode == 124)
		data->mov.lr = 1;
	else if (keycode == 125)
		data->mov.ld = 1;
	else if (keycode == 126)
		data->mov.lu = 1;
	else if (keycode == 12)
	{
		if (data->pause == 0)
			data->pause = 1;
		else
			data->pause = 0;
	}
	else if (keycode == 15)
		data->mov.fast = 1;
	else if (keycode == 14)
		data->mov.slow = 1;
	else if (keycode == 78)
		data->framerate.slow = 1;
	else if (keycode == 69)
		data->framerate.fast = 1;
	else if (keycode == 36)
		terminal(data);
	else
		return (0);
	return (0);
}

int	ft_eventsrealese(int keycode, void *temp)
{
	t_data *data = temp;
	if (keycode == 13)
		data->mov.f = 0;
	else if (keycode == 1)
		data->mov.b = 0;
	else if (keycode == 2)
		data->mov.r = 0;
	else if (keycode == 0)
		data->mov.l = 0;
	else if (keycode == 9)
		data->mov.d = 0;
	else if (keycode == 49)
		data->mov.u = 0;
	else if (keycode == 123)
		data->mov.ll = 0;
	else if (keycode == 124)
		data->mov.lr = 0;
	else if (keycode == 125)
		data->mov.ld = 0;
	else if (keycode == 126)
		data->mov.lu = 0;
	else if (keycode == 15)
		data->mov.fast = 0;
	else if (keycode == 14)
		data->mov.slow = 0;
	else if (keycode == 78)
		data->framerate.slow = 0;
	else if (keycode == 69)
		data->framerate.fast = 0;
	return (0);
}

void	startSimulation(t_data *data)
{
	(void)data;
	printf("%sRunning simulation%s\n", GREEN, RESET);
	data->running = 1;
	data->pause = 1;
	mlx_hook(data->mlx.win, 2, 1L << 0, ft_eventspress, data);
	mlx_hook(data->mlx.win, 3, 1L << 0, ft_eventsrealese, data);
	mlx_loop_hook(data->mlx.mlx, cycle, data);
	mlx_loop(data->mlx.mlx);
	
}