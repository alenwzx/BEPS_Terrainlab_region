/*--------------------------------------------------------------*/
/*                                                              */
/*		compute_cap_rise				*/
/*                                                              */
/*  NAME                                                        */
/*		compute_cap_rise				*/
/*                                                              */
/*                                                              */
/*  SYNOPSIS                                                    */
/*  void compute_capillary_rise(soil)				*/
/*					                                            */
/*  OPTIONS                                                     */
/*	int	verbose_flag					*/
/*	double	Z - (m) water table depth 			*/
/*	double	psi_1 - (Pa)  air_entry_pressure		*/
/*	double	pore_size_index,				*/
/*	double	m - TOPMODEL conductivitity decay parameter	*/
/*	double	Ksat_0	- (m/day) sat. hydraulic conductivity	*/
/*				at the surface			*/
/*                                                              */
/*                                                              */
/*  DESCRIPTION                                                 */
/*                                                              */
/*	This routine estimates the rate of capillary rise in	*/
/*	a soil profile following the methods and assumptions	*/
/*	of Gardiner (1958) as found in Eagleson (1978).		*/
/*								*/
/*	A basic outline of the development is as follows:	*/
/*								*/
/*	i) Use a 1-D Richard's Equation:			*/
/*								*/
/*		dT = d [ K(T) [ d psi(T) + 1 ]			*/
/*		__   __         _______				*/
/*		dt   dz         dz                              */
/*								*/
/*	where T - theta (effective soil moisture content ) (0-1)*/
/*		= (actual water vol. - min. water vol. )/	*/
/*		  (porosity - min. water. vol. )		*/
/*	      t - time (s) 					*/
/*	      K(T) - vertical hydraulic conductivity as a 	*/
/*			function of T (m/s)			*/
/*	      psi(T) - soil matric potential as a function of 	*/
/*			T (Pa)					*/
/*	and,							*/
/*		we assume that down is positive,		*/
/*		we assume that K an psi functions are in terms  */
/*		of effective moisture content 			*/
/*								*/
/*	ii) We assume that steady state flow has been reached:	*/
/*								*/
/*		dT/dt = 0 OR					*/
/*                                                              */
/*		-w =  K(T) [ d psi(T) + 1 ]			*/
/*		            _______				*/
/*		             dz                            	*/
/*								*/
/*	iii) isolating for dz and integrating from Z to 0 gives */
/*								*/
/*		Z = int(B1..B2) [ d(psi(T)) ]			*/
/*				____________			*/
/*				1 + -w/K(T)			*/
/*								*/
/*	where B1 and B2 are boundary conditions for K,psi,z	*/
/*	for the soil at Z and 0 respectively.			*/
/*								*/
/*	This integral is non-trivial.				*/
/*								*/
/*	iv) Assuming:						*/
/*								*/
/*		K(T) = a * psi(T)^b				*/
/*								*/
/*	where a and b are NOT functions of z.			*/
/* 	The integral can be solved for w.			*/
/*	For example, with b = 2, A=sqrt(a):			*/
/*								*/
/*	w = (A/Z) [ arctan({psi(B2)/A}) - arctan{psi(b2)/A)}	*/
/*								*/
/*	v) Assuming psi(b2) = infinity and psi(b1) = 0		*/
/*								*/
/*	Gardiner (1958) provided an analytical approximation	*/
/*								*/
/*	w = w_max = Ba/(Z^b)					*/
/*								*/
/*	where B = 1 + 1.5/(b-1)					*/
/*								*/
/*	vi) The specification of a follows by assuming that	*/
/*								*/
/*	K(t)/K(1) = [psi(1)/psi(t)]^b				*/
/*								*/
/*	this assumption itself comes by assuminga Brooks and	*/
/*	Corey (1958) wetting curve for K(t) and psi(t):		*/
/*								*/
/*	k(t) = k(1)s^[(2+3m)/m]					*/
/*	psi(t) = psi(1)s^(-1/m)					*/
/*								*/
/*	and m is the pore size distribution index.		*/
/*								*/
/*	when b = [(2+3m)/m]*(-1/m)				*/
/*								*/
/*	a = k(1)[psi(1)]^b					*/
/*								*/
/*								*/
/*	Comments:						*/
/*								*/
/*	The first concern in using this formulation is		*/
/*	the steady state flow assumption.  However, if applied	*/
/*	at daily time steps this is likely OK.			*/
/*								*/
/*	The second concern is the use of the Brook's and Corey	*/
/*	curves.  These curves are not useful for soils and peats*/
/*	with a gradual drainage when saturated.  		*/
/*	Ther van Genuchten curves are empirically more suitable */
/*	but would complicate the derivation.			*/
/*								*/
/*	The third concern is that in reality k(1) and psi(1)	*/
/*	and m change with depth.  Typically both porosity  	*/
/*	and fraction of large pores drops with depth.		*/
/*								*/
/*	In light of these comments the user of this algorithm 	*/
/*	may want to consider it to be a non-linear regression	*/
/*	of sorts and may want to also consider the application	*/
/*	of strictly empirical fits to get cap rise as a function*/
/*	of depth of the water table.				*/
/*								*/
/*								*/
/*  PROGRAMMER NOTES                                            */
/*                                                              */
/*                                                              */
/*--------------------------------------------------------------*/
#include "stdafx.h"
#include "BepsHydrScience.h"
#include <math.h>

double	compute_cap_rise(Soil_t soils2, double por)
{
/*--------------------------------------------------------------*/
/*  Local variable definition.                                  */
/*--------------------------------------------------------------*/
	double	air_entry,w, md, c;
	double Ksat_z;

	if ( soils2.K0_decay_m != 0 && soils2.water_table > 0.01)

		Ksat_z = soils2.saturated_Kv * exp( -1 * (soils2.water_table * soils2.K0_decay_m));

	else

		Ksat_z = soils2.saturated_Kv;



	air_entry = soils2.saturation_suction/((float)pow((soils2.unsaturated_storage/(soils2.water_table*por)),(double)-soils2.K0_decay_m));


	if(soils2.water_table>0.1)
	{



	w = Ksat_z * pow((1 + 1.5/(1 + 3* soils2.soil_b)) * (air_entry/(soils2.water_table - air_entry)), (2 + 3*soils2.soil_b));


	}
	else
	{
		w = 0.0;
//		w = Ksat_z * ( 1 + 1.5 / (soils2.soil_b - 1))*0.005;
	}

	return(w);

}

