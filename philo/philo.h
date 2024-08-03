/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euc <euc@student.42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:59:18 by euc               #+#    #+#             */
/*   Updated: 2024/08/01 17:56:53 by euc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	int				control;
	long long		eat_count;
	long long		last_eat_time;
	pthread_t		philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	long long		n_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		must_eat;
	int				is_dead;
	long long		start_time;
	int				err;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*die_check;
	t_philo			*philos;
}					t_data;
int			init_data(t_data *data);
void		init_philo(t_data *data, int i);
long long	get_time(void);
void		*routine(void *arg);
int			ft_isdigit(char *str);
int			ft_atoi(const char *s);
int			dead_check(t_philo *philo);
void		prts(t_philo *philo, long long time, char *status);
void		check_control(t_philo *philo);
void		prnt_fork(t_philo *philo);
#endif
