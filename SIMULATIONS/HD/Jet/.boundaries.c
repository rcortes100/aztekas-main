/* 
 *  aztekas boundaries module
 *  Date of creation: 02-01-2019 18:32:00
 *  author: Alejandro Aguayo Ortiz 
 */
#include"main.h"

int Boundaries(double *B)
{
   int n, i, j, k, cell;

   Outflow(B);
   Reflection(B);

   for(i = 0; i <= Nx1; i++)
   {
      for(j = 0; j <= Nx2; j++)
      {
         if(grid.X1[i] <= r_jet && grid.X2[j] <= z_jet)
         {
            B(RHO,i,j) = rho_jet;
            B(PRE,i,j) = p_jet;
            B(VX1,i,j) = vx1_jet;
            B(VX2,i,j) = vx2_jet;
         }
      }
   }

   return 0;
}
