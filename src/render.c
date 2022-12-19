/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:38:31 by ecamara           #+#    #+#             */
/*   Updated: 2022/12/16 14:24:12 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sim.h"

int	proyectPixel(t_data *data, t_particule *particule, t_uv *ans)
{
	t_couple vec = normalized(c_res(particule->pos, data->input.cam.origin));
	double	t;
	double	angle_r;
	double	angle_up;

	t = dot(vec, data->input.cam.direction);
	//printf("[%lf]", t);
	if (t > 0)
	{
		t = 1 / t;
		if (t > 0)
		{
			t_couple point = c_sum(c_mul(vec, t), data->input.cam.origin);
			t_couple help = c_res(point, c_sum(data->input.cam.direction, data->input.cam.origin));
			//printf("nice\n");
			//c_print(point);
			//c_print(help);
			if (help.x == 0 && help.y == 0 && help.z == 0)
			{
				angle_r = 0;
				angle_up = 0;
			}
			else
			{
				angle_r = dot(data->input.cam.right, normalized(help));
				angle_up = dot(data->input.cam.up, normalized(help));
			}
			double right_help = len(help) * angle_r;
			double up_help = len(help) * angle_up;
			//printf("[%lf][%lf]\n", right_help, up_help);
			/*if (angle_r < 0)
				right_help *= -1;
			if (angle_up < 0)
				up_help *= -1;*/
			if (up_help > 1 || up_help < -1)
				return (0);
			//printf("[%lf][%lf]\n", right_help, up_help);
			if (right_help > data->input.cam.fov || right_help < -data->input.cam.fov)
				return (0);
			ans->x = ((right_help / data->input.cam.fov) + 1) / 2 * WIDTH;
			//printf("w[%lf]", ans->x);
			//printf_uv(uv(right_help, up_help));
			ans->y = (1 - ((up_help + 1) / 2)) * HEIGHT;
			//printf_uv(*ans);
			//printf("end\n");
			//printf("success\n");
			return (1);
		}
	}
	return (0);
}

void	proyect(t_data *data)
{
	int	i;
	t_uv	pos;

	i = 0;
	while (i < data->input.finalMax - 1)
	{
		pos.x = 0;
		pos.y = 0;
		//printf("hola\n");
		if (proyectPixel(data, &data->input.finalArray[i],&pos))
		{
		//	printf("hola\n");
			int col = 0x0000FF + convert_rgb(vector(clamp(0, 255, len(data->input.finalArray[i].u) * 10), 0, 0));
			data->bakery.frames[data->bakery.index].add[(int)clamp(0, WIDTH * HEIGHT - 1, (int)pos.y * WIDTH + (int)pos.x)] += col;
		}
		i++;
	}/*
	int j;

	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			if (j == 650)
				data->bakery.frames[data->bakery.index].add[j * WIDTH + i] += 20;
			i++;
		}
		j++;
	}*/
}

void	bloom(t_img *img1, t_img *img2)
{
	int	i;
	int	j;
	int	check;

	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while(i < WIDTH)
		{
			check = 0;
			if (j > 0)//up
			{
				img2->add[j * WIDTH + i] += img1->add[(j - 1)* WIDTH + i];
				check++;
			}
			if (j < HEIGHT - 1)//down
			{
				img2->add[j * WIDTH + i] += img1->add[(j + 1) * WIDTH + i];
				check++;
			}
			if (i > 0) // left
			{
				img2->add[j * WIDTH + i] += img1->add[j * WIDTH + i + 1];
				check++;
			}
			if (i < WIDTH - 1) // right
			{
				img2->add[j * WIDTH + i] += img1->add[j* WIDTH + i - 1];
				check++;
			}
			if (j > 0 && i > 0) // up left
			{
				img2->add[j * WIDTH + i] += img1->add[(j - 1)* WIDTH + i + 1];
				check++;
			}
			if (j > 0 && j < WIDTH - 1) // up right
			{
				img2->add[j * WIDTH + i] += img1->add[(j - 1)* WIDTH + i - 1];
				check++;
			}
			if (j < HEIGHT - 1 && i > 0) //down left
			{
				img2->add[j * WIDTH + i] += img1->add[(j + 1) * WIDTH + i + 1];
				check++;
			}
			if (j < HEIGHT - 1 && i < WIDTH - 1) // down right
			{
				img2->add[j * WIDTH + i] += img1->add[(j + 1) * WIDTH + i - 1];
				check++;
			}
			img2->add[j * WIDTH + i] += img1->add[j * WIDTH + i];
			if (check)
				img2->add[j * WIDTH + i] /= check + 1;
			i++;
		}
		j++;
	}
}

void	conbineTwoImages(t_img *img1, t_img *img2, double value)
{
	int	i;
	int	j;

	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while(i < WIDTH)
		{
		//	img1->add[j * WIDTH + i] += img2->add[j * WIDTH + i] * value;
			img1->add[j * WIDTH + i] = convert_rgb(col_to_255(mix(int_to_col01(img1->add[j * WIDTH + i]), int_to_col01(img2->add[j * WIDTH + i]), value)));
			i++;
		}
		j++;
	}
}

/*
void	in_plane(t_intersect *intersect, t_ray ray, t_plane *plane)
{
	double	t;

	t = dot(ray.direction, plane->normal);
	if (t != 0)
	{
		t = dot(c_res(plane->origin, ray.origin), plane->normal) / t;
		if (t > 0 && (t < intersect->t || intersect->t == 0))
		{
			ray.t = t;
			get_in_pl(intersect, plane, ray);
		}
	}
}*/