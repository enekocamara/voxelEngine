/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:14:05 by ecamara           #+#    #+#             */
/*   Updated: 2022/12/16 14:22:21 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sim.h"

t_couple	col_to_01(t_couple col)
{
	return (c_div(col, 255));
}

t_couple	col_to_255(t_couple col)
{
	return (c_mul(col, 255));
}
/*
t_couple	gamm_correction(t_couple col)
{
	double	ammount;

	ammount = GAMMA;
	col.x = pow(col.x, ammount);
	col.y = pow(col.y, ammount);
	col.z = pow(col.z, ammount);
	return (col);
}*/

t_couple	mix(t_couple col, t_couple col2, double grade)
{
	t_couple	result;

	result = vector(0, 0, 0);
	result.x = col.x * (1.0 - grade) + col2.x * grade;
	result.y = col.y * (1.0 - grade) + col2.y * grade;
	result.z = col.z * (1.0 - grade) + col2.z * grade;
	return (result);
}

int	convert_rgb(t_couple col)
{
	int	trgb;

	trgb = 0 << 24 | (int)col.x << 16 | (int)col.y << 8 | (int)col.z;
	return (trgb);
}

t_couple	int_to_col01(int temp)
{
	t_couple	col;

	col.x = (temp >> 16) & 0xFF;
	col.y = (temp >> 8) & 0xFF;
	col.z = temp & 0xFF;
	return (col);
}