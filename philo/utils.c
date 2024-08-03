/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euc <euc@student.42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:31:55 by euc               #+#    #+#             */
/*   Updated: 2024/07/14 20:48:49 by euc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *s)
{
	int		i;
	long	back;
	int		np;

	back = 0;
	np = 1;
	i = 0;
	while ((s[i] <= 13 && s[i] >= 9) || s[i] == 32)
		i++;
	if (s[i] == 43 || s[i] == 45)
	{
		if (s[i] == 45)
			np *= -1;
		i++;
	}
	while (s[i] >= 48 && s[i] <= 57)
	{
		back = back * 10 + (s[i] - 48) * np;
		if (back > 2147483647)
			return (-1);
		if (back < -2147483648)
			return (0);
		i++;
	}
	return ((int)back);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (!(str[i] >= 48 && str[i] <= 57))
		{
			printf("%s | Error ARG : %s\n", "this is not a number", str);
			return (0);
		}
		i++;
	}
	return (1);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000));
}

void	init_philo(t_data *data, int i)
{
	data->philos[i].id = i + 1;
	data->philos[i].data = data;
	data->philos[i].last_eat_time = get_time() - data->start_time;
	data->philos[i].eat_count = 0;
	data->philos[i].control = 0;
}

int	init_data(t_data *data)
{
	data->n_philo = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->must_eat = -1;
	data->is_dead = 0;
	data->start_time = get_time();
	data->print = malloc(sizeof(pthread_mutex_t));
	if (!data->print)
		return (free(data), 0);
	data->die_check = malloc(sizeof(pthread_mutex_t));
	if (!data->die_check)
		return (free(data->print), free(data), 0);
	return (1);
}
