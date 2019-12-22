/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enigma_ini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 18:16:21 by fhenrion          #+#    #+#             */
/*   Updated: 2019/12/22 18:22:59 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enigma.h"

static int			check_char(char c)
{
	return (c >= 'A' && c <= 'Z');
}

static t_error		next_token(char **str, char c)
{
	while (**str && **str != c)
		(*str)++;
	if (!**str)
		return (ERROR);
	(*str)++;
	return (NO_ERROR);
}

static const char	*get_rotor(t_rotor i, const char **rotors)
{
	return (rotors[i]);
}

static t_error		parse_rotors(t_conf *conf, char **str)
{
	t_rotor	rotor[3];

	rotor[0] = atoi(*str);
	if (rotor[0] < 1 || rotor[0] > 8 || next_token(str, '-'))
		return (ERROR);
	conf->rotor[0] = get_rotor(rotor[0] - 1, ROTORS);
	rotor[1] = atoi(*str);
	if (rotor[1] < 1 || rotor[1] > 8 || rotor[1] == rotor[0]
	|| next_token(str, '-'))
		return (ERROR);
	conf->rotor[1] = get_rotor(rotor[1] - 1, ROTORS);
	rotor[2] = atoi(*str);
	if (rotor[2] < 1 || rotor[2] > 8 || rotor[2] == rotor[0]
	|| rotor[2] == rotor[1] || next_token(str, '-'))
		return (ERROR);
	conf->rotor[2] = get_rotor(rotor[2] - 1, ROTORS);
	if (**str == 'B')
		conf->reflector = REFLECTOR_B;
	else if (**str == 'C')
		conf->reflector = REFLECTOR_C;
	else
		return (ERROR);
	return (next_token(str, '-'));
}

static t_error		parse_positions(t_conf *conf, char **str)
{
	conf->position[0] = atoi(*str) - 1;
	if (conf->position[0] < 0 || conf->position[0] > 25 || next_token(str, '-'))
		return (ERROR);
	conf->position[1] = atoi(*str) - 1;
	if (conf->position[1] < 0 || conf->position[1] > 25 || next_token(str, '-'))
		return (ERROR);
	conf->position[2] = atoi(*str) - 1;
	if (conf->position[2] < 0 || conf->position[2] > 25 || next_token(str, '-'))
		return (ERROR);
	return (NO_ERROR);
}

static t_error		parse_wire(t_conf *conf, char **str, size_t wire_nb)
{
	size_t	i = 0;

	while (conf->wires[0][i])
	{
		if (**str == conf->wires[0][i] || **str == conf->wires[1][i])
			return (ERROR);
		i++;
	}
	conf->wires[0][wire_nb] = **str;
	if (next_token(str, '/'))
		return (ERROR);
	i = 0;
	while (conf->wires[0][i])
	{
		if (**str == conf->wires[0][i] || **str == conf->wires[1][i])
			return (ERROR);
		i++;
	}
	conf->wires[1][wire_nb] = **str;
	next_token(str, '-');
	return (NO_ERROR);
}

static t_error		parse_wires(t_conf *conf, char **str)
{
	size_t	i = 0;

	bzero(conf->wires[0], 13);
	bzero(conf->wires[1], 13);
	while (check_char(**str) && i < 13)
	{
		if (parse_wire(conf, str, i))
			return (ERROR);
		i++;
	}
	return (**str ? ERROR : NO_ERROR);
}

t_error				get_conf(t_conf *conf, char *str)
{
	if (parse_rotors(conf, &str))
		return (ERROR);
	if (parse_positions(conf, &str))
		return (ERROR);
	if (parse_wires(conf, &str))
		return (ERROR);
	return (NO_ERROR);
}