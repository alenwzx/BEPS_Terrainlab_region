/*************************************************************************
  Program:     inter.c
  --------
  Description:
  -----------
	Compute rain, snow to ground and to air.
  Details:
  -------
	INPUTS:
	b[4]	: snow & rain interception coefficient (=0.00025 m/lai/day)
	b[7]	: water absorption coefficient (dimensionless)
	b[8]	: snow absorption coefficient (dimensionless)
	z[3]	: precipitation (m)
	z[8]	: daily total short wave radiation (kJ/m2/d)
	z[10]	: lai
	z[14]	: daytime average temperature (C deg)

	OUTPUTS:
	g[1]	:ground rain -- MEM: throgoutfall (m)
	g[2]	:ground snow -- MEM: throgoutfall (m)
	g[4]	:evaporation of precipitation from canopy (m of h2o/ha/day)
	g[5]	:sublimation of precipitation from canopy (m of h2o/ha/day)
	g[6]	:ground rain from canopy
	g[7]	:ground snow from canopy
	g[11]	:intercepted precip. (m)
***************************************************************************
  CCRS (EMS/Applications Division)
  Written by:   J. Liu
  Last update:	December 2000
*****************************************************************************/
#include "stdafx.h"
#include "BepsHydrScience.h"

void inter(double *b,double *g,double *x,double *z)
//    double  b[], g[], x[], z[];
{
    double lh_evp=2.5E+6;
    double lh_sub=2.8E+6;
    double Evap;
    /* fresh snow */
    b[8] = 0.1; //orig-->0.05

    /* intercepted precip */
    g[11] = MIN(z[3], z[10]* b[4]);             //截留降水量 = 降水量和最大截留量中的最小值
//	g[11] = MIN(z[3], z[3]*z[10]* b[4]);		// MEM

    /* rain vs snow */

    if (/*z[14]*/ z[5]  > 0.0 ) //如果日最低气温大于0摄氏度， daytime average temperature (C deg) > 0 therefor assume rain
    {
        g[1] = z[3] - g[11]; //throughfall rain :地面降雨量=降水量-树冠截留降水量
        g[2] = 0.0;          //地面雪深为0
    }
    else
    {
        // 如果日最低气温低于0摄氏度，assume snow
        g[1]=0.0;               //地面降雨量为0
        g[2] = z[3] - g[11];	//throughfall snow：地面降雪量=降水量-树冠截留降水量
    }

    /* water loss from canopy */ /*从冠层蒸发的降水量*/
    if (z[14]  > 0.0 ) // assume rain 白天气温大于0度，降水形式为雨
    {
        Evap= (((penmon(z[14],z[16],z[38],g[70],1000)*z[32])+
                (penmon(z[14],z[16],z[39],g[70],1000)*z[33])))*z[18];
        g[4] =  MIN(g[11], Evap);
        g[4]=MAX(0,g[4]); //EPHYSE
        //g[4]  //
//g[4]= MIN(g[11], z[8]*b[7]/lh_evp);
        g[5] =0.0;
    }
    else
    {
        // assume snow
        g[4] =0.0;
        g[5] = MIN(g[11], z[8]*b[8]/lh_sub);
        g[5]=MAX(0,g[5]); //EPHYSE
    }

    /* canopy water to ground */ /*从冠层流向地面的降水量*/
    if (z[14]  > 0.0 )
    {
        g[6] = MAX(0.0, g[11]-g[4]);
        g[7] =0.0;
    }
    else
    {
        g[6]=0.0;
        g[7] = MAX(0.0, g[11]-g[5]);
    }

    return;
}


