/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeaudoi <tbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:52:11 by tbeaudoi          #+#    #+#             */
/*   Updated: 2022/12/16 15:03:23 by tbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_bool	error_quit(int code)
{
	write (2, "Error\n", 6);
	if (code == 1)
		printf("Bad input.\n");
	if (code == 2)
		printf("4 args + 1 optional.\n");
	if (code == 3)
		printf("Too many philo.\n");
	if (code == 4)
		printf("Problem occured with mutex creation.\n");
	return (false);
}

t_bool	check_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

t_bool	check_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (i == 4)
			return (false);
		i++;
	}
	return (true);
}

t_bool	check_range(long input)
{
	if (input < 1)
		return (false);
	return (true);
}

t_bool	check_errors(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (check_digits(argv[i]) == false
			|| check_len(argv[i]) == false
			|| check_range(ft_atol(argv[i])) == false)
			return (error_quit(1));
		i++;
	}
	return (true);
}
