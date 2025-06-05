/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/05 05:03:35 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_join_and_free(char *s1, char *s2)
{
	char	*ans;
	int		i;
	int		j;

	if (s1 == NULL)
		return (NULL);
	ans = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ans == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ans[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		ans[i++] = s2[j++];
	ans[i] = '\0';
	free(s1);
	free(s2);
	return (ans);
}
