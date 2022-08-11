#include <stdio.h>
#include <stdlib.h>
#include "ECHAIM/ECHAIM.h"
#include "ECHAIM/errorCodes.h"

#define INDEX(a,i,j,dim) a[j*dim + i]
//int* JF,float lat,float lon,float year,float month,float day,float hour,float min,float sec,float* alt,float* outf

// double ** densityProfile();
//


void CArrayToFortran_2D(float* out,double** arr,int dim1,int dim2)
{
  for (size_t i = 0; i < dim1; i++) {
    for (size_t j = 0; j < dim2; j++) {
      out[j] = arr[i][j];
    //  printf("%f ",arr[i][j] );
    }
  }
//  printf("\n");
}

void fortranArrayToC_2D(float** out,float* arr,int dim1,int dim2)
{
  for (size_t i = 0; i < dim1; i++) {
    for (size_t j = 0; j < dim2; j++) {
      out[i][j] = INDEX(arr,i,j,dim2);
    }
  }
}

float** alloc_2d_array_float(int a,int b)
{
  float** mem = malloc(sizeof(float*)*a);
  for (int i = 0 ; i < b;i++)
  {
    mem[i] = malloc(sizeof(float)*b);
  }
  return mem;
}

double* fortranRealToDouble(float* i,int count)
{
  double* alloc = malloc(sizeof(double)*count);
  for (size_t j = 0; j < count; j++) {
    alloc[j] = i[j];
  }
  return alloc;
}

double* makeAltProfile(double start,double end,int steps)
{
  double* alloc = malloc(sizeof(double)*steps);
  for (size_t i = 0; i < steps; i++) {
    alloc[i] = start + i*((end - start)/500.0);
  }
  return alloc;
}

void densityprofilefortraninterop_(float *lat, float *lon, float *year, float *month, float *day, \
float *hour, float *min, float *sec,float* oput)
{
  // float** testvar_re = alloc_2d_array_float(2,2);
  // fortranArrayToC_2D(testvar_re,testvar,2,2);
  // printf("Test %f %f %f %f\n",testvar_re[0][0],testvar_re[0][1],testvar_re[1][0],testvar_re[1][1] );
  double* lat_d = fortranRealToDouble(lat,1);
  double* lon_d = fortranRealToDouble(lon,1);
  double* year_d = fortranRealToDouble(year,1);
  double* month_d = fortranRealToDouble(month,1);
  double* day_d = fortranRealToDouble(day,1);
  double* hour_d = fortranRealToDouble(hour,1);
  double* min_d = fortranRealToDouble(min,1);
  double* sec_d = fortranRealToDouble(sec,1);
  //double* alt_d = fortranRealToDouble(alt,*l1);

  double* alt_d = makeAltProfile(60,560,500);
//  printf("%f\n",alt_d[400] );
  // double lat[2] = {60,44}; //geographic latitude
	// double lon[2] = {210,220}; //geographic longitude
	// double altProfile[10] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}; //altitude (km) (for profile)
	// double altPath[2] = {200, 210}; //altitude (km) (for path)
	// double y[2]= {1996,2012}; //year
	// double m[2] = {8,2}; //month
	// double d[2]={21,12}; //day
	// double h[2]={5,16}; //hour
	// double mi[2]={0,11}; //minute
	// double s[2]={0,0}; //second
	// int l0 = 2; //lat/lon/time array size
	// int l1 = 10; //alt array size
	char **er; //error output

  double **output2;
	int storm = 0; //storm perturbation flag
	int precip = 0; //precipitation model flag
	int dregion = 1; //d region model flag
	//Ask the model to log possible error codes
	logErrors(1);
  //fprintf(stderr,"%f %f %f %f %f %f\n",*year_d, *month_d, *day_d, *hour_d, *min_d, *sec_d);
//  fprintf(stderr, "%f %f\n",*lat_d, *lon_d );
//	printf("Now running densityProfile function \n");

	output2 = densityProfile(lat_d, lon_d, year_d, month_d, day_d, hour_d, min_d, sec_d, storm, precip, dregion, 1, alt_d, 500, 0);

//  printf("Output of densityProfile function \n");

  // for (int i=0; i<l0; i++)
  // {
  //   int j;
  //   for (int j=0; j<l1; j++)
  //   {
  //     printf("%f ", output2[i][j]);
  //   }
  //
  //   printf("%f\n\n", output2[i][j]);
  // }
  //
  // //get and print the error codes
  // er = getErrors();
  //
  // for (int i=0; i<1; i++)
  // {
  //   printf("Error Codes: %c%c%c%c%c%c%c%c%c%c\n", er[i][0],er[i][1],er[i][2],er[i][3], \
  //     er[i][4],er[i][5],er[i][6],er[i][7],er[i][8],er[i][9]);
  // }

  for (int i=0; i<1; i++) {free(output2[i]);}

  CArrayToFortran_2D(oput,output2,1,500);
  free(output2);
}
