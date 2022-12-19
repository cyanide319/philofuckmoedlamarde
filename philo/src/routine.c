/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeaudoi <tbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:53:55 by tbeaudoi          #+#    #+#             */
/*   Updated: 2022/12/19 15:26:35 by tbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_bool	check_dead(t_rules *rules)
{
	pthread_mutex_lock(&rules->mute_death);
	if (rules->dth_flag == true)
	{
		pthread_mutex_unlock(&rules->mute_death);
		return (true);
	}
	pthread_mutex_unlock(&rules->mute_death);
	return (false);
}

void	*reaping(void *arg)
{
	t_rules	*rules;
	int		i;

	rules = (t_rules *)arg;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&rules->mute_time);
		if ((init_time() - rules->start_time) - rules->philo[i].last_eat
			> rules->tm_to_die)
		{
			pthread_mutex_lock(&rules->mute_death);
			if (rules->dth_flag == true)
				return (0);
			rules->dth_flag = true;
			pthread_mutex_unlock(&rules->mute_death);
			printf("%ld %d is dead\n", (init_time() - rules->start_time),
				rules->philo[i].id);
			return (0);
		}
		pthread_mutex_unlock(&rules->mute_time);
		i = (i + 1) % rules->nb_philo;
	}
	return (0);
}

void	*feasting(void *arg)
{
	t_rules		*rules;
	int			i;
	static int	j = 0;

	rules = (t_rules *)arg;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&rules->mute_eat);
		if (rules->philo[i].nb_eat == rules->nb_of_eat)
			j++;
		pthread_mutex_unlock(&rules->mute_eat);
		if (j == rules->nb_philo && rules->dth_flag == false)
		{
			pthread_mutex_lock(&rules->mute_death);
			rules->dth_flag = true;
			pthread_mutex_unlock(&rules->mute_death);
			pthread_mutex_lock(&rules->mute_write);
			printf("Fuckers are full.\n");
			pthread_mutex_unlock(&rules->mute_write);
			return (0);
		}
		i = (i + 1) % rules->nb_philo;
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep (200);
	while (1)
	{
		if (eat(philo) == false)
			return (0);
		if (fucking_sleep(philo) == false)
			return (0);
		if (think(philo) == false)
			return (0);
	}
	return (0);
}

void	*one_philo_fuck_it(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	pthread_mutex_lock(&philo->rules->mute_forks[philo->forks.left]);
	print_output(philo, LF);
	init_wait_time(philo->rules, philo->rules->tm_to_die);
	philo->rules->dth_flag = true;
	pthread_mutex_lock(&philo->rules->mute_write);
	printf("%ld %d is dead\n", (init_time() - philo->rules->start_time),
		philo->id);
	pthread_mutex_unlock(&philo->rules->mute_write);
	pthread_mutex_unlock(&philo->rules->mute_forks[philo->forks.left]);
	return (0);
}
