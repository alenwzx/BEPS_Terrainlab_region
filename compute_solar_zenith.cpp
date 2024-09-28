
/*			Solar Radiation
/*
/*				Given Latitude, Logitude, Reference Meridian, Julian Day and Radiation Above
/*				Canopy (RAC), average daily radiation at a pixel equals 0.707*Radiation_at_noon.
/*				So, we need to calculate the RAC at noon first.
/*
/*				Decimal_hour = 12.00				(in hours)
/*				Theta = 0.0172*iJulian_day (in radiance)
/*				Theta = Angle_julian_day
/*				Equation_of_time = 0.000075 + 0.001868*cos(Theta)-0.03207*sin(Theta)
/*									- 0.014615*cos(2.0*Theta)-0.040849*sin(2.0*Theta)
/*				Equation_of_time = Equation_of_time*24.0/(2.0*pi)
/*
/*				Solar_time = Decimal_hour + (longref-longitude)/15.0 + Equation_of_time;
/*
/*				Solar_declination = 0.006918 - 0.399912*cos(Theta) + 0.070257*sin(Theta)
/*						-0.006758*cos(2.0*Theta) + 0.000907*sin(2.0*Theta) -
/*						0.002697*cos(3.0*Theta) + 0.00148*sin(3.0*Theta)
/*
/*
/*				Phi = latitude *pi/180.0
/*				Sun_zenith = sin(Phi)*sin(Solar_declination) + cos(Phi)*cos(Solar_declination)*
/*							cos((Solar_time - 12.0)*pi/12.0)
/*
/*				Sun_zenith = arctan(SQRT(1.0 - Sun_zenith*Sun_zenith)/Sun_zenith))
/*
/*				Sun_elevation = pi/2.0 - Sun_zenith
/*
/*
/*				Sun_azimuth = cos(Solar_declination)*sin((Solar_time - 12.0)*pi/12.0)/sin(Sun_zenith)
/*				Sun_azimuth = arctan(Sun_azimuth/sqrt((1.0-Sun_azimuth*Sun_azimuth))
/*
/*				Given local sope azimuth and slope magnitude in degrees
/*
/*				radiation correction is calcualted
/*
/*				Relative_radiance = cos(Slope_azimuth - Sun_azimuth)*cos(90-Slope_magnitude)*
/*									cos(Sun_elevation) + sin(90-Slope_magnitude) *sin(Sun_elevatin)
/*
/*				Ri,j = Relative_radiance * 0.707 * Radiation
/*
/*
/*----------------------------------------------------------------------------------------------------*/
#include "stdafx.h"
#include "BepsHydrScience.h"
#include <math.h>

double compute_solar_zenith(baseline_t *baseline, unsigned int iD)
{


	double  dSolar_Azimuth=0;

	double dDH = 12.0; //decimal hour. dDH can vary between 1 to 24 in theory

	double dTheta = 0.0172*iD; //angle in radiance of Julian day

	double dTime = 0.000075 + 0.001868*cos(dTheta) - 0.032077*sin(dTheta)
					- 0.014615*cos(2.0*dTheta) - 0.040849*sin(2.0*dTheta);
		   dTime = dTime*12.0/PI;
	//assume both the dLongref and dLong have negative signs because of north America
	double dSolarTime = dDH - (baseline->dLongref - baseline->dLong)/15.0 + dTime;

	double dSolar_Declination = 0.006918 - 0.399912*cos(dTheta) + 0.070257*sin(dTheta)
			- 0.006758*cos(2.0*dTheta) + 0.000907*sin(2.0*dTheta) - 0.002697*cos(3.0*dTheta)+
			0.00148*sin(3.0*dTheta);
	double dPhi = baseline->dLat*PI/180.0;
	double dZ1 = sin(dPhi)*sin(dSolar_Declination) + cos(dPhi)*cos(dSolar_Declination)*
				cos((dSolarTime - 12.0)*PI/12.0);
	double dSolar_Zenith = atan(sqrt(1.0 - dZ1*dZ1)/dZ1); //in radiance
	double dSolar_Elevation = PI/2.0 - dSolar_Zenith;
	double dA = cos(dSolar_Declination)*sin((dSolarTime-12.0)*PI/12.0)/sin(dSolar_Zenith);
	double h = 15.0*(12.0 - dSolarTime);
	double rou_cos = (cos(dPhi)*sin(dSolar_Declination) -
		cos(dPhi)*sin(dSolar_Declination)*cos( 15*(12-dSolarTime)))/sin(dSolar_Zenith);

	if(dSolarTime <= 12.0 )
		 dSolar_Azimuth = acos(rou_cos);
	else
		dSolar_Azimuth = 2*PI - acos(rou_cos);

		return dSolar_Zenith;

}
