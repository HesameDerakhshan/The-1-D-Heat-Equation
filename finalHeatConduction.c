
#include <stdio.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_vector.h>


int main (){
 
  double a=0.005;
  int	 y = 100;
  int loop_n =100000;
  
  //-------------------------------------------------------
  gsl_vector * d = gsl_vector_alloc (y);
  gsl_vector_set_all (d, ((2*a)+1)); //initialize vector diag by gsl patern

  //------------------------------------------------------- 
    
  gsl_vector * e = gsl_vector_alloc (y-1);
  gsl_vector_set_all (e, (-a)); //initialize vector e by gsl patern
  
  //-------------------------------------------------------
 
  gsl_vector * b = gsl_vector_alloc (y);
  gsl_vector_set_all (b, 0); //initialize vector e by gsl patern
  gsl_vector_set (b, 0,100);

   //-------------------------------------------------------
 
  gsl_vector * T = gsl_vector_alloc (y);
    
   //------------------------------------------------------- 
  


 for(int j=1;j<(loop_n);j++){
  gsl_linalg_solve_symm_tridiag(d,e,b,T); 
  
  gsl_vector_memcpy(b,T);
  gsl_vector_set (b, 0,100);
  gsl_vector_set (b, y-1,0);

     char buffer[32];
 if (j%(loop_n/10)==0 )
  {
  snprintf(buffer, sizeof(char) * 32,"file%i.txt",j);
   
  FILE * k = fopen (buffer, "w");
  gsl_vector_fprintf (k,b,"%.6g");
   
  fclose (k); 

  } 
  }



  gsl_vector_free (d);
  gsl_vector_free (e);
  gsl_vector_free (T);
  gsl_vector_free (b);
  
  return 0;
}
