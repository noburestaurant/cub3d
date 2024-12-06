/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:01:25 by hnakayam          #+#    #+#             */
/*   Updated: 2024/08/31 16:12:54 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "./../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 11
# endif

char	*get_next_line(int fd);
int		put(char **ans, char *buf, char **mem);
char	*all_free(char **ans, char **buf, char **mem, char flag);
int		nobu_set(char **ans, char **buf, int *flag);
char	*nobu_strjoin(char const *s1, char const *s2, ssize_t n);
ssize_t	nobu_strchar(const char *s, char c);

#endif
