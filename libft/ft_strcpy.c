/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:11:58 by ccepre            #+#    #+#             */
/*   Updated: 2018/11/12 14:00:28 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dest, const char *src)
{
	int i;

	i = -1;
	while (src[++i] != '\0')
		dest[i] = (unsigned char)src[i];
	dest[i] = '\0';
	return (dest);
}
