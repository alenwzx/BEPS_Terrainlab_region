/***************************************************************************************************************

	NNAME: ReadInSoil.cpp

	SYNOPSIS
	void Current_Tz(unsigned int iC, unsigned int iR,
	soil soils[], Array Tz[], starter myseed)

	OPTIONS
	iC ---- current location in a row of a database
	iR ---- current location in a column of a databse
	soils ----- struction contains soil information
	Tz ---- Array class contains current Tz diffusivity
	myseed -- Initial database information
	DESCRIPTION

	This routine is to calculate hydrolic diffusivity given
	depth to the water table, saturated hydrolic conductivity,
	and soil saturation conductivity decay factor.
	Totally nine pixels are calculated.
	The newly calculated Tz values are returned by reference


	Background and ALGORITHMS:
	According to Beven (1982), SATURATED HYDROLIC Conductivity
	decreases with depth below the soil surface in a manner of
	exponential function.
	Tz = Kz*[exp(-m*z) - exp(-m*Z)]/m

	SPECIAL NOTES:
	One applicaiton of this equation was used by Wigmosta(1994)
	Alternatively Tz = K0*[(exp(-s/m) - exp(-s/Z)]

  **************************************************************************************************************
	OTHER UPDATES:
	1.	Date:			September 4, 2003
		Author:			A. Bulynko
		Description:	1)	File I/O was moved outside of the function.
						2)	Function was modified to work on a per-line basis.
							It is now setup to receive 3-row Soil_Array input array
							and to select out of it a 9-element soil output array.
**************************************************************************************************************/
#include "stdafx.h"
#include "BepsHydrScience.h"
#include "string.h"
#include "malloc.h"
#include "stdio.h"

//void ReadInSoil(char *soilfilename, Soil_t  *soil, unsigned int iLine, unsigned int iPixel,
//				pubv *myseed, char *pathName) //***Removed by Andriy
void ReadInSoil(Soil_t* Soil_Array_3r,Soil_t* current_soil,
				unsigned int iLine,unsigned int iPixel,pubv* myseed) //***Added by Andriy
{
	unsigned int i, j, iX, iY;

	j = iPixel;
	iY = myseed->npixels;
	iX = myseed->nlines;

	//determine whether dealing with 1st, 2nd or 3rd line of 3-line Soil_Array array
	if (iLine == 0)
		i = 0;
	else if (iLine == iX-1)
		i = 2;
	else
		i = 1;

	if(iLine==0)
	{
		if(j==0)//at the upper left corner
		{
			//fseek(soil_ptr, INDEX(i,j,iY)*sizeof(Soil_t), SEEK_SET);					//***Removed by Andriy
			//fread(&soil[4], sizeof(Soil_t), 1, soil_ptr );							//***Removed by Andriy
			memcpy(&current_soil[4],&Soil_Array_3r[INDEX(i,j,iY)],sizeof(Soil_t));		//***Added by Andriy

			//fseek(soil_ptr, INDEX(i,j+1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[5], sizeof(Soil_t), 1, soil_ptr );							//***Removed by Andriy
			memcpy(&current_soil[5],&Soil_Array_3r[INDEX(i,j+1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i+1,j+1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[8], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[8],&Soil_Array_3r[INDEX(i+1,j+1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i+1,j,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[7], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[7],&Soil_Array_3r[INDEX(i+1,j,iY)],sizeof(Soil_t));	//***Added by Andriy

		}
		if(j+1==iY) //at the up right corner
		{

			//fseek(soil_ptr, INDEX(i,j,iY)*sizeof(Soil_t), SEEK_SET);					//***Removed by Andriy
			//fread(&soil[4], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[4],&Soil_Array_3r[INDEX(i,j,iY)],sizeof(Soil_t));		//***Added by Andriy

			//fseek(soil_ptr, INDEX(i,j-1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[3], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[3],&Soil_Array_3r[INDEX(i,j-1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i+1,j-1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[6], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[6],&Soil_Array_3r[INDEX(i+1,j-1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i+1,j,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[7], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[7],&Soil_Array_3r[INDEX(i+1,j,iY)],sizeof(Soil_t));	//***Added by Andriy

		}
		if(0<j && j+1<iY)
		{
			//fseek(soil_ptr, INDEX(i,j,iY)*sizeof(Soil_t), SEEK_SET);					//***Removed by Andriy
			//fread(&soil[4], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[4],&Soil_Array_3r[INDEX(i,j,iY)],sizeof(Soil_t));		//***Added by Andriy

			//fseek(soil_ptr, INDEX(i,j-1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[3], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[3],&Soil_Array_3r[INDEX(i,j-1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i,j+1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[5], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[5],&Soil_Array_3r[INDEX(i,j+1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i+1,j-1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[6], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[6],&Soil_Array_3r[INDEX(i+1,j-1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i+1,j,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[7], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[7],&Soil_Array_3r[INDEX(i+1,j,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i+1,j+1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[8], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[8],&Soil_Array_3r[INDEX(i+1,j+1,iY)],sizeof(Soil_t));	//***Added by Andriy

		}
	}//end of if i==0 block

	if(j==0)
	{
		if((iLine+1) == iX)
		{
			//fseek(soil_ptr, INDEX(i,j,iY)*sizeof(Soil_t), SEEK_SET);					//***Removed by Andriy
			//fread(&soil[4], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[4],&Soil_Array_3r[INDEX(i,j,iY)],sizeof(Soil_t));		//***Added by Andriy

			//fseek(soil_ptr, INDEX(i-1,j,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[1], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[1],&Soil_Array_3r[INDEX(i-1,j,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i-1,j+1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[2], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[2],&Soil_Array_3r[INDEX(i-1,j+1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i,j+1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[5], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[5],&Soil_Array_3r[INDEX(i,j+1,iY)],sizeof(Soil_t));	//***Added by Andriy

		}
		if(iLine>0 && (iLine+1) < iX)
		{
			//fseek(soil_ptr, INDEX(i,j,iY)*sizeof(Soil_t), SEEK_SET);					//***Removed by Andriy
			//fread(&soil[4], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[4],&Soil_Array_3r[INDEX(i,j,iY)],sizeof(Soil_t));		//***Added by Andriy

			//fseek(soil_ptr, INDEX(i-1,j,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[1], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[1],&Soil_Array_3r[INDEX(i-1,j,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i-1,j+1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[2], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[2],&Soil_Array_3r[INDEX(i-1,j+1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i,j+1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[5], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[5],&Soil_Array_3r[INDEX(i,j+1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i+1,j+1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[8], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[8],&Soil_Array_3r[INDEX(i+1,j+1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i+1,j,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[7], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[7],&Soil_Array_3r[INDEX(i+1,j,iY)],sizeof(Soil_t));	//***Added by Andriy

		}

	}//end of if(j==0) block
	if((j+1)==iY)
	{
		if((iLine+1)==iX)
		{
			//fseek(soil_ptr, INDEX(i,j,iY)*sizeof(Soil_t), SEEK_SET);					//***Removed by Andriy
			//fread(&soil[4], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[4],&Soil_Array_3r[INDEX(i,j,iY)],sizeof(Soil_t));		//***Added by Andriy

			//fseek(soil_ptr, INDEX(i,j-1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[3], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[3],&Soil_Array_3r[INDEX(i,j-1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i-1,j-1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[0], sizeof(Soil_t), 1, soil_ptr);								//***Removed by Andriy
			memcpy(&current_soil[0],&Soil_Array_3r[INDEX(i-1,j-1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i-1,j,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[1],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[1],&Soil_Array_3r[INDEX(i-1,j,iY)],sizeof(Soil_t));	//***Added by Andriy

		}
		if(iLine>0 && (iLine+1)<iX)
		{
			//fseek(soil_ptr, INDEX(i,j,iY)*sizeof(Soil_t), SEEK_SET);					//***Removed by Andriy
			//fread(&soil[4],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[4],&Soil_Array_3r[INDEX(i,j,iY)],sizeof(Soil_t));		//***Added by Andriy

			//fseek(soil_ptr, INDEX(i-1,j,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[1],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[1],&Soil_Array_3r[INDEX(i-1,j,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i-1,j-1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[0],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[0],&Soil_Array_3r[INDEX(i-1,j-1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i,j-1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[3],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[3],&Soil_Array_3r[INDEX(i,j-1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i+1,j-1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[6],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[6],&Soil_Array_3r[INDEX(i+1,j-1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i+1,j,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[7],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[7],&Soil_Array_3r[INDEX(i+1,j,iY)],sizeof(Soil_t));	//***Added by Andriy

		}

	}//end of if(j+1 == iY) block

	if((iLine+1)==iX)
	{

		if(j>0 && (j+1) < iY)
		{
			//fseek(soil_ptr, INDEX(i,j,iY)*sizeof(Soil_t), SEEK_SET);					//***Removed by Andriy
			//fread(&soil[4],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[4],&Soil_Array_3r[INDEX(i,j,iY)],sizeof(Soil_t));		//***Added by Andriy

			//fseek(soil_ptr, INDEX(i-1,j-1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[0],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[0],&Soil_Array_3r[INDEX(i-1,j-1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i-1,j,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[1],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[1],&Soil_Array_3r[INDEX(i-1,j,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i-1,j+1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[2],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[2],&Soil_Array_3r[INDEX(i-1,j+1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i,j+1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[5],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[5],&Soil_Array_3r[INDEX(i,j+1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i,j-1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[3],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[3],&Soil_Array_3r[INDEX(i,j-1,iY)],sizeof(Soil_t));	//***Added by Andriy

		}
	}//end of if(i+1 == iX) block

	if(iLine>0 && (iLine+1)<iX && j>0 && (j+1)<iY)
	{
			//fseek(soil_ptr, INDEX(i,j,iY)*sizeof(Soil_t), SEEK_SET);					//***Removed by Andriy
			//fread(&soil[4],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[4],&Soil_Array_3r[INDEX(i,j,iY)],sizeof(Soil_t));		//***Added by Andriy

			//fseek(soil_ptr, INDEX(i-1,j-1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[0],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[0],&Soil_Array_3r[INDEX(i-1,j-1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i-1,j,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[1],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[1],&Soil_Array_3r[INDEX(i-1,j,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i-1,j+1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[2],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[2],&Soil_Array_3r[INDEX(i-1,j+1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i,j-1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[3],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[3],&Soil_Array_3r[INDEX(i,j-1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i,j+1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[5],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[5],&Soil_Array_3r[INDEX(i,j+1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i+1,j-1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[6],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[6],&Soil_Array_3r[INDEX(i+1,j-1,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i+1,j,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[7],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[7],&Soil_Array_3r[INDEX(i+1,j,iY)],sizeof(Soil_t));	//***Added by Andriy

			//fseek(soil_ptr, INDEX(i+1,j+1,iY)*sizeof(Soil_t), SEEK_SET);				//***Removed by Andriy
			//fread(&soil[8],  sizeof(Soil_t), 1, soil_ptr);							//***Removed by Andriy
			memcpy(&current_soil[8],&Soil_Array_3r[INDEX(i+1,j+1,iY)],sizeof(Soil_t));	//***Added by Andriy

	}//end of if(i>0 && (i+1)<iX && j>0 && (j+1)<iY) block
}//end of function

