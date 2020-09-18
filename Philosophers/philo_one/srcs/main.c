/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 09:00:36 by user42            #+#    #+#             */
/*   Updated: 2020/09/16 11:27:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void initKeys(t_global *global)
{
    int i;

    i = 0;
    if (!(global->keys = malloc(sizeof(pthread_mutex_t) * global->nb_philos)))
        return ;
    while (i < global->nb_philos)
    {
        pthread_mutex_init(&global->keys[i], NULL);
        pthread_mutex_unlock(&global->keys[i]);
        i++;
    }
}

int initGobal(char **str, int ac, t_global *global)
{
    global->maxeats = (ac == 5) ? -1 : ft_atoi(str[5]);
    global->threads = 0;
    global->die = 0;
    if ((ac == 6 && global->maxeats <= 0) || (global->nb_philos = ft_atoi(str[1])) <= 0
    || (global->time_to_die = ft_atoi(str[2])) <= 0
    || (global->time_to_eat = ft_atoi(str[3])) <= 0 || (global->time_to_sleep = ft_atoi(str[4])) <= 0)
    {
        ft_putstr("Error : launch correctly the program !\n", 2);
        return (0);
    }
    if (!(global->philos = malloc((sizeof(t_philo) * global->nb_philos))))
    {
        ft_putstr("Error : malloc problem !\n", 2);
        return (0);
    }
    pthread_mutex_init(&global->talk, NULL);
    pthread_mutex_unlock(&global->talk);
    initKeys(global);
    return (1);
}

void    ft_tmessage(int type)
{
    if (type == 1)
        ft_putstr(" is launch !\n", 1);
    else if (type == 2)
        ft_putstr(" is die !\n", 1);
    else if (type == 3)
        ft_putstr(" is eating !\n", 1);
    else if (type == 4)
        ft_putstr(" is sleeping ! \n", 1);
    
}
/*
void    ft_messages(int id, long int timestamp, t_global *global, char *message)
{
    if (pthread_mutex_lock(&global->talk) == 0)
    {
        ft_putnbr(timestamp);
        ft_putstr(" ", 1);
        ft_putnbr(id);
        ft_putstr(" ", 1);
        ft_putstr(message, 1);
        ft_putchar('\n', 1);
        pthread_mutex_unlock(&global->talk);
    }
}*/

void    ft_eat(t_philo *philo, long int timestamp, t_global *global)
{
    int i;

    i = 0;
    i = (philo->id == 0) ? global->nb_philos - 1 : -1 ;
    if (pthread_mutex_lock(&global->keys[philo->id]) == 0 && pthread_mutex_lock(&global->keys[philo->id + i]) == 0)
    {
        ft_messages2(philo->id, timestamp, global, "is eating !");
        philo->last_eat = get_time(0);
        ft_sleep(global->time_to_eat);
        pthread_mutex_unlock(&global->keys[philo->id]);
        pthread_mutex_unlock(&global->keys[philo->id + i]);
    }
}


void    ft_sleeping(t_philo *philo, long int timestamp, t_global *global)
{
        ft_messages2(philo->id, timestamp, global, "is sleeping !");
        ft_sleep(global->time_to_sleep);
}

void    *ft_jobs(void *global)
{
    t_global    *info;
    long int    time;
    int         i;
 
    info = (t_global*)global;
    i = info->threads;
    info->philos[i].id = info->threads;
    ft_messages2(i, 0, info, "was launch");
    info->philos[i].t_start = get_time(0);
    while (info->die == 0)
    {
        time = get_time(info->philos[i].t_start);
        ft_eat(&info->philos[i], time, info);
        ft_sleeping(&info->philos[i], time, info);
        ft_messages2(info->philos[i].id, time, global, "is thinking !");
        if (get_time(info->philos[i].last_eat) > info->time_to_die)
        {
            ft_messages2(info->philos[i].id, time, global, "is die !");
            info->die += 1;
        }
    }
    return (global);
}

void    ft_core(t_global *global)
{
    int i;
    pthread_t   tid;

    i = 0;
    while (i < global->nb_philos)
    {
        if (pthread_create(&tid, NULL, ft_jobs, global) != 0)
            return ;
        pthread_detach(tid);
        global->threads += 1;
        ft_sleep(10);
        i++;
    }
}

int     main(int ac, char **av)
{ 
    if (ac == 5 || ac == 6)
    {
        t_global global;
        if (initGobal(av, ac, &global) == 0)
            return (0);
        ft_core(&global);
        while (global.die == 0);
        return (1);
    }
    ft_putstr("Error : launch correctly the program !\n", 2);
    return (1);
}