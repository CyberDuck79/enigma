/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enigma_conf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 18:16:21 by fhenrion          #+#    #+#             */
/*   Updated: 2020/01/05 09:12:32 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enigma.h"

static t_error	next_token(char **str, char c)
{
	while (**str && **str != c)
		(*str)++;
	if (!**str)
		return (ERROR);
	(*str)++;
	return (NO_ERROR);
}

static t_error	check_rotor_nb(int *rotor, int nb)
{
	if (rotor[nb] < 0 || rotor[nb] > 7)
		return (ERROR);
	if (nb > 0 && rotor[1] == rotor[0])
		return (ERROR);
	if (nb > 1 && (rotor[2] == rotor[0] || rotor[2] == rotor[1]))
		return (ERROR);
	return (NO_ERROR);
}

static void		copy_rotor(const int **rotors, int i, int *rotor)
{
	memcpy(rotor, rotors[i], sizeof(int) * 26);
}

// inverser le sens d'entree des rotors
static t_error	parse_rotors(t_conf *conf, char **str)
{
	int	rotor_nb[3] = {0};

	rotor_nb[0] = atoi(*str) - 1;
	if (check_rotor_nb(rotor_nb, 0) || next_token(str, '-'))
		return (ERROR);
	copy_rotor(ROTORS, rotor_nb[0], conf->rotor[0][0]);
	copy_rotor(R_ROTORS, rotor_nb[0], conf->rotor[0][1]);
	rotor_nb[1] = atoi(*str) - 1;
	if (check_rotor_nb(rotor_nb, 1) || next_token(str, '-'))
		return (ERROR);
	copy_rotor(ROTORS, rotor_nb[1], conf->rotor[1][0]);
	copy_rotor(R_ROTORS, rotor_nb[1], conf->rotor[1][1]);
	rotor_nb[2] = atoi(*str) - 1;
	if (check_rotor_nb(rotor_nb, 2) || next_token(str, '-'))
		return (ERROR);
	copy_rotor(ROTORS, rotor_nb[2], conf->rotor[2][0]);
	copy_rotor(R_ROTORS, rotor_nb[2], conf->rotor[2][1]);
	if (**str == 'B')
		copy_rotor(REFLECTORS, 0, conf->reflector);
	else if (**str == 'C')
		copy_rotor(REFLECTORS, 1, conf->reflector);
	else
		return (ERROR);
	return (next_token(str, '-'));
}

static t_error	check_position(int position)
{
	if (position < 0 || position > 25)
		return (ERROR);
	return (NO_ERROR);
}

static t_error	parse_positions(t_conf *conf, char **str)
{
	conf->position[0] = (**str - 65);
	if (check_position(conf->position[0]) || next_token(str, '-'))
		return (ERROR);
	conf->position[1] = (**str - 65);
	if (check_position(conf->position[1]) || next_token(str, '-'))
		return (ERROR);
	conf->position[2] = (**str - 65);
	if (check_position(conf->position[2]) || next_token(str, '-'))
		return (ERROR);
	return (NO_ERROR);
}

static t_error	check_wire(t_conf *conf, char *str)
{
	size_t	i = 0;

	while (conf->wires[0][i])
	{
		if (*str == conf->wires[0][i] || *str == conf->wires[1][i])
			return (ERROR);
		i++;
	}
	return (NO_ERROR);
}

static t_error	parse_wire(t_conf *conf, char **str, size_t wire_nb)
{
	if (check_wire(conf, *str))
		return (ERROR);
	conf->wires[0][wire_nb] = **str;
	if (next_token(str, '/'))
		return (ERROR);
	if (check_wire(conf, *str))
		return (ERROR);
	conf->wires[1][wire_nb] = **str;
	next_token(str, '-');
	return (NO_ERROR);
}

static t_error	parse_wires(t_conf *conf, char **str)
{
	size_t	i = 0;

	bzero(conf->wires[0], 13);
	bzero(conf->wires[1], 13);
	while (**str >= 'A' && **str <= 'Z' && i < 13)
	{
		if (parse_wire(conf, str, i))
			return (ERROR);
		i++;
	}
	return (**str ? ERROR : NO_ERROR);
}

t_error			get_conf(t_conf *conf, char *str)
{
	if (parse_rotors(conf, &str))
		return (ERROR);
	if (parse_positions(conf, &str))
		return (ERROR);
	if (parse_wires(conf, &str))
		return (ERROR);
	return (NO_ERROR);
}