#include "s21_matrix.h"
#include <math.h>
#include <stdio.h>

static double **inverse(double **src, int size)
{
	
	int i,j,k,n;

	n = size;

    double a[(n * 2) + 1][(n * 2) + 1];
    double ratio;
    
    
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            
            a[i][j] = src[i - 1][j - 1];
        }
    }
    
    /* Augmenting Identity Matrix of Order n */
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(i==j)
            {
                a[i][j+n] = 1;
            }
            else
            {
                a[i][j+n] = 0;
            }
        }
    }
    
    /* Applying Gauss Jordan Elimination */
    for(i=1;i<=n;i++)
    {
        if(a[i][i] == 0.0)
        {
            return NULL;
        }
        for(j=1;j<=n;j++)
        {
            if(i!=j)
            {
                ratio = a[j][i]/a[i][i];
                for(k=1;k<=2*n;k++)
                {
                    a[j][k] = a[j][k] - ratio*a[i][k];
                }
            }
        }
    }
    
    
    /* Row Operation to Make Principal Diagonal to 1 */
    for(i=1;i<=n;i++)
    {
        for(j=n+1;j<=2*n;j++)
        {
        a[i][j] = a[i][j]/a[i][i];
        }
    }

    
    double **matrix = s21_create_matrix_array(size, size);
    int m = 0;
    int p;
    
    for(i=1;i<=n;i++)
    {
        p = 0;
        for(j=n+1;j<=2*n;j++)
        {
            matrix[m][p] = a[i][j];
            p++;
        }
        m++;
    }
    return matrix;
}

matrix_t s21_inverse_matrix(matrix_t *A)
{
    if (A->rows != A->columns || A->rows < 1 || A->columns < 1) {
		return s21_get_incorrect_matrix();
	}
    matrix_t inverse_matrix = s21_create_matrix(A->rows, A->columns);
    double **inverse_array = inverse(A->matrix, A->rows);
    if (!inverse_array) {
        return s21_get_incorrect_matrix();
    }
    s21_free_matrix(&inverse_matrix, A->rows);
    inverse_matrix.matrix = inverse_array;
    inverse_matrix.matrix_type = CORRECT_MATRIX;
    return inverse_matrix;
}