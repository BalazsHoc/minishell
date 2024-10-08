/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: i2024/04/09 12:30:45 by bhocsak           #+#    #+#            */
/*   Updated: 2024/04/23 12:33:53 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;

	if (!nmemb || !size)
		return (malloc(0));
	if (size > SIZE_MAX / nmemb)
		return (0);
	buffer = (void *)malloc(size * nmemb);
	if (!buffer)
		return (0);
	ft_bzero(buffer, size * nmemb);
	return (buffer);
}
/*
#include <stdio.h>

int main()
{
    int *arr;
    size_t num_elements = 10;
    size_t element_size = sizeof(int);

    // Allocate memory for an array of integers using calloc
    arr = (int *)ft_calloc(num_elements, element_size);

    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Initialize array elements
    for (size_t i = 0; i < num_elements; i++) {
        arr[i] = i + 1;
    }

    // Print array elements
    printf("Array elements:\n");
    for (size_t i = 0; i < num_elements; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Free allocated memory
    free(arr);

    return 0;
}*/
