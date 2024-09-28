
/*************************************************************************
					SNOW ACCUMMULATION AND MELT  21 June 2006
                            by Ajit Govind
This subroutine is used to calculate snowmelt in the spring season, which if not
represented will spoil the water table in Spring. The equations are adopted from
Tague and Band ,2004, Earth Interactions . ie "QUASI_ ENERGY BALANCE APPROACH"

  Assumptions: Age of Snow is Day# (100- doy)
  SAD sad is initialised as -30 on day 0 ie Dec31,2003
  -------
	input:
	b[6]: snow melt temp. coefficient (m/C/day)(=0.001)
	b[8]: snow aborptivity
	x[1]: SWE  (m)
    x[26]: snow density
    x[27]: snow depth (m)


	z[8]: shortwave radiation at forest floor (kj/m2/d)
	z[14]: daytime average temperature (C deg)
	// 2005-May-3
	z[38]	net radiation for sunlit leaves				(W/m2)
	z[39]	net radiation for shaded leaves				(W/m2)
	z[40]	net radiation for understory				(W/m2)
	z[41]	net radiation for ground					(W/m2)
	z[4]	: Tmax
	z[5]	: Tmin
	z[10]	: LAI
	z[18]	: daylength
	z[44]: Windspeed

	output:
	g[3]: total melt (m)
	g[8]: radiation melt (m)
	g[9]: temperature melt (m)
	g[13]: sublimation from the snow at ground (m)    µØÃæÑ©µÄÉý»ª


***************************************************************************/

#include "stdafx.h"
#include "BepsHydrScience.h"
#include "math.h"
#define row 1000  //density of water
#define KSNOW 50  //k_snow as in  Tague's paper

void melt(int jday,double sad,double snow_acc, double *b,double *g,double *x,double *z)
//    double b[], g[], x[], z[];
{
	double lh_fus=3.5E+5; //与融化相关的系数
	double lh_evp=2.5E+6; //与蒸发相关的系数
	double lh_sub=2.8E+6; //与升华相关的系数
	double sp_heat=4.18E+3;//水的比热容 J/(g·℃)
	double sigma1=5.67/100000000;
    double rho_snow_new, depth_snow_new;
    double rho_snow_old, depth_snow_old;
	double sad_max=10;
	double albedo; //(Laramie and Schaake,1972)
	double v_frac=z[42]+z[10]/10; //dirty way assuming max lai=7
	double cf;
	int age;
	double essm;
	double M_rad, M_v, M_t;

/*	b[8]: snow absorption */
	b[8]=0.1;//0.3/3.0;
//	b[8]=0.3;

/*
//	2004 stuff
if(jday>130 && jday <=180)  //160-->180 good  130->180
//if((jday>130 && jday <=180) ||(jday>290 && jday <=363)) //160-->180 good
//<<<<<<<<<<<<<<<<<<<OLD STUFF>>>>>>>>>>>>>>>>>>>>>
{//start Spring
	if(g[6]>0)
	{
	g[8]=0.0;
	g[9]=0.0;
	g[3]=(z[14]*g[6]*sp_heat)/lh_fus;//0.0;
	g[13]=0.0;
	}
	else
	{//start of 1st else
	if (z[14] > 0)
	{
	g[8] = z[8]*b[8]*0.05/lh_fus;	// radiation  melt
	g[9] = b[6] *0.1 *z[14];		//temperature melt
	g[3] =(g[8]+g[9]);// __min(x[1], (g[8]+g[9]);
	g[13] =0.0;
	}

	else
	{
	g[8]=0.0;
	g[9]=0.0;
	g[3]=0.0;
	g[13] = __min(x[1], ((z[8]-z[19])*b[8]/lh_sub));
	}
	}//end of 1st else
}//end Spring

if(jday>290 && jday <=364)
{

	g[13] = ((z[8]-z[19])*b[8]/lh_sub);
}
//<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>

*/

/*  //2005 stuff*/
if(jday>80/*95*/ && jday <=176)  //160-->180 good  130->180     这里计算了春季融雪情况
//if((jday>130 && jday <=180) ||(jday>290 && jday <=363)) //160-->180 good
//<<<<<<<<<<<<<<<<<<<OLD STUFF>>>>>>>>>>>>>>>>>>>>>
{//start Spring
	if(g[6]>0)
	{
	g[8]=0.0;
	g[9]=0.0;
	g[3]=(z[14]*g[6]*sp_heat*2.5)/lh_fus;//2 in 2004  , 1 in 2005  总融雪量=（白天平均气温*冠层向地面流失的降雨量*比热容*2.5）/与融化相关的系数
	g[13]=0.0;
	}
	else
	{//start of 1st else
	if (z[14] > 0)
	{
	g[8] = z[8]*b[8]*0.4/lh_fus;//辐射融雪量 = 日总入射太阳辐射量*雪的辐射吸收效率*0.4/与融化相关的系数
	g[9] = b[6] *0.4 *z[14];    //温度融雪量 = 白天平均气温*雪的温度吸收效率*0.4
	g[3] =(g[8]+g[9]);          //总融雪量   = 辐射融雪量+温度融雪量
	g[13] =0.0;                 //地面雪的升华
	}

	else
	{
	g[8]=0.0;
	g[9]=0.0;
	g[3]=0.0;
	g[13] = MIN(x[1], ((z[8]-z[19])*b[8]*1/lh_sub));//MIN(雪水当量，（日总入射太阳辐射量-日总吸收太阳辐射量）*雪的辐射吸收效率/与升华相关的系数）
	}
	}//end of 1st else


}//end Spring



if(jday>290 && jday <=364)
{

	g[13] = ((z[8]-z[19])*b[8]/lh_sub);
}






/*
//<<<<<<<<<<<<<<<<<<<<<<   TAGUE AND BAND 2004 APPROACH  >>>>>>>>>>>>>>>>>>>>>>>>>>>>
//tried by Ajit


{  //start of SPRING
sad=max(sad+z[14],sad_max);
age=jday-50;
cf=0.5; //cloud fraction --> assumed 50%
essm=(1-v_frac)*(0.53+(0.065*((pow(z[46],0.5)/100)*(1+(4*cf)+v_frac))));

//****************(A)****Radiation Melt*****************************
int term1,term2;

if(sad>=0.0)
{
	albedo=0.85*pow(0.82,(pow(age,0.46)));
	term1=(1-albedo)*z[45]*(1-exp(-KSNOW));//z[45] represents absorption of dir and diff components together
}
else
{
	albedo=0.85*pow(0.94,(pow(age,0.58)));
	term1=(1-albedo)*z[45]*(1-exp(-KSNOW));  //z[45] represents absorption of dir and diff components together

}

if ((z[14]>=0.0) && (sad >= 0.0) )
{ //term2 represents absorption of longwave component (Croley 1989)
	term2=41.868*(essm*sigma1*(pow((z[14]+273),4)-663));
}
if ((z[14]<0.0) && (sad <0.0) )
{ //term2 represents absorption of longwave component (Croley 1989)
	term2=41.868*((essm-1)*sigma1*(pow((z[14]+273),4)-663));
}

g[8]=(term1+term2)/(row*(lh_fus+lh_evp));

//*******************End of radiation melt stuff********************

//___________________TEMPERATURE MELT & Advection________________________________
M_t= b[6]*z[14]*(1-(0.8*v_frac));
M_v=(row*z[14]*g[6]*sp_heat)/lh_fus;
g[9]=M_t+M_v;
//___________________End of Temp.& Advection melt________________________________

g[3]=  (g[8]+g[9])*0.25;
} //end of SPRING*/


float snow;


  if(g[2]+g[7]>0) //if fresh snow falls
	{
      if(z[14]<=-15.0) //if fresh snow falls and temp is too low
		  rho_snow_new=50.0;
		else                //if fresh snow falls and temp is warm
		  rho_snow_new=50.0+1.75*pow(z[14]+15,1.5);
	      depth_snow_new=(g[2]+g[7])/rho_snow_new;
	}
	else {//if NO  fresh snow falls
	depth_snow_new=0;
	}


if(jday==1)
{depth_snow_old=0.60; //0.60 for 2005 and 0.49 for 2004
x[1]=0.072;
x[26]=(x[1]/depth_snow_old)*1000; //snow density
}
rho_snow_old  =x[26];
depth_snow_old=x[27];

if(	depth_snow_new>0 || depth_snow_old>0)


{


	if (depth_snow_new<=0 && depth_snow_old>0 && z[14]>6) //spring
	{x[26]=rho_snow_old+ ((0.95)*depth_snow_old)+ ((g[3]+g[13])*0.4); //spring ，water infiltration to the soil, including trough fall, snow melting and ground rain from canopy
	x[1]=x[1]-(((-0.00012*x[26]*x[26])+0.043*x[26])/200);} //spring

	else if (jday<90 || jday>300)// && depth_snow_old<=0)) //winter
	{
	    if (depth_snow_new>0  && jday <90)// && depth_snow_old<=0)) //winter
		x[26]=( (110/*rho_snow_new*0.40*/)+(rho_snow_old))/2;

		else if (depth_snow_new>0  && jday >300)// && depth_snow_old<=0)) //winter
		x[26]=( (35/*rho_snow_new*0.40*/)+(rho_snow_old))/2;

		else x[26]=rho_snow_old+ ((0.05*kstep/3600.0)*depth_snow_old);
		//x[26]=( (rho_snow_new*0.50)+(rho_snow_old*0.50));
	}




if(x[26]<=0) x[27]=0;
else   snow	=(x[1])/x[26]*1000.0;
x[27]=MAX(0, snow);

}
else if(	(depth_snow_new<=0) || (depth_snow_old<=0))
{
x[26]=0;
x[27]=0;
}


    return;
  }

