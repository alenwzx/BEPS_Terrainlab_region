/*************************************************************************
  Program:     zcomp.c
  --------
 	 Description:
	 ------------
	 Calculate z variables

	 Details:
	 -------

	Z 	Description
	-------------------------------------------------------------

   	2	day of year
 	3	precipitation 							(m)
	4 	max. Air temperature 					(deg c)
 	5  	min. Air temperature					(deg c)
   	6  	relative humidity						(%)
   	7  	soil temperature, ave 24 hr temp   		(deg c)
   	8  	daily total incoming solar radiation	(kj/m2/d)
   	9  	average incoming solar radiation		(W/m2)
	10	LAI
    14 	daylight average air temperature		(deg c)
    15 	average night min. temperature			(deg c)
    16 	vapor pressure deficit					(mb)
    17 	absolute humidity deficit				(mic. gm/m3)
   	18 	running periods (day length for daily model)    (sec)
   	19 	daily total absorbed radiation    		(kj/m2/d)
	20	daily averaged absorbed radiation		(W/m2)

	22	available water capacity				(m)
	23	land cover type

	26	leaf nitrogen concentration  fraction

	30	Cos(Theta_noon)
	31	Cos(Theta_mean)
	32	sunlit LAI
	33	shaded LAI
	34	daily mean radiation over sunlit leaves	(W/m2)
	35	daily mean radiation over shaded leaves	(W/m2)
	36	radiation over sunlit leaves at noon	(W/m2)
	37	radiation over shaded leaves at noon	(W/m2)
	38	net radiation for sunlit leaves			(W/m2)
	39	net radiation for shaded leaves			(W/m2)
	40	net radiation for understory			(W/m2)
	41	net radiation for ground				(W/m2)
	42  understory LAI
	43	Ground heat Flux						(W/m2)  //added by Ajit
	44  Windspeed                               (m/sec) //adeded by Ajit
	45  Snowdepth                               (m/sec) //adeded by Ajit
	46  watertable                              (m/sec) //adeded by Ajit
***************************************************************************
  CCRS (EMS/Applications Division)
  Written by:   J. Liu
  Last update:	May 2000
*****************************************************************************/
#include "stdafx.h"
#include "BepsHydrScience.h"
#include <math.h>

void zcomp(int jday,int pix,double lat_p,unsigned char lc_p,double soil_depth,
           double lai_p,double *b,double *x,double *z,climatedata *sdat,
           BH_SubParams2_t* pBH_SubParams2)
{
    double   xtmax, xtmin, xrad,frad, xppt, tave, dewpt;
    double	xwind;                              // x snow depth, x water table
    double   esd, es, ampl, day, xd;
    int kkk;
    double gfn;				                    // gap function at noon
    double omega;			                    // clumping index
    double theta_m;			                    // solar zenith angle at noon
    double alfa;
    double ssun;			                    // radiation for sunlit leaves
    double sshade;			                    // radiation for shaded leaves

    /* for shortwave radiation */
    double lai_u;			                    // understory lai
    double n_ssun;			                    // net shortwave radiation for sunlit leaves
    double n_sshade;		                    // net shortwave radiation for sunshade leaves
    double n_sunder;		                    // net shortwave radiation for understory
    double n_sground;		                    // net shortwave radiation for ground

    /* for longwave radiation */
    double m_lnet_o;		                    // mean longwave radiation for overstory
    double m_lnet_u;		                    // mean longwave radiation for understory
    double lnet_g;			                    // net longwave radiation for ground

    double vc_a=6.108, vc_b=17.269, vc_c=237.3; //constants used for vapor pressure calculation
    double groundheat;                          // Ajit: to be modified later Ground Heat Flux +/-

    xtmax = sdat[pix].tmax;
    xtmin = sdat[pix].tmin;

    xwind = sdat[pix].wind;//ajit
    dewpt = sdat[pix].dewp;				        //note: In this program, it is dew-point
    xrad  = sdat[pix].srad;
    frad  = sdat[pix].frad;
    xppt  = sdat[pix].precip;			        // MEM: in mm

    z[2]  = jday;
    z[3] = xppt / 1000.0;                       // convert mm to meter
    z[4] = xtmax;
    z[5] = xtmin;

    tave = (z[4]+z[5])/2.0;

    if (jday <= 1)
        z[1] = b[22];

    z[1] = MAX((z[1]+tave), b[22]);
    z[7] = tave;                                // average temperatures, soil, air
    z[10] =lai_p;                               // leaf area index one sides
    z[14] = 0.212 * (z[4] - tave) + tave;       // daylight  mean temp. z[14]
    z[15] = (z[14] + z[5])/2.0;                 // nighttime mean temp. z[15]

    es = vc_a*exp(vc_b/(vc_c/dewpt+1));
    esd = vc_a * exp((vc_b*z[14])/(vc_c + z[14]));

    z[46]=es;                                   // for snow melt , just copied to another vriable for another use
    z[16] = MAX((esd-es),0.0);                  // vapour pressure defivit
    z[6]= 100*es/esd;                           // Relative humidity

    /* compute daylength in seconds */
    xd  =  (double) jday - 79.0;
    if (xd < 0.0)
        xd = 286.0 + (double) jday;
    ampl = exp(7.42+0.045*lat_p)/3600.0;
    day  = ampl * (sin(xd*0.01721)) + 12.0;
    z[18]  =  day * 3600.0 * 0.85;

    z[9] = xrad+frad;                           // average incoming solar radiation in w·m-2
    z[8]  = z[9]*z[18]/1000;                    // total incoming solar radiation in kj·m-2·s-1

    /* FPAR */
    theta_m=(lat_p-23.5*sin((jday-81)*2*PI/365))*PI/180;

    if (fabs(PI/2-theta_m)<0.01)
        alfa=0.05;
    else
        alfa=(cos(theta_m)-(PI/2-theta_m)*sin(theta_m))/((PI/2-theta_m)*(1-sin(theta_m)));

    omega=b[51];

    if (fabs(PI/2-theta_m)<0.01)
        gfn = 0.1;
    else
        gfn = exp(-0.4*omega*z[10]/cos(theta_m));

    z[19] = MAX(0.0,(0.95-0.94*alfa*gfn));
    z[19] = z[8]*z[19];

    /*  daily averaged absorbed radiation in W/m2 */
    z[20]=1000*z[19]/z[18];

    /* leaf nitrogen */
    z[21] = b[26];

    /* awc */
    //z[22]=awc_p;
    // AWC equals (field capacity- wilting point)*soil depth.	// weimin     AWC����(����ˮ��-ή���)*�������
    z[22] = (x[21]-x[20])*soil_depth ;		// MM/juw  2005-May-6
    x[35]=soil_depth; //soil depth Ajit 27 oct
    /* land cover */
    z[23]=(double)lc_p;

    /* cos(Thita_m)  */

    /* cos(Thita_m)  */
    z[30]=cos(theta_m);

    /* cos(Thita_avg) */
    z[31]=cos(PI/8+3*theta_m/4);

    /* average sunlit leaves */
    if (z[31]<0.01)
        z[32]=0;
    else
        z[32]=2*z[31]*(1-exp(-0.5*omega*lai_p/z[31]));

    /* average shaded leaves */
    z[33]=lai_p-z[32];

    /* daily averaged radiation for sunlit and shaded leaves */
    rad_ssl(xrad,frad,z[31],z[10],omega,&ssun,&sshade);  //juw
    z[34]=ssun;
    z[35]=sshade;

    /*  radiation for sunlit and shaded leaves at noon*/
    rad_ssl(xrad*PI/2,frad*PI/2,z[30],z[10],omega,&ssun,&sshade);
    z[36]=ssun;
    z[37]=sshade;

    switch(lc_p)
    {
    case 1:
    case 3://NF
        lai_u=1.175*exp(-0.991*z[10]);
        break;
    case 2:
    case 4://BF
        lai_u=1.5;
        break;

    case 5://MF
        lai_u=0.5*(1.5+1.175*exp(-0.991*z[10]));
        break;
    default:
        lai_u=0.0;

    }

    // net shortwave radiation calculation
    net_shortwave(xrad,frad, z[31],z[10],omega,&ssun,&sshade,lai_u,&n_ssun,&n_sshade,&n_sunder,&n_sground);

    // net longwave radiation calculation
    net_longwave(lai_p,lai_u,omega,es,(z[14]+275.0),&m_lnet_o,&m_lnet_u,&lnet_g);

    z[38]=n_ssun+m_lnet_o;                                  // net radiation for sunlit leaves			(W/m2)
    z[39]=n_sshade+m_lnet_o;                                // net radiation for shaded leaves			(W/m2)
    z[40]=n_sunder + m_lnet_u;                              // net radiation for understory			    (W/m2)
    z[41]=n_sground + lnet_g;                               // net radiation for ground				    (W/m2)
    z[45]=n_sground;                                        // to use in snowmelt. It needs SW and Diffuse SW to ground
    if(z[41]<-100 ||z[41]>1000)
    {
        kkk=0;
    }
    z[42]=lai_u;
    z[43]=groundheat=0;                                     // for surface energy balance calculation, soil temperature simulator, presently set to zero, we can modify it later with
    z[44]=xwind;
}

int rad_ssl(double sg_r,double sg_f,double cos_theta,double lai_p,double omega,double *ssun,double *sshade)
{
    double theta_avg; 		                                // Mean cos(thita)
    double sdir;		                                    // direct radiation W m-2
    double sdif_over;		                                // diffusive radiation over plant canopy
    double sdif_under;		                                // diffusive radiation under plant canopy
    double c;			                                    // radiation from multiple scattering

    /************* calcuate sdir and sdif_over ********************/
    sdif_over=sg_f;
    sdir     =sg_r;

    /************* calculate ssun and sshade ***********************/

    /* radiation from multiple scattering */
    c=0.07*omega*sdir*(1.1-0.1*lai_p)*exp(-cos_theta);

    /* sdif_under */
    theta_avg=0.537+0.025*lai_p;
    sdif_under=sdif_over*exp(-0.5*omega*lai_p/theta_avg);

    /* radiation for shaded leaves */
    if ((lai_p<0.01) && (sdif_over-sdif_under)<0)
        *sshade=0;
    else
        *sshade=(sdif_over-sdif_under)/lai_p+c;

    /* radiation for sunlit leaves */
    if (cos_theta <0.01)
        *ssun=0;
    else
        *ssun=0.5*sdir/cos_theta +*sshade;

    return 1;
}

int net_shortwave(double sg_r,double sg_f,double cos_theta,double lai_p,double omega,double *ssun,double *sshade,double lai_u,double *n_ssun,double *n_sshade,double *n_sunder,double *n_sground)
{
    double theta_avg; 		                                // Mean cos(theta)
    double sdir;		                                    // direct radiation W m-2
    double sdif_over;		                                // diffusive radiation over plant canopy
    double sdif_under;		                                // diffusive radiation under plant canopy
    double c;			                                    // radiation from multiple scattering
    double c_for_net;
    double alpha_l=0.25;
    double alpha_g=0.2;
    double theta_avg_under;                                 // Mean cos(theta) for understory

    /************* calcuate sdir and sdif_over ********************/
    sdif_over=sg_f;
    sdir     =sg_r;

    /************* calculate ssun and sshade ***********************/

    /* radiation from multiple scattering */
    c=0.07*omega*sdir*(1.1-0.1*lai_p)*exp(-cos_theta);

    /* sdif_under */
    theta_avg=0.537+0.025*lai_p;
    sdif_under=sdif_over*exp(-0.5*omega*lai_p/theta_avg);

    /* radiation for shaded leaves */
    if ((lai_p<0.01) && (sdif_over-sdif_under)<0)
        *sshade=0.0;
    else
        *sshade=(sdif_over-sdif_under)/lai_p+c;

    /* radiation for sunlit leaves */
    if (cos_theta <0.01)
        *ssun=0.0;
    else
        *ssun=0.5*sdir/cos_theta + *sshade;

    /* net short radiation for shaded leaves */
    c_for_net=alpha_l*omega*sdir*(1.1-0.1*lai_p)*exp(-cos_theta);;
    if ((lai_p<0.01) && (sdif_over-sdif_under)<0.0)
        *n_sshade=0;
    else
        *n_sshade=(sdif_over-sdif_under)/lai_p+c_for_net;

    /* net short radiation for sunlit leaves */
    *n_ssun=(1-alpha_l)**ssun + *n_sshade;

    /* net short radiation for understory */
    *n_sunder=(1-alpha_l)*(sdir*exp(-0.5*omega*lai_p/cos_theta)+sdif_under);

    /* net short radiation for ground */
    theta_avg_under=theta_avg=0.537+0.025*lai_u;
    *n_sground=(1-alpha_g)*(sdir*exp(-0.5*omega*(lai_p+lai_u)/cos_theta)+sdif_under*exp(-0.5*omega*lai_u/theta_avg_under));

    return 1;
}

int net_longwave(double lai_o,double lai_u,double omega,double es,double ta,double *m_lnet_o,double *m_lnet_u,double *lnet_g)

{
    double sigma;			                                // Stefan-Boltzmann constant =5.67*10^(-8) W m^-2 K^-4
    double epsilon_a, epsilon_o,epsilon_u, epsilon_g;
    double to,tu,tg;		                                // temperature, in K
    double l_a,l_o,l_u,l_g;				                    // longwave radiation
    double r_ctheta_o, r_ctheta_u;                          // representive zenith angle
    double exponent_o, exponent_u;
    double lnet_o, lnet_u;

    sigma=5.67/100000000;

    epsilon_o=0.98;
    epsilon_u=0.98;
    epsilon_g=0.95;
    epsilon_a=1.24*pow((es/ta), (1.0/7.0));             // es in mbar, ta in K

    to=ta;	                                                // in K
    tu=ta;
    tg=ta;

    // longwave radiation
    l_a=epsilon_a*sigma*pow(ta,4.0);
    l_o=epsilon_o*sigma*pow(to,4.0);
    l_u=epsilon_u*sigma*pow(tu,4.0);
    l_g=epsilon_o*sigma*pow(tg,4.0);

    // represntive angle
    r_ctheta_o=0.573+0.025*lai_o;
    r_ctheta_u=0.573+0.025*lai_u;

    exponent_o=exp(-0.5*lai_o*omega/r_ctheta_o);
    exponent_u=exp(-0.5*lai_u*omega/r_ctheta_u);

    //net longwave radiation
    lnet_o=(l_a + l_u* (1-exponent_u) + l_g* exponent_u - 2*l_o)*(1-exponent_o);
    lnet_u=(l_a*exponent_o + l_o* (1-exponent_o) + l_g - 2*l_u)*(1-exponent_u);
    *lnet_g=(l_a*exponent_o + l_o* (1-exponent_o))*exponent_u + l_u*(1-exponent_u) - l_g ;

    if (lai_o>0.01)
        *m_lnet_o =lnet_o/lai_o;
    else
        *m_lnet_o=0.0;
    if (lai_u !=0)
        *m_lnet_u = lnet_u/lai_u;
    else
        *m_lnet_u=0.0;


    return 1;
}
