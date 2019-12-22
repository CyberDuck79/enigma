/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enigma.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:10:47 by fhenrion          #+#    #+#             */
/*   Updated: 2019/12/22 18:23:41 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENIGMA_H
# define ENIGMA_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

# define ALPHABET		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define ROTOR_I		"EKMFLGDQVZNTOWYHXUSPAIBRCJ"
# define ROTOR_II		"AJDKSIRUXBLHWTMCQGZNPYFVOE"
# define ROTOR_III		"BDFHJLCPRTXVZNYEIWGAKMUSQO"
# define ROTOR_IV		"ESOVPZJAYQUIRHXLNFTGKDCMWB"
# define ROTOR_V		"VZBRGITYUPSDNHLXAWMJQOFECK"
# define ROTOR_VI		"JPGVOUMFYQBENHZRDKASXLICTW"
# define ROTOR_VII		"NZJHGRCXMYSWBOUFAIVLPEKQDT"
# define ROTOR_VIII		"FKQHTLXOCBJSPDZRAMEWNIUYGV"
# define REFLECTOR_B	"YRUHQSLDPXNGOKMIEBFZCWVJAT"
# define REFLECTOR_C	"RDOBJNTKVEHMLFCWZAXGYIPSUQ"
# define ROTORS (const char* [8]) \
{ROTOR_I,ROTOR_II,ROTOR_III,ROTOR_IV,ROTOR_V,ROTOR_VI,ROTOR_VII,ROTOR_VIII}

typedef unsigned char t_rotor;

typedef enum	e_dir
{
	FIRST_PASS,
	REFLECTION
}				t_dir;

typedef enum	e_error
{
	NO_ERROR,
	ERROR
}				t_error;

typedef struct	s_conf
{
	const char	*rotor[3];
	const char	*reflector;
	int			position[3];
	char		wires[2][13];
}				t_conf;

t_error			get_conf(t_conf *conf, char *str);
t_error			encode(t_conf *conf, char *str);

#endif