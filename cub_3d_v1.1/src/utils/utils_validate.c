
#include "cub_3d.h"

/*
5. Las utilidades de matrices (Gestión del Heap)
Las herramientas necesarias para que check_walls maneje la memoria sin romper nada.
FUNCIÓN free_matrix(matrix, height):
    VARIABLE i = 0
    SI matrix es NULL:
        RETORNAR

    MIENTRAS i < height:
        LIBERAR(matrix[i])
        i++
    LIBERAR(matrix)

FUNCIÓN duplicate_matrix(src_matrix, height):
    // Reservamos memoria para los punteros de las filas (+1 para el NULL de cierre)
    VARIABLE dst_matrix = MALLOC(sizeof(char *) * (height + 1))
    SI dst_matrix es NULL:
        RETORNAR (NULL)

    VARIABLE i = 0
    MIENTRAS i < height:
        // Duplicamos el string de la fila con tu ft_strdup
        dst_matrix[i] = ft_strdup(src_matrix[i])
        
        // Control defensivo: si falla un malloc intermedio, liberamos lo que llevamos para evitar leaks
        SI dst_matrix[i] es NULL:
            free_matrix(dst_matrix, i)
            RETORNAR (NULL)
        i++

    dst_matrix[i] = NULL // Cierre seguro de la matriz clonada
    RETORNAR (dst_matrix)

*/