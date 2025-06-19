#include "philos.h"

static void	ph_print(char *print, t_philo *philo, t_data *data);
static void	ph_take_forks_eat(t_data *data, t_philo *philo);
static void	ph_prep_meal(t_philo *philo);
static void	ph_think_sleep(t_philo *philo);

void	run_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (philo->data->start_ms > ph_time_to_ms())
		usleep(500);
	ph_print(THINKING, philo, philo->data);
	if (philo->data->ph_count == 1)
	{
		solo_philo(philo);
		return ;
	}
	philo->last_meal = philo->data->start_ms;
	if (philo->index % 2 != 0 && philo->data->ph_count > 1)
		usleep((philo->data->eat_ms / 4) * 1000);
	while (!philo->data->dead)
	{
		if (philo->data->dead)
			return ;
		ph_prep_meal(philo);
		if (philo->data->dead)
			return ;
		ph_think_sleep(philo);
	}
}

static void	ph_print(char *print, t_philo *philo, t_data *data)
{
	long	current_time;

	pthread_mutex_lock(&data->print_lock);
	current_time = ph_time_to_ms() - data->start_ms;
	if (!data->dead && data->sated < data->ph_count)
		printf("%ld %zu %s\n", current_time, philo->index, print);
	pthread_mutex_unlock(&data->print_lock);
}

static void	ph_think_sleep(t_philo *philo)
{
	t_data	*data;
	long	current_time;

	data = philo->data;
	ph_print(SLEEPING, philo, data);
	current_time = ph_time_to_ms();
	while (ph_time_to_ms() - current_time < data->sleep_ms)
	{
		if (data->dead)
			break ;
		usleep(500);
	}
	ph_print(THINKING, philo, data);
	if (philo->data->ph_count % 2 != 0
		&& ph_time_to_ms() - philo->last_meal > data->sleep_ms)
		usleep(250);
}

static void	ph_prep_meal(t_philo *philo)
{
	t_data	*data;
	long	current_time;

	data = philo->data;
	ph_take_forks_eat(data, philo);
	if (data->ph_count == 1)
		return ;
	philo->last_meal = ph_time_to_ms();
	current_time = ph_time_to_ms();
	while (ph_time_to_ms() - current_time < data->eat_ms
		&& (!data->dead || data->sated != data->ph_count))
		usleep(500);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->meals_eaten++;
}

static void	ph_take_forks_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ph_print(FORKING, philo, data);
	pthread_mutex_lock(philo->l_fork);
	ph_print(FORKING, philo, data);
	ph_print(EATING, philo, data);
	/*
	if (philo->index % 2 != 0)
	{
		pthread_mutex_lock(philo->l_fork);
		ph_print(FORKING, philo, data);
		pthread_mutex_lock(philo->r_fork);
		ph_print(FORKING, philo, data);
		ph_print(EATING, philo, data);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		ph_print(FORKING, philo, data);
		pthread_mutex_lock(philo->l_fork);
		ph_print(FORKING, philo, data);
		ph_print(EATING, philo, data);
	}
	*/
}
