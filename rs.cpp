/*************************************************************************
  Program:     rs.c
  --------
  Description:
  -----------
	Output stomatal resistance/conductance.

	Input	:
	---------
		b[11] - max. canopy cond., h20  m s-1
		b[27] - soil characteristic parameter
		b[39] - Ratio of gmax of overstory to understory
		x[2]  - available soil water                                   //土壤水分
		x[19] - water table                                            //地下水位
		x[20] - soil texture - soil survey buffer
		z[5] - min. Air temperature						(deg c)
		z[9] - average incoming solar radiation			(W/m2)
		z[10] - LAI
		z[14] - daylight average air temperature			(deg c)
		z[16] - vapor pressure deficit	                               //VPD饱和水汽压差					(mb)
		z[20] - daily averaged absorbed radiation			(W/m2)
		z[23] - land cover type (index) (or lc_p )
		z[32] - sunlit LAI
		z[33] - shaded LAI
		z[36] - radiation over sunlit leaves at noon		(W/m2)
		z[37] - radiation over shaded leaves at noon		(W/m2)

	Output	:
	---------
		g[19] - canopy->litter_evaporation
		g[20] - final stomatal conductance for sunlit leaves
		g[21] - final stomatal conductance for shaded leaves
		g[22] - canopy conductance
***************************************************************************
  CCRS (EMS/Applications Division)
  Written by:   J. Liu
		(Based on BIOME-BGC)
  Last update:	May 1998
*****************************************************************************/
#include "stdafx.h"
#include "BepsHydrScience.h"
#include <math.h>

void rs(int jday,double *b,double *g,double *x,double *z, BH_SubParams2_t* pBH_SubParams2)
//    double b[], g[], x[], z[];
{

/* declaration for temporary variables/functions */
	double ppfd;
 	double tavg;
	double tmin;
	double Topt, Tmax,Tmin;
	double vpd,vpd_open,vpd_close;
	double psi,psi_open,psi_close,psi_sat;
	double m_tavg, m_tmin, m_psi, m_co2, m_ppfd, m_vpd,m_psi_2,m_soil;
	double m_most;
	double m_most_2;
	double lai;
    double r1,r2;
    double psi1,psi2,psi1_sat;

	double ppfd_coef;
	double cs,cc,cbl,cs_2;
	double i;	/* index for 0:sunlit leaves and 1:shaded leaves */
	double lai_under;
	int short lc_p;
// juw////////////////////////////////////////////////////
   // double r1,r2,w_table; // f_c
	double vsm_us;
    double ss,sf,sw;//porosity, field capacity, wilting point
    double w_table;
/////////////////////////////////////////////////////////////

//===============================================================================
	                 //Computing Slopes of temp and RH
double t1,t2,h1,h2,w1,w2;
t1 = z[14]+0.5;
t2 = z[14]-0.5;
h1= z[6]+0.5;
h2= z[6]-0.5;
w1=z[19]+0.5;
w2=z[19]-0.5;
g[82]= t1-t2;
g[83]= h1-h2;


//===============================================================================
	/* assign variables that are used more than once */
  	tavg =      z[14];  //日均温
	tmin =      z[5];
	vpd =       0.1*z[16];		/* in kPa */
	ppfd_coef=  b[12];
	Topt=b[16];
	Tmax=b[18];
    Tmin=b[17];
	psi =       1;
	lai =       z[10];

	psi_open = -b[14];			/* in -MPa */
	psi_close = -b[15];
	vpd_open =  2;		/* in mb */ // changed by Ajit from 7.5 after refering Chen (1999)
	vpd_close =20;      //这里VPD的修改是否影响了结果呢
	lc_p=(int short)z[23];
   switch(lc_p)
    {
    case 1:
    case 3://NF
        lai_under=1.175*exp(-0.991*z[10]);
        break;
    case 2:
    case 4://BF
        lai_under=1.5;
        break;

    case 5://MF
        lai_under=0.5*(1.5+1.175*exp(-0.991*z[10]));
        break;
    default:
        lai_under=0.0;

    }



	for(i=0;i<=1; i++)
	{
        if (i==0)
			ppfd =0.5*4.55*z[36];
        else
			ppfd=0.5*4.55*z[37];

		m_ppfd = ppfd * ppfd_coef / (1.0 + (ppfd * ppfd_coef));

		/* use the tempcurve function to generate the daily average air
		temperature conductance multiplier */

		if(tavg<Tmin || Tmax>40)
			m_tavg=0.0;
		else
		{
			if(tavg<Topt)
				m_tavg=log(tavg)/log(Topt);
			else
				m_tavg=cos(3.1415926*(tavg-Topt)/(2*(Tmax-Topt)));
			//m_tavg=cos(3.1415926*((tavg-Topt)/(2*(Tmax-Topt))));
		}
		//m_tavg=__max(0,m_tavg);

if (jday<200)   //为什么是小于200天时这样计算
m_tavg=0.45*m_tavg* (jday*0.01);//xtra




	//=====================================
			//origialstarts -->
			if (vpd < vpd_open)
			m_vpd=1;
			else if (vpd_open < vpd < vpd_close)
			m_vpd= ((vpd_close-vpd)/(vpd_close-vpd_open));
		//	m_vpd=__max(0,m_vpd);
			if (vpd> vpd_close)
				m_vpd=0;

if (jday<200)
m_vpd=0.45*m_vpd* (jday*0.01); //xtra

            //today m_vpd=1/(1+b[13]*vpd);

			//<---original ends */
	//=====================================



		/* leaf water potential pre-dawn  */

		sw = x[20]; // MM assign the wilting point
		sf = x[21]; // MM assign the field capacity
		ss = x[22]; // MM assign the porosity

// This modifier of soil water to stomatal cinductance is based on Jing's paper on Journal of Hydrology, 2005
w_table=x[19];
if(w_table>0.0){
vsm_us=x[2]/w_table;  // conver unsaturated_storage to volumetric soil moisture content;
//r1=1-pow(b[37],w_table*100.0); r1=__min(1.0,r1);r1=__max(0,r1); r2=1.0-r1;

if(vsm_us<=sw) psi1=0;
else if ((vsm_us>sw && vsm_us<=sf) ) psi1=(vsm_us-sw)/(sf-sw);
else if ((vsm_us>sf))  psi1=1.0-0.5*(vsm_us-sf)/(ss-sf);
}
else psi1=0.5; //if WT  <0
psi=psi1;               //psi:不同情况下非饱和带土壤体积含水量对气孔导度的影响

//SSaturated Zone

m_psi=psi;
m_psi_2=0.5; 	//Ajit adedd for saturated case


		/* CO2 multiplier */
		m_co2 = 1.0;

		/* freezing night minimum temperature multiplier */
		if (tmin > 0.0)        /* no effect */
			m_tmin = 1.0;
		else if (tmin < -8.0)  /* full tmin effect */
			m_tmin = 0.0;
		else                   /* partial reduction (0.0 to -8.0 C) */
			m_tmin = 1.0 + (0.125 * tmin);

		m_tmin = 1.0; // cancelling m-tmin !!!!!!!!!

		//Soil temperature multiplier
		m_soil= 0.176+(0.0770*z[14])-(0.0018*pow(z[14],2));

		if(m_soil <0)
		{
			m_soil=MAX(0,m_soil);
		}



		/* vapor pressure deficit multiplier, vpd in Pa */

		/* Deciduous lc=6 , mixed lc=7,8,9,10*/
		/*if (z[23]==6)
			m_vpd=1/(1+0.429*vpd);
		else if ((z[23]==7 || z[23]==8 ) || (z[23]==9 || z[23]==10))
			m_vpd=0.5*(1/(1+0.429*vpd)+ 1/(1+0.076*vpd));
		else
			m_vpd=1/(1+0.076*vpd);
        */

	//vpd place

		/* apply all multipliers to the maximum stomatal conductance */
		m_most= m_tavg * m_psi * m_co2 * m_tmin * m_vpd*m_soil;//unsaturated soil mositure scalar
		m_most_2= m_tavg * m_psi_2 * m_co2 * m_tmin * m_vpd*m_soil;//saturated soil mositure scalar


		/*g[84]=m_tavg;
		g[85]=m_psi;
		g[86]=m_tmin;
		g[87]=m_vpd;
		*/
		//	m_most=1;
		cs =b[9]*m_ppfd*m_most;
		cs_2 =b[9]*m_ppfd*m_most_2;//Ajit adedd for saturated case
		/* leaf boundary-layer conductance */
		cbl=b[55];

		/* leaf cuticular conductance */
		cc=b[56];

		/* final stomatal conductance for sunlit and shaded leaves  */
		if (i==0){
			g[20] = cbl*(cc+cs)/(cbl+cc+cs);  //sunlit,unsat
		   if(cs<=0)g[20]=0;

			g[60] = cbl*(cc+cs_2)/(cbl+cc+cs_2);  //Ajit added sunlit,sat
		   if(cs_2<=0)g[60]=0;
		}
		else{
		    g[21] = cbl*(cc+cs)/(cbl+cc+cs);	// shaded,unsat
			if(cs<=0)g[21]=0;

			g[61] = cbl*(cc+cs_2)/(cbl+cc+cs_2);  //Ajit added shaded,sat
			if(cs_2<=0)g[61]=0;

		}

		}


	/* canopy conductance */
    g[22]=g[20]*z[32]+g[21]*z[33];
	/* canopy conductance for big leaf model

	ppfd=0.5*4.55*z[20];

	m_ppfd = ppfd * ppfd_coef / (1.0 + (ppfd * ppfd_coef));

	g[22]=z[10]*b[11]*m_ppfd*m_most;
	*/
	/* understory conductance */



	ppfd=0.5*4.55*(z[9]-z[20]);

	m_ppfd = ppfd * ppfd_coef / (1.0 + (ppfd * ppfd_coef));
	g[19]=(b[9]/b[11])*m_ppfd*m_most*(lai_under);//lai_under*g[20];//
	g[77]=(b[9]/b[11])*m_ppfd*m_most_2*(lai_under);//*lai_under;
	//g[78]=lai_under;
    return;
}
