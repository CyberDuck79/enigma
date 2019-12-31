/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enigma_enc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 11:04:45 by fhenrion          #+#    #+#             */
/*   Updated: 2019/12/31 17:33:38 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enigma.h"
#include <stdio.h>

static int	check_char(char c)
{
	return (c >= 'A' && c <= 'Z');
}

static char	wire(t_conf *conf, char c)
{
	size_t	i = 0;

	while (conf->wires[0][i])
	{
		if (c == conf->wires[0][i])
			return (conf->wires[1][i]);
		if (c == conf->wires[1][i])
			return (conf->wires[0][i]);
		i++;
	}
	return (c);
}

static void	rotors_shift(t_conf *conf)
{
	if (++conf->position[0] > 25)
	{
		conf->position[0] = 0;
		if (++conf->position[1] > 25)
		{
			conf->position[1] = 0;
			if (++conf->position[2] > 25)
				conf->position[2] = 0;
		}
	}
}

static char	cypher(t_conf *conf, int i, t_rotor r, t_dir d)
{
	if (r == REFLECTOR)
		return (cypher(conf, conf->reflector[i], 2, 1));
	if ((i += conf->position[r]) > 25)
		i -= 26;
	i = conf->rotor[r][d][i];
	if ((i -= conf->position[r]) < 0)
		i += 26;
	if (r == ROTOR_I && d == REFLECTION)
		return ((char)(i + 65));
	return (cypher(conf, i, d ? r - 1 : r + 1, d));
}

t_error		encode(t_conf *conf, char *str)
{
	char	*enc_char = malloc(strlen(str) + 1);
	char	*enc_str = enc_char;

	while (*str)
	{
		if (check_char(*str))
		{
			rotors_shift(conf);
			*enc_char = cypher(conf, wire(conf, *str) - 65, 0, 0);
			*enc_char = wire(conf, *enc_char);
			enc_char++;
		}
		str++;
	}
	*enc_char = '\0';
	write(1, enc_str, strlen(enc_str));
	return (NO_ERROR);
}
