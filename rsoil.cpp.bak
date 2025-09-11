/*************************************************************************
  Program:     rsoil.c
  --------
  Description:
  -----------
	Output soil conductance/resistance to water, based on BIOME-BGC.
***************************************************************************
  CCRS (EMS/Applications Division)
  Written by:   J. Liu
  Last update:	May 1998
*****************************************************************************/
#include "stdafx.h"
#include "BepsHydrScience.h"

void rsoil(double *b,double *g,double *x,double *z)
//    double b[], g[], x[], z[];m
{
//	double rsw;		/* relative soil moisture */

// juw added  2005-Arp-22///////////////////////////////////
	double vsm_us;
    double ss,sf,sw,w_table;//porosity, field capacity, wilting point  土壤质地的参数
   int kkk;


	sw = x[20]; // MM assign the wilting point
	sf = x[21]; // MM assign the field capacity
	ss = x[22]; // MM assign the porosity

w_table=x[19];
if(w_table>0.05){
vsm_us=x[2]/w_table;  // conver unsaturated_storage to volumetric soil moisture content;

if(vsm_us<=sw) g[41]=0.0001;
else if (vsm_us>sw && vsm_us<=ss) g[41]=(vsm_us-sw)/(ss-sw)*(x[23]-0.0001)+0.0001;
//else if (vsm_us>sf )  g[41]=0.005;
}
else{
g[41]=x[23];   //soil conductance/resistance
}
/////////////////////////////////////////////////////////////////
/* removed by juw  2005-Apr-22
    rsw=100*x[2]/z[22];

    g[41]=0.002; 		// default value //

	if(rsw<20.0) 				g[41]=0.0000001;
    if(rsw>20.0 && rsw<=30.0) 	g[41]=0.00001;
    if(rsw>30.0 && rsw<=40.0) 	g[41]=0.00006;
    if(rsw>40.0 && rsw<=50.0) 	g[41]=0.000125;
    if(rsw>50.0 && rsw<=60.0)	g[41]=0.00025;
    if(rsw>60.0 && rsw<=70.0) 	g[41]=0.0005;
    if(rsw>70.0 && rsw<=80.0)	g[41]=0.001;
    if(rsw>80.0) 				g[41]=0.002;
								g[41]=MIN(0.002,g[41]);
*/

    return;



}
