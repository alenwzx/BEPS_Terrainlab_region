


/*-----------------------------------------------------------------------------*/
/* 																				*/
/*  NNAME:	Current_Tz.cpp														*/
/*																				*/
/*	SYNOPSIS																	*/
/*	void Current_Tz(unsigned int iR, unsigned int iC,n
/*  soil soils[], Array Tz[], starter myseed)									*/
/*																				*/
/*	OPTIONS																		*/
/*	iC ---- current location in a row of a database							  	*/
/*	iR ---- current location in a column of a databse							*/
/*	soils ----- struction contains soil information
/*	Tz ---- Array contains current Tz diffusivity								*/
/*	myseed -- Initial database information										*/
/*	DESCRIPTION																	*/
/*																				*/
/*	This routine is to calculate hydrolic diffusivity given						*/
/*	depth to the water table. Totally nine pixels are calculated				*/
/*	The newly calculated Tz values are returned by reference					 */
/*		                    													*/
/*	Pixels are number in the following way in a moving window					*/
/*
/*				------> j	i
/*				0,	1,	2	^
/*				3,	4,	5	|
/*				6,	7,	8	|
/*
/*
/*
/*
/*
/*	Background and ALGORITHMS:    												*/
/*  According to Beven (1982), SATURATED HYDROLIC Conductivity
/*	decreases with depth below the soil surface in a manner of
/*	exponential function.
/*	Tz = Kz*[exp(-m*z) - exp(-m*Z)]/m  Kz是饱和导水率，Tz是液压透射率
/*
/*  SPECIAL NOTES:																*/
/*  One applicaiton of this equation was used by Wigmosta(1994)					*/
/*  Alternatively Tz = K0*[(exp(-s/m) - exp(-s/Z)]                              */
/*--------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "BepsHydrScience.h"
#include <math.h>
#define MOSS 280
#define A 16.25
#define f_moss 7.5048
float moss_peat;
unsigned char lc_p;							 /*land cover criteria*/
void Current_Tz(unsigned int iR, unsigned int iC,Soil_t soils[],  Soil_t* soil, double Tz[], pubv *myseed)
{

	unsigned int i, j, iX, iY;
	i = iR; //current line
	j = iC; //current pixel
	iX = myseed->nlines;
	iY = myseed->npixels;
double ft;



/*
if(soil[4].soil_temp>0) ft=1.0;
else if(soil[4].soil_temp<-7) ft=0.07;
else ft=0.05+(soil[4].soil_temp+5)/5.0*0.95;
*/
/*
//no temp constrin
if(soilt>0) ft=1.0;
else if(soilt<-5) ft=1.0;//0.05;
else ft=1.0;//0.05+(soilt+5)/5.0*0.95;
*/


//******************************PEAT LAYER CRITERIA**********************************************
								  moss_peat=0.15; //进行了修改，这里的泥炭层标准应该不同地方不一样吧  moss_peat=0.15
/*This a hypothetical case of 0.20m deep peat-moss complex above the mineral soil, irrespective of
  land cover. But in reality this varies with LC, with Black Spruce dominated one having thick layer
  To do this, LC has to be read in 3 rows similar to the hydrological parameters and assigned specific
								peat depth criteria--->things for future*/
//***********************************************************************************************

	Tz[0]=(soils[0].saturated_Ks); //value is the same but the units. m^2/day
	Tz[1]=(soils[1].saturated_Ks); //value is the same but the units. m^2/day
	Tz[2]=(soils[2].saturated_Ks); //value is the same but the units. m^2/day
	Tz[3]=(soils[3].saturated_Ks); //value is the same but the units. m^2/day
	Tz[4]=(soils[4].saturated_Ks); //value is the same but the units. m^2/day
	Tz[5]=(soils[5].saturated_Ks); //value is the same but the units. m^2/day
	Tz[6]=(soils[6].saturated_Ks); //value is the same but the units. m^2/day
	Tz[7]=(soils[7].saturated_Ks); //value is the same but the units. m^2/day
	Tz[8]=(soils[8].saturated_Ks); //value is the same but the units. m^2/day

	//recalculate the Tz values in the rest of this routine

	if(soils[4].K0_decay_m > 0 && soils[4].water_table > 0)

			{
				if(soils[4].water_table > moss_peat)
				Tz[4] = soils[4].saturated_Ks*(exp(-soils[4].K0_decay_m*soils[4].water_table)-
				exp(-soils[4].K0_decay_m*(soils[4].Max_depth_Z)))/soils[4].K0_decay_m;
				else
				//Tz[4] = MOSS*(exp(-((soils[4].water_table+5.0504)/A)));
				Tz[4] = MOSS*(exp(-(soils[4].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;

			}

	if(i==0)
	{
		if(j==0)//at the upper left corner
		{



			if(soils[5].K0_decay_m > 0 && soils[5].water_table >0 )
//if(soils[5].K0_decay_m > 0 )
			{
				if(soils[5].water_table > moss_peat)
				Tz[5] = soils[5].saturated_Ks*(exp(-soils[5].K0_decay_m*soils[5].water_table)-
							exp(-soils[5].K0_decay_m*(soils[5].Max_depth_Z)))/soils[5].K0_decay_m;
				else
				//Tz[5] = MOSS*(exp(-((soils[5].water_table+5.0504)/A)));
					Tz[5] = MOSS*(exp(-(soils[5].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			if(soils[7].K0_decay_m > 0 && soils[7].water_table > 0)
//if(soils[7].K0_decay_m > 0 )
			{
				if(soils[7].water_table > moss_peat)
					Tz[7] = soils[7].saturated_Ks*(exp(-soils[7].K0_decay_m*soils[7].water_table)-
							exp(-soils[7].K0_decay_m*(soils[7].Max_depth_Z)))/soils[7].K0_decay_m;
				else
					//Tz[7] = MOSS*(exp(-((soils[7].water_table+5.0504)/A)));
					Tz[7] = MOSS*(exp(-(soils[7].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			if(soils[8].K0_decay_m > 0 && soils[8].water_table > 0)
	//if(soils[8].K0_decay_m > 0 )
			{
				if(soils[8].water_table > moss_peat)
					Tz[8] = soils[8].saturated_Ks*(exp(-soils[8].K0_decay_m*soils[8].water_table)-
						exp(-soils[8].K0_decay_m*(soils[8].Max_depth_Z)))/soils[8].K0_decay_m;
				else
					//Tz[8] = MOSS*(exp(-((soils[8].water_table+5.0504)/A)));
Tz[8] = MOSS*(exp(-(soils[8].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}


	Tz[0]=0;
	Tz[1]=0;
	Tz[2]=0;
	Tz[3]=0;
	Tz[6]=0;


		}


		if(j+1==iY) //at the up right corner
		{

			if(soils[3].K0_decay_m > 0 && soils[3].water_table > 0)
//if(soils[3].K0_decay_m > 0 )
			{
				if(soils[3].water_table > moss_peat)
				Tz[3] = soils[3].saturated_Ks*(exp(-soils[3].K0_decay_m*soils[3].water_table)-
						exp(-soils[3].K0_decay_m*(soils[3].Max_depth_Z)))/soils[3].K0_decay_m;
				else
				//Tz[3] = MOSS*(exp(-((soils[3].water_table+5.0504)/A)));
Tz[3] = MOSS*(exp(-(soils[3].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			if(soils[6].K0_decay_m > 0 && soils[6].water_table > 0)
//if(soils[6].K0_decay_m > 0 )
			{
				if(soils[6].water_table > moss_peat)
				Tz[6] = soils[6].saturated_Ks*(exp(-soils[6].K0_decay_m*soils[6].water_table)-
						exp(-soils[6].K0_decay_m*(soils[6].Max_depth_Z)))/soils[6].K0_decay_m;
				else
				//Tz[6] = MOSS*(exp(-((soils[6].water_table+5.0504)/A)));
Tz[6] = MOSS*(exp(-(soils[6].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			if(soils[7].K0_decay_m > 0 && soils[7].water_table > 0)
//if(soils[7].K0_decay_m > 0 )
			{
				if(soils[7].water_table > moss_peat)
				Tz[7] = soils[7].saturated_Ks*(exp(-soils[7].K0_decay_m*soils[7].water_table)-
						exp(-soils[7].K0_decay_m*(soils[7].Max_depth_Z)))/soils[7].K0_decay_m;
				else
				//Tz[7] = MOSS*(exp(-((soils[7].water_table+5.0504)/A)));
Tz[7] = MOSS*(exp(-(soils[7].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

	Tz[0]=0;
	Tz[1]=0;
	Tz[2]=0;
	Tz[5]=0;
	Tz[8]=0;


		}

		if(0<j && j+1<iY)
		{
			if(soils[3].K0_decay_m > 0 && soils[3].water_table > 0)
//if(soils[3].K0_decay_m > 0 )
			{
				if(soils[3].water_table > moss_peat)
				Tz[3] = soils[3].saturated_Ks*(exp(-soils[3].K0_decay_m*soils[3].water_table)-
						exp(-soils[3].K0_decay_m*(soils[3].Max_depth_Z)))/soils[3].K0_decay_m;
				else
				//Tz[3] = MOSS*(exp(-((soils[3].water_table+5.0504)/A)));
Tz[3] = MOSS*(exp(-(soils[3].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			if(soils[5].K0_decay_m > 0 && soils[5].water_table > 0)
//if(soils[5].K0_decay_m > 0 )
			{
				if(soils[5].water_table > moss_peat)
				Tz[5] = soils[5].saturated_Ks*(exp(-soils[5].K0_decay_m*soils[5].water_table)-
						exp(-soils[5].K0_decay_m*(soils[5].Max_depth_Z)))/soils[5].K0_decay_m;
				else
			//	Tz[5] = MOSS*(exp(-((soils[5].water_table+5.0504)/A)));
Tz[5] = MOSS*(exp(-(soils[5].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			if(soils[6].K0_decay_m > 0 && soils[6].water_table > 0)
//if(soils[6].K0_decay_m > 0 )
			{	if(soils[6].water_table > moss_peat)
				Tz[6] = soils[6].saturated_Ks*(exp(-soils[6].K0_decay_m*soils[6].water_table)-
						exp(-soils[6].K0_decay_m*(soils[6].Max_depth_Z)))/soils[6].K0_decay_m;
				else
				//Tz[6] = MOSS*(exp(-((soils[6].water_table+5.0504)/A)));
Tz[6] = MOSS*(exp(-(soils[6].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			if(soils[7].K0_decay_m > 0 && soils[7].water_table > 0)
//if(soils[7].K0_decay_m > 0 )
			{
				if(soils[7].water_table > moss_peat)
				Tz[7] = soils[7].saturated_Ks*(exp(-soils[7].K0_decay_m*soils[7].water_table)-
						exp(-soils[7].K0_decay_m*(soils[7].Max_depth_Z)))/soils[7].K0_decay_m;
				else
				//Tz[7] = MOSS*(exp(-((soils[7].water_table+5.0504)/A)));
Tz[7] = MOSS*(exp(-(soils[7].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			if(soils[8].K0_decay_m > 0 && soils[8].water_table > 0)
//if(soils[8].K0_decay_m > 0 )
			{
				if(soils[8].water_table > moss_peat)
				Tz[8] = soils[8].saturated_Ks*(exp(-soils[8].K0_decay_m*soils[8].water_table)-
						exp(-soils[8].K0_decay_m*(soils[8].Max_depth_Z)))/soils[8].K0_decay_m;
				else
				//Tz[8] = MOSS*(exp(-((soils[8].water_table+5.0504)/A)));
Tz[8] = MOSS*(exp(-(soils[8].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

	Tz[0]=0;
	Tz[1]=0;
	Tz[2]=0;

		}
	}//end of if i==0 block

	if(j==0)
	{
		if((i+1) == iX)
		{
			if(soils[1].K0_decay_m > 0 && soils[1].water_table > 0)
			//if(soils[1].K0_decay_m > 0 )
			{
				if(soils[1].water_table > moss_peat)
				Tz[1] = soils[1].saturated_Ks*(exp(-soils[1].K0_decay_m*soils[1].water_table)-
						exp(-soils[1].K0_decay_m*(soils[1].Max_depth_Z)))/soils[1].K0_decay_m;
				else
				//Tz[1] = MOSS*(exp(-((soils[1].water_table+5.0504)/A)));
Tz[1] = MOSS*(exp(-(soils[1].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			if(soils[2].K0_decay_m > 0 && soils[2].water_table > 0)
			//if(soils[2].K0_decay_m > 0 )
			{
				if(soils[2].water_table > moss_peat)
				Tz[2] = soils[2].saturated_Ks*(exp(-soils[2].K0_decay_m*soils[2].water_table)-
						exp(-soils[2].K0_decay_m*(soils[2].Max_depth_Z)))/soils[2].K0_decay_m;
				else
				//Tz[2] = MOSS*(exp(-((soils[2].water_table+5.0504)/A)));
Tz[2] = MOSS*(exp(-(soils[2].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;

			}

			if(soils[5].K0_decay_m > 0 && soils[5].water_table > 0)
			//if(soils[5].K0_decay_m > 0)
			{
				if(soils[5].water_table > moss_peat)
				Tz[5] = soils[5].saturated_Ks*(exp(-soils[5].K0_decay_m*soils[5].water_table)-
						exp(-soils[5].K0_decay_m*(soils[5].Max_depth_Z)))/soils[5].K0_decay_m;
				else
				//Tz[5] = MOSS*(exp(-((soils[5].water_table+5.0504)/A)));
Tz[5] = MOSS*(exp(-(soils[5].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}


	Tz[0]=0;
	Tz[3]=0;
	Tz[6]=0;
	Tz[7]=0;
	Tz[8]=0;


		}

		if(i>0 && (i+1) < iX)
		{
			if(soils[1].K0_decay_m > 0 && soils[1].water_table > 0)
//if(soils[1].K0_decay_m > 0)
			{
				if(soils[1].water_table > moss_peat)
				Tz[1] = soils[1].saturated_Ks*(exp(-soils[1].K0_decay_m*soils[1].water_table)-
						exp(-soils[1].K0_decay_m*(soils[1].Max_depth_Z)))/soils[1].K0_decay_m;
				else
				//Tz[1] = MOSS*(exp(-((soils[1].water_table+5.0504)/A)));
Tz[1] = MOSS*(exp(-(soils[1].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}


			if(soils[2].K0_decay_m > 0 && soils[2].water_table > 0)
//if(soils[2].K0_decay_m > 0 )
			{
				if(soils[2].water_table > moss_peat)
				Tz[2] = soils[2].saturated_Ks*(exp(-soils[2].K0_decay_m*soils[2].water_table)-
						exp(-soils[2].K0_decay_m*(soils[2].Max_depth_Z)))/soils[2].K0_decay_m;
				else
			//Tz[2] = MOSS*(exp(-((soils[2].water_table+5.0504)/A)));
Tz[2] = MOSS*(exp(-(soils[2].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			if(soils[5].K0_decay_m > 0 && soils[5].water_table > 0)
//if(soils[5].K0_decay_m > 0 )
			{
				if(soils[5].water_table > moss_peat)
				Tz[5] = soils[5].saturated_Ks*(exp(-soils[5].K0_decay_m*soils[5].water_table)-
						exp(-soils[5].K0_decay_m*(soils[5].Max_depth_Z)))/soils[5].K0_decay_m;
				else
				//Tz[5] = MOSS*(exp(-((soils[5].water_table+5.0504)/A)));
Tz[5] = MOSS*(exp(-(soils[5].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			if(soils[7].K0_decay_m > 0 && soils[7].water_table > 0)
//if(soils[7].K0_decay_m > 0 )
			{
				if(soils[7].water_table > moss_peat)
				Tz[7] = soils[7].saturated_Ks*(exp(-soils[7].K0_decay_m*soils[7].water_table)-
						exp(-soils[7].K0_decay_m*(soils[7].Max_depth_Z)))/soils[7].K0_decay_m;
				else
				//Tz[7] = MOSS*(exp(-((soils[7].water_table+5.0504)/A)));
Tz[7] = MOSS*(exp(-(soils[7].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			if(soils[8].K0_decay_m > 0 && soils[8].water_table > 0)
//if(soils[8].K0_decay_m > 0 )
			{
				if(soils[8].water_table > moss_peat)
				Tz[8] = soils[8].saturated_Ks*(exp(-soils[8].K0_decay_m*soils[8].water_table)-
						exp(-soils[8].K0_decay_m*(soils[8].Max_depth_Z)))/soils[8].K0_decay_m;
				else
				//Tz[8] = MOSS*(exp(-((soils[8].water_table+5.0504)/A)));
Tz[8] = MOSS*(exp(-(soils[8].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

	Tz[0]=0;
	Tz[3]=0;
	Tz[6]=0;

		}
	}//end of if(j==0) block

	if((j+1)==iY)
	{
		if((i+1)==iX)
		{
			if(soils[0].K0_decay_m > 0 && soils[0].water_table > 0)
//if(soils[0].K0_decay_m > 0 )
			{
				if(soils[0].water_table > moss_peat)
				Tz[0] = soils[0].saturated_Ks*(exp(-soils[0].K0_decay_m*soils[0].water_table)-
						exp(-soils[0].K0_decay_m*(soils[0].Max_depth_Z)))/soils[0].K0_decay_m;
				else
				//Tz[0] = MOSS*(exp(-((soils[0].water_table+5.0504)/A)));
Tz[0] = MOSS*(exp(-(soils[0].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			//default diffusivity data should be added later

			if(soils[1].K0_decay_m > 0 && soils[1].water_table > 0)
//if(soils[1].K0_decay_m > 0)
			{
				if(soils[1].water_table > moss_peat)
				Tz[1] = soils[1].saturated_Ks*(exp(-soils[1].K0_decay_m*soils[1].water_table)-
						exp(-soils[1].K0_decay_m*(soils[1].Max_depth_Z)))/soils[1].K0_decay_m;
				else
			//Tz[1] = MOSS*(exp(-((soils[1].water_table+5.0504)/A)));
Tz[1] = MOSS*(exp(-(soils[1].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			if(soils[3].K0_decay_m > 0 && soils[3].water_table > 0)
//if(soils[3].K0_decay_m > 0 )
			{
				if(soils[3].water_table > moss_peat)
				Tz[3] = soils[3].saturated_Ks*(exp(-soils[3].K0_decay_m*soils[3].water_table)-
						exp(-soils[3].K0_decay_m*(soils[3].Max_depth_Z)))/soils[3].K0_decay_m;
				else
				//Tz[3] = MOSS*(exp(-((soils[3].water_table+5.0504)/A)));
Tz[3] = MOSS*(exp(-(soils[3].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

	Tz[2]=0;
	Tz[5]=0;
	Tz[6]=0;

	Tz[7]=0;
	Tz[8]=0;

		}

		if(i>0 && (i+1)<iX)
		{
			if(soils[0].K0_decay_m > 0 && soils[0].water_table > 0)
//if(soils[0].K0_decay_m > 0 )
			{
				if(soils[0].water_table > moss_peat)
				Tz[0] = soils[0].saturated_Ks*(exp(-soils[0].K0_decay_m*soils[0].water_table)-
						exp(-soils[0].K0_decay_m*(soils[0].Max_depth_Z)))/soils[0].K0_decay_m;
				else
				//Tz[0] = MOSS*(exp(-((soils[0].water_table+5.0504)/A)));
Tz[0] = MOSS*(exp(-(soils[0].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			//default diffusivity data should be added later

			if(soils[1].K0_decay_m > 0 && soils[1].water_table > 0)
//if(soils[1].K0_decay_m > 0 )
			{
				if(soils[1].water_table > moss_peat)
				Tz[1] = soils[1].saturated_Ks*(exp(-soils[1].K0_decay_m*soils[1].water_table)-
						exp(-soils[1].K0_decay_m*(soils[1].Max_depth_Z)))/soils[1].K0_decay_m;
				else
				//Tz[1] = MOSS*(exp(-((soils[1].water_table+5.0504)/A)));
Tz[1] = MOSS*(exp(-(soils[1].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			if(soils[3].K0_decay_m > 0 && soils[3].water_table > 0)
	//if(soils[3].K0_decay_m > 0 )
			{
				if(soils[3].water_table > moss_peat)
				Tz[3] = soils[3].saturated_Ks*(exp(-soils[3].K0_decay_m*soils[3].water_table)-
						exp(-soils[3].K0_decay_m*(soils[3].Max_depth_Z)))/soils[3].K0_decay_m;
				else
				//Tz[3] = MOSS*(exp(-((soils[3].water_table+5.0504)/A)));
Tz[3] = MOSS*(exp(-(soils[3].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			if(soils[6].K0_decay_m > 0 && soils[6].water_table > 0)
//if(soils[6].K0_decay_m > 0 )
			{
				if(soils[6].water_table > moss_peat)
				Tz[6] = soils[6].saturated_Ks*(exp(-soils[6].K0_decay_m*soils[6].water_table)-
						exp(-soils[6].K0_decay_m*(soils[6].Max_depth_Z)))/soils[6].K0_decay_m;
				else
				//Tz[6] = MOSS*(exp(-((soils[6].water_table+5.0504)/A)));
Tz[6] = MOSS*(exp(-(soils[6].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			if(soils[7].K0_decay_m > 0 && soils[7].water_table > 0)
	//if(soils[7].K0_decay_m > 0 )
			{
				if(soils[7].water_table > moss_peat)
				Tz[7] = soils[7].saturated_Ks*(exp(-soils[7].K0_decay_m*soils[7].water_table)-
						exp(-soils[7].K0_decay_m*(soils[7].Max_depth_Z)))/soils[7].K0_decay_m;
				else
				//Tz[7] = MOSS*(exp(-((soils[7].water_table+5.0504)/A)));
Tz[7] = MOSS*(exp(-(soils[7].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

	Tz[2]=0;
	Tz[8]=0;



		}
	}//end of if(j+1 == iY) block

	if((i+1)==iX)
	{
		if(j>0 && (j+1) < iY)
		{
			if(soils[0].K0_decay_m > 0 && soils[0].water_table > 0)
//if(soils[0].K0_decay_m > 0 )
			{
				if(soils[0].water_table > moss_peat)
				Tz[0] = soils[0].saturated_Ks*(exp(-soils[0].K0_decay_m*soils[0].water_table)-
						exp(-soils[0].K0_decay_m*(soils[0].Max_depth_Z)))/soils[0].K0_decay_m;
				else
				//Tz[0] = MOSS*(exp(-((soils[0].water_table+5.0504)/A)));
Tz[0] = MOSS*(exp(-(soils[0].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			//default diffusivity data should be added later

			if(soils[1].K0_decay_m > 0 && soils[1].water_table > 0)
//if(soils[1].K0_decay_m > 0 )
			{
				if(soils[1].water_table > moss_peat)
				Tz[1] = soils[1].saturated_Ks*(exp(-soils[1].K0_decay_m*soils[1].water_table)-
						exp(-soils[1].K0_decay_m*(soils[1].Max_depth_Z)))/soils[1].K0_decay_m;
				else
				//Tz[1] = MOSS*(exp(-((soils[1].water_table+5.0504)/A)));
Tz[1] = MOSS*(exp(-(soils[1].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			if(soils[2].K0_decay_m > 0 && soils[2].water_table > 0)
//if(soils[2].K0_decay_m > 0 )
			{
				if(soils[2].water_table > moss_peat)
				Tz[2] = soils[2].saturated_Ks*(exp(-soils[2].K0_decay_m*soils[2].water_table)-
						exp(-soils[2].K0_decay_m*(soils[2].Max_depth_Z)))/soils[2].K0_decay_m;
				else
				//Tz[2] = MOSS*(exp(-((soils[2].water_table+5.0504)/A)));
Tz[2] = MOSS*(exp(-(soils[2].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			if(soils[3].K0_decay_m > 0 && soils[3].water_table > 0)
//if(soils[3].K0_decay_m > 0 )
			{
				if(soils[3].water_table > moss_peat)
				Tz[3] = soils[3].saturated_Ks*(exp(-soils[3].K0_decay_m*soils[3].water_table)-
						exp(-soils[3].K0_decay_m*(soils[3].Max_depth_Z)))/soils[3].K0_decay_m;
				else
				//Tz[3] = MOSS*(exp(-((soils[3].water_table+5.0504)/A)));
Tz[3] = MOSS*(exp(-(soils[3].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

			if(soils[5].K0_decay_m > 0 && soils[5].water_table > 0)
//if(soils[5].K0_decay_m > 0 )
			{
				if(soils[5].water_table > moss_peat)
				Tz[5] = soils[5].saturated_Ks*(exp(-soils[5].K0_decay_m*soils[5].water_table)-
						exp(-soils[5].K0_decay_m*(soils[5].Max_depth_Z)))/soils[5].K0_decay_m;
				else
				//Tz[5] = MOSS*(exp(-((soils[5].water_table+5.0504)/A)));
Tz[5] = MOSS*(exp(-(soils[5].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
			}

	Tz[6]=0;
	Tz[7]=0;
	Tz[8]=0;

		}
	}//end of if(i+1 == iX) block

	if(i>0 && (i+1)<iX && j>0 && (j+1)<iY)
	{
		if(soils[0].K0_decay_m > 0 && soils[0].water_table > 0)
//if(soils[0].K0_decay_m > 0 )
		{
			if(soils[0].water_table > moss_peat)
			Tz[0] = soils[0].saturated_Ks*(exp(-soils[0].K0_decay_m*soils[0].water_table)-
					exp(-soils[0].K0_decay_m*(soils[0].Max_depth_Z)))/soils[0].K0_decay_m;
			else
			//Tz[0] = MOSS*(exp(-((soils[0].water_table+5.0504)/A)));
Tz[5] = MOSS*(exp(-(soils[5].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
		}

		//default diffusivity data should be added later

		if(soils[1].K0_decay_m > 0 && soils[1].water_table > 0)
//if(soils[1].K0_decay_m > 0 )
		{
			if(soils[1].water_table > moss_peat)
			Tz[1] = soils[1].saturated_Ks*(exp(-soils[1].K0_decay_m*soils[1].water_table)-
					exp(-soils[1].K0_decay_m*(soils[1].Max_depth_Z)))/soils[1].K0_decay_m;
			else
			//Tz[1] = MOSS*(exp(-((soils[1].water_table+5.0504)/A)));
Tz[1] = MOSS*(exp(-(soils[1].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
		}

		if(soils[2].K0_decay_m > 0 && soils[2].water_table > 0)
//if(soils[2].K0_decay_m > 0 )
		{
			if(soils[2].water_table > moss_peat)
			Tz[2] = soils[2].saturated_Ks*(exp(-soils[2].K0_decay_m*soils[2].water_table)-
					exp(-soils[2].K0_decay_m*(soils[2].Max_depth_Z)))/soils[2].K0_decay_m;
			else
			//Tz[2] = MOSS*(exp(-((soils[2].water_table+5.0504)/A)));
Tz[2] = MOSS*(exp(-(soils[2].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
		}

		if(soils[3].K0_decay_m > 0 && soils[3].water_table > 0)
	//if(soils[3].K0_decay_m > 0 )
		{
			if(soils[3].water_table > moss_peat)
			Tz[3] = soils[3].saturated_Ks*(exp(-soils[3].K0_decay_m*soils[3].water_table)-
					exp(-soils[3].K0_decay_m*(soils[3].Max_depth_Z)))/soils[3].K0_decay_m;
			else
			//Tz[3] = MOSS*(exp(-((soils[3].water_table+5.0504)/A)));
Tz[3] = MOSS*(exp(-(soils[3].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
		}

		if(soils[5].K0_decay_m > 0 && soils[5].water_table > 0)
//if(soils[5].K0_decay_m > 0 )
		{	if(soils[5].water_table > moss_peat)
			Tz[5] = soils[5].saturated_Ks*(exp(-soils[5].K0_decay_m*soils[5].water_table)-
					exp(-soils[5].K0_decay_m*(soils[5].Max_depth_Z)))/soils[5].K0_decay_m;
			else
			//Tz[5] = MOSS*(exp(-((soils[5].water_table+5.0504)/A)));
Tz[5] = MOSS*(exp(-(soils[5].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
		}

		if(soils[6].K0_decay_m > 0 && soils[6].water_table > 0)
//if(soils[6].K0_decay_m > 0 )
		{
			if(soils[6].water_table > moss_peat)
			Tz[6] = soils[6].saturated_Ks*(exp(-soils[6].K0_decay_m*soils[6].water_table)-
					exp(-soils[6].K0_decay_m*(soils[6].Max_depth_Z)))/soils[6].K0_decay_m;
			else
			//Tz[6] = MOSS*(exp(-((soils[6].water_table+5.0504)/A)));
Tz[6] = MOSS*(exp(-(soils[6].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
		}

		if(soils[7].K0_decay_m > 0 && soils[7].water_table > 0)
	//if(soils[7].K0_decay_m > 0 )
		{
			if(soils[7].water_table > moss_peat)
			Tz[7] = soils[7].saturated_Ks*(exp(-soils[7].K0_decay_m*soils[7].water_table)-
					exp(-soils[7].K0_decay_m*(soils[7].Max_depth_Z)))/soils[7].K0_decay_m;
			else
			//Tz[7] = MOSS*(exp(-((soils[7].water_table+5.0504)/A)));
Tz[7] = MOSS*(exp(-(soils[7].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
		}

		if(soils[8].K0_decay_m > 0 && soils[8].water_table > 0)
	//if(soils[8].K0_decay_m > 0 )
		{
			if(soils[8].water_table > moss_peat)
			Tz[8] = soils[8].saturated_Ks*(exp(-soils[8].K0_decay_m*soils[8].water_table)-
					exp(-soils[8].K0_decay_m*(soils[8].Max_depth_Z)))/soils[8].K0_decay_m;
			else
			//Tz[8] = MOSS*(exp(-((soils[8].water_table+5.0504)/A)));
Tz[8] = MOSS*(exp(-(soils[8].water_table*f_moss)-exp(-(f_moss*moss_peat))))/f_moss;
		}



	}//end of if(i>0 && (i+1)<iX && j>0 && (j+1)<iY)
 /*Tz[0]= Tz[0]*ft;
	Tz[1]= Tz[1]*ft;
	Tz[2]= Tz[2]*ft;
	Tz[3]= Tz[3]*ft;
	Tz[4]= Tz[4]*ft;
	Tz[5]= Tz[5]*ft;
	Tz[6]= Tz[6]*ft;
	Tz[7]= Tz[7]*ft;
	Tz[8]= Tz[8]*ft;


	if(ft==1){
j=j;
	}
*/
}//end of function
