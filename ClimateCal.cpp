/*----------------------------------------------------------------------------------------------
 This code is used to produce climatic inputs for BEPS according to records of a basestation.
 Input items for are daily Maximum, Minimum, Mean,Dewpoint Temperatures,
 Precipitation, total radiation, wind speed. Output items for each pixel are Maximum, Minimum, Mean,
 Dewpoint Temperatures,Precipitation, diffused and direect radiance, wind speed.
 For each day, the interpolated values of each climatic variable are saved in one file. So,there
 are seven files every day.
 Assume files such as base station climate, DEM,slope magnitude (in degree)
 and slope azimuth (in degree) files are already coreated elsewhere.*/
/*
/*            Assumptions:
/*
/*				In a relatively small area (<100 km by 100km), solar elevation, solar
/*				zenith angle and solar azmuth are constant.
/*
/*				The only attributes of topography which modify the normal radiation are slope
/*				and slope azimuth.
/*				Given Latitude, Logitude, Reference Meridian, Julian Day and Radiation Above
/*				Canopy (RAC), average daily radiation at a pixel equals 0.707*Radiation_at_noon.
/*				So, we need to calculate the RAC at noon first.
/*
/*
/*	    The format of input climate file of the base station file is:
/*
/*		Latitude(decimal degree), Longitude(decimal degree), Elevation (meter), ReferenceLong.
/*
/*	    Julian_Day	Tmin, Tmax, tmean, Dewpoint_T, Precipitation(mm), Radiation(kj/m^2/day)
/*
/*	    The output files are  in short integer binary format.Values of temepratures, precipitaion
/*      radiation are multiplied by 10 and then converted into short integers (Radiation*10,Tmin*10,
/*		Tmax*10, Precipitation*10,dew-point-T*10).
/*
/*      Major algorithms of calculaitons are adopted from Running et al. (1987) and Chen et al.(1999):
/*
/*		Temperature:
/*
/*				Ti,j = (Taverage - f(elevation) x elevation + f(LAI))xf(topography)
/*
/*					where
/*						Ti.j = instantaneous temperature at a pixel
/*						Taverage = weighted average daylight air temperature
/*						f(elevation) = elevation lapse rate correction -7degree C/Km
/*						f(topography) = topographic correction. Radiation ratio of slope:flat.
/*										It will be discussed later
/*						f(LAI) = site leaf area index correction. Unit: degree C/LAI
/*								For south facing slope (135 - 225 degree), if LAI <2.0
/*								f(LAI) = 2 else f(LAI)=1
/*					If the ratio of basestation to expected radiation is < 0.5W/m^2,
/*						Ti,j += Ti.j*10%
/*					else
/*						Ti,j -= Ti.j*10%
/*		Dew Point:
/*
/*				If there is no dew point measured at base station, use the minimum temperature
/*				as daily dew point. Dew poit is used as intermediate variable for VPD calculation.
/*				DewPi,j = DewPbase-f(elevation)*Ei.j
/*				 	Where
/*						DewPi.j = daily dew point at pixel i.j
/*						DewPbase = measured daily dew point at base station
/*						f(elevation)= -1.25 degree C /km
/*				 		Ei,j = elevation at pixel i.j
/*
/*			Precipitation
/*
/*				Popi,j = PopBase * f(elevation)
/*
/*				Where
/*					Popi,j = precipitation at pixel i,j
/*					PopBase = base station precipitation
/*					f(elevation) = Isohyet or the site:base ratio of precipitation. It is currently
/*					assigned as 1.
//
//  MM/juw 2005-May-6  Changed data type from float to short int to reduce disc requirements
----------------------------------------------------------------------------------------------*/
#include "stdafx.h"
#include "BepsHydrScience.h"
#include "string.h"
#include "malloc.h"
#include "stdio.h"
#include <stdlib.h>
void ClimateCalculate(BH_SubParams1_t* BH_SubParams1,BH_SubParams1a_t* BH_SubParams1a)
{
    int counter;
    int iIndex,iTime,iDay;
    double delta_elevation;
    double  dewpoint;
    double a=0.611, b=17.502, c=240.97; //constants used for vapor pressure calculation.a:KPa,
    double dIsoHyet[]= {1,1,1};         //site:base ratio of precipitation. Currently using constants
    double dDaylong;                    //in unit of hours
    double dTheta;                      //, Sdif, Sdir;
    double p1 =0.05, p2=0.06;
    double wind;
    double dSolar_radiation_r,dSolar_radiation_f;  /*direct and diffused radiation*/

    int rcode;
    struct pubv		v;
    struct pubv*	pv = &v;

    climatedata climate;  	//define a structure pointer climate points to Climate_t structure.
    baseline_t baseline;
    base_t* basetemp;  // define structure type of base_t to hold the daily information of the base station

    char    pszTempStrings[10][32];
    short int*	climate_rad_r,	*climate_rad_f;	//climate_rad;
    short int*	climate_ti;
    short int*	climate_tm;
    short int*	climate_tmean;    //自行添加
    short int*	climate_prec;
    short int*	climate_dew;
    short int*	climate_wind;
    float*	climate_snowd;
    float*	climate_watert;

    float* pfAltitude;
    float* pfGradient;
    float* pfAzimuth;
    FILE* base_ptr;
    FILE* dem_ptr;
    FILE* slope_ptr;
    FILE* aspect_ptr;

    FILE* climate_rad_r_ptr, *climate_rad_f_ptr;	//climate_rad_ptr;	MM/juw
    FILE* climate_ti_ptr;
    FILE* climate_tm_ptr;
    FILE* climate_tmean_ptr;                       // 自行添加
    FILE* climate_prec_ptr;
    FILE* climate_dew_ptr;
    FILE* climate_wind_ptr;
    int kkk=0;
// changed radiative flux file from one (ie RAD) to two, RAD_r is direct, RAD_f is diffuse  MM/juw  2005-May-6
    char	szClimateOutFileNameRAD_r[MAX_PATH],
            szClimateOutFileNameRAD_f[MAX_PATH],
            szClimateOutFileNameTI[MAX_PATH],
            szClimateOutFileNameTM[MAX_PATH],
            szClimateOutFileNameTMEAN[MAX_PATH],        // 自行添加
            szClimateOutFileNamePREC[MAX_PATH],
            szClimateOutFileNameDEW[MAX_PATH],
            szClimateOutFileNameWIND[MAX_PATH];
    //szClimateOutFileNameSNOWD[MAX_PATH],szClimateOutFileNameWATERT[MAX_PATH];

    //initialization:
    counter						= 0;
    rcode						= 0;
    climate_rad_r				= NULL;
    climate_rad_f				= NULL;
    climate_ti					= NULL;
    climate_tm					= NULL;
    climate_tmean				= NULL;    //自行添加
    climate_prec				= NULL;
    climate_dew					= NULL;
    climate_wind				= NULL;
    climate_snowd				= NULL;
    climate_watert				= NULL;
    pfAltitude					= NULL;
    pfGradient					= NULL;
    pfAzimuth					= NULL;
    basetemp					= NULL;
    base_ptr					= NULL;
    dem_ptr						= NULL;
    slope_ptr					= NULL;
    aspect_ptr					= NULL;
    climate_rad_r_ptr			= NULL;
    climate_rad_f_ptr			= NULL;
    climate_ti_ptr				= NULL;
    climate_tm_ptr				= NULL;
    climate_tmean_ptr			= NULL;   //自行添加
    climate_prec_ptr			= NULL;
    climate_dew_ptr				= NULL;
    climate_wind_ptr			= NULL;

    v.jday_start				= BH_SubParams1->iDayStart;		//150
    v.jday_end					= BH_SubParams1->iDayEnd;			//152
    v.nlines					= BH_SubParams1->iNumLines;		//360
    v.npixels					= BH_SubParams1->iNumPixels;		//360
    v.factor					= BH_SubParams1->iNPPMultFactor;	//10000

    v.ULLat						= BH_SubParams1->fULCLatitude;		//54.0320
    v.ULLong					= BH_SubParams1->fULCLongitude;	//105.188
    v.LRLat						= BH_SubParams1->fLRCLatitude;		//53.9230
    v.LRLong					= BH_SubParams1->fLRCLongitude;	//104.943



    if (	((pfAltitude		= new float[pv->npixels])		== NULL)
            ||	((pfGradient		= new float[pv->npixels])		== NULL)
            ||	((pfAzimuth			= new float[pv->npixels])		== NULL)
            ||	((climate_rad_r		= new short int[pv->npixels])		== NULL)
            ||	((climate_rad_f		= new short int[pv->npixels])		== NULL)
            ||	((climate_ti		= new short int[pv->npixels])		== NULL)
            ||	((climate_tm		= new short int[pv->npixels])		== NULL)
            ||	((climate_tmean		= new short int[pv->npixels])		== NULL)   //自行添加
            ||	((climate_prec		= new short int[pv->npixels])		== NULL)
            ||	((climate_dew		= new short int[pv->npixels])		== NULL)
            ||	((climate_wind		= new short int[pv->npixels])		== NULL)
            ||	((basetemp			= new base_t[pv->jday_end - pv->jday_start + 1])==NULL))
        rcode = PERROR;
    else if (((base_ptr			=fopen(BH_SubParams1->szInFileNameBaseClimate	,"rb"))==NULL)
             ||	((dem_ptr			=fopen(BH_SubParams1->szInFileNameDEM			,"rb"))==NULL)
             ||	((slope_ptr			=fopen(BH_SubParams1->szInFileNameSlope		,"rb"))==NULL)
             ||	((aspect_ptr		=fopen(BH_SubParams1->szInFileNameAspect		,"rb"))==NULL))
        rcode = PERROR;

    if (rcode!=PERROR)
    {
        //读取站点信息
        if (fscanf(base_ptr,"%s\t%s\t%s\t%s\n"
                   ,pszTempStrings[0],pszTempStrings[1],pszTempStrings[2],pszTempStrings[3]) != 4)
            rcode = PERROR;
        else
        {
            baseline.dLat			= atof(pszTempStrings[0]);
            baseline.dLong			= atof(pszTempStrings[1]);
            baseline.dElevation		= atof(pszTempStrings[2]);
            baseline.dLongref		= atof(pszTempStrings[3]);

            printf("Sites Informatin:%f %f %f %f \n",baseline.dLat,baseline.dLong,baseline.dElevation,baseline.dLongref);
        }

        //读取站点气象数据
        for(iTime=0,counter=0; (iTime<365)&&(counter<pv->jday_end-pv->jday_start+1)&&(rcode!=PERROR); iTime++)
        {
            if (fscanf(	base_ptr
                        ,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n" //t%s\t%s\n
                        ,pszTempStrings[0],pszTempStrings[1],pszTempStrings[2],pszTempStrings[3]
                        ,pszTempStrings[4],pszTempStrings[5],pszTempStrings[6],pszTempStrings[7]) != 8)
                rcode = PERROR;
            else
                iDay = atoi(pszTempStrings[0]);

            //when the simulation day is reached, assign the structure data to basetemp array
            if((iDay>=pv->jday_start)&&(iDay<=pv->jday_end)&&(rcode!=PERROR))
            {
                basetemp[counter].iday			= iDay;
                basetemp[counter].dTmax			= atof(pszTempStrings[1]);
                basetemp[counter].dTmin			= atof(pszTempStrings[2]);
                basetemp[counter].dTmean		= atof(pszTempStrings[3]);  //自带
                basetemp[counter].dDewpoint		= atof(pszTempStrings[4]);
                basetemp[counter].dPrecip		= atof(pszTempStrings[5]);
                basetemp[counter].dRadiation	= atof(pszTempStrings[6]);
                basetemp[counter].dWind			= atof(pszTempStrings[7]);

                dDaylong						= compute_daylength(&baseline,iDay)*0.85;
                basetemp[counter].dRadiation	= basetemp[counter].dRadiation*1000.0/(dDaylong*3600);//unit w per square meter


                //printf("Procecss Day: %d %f \n", basetemp[counter].iday, basetemp[counter].dTmin);
                counter++;
                kkk=0;
            }
        }//end of iTime for-loop

        fclose(base_ptr);
        base_ptr = NULL;

        //站点区域插值

        for (iDay=pv->jday_start; (iDay<=pv->jday_end)&&(rcode!=PERROR); iDay++)
        {
            //set output file names:

            printf("Procecss Day: %d\n",iDay);

            insert_day_number(szClimateOutFileNameRAD_r,BH_SubParams1a->szOutFileNameClimateRAD_r,iDay); // same base name with new suffix MM/juw
            insert_day_number(szClimateOutFileNameRAD_f,BH_SubParams1a->szOutFileNameClimateRAD_f,iDay);
            insert_day_number(szClimateOutFileNameTI,BH_SubParams1a->szOutFileNameClimateTi,iDay);
            insert_day_number(szClimateOutFileNameTM,BH_SubParams1a->szOutFileNameClimateTm,iDay);
            insert_day_number(szClimateOutFileNameTMEAN,BH_SubParams1a->szOutFileNameClimateTmean,iDay);       //自行添加
            insert_day_number(szClimateOutFileNamePREC,BH_SubParams1a->szOutFileNameClimatePrec,iDay);
            insert_day_number(szClimateOutFileNameDEW,BH_SubParams1a->szOutFileNameClimateDew,iDay);
            insert_day_number(szClimateOutFileNameWIND,BH_SubParams1a->szOutFileNameClimateWind,iDay);

            if(((climate_rad_r_ptr	=fopen(szClimateOutFileNameRAD_r	,"wb"))==NULL)
                    ||	((climate_rad_f_ptr	=fopen(szClimateOutFileNameRAD_f	,"wb"))==NULL)
                    ||  ((climate_ti_ptr	=fopen(szClimateOutFileNameTI		,"wb"))==NULL)
                    ||  ((climate_tm_ptr	=fopen(szClimateOutFileNameTM		,"wb"))==NULL)
                    ||  ((climate_tmean_ptr	=fopen(szClimateOutFileNameTMEAN	,"wb"))==NULL)     //自行添加
                    ||  ((climate_prec_ptr	=fopen(szClimateOutFileNamePREC		,"wb"))==NULL)
                    ||  ((climate_dew_ptr	=fopen(szClimateOutFileNameDEW		,"wb"))==NULL)
                    ||  ((climate_wind_ptr	=fopen(szClimateOutFileNameWIND		,"wb"))==NULL)
              )
                rcode = PERROR;

            //Radiance value is required for dTheta.
            iIndex = iDay - pv->jday_start;
            dTheta = compute_solar_zenith(&baseline, iDay);		//solar zenith angle at solar noon.

            //rewind data files:
            if (    (fseek(dem_ptr		,0,SEEK_SET)!=0)
                    ||	(fseek(slope_ptr	,0,SEEK_SET)!=0)
                    ||	(fseek(aspect_ptr	,0,SEEK_SET)!=0))
                rcode = PERROR;

            /*====================Start the line loop================================================== */
            /*====================Start the line loop================================================== */

            for (int iL=0; (iL<pv->nlines)&&(rcode!=PERROR); iL++)
            {
                //read in one line of data into each of three input buffers:
                if (	(fread(pfAltitude	,sizeof(float),pv->npixels,dem_ptr)		!=(size_t)pv->npixels)
                        ||	(fread(pfGradient	,sizeof(float),pv->npixels,slope_ptr)	!=(size_t)pv->npixels)
                        ||	(fread(pfAzimuth	,sizeof(float),pv->npixels,aspect_ptr)	!=(size_t)pv->npixels))
                    rcode = PERROR;

                if (rcode!=PERROR)
                {
                    //process a line of data
                    for (int iP=0; iP<pv->npixels; iP++)
                    {
                        if (pfAltitude[iP]>=9999.0f)
                        {
                            //prepare output:
                            climate_rad_r[iP]		= -9999;
                            climate_rad_f[iP]		= -9999;
                            climate_ti[iP]			= -9999;
                            climate_tm[iP]			= -9999;
                            climate_tmean[iP]		= -9999;  //自行添加
                            climate_prec[iP]		= -9999;
                            climate_dew[iP]			= -9999;
                            climate_wind[iP]		= -9999;
                        }//end if pfAltitude[iP] >= 9999
                        else
                        {
                            delta_elevation = (double)pfAltitude[iP] - baseline.dElevation; //elevation diference between current pix/the base station
                            //climate.tmax	= basetemp[iIndex].dTmax - delta_elevation*8/1000;
                            climate.tmax	= basetemp[iIndex].dTmax - delta_elevation*4.9/1000;
                            climate.tmean	= basetemp[iIndex].dTmean - delta_elevation*1.05/1000;   //自行添加
                            climate.tmin	= basetemp[iIndex].dTmin - delta_elevation*1.05/1000;
                            climate.precip  = basetemp[iIndex].dPrecip;


                            if(basetemp[iIndex].dRadiation <= 0||basetemp[iIndex].dRadiation==9999.0)
                            {
                                if(climate.precip>0)
                                    basetemp[iIndex].dRadiation=1370*dTheta*0.707*0.5;
                                else
                                    basetemp[iIndex].dRadiation=1370*dTheta*0.707*0.75;
                            }

                            radiation_ratio(&baseline, iDay, (double)pfGradient[iP], (double)pfAzimuth[iP],basetemp[iIndex].dRadiation,&dSolar_radiation_r,&dSolar_radiation_f);	//ratioed radiance of slope/flat surfaces.

                            if(basetemp[iIndex].dDewpoint == 9999.0)
                            {
                                dewpoint = climate.tmin;	// upgrade MM 2005-Apr-26
                            }
                            else
                                dewpoint = basetemp[iIndex].dDewpoint - 1.25*delta_elevation/1000;

                            /*assuimg that wind is spatially homogeneous  */
                            if(basetemp[iIndex].dWind<0)
                                wind=-10.0;
                            else
                                wind=basetemp[iIndex].dWind;

                            climate_rad_r[iP]		= (short int)(10.0*dSolar_radiation_r);
                            climate_rad_f[iP]		= (short int)(10.0*dSolar_radiation_f);
                            climate_ti[iP]			= (short int)(10.0*climate.tmin);
                            climate_tm[iP]			= (short int)(10.0*climate.tmax);
                            climate_tmean[iP]		= (short int)(10.0*climate.tmean);     //自行添加
                            climate_prec[iP]		= (short int)(10.0*climate.precip);
                            climate_dew[iP]			= (short int)(10.0*dewpoint);
                            climate_wind[iP]		= (short int)(10.0*wind);


                        } //end of end if pfAltitude[iP] < 9999

                    } //end of iP loop

                    //write out a line of data to output climate file:
                    if ((fwrite(climate_rad_r	,sizeof(short int),pv->npixels,climate_rad_r_ptr)	!=(size_t)pv->npixels)
                            ||	(fwrite(climate_rad_f	,sizeof(short int),pv->npixels,climate_rad_f_ptr)	!=(size_t)pv->npixels)

                            ||	(fwrite(climate_ti	,sizeof(short int),pv->npixels,climate_ti_ptr)	!=(size_t)pv->npixels)
                            ||	(fwrite(climate_tm	,sizeof(short int),pv->npixels,climate_tm_ptr)	!=(size_t)pv->npixels)
                            ||	(fwrite(climate_tmean	,sizeof(short int),pv->npixels,climate_tmean_ptr)	!=(size_t)pv->npixels)
                            ||	(fwrite(climate_prec,sizeof(short int),pv->npixels,climate_prec_ptr)!=(size_t)pv->npixels)
                            ||	(fwrite(climate_dew	,sizeof(short int),pv->npixels,climate_dew_ptr)	!=(size_t)pv->npixels)
                            ||	(fwrite(climate_wind,sizeof(short int),pv->npixels,climate_wind_ptr)	!=(size_t)pv->npixels)
                       )
                        rcode=PERROR;

                }//end if(rcode!=PERROR)


            }
            /*======================the end of line loop====================================*/
            /*======================the end of line loop====================================*/
            if (climate_rad_r_ptr)
                fclose(climate_rad_r_ptr);
            climate_rad_r_ptr		= NULL;
            if (climate_rad_f_ptr)
                fclose(climate_rad_f_ptr);
            climate_rad_f_ptr		= NULL;
            if (climate_ti_ptr)
                fclose(climate_ti_ptr);
            climate_ti_ptr		= NULL;
            if (climate_tm_ptr)
                fclose(climate_tm_ptr);
            climate_tm_ptr		= NULL;
            if (climate_tmean_ptr)       //自行添加
                fclose(climate_tmean_ptr);
            climate_tmean_ptr		= NULL;
            if (climate_prec_ptr)
                fclose(climate_prec_ptr);
            climate_prec_ptr	= NULL;
            if (climate_dew_ptr)
                fclose(climate_dew_ptr);
            climate_dew_ptr		= NULL;
            if (climate_wind_ptr)
                fclose(climate_wind_ptr);
            climate_wind_ptr		= NULL;

        }

        /*========================the end of the daily loop=======================================*/

    }//end of if (rcode!=PERROR)

    /*free memory used */
    if (climate_rad_r)
        delete[] climate_rad_r;
    if (climate_rad_f)
        delete[] climate_rad_f;
    if (climate_ti)
        delete[] climate_ti;
    if (climate_tm)
        delete[] climate_tm;
    if (climate_tmean)             //自行添加
        delete[] climate_tmean;
    if (climate_prec)
        delete[] climate_prec;
    if (climate_dew)
        delete[] climate_dew;
    if (climate_wind)
        delete[] climate_wind;
    if (basetemp)
        delete[] basetemp;
    if (pfAltitude)
        delete[] pfAltitude;
    if (pfGradient)
        delete[] pfGradient;
    if (pfAzimuth)
        delete[] pfAzimuth;
    if (dem_ptr)
        fclose(dem_ptr);
    if (slope_ptr)
        fclose(slope_ptr);
    if (aspect_ptr)
        fclose(aspect_ptr);

}

