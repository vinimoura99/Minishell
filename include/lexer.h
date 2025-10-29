/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoura-d <vmoura-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:00:00 by joao-vri          #+#    #+#             */
/*   Updated: 2025/10/19 13:41:09 by vmoura-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "types.h"
# include <stddef.h>

/* ----------------LEXER---------------- */

void	tokenizer(char *input, t_token **head, int input_count);
int		*define_quote(char **input, int input_count);
int		*define_type(char **input, int input_count, int *quotes);
void	create_token(t_token **head, char type, char *str, char quote);
void	clear_inside_quotes(char ***input, int *quotes);
void	clear_outside_quotes(char ***input);

/* -----------FT_SPLIT_QUOTED----------- */

size_t	ft_untilnext_q(const char *str);
size_t	ft_skip_quoted(const char *str, size_t i);
size_t	ft_strcount_q(const char *str);
char	**ft_alloc_word(char **strs, const char **s, size_t i);
char	**ft_split_quoted(char const *s);

#endif