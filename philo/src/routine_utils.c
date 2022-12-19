/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeaudoi <tbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:57:50 by tbeaudoi          #+#    #+#             */
/*   Updated: 2022/12/19 15:05:19 by tbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_bool	print_output(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->rules->mute_write);
	pthread_mutex_lock(&philo->rules->mute_death);
	if (philo->rules->dth_flag == true)
	{
		pthread_mutex_unlock(&philo->rules->mute_death);
		pthread_mutex_unlock(&philo->rules->mute_write);
		return (false);
	}
	pthread_mutex_unlock(&philo->rules->mute_death);
	printf("%ld %d %s\n", (init_time() - philo->rules->start_time),
		philo->id, str);
	pthread_mutex_unlock(&philo->rules->mute_write);
	return (true);
}

t_bool	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->mute_forks[philo->forks.left]);
	if (print_output(philo, LF) == false)
	{
		pthread_mutex_unlock(&philo->rules->mute_forks[philo->forks.left]);
		return (false);
	}
	pthread_mutex_lock(&philo->rules->mute_forks[philo->forks.right]);
	if (print_output(philo, RF) == false)
		return (double_unlock_pas_propre(philo));
	pthread_mutex_lock(&philo->rules->mute_time);
	philo->last_eat = init_time() - philo->rules->start_time;
	pthread_mutex_unlock(&philo->rules->mute_time);
	pthread_mutex_lock(&philo->rules->mute_eat);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->rules->mute_eat);
	if (print_output(philo, EAT) == false)
		return (double_unlock_pas_propre(philo));
	init_wait_time(philo->rules, philo->rules->tm_to_eat);
	pthread_mutex_unlock(&philo->rules->mute_forks[philo->forks.left]);
	pthread_mutex_unlock(&philo->rules->mute_forks[philo->forks.right]);
	return (true);
}

t_bool	double_unlock_pas_propre(t_philo *philo)
{
	pthread_mutex_unlock(&philo->rules->mute_forks[philo->forks.left]);
	pthread_mutex_unlock(&philo->rules->mute_forks[philo->forks.right]);
	return (false);
}

t_bool	fucking_sleep(t_philo *philo)
{
	if (print_output(philo, SLP) == false)
		return (false);
	init_wait_time(philo->rules, philo->rules->tm_to_sleep);
	return (true);
}

t_bool	think(t_philo *philo)
{
	if (print_output(philo, THK) == false)
		return (false);
	return (true);
}
