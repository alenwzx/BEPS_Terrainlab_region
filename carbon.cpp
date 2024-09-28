/*************************************************************************
  Program:     carbon.c
  --------
  Description:
  -----------
	Estimate photosythesis and plant respiration.
  Details:
  -------
 	Use Farquhar's model for photosynthesis calculation

	INPUTS:
	b[25]	: Q10 for leaf
	b[28]	: Q10 for stem
	b[29]	: Q10 for root

	b[19]	: leaf maintenance res. coe
	b[20]	: stem maintenance res. coe
	b[21]	: coarse root maintenance res. coe
	b[24]	: fine root maintenance res. coe
	x[8]	: leafC
	x[9]	: stemC
	x[10]	: rootC
	z[4]	: Tmax
	z[5]	: Tmin
	z[10]	: LAI
	z[14]	: daylight average temperature
	z[18]	: daylength

	OUTPUTS
	g[25]	: leaf Rm(forest) or total Rm (other land cover) in kg C/m2/day
***************************************************************************
  CCRS (EMS/Applications Division)
  Written by:   J. Liu
  Last update:	December 2000
*****************************************************************************/
#include "stdafx.h"
#include "BepsHydrScience.h"
#include <math.h>


void carbon(int jday,float T_m,double *b,double *g,double *x,double *z,BH_SubParams2_t* pBH_SubParams2)
//  double b[], g[], x[], z[];
{
  double exponent;
  double exponent2;
  double sapw_max=0.1;
  double rf25, pr;		/* for Rm with Bonan (1995) */
  int lc_p;
  double ratio_froot=1;
  double tb;			/* base temperature */
 // double q1,q2;

/* RESPIRATION	*/

/* leaf day time maintenance respiration*/
/* a equation below can overwrite this one */

  if(jday< 170 && x[33] <=7){tb=35;}
  else tb=12; //17
    exponent=(z[14]-tb)/10.0;
   exponent2=(z[14]-(tb-5))/10.0;
    g[23] = x[8]*b[19]*pow(b[25],exponent)*z[18]/86400;
    g[23] = MAX( g[23], 0.0);






//if (jday>=95 && jday <=330)  ×ÔÐÐÐÞ¸Ä
if (jday>=0 && jday <=366)
{
/* gross psn
  Calling Farquahar three times for explicit  calculation of  photosynthesis for overstorey,
  understorey and moss Assuming understorey LAI from negative  exponential model and moss LAI as 0.75
  No sunlit sahaded seperation.
*///||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
MAX(0,(farq_psn(b,z,x,g,pBH_SubParams2)));
MAX(0,(farq_psn_under(b,z,x,g,pBH_SubParams2)));
MAX(0,(farq_psn_moss(b,z,x,g,pBH_SubParams2)));
/* daily gross psn */
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

}

	//********************partitioning overstorey carbon***************

	double beta;
	b[99]	= z[18];											// daylength transfer
	if(x[19]>0)
	beta		=MIN(1.0,pow(b[37],x[19]*100.0)); //100 to convert to cm
	else beta=1.0;
	beta	    =MAX(0,beta);


	double bz_u;

	if(x[19]>0)
	bz_u		=MIN(1.0,pow((b[37]/1.25),x[19]*100.0)); //100 to convert to cm
	else bz_u=1.0;
	bz_u	    =MAX(0,bz_u);



	//********************partitioning overstorey gpp***************


// GPP written out together ie over, under, moss

   g[24] = (((g[28]*z[32]*(1-beta))+(g[80]*z[32]*beta)+
			  (g[29]*z[33]*(1-beta))+(g[81]*z[33]*beta)) + g[44] + g[45])*z[18]*12/1000000000;  // with understorey and moss

g[24]=MAX(0, g[24]); //added @ EPHYSE


   //SUNLIT-SHADED 3 LAYER
//Autotrophic Respiration
	lc_p=(int)z[23];

	if (	((lc_p >= pBH_SubParams2->iMinConifer)	&&	(lc_p >= pBH_SubParams2->iMaxConifer))
		||	((lc_p >= pBH_SubParams2->iMinDecidious)&&	(lc_p >= pBH_SubParams2->iMaxDecidious))
		||	((lc_p >= pBH_SubParams2->iMinMixed)	&&	(lc_p >= pBH_SubParams2->iMaxMixed)))
	{


		x[8]= z[10]/b[1];

		/* leaf night time maintenance respiration */
		//exponent=(z[15]-tb)/10.0;
		//g[25] =x[8]*b[19]*pow(b[25],exponent)*(86400.0-z[18])/86400;
		g[25] =(x[52]/1000)*b[19]*pow(b[25],exponent);
		g[25] = MAX( g[25], 0.0);

		/* stem maintenance respiration */
		//exponent=(z[15]-tb)/10.0;
		//g[30] = (0.05*x[9]*0.1)/(0.05*x[9]+0.1)*b[20]*pow(b[28],exponent);
		g[30] = (x[50]/1000)*0.05*b[20]*pow(b[28],exponent);
		g[30] = MAX( g[30], 0.0);


		/* root maintenance respiration */
		//exponent=(z[15]-tb)/10.0;
		ratio_froot=exp(1.007)*pow(x[10],-(0.841));
		ratio_froot=MIN(0.9, ratio_froot);

		//g[31]=0.05*x[10]*(1-ratio_froot)*b[21]*pow(b[29],exponent);		/*coarse root */
		//g[31]=g[31]+0.05*x[10]*ratio_froot*b[24]*pow(b[29],exponent);	/* coarse + fine root */
		g[31]=(x[51]/1000)*0.05*b[21]*pow(b[29],exponent2);
		g[31]=g[31]+(x[53]/1000)*0.05*b[24]*pow(b[29],exponent2);
		g[31] = MAX(g[31], 0.0);


	}
	//break;
	//case 23: case 24: case 25: case 26: case 27: case 28:	/* agricultural land */
	else if ((lc_p >= pBH_SubParams2->iMinAgricultural)	&& (lc_p >= pBH_SubParams2->iMaxAgricultural))
	{
		rf25=0.50;
		pr=0;
		/* g[25] is total rm in kg C/m2/day*/
		g[30]=0.0;
		g[31]=0.0;
		g[25] = 0.00368*0.5*(1*z[10])*rf25*(1+pr)*pow(0.5, 0.1*(0.5*(z[4]+z[5])-25.0))/1000;
   	}
	//break;
	//case 16:												/* pasture */
	else if ((lc_p >= pBH_SubParams2->iMinPasture) && (lc_p >= pBH_SubParams2->iMaxPasture))
	{
		rf25=0.5;
		pr=0;
		/* g[25] is total rm in kg C/m2/day*/
		g[30]=0.0;
		g[31]=0.0;
		g[25] = 0.00368*0.25*(0.250*z[10])*rf25*(1+pr)*pow(0.5, 0.1*(0.5*(z[4]+z[5])-25.0))/1000;
	}
	//break;
	// new land cover types MM 2005-Apr-25
	else if ((lc_p >= pBH_SubParams2->iMinOpen) && (lc_p >= pBH_SubParams2->iMaxOpen))
	{
		rf25=0;
		pr=0;
		/* g[25] is total rm in kg C/m2/day*/
		g[30]=0.0;
		g[31]=0.0;
		g[25] =0;// 1.0368*(2*z[10])*rf25*(1+pr)*pow(2, 0.1*(0.5*(z[4]+z[5])-25.0))/1000;
	}
	//break;
	// new land cover types MM 2005-Apr-25
	else if ((lc_p >= pBH_SubParams2->iMinWater) && (lc_p >= pBH_SubParams2->iMaxWater))
	{
		rf25=0.5;
		pr=0;
		/* g[25] is total rm in kg C/m2/day*/
		g[30]=0.0;
		g[31]=0.0;
		g[25] = 0;//1.0368*(2*z[10])*rf25*(1+pr)*pow(2, 0.1*(0.5*(z[4]+z[5])-25.0))/1000;
	}
	//break;
	// new land cover types MM 2005-Apr-25
	else if ((lc_p >= pBH_SubParams2->iMinUrban) && (lc_p >= pBH_SubParams2->iMaxUrban))
	{
		rf25=0.5;
		pr=0;
		/* g[25] is total rm in kg C/m2/day*/
		g[30]=0.0;
		g[31]=0.0;
		g[25] = 0;//1.0368*(2*z[10])*rf25*(1+pr)*pow(2, 0.1*(0.5*(z[4]+z[5])-25.0))/1000;
	}
	//break;
	//default:												/* other land cover types */
	else
	{
		rf25=0.25;
		pr=0;
		g[30]=0.0;
		g[31]=0.0;
		g[25] = 1.0368*(2*z[10])*rf25*(1+pr)*pow(2, 0.1*(0.5*(z[4]+z[5])-25.0))/1000;
	}


/* 24HR. NET C/m2  NPP Caqlculation */

g[26] = 0.70*g[24]-g[25]-g[30]-g[31]; //earlier with one canopy layer
g[26]=MAX(0, g[26]);

//if(jday<178)
//g[26] = (0.75*g[24])-(((g[25]+g[30]+g[31])*0.40));  //in winter time, no moss and understory
//else
//g[26] = (0.75*g[24])-(g[25]+g[30]+g[31])-((0.5*g[25])+(0.5*g[30])+(0.5*g[31]))-((0.15*g[25])+(0.150*g[30])+(0.150*g[31]));



	return;

    }


int farq_psn(double *b,double *z,double *x,double *g,BH_SubParams2_t* pBH_SubParams2)
//	double z[], g[];
{
	double pa; 		/* (Pa) atmospheric pressure */
//	double co2;		/* (ppm) atmospheric [CO2] */
	double t;		/* (deg C) air temperature */
	double irad;	/* (umol/m2/s) PAR photon flux density */
	double gg,gg_sat;      /* (m/s) conductance to CO2 */
	double Rd;		/* (umol/m2/s) dark respiration rate  */
	double tk;     /* (K) absolute temperature */
	double O2;     /* (Pa) atmospheric partial pressure O2 */
	double Ca;     /* (Pa) atmospheric partial pressure CO2 */
	double gamma;  /* (Pa) co2 compensation point, no dark respiration */
	double Kc;     /* (Pa) MM constant for carboxylase reaction */
	double Ko;     /* (Pa) MM constant for oxygenase reaction */
	double act;    /* (umol/kgRubisco/s) Rubisco activity */
	double Vmax;   /* (umol/m2/s) maximum carboxylation velocity */
	double Jmax;   /* (umol/m2/s) maximum rate of electron transport */
	double J;      /* (umol/m2/s) maximum rate of Rubisco regeneration */
	double Av;     /* (umol/m2/s) Rubisco limited assimilation rate */
	double Aj;     /* (umol/m2/s) RuBP regeneration limited assim rate */
	double A;      /* (umol/m2/s) net assimilation rate */
	double Vmax25;
	double Nratio;
	int short lc_p;

	double kk,aa,bb,cc,dd,ee, term1,term2,term3;

	static double fnr		= 7.16;   	/* kg Rub/kg NRub */
	static double Kc25		= 30.0; 	/* (Pa) MM const carboxylase, 25 deg C */
	static double q10Kc		= 2.1;    	/* (DIM) Q_10 for kc */
	static double Ko25		= 30000.0;  /* (Pa) MM const oxygenase, 25 deg C */
	static double q10Ko		= 1.2;   	/* (DIM) Q_10 for ko */
	static double act25		= 3.6;    	/* (umol/mgRubisco/min) Rubisco activity */
	static double q10act	= 2.4;  	/* (DIM) Q_10 for Rubisco activity */
	int				i;					/* index for sunlit/shaded leaves, 0: sun, 1 shade */
  	for (i=0;i<=3;i++) //4 loops
        {

	/* convert w/m2 to umol/m2/s */
	if ((i==0) ||(i==2)  ) irad=2.04*z[34];
	else
          irad=2.04*z[35];

	t = z[14];
	tk = t + 273.15;

	if (i==0) gg=g[20] ;
	else if (i==1)gg=g[60];
	else if (i==2)gg=g[21];
  	else   gg=g[61];


	/* convert conductance from m/s --> umol/m2/s/Pa */
	gg =(gg/1.6* 1000000) / (8.3143 * tk);

	/* calculate the atomsheric pressure */
	pa=100000;

	/* convert atmospheric CO2 from ppm --> Pa */
	Ca = 370 * pa / 1e6;

	/* calculate atmospheric O2 in Pa, assumes 21% O2 by volume */
	O2 = 0.21 * pa;

	/* correct kinetic constants for temperature, and do unit conversions */
	Ko = Ko25 * pow(q10Ko, (t-25.0)/10.0);
	Kc = Kc25 * pow(q10Kc, (t-25.0)/10.0);
	act = pow(q10act, (t-b[16])/10.0); // earlier 25 //b[16] is the Optimum temp

	/* calculate gamma (Pa), assumes Vomax/Vcmax = 0.21 */
	gamma = 4.02*pow(1.75, (t-25)/10);

	double f_T= 1;//1/(1+exp((-220000+(710*(t+273)))/(8.314*(t+273))));

	/**************** Modification according to Bonan ************* */

	lc_p=(int)z[23];

	Vmax25=b[52];
	//Nratio=1;//b[54]/b[53]; //test
	Nratio=MAX(1,(x[36]/b[53]));///b[53];

	Vmax=Nratio*Vmax25*act*f_T;

	/**************** End of the modification ********************/

	/* calculate Jmax = f(Vmax) */

	Jmax = 29.1 + 1.64*Vmax;

	/* calculate J = f(Jmax, I) */
	J = Jmax * irad / (irad + 2.1*Jmax);

	/* Rd */
  	Rd=0.015*Vmax;
	g[23]=Rd*z[18]*12.01;
/***************** With daily integration **************************/
	kk=Kc*(1+O2/Ko);

/* Av */
	Av=0;

    	aa = (kk+Ca)*(kk+Ca);
    	bb = 2*(2*gamma+kk-Ca)*Vmax+2*(Ca+kk)*Rd;
    	cc = (Vmax-Rd)*(Vmax-Rd);

     	if (aa>0 && cc>0)
        {
	dd = sqrt(aa*gg*gg+bb*gg+cc);
	ee = (bb*bb-4*aa*cc)/(8*aa*sqrt(aa));
	term1=sqrt(aa)*gg*gg/2+sqrt(cc)*gg;
	term2=((2*aa*gg+bb)*dd-bb*sqrt(cc))/(4*aa);
	term3=ee*(log(2*aa*gg+bb+2*sqrt(aa)*dd)-log(bb+2*sqrt(aa)*sqrt(cc)));
	if (gg!=0) Av=0.5*1.27*(term1-term2+term3)/gg;
	}

/* Aj */
 	Aj=0;

	aa = (2.33*gamma+Ca)*(2.33*gamma+Ca);
    	bb = 0.4*(4.3*gamma-Ca)*J+2*(Ca+2.3*gamma)*Rd;
    	cc = (0.22*J-Rd)*(0.22*J-Rd);

      	if (aa>0 && cc>0)
        {
	dd = sqrt(aa*gg*gg+bb*gg+cc);
	ee = (bb*bb-4*aa*cc)/(8*aa*sqrt(aa));

	term1=sqrt(aa)*gg*gg/2+sqrt(cc)*gg;
	term2=((2*aa*gg+bb)*dd-bb*sqrt(cc))/(4*aa);
	term3=ee*(log(2*aa*gg+bb+2*sqrt(aa)*dd)-log(bb+2*sqrt(aa)*sqrt(cc)));

	if (gg!=0) Aj=0.5*1.27*(term1-term2+term3)/gg;

	}

	/* calculate A as the minimum of (Av,Aj) */
	if (Av < Aj) A = Av;
	else         A = Aj;

	/* primary output */

	if (i==0) g[28]=A;
	else if (i==1) g[80]=A;
	else if (i==2) g[29]=A;
	else g[81]=A;

   }
	return 1;
 }



 /*********************************************************************************************

This  will do the calculation of photosynthesis for understorey. For simplicity, the total
GPP is in one variable. Now it is revised as over storey + understorey+moss. The understorey
LAI is  negative exponentially related.
Ajit 12 may 2006
**********************************************************************************************/
int farq_psn_under(double *b,double *z,double *x,double *g,BH_SubParams2_t* pBH_SubParams2)
//	double z[], g[];
{
	double pa_u; 		/* (Pa) atmospheric pressure */
//	double co2;		/* (ppm) atmospheric [CO2] */
	double t_u;		/* (deg C) air temperature */
	double irad_u;	/* (umol/m2/s) PAR photon flux density */
	double gg_u;      /* (m/s) conductance to CO2 */
	double Rd_u;		/* (umol/m2/s) dark respiration rate  */
//	double lnc;		/* (kg Nleaf/m2) leaf N concentration, area units */
//	double flnr;	/* (kg NRub/kg Nleaf) fraction of leaf N in Rubisco */

	double tk_u;     /* (K) absolute temperature */
	double O2_u;     /* (Pa) atmospheric partial pressure O2 */
	double Ca_u;     /* (Pa) atmospheric partial pressure CO2 */
	double gamma_u;  /* (Pa) co2 compensation point, no dark respiration */
	double Kc_u;     /* (Pa) MM constant for carboxylase reaction */
	double Ko_u;     /* (Pa) MM constant for oxygenase reaction */
	double act_u;    /* (umol/kgRubisco/s) Rubisco activity */
	double Vmax_u;   /* (umol/m2/s) maximum carboxylation velocity */
	double Jmax_u;   /* (umol/m2/s) maximum rate of electron transport */
	double J_u;      /* (umol/m2/s) maximum rate of Rubisco regeneration */
	double Av_u;     /* (umol/m2/s) Rubisco limited assimilation rate */
	double Aj_u;     /* (umol/m2/s) RuBP regeneration limited assim rate */
	double A_u;      /* (umol/m2/s) net assimilation rate */
	double Vmax25_u;
	double Nratio_u;
	int short lc_p_u;


	double kk_u,aa_u,bb_u,cc_u,dd_u,ee_u, term1_u,term2_u,term3_u;

	static double fnr_u		= 7.16;   	/* kg Rub/kg NRub */
	static double Kc25_u		= 30.0; 	/* (Pa) MM const carboxylase, 25 deg C */
	static double q10Kc_u		= 2.1;    	/* (DIM) Q_10 for kc */
	static double Ko25_u		= 30000.0;  /* (Pa) MM const oxygenase, 25 deg C */
	static double q10Ko_u		= 1.2;   	/* (DIM) Q_10 for ko */
	static double act25_u		= 3.6;    	/* (umol/mgRubisco/min) Rubisco activity */
	static double q10act_u	= 2.4;  	/* (DIM) Q_10 for Rubisco activity */
					/* index for sunlit/shaded leaves, 0: sun, 1 shade */

	/* convert w/m2 to umol/m2/s */
	 irad_u=2.04*(z[34]+z[35])*exp(-(z[32]+z[33]));

	t_u = z[14];
	tk_u = t_u + 273.15;



	gg_u=g[19];
	/* convert conductance from m/s --> umol/m2/s/Pa */

	gg_u =gg_u/1.6 * 1000000 / (8.3143 * tk_u); //USABLE
	//gg_u =(gg_u* 1000000) / (0.0224*1.6*(tk_u/273.16));	//Sellers
	/* calculate the atomsheric pressure */
	pa_u=100000;

	/* convert atmospheric CO2 from ppm --> Pa */
	Ca_u =370*pa_u/1e6;

	/* calculate atmospheric O2 in Pa, assumes 21% O2 by volume */
	O2_u = 0.21 * pa_u;

	/* correct kinetic constants for temperature, and do unit conversions */
	Ko_u = Ko25_u * pow(q10Ko_u, (t_u-25.0)/10.0);
	Kc_u = Kc25_u * pow(q10Kc_u, (t_u-25.0)/10.0);
	act_u = pow(q10act_u, (t_u-b[16])/10.0); //earlier 25
	double f_T= 1;//1/(1+exp((-220000+(710*(t_u+273)))/(8.314*(t_u+273))));
	/* calculate gamma (Pa), assumes Vomax/Vcmax = 0.21 */
	gamma_u = 4.02*pow(1.75, (t_u-25)/10);
	//double f_T= (1+exp((-220000+(710*(t+273)))/(8.314*(t+273))));
	/**************** Modification according to Bonan ************* */

	lc_p_u=(int)z[23];

	Vmax25_u=65;  //understory id deciduous shrubs
//Nratio_u=1;//b[54]/b[53];
	Nratio_u=MAX(1, (x[36]/b[53]));///b[53];
	Vmax_u=Nratio_u*Vmax25_u*act_u*f_T;

	/**************** End of the modification ********************/

	/* calculate Jmax = f(Vmax) */

	Jmax_u = 29.1 + 1.64*Vmax_u;

	/* calculate J = f(Jmax, I) */
	J_u = Jmax_u * irad_u / (irad_u + 2.1*Jmax_u);

	/* Rd */
  	Rd_u=0.015*Vmax_u;
	g[23]=Rd_u*z[18]*12.01;
/***************** With daily integration *****************************/
	kk_u=Kc_u*(1+O2_u/Ko_u);

/* Av */
	Av_u=0;

    	aa_u = (kk_u+Ca_u)*(kk_u+Ca_u);
    	bb_u = 2*(2*gamma_u+kk_u-Ca_u)*Vmax_u+2*(Ca_u+kk_u)*Rd_u;
    	cc_u = (Vmax_u-Rd_u)*(Vmax_u-Rd_u);

     	if (aa_u>0 && cc_u>0)
        {
	dd_u = sqrt(aa_u*gg_u*gg_u+bb_u*gg_u+cc_u);
	ee_u = (bb_u*bb_u-4*aa_u*cc_u)/(8*aa_u*sqrt(aa_u));

	term1_u=sqrt(aa_u)*gg_u*gg_u/2+sqrt(cc_u)*gg_u;
	term2_u=((2*aa_u*gg_u+bb_u)*dd_u-bb_u*sqrt(cc_u))/(4*aa_u);
	term3_u=ee_u*(log(2*aa_u*gg_u+bb_u+2*sqrt(aa_u)*dd_u)-log(bb_u+2*sqrt(aa_u)*sqrt(cc_u)));

	if (gg_u!=0) Av_u=0.5*1.27*(term1_u-term2_u+term3_u)/gg_u;

		}

/* Aj */
 	Aj_u=0;

	aa_u = (2.33*gamma_u+Ca_u)*(2.33*gamma_u+Ca_u);
    	bb_u = 0.4*(4.3*gamma_u-Ca_u)*J_u+2*(Ca_u+2.3*gamma_u)*Rd_u;
    	cc_u = (0.22*J_u-Rd_u)*(0.22*J_u-Rd_u);

      	if (aa_u>0 && cc_u>0)
        {
	dd_u = sqrt(aa_u*gg_u*gg_u+bb_u*gg_u+cc_u);
	ee_u = (bb_u*bb_u-4*aa_u*cc_u)/(8*aa_u*sqrt(aa_u));

	term1_u=sqrt(aa_u)*gg_u*gg_u/2+sqrt(cc_u)*gg_u;
	term2_u=((2*aa_u*gg_u+bb_u)*dd_u-bb_u*sqrt(cc_u))/(4*aa_u);
	term3_u=ee_u*(log(2*aa_u*gg_u+bb_u+2*sqrt(aa_u)*dd_u)-log(bb_u+2*sqrt(aa_u)*sqrt(cc_u)));

	if (gg_u!=0) Aj_u=0.5*1.27*(term1_u-term2_u+term3_u)/gg_u;

	}


	if (Av_u < Aj_u) A_u = Av_u;
	else         A_u = Aj_u;


	 g[44]=A_u;



	return 1;
 }


 /*****************************************************************
FOR MOSS
AJIT
******************************************************************/
int farq_psn_moss(double *b,double *z,double *x,double *g,BH_SubParams2_t* pBH_SubParams2)
//	double z[], g[];
{
	double pa_moss; 		/* (Pa) atmospheric pressure */
//	double co2;		/* (ppm) atmospheric [CO2] */
	double t_moss;		/* (deg C) air temperature */
	double irad_moss;	/* (umol/m2/s) PAR photon flux density */
	double gg_moss;      /* (m/s) conductance to CO2 */
	double Rd_moss;		/* (umol/m2/s) dark respiration rate  */
//	double lnc;		/* (kg Nleaf/m2) leaf N concentration, area units */
//	double flnr;	/* (kg NRub/kg Nleaf) fraction of leaf N in Rubisco */

	double tk_moss;     /* (K) absolute temperature */
	double O2_moss;     /* (Pa) atmospheric partial pressure O2 */
	double Ca_moss;     /* (Pa) atmospheric partial pressure CO2 */
	double gamma_moss;  /* (Pa) co2 compensation point, no dark respiration */
	double Kc_moss;     /* (Pa) MM constant for carboxylase reaction */
	double Ko_moss;     /* (Pa) MM constant for oxygenase reaction */
	double act_moss;    /* (umol/kgRubisco/s) Rubisco activity */
	double Vmax_moss;   /* (umol/m2/s) maximum carboxylation velocity */
	double Jmax_moss;   /* (umol/m2/s) maximum rate of electron transport */
	double J_moss;      /* (umol/m2/s) maximum rate of Rubisco regeneration */
	double Av_moss;     /* (umol/m2/s) Rubisco limited assimilation rate */
	double Aj_moss;     /* (umol/m2/s) RuBP regeneration limited assim rate */
	double A_moss;      /* (umol/m2/s) net assimilation rate */
	double Vmax25_moss;
	double Nratio_moss;
	int short lc_p_moss;


	double kk_moss,aa_moss,bb_moss,cc_moss,dd_moss,ee_moss, term1_moss,term2_moss,term3_moss;

	static double fnr_moss		= 7.16;   	/* kg Rub/kg NRub */
	static double Kc25_moss		= 30.0; 	/* (Pa) MM const carboxylase, 25 deg C */
	static double q10Kc_moss		= 2.1;    	/* (DIM) Q_10 for kc */
	static double Ko25_moss		= 30000.0;  /* (Pa) MM const oxygenase, 25 deg C */
	static double q10Ko_moss		= 1.2;   	/* (DIM) Q_10 for ko */
	static double act25_moss		= 3.6;    	/* (umol/mgRubisco/min) Rubisco activity */
	static double q10act_moss	= 2.4;  	/* (DIM) Q_10 for Rubisco activity */
					/* index for sunlit/shaded leaves, 0: sun, 1 shade */

	/* convert w/m2 to umol/m2/s */
	 irad_moss=2.04*((z[34]+z[35])*exp(-(z[32]+z[33]+1.5/*z[42]*/))); // light exponentially decreases

	t_moss = z[14]; //temp small in forest floor
	tk_moss = t_moss + 273.15;

	double M= 18.8-(12.5*x[19]);//17; //M as a fn of Frolking 2002
  double gg_moss1=1*(-0.195+(0.134*M)-(0.0256*pow(M,2))+(0.00288*pow(M,3))-(0.0000984*pow(M,4))+(0.00000168*pow(M,5)));
 gg_moss= gg_moss1/(8.3143 * (273+z[14]));


	pa_moss=100000;

	/* convert atmospheric CO2 from ppm --> Pa */
	Ca_moss =370*pa_moss/1e6;

	/* calculate atmospheric O2 in Pa, assumes 21% O2 by volume */
	O2_moss = 0.21 * pa_moss;

	/* correct kinetic constants for temperature, and do unit conversions */
	Ko_moss = Ko25_moss * pow(q10Ko_moss, (t_moss-25.0)/10.0);
	Kc_moss = Kc25_moss * pow(q10Kc_moss, (t_moss-25.0)/10.0);
	act_moss = pow(q10act_moss, (t_moss-b[16])/10.0); //earlier 25
	double f_T= 1;//1/(1+exp((-220000+(710*(t_moss+273)))/(8.314*(t_moss+273))));
	/* calculate gamma (Pa), assumes Vomax/Vcmax = 0.21 */
	gamma_moss = 4.02*pow(1.75, (t_moss-25)/10);

	/**************** Modification according to Bonan ************* */

	lc_p_moss=(int)z[23];

	Vmax25_moss=20;
	//Nratio_moss=1;//b[54]/b[53];
	Nratio_moss=MAX(1, (x[36]/b[53]));;//;
	Vmax_moss=Nratio_moss*Vmax25_moss*act_moss*f_T;

	Jmax_moss = 29.1 + 1.64*Vmax_moss;

	/* calculate J = f(Jmax, I) */
	J_moss = Jmax_moss * irad_moss / (irad_moss + 2.1*Jmax_moss);

	/* Rd */
  	Rd_moss=0.015*Vmax_moss;
	g[23]=Rd_moss*z[18]*12.01;
/***************** With daily integration *****************************/
	kk_moss=Kc_moss*(1+O2_moss/Ko_moss);

/* Av */
	Av_moss=0;

    	aa_moss = (kk_moss+Ca_moss)*(kk_moss+Ca_moss);
    	bb_moss = 2*(2*gamma_moss+kk_moss-Ca_moss)*Vmax_moss+2*(Ca_moss+kk_moss)*Rd_moss;
    	cc_moss = (Vmax_moss-Rd_moss)*(Vmax_moss-Rd_moss);

     	if (aa_moss>0 && cc_moss>0)
        {
	dd_moss = sqrt(aa_moss*gg_moss*gg_moss+bb_moss*gg_moss+cc_moss);
	ee_moss = (bb_moss*bb_moss-4*aa_moss*cc_moss)/(8*aa_moss*sqrt(aa_moss));

	term1_moss=sqrt(aa_moss)*gg_moss*gg_moss/2+sqrt(cc_moss)*gg_moss;
	term2_moss=((2*aa_moss*gg_moss+bb_moss)*dd_moss-bb_moss*sqrt(cc_moss))/(4*aa_moss);
	term3_moss=ee_moss*(log(2*aa_moss*gg_moss+bb_moss+2*sqrt(aa_moss)*dd_moss)-log(bb_moss+2*sqrt(aa_moss)*sqrt(cc_moss)));

	if (gg_moss!=0) Av_moss=0.5*1.27*(term1_moss-term2_moss+term3_moss)/gg_moss;

		}

/* Aj */
 	Aj_moss=0;

	aa_moss = (2.33*gamma_moss+Ca_moss)*(2.33*gamma_moss+Ca_moss);
    	bb_moss = 0.4*(4.3*gamma_moss-Ca_moss)*J_moss+2*(Ca_moss+2.3*gamma_moss)*Rd_moss;
    	cc_moss = (0.22*J_moss-Rd_moss)*(0.22*J_moss-Rd_moss);

      	if (aa_moss>0 && cc_moss>0)
        {
	dd_moss = sqrt(aa_moss*gg_moss*gg_moss+bb_moss*gg_moss+cc_moss);
	ee_moss = (bb_moss*bb_moss-4*aa_moss*cc_moss)/(8*aa_moss*sqrt(aa_moss));

	term1_moss=sqrt(aa_moss)*gg_moss*gg_moss/2+sqrt(cc_moss)*gg_moss;
	term2_moss=((2*aa_moss*gg_moss+bb_moss)*dd_moss-bb_moss*sqrt(cc_moss))/(4*aa_moss);
	term3_moss=ee_moss*(log(2*aa_moss*gg_moss+bb_moss+2*sqrt(aa_moss)*dd_moss)-log(bb_moss+2*sqrt(aa_moss)*sqrt(cc_moss)));

	if (gg_moss!=0) Aj_moss=0.5*1.27*(term1_moss-term2_moss+term3_moss)/gg_moss;

	}

	/* calculate A as the minimum of (Av,Aj) */
	if (Av_moss < Aj_moss) A_moss = Av_moss;
	else         A_moss = Aj_moss;



	 g[45]=MAX(0,A_moss);



	return 1;
 }
