/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bootup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:49:07 by ecamara           #+#    #+#             */
/*   Updated: 2022/12/10 15:51:32 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sim.h"

void	showFirstTime(t_data *data)
{
	printf( "This is a list of all the %skeywords%s you can use when terminal is active:\n", BLUE, RESET);
	showKeyWords(data);
	printf( "Write %schange input%s to set your input file\n", BLUE, RESET);
	terminal(data);
}

void	firstTime(t_data *data)
{
	printf("First time?(yes)(no)\n");
	if (yesNoQuestion())
		showFirstTime(data);
}

void	setMov(t_data *data)
{
	data->pause = 1;
	data->mov.f = 0;
	data->mov.b = 0;
	data->mov.l = 0;
	data->mov.r = 0;
	data->mov.u = 0;
	data->mov.d = 0;
	data->mov.ll = 0;
	data->mov.lr = 0;
	data->mov.lu = 0;
	data->mov.ld = 0;
	data->mov.speed = 10;
	data->mov.slow = 0;
	data->mov.fast = 0;
}

void	setConfig(t_data *data)
{
	data->config.blackhole.pos = point(50,50,50);
	data->config.blackhole.force = 100000;
	data->config.blackhole.active = 0;
	data->config.max = 6;
	data->config.gravityValue = 1;
	data->config.list[0] = "set blackhole force";
	data->config.list[1] = "set blackhole position";
	data->config.list[2] = "activate/deactivate blackhole";
	data->config.list[3] = "show config";
	data->config.list[4] = "show config keywords";
	data->config.list[5] = "change gravity";
	data->config.list[6] = "finish config";
	data->config.functs[0] = setBlackHoleForce;
	data->config.functs[1] = setBlackHolePos;
	data->config.functs[2] = activateDeactivateBlackhole;
	data->config.functs[3] = showConfig;
	data->config.functs[4] = showConfigKeyWords;
	data->config.functs[5] = changeGravity;
}

void	boot_up(t_data *data)
{
	init_mlx(data);
	setInput(data);
	setKeyWords(data);
	setMov(data);
	setConfig(data);
	create_threat(data);
	backeryStart(data);
	data->running = 0;
	printf( "%sGravity3d sim successfully started.%s\n\n", GREEN, RESET);
	firstTime(data);
	terminal(data);
}