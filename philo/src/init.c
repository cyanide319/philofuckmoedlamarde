/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeaudoi <tbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:53:51 by tbeaudoi          #+#    #+#             */
/*   Updated: 2022/12/19 18:22:48 by tbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_thread(t_rules *rules)
{
	int	i;

	i = -1;
	rules->fll_flag = false;
	while (++i < rules->nb_philo)
	{
		pthread_create(&rules->philo[i].p_t, NULL,
			routine, &rules->philo[i]);
		usleep(100);
	}
	pthread_create(&rules->death_watch, NULL, reaping, (void *)rules);
	if (rules->eat_flag == true)
	{
		pthread_create(&rules->weight_watcher, NULL, feasting, (void *)rules);
	}
	return ;
}

time_t	init_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	init_wait_time(t_rules *rules, int wait)
{
	time_t	time;

	time = init_time() + wait - rules->start_time;
	while ((init_time() - rules->start_time) < time)
		usleep(50);
}

t_bool	init_philo(t_rules *rules)
{
	int	i;
	int	j;

	i = -1;
	j = 1;
	while (++i < rules->nb_philo)
	{
		rules->philo[i].rules = rules;
		rules->philo[i].id = j;
		rules->philo[i].forks.left = i;
		if (pthread_mutex_init(&rules->mute_forks[i], NULL) != 0)
			return (error_quit(4));
		if (j == rules->nb_philo)
			rules->philo[i].forks.right = 0;
		else
			rules->philo[i].forks.right = j;
		rules->philo[i].nb_eat = -1;
		rules->philo[i].last_eat = 0;
		j++;
	}
	return (true);
}

t_bool	init_rules(t_rules	*rules, int argc, char **argv)
{
	rules->dth_flag = false;
	rules->nb_philo = ft_atol(argv[1]);
	if (rules->nb_philo > 200)
		return (error_quit(3));
	rules->tm_to_die = ft_atol(argv[2]);
	rules->tm_to_eat = ft_atol(argv[3]);
	rules->tm_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		rules->nb_of_eat = ft_atol(argv[5]);
		rules->eat_flag = true;
	}
	else
		rules->eat_flag = false;
	rules->start_time = init_time();
	if (pthread_mutex_init(&rules->mute_write, NULL) != 0)
		return (error_quit(4));
	if (pthread_mutex_init(&rules->mute_death, NULL) != 0)
		return (error_quit(4));
	if (pthread_mutex_init(&rules->mute_time, NULL) != 0)
		return (error_quit(4));
	if (pthread_mutex_init(&rules->mute_eat, NULL) != 0)
		return (error_quit(4));
	return (init_philo(rules));
}
