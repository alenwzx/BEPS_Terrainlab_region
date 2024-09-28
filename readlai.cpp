/*************************************************************************
  Function:     readlai.c
  --------
  Description:
  -----------
 	Read LAI files
***************************************************************************
  CCRS (EMS/Applications Division)
  Written by:   J. Liu
  Last update:  May 1998

***************************************************************************
  OTHER UPDATES:
  1.	Date:			August 21, 2003
		Author:			A. Bulynko
		Description:	File I/O was moved outside of the function.
						readlai() will now only "process" the line of integer
						data provided from the main() function, using the
						original (non-comented-out) code.
*****************************************************************************/
#include "stdafx.h"
#include "BepsHydrScience.h"

void readlai(int np,unsigned char* laiimg,double* lai)
{

	int pix;

	// assign the minimum lai values for the major land cover types during the grow season
	// landcover types are: 0 - conifer, 1 - Deciduous, 2 - Mixed, 3 - Burn, 4 - Shr/tran
	//						5 - Shrubwetland, 6 - Grass, 7 - Barren, 8 - Crop, 9 - Urban
	//double laimin[]={1.46,0.45,0.70,0.21,0.32,0.29,0.12,0.13,0.16,0.23};

	for (pix=0;pix<np;pix++)
	{
		//this single date LAI has to be mobiled during grow season especially for decidous
		//mixed forest
	    lai[pix]=((double)laiimg[pix])/10.0;

		if ((lai[pix]<=0)||(lai[pix]>=19)) //==25.5

			lai[pix]=0.01;
	}
}
