/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:35:16 by raisufaj          #+#    #+#             */
/*   Updated: 2025/10/08 12:46:11 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_number(char *str)
{
	size_t	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647)
			return (-1);
		i++;
	}
	return (result * sign);
}

void	destroy_all(t_program *program, pthread_mutex_t *forks, char *message)
{
	int	i;

	if (message)
		printf("Error: %s\n", message);
	if (program->philos)
	{
		i = 0;
		while (i < program->philos->num_of_philos)
		{
			pthread_mutex_destroy(&forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->write_lock);
}

// Sleeps half the remaining time per step: ms-precise, but only ~log2(ms)
// wakeups per call, so 200 sleeping threads don't flood the scheduler.
// Steps are capped at 0.5s: macOS usleep() rejects values >= 1s.
int	ft_usleep(size_t time_in_ms)
{
	size_t	start;
	size_t	elapsed;

	start = get_current_time();
	elapsed = 0;
	while (elapsed < time_in_ms)
	{
		if (time_in_ms - elapsed > 1000)
			usleep(500000);
		else
			usleep((time_in_ms - elapsed) * 500);
		elapsed = get_current_time() - start;
	}
	return (0);
}

// Convert the time into milliseconds
size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (size_t)1000) + (time.tv_usec / 1000));
}
