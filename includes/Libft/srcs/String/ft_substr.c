/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_substr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: siferrar <siferrar@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 13:03:23 by siferrar     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/16 23:44:00 by siferrar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/libft.h"

static size_t	ft_strlcpy_cust(char *dst, const char *src, size_t size)
{
	int i;

	i = -1;
	while (src[++i] && (--size + 1))
		dst[i] = src[i];
	dst[i] = '\0';
	while (src[i])
		i++;
	return ((size_t)i);
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (calloc(1, 1));
	while (s[start + i] && len)
		i++;
	if (len > i)
		len = i;
	if (!(str = (char *)(malloc(sizeof(char) * (len + 1)))))
		return (NULL);
	ft_strlcpy_cust(str, &s[start], len);
	return (str);
}
