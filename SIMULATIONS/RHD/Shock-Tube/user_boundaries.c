/*
 * File Name : user_boundaries.c
 * Description : aztekas boundaries module for Relativistic Shock-Tube
 * Creation Date : 28-09-2019
 * Last Modified : 28-10-2019 17:28:24
 * Created By : Alejandro Aguayo-Oritz
 */

#include"main.h"

void User_Boundaries(double *B)
{
   int i, j, k, n, cell;

#if DIM == 2
   
   // Linear extrapolation. Important for the diagonal shock tube
 
   #if INTERFACE == DIAGONAL
   for(i = 0; i <= Nx1; i++)
   {
      for(j = 0; j <= Nx2; j++)
      {
         for(n = 0; n < eq; n++)
         {
            if(i > Nx1-gc)
            {
               B(n,i,j) = B(n,i-2,j) + ((grid.X1[i] - grid.X1[i-2])/(grid.X1[i-1] - grid.X1[i-2]))*(B(n,i-1,j) - B(n,i-2,j)); 
            }
            if(j > Nx2-gc)
            {
               B(n,i,j) = B(n,i,j-2) + ((grid.X2[j] - grid.X2[j-2])/(grid.X2[j-1] - grid.X2[j-2]))*(B(n,i,j-1) - B(n,i,j-2)); 
            }
         }
      }
   }

   for(i = Nx1; i >= 0; i--)
   {
      for(j = Nx2; j <= 0; j--)
      {
         for(n = 0; n < eq; n++)
         {
            if(i > Nx1-gc)
            {
               B(n,i,j) = B(n,i+2,j) + ((grid.X1[i] - grid.X1[i+2])/(grid.X1[i+1] - grid.X1[i+2]))*(B(n,i+1,j) - B(n,i+2,j)); 
            }
            if(j > Nx2-gc)
            {
               B(n,i,j) = B(n,i,j+2) + ((grid.X2[j] - grid.X2[j+2])/(grid.X2[j+1] - grid.X2[j+2]))*(B(n,i,j+1) - B(n,i,j+2)); 
            }
         }
      }
   }
   #endif 
   
#endif
}
