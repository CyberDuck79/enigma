/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enigma.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 11:04:45 by fhenrion          #+#    #+#             */
/*   Updated: 2019/12/22 12:41:29 by fhenrion         ###   ########.fr       */
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

const char	*get_rotor_conf(t_rotor i, char **rotors)
{
	return (rotors[i]);
}

t_error	parse_rotors(t_conf *conf, char **str)
{
	t_rotor	rotor[3];

	rotor[0] = atoi(*str);
	if (rotor[0] < 1 || rotor[0] > 8 || next_token(str, '-'))
		return (ERROR);
	conf->rotor[0] = get_rotor_conf(rotor[0] - 1, ROTORS);
	rotor[1] = atoi(*str);
	if (rotor[1] < 1 || rotor[1] > 8 || rotor[1] == rotor[0]
	|| next_token(str, '-'))
		return (ERROR);
	conf->rotor[1] = get_rotor_conf(rotor[1] - 1, ROTORS);
	rotor[2] = atoi(*str);
	if (rotor[2] < 1 || rotor[2] > 8 || rotor[2] == rotor[0]
	|| rotor[2] == rotor[1] || next_token(str, '-'))
		return (ERROR);
	conf->rotor[2] = get_rotor_conf(rotor[2] - 1, ROTORS);
	if (**str == 'B')
		conf->reflector = REFLECTOR_B;
	else if (**str == 'C')
		conf->reflector = REFLECTOR_C;
	else
		return (ERROR);
	return (next_token(str, '-'));
}

t_error	parse_positions(t_conf *conf, char **str)
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

int	in_string(char c, char *str)
{
	size_t	i = 0;

	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		check_char(char c)
{
	return (c >= 'A' && c <= 'Z');
}

t_error parse_wire(t_conf *conf, char **str, size_t i)
{
	static char	*used[2];
	// en cours nouveau parsing cablages
}

size_t	count_wires(char *str)
{
	size_t count = 0;

	while (*str)
	{
		if (*str == '/')
			count++;
		str++;
	}
	return (count);
}

t_error	parse_wires(t_conf *conf, char **str)
{
	size_t	i = 0;
	size_t	wires_nb = count_wires(*str);

	conf->wires[0] = malloc(wires_nb + 1);
	conf->wires[1] = malloc(wires_nb + 1); // faire gestion terminaison
	if (!conf->wires[0] || !conf->wires[0])
		return (ERROR);
	// continuer parsing et nouvelle gestion des cablages
	while (check_char(**str)) // permettre un nombre non defini de cablages
	{
		if (parse_wire(conf, str, i))
			return (ERROR);
		i++;
	}
	return (**str ? ERROR : NO_ERROR);
}

t_error	get_conf(t_conf *conf, char *str)
{
	if (parse_rotors(conf, &str))
		return (ERROR);
	//write(1, "rotors OK\n", 10);
	if (parse_positions(conf, &str))
		return (ERROR);
	//write(1, "positions OK\n", 13);
	if (parse_wires(conf, &str))
	{
		free_wires(conf->wires);
		return (ERROR);
	}
	//write(1, "wires OK\n", 9);
	return (NO_ERROR);
}

char	wire(t_conf *conf, char c)
{
	// refaire apres nouveau parsing cablage
	return (c);
}

void	rotors_shift(t_conf *conf)
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

char	cypher(t_conf *conf, char c, t_rotor r, t_dir dir)
{
	size_t	i = c - 65;

	if (r == 0 && dir == REFLECTION)
		return (c);
	if (r == 3)
		return (cypher(conf, conf->reflector[i], r - 1, REFLECTION));
	if ((i += conf->position[r]) > 25)
		i %= 26;
	return (cypher(conf, conf->rotor[r][i], dir ? r - 1 : r + 1, dir));
}

t_error	encode(t_conf *conf, char *str)
{
	char	*enc_char = malloc(strlen(str) + 1);
	char	*enc_str = enc_char;

	while (*str)
	{
		if (check_char(*str))
		{
			rotors_shift(conf);
			*enc_char = wire(conf, *str);
			if (!(*enc_char = cypher(conf, *enc_char, 0, FIRST_PASS)))
				return (ERROR);
			*enc_char = wire(conf, *str);
			enc_char++;
		}
		str++;
	}
	*enc_char = '\0';
	write(1, enc_str, strlen(enc_str));
	return (NO_ERROR);
}

int		main(int ac, char **av)
{
	t_conf	conf_ini;

	if (ac == 3)
	{
		if (get_conf(&conf_ini, av[1]))
		{
			write(1, "configuration error\n", 20);
			return (0);
		}
		if (encode(&conf_ini, av[2]))
			write(1, "encoding error\n", 15);
		free_wires(conf_ini.wires);
		return (0);
	}
	write(1, "USAGE : configuration message\n", 30);
}