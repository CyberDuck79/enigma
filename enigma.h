/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enigma.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:10:47 by fhenrion          #+#    #+#             */
/*   Updated: 2019/12/17 15:02:03 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENIGMA_H
# define ENIGMA_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

# define ALPHABET			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define ROTOR_I			"EKMFLGDQVZNTOWYHXUSPAIBRCJ"
# define ROTOR_II			"AJDKSIRUXBLHWTMCQGZNPYFVOE"
# define ROTOR_III			"BDFHJLCPRTXVZNYEIWGAKMUSQO"
# define ROTOR_IV			"ESOVPZJAYQUIRHXLNFTGKDCMWB"
# define ROTOR_V			"VZBRGITYUPSDNHLXAWMJQOFECK"
# define ROTOR_VI			"JPGVOUMFYQBENHZRDKASXLICTW"
# define ROTOR_VII			"NZJHGRCXMYSWBOUFAIVLPEKQDT"
# define ROTOR_VIII			"FKQHTLXOCBJSPDZRAMEWNIUYGV"
# define REFLECTOR_B		"YRUHQSLDPXNGOKMIEBFZCWVJAT"
# define REFLECTOR_C		"RDOBJNTKVEHMLFCWZAXGYIPSUQ"

typedef enum			e_error
{
	NO_ERROR,
	ERROR
}						t_error;

typedef struct			s_conf
{
	char				*rotor[3];
	char				*reflector;
	int					pos_ini[3];
	char				wire[5][2];
}						t_conf;

t_error			get_conf(t_conf *conf, char *str);

// TODO :
// - Fonction de parsing de la configuration
// - Fonction de chiffrement

// 2-5-3-B-1-24-3-A/F-G/D-G/E-G/V-Z/T

// CONCEPT
/*
- ordre des rotors
- orientations initiales
- branchements du tableau de connexions -> echange deux inputs
exemple : on tape A mais on prends l'index de L dans l'input

ROTOR positions : 1)Right 2)Middle 3)Left

EXEMPLE :
	Position des rotors : 2 - 3 - 1
	Orientations des rotors : 2 - 23 - 5
	Branchements des connexions : A/L - P/R - T/D - B/W - K/F - O/Y
	Indicateurs : B - W - E

On prends l'input ex : A -> index 1, on le permute en la lettre du premier rotor a l'index 1 + decalage, on continue jusqu'au reflecteur qui fait prendre le sens inverse en donnant l'index sur lequel reprendre la permutation

- si (index + decalage) > 25 %= 26
- si decalage > 25 %= 26

char input;
char alphabet[26];
char rotor_1[26]; -> ini selon define
char rotor_2[26];
char rotor_3[26];
size_t index;
size_t index_1;
size_t index_2;
size_t index_3;
size_t shift_1; -> ini a orientation
size_t shift_2;
size_t shift_3;

index = 0;
while (alphabet[index] != input)
	index++;
if (shift_1 > 25)
	shift_1 %= 26;
index_1 = index + shift_1 > 25 ? (index + shift_1) % 26 : index + shift_1;
input = rotor_1[index_1];
index = 0;
while (alphabet[index] != input)
	index++;
if (shift_2 > 25)
	shift_2 %= 26;
index_2 = index + shift_2 > 25 ? (index + shift_2) % 26 : index + shift_2;
input = rotor_2[index_1];
ect...
*/

#endif