/*************************************************************************
  Program:     doflux.c
  --------
  Description:
  -----------
	Calculate and update the fluxes in carbon and water cycles.计算并更新碳循环和水循环中的通量
  Details:
  -------
	input:
	z[14]: daylight average air temperature			    (deg c)
	z[16]: vapor pressure deficit						(mb)
	z[18]: running periods (daylength for daily model)	(sec)
	z[22]: available water capacity					(m)
	z[23]: land cover type (index)
	z[32]: sunlit LAI
	z[33]: shaded LAI
	z[38]: net radiation for sunlit leaves				(W/m2)
	z[39]: net radiation for shaded leaves				(W/m2)
	z[40]: net radiation for understory				    (W/m2)
	z[41]: net radiation for ground					    (W/m2)
	z[42]: understory lai
	g[2]:  ground snow -- MEM: throgoutfall             (m)
	g[3]:  total melt                                   (m)
	g[4]:  evaporation of precipitation from canopy     (m of h2o/ha/day)
	g[5]:  sublimation of precipitation from canopy     (m of h2o/ha/day)
	g[7]:  ground snow from canopy
	g[13]: sublimation from the snow at ground          (m)
	g[20]: final stomatal conductance for sunlit leaves
	g[21]: final stomatal conductance for shaded leaves
	g[26]: NPP
	g[40]: total air conductance
	g[41]: ?? conductance
	output:

    x[1]:  SWE (in m)   //snow pack
    x[2]:  soil water
    x[3]:  out flow
    x[4]:  transpiration
	x[5]:  evaporation
	x[6]:  NPP
	x[7]:  Rm
	x[14]: GPP
	x[15]: NEP
	x[16]: Ra
    x[17]: Rh
	x[18]: understory Transpiration
	x[26]: snow density
	x[27]: snow depth in m
	x[26]  water infiltration to the soil, including trough fall, snow melting and ground rain from canopy

	g[12]: Penman - Monteith estimate of evaporation from soil
	g[16]: Penman - Monteith estimate of transpiration, overstory
	g[17]: canopy transpiration
	g[19]: Penman - Monteith estimate of evaporation from understory
	g[33]: outflow
	g[40]: total air conductance (see ra.cpp)
	b[34]: field capacity
	b[35]: field capacity
	b[36]: saturation
***************************************************************************
  CCRS (EMS/Applications Division)
  Written by:   J. Liu
  Last update:	December 2000
*****************************************************************************/

#include "stdafx.h"
#include "BepsHydrScience.h"
#include "math.h"
void doflux(int jday,float T_m,double sad, double soilt,double snow_acc,double snow_today,double *b,double *g,double *x,double *z,unsigned char lc_p,
            BH_SubParams2_t* pBH_SubParams2)
{

    double soilw_in=0;
    double soilw_out=0;
    int kkk;
    double dnep;



    b[34]=x[20];	// Field capacity
    b[35]=x[21];	// Field capacity
    b[36]=x[22];   	// Saturation

    /*  canopy interception */
    inter(b, g, x, z);
    snow_today=(g[2]+g[7]);

    /*  snowmelt routine  */
    melt (jday,sad,snow_acc, b, g, x, z);

    /*  aerodynamic resistance*/
    ra(b, g, x, z);

    /*canopy stomata resistance*/
    rs(jday, b, g, x, z, pBH_SubParams2);

    /*soil resistance*/
    rsoil(b, g, x, z);


    /*估算光合作用和植物呼吸作用部分GPP\NPP等等*/
    carbon(jday,T_m,b, g, x, z, pBH_SubParams2);
    //soilresp(b, g, x, z); //shifted  by Ajit  to Terrainlab   //土壤呼吸计算转移到了Terrainlab


    /* Penman - Monteith estimate of transpiration, overstory */
    double gsun_unsat=g[20];
    double gsun_sat=g[60];
    double gshade_unsat=g[21];
    double gshade_sat=g[61];
    b[99]	= z[18];
//********************partitioning overstorey transpiration***************

    double bz;
    // daylength transfer
    if(x[19]>0)
        bz		=MIN(1.0,pow(b[37],x[19]*100.0)); //100 to convert to cm与WTD相关
    else
        bz=1.0;
    bz	    =MAX(0,bz);

    double bz_u;
    // daylength transfer
    if(x[19]>0)
        bz_u		=MIN(1.0,pow((b[37]/1.25),x[19]*100.0)); //100 to convert to cm
    else
        bz_u=1.0;
    bz_u	    =MAX(0,bz_u);

    /********************partitioning overstorey transpiration***************/
    //整个冠层的蒸腾作用，分阴阳叶片，好像并没有分上下层
    g[16]=	       (penmon(z[14],z[16],z[38],g[70],gsun_unsat  )*z[32]*(1-bz))+ //earlier g[70] was g[40]
                   (penmon(z[14],z[16],z[38],g[70],gsun_sat    )*z[32]*bz);
    g[16]= g[16] + (penmon(z[14],z[16],z[39],g[70],gshade_unsat)*z[33]*(1-bz))+
                    (penmon(z[14],z[16],z[39],g[70],gshade_sat )*z[33]*bz);

    //Rearrange unsat and saturated parts to pass to model.cpp
    g[62]= penmon(z[14],z[16],z[38],g[70],gsun_unsat    )*z[32]*(1-bz);
    g[63]= penmon(z[14],z[16],z[39],g[70],gshade_unsat  )*z[33]*(1-bz);
    g[64]= penmon(z[14],z[16],z[38],g[70],gsun_sat      )*z[32]*bz;
    g[65]= penmon(z[14],z[16],z[39],g[70],gshade_sat    )*z[33]*bz;
    g[66]=(g[62]+g[63])*z[18];                                      //unsaturated part
    g[67]=(g[64]+g[65])*z[18];                                      //saturated part


    /* canopy transpiration  */
    g[17] =g[16]* z[18];


//_____________________________________________________________________________________________________________
    /* Penman - Monteith estimate of evaporation from soil/moss surface(FOREST FLOOR) */
    //土壤/苔藓表面蒸发

    float moss_frac;
    float soil_frac;

    double M= 18.8-(12.5*x[19]);//17; //M as a fn of Frolking 2002
    double Se; // Entekhabi and Eagleson, 1989
    double hb; //Bubbling pressure head(冒泡压力水头), after Steiglitz,1997 J of Climate
    if (x[30]==10)
        hb=0;
    else if (x[30]==20)
        hb=0;
    else if (x[30]==30)
        hb=0.147;
    else if (x[30]==40)
        hb=0.208;
    else if (x[30]==50)
        hb=0;
    else if (x[30]==60)
        hb=0;
    else if (x[30]==70)
        hb=0;
    else if (x[30]==80)
        hb=0;
    else if (x[30]==90)
        hb=0;
    else if (x[30]==100)
        hb=0;
    else if (x[30]==110)
        hb=0;
    else if (x[30]==120)
        hb=0.073;

    double termA, termB,termC;
    double gg_moss1=(-0.195+(0.134*M)-(0.0256*pow(M,2))+(0.00288*pow(M,3))-(0.0000984*pow(M,4))+(0.00000168*pow(M,5)))*1.6;
    double gg_moss2/*in m/s */= gg_moss1/(8.3143 * (273+z[14]));//不懂，为什么要除以RT？

    switch(lc_p)
    {
    case 1:
    case 3:
        moss_frac=0.85;
        soil_frac=(1-moss_frac);

        if((z[14]<0) || (z[23]==31))
            g[12]=0.0;
        else
            g[12]= z[18]*((penmon(z[14],z[16],z[41],g[72],g[41]   )*soil_frac)+
                          (penmon(z[14],z[16],z[41],g[72],gg_moss2)*moss_frac)); //soil and Moss ET from BS floor

        break;
    case 2:
    case 4:
        moss_frac=0.75;
        soil_frac=(1-moss_frac);

        if((z[14]<0) || (z[23]==31))
            g[12]=0.0;
        else
            g[12]= z[18]*((penmon(z[14],z[16],z[41],g[72],g[41])*soil_frac)+

                          (penmon(z[14],z[16],z[41],g[72],gg_moss2)*moss_frac)); //soil and Moss ET from BS floor

        break;
    case 5:
        moss_frac=0.80;
        soil_frac=(1-moss_frac);

        if((z[14]<0) || (z[23]==31))
            g[12]=0.0;
        else
            g[12]= z[18]*((penmon(z[14],z[16],z[41],g[72],g[41])*soil_frac)+

                          (penmon(z[14],z[16],z[41],g[72],gg_moss2)*moss_frac)); //soil and Moss ET from BS floor

        break;
    case 6:
    case 7:
    case 8:
        moss_frac=0.50;
        soil_frac=(1-moss_frac);

        if((z[14]<0) || (z[23]==31))
            g[12]=0.0;
        else
            g[12]= z[18]*((penmon(z[14],z[16],z[41],g[72],g[41])*soil_frac)+

                          (penmon(z[14],z[16],z[41],g[72],gg_moss2)*moss_frac)); //soil and Moss ET from BS floor

        break;
    default:
            g[12]= z[18]*(penmon(z[14],z[16],z[41],g[72],g[41])); //original    土壤/苔藓的蒸发计算
    }

//___________________________________________End of Forest Floor ET___________________________________________



    /* Urban area */
    if (z[23]==29)
        g[12]=0.25*g[12];  //earlier 0.8*g[12]; g[12]：Penman - Monteith estimate of evaporation from soil/moss

    g[19]=g[19]; // Ajit 9dec2006 //understorey canopy conductance //凋落物的蒸发

    /* Penman - Monteith estimate of evaporation from understory */
    if( ((z[14]<0) || (z[23]==31)) || z[42]==0)
        g[37]=0.0;
    else
        g[37]= z[18]*((penmon(z[14],z[16],z[40],g[71],g[19])*(1-bz_u))+
                      (penmon(z[14],z[16],z[40],g[71],g[77])*(bz_u))); // big leaf using canopy condu directly
    /* ********** Water update *****************/

    /*  snow pack = snow pack + ground snow + snow from canopy - melt - sublimation */
    x[1] = x[1] + g[7] ;//- g[3]- g[13]; //snow equivalent water


    if (x[1]==0)
        x[26]==0;
    x[1]=MAX(0,x[1]);
    /* ground rain + ground snow + ground rain from canopy + ground snow from canopy */
    x[28]=g[1]+g[2]+g[6]+g[7]; // g[4] is canopy evaoration  这里计算waterin,雪的那些参数可能对结果有影响,删除了融雪量
    /* ground rain + total melt + ground rain from canopy + ground snow from canopy */
    g[50]= g[1]+ g[3] + g[6] +g[7];
    g[51]= x[1];
    /* g[33] - outflow = available soil water - field capacity*/
    g[33]=MAX(0.0, (x[2]-b[35]));
    /* x[3] - out flow = old out flow + new out flow*/
    x[3] = x[3] + g[33];

    //trans
    x[4] = 0;
    /* trans = old trans + canopy trans + understory trans */
    x[4] = x[4] + g[17] +g[37];

    //evapo
    x[5]=0;
    /*  evapo = evapo + evap_canopy + sublimatio_canopy + evap_soil + sublimation_snow */
    x[5] =x[5] +g[4]+ g[5];//+g[12]+g[13];


    /********* carbon update **********/
    x[6] =x[6]+g[26];// NPP accumulated
    x[14]=x[14]+g[24];//GPP updates
    x[16]=x[14]-x[6]; //ra
    x[17]=0;//Rh: x[17]=x[6]-x[15]; replace this with actual Rh later from TerrainLab--ephyse
}





