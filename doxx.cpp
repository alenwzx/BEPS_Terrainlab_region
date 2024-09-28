/*************************************************************************
  Program:     doxx.c
  --------
  Description:
  -----------
 	Zero xx, read xx, write to xx.

  Variables List:
  ---------------
	x1 - snow pack
	x2 - soil water
	x3 - out flow
	x4 - transpiration
	x5 - evaporation
	x6 - photosynthesis
	x7 - Rm
	x8 - leaf C
	x9 - stem C
	x10 - root C
	x11 - GPP
	x12 - ResSoil
	x13 - NEP
	x14 - M Res leaf
	x15 - M Res stem
	x16 - M Res root
	x17 - Number of days with rain
	x18 - understory Trans
	x19 - water-table
	x20 - soil wilting point
	x21 - soil field capacity
	x22 - soil porosity

  ***************************************************************************
  CCRS (EMS/Applications Division)
  Written by:   J. Liu
  Last update:	May 1998
*****************************************************************************/
#include "stdafx.h"
#include "BepsHydrScience.h"

void zeroxx(int pix,double *x,xvalue *xx)
//  int long pix;
//  double x[];
//  struct xvalue xx[];
{
	xx[pix].x1=0;
	xx[pix].x2=0;

	xx[pix].x3=0;
	xx[pix].x4=0;

	xx[pix].x5=0;
	xx[pix].x6=0;

	xx[pix].x7=0;
	xx[pix].x8=0;

	xx[pix].x9=0;
	xx[pix].x10=0;
	xx[pix].x11=0;
	//xx[pix].x12=0;
	xx[pix].x13=0;
	xx[pix].x14=0;
	xx[pix].x15=0;
	xx[pix].x16=0;
	xx[pix].x17=0;
	xx[pix].x18=0;
//	xx[pix].x19=0; //juw
//	xx[pix].x20=0; //MM
//	xx[pix].x21=0; //MM
	//xx[pix].x22=0; //MM
    //xx[pix].x26=0; //MM
	//xx[pix].x27=0; //MM
   // xx[pix].x28=0; //MM
//	xx[pix].x33 = 0;
}

void readxx(int pix,double *x,xvalue *xx)
//  int long pix;
//  double x[];
//  struct xvalue xx[];
{
	x[0] = 0.0;	// to be precies, MM
	x[1]=xx[pix].x1;
	x[2]=xx[pix].x2;
	x[3]=xx[pix].x3;
	x[4]=xx[pix].x4;
	x[5]=xx[pix].x5;
	x[6]=xx[pix].x6;
	x[7]=xx[pix].x7;
	x[8]=xx[pix].x8;
	x[9]=xx[pix].x9;
	x[10]=xx[pix].x10;
	x[11]=xx[pix].x11;
	x[12]=xx[pix].x12;
	x[13]=xx[pix].x13;
	x[14]=xx[pix].x14;
	x[15]=xx[pix].x15;
	x[16]=xx[pix].x16;
	x[17]=xx[pix].x17;
	x[18]=xx[pix].x18;
	x[19]=xx[pix].x19; //juw
	x[20]=xx[pix].x20; //MM
	x[21]=xx[pix].x21; //MM
	x[22]=xx[pix].x22; //MM
    x[23]=xx[pix].x23; //MM

    x[26]=xx[pix].x26; //MM
	x[27]=xx[pix].x27; //MM
    x[28]=xx[pix].x28;//MM
	x[30]=xx[pix].x30; //texture
	 x[33]=xx[pix].x33;//4nov2006
	 x[36]=xx[pix].x36;//nitrogen
x[37]=xx[pix].x37;
x[38]=xx[pix].x38;
	/*x[41]=xx[pix].x41;
	x[42]=xx[pix].x42;
	x[43]=xx[pix].x43;
	x[44]=xx[pix].x44;
	x[45]=xx[pix].x45;  //POOLS
	x[46]=xx[pix].x46;
	x[47]=xx[pix].x47;
	x[48]=xx[pix].x48;
	x[49]=xx[pix].x49;*/
x[50]=xx[pix].x50;
x[51]=xx[pix].x51;
x[52]=xx[pix].x52;
x[53]=xx[pix].x53;




}

void writexx(int pix,double *x,xvalue *xx)
//  int long pix;
//  double x[];
//  struct xvalue xx[];
{
	xx[pix].x1=x[1];
	xx[pix].x2=x[2];

	xx[pix].x3=x[3];
	xx[pix].x4=x[4];

	xx[pix].x5=x[5];
	xx[pix].x6=x[6];

	xx[pix].x7=x[7];
	xx[pix].x8=x[8];

	xx[pix].x9=x[9];
	xx[pix].x10=x[10];
	xx[pix].x11=x[11];
	xx[pix].x12=x[12];
	xx[pix].x13=x[13];
	xx[pix].x14=x[14];
	xx[pix].x15=x[15];
	xx[pix].x16=x[16];
	xx[pix].x17=x[17];
	xx[pix].x18=x[18];
	xx[pix].x19=x[19]; //juw
	xx[pix].x20=x[20]; // MM
	xx[pix].x21=x[21]; // MM
	xx[pix].x22=x[22]; // MM
    xx[pix].x23=x[23]; // MM
    xx[pix].x26=x[26]; // MM
	xx[pix].x27=x[27]; // MM
    xx[pix].x28=x[28]; // MM
	xx[pix].x30=x[30]; //texture
	xx[pix].x33=x[33];
	xx[pix].x36=x[36];
	xx[pix].x37=x[37];
	xx[pix].x38=x[38];
	/*xx[pix].x41=x[41];
	xx[pix].x42=x[42];
	xx[pix].x43=x[43];
	xx[pix].x44=x[44];
	xx[pix].x45=x[45];
	xx[pix].x46=x[46]; //pools
	xx[pix].x47=x[47];
	xx[pix].x48=x[48];
	xx[pix].x49=x[49];*/

	xx[pix].x50=x[50];
	xx[pix].x51=x[51];
	xx[pix].x52=x[52];
	xx[pix].x53=x[53];


}
