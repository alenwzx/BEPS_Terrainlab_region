/*************************************************************************
  Program:     readclim.c
  --------
	Last update: May, 2003

***************************************************************************
  OTHER UPDATES:
  1.	Date:			August 21, 2003
		Author:			A. Bulynko
		Description:	File I/O was moved outside of the function.
						readclim() will now only "process" the line of integer
						data provided from the main() function, using the
						original logic.

  2.	Date :			2005-May-3
		Author			Mark Mortimer/Ajit
		Desription:		added new snow melt parameters, wind, snow depth,water table

  3.	Date :			2005-May-6
		Author			Mark Mortimer/juw
		Desription:		added conversion from short integer to double
*****************************************************************************/
#include "stdafx.h"
#include "BepsHydrScience.h"
#include <math.h>

//void readclim(int np,Climate_t* in_climate_buff, double* climate_buff)	//***Removed by Andriy
void readclim(int np,
              float temp_a,
              short int* climate_rad_r,
              short int* climate_rad_f,
              short int* climate_ti,
              short int* climate_tm,
              short int* climate_prec,
              short int* climate_dew,
              short int* climate_wind,
              climatedata* sdat)		//***Added by Andriy
{


    for(int pix=0; pix<np; pix++)
    {

        if (climate_rad_r[pix]<0)
        {
            sdat[pix].srad		= 0.0;
            sdat[pix].frad		= 0.0;
            sdat[pix].tmin		= 0.0;
            sdat[pix].tmax		= 0.0;
            sdat[pix].precip	= 0.0;
            sdat[pix].dewp		= 0.0;
            sdat[pix].wind		= 0.0;
        }
        else
        {
            sdat[pix].srad		= (double)climate_rad_r[pix]/10.0;
            sdat[pix].frad		= (double)climate_rad_f[pix]/10.0;
            sdat[pix].tmin		= (double)climate_ti[pix]/10.0;
            sdat[pix].tmax		= (double)climate_tm[pix]/10.0;
            sdat[pix].precip	= (double)climate_prec[pix]/10.0;
            sdat[pix].dewp		= (double)climate_dew[pix]/10.0;
            sdat[pix].wind		= (double)climate_wind[pix]/10.0;
        }
    }
}
