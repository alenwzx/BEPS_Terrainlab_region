/*************************************************************************
  Program:     model.c
  --------
  Description:
  -----------
	Simulate carbon and water cycles for a single pixel on a day.
***************************************************************************
  OTHER UPDATES:
  1.	Date:			August 24, 2003
		Author:			A. Bulynko
		Description:	g- and z- buffers were added to the function's
						parameter list. these buffers will now be allocated
						in the top level routine responsible for
						memory management.
*****************************************************************************/
#include "stdafx.h"
#include "BepsHydrScience.h"
#include "string.h"
#include "malloc.h"
#include "stdio.h"
#include "math.h"

void model(double soilt,double snow_acc,double snow_today,float T_m,int jday,double sad,int pix,int day_start,double lat_p,double lai_p,
		   double soil_depth,unsigned char lc_p,double *x,double *b,climatedata *sdat,
		   xvalue *xx,Canopy_t *canopy,double* g, double* z,BH_SubParams2_t* pBH_SubParams2)
{

	double bz,beta;

    beta=b[37];									// the decayed rate of roots

	//blank all intermediate values
	memset(g,0,SIZEG*sizeof(double));
    memset(z,0,SIZEZ*sizeof(double));
	memset(x,0,SIZEX*sizeof(double));

	if(jday==day_start)
	{
		readxx(pix,x,xx);						// read snowpack and others
		setx(lc_p,x,b,pBH_SubParams2);       	// set x[2]-x[10]
	}
	else{
		readxx(pix,x,xx);						//read & compute forest-bgc daily climate data
	}

	/* compute Canopy Radiation Distribution */
	zcomp(jday,pix,lat_p,lc_p,soil_depth,lai_p,b,x,z,sdat,pBH_SubParams2);

	//daily water and carbon dynamics
	doflux(jday,T_m,sad,soilt,snow_acc,snow_today,b,g,x,z,lc_p,pBH_SubParams2);

	/* writing forest-bgc daily climate data */
  	writexx(pix,x,xx);

	/* 冠层和地表的水文过程 */
	/* 冠层蒸发 */
	canopy->canopy_evaporation			= (float)( g[4]	*1000.0);	//mm
	/* 冠层阴阳叶的蒸腾 */
	canopy->canopy_transpiration_unsat	= MAX(0.0, (float)(g[66]*1000.0));	//mm
	canopy->canopy_transpiration_sat	= MAX(0.0, (float)(g[67]*1000.0));	//mm
	/* 冠层的气孔导度 */
	canopy->canopy_stomata			    = (float)(g[22] *1000/2);	//convert units if required
	/* 冠层的截留 */
	canopy->canopy_intercepted			= (float)(g[11]	*1000.0);	//mm
	/* 凋落物蒸发 */
	canopy->litter_evaporation			= (float)(g[37]	*1000.0);	//mm
	/* 苔藓蒸发 */
	canopy->moss_transpiration			= (float)0.0;				//mm
	/* 土壤蒸发 */
	canopy->soil_evaporation			= (float)(g[12]	*1000.0);	//mm

}


void setx(unsigned char lc_p,double *x,double *b,BH_SubParams2_t* pBH_SubParams2)
    {
/* Set x[3] to x[7], x[11]-x[19] to zero */
    x[3]=0.0;
    x[4]=0.0;
    x[5]=0.0;
    x[6]=0.0;
    x[7]=0.0;
    x[11]=0.0;
    x[12]=0.0;
	x[13]=0.0;
	x[14]=0.0;
	x[15]=0.0;
	x[16]=0.0;
	x[17]=0.0;
	x[18]=0.0;
	x[19]=0.0;
	x[33]=0.0;
	x[36]=0.0;

	if ((lc_p >= pBH_SubParams2->iMinConifer) && (lc_p >= pBH_SubParams2->iMaxConifer))
	{
		if (x[9]==0)
			x[9]=10.1;										/* stem biomass Canada average in Inv.*/
   		   x[10]=0.2317*x[9];									/* root biomass in t/h b */
	}
	else if ((lc_p >= pBH_SubParams2->iMinDecidious) && (lc_p >= pBH_SubParams2->iMaxDecidious))
	{
		if (x[9]==0)
			x[9]=8.8;										/* stem biomass Canada average in Inv. */
   		x[10]=exp(0.359)*pow(x[9],0.639);					/* root biomass in t/h */
	}
	else if ((lc_p >= pBH_SubParams2->iMinMixed)		&&	(lc_p >= pBH_SubParams2->iMaxMixed))
	{
    	if (x[9]==0)
			x[9]=8.1;										/* stem biomass Canada average in Inv. */
   		x[10]=0.5*(0.2317*x[9]+exp(0.359)*pow(x[9],0.639));	/* root biomass in t/h */
	}
	else if ((lc_p >= pBH_SubParams2->iMinAgricultural)		&&	(lc_p >= pBH_SubParams2->iMaxAgricultural))
	{
		x[9]=1.0;
   		x[10]=0.2;
	}
	else if ((lc_p >= pBH_SubParams2->iMinPasture)		&&	(lc_p >= pBH_SubParams2->iMaxPasture))
	{
		x[9]=1.0;
   		x[10]=0.2;
	}
	else if ((lc_p >= pBH_SubParams2->iMinOpen)			&&	(lc_p >= pBH_SubParams2->iMaxOpen))
	{
		x[9]=1.0;
   		x[10]=0.2;
	}
	else if ((lc_p >= pBH_SubParams2->iMinWater)		&&	(lc_p >= pBH_SubParams2->iMaxWater))
	{
		x[9]=1.0;
   		x[10]=0.2;
	}
	else if ((lc_p >= pBH_SubParams2->iMinUrban)		&&	(lc_p >= pBH_SubParams2->iMaxUrban))
	{
		x[9]=1.0;
   		x[10]=0.2;
	}
	else
	{
		x[9]=1.0;
   		x[10]=0.2;
    }
}



