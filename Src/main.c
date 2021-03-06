/**
 * @mainpage AZTEKAS: a hydrodynamic GPL code
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file main.c
 *
 * @author Alejandro Aguayo-Ortiz.
 *
 * @brief Main file of aztekas.
 */

//Do not erase any of these libraries//
#include"main.h"

int main(int argc, char *argv[])
{
   int itprint;
   double dtprint, tprint;

   if(argc != 2) 
   {
      printf("%s\n","Wrong number of arguments") ;
      printf("%s\n","Execute as:") ;    
      printf("%s\n","./aztekas paramfile") ;  
      exit(EXIT_FAILURE);
   }

   strcpy(paramfile_name, argv[1]);
   
   /*
    * Read necessary and user defined parameters from file.param
    * and print info in screen
    */
   Default_Parameters(paramfile_name);
   User_Parameters(paramfile_name);

   /**
    * Check paramfile, print info of the simulation on screen
    * and also inside a directory named INFO inside the simulation
    * directory. Print INFO on the screen.
    */
   Manage_Simulation_Info(argc,argv);

   /**
    * Allocate the space for all the arrays used by aztekas
    */
   Allocate_Array();

   /**
    * Create a Cartesian-like mesh grid
    */
   Mesh();

   /**
    * Initialize solution vector U
    */
   Init_Simulation(&tprint,&itprint);

   /*
    * Frequency of printing output
    */
   Frequency_Output(&dtprint);

#ifdef _OPENMP
   start = omp_get_wtime();
   omp_set_num_threads(OMP_NUM);
#else
   start = clock();
#endif
   while(grid.time <= tmax)
   {
      //In this part we compute the time step
      dt = TimeStep();

      //We print the values: file (DATOS*) and to terminal func_planarOUTPUT.c
      Print_Values(&tprint,&dtprint,&itprint);

      //In here we set the integration method (Finite volume method)
      Integration();

      printf("Time = %e, dt = %e\r",grid.time,dt);
      fflush(stdout); 
   }

   Print_Values(&tprint,&dtprint,&itprint);

   printf("\n");
#ifdef _OPENMP
   printf("Expend %.4f seconds parallelized using  %d threads of %d available.\n",omp_get_wtime()-start,OMP_NUM,MAX_NUM_THREADS);
#else
   printf("Expend %.4f seconds in serial version.\n",((double)(clock()-start))/CLOCKS_PER_SEC);
#endif

   free(U);
   free(grid.X1);
   free(grid.X2);
   free(grid.X3);

   return 0;
}
