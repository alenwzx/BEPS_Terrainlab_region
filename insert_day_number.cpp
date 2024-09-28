#include "stdafx.h"
#include "BepsHydrScience.h"
#include "string.h"
#include "malloc.h"
#include "stdio.h"
#include "stdlib.h"
#include "tchar.h"

void insert_day_number(char* szFileName,const char* szInFileName, int iDayNumber)
{
    char drive[255];
    char dir[255];
    char fname[255];
    char ext[255];
    char szNumber[8];
    //get string representation of number:
    _stprintf(szNumber,"%d",iDayNumber);

    //split current path into components:
    _tsplitpath(szInFileName,drive,dir,fname,ext);

    //append number to file name:
    _tcscat(fname,szNumber);

    //build new path:
    _makepath(szFileName,drive,dir,fname,ext);
}

void remove_day_number(char* szFileName,const char* szInFileName, int iDayNumber)
{
	char drive[255];
	char dir[255];
	char fname[255],new_fname[255];
	char ext[255];
	char day_number[8];
	int iDayNumberStringLength, iFileNameLength;

	//initilaize work-string buffer:
	memset(new_fname,0,_MAX_FNAME*sizeof(char));

	//get string representation of day number and the length of such string:
	_stprintf(day_number,"%d",iDayNumber);
	iDayNumberStringLength = _tcslen(day_number);

	//split current path into components:
	_tsplitpath(szInFileName,drive,dir,fname,ext);

	//make sure the day number is appended to the end of file name;
	//if it is, cut it out, else have erroneous input:
	bool bError = true;
	if ((iFileNameLength=_tcslen(fname))>=3)
	{
		if (!_tcscmp(&fname[iFileNameLength-iDayNumberStringLength],day_number))
		{
			bError = false;

			//copy part of original file name without day number to new buffer:
			_tcsncat(new_fname,fname,iFileNameLength-iDayNumberStringLength);

			//build new path:
			_makepath(szFileName,drive,dir,new_fname,ext);
		}
	}

	//if some error occured, make output the same as input:
	if (bError)
		_tcscpy(szFileName,szInFileName);
}
void AssembleSoilArray(int iLength,float* K0_decay_m,float* soil_b,float* saturation_suction,
								float* saturated_Kv,float* saturated_Ks,float* saturation_deficit,float* unsaturated_storage,
								float* water_table,float* soil_temp, float* pondwater,float* Max_depth_Z,
								float*pool1,float*pool2,float*pool3,float*pool4,float*pool5,float*pool6,float*pool7,float*pool8,float*pool9,
								float*poolb1,float*poolb2,float*poolb3,float*poolb4,float* nitrogen,
								float* CNcd_m,float* CNssd_m,float* CNsmd_m,float* CNfsd_m,float* CNfmd_m,
								float* CNsm_m,float* CNm_m,float* CNs_m,float* CNp_m,float* CNw_m,float* CNfr_m,
								float* CNl_m,
								float*ST_Layer_1,float*ST_Layer_2,float*ST_Layer_3,float*ST_Layer_4,float*ST_Layer_5,float*ST_Layer_6,
								Soil_t* soil)
{															/*pond*//* 2nov2006*/
	for (int i=0;i<iLength;i++)
	{
		soil[i].K0_decay_m				= K0_decay_m[i];
		soil[i].soil_b					= soil_b[i];
		soil[i].saturation_suction		= saturation_suction[i];
		soil[i].saturated_Kv				= saturated_Kv[i];
		soil[i].saturated_Ks				= saturated_Ks[i];

		soil[i].saturation_deficit		= saturation_deficit[i];
		soil[i].unsaturated_storage		= unsaturated_storage[i];
		soil[i].water_table				=water_table[i];
		soil[i].soil_temp				=soil_temp[i];
		soil[i].pool1				=pool1[i];
		soil[i].pool2				=pool2[i];
		soil[i].pool3				=pool3[i];
		soil[i].pool4				=pool4[i];
		soil[i].pool5				=pool5[i];
		soil[i].pool6				=pool6[i];
		soil[i].pool7				=pool7[i];
		soil[i].pool8				=pool8[i];
		soil[i].pool9				=pool9[i];
		soil[i].poolb1			=poolb1[i];
		soil[i].poolb2			=poolb2[i];
		soil[i].poolb3			=poolb3[i];
		soil[i].poolb4			=poolb4[i];
		soil[i].nitrogen		=nitrogen[i];

		soil[i].CNcd_m=CNcd_m[i];
		soil[i].CNssd_m=CNssd_m[i];
		soil[i].CNsmd_m=CNsmd_m[i];
		soil[i].CNfsd_m=CNfsd_m[i];
		soil[i].CNfmd_m=CNfmd_m[i];
		soil[i].CNsm_m=CNsm_m[i];
		soil[i].CNm_m=CNm_m[i];
		soil[i].CNs_m=CNs_m[i];
		soil[i].CNp_m=CNp_m[i];
		soil[i].CNw_m=CNw_m[i];
		soil[i].CNfr_m=CNfr_m[i];
		soil[i].CNl_m=CNl_m[i];

		soil[i].ST_Layer_1=ST_Layer_1[i];
		soil[i].ST_Layer_2=ST_Layer_2[i];
		soil[i].ST_Layer_3=ST_Layer_3[i];
		soil[i].ST_Layer_4=ST_Layer_4[i];
		soil[i].ST_Layer_5=ST_Layer_5[i];
		soil[i].ST_Layer_6=ST_Layer_6[i];


		soil[i].pondwater				=pondwater[i]; //pond
		soil[i].Max_depth_Z				= Max_depth_Z[i];
	}
}

void DisassembleSoilArray(int iLength,float* K0_decay_m,float* soil_b,float* saturation_suction,
						float* saturated_Kv,		float* saturated_Ks,float* saturation_deficit,float* unsaturated_storage,
						float* water_table,float* soil_temp,float* pondwater,float* Max_depth_Z,
						float*pool1,float*pool2,float*pool3,float*pool4,float*pool5,float*pool6,float*pool7,float*pool8,float*pool9,
						float*poolb1,float*poolb2,float*poolb3,float*poolb4,float* nitrogen,
						float* CNcd_m,float* CNssd_m,float* CNsmd_m,float* CNfsd_m,float* CNfmd_m,
						float* CNsm_m,float* CNm_m,float* CNs_m,float* CNp_m,float* CNw_m,float* CNfr_m,
						float* CNl_m,
						float*ST_Layer_1,float*ST_Layer_2,float*ST_Layer_3,float*ST_Layer_4,float*ST_Layer_5,float*ST_Layer_6,
						Soil_t* soil)
{                                       /*pond*//* 2nov2006*/
	for (int i=0;i<iLength;i++)
	{
		K0_decay_m[i]					= soil[i].K0_decay_m;
		soil_b[i]						= soil[i].soil_b;
		saturation_suction[i]			= soil[i].saturation_suction;
		saturated_Kv[i]					= soil[i].saturated_Kv;
       saturated_Ks[i]					= soil[i].saturated_Ks;

		saturation_deficit[i]			= soil[i].saturation_deficit;
		unsaturated_storage[i]			= soil[i].unsaturated_storage;
		water_table[i]					= soil[i].water_table;
		soil_temp[i]					= soil[i].soil_temp;
		pool1[i]						= soil[i].pool1;
		pool2[i]						= soil[i].pool2;
		pool3[i]						= soil[i].pool3;
		pool4[i]						= soil[i].pool4;
		pool5[i]						= soil[i].pool5;
		pool6[i]						= soil[i].pool6;
		pool7[i]						= soil[i].pool7;
		pool8[i]						= soil[i].pool8;
		pool9[i]						= soil[i].pool9;
		poolb1[i]						= soil[i].poolb1;
		poolb2[i]						= soil[i].poolb2;
		poolb3[i]						= soil[i].poolb3;
		poolb4[i]						= soil[i].poolb4;
		nitrogen[i]						= soil[i].nitrogen;
		CNcd_m[i]=soil[i].CNcd_m;
		CNssd_m[i]=soil[i].CNssd_m;
		CNsmd_m[i]=soil[i].CNsmd_m;
		CNfsd_m[i]=soil[i].CNfsd_m;
		CNfmd_m[i]=soil[i].CNfmd_m;
		CNsm_m[i]=soil[i].CNsm_m;
		CNm_m[i]=soil[i].CNm_m;
		CNs_m[i]=soil[i].CNs_m;
		CNp_m[i]=soil[i].CNp_m;
		CNw_m[i]=soil[i].CNw_m;
		CNfr_m[i]=soil[i].CNfr_m;
		CNl_m[i]=soil[i].CNl_m;
		ST_Layer_1[i]=soil[i].ST_Layer_1;
		ST_Layer_2[i]=soil[i].ST_Layer_2;
		ST_Layer_3[i]=soil[i].ST_Layer_3;
		ST_Layer_4[i]=soil[i].ST_Layer_4;
		ST_Layer_5[i]=soil[i].ST_Layer_5;
		ST_Layer_6[i]=soil[i].ST_Layer_6;



		pondwater[i]					= soil[i].pondwater; //pond
		Max_depth_Z[i]					= soil[i].Max_depth_Z;
	}
}
void	AssembleCanopyArray(int iLength,float* canopy_evaporation,
							float* canopy_transpiration_unsat,float* canopy_transpiration_sat,
							float* canopy_intercepted,float* litter_evaporation,
							float* moss_transpiration,float* soil_evaporation,float* canopy_stomata,Canopy_t* canopy)
{
	for (int i=0;i<iLength;i++)
	{
		canopy[i].canopy_evaporation			= canopy_evaporation[i];
		canopy[i].canopy_stomata			= canopy_stomata[i];
		canopy[i].canopy_transpiration_unsat	= canopy_transpiration_unsat[i];
		canopy[i].canopy_transpiration_sat		= canopy_transpiration_sat[i];
		canopy[i].canopy_intercepted			= canopy_intercepted[i];
		canopy[i].litter_evaporation			= litter_evaporation[i];
		canopy[i].moss_transpiration			= moss_transpiration[i];
		canopy[i].soil_evaporation				= soil_evaporation[i];
	}
}

void	DisassembleCanopyArray(int iLength,float* canopy_evaporation,
							float* canopy_transpiration_unsat,float* canopy_transpiration_sat,
							float* canopy_intercepted,float* litter_evaporation,
							float* moss_transpiration,float* soil_evaporation,float* canopy_stomata,Canopy_t* canopy)
{
	for (int i=0;i<iLength;i++)
	{
		canopy_evaporation[i]			= canopy[i].canopy_evaporation;
		canopy_stomata[i]		    	= canopy[i].canopy_stomata;
		canopy_transpiration_unsat[i]	= canopy[i].canopy_transpiration_unsat;
		canopy_transpiration_sat[i]		= canopy[i].canopy_transpiration_sat;
		canopy_intercepted[i]			= canopy[i].canopy_intercepted;
		litter_evaporation[i]			= canopy[i].litter_evaporation;
		moss_transpiration[i]			= canopy[i].moss_transpiration;
		soil_evaporation[i]				= canopy[i].soil_evaporation;
	}
}
// Energy routines added 2005-May-3  MM/Ajit
void	AssembleEnergyArray(int iLength,
						//	 float* climate_snowmelt,
							float *NRFlux,
						    float* sensibleHeatFlux,
							float* latentHeatFlux,
							Energy * energy)
{
	for (int i=0;i<iLength;i++)
	{
		energy[i].NRFlux     		=	NRFlux[i];
		energy[i].sensibleHeatFlux	=	sensibleHeatFlux[i];
		energy[i].latentHeatFlux	=	latentHeatFlux[i];
	}
}

void	DisassembleEnergyArray(int iLength,
							float* NRFlux,
							float* sensibleHeatFlux,
							float* latentHeatFlux,
							Energy * energy )
{
	for (int i=0;i<iLength;i++)
	{
	//	climate_snowmelt[i]				= climate[i].snowmelt;
		NRFlux[i]               = energy[i].NRFlux;
		sensibleHeatFlux[i]		= energy[i].sensibleHeatFlux;
		latentHeatFlux[i]		= energy[i].latentHeatFlux;
	}
}





// snow routines added 2005-May-3  MM/Ajit
void	AssembleSnowArray(int iLength,
						//	 float* climate_snowmelt,
							float*   swe,
						    float*   depth,
							float*   desnity,
							Snow_t * snow)
{
	for (int i=0;i<iLength;i++)
	{
		snow[i].SWE  	=	swe[i];
		snow[i].Depth	=	depth[i];
		snow[i].Density =	desnity[i];
	}
}

void	DisassembleSnowArray(int iLength,
							float* swe,
							float* depth,
							float* density,
							Snow_t * snow )
{
	for (int i=0;i<iLength;i++)
	{
	//	climate_snowmelt[i]				= climate[i].snowmelt;
		swe[i]          = snow[i].SWE;
		depth[i]		= snow[i].Depth;
		density[i]		= snow[i].Density;
	}
}
