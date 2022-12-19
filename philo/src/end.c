/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeaudoi <tbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:49:05 by tbeaudoi          #+#    #+#             */
/*   Updated: 2022/12/19 15:06:55 by tbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	close_threads(t_rules *rules)
{
	int	i;

	i = 0;
	pthread_join(rules->death_watch, NULL);
	while (i < rules->nb_philo)
	{
		pthread_join(rules->philo[i].p_t, NULL);
		i++;
	}
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&rules->mute_forks[i]);
		i++;
	}
	if (rules->eat_flag == true)
		pthread_join(rules->weight_watcher, NULL);
	pthread_mutex_destroy(&rules->mute_write);
	pthread_mutex_destroy(&rules->mute_death);
	pthread_mutex_destroy(&rules->mute_time);
}
