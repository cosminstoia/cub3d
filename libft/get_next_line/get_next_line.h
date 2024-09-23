/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:12:11 by cstoia            #+#    #+#             */
/*   Updated: 2024/04/17 19:40:49 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

size_t	ft_gnl_strlen(char *str);
char	*ft_gnl_strchr(char *str, int c);
char	*ft_strjoin_and_free(char *string, char *buffer);
char	*ft_gnl_strjoin(char *s1, char *s2);
void	ft_gnl_bzero(void *s, size_t n);
char	*ft_read_file(int fd, char *string);
char	*ft_extract_line(char *string);
char	*ft_update_string(char *string);
char	*get_next_line(int fd);

#endif
