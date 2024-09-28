
/*************************************************************************
  Program:     readb.c
  --------
  Description:
  -----------
 	Read biological parameters based on vegetation type.
***************************************************************************
  CCRS (EMS/Applications Division)
  Written by:   J. Liu
  Last update:	December 2000
*****************************************************************************/
#include "stdafx.h"
#include "BepsHydrScience.h"

//***Modified by Andriy: joined readb_init() and readb()
void readb(double *b,unsigned char lc_p,BH_SubParams2_t* pBH_SubParams2)
{
    // XXY applied to IGBP. only for GPP
        b[19]=	0.002; 	//Leaf Resp. Coeff. (kgC/day/kg)
        b[20]=	0.001; 	//Stem Resp. Coeff. (kgC/day/kg)
        b[21]=	0.001; 	//Coarse Root Resp. Coeff. (kgC/day/kg)
        b[24]=	0.003; 	//Fine Root Resp. Coeff. (kgC/day/kg)

     	b[25]=	2.1; //Leaf Exp. Respiration Constant(Q10)
		b[28]=	1.7; //Stem Exp. Respiration Constant(Q10)
		b[29]=	1.9; //Root Exp. Respiration Constant(Q10)

    	b[37]=	0.95; //The decay rate of roots
		b[38]=	0; //Stem Litter C Turnover Fraction
		b[39]=	0.4; //Root Litter C Turnover Fraction
		b[43]=	0.35; //Leaf Growth Resp. Fraction
		b[44]=	0.30; //Stem Growth Resp. Fraction
		b[45]=	0.35; //Root Growth Resp. Fraction
        b[10]=	0; //Minimum stomatal Conduction (m/sec)

	    b[55]=  0.08; // Leaf Boundary Layer Conductance
		b[56]=  0.00005; // Leaf Cuticular Conductance

        b[12]=	0.01;  //Coefficient in the relationship between Gs and PPFD

        b[17]=0; 	//Minimum Temperature for Photosynthesis (0C)
		b[18]=40; 	//Maximum Temperature for Photosynthesis (0C)
		b[16]=20; 	//Optimum Temperature for Photosynthesis (0C)

		b[14]=1;  /* Leaf Water Potential at Stomatal Opening (-Mpa)	*/

		b[53]= 1.5 ;  // Maximum Leaf N content (%)
        b[54]=  1.2; //Actural Leaf N content (%)

		b[7]=0.5; /* b(7) water aborption */
		b[8]=0.12; /* b(8) snow absorption  */

		b[22]= -30;	/* b(22) snowpack energy deficit C 		*/
    	b[27]=0.2; /* b(27) soil characteristic parameter	*/

		b[4]=0.0003;	/* b(4) Ppt Interception co. m lai-1 d-1 */


     switch(lc_p)
	{
	case 1://ENF

        b[1]  =20;	//specific leaf area m2 kg-1 C
		b[6]  =0.0022;/* b(6) Snowmelt Temp coeff.  */
		b[15] =4;//2.3;  /* Leaf Water Potential at Stomatal Closure(-Mpa)		*/
		b[52] =62.8; // Vmax at 25 0C
        b[51] =0.6; // Canopy Clumping Index
		b[9]  =0.002; //Maximum stomatal Conduction (m/sec)
		b[13] =0.076;  /* Chnage of Stomatal Conductance with VPD*/
		b[11] =2;  //Ratio of Gmax of Overstory to that of Under


    break;
		case 2://EBF

        b[1]  =25;	//specific leaf area m2 kg-1 C
		b[6]  =0.001;/* b(6) Snowmelt Temp coeff.  */
		b[15] =8;//3.9;  /* Leaf Water Potential at Stomatal Closure(-Mpa)		*/
		b[52] =42.4; // Vmax at 25 0C
        b[51] =0.8; // Canopy Clumping Index
		b[9]  =0.004; //Maximum stomatal Conduction (m/sec)
		b[13] =0.429;  /* Chnage of Stomatal Conductance with VPD*/
		b[11] =0.5;  //Ratio of Gmax of Overstory to that of Under


    break;
		case 3://DNF

        b[1]  =22.5;	//specific leaf area m2 kg-1 C
		b[6]  =0.0022;/* b(6) Snowmelt Temp coeff.  */
		b[15] =4;//2.3;  /* Leaf Water Potential at Stomatal Closure(-Mpa)		*/
		b[52] =41.7; // Vmax at 25 0C
        b[51] =0.6; // Canopy Clumping Index
		b[9]  =0.0025; //Maximum stomatal Conduction (m/sec)
		b[13] =0.076;  /* Chnage of Stomatal Conductance with VPD*/
		b[11] =2;  //Ratio of Gmax of Overstory to that of Under


    break;
		case 4://DBF

        b[1]  =26.5;	//specific leaf area m2 kg-1 C
		b[6]  =0.001;/* b(6) Snowmelt Temp coeff.  */
		b[15] =8;//3.9;  /* Leaf Water Potential at Stomatal Closure(-Mpa)		*/
		b[52] =59.9; // Vmax at 25 0C
        b[51] =0.8; // Canopy Clumping Index
		b[9]  =0.0045; //Maximum stomatal Conduction (m/sec)
		b[13] =0.429;  /* Chnage of Stomatal Conductance with VPD*/
		b[11] =0.5;  //Ratio of Gmax of Overstory to that of Under


    break;
		case 5://MF

        b[1]  =24;	//specific leaf area m2 kg-1 C
		b[6]  =0.0015;/* b(6) Snowmelt Temp coeff.  */
		b[15] =8;//2.3;  /* Leaf Water Potential at Stomatal Closure(-Mpa)		*/
		b[52] =51.7; // Vmax at 25 0C
        b[51] =0.7; // Canopy Clumping Index
		b[9]  =0.0036; //Maximum stomatal Conduction (m/sec)
		b[13] =0.253;  /* Chnage of Stomatal Conductance with VPD*/
		b[11] =1;  //Ratio of Gmax of Overstory to that of Under


    break;
		case 6://SHR

        b[1]  =28.7;	//specific leaf area m2 kg-1 C
		b[6]  =0.002;/* b(6) Snowmelt Temp coeff.  */
		b[15] =8;//4.2;  /* Leaf Water Potential at Stomatal Closure(-Mpa)		*/
		b[52] =59.5; // Vmax at 25 0C
        b[51] =0.5; // Canopy Clumping Index
		b[9]  =0.004; //Maximum stomatal Conduction (m/sec)
		b[13] =0.076;  /* Chnage of Stomatal Conductance with VPD*/
		b[11] =1;  //Ratio of Gmax of Overstory to that of Under


    break;
		case 7://GRA

        b[1]  =30;	//specific leaf area m2 kg-1 C
		b[6]  =0.001;/* b(6) Snowmelt Temp coeff.  */
		b[15] =8;//2.7;  /* Leaf Water Potential at Stomatal Closure(-Mpa)		*/
		b[52] =90.3; // Vmax at 25 0C
        b[51] =0.85; // Canopy Clumping Index
		b[9]  =0.01; //Maximum stomatal Conduction (m/sec)
		b[13] =0.076;  /* Chnage of Stomatal Conductance with VPD*/
		b[11] =1;  //Ratio of Gmax of Overstory to that of Under


    break;
		case 8://CRO

        b[1]  =30;	//specific leaf area m2 kg-1 C
		b[6]  =0.001;/* b(6) Snowmelt Temp coeff.  */
		b[15] =8;//2.7;/* Leaf Water Potential at Stomatal Closure(-Mpa)		*/
		b[52] =90.5; // Vmax at 25 0C
        b[51] =0.85; // Canopy Clumping Index
		b[9]  =0.01; //Maximum stomatal Conduction (m/sec)
		b[13] =0.076;  /* Chnage of Stomatal Conductance with VPD*/
		b[11] =1;  //Ratio of Gmax of Overstory to that of Under


    break;
		case 9://urban

        b[1]  =0;	//specific leaf area m2 kg-1 C
		b[6]  =0.001;/* b(6) Snowmelt Temp coeff.  */
		b[15] =0;  /* Leaf Water Potential at Stomatal Closure(-Mpa)		*/
		b[52] =0; // Vmax at 25 0C
        b[51] =0; // Canopy Clumping Index
		b[9]  =0; //Maximum stomatal Conduction (m/sec)
		b[13] =0.01;  /* Chnage of Stomatal Conductance with VPD*/
		b[11] =0;  //Ratio of Gmax of Overstory to that of Under

		b[53]= 0;  // Maximum Leaf N content (%)
        b[54]=  0; //Actural Leaf N content (%)
        b[17]=0; 	//Minimum Temperature for Photosynthesis (0C)
		b[18]=0; 	//Maximum Temperature for Photosynthesis (0C)
		b[16]=0; 	//Optimum Temperature for Photosynthesis (0C)
		b[7]=1; /* b(7) water aborption */
		b[8]=1; /* b(8) snow absorption  */
		b[4]=0;	/* b(4) Ppt Interception co. m lai-1 d-1 */
		b[22]=0;	/* b(22) snowpack energy deficit C 		*/
    	b[27]=0; /* b(27) soil characteristic parameter		*/
		 break;
	case 0://water

        b[1]  =0;	//specific leaf area m2 kg-1 C
		b[6]  =0.001;/* b(6) Snowmelt Temp coeff.  */
		b[15] =0;  /* Leaf Water Potential at Stomatal Closure(-Mpa)		*/
		b[52] =0; // Vmax at 25 0C
        b[51] =0; // Canopy Clumping Index
		b[9]  =0; //Maximum stomatal Conduction (m/sec)
		b[13] =0.01;  /* Chnage of Stomatal Conductance with VPD*/
		b[11] =0;  //Ratio of Gmax of Overstory to that of Under

		b[53]= 0;  // Maximum Leaf N content (%)
        b[54]=  0; //Actural Leaf N content (%)
        b[17]=0; 	//Minimum Temperature for Photosynthesis (0C)
		b[18]=0; 	//Maximum Temperature for Photosynthesis (0C)
		b[16]=0; 	//Optimum Temperature for Photosynthesis (0C)
		b[7]=1; /* b(7) water aborption */
		b[8]=1; /* b(8) snow absorption  */
		b[4]=0;	/* b(4) Ppt Interception co. m lai-1 d-1 */
		b[22]=0;	/* b(22) snowpack energy deficit C 		*/
    	b[27]=0; /* b(27) soil characteristic parameter		*/

    break;
	default://ENF

        b[1]  =25;	//specific leaf area m2 kg-1 C
		b[6]  =0.001;/* b(6) Snowmelt Temp coeff.  */
		b[15] =8;//2.8;  /* Leaf Water Potential at Stomatal Closure(-Mpa)		*/
		b[52] =60; // Vmax at 25 0C
        b[51] =0.7; // Canopy Clumping Index
		b[9]  =5; //Maximum stomatal Conduction (m/sec)
		b[13] =0.076;  /* Chnage of Stomatal Conductance with VPD*/
		b[11] =1;  //Ratio of Gmax of Overstory to that of Under


    break;
	}



}
