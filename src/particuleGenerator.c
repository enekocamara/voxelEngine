/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particuleGenerator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:26:28 by ecamara           #+#    #+#             */
/*   Updated: 2022/12/09 12:36:18 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sim.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

int	random_number(int max)
{
	return (rand() % max);
}
/*
void	sea(int maxx, int minx, int maxy, int miny)
{
	double x;
	double	y;
	x = random_number(maxx + minx) - minx;
	y = random_number(maxy + miny) - miny;
	printf("%lf,%lf ", x, y);
}*/

void	grid(int x, int y, int i, int num)
{
	double	radious = 5;
	double	step;
	
	step = 1;
	printf("%lf,%lf ", (double)(x + (i % (int)sqrt(num)) * 1), y + (double)(i / sqrt(num)) * 1);
}


void	sea(int maxx, int minx, int maxy, int miny, int maxz, int minz)
{
	double x;
	double	y;
	double	z;
	x = random_number(maxx + minx) - minx;
	y = random_number(maxy + miny) - miny;
	z = random_number(maxz + minz) - minz;
	printf("%lf,%lf,%lf ", x, y, z);
}

int	main()
{
	int i;
	int	num = 50000;
	i = 0;
	int fd;
	fd = open("../particules", O_WRONLY);
	dup2(fd, STDOUT_FILENO);
	while(i < num)
	{
		sea(100,0,100,0,100,0);
		printf("\n");
		//sea(WIDTH, 0, HEIGH, 0);
		//grid(WIDTH / 2 - 50, HEIGH / 2 - 50, i, num);
		
		i++;
	}/*
	i = 8000;
	while(i < num)
	{
		sea(0,-500,0,-500,0,-500);
		printf("\n");
		//sea(WIDTH, 0, HEIGH, 0);
		//grid(WIDTH / 2 - 50, HEIGH / 2 - 50, i, num);
		
		i++;
	}*/
	
}