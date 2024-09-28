/*--------------------------------------------------------------*/
/* 																*/
/*		compute_unsat_zone_drainage								*/
/*																*/
/*	NAME														*/
/*	compute_unsat_zone_drainage - estimates vertical 			*/
/*		drainage from the unsat to sat zone.					*/
/*																*/
/*																*/
/*	SYNOPSIS													*/
/*	compute_unsat_zone_drainage(soil, double, double )					*/
/*																*/
/*	returns:													*/
/*	unsat_zone_drainage - (m water) drainage from unsat to		*/
/*			sat zone.											*/
/*

									*/
/*	OPTIONS														*/
/*	soil structure at pixel i, j
/*	field_capacity			---- m H2O							*/
/*	double	potential_drainage - (m water) difference			*/
/*		between current unsat_zone_storage and current			*/
/*		field capacity.											*/
/*																*/
/*	DESCRIPTION													*/
/*																*/
/*	This routine is designed to estimate unsaturated zone		*/
/*	drainage from soils with "TOPMODEL" properties under		*/
/*	the assumptions that:					*/
/*								*/
/*	i) a field capacity for the unsat zone is known.	*/
/*	ii) the drainage will be the minimum of drainage to	field capacity or the amount resulting from	the current Ksat at the water table.		*/
/*								*/
/*	iii) the change in sat_deficit due to drainage does not significantly affect field capacity.	*/
/*								*/
/*	PROGRAMMER NOTES					*/
/* Input variable por added. juw  2005-Apr-22		*/
/*--------------------------------------------------------------*/
#include "stdafx.h"
#include "BepsHydrScience.h"
#include <math.h>

double	compute_unsat_zone_drainage(unsigned char textureindext, Soil_t soils2, double threthod,double fieldcapacity,double por )
{

/*--------------------------------------------------------------*/
/*	Local variable definition.									*/
/*--------------------------------------------------------------*/
	double	unsat_zone_drainage, temp;
	double   b, c, vg, p, q, r;
	double Ksat_z;//depth, porosity;
	int counter=1;
	double kkk,wp,wt,control;
	double a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,f=1.0,A,B,pc;
	double deltawt;


	if ( soils2.water_table>0.01)
	{


	Ksat_z = soils2.saturated_Kv ;


	}
 	else

		Ksat_z = soils2.saturated_Kv;


	if ( soils2.water_table>0.01){


		b = soils2.soil_b *2 +3;
		kkk=soils2.unsaturated_storage/soils2.water_table ;
		wt=soils2.water_table;

		if ((textureindext == 2)||(textureindext == 3)||(textureindext == 11)){

			p = (1 - (pow((soils2.unsaturated_storage/(wt*por)), (1/0.42))));
			q = pow(p, 0.5);
			r = pow((1 - q), 2);
			vg = (pow((soils2.unsaturated_storage/(wt*por)), 0.42)*r);

		} else {

			c = pow((soils2.unsaturated_storage/(wt*por)),b);

		}


		if(c>=0.1)	{

			unsat_zone_drainage = Ksat_z*0.1;

		} else {


			if ((textureindext == 2)||(textureindext == 3)||(textureindext == 11)){

			unsat_zone_drainage = Ksat_z *vg;

			} else {

			unsat_zone_drainage = Ksat_z *c;

		}

		}
		unsat_zone_drainage=MIN(control*0.75,unsat_zone_drainage);
	unsat_zone_drainage=MAX(0.0,unsat_zone_drainage);
	}
	else

		unsat_zone_drainage=0;





    	b = soils2.soil_b *2 +3;
		a0=soils2.unsaturated_storage/soils2.water_table ;
		a1=soils2.water_table;

		A=Ksat_z*  pow(kkk/por,b);
	    B=Ksat_z*pow(kkk/por,b-1);
	    wt=soils2.water_table;
        a2=wt*kkk*(por-kkk)-A*(1-f*b)*por;
        a3=(1-b*f)*A-wt*(por-kkk)-f*B*b;
	    a4=b*f*B/por;

	    a6=-a2/a3;
	    a5=(-a3-sqrt(a3*a3-4*a2*a4))/(2*a4);
	    a7=(-a3+sqrt(a3*a3-4*a2*a4))/(2*a4);


pc=1*Ksat_z*  pow(kkk/por,b) +
	  b*f*Ksat_z*  pow(kkk/por,b-1)*(a5-kkk)/por;
unsat_zone_drainage=pc;

	return(unsat_zone_drainage);

} /*compute_unsat_zone_drainage*/
