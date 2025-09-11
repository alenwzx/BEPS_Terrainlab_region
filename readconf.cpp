#include "stdafx.h"
#include "BepsHydrScience.h"
#include "string.h"
#include "malloc.h"
#include "stdio.h"
#include <stdlib.h>
void readconf(char *conf,BH_SubParams1_t* BH_SubParams1,BH_SubParams1a_t* BH_SubParams1a,BH_SubParams2_t* BH_SubParams2,int *rcode)
{
    char ss1[255],ss2[255],ss3[255],ss4[255],ss5[255],ss6[255],ss7[255];
    char ss8[255],ss9[255],ss10[255],ss11[255],ss12[255],ss13[255],ss14[255],ss15[255],ss16[255];
    char field_descr[255];
    FILE* fcon;

    if ((fcon = fopen(conf,"r")) == nullptr)
    {
        printf("Unable to open <%s>...\n", conf);
        *rcode = NOPERROR;
        return;
    }

    field_descr[0]='\0';
    fscanf(fcon,"%s %s", &field_descr, &ss1);   //jday_start
    field_descr[0]='\0';
    fscanf(fcon,"%s %s", &field_descr, &ss2);   //jday_end
    field_descr[0]='\0';
    fscanf(fcon,"%s %s", &field_descr, &ss3);   //nlines
    field_descr[0]='\0';
    fscanf(fcon,"%s %s", &field_descr, &ss4);   //npixels
    field_descr[0]='\0';
    fscanf(fcon,"%s %s", &field_descr, &ss5);   //iXsize
    field_descr[0]='\0';
    fscanf(fcon,"%s %s", &field_descr, &ss6);   //iYsize
    field_descr[0]='\0';
    fscanf(fcon,"%s %s", &field_descr, &ss7);   //factor
    field_descr[0]='\0';
    fscanf(fcon,"%s %s", &field_descr, &ss8);   //ULLat
    field_descr[0]='\0';
    fscanf(fcon,"%s %s", &field_descr, &ss9);   //ULLong
    field_descr[0]='\0';
    fscanf(fcon,"%s %s", &field_descr, &ss10);   //LRLat
    field_descr[0]='\0';
    fscanf(fcon,"%s %s", &field_descr, &ss11);   //LRLong
    field_descr[0]='\0';
    fscanf(fcon,"%s %s", &field_descr, &ss12);   //InitialSnowDEN
    field_descr[0]='\0';
    fscanf(fcon,"%s %s", &field_descr, &ss13);   //InitialSWE
    field_descr[0]='\0';
    fscanf(fcon,"%s %s", &field_descr, &ss14);   //inputpath
    field_descr[0]='\0';
    fscanf(fcon,"%s %s", &field_descr, &ss15);   //outpath
    field_descr[0]='\0';
    fscanf(fcon,"%s %s", &field_descr, &ss16);   //caculatePattern
    fclose(fcon);

//***********************************************Start of input parameters **********************************************
    BH_SubParams1->iDayStart=atoi(ss1);
    BH_SubParams1->iDayEnd=atoi(ss2);
    BH_SubParams1->iNumLines=atoi(ss3);
    BH_SubParams1->iNumPixels=atoi(ss4);
    BH_SubParams1->iPixelX=atoi(ss5);
    BH_SubParams1->iPixelY=atoi(ss6);
    BH_SubParams1->iNPPMultFactor=atoi(ss7);
    BH_SubParams1->fULCLatitude=atof(ss8);
    BH_SubParams1->fULCLongitude=atof(ss9);
    BH_SubParams1->fLRCLatitude=atof(ss10);
    BH_SubParams1->fLRCLongitude=atof(ss11);
    BH_SubParams1->InitialSnowDEN=atof(ss12);
    BH_SubParams1->InitialSWE=atof(ss13);
    BH_SubParams1->bCalculateClimate=atoi(ss16);

    strcpy(BH_SubParams1->szInFileNameAspect,ss14);
    strcpy(BH_SubParams1->szInFileNameDEM,ss14);
    strcpy(BH_SubParams1->szInFileNameSlope,ss14);
    strcpy(BH_SubParams1->szInFileNameLC,ss14);
    strcpy(BH_SubParams1->szInFileNameLAI,ss14);
    strcpy(BH_SubParams1->szInFileNameWatershed,ss14);
    strcpy(BH_SubParams1->szInFileNameBaseClimate,ss14);
    strcpy(BH_SubParams1->szInFileNameSoilTexture,ss14);
    strcpy(BH_SubParams1->szInFileNameSoilDepth,ss14);
    strcpy(BH_SubParams1->szInFileNameSoilInitZ,ss14);
    strcpy(BH_SubParams1->szInFileNameSoilInitTemp,ss14);
    strcpy(BH_SubParams1->szInFileNameCarbonPool1,ss14);
    strcpy(BH_SubParams1->szInFileNameCarbonPool2,ss14);
    strcpy(BH_SubParams1->szInFileNameCarbonPool3,ss14);
    strcpy(BH_SubParams1->szInFileNameCarbonPool4,ss14);
    strcpy(BH_SubParams1->szInFileNameCarbonPool5,ss14);
    strcpy(BH_SubParams1->szInFileNameCarbonPool6,ss14);
    strcpy(BH_SubParams1->szInFileNameCarbonPool7,ss14);
    strcpy(BH_SubParams1->szInFileNameCarbonPool8,ss14);
    strcpy(BH_SubParams1->szInFileNameCarbonPool9,ss14);
    strcpy(BH_SubParams1->szInFileNameBiomassPool1,ss14);
    strcpy(BH_SubParams1->szInFileNameBiomassPool2,ss14);
    strcpy(BH_SubParams1->szInFileNameBiomassPool3,ss14);
    strcpy(BH_SubParams1->szInFileNameBiomassPool4,ss14);

    strcat(BH_SubParams1->szInFileNameAspect,"aspect.bin");
    strcat(BH_SubParams1->szInFileNameDEM,"DEM.bin");
    strcat(BH_SubParams1->szInFileNameSlope,"slope.bin");
    strcat(BH_SubParams1->szInFileNameLC,"landcover.bin");

    strcat(BH_SubParams1->szInFileNameWatershed,"Watershed.bin");
    strcat(BH_SubParams1->szInFileNameSoilDepth,"soil-depth.bin");
    strcat(BH_SubParams1->szInFileNameSoilTexture,"soil-texture.bin");

    strcat(BH_SubParams1->szInFileNameSoilInitTemp,"initial-SoilTemp.bin");

    strcat(BH_SubParams1->szInFileNameSoilInitZ,"initial-WTD.bin");
    strcpy(BH_SubParams1->szInFileNameSoilInitMoisture,ss14);
    strcat(BH_SubParams1->szInFileNameSoilInitMoisture,"initial-soil-moisture.bin");
    strcat(BH_SubParams1->szInFileNameLAI,"lai.bin");
    strcat(BH_SubParams1->szInFileNameBaseClimate,"climate.txt");

    strcat(BH_SubParams1->szInFileNameCarbonPool1,"Ccd.bin");
    strcat(BH_SubParams1->szInFileNameCarbonPool2,"Cssd.bin");
    strcat(BH_SubParams1->szInFileNameCarbonPool3,"Csmd.bin");
    strcat(BH_SubParams1->szInFileNameCarbonPool4,"Cfmd.bin");
    strcat(BH_SubParams1->szInFileNameCarbonPool5,"Cfsd.bin");
    strcat(BH_SubParams1->szInFileNameCarbonPool6,"Cm.bin");
    strcat(BH_SubParams1->szInFileNameCarbonPool7,"Cs.bin");
    strcat(BH_SubParams1->szInFileNameCarbonPool8,"Cp.bin");
    strcat(BH_SubParams1->szInFileNameCarbonPool9,"Csm.bin");

    strcat(BH_SubParams1->szInFileNameBiomassPool1,"Bio_Wood.bin");
    strcat(BH_SubParams1->szInFileNameBiomassPool2,"Bio_C.Root.bin");
    strcat(BH_SubParams1->szInFileNameBiomassPool3,"Bio_Leafs.bin");
    strcat(BH_SubParams1->szInFileNameBiomassPool4,"Bio_F.Root.bin");


    // //set default soil texture index parameters:
    // BH_SubParams1->SoilTextureIndexVals[0].mytexture		= 10;
    // BH_SubParams1->SoilTextureIndexVals[0].pore_index		= 0.070;
    // BH_SubParams1->SoilTextureIndexVals[0].soil_b			= 4.05;
    // BH_SubParams1->SoilTextureIndexVals[0].suction_head	    = 0.121;
    // BH_SubParams1->SoilTextureIndexVals[0].soil_K0		    = 15.21;
    // BH_SubParams1->SoilTextureIndexVals[0].max_z			= 2.0;
    // BH_SubParams1->SoilTextureIndexVals[0].wilting_pt		= 0.03;
    // BH_SubParams1->SoilTextureIndexVals[0].field_cap		= 0.09;
    // BH_SubParams1->SoilTextureIndexVals[0].porosity		    = 0.437;
    // BH_SubParams1->SoilTextureIndexVals[0].MaxiGs		    = 0.01;
    // BH_SubParams1->SoilTextureIndexVals[0].soil_K0H		    = 10.0;
    //
    // BH_SubParams1->SoilTextureIndexVals[1].mytexture		= 20;
    // BH_SubParams1->SoilTextureIndexVals[1].pore_index		= 0.027;
    // BH_SubParams1->SoilTextureIndexVals[1].soil_b			= 10.40;
    // BH_SubParams1->SoilTextureIndexVals[1].suction_head	    = 0.490;
    // BH_SubParams1->SoilTextureIndexVals[1].soil_K0		    = 0.09;
    // BH_SubParams1->SoilTextureIndexVals[1].max_z			= 2.0;
    // BH_SubParams1->SoilTextureIndexVals[1].wilting_pt		= 0.06;
    // BH_SubParams1->SoilTextureIndexVals[1].field_cap		= 0.13;
    // BH_SubParams1->SoilTextureIndexVals[1].porosity		    = 0.437;
    // BH_SubParams1->SoilTextureIndexVals[1].MaxiGs		    = 0.01;
    // BH_SubParams1->SoilTextureIndexVals[1].soil_K0H		    = 10.0;
    //
    // BH_SubParams1->SoilTextureIndexVals[2].mytexture		= 30;      //sandy loam
    // BH_SubParams1->SoilTextureIndexVals[2].pore_index		= 0.050;
    // BH_SubParams1->SoilTextureIndexVals[2].soil_b			= 4.90;
    // BH_SubParams1->SoilTextureIndexVals[2].suction_head     = 0.218;
    // BH_SubParams1->SoilTextureIndexVals[2].soil_K0		    = 3.00;
    // BH_SubParams1->SoilTextureIndexVals[2].max_z			= 2.0;      // 土壤深度
    // BH_SubParams1->SoilTextureIndexVals[2].wilting_pt		= 0.10;
    // BH_SubParams1->SoilTextureIndexVals[2].field_cap		= 0.21;
    // BH_SubParams1->SoilTextureIndexVals[2].porosity		    = 0.453;
    // BH_SubParams1->SoilTextureIndexVals[2].MaxiGs		    = 0.01;
    // BH_SubParams1->SoilTextureIndexVals[2].soil_K0H		    = 10.0;
    //
    // BH_SubParams1->SoilTextureIndexVals[3].mytexture		= 40;
    // BH_SubParams1->SoilTextureIndexVals[3].pore_index		= 0.045;
    // BH_SubParams1->SoilTextureIndexVals[3].soil_b			= 5.30;
    // BH_SubParams1->SoilTextureIndexVals[3].suction_head	    = 0.786;
    // BH_SubParams1->SoilTextureIndexVals[3].soil_K0		    = 0.62;
    // BH_SubParams1->SoilTextureIndexVals[3].max_z			= 2.0;
    // BH_SubParams1->SoilTextureIndexVals[3].wilting_pt		= 0.13;
    // BH_SubParams1->SoilTextureIndexVals[3].field_cap		= 0.33;
    // BH_SubParams1->SoilTextureIndexVals[3].porosity		    = 0.501;
    // BH_SubParams1->SoilTextureIndexVals[3].MaxiGs		    = 0.01;
    // BH_SubParams1->SoilTextureIndexVals[3].soil_K0H		    = 10.0;
    //
    // BH_SubParams1->SoilTextureIndexVals[4].mytexture		= 50;   //loam
    // BH_SubParams1->SoilTextureIndexVals[4].pore_index		= 0.040;
    // BH_SubParams1->SoilTextureIndexVals[4].soil_b			= 5.39;
    // BH_SubParams1->SoilTextureIndexVals[4].suction_head     = 0.478;
    // BH_SubParams1->SoilTextureIndexVals[4].soil_K0		    = 0.60;
    // BH_SubParams1->SoilTextureIndexVals[4].max_z			= 2.0;
    // BH_SubParams1->SoilTextureIndexVals[4].wilting_pt		= 0.12;
    // BH_SubParams1->SoilTextureIndexVals[4].field_cap		= 0.27;
    // BH_SubParams1->SoilTextureIndexVals[4].porosity		    = 0.463;
    // BH_SubParams1->SoilTextureIndexVals[4].MaxiGs		    = 0.01;
    // BH_SubParams1->SoilTextureIndexVals[4].soil_K0H		    = 0;
    //
    // BH_SubParams1->SoilTextureIndexVals[5].mytexture		= 60;  //sandy clay loam
    // BH_SubParams1->SoilTextureIndexVals[5].pore_index		= 0.038;
    // BH_SubParams1->SoilTextureIndexVals[5].soil_b			= 7.12;
    // BH_SubParams1->SoilTextureIndexVals[5].suction_head 	= 0.299;
    // BH_SubParams1->SoilTextureIndexVals[5].soil_K0		    = 0.54;
    // BH_SubParams1->SoilTextureIndexVals[5].max_z			= 2.0;
    // BH_SubParams1->SoilTextureIndexVals[5].wilting_pt		= 0.15;
    // BH_SubParams1->SoilTextureIndexVals[5].field_cap		= 0.26;
    // BH_SubParams1->SoilTextureIndexVals[5].porosity		    = 0.398;
    // BH_SubParams1->SoilTextureIndexVals[5].MaxiGs		    = 0.01;
    // BH_SubParams1->SoilTextureIndexVals[5].soil_K0H		    = 10.0;
    //
    // BH_SubParams1->SoilTextureIndexVals[6].mytexture		= 70;
    // BH_SubParams1->SoilTextureIndexVals[6].pore_index		= 0.035;
    // BH_SubParams1->SoilTextureIndexVals[6].soil_b			= 7.75;
    // BH_SubParams1->SoilTextureIndexVals[6].suction_head	    = 0.356;
    // BH_SubParams1->SoilTextureIndexVals[6].soil_K0		    = 0.15;
    // BH_SubParams1->SoilTextureIndexVals[6].max_z			= 2.0;
    // BH_SubParams1->SoilTextureIndexVals[6].wilting_pt		= 0.32;
    // BH_SubParams1->SoilTextureIndexVals[6].field_cap		= 0.37;
    // BH_SubParams1->SoilTextureIndexVals[6].porosity  		= 0.471;
    // BH_SubParams1->SoilTextureIndexVals[6].MaxiGs		    = 0.01;
    // BH_SubParams1->SoilTextureIndexVals[6].soil_K0H	    	= 10.0;
    //
    //
    // BH_SubParams1->SoilTextureIndexVals[7].mytexture		= 80;  //clay loam
    // BH_SubParams1->SoilTextureIndexVals[7].pore_index		= 0.029;
    // BH_SubParams1->SoilTextureIndexVals[7].soil_b			= 8.52;
    // BH_SubParams1->SoilTextureIndexVals[7].suction_head	    = 0.630;
    // BH_SubParams1->SoilTextureIndexVals[7].soil_K0		    = 0.21;
    // BH_SubParams1->SoilTextureIndexVals[7].max_z			= 2.0;
    // BH_SubParams1->SoilTextureIndexVals[7].wilting_pt		= 0.20;
    // BH_SubParams1->SoilTextureIndexVals[7].field_cap		= 0.32;
    // BH_SubParams1->SoilTextureIndexVals[7].porosity		    = 0.464;
    // BH_SubParams1->SoilTextureIndexVals[7].MaxiGs		    = 0.01;
    // BH_SubParams1->SoilTextureIndexVals[7].soil_K0H		    = 10.0;
    //
    //
    // BH_SubParams1->SoilTextureIndexVals[8].mytexture	= 90;
    // BH_SubParams1->SoilTextureIndexVals[8].pore_index	= 0.026;
    // BH_SubParams1->SoilTextureIndexVals[8].soil_b		= 10.40;
    // BH_SubParams1->SoilTextureIndexVals[8].suction_head	= 0.153;
    // BH_SubParams1->SoilTextureIndexVals[8].soil_K0		= 0.19;
    // BH_SubParams1->SoilTextureIndexVals[8].max_z		= 2.0;
    // BH_SubParams1->SoilTextureIndexVals[8].wilting_pt	= 0.24;
    // BH_SubParams1->SoilTextureIndexVals[8].field_cap	= 0.34;
    // BH_SubParams1->SoilTextureIndexVals[8].porosity		= 0.430;
    // BH_SubParams1->SoilTextureIndexVals[8].MaxiGs		= 0.01;
    // BH_SubParams1->SoilTextureIndexVals[8].soil_K0H		= 10.0;
    //
    //
    // BH_SubParams1->SoilTextureIndexVals[9].mytexture	= 100;
    // BH_SubParams1->SoilTextureIndexVals[9].pore_index	= 0.054;
    // BH_SubParams1->SoilTextureIndexVals[9].soil_b		= 4.38;
    // BH_SubParams1->SoilTextureIndexVals[9].suction_head	= 0.090;
    // BH_SubParams1->SoilTextureIndexVals[9].soil_K0		= 13.51;
    // BH_SubParams1->SoilTextureIndexVals[9].max_z		= 2.0;
    // BH_SubParams1->SoilTextureIndexVals[9].wilting_pt	= 0.25;
    // BH_SubParams1->SoilTextureIndexVals[9].field_cap	= 0.39;
    // BH_SubParams1->SoilTextureIndexVals[9].porosity		= 0.475;
    // BH_SubParams1->SoilTextureIndexVals[9].MaxiGs		= 0.01;
    // BH_SubParams1->SoilTextureIndexVals[9].soil_K0H		= 10.0;
    //
    // BH_SubParams1->SoilTextureIndexVals[10].mytexture	= 110;  //clay
    // BH_SubParams1->SoilTextureIndexVals[10].pore_index	= 0.020;
    // BH_SubParams1->SoilTextureIndexVals[10].soil_b		= 11.40;
    // BH_SubParams1->SoilTextureIndexVals[10].suction_head= 0.405;
    // BH_SubParams1->SoilTextureIndexVals[10].soil_K0		= 0.11;
    // BH_SubParams1->SoilTextureIndexVals[10].max_z		= 2.0;
    // BH_SubParams1->SoilTextureIndexVals[10].wilting_pt	= 0.27;
    // BH_SubParams1->SoilTextureIndexVals[10].field_cap	= 0.40;
    // BH_SubParams1->SoilTextureIndexVals[10].porosity	= 0.475;
    // BH_SubParams1->SoilTextureIndexVals[10].MaxiGs		= 0.01;
    // BH_SubParams1->SoilTextureIndexVals[10].soil_K0H	= 10.0;
    //
    // BH_SubParams1->SoilTextureIndexVals[11].mytexture	  = 120;
    // BH_SubParams1->SoilTextureIndexVals[11].pore_index	  = 0.050;
    // BH_SubParams1->SoilTextureIndexVals[11].soil_b		  = 6.00;
    // BH_SubParams1->SoilTextureIndexVals[11].suction_head  = 0.05;
    // BH_SubParams1->SoilTextureIndexVals[11].soil_K0		  = 0.30;
    // BH_SubParams1->SoilTextureIndexVals[11].max_z		  = 2.0;
    // BH_SubParams1->SoilTextureIndexVals[11].wilting_pt	  = 0.15;
    // BH_SubParams1->SoilTextureIndexVals[11].field_cap	  = 0.6;
    // BH_SubParams1->SoilTextureIndexVals[11].porosity	  = 0.83;
    // BH_SubParams1->SoilTextureIndexVals[11].MaxiGs		  = 0.01;
    // BH_SubParams1->SoilTextureIndexVals[11].soil_K0H	  = 10.0;





    // test
    // BH_SubParams1->SoilTextureIndexVals[2].mytexture		= 30;
    // BH_SubParams1->SoilTextureIndexVals[2].pore_index		= 0.03;
    // BH_SubParams1->SoilTextureIndexVals[2].soil_b			= 4.90;
    // BH_SubParams1->SoilTextureIndexVals[2].suction_head	    = 0.45;
    // BH_SubParams1->SoilTextureIndexVals[2].soil_K0		    = 50;
    // BH_SubParams1->SoilTextureIndexVals[2].max_z			= 0.7;
    // BH_SubParams1->SoilTextureIndexVals[2].wilting_pt		= 0.10;
    // BH_SubParams1->SoilTextureIndexVals[2].field_cap		= 0.21;
    // BH_SubParams1->SoilTextureIndexVals[2].porosity		    = 0.435;
    // BH_SubParams1->SoilTextureIndexVals[2].MaxiGs		    = 0.002;
    // BH_SubParams1->SoilTextureIndexVals[2].soil_K0H		    = 6;
    //
    // BH_SubParams1->SoilTextureIndexVals[3].mytexture		= 40;
    // BH_SubParams1->SoilTextureIndexVals[3].pore_index		= 0.005;
    // BH_SubParams1->SoilTextureIndexVals[3].soil_b			= 5.30;
    // BH_SubParams1->SoilTextureIndexVals[3].suction_head  	= 0.786;
    // BH_SubParams1->SoilTextureIndexVals[3].soil_K0		    = 3;
    // BH_SubParams1->SoilTextureIndexVals[3].max_z		 	= 0.7;
    // BH_SubParams1->SoilTextureIndexVals[3].wilting_pt		= 0.13;
    // BH_SubParams1->SoilTextureIndexVals[3].field_cap		= 0.33;
    // BH_SubParams1->SoilTextureIndexVals[3].porosity		    = 0.501;
    // BH_SubParams1->SoilTextureIndexVals[3].MaxiGs		    = 0.004;
    // BH_SubParams1->SoilTextureIndexVals[3].soil_K0H		    = 3;
    //
    //
    // BH_SubParams1->SoilTextureIndexVals[11].mytexture	    = 120;
    // BH_SubParams1->SoilTextureIndexVals[11].pore_index	    = 0.050;
    // BH_SubParams1->SoilTextureIndexVals[11].soil_b		    = 6.00;
    // BH_SubParams1->SoilTextureIndexVals[11].suction_head    = 0.2;
    // BH_SubParams1->SoilTextureIndexVals[11].soil_K0		    = 50;
    // BH_SubParams1->SoilTextureIndexVals[11].max_z		    = 0.7;
    // BH_SubParams1->SoilTextureIndexVals[11].wilting_pt	    = 0.15;
    // BH_SubParams1->SoilTextureIndexVals[11].field_cap	    = 0.6;
    // BH_SubParams1->SoilTextureIndexVals[11].porosity	    = 0.83;
    // BH_SubParams1->SoilTextureIndexVals[11].MaxiGs		    = 0.002;
    // BH_SubParams1->SoilTextureIndexVals[11].soil_K0H	    = 50.0;


// --- Start of parameter initialization logic ---
    Soil_index_t* soilParams = BH_SubParams1->SoilTextureIndexVals;
    const int num_layers = MAX_LAYERS;

    // --- Texture 10 (Sand) ---
    int idx = 0;
    soilParams[idx].mytexture           = 10;
    // -- Scalar parameters (Use actual BTL default values here!) --
    soilParams[idx].pore_index          = 0.070;
    soilParams[idx].max_z               = 2.0;
    soilParams[idx].MaxiGs              = 0.01;
    soilParams[idx].wilting_pt          = 0.03;      // wilting_pt (theta_vwp)
    // -- Layered parameters (Values from init_soil.c case 1) --
    // soil_b
    soilParams[idx].soil_b[0]           = 1.7;       soilParams[idx].soil_b[1]           = 1.9;       soilParams[idx].soil_b[2]           = 2.1;       soilParams[idx].soil_b[3]           = 2.3;       soilParams[idx].soil_b[4]           = 2.5;
    // suction_head (psi_sat)
    soilParams[idx].suction_head[0]     = 0.07;      soilParams[idx].suction_head[1]     = 0.08;      soilParams[idx].suction_head[2]     = 0.09;      soilParams[idx].suction_head[3]     = 0.10;      soilParams[idx].suction_head[4]     = 0.12;
    // soil_K0 (Vertical Ksat, m/day)
    soilParams[idx].soil_K0[0]          = 5.0112;    soilParams[idx].soil_K0[1]          = 4.4928;    soilParams[idx].soil_K0[2]          = 3.9744;    soilParams[idx].soil_K0[3]          = 3.0240;    soilParams[idx].soil_K0[4]          = 0.8640;
    // field_cap (theta_vfc) - now layered
    soilParams[idx].field_cap[0]        = 0.09;      soilParams[idx].field_cap[1]        = 0.09;      soilParams[idx].field_cap[2]        = 0.09;      soilParams[idx].field_cap[3]        = 0.09;      soilParams[idx].field_cap[4]        = 0.09;
    // porosity (fei) - now layered
    soilParams[idx].porosity[0]         = 0.437;     soilParams[idx].porosity[1]         = 0.437;     soilParams[idx].porosity[2]         = 0.437;     soilParams[idx].porosity[3]         = 0.437;     soilParams[idx].porosity[4]         = 0.437;
    // soil_K0H (Horizontal Ksat) - Use BTL scalar default for all layers
    for(int i=0; i<num_layers; ++i) soilParams[idx].soil_K0H[i] = 10.0;// CHECK BTL DEFAULT for Sand!
    soilParams[idx].water_table_change_limit = 0.05;  // Maximum daily water table change (m)

    // --- Texture 20 (Loamy Sand) ---
    idx = 1;
    soilParams[idx].mytexture           = 20;
    // -- Scalar parameters (Use actual BTL default values here!) --
    soilParams[idx].pore_index          = 0.027;
    soilParams[idx].max_z               = 2.0;
    soilParams[idx].MaxiGs              = 0.01;
    soilParams[idx].wilting_pt          = 0.06;
    // -- Layered parameters (Values from init_soil.c case 2) --
    soilParams[idx].soil_b[0]           = 2.1;      soilParams[idx].soil_b[1]           = 2.3;      soilParams[idx].soil_b[2]           = 2.5;      soilParams[idx].soil_b[3]           = 2.7;      soilParams[idx].soil_b[4]           = 2.9;
    soilParams[idx].suction_head[0]     = 0.09;     soilParams[idx].suction_head[1]     = 0.10;     soilParams[idx].suction_head[2]     = 0.11;     soilParams[idx].suction_head[3]     = 0.12;     soilParams[idx].suction_head[4]     = 0.14;
    soilParams[idx].soil_K0[0]          = 1.4688;   soilParams[idx].soil_K0[1]          = 1.2960;   soilParams[idx].soil_K0[2]          = 1.2096;   soilParams[idx].soil_K0[3]          = 0.8640;   soilParams[idx].soil_K0[4]          = 0.2592;
    // field_cap (theta_vfc) - now layered
    soilParams[idx].field_cap[0]        = 0.21;     soilParams[idx].field_cap[1]        = 0.21;     soilParams[idx].field_cap[2]        = 0.21;     soilParams[idx].field_cap[3]        = 0.21;     soilParams[idx].field_cap[4]        = 0.21;
    // porosity (fei) - now layered
    soilParams[idx].porosity[0]         = 0.437;    soilParams[idx].porosity[1]         = 0.437;    soilParams[idx].porosity[2]         = 0.437;    soilParams[idx].porosity[3]         = 0.437;    soilParams[idx].porosity[4]         = 0.437;
    for(int i=0; i<num_layers; ++i) soilParams[idx].soil_K0H[i] = 10.0;// CHECK BTL DEFAULT for Loamy Sand!
    soilParams[idx].water_table_change_limit = 0.05;  // Maximum daily water table change (m)

    // --- Texture 30 (Sandy Loam) ---
    idx = 2;
    soilParams[idx].mytexture           = 30;
    // -- Scalar parameters (Use actual BTL default values here!) --
    soilParams[idx].pore_index          = 0.016;
    soilParams[idx].max_z               = 2.0;
    soilParams[idx].MaxiGs              = 0.01;
    soilParams[idx].wilting_pt          = 0.10;
    // -- Layered parameters (Values from init_soil.c case 3) --
    soilParams[idx].soil_b[0]           = 3.1;      soilParams[idx].soil_b[1]           = 3.3;      soilParams[idx].soil_b[2]           = 3.5;      soilParams[idx].soil_b[3]           = 3.7;      soilParams[idx].soil_b[4]           = 3.9;
    soilParams[idx].suction_head[0]     = 0.15;     soilParams[idx].suction_head[1]     = 0.16;     soilParams[idx].suction_head[2]     = 0.17;     soilParams[idx].suction_head[3]     = 0.18;     soilParams[idx].suction_head[4]     = 0.20;
    soilParams[idx].soil_K0[0]          = 0.62208;  soilParams[idx].soil_K0[1]          = 0.559872; soilParams[idx].soil_K0[2]          = 0.497664; soilParams[idx].soil_K0[3]          = 0.373248; soilParams[idx].soil_K0[4]          = 0.124416;
    // field_cap (theta_vfc) - now layered
    soilParams[idx].field_cap[0]        = 0.21;     soilParams[idx].field_cap[1]        = 0.21;     soilParams[idx].field_cap[2]        = 0.21;     soilParams[idx].field_cap[3]        = 0.21;     soilParams[idx].field_cap[4]        = 0.21;
    // porosity (fei) - now layered
    soilParams[idx].porosity[0]         = 0.453;    soilParams[idx].porosity[1]         = 0.453;    soilParams[idx].porosity[2]         = 0.453;    soilParams[idx].porosity[3]         = 0.453;    soilParams[idx].porosity[4]         = 0.453;
    for(int i=0; i<num_layers; ++i) soilParams[idx].soil_K0H[i] = 10.0;// CHECK BTL DEFAULT for Sandy Loam!
    soilParams[idx].water_table_change_limit = 0.05;  // Maximum daily water table change (m)

    // --- Texture 40 (Loam) ---
    idx = 3;
    soilParams[idx].mytexture           = 40;
    // -- Scalar parameters (Use actual BTL default values here!) --
    soilParams[idx].pore_index          = 0.011;
    soilParams[idx].max_z               = 2.0;
    soilParams[idx].MaxiGs              = 0.01;
    soilParams[idx].wilting_pt          = 0.12;
    // -- Layered parameters (Values from init_soil.c case 4) --
    soilParams[idx].soil_b[0]           = 4.5;      soilParams[idx].soil_b[1]           = 4.7;      soilParams[idx].soil_b[2]           = 4.9;      soilParams[idx].soil_b[3]           = 5.1;      soilParams[idx].soil_b[4]           = 5.3;
    soilParams[idx].suction_head[0]     = 0.11;     soilParams[idx].suction_head[1]     = 0.12;     soilParams[idx].suction_head[2]     = 0.13;     soilParams[idx].suction_head[3]     = 0.14;     soilParams[idx].suction_head[4]     = 0.16;
    soilParams[idx].soil_K0[0]          = 0.31968;  soilParams[idx].soil_K0[1]          = 0.28512;  soilParams[idx].soil_K0[2]          = 0.255744; soilParams[idx].soil_K0[3]          = 0.191808; soilParams[idx].soil_K0[4]          = 0.063936;
    // field_cap (theta_vfc) - now layered
    soilParams[idx].field_cap[0]        = 0.31;     soilParams[idx].field_cap[1]        = 0.34;     soilParams[idx].field_cap[2]        = 0.38;     soilParams[idx].field_cap[3]        = 0.40;     soilParams[idx].field_cap[4]        = 0.40;
    // porosity (fei) - now layered
    soilParams[idx].porosity[0]         = 0.463;    soilParams[idx].porosity[1]         = 0.463;    soilParams[idx].porosity[2]         = 0.463;    soilParams[idx].porosity[3]         = 0.463;    soilParams[idx].porosity[4]         = 0.463;
    for(int i=0; i<num_layers; ++i) soilParams[idx].soil_K0H[i] = 10.0;// CHECK BTL DEFAULT for Loam!
    soilParams[idx].water_table_change_limit = 0.05;  // Maximum daily water table change (m)

    // --- Texture 50 (Silty Loam) ---
    idx = 4;
    soilParams[idx].mytexture           = 50;
    // -- Scalar parameters (Use actual BTL default values here!) --
    soilParams[idx].pore_index          = 0.04;
    soilParams[idx].max_z               = 20.0;
    soilParams[idx].MaxiGs              = 0.008;
    soilParams[idx].wilting_pt          = 0.12;
    // -- Layered parameters (Values from init_soil.c case 5) --
    soilParams[idx].soil_b[0]           = 5.9;      soilParams[idx].soil_b[1]           = 6.5;      soilParams[idx].soil_b[2]           = 6.7;      soilParams[idx].soil_b[3]           = 6.9;      soilParams[idx].soil_b[4]           = 6.9;
    soilParams[idx].suction_head[0]     = 0.15;     soilParams[idx].suction_head[1]     = 0.16;     soilParams[idx].suction_head[2]     = 0.17;     soilParams[idx].suction_head[3]     = 0.18;     soilParams[idx].suction_head[4]     = 0.19;
    soilParams[idx].soil_K0[0]          = 0.31968;  soilParams[idx].soil_K0[1]          = 0.28512;  soilParams[idx].soil_K0[2]          = 0.255744; soilParams[idx].soil_K0[3]          = 0.191808; soilParams[idx].soil_K0[4]          = 0.063936;
    // field_cap (theta_vfc)
    soilParams[idx].field_cap[0]        = 0.38;     soilParams[idx].field_cap[1]        = 0.41;     soilParams[idx].field_cap[2]        = 0.50;     soilParams[idx].field_cap[3]        = 0.42;     soilParams[idx].field_cap[4]        = 0.42;
    // porosity (fei)
    soilParams[idx].porosity[0]         = 0.50;     soilParams[idx].porosity[1]         = 0.50;     soilParams[idx].porosity[2]         = 0.65;     soilParams[idx].porosity[3]         = 0.46;    soilParams[idx].porosity[4]         = 0.46;
    soilParams[idx].soil_K0H[0]         = 0.00;     soilParams[idx].soil_K0H[1]         = 0.06;     soilParams[idx].soil_K0H[2]         = 0.06;      soilParams[idx].soil_K0H[3]         = 0.04;      soilParams[idx].soil_K0H[4]         = 0.04;
    soilParams[idx].water_table_change_limit = 0.1;  // Maximum daily water table change (m)

    // --- Texture 60 (Sandy Clay Loam) ---
    idx = 5;
    soilParams[idx].mytexture           = 60;
    // -- Scalar parameters (Use actual BTL default values here!) --
    soilParams[idx].pore_index          = 0.01;
    soilParams[idx].max_z               = 2.0;
    soilParams[idx].MaxiGs              = 0.005;
    soilParams[idx].wilting_pt          = 0.15;
    // -- Layered parameters (Values from init_soil.c case 6) --
    soilParams[idx].soil_b[0]           = 4.0;      soilParams[idx].soil_b[1]           = 4.2;      soilParams[idx].soil_b[2]           = 4.4;      soilParams[idx].soil_b[3]           = 4.6;      soilParams[idx].soil_b[4]           = 4.8;
    soilParams[idx].suction_head[0]     = 0.28;     soilParams[idx].suction_head[1]     = 0.29;     soilParams[idx].suction_head[2]     = 0.30;     soilParams[idx].suction_head[3]     = 0.31;     soilParams[idx].suction_head[4]     = 0.33;
    soilParams[idx].soil_K0[0]          = 0.10368;  soilParams[idx].soil_K0[1]          = 0.093312; soilParams[idx].soil_K0[2]          = 0.082944; soilParams[idx].soil_K0[3]          = 0.062208; soilParams[idx].soil_K0[4]          = 0.020736;
    // field_cap (theta_vfc) - now layered
    soilParams[idx].field_cap[0]        = 0.26;     soilParams[idx].field_cap[1]        = 0.26;     soilParams[idx].field_cap[2]        = 0.26;     soilParams[idx].field_cap[3]        = 0.26;     soilParams[idx].field_cap[4]        = 0.26;
    // porosity (fei) - now layered
    soilParams[idx].porosity[0]         = 0.398;    soilParams[idx].porosity[1]         = 0.398;    soilParams[idx].porosity[2]         = 0.398;    soilParams[idx].porosity[3]         = 0.398;    soilParams[idx].porosity[4]         = 0.398;
    for(int i=0; i<num_layers; ++i) soilParams[idx].soil_K0H[i] = 0.24;// CHECK BTL DEFAULT for Sandy Clay Loam!
    soilParams[idx].water_table_change_limit = 0.05;  // Maximum daily water table change (m)

    // --- Texture 70 (Clay Loam) ---
    idx = 6;
    soilParams[idx].mytexture           = 70;
    // -- Scalar parameters (Use actual BTL default values here!) --
    soilParams[idx].pore_index          = 0.008;
    soilParams[idx].max_z               = 2.0;
    soilParams[idx].MaxiGs              = 0.008;
    soilParams[idx].wilting_pt          = 0.20;
    // -- Layered parameters (Values from init_soil.c case 7) --
    soilParams[idx].soil_b[0]           = 5.2;      soilParams[idx].soil_b[1]           = 5.4;      soilParams[idx].soil_b[2]           = 5.6;      soilParams[idx].soil_b[3]           = 5.8;      soilParams[idx].soil_b[4]           = 6.0;
    soilParams[idx].suction_head[0]     = 0.26;     soilParams[idx].suction_head[1]     = 0.27;     soilParams[idx].suction_head[2]     = 0.28;     soilParams[idx].suction_head[3]     = 0.29;     soilParams[idx].suction_head[4]     = 0.31;
    soilParams[idx].soil_K0[0]          = 0.055296; soilParams[idx].soil_K0[1]          = 0.050112; soilParams[idx].soil_K0[2]          = 0.044064; soilParams[idx].soil_K0[3]          = 0.032832; soilParams[idx].soil_K0[4]          = 0.011232;
    // field_cap (theta_vfc) - now layered
    // soilParams[idx].field_cap[0]        = 0.32;     soilParams[idx].field_cap[1]        = 0.32;     soilParams[idx].field_cap[2]        = 0.32;     soilParams[idx].field_cap[3]        = 0.32;     soilParams[idx].field_cap[4]        = 0.32;
    soilParams[idx].field_cap[0]        = 0.26;     soilParams[idx].field_cap[1]        = 0.28;     soilParams[idx].field_cap[2]        = 0.30;     soilParams[idx].field_cap[3]        = 0.35;     soilParams[idx].field_cap[4]        = 0.35;
    // porosity (fei) - now layered
    // soilParams[idx].porosity[0]         = 0.464;    soilParams[idx].porosity[1]         = 0.464;    soilParams[idx].porosity[2]         = 0.464;    soilParams[idx].porosity[3]         = 0.464;    soilParams[idx].porosity[4]         = 0.464;
    soilParams[idx].porosity[0]         = 0.400;    soilParams[idx].porosity[1]         = 0.400;    soilParams[idx].porosity[2]         = 0.391;    soilParams[idx].porosity[3]         = 0.421;    soilParams[idx].porosity[4]         = 0.421;
    soilParams[idx].soil_K0H[0]         = 0.055;    soilParams[idx].soil_K0H[1]         = 0.050;     soilParams[idx].soil_K0H[2]         = 0.044;      soilParams[idx].soil_K0H[3]         = 0.032;      soilParams[idx].soil_K0H[4]         = 0.011;
    soilParams[idx].water_table_change_limit = 0.05;  // Maximum daily water table change (m)

    // --- Texture 80 (Silty Clay Loam) ---
    idx = 7;
    soilParams[idx].mytexture           = 80;
    // -- Scalar parameters (Use actual BTL default values here!) --
    soilParams[idx].pore_index          = 0.005;
    soilParams[idx].max_z               = 2.0;
    soilParams[idx].MaxiGs              = 0.01;
    soilParams[idx].wilting_pt          = 0.32;
    // -- Layered parameters (Values from init_soil.c case 7) --
    soilParams[idx].soil_b[0]           = 6.6;      soilParams[idx].soil_b[1]           = 6.8;      soilParams[idx].soil_b[2]           = 7.0;      soilParams[idx].soil_b[3]           = 7.2;      soilParams[idx].soil_b[4]           = 7.4;
    soilParams[idx].suction_head[0]     = 0.33;     soilParams[idx].suction_head[1]     = 0.34;     soilParams[idx].suction_head[2]     = 0.35;     soilParams[idx].suction_head[3]     = 0.36;     soilParams[idx].suction_head[4]     = 0.38;
    soilParams[idx].soil_K0[0]          = 0.036288; soilParams[idx].soil_K0[1]          = 0.032832; soilParams[idx].soil_K0[2]          = 0.029376; soilParams[idx].soil_K0[3]          = 0.0217728; soilParams[idx].soil_K0[4]          = 0.0072576;
    // field_cap (theta_vfc) - now layered
    soilParams[idx].field_cap[0]        = 0.37;     soilParams[idx].field_cap[1]        = 0.37;     soilParams[idx].field_cap[2]        = 0.37;     soilParams[idx].field_cap[3]        = 0.37;     soilParams[idx].field_cap[4]        = 0.37;
    // porosity (fei) - now layered
    soilParams[idx].porosity[0]         = 0.471;    soilParams[idx].porosity[1]         = 0.471;    soilParams[idx].porosity[2]         = 0.471;    soilParams[idx].porosity[3]         = 0.471;    soilParams[idx].porosity[4]         = 0.471;
        for(int i=0; i<num_layers; ++i) soilParams[idx].soil_K0H[i] = 10.0;// CHECK BTL DEFAULT for Silty Clay Loam!
    soilParams[idx].water_table_change_limit = 0.05;  // Maximum daily water table change (m)

    // --- Texture 90 (Sandy Clay) ---
    idx = 8;
    soilParams[idx].mytexture           = 90;
    // -- Scalar parameters (Use actual BTL default values here!) --
    soilParams[idx].pore_index          = 0.006;
    soilParams[idx].max_z               = 2.0;
    soilParams[idx].MaxiGs              = 0.01;
    soilParams[idx].wilting_pt          = 0.15;
    // -- Layered parameters (Values from init_soil.c case 9) --
    soilParams[idx].soil_b[0]           = 6.0;      soilParams[idx].soil_b[1]           = 6.2;      soilParams[idx].soil_b[2]           = 6.4;      soilParams[idx].soil_b[3]           = 6.6;      soilParams[idx].soil_b[4]           = 6.8;
    soilParams[idx].suction_head[0]     = 0.29;     soilParams[idx].suction_head[1]     = 0.30;     soilParams[idx].suction_head[2]     = 0.31;     soilParams[idx].suction_head[3]     = 0.32;     soilParams[idx].suction_head[4]     = 0.34;
    soilParams[idx].soil_K0[0]          = 0.028512; soilParams[idx].soil_K0[1]          = 0.025920; soilParams[idx].soil_K0[2]          = 0.0228096;soilParams[idx].soil_K0[3]          = 0.0171072;soilParams[idx].soil_K0[4]          = 0.0057024;
    // field_cap (theta_vfc) - now layered
    soilParams[idx].field_cap[0]        = 0.34;     soilParams[idx].field_cap[1]        = 0.34;     soilParams[idx].field_cap[2]        = 0.34;     soilParams[idx].field_cap[3]        = 0.34;     soilParams[idx].field_cap[4]        = 0.34;
    // porosity (fei) - now layered
    soilParams[idx].porosity[0]         = 0.430;    soilParams[idx].porosity[1]         = 0.430;    soilParams[idx].porosity[2]         = 0.430;    soilParams[idx].porosity[3]         = 0.430;    soilParams[idx].porosity[4]         = 0.430;
    for(int i=0; i<num_layers; ++i) soilParams[idx].soil_K0H[i] = 10.0;// CHECK BTL DEFAULT for Sandy Clay!
    soilParams[idx].water_table_change_limit = 0.05;  // Maximum daily water table change (m)

    // --- Texture 100 (Silty Clay) ---
    idx = 9;
    soilParams[idx].mytexture           = 100;
    // -- Scalar parameters (Use actual BTL default values here!) --
    soilParams[idx].pore_index          = 0.005;
    soilParams[idx].max_z               = 2.0;
    soilParams[idx].MaxiGs              = 0.01;
    soilParams[idx].wilting_pt          = 0.25;
    // -- Layered parameters (Values from init_soil.c case 10) --
    soilParams[idx].soil_b[0]           = 7.9;      soilParams[idx].soil_b[1]           = 8.1;      soilParams[idx].soil_b[2]           = 8.3;      soilParams[idx].soil_b[3]           = 8.5;      soilParams[idx].soil_b[4]           = 8.7;
    soilParams[idx].suction_head[0]     = 0.34;     soilParams[idx].suction_head[1]     = 0.35;     soilParams[idx].suction_head[2]     = 0.36;     soilParams[idx].suction_head[3]     = 0.37;     soilParams[idx].suction_head[4]     = 0.39;
    soilParams[idx].soil_K0[0]          = 0.021600; soilParams[idx].soil_K0[1]          = 0.019440; soilParams[idx].soil_K0[2]          = 0.017280; soilParams[idx].soil_K0[3]          = 0.012960; soilParams[idx].soil_K0[4]          = 0.004320;
    // field_cap (theta_vfc) - now layered
    soilParams[idx].field_cap[0]        = 0.39;     soilParams[idx].field_cap[1]        = 0.39;     soilParams[idx].field_cap[2]        = 0.39;     soilParams[idx].field_cap[3]        = 0.39;     soilParams[idx].field_cap[4]        = 0.39;
    // porosity (fei) - now layered
    soilParams[idx].porosity[0]         = 0.479;    soilParams[idx].porosity[1]         = 0.479;    soilParams[idx].porosity[2]         = 0.479;    soilParams[idx].porosity[3]         = 0.479;    soilParams[idx].porosity[4]         = 0.479;
    for(int i=0; i<num_layers; ++i) soilParams[idx].soil_K0H[i] = 10.0;// CHECK BTL DEFAULT for Silty Clay!
    soilParams[idx].water_table_change_limit = 0.05;  // Maximum daily water table change (m)

    // --- Texture 110 (Clay) ---
    idx = 10;
    soilParams[idx].mytexture           = 110;
    // -- Scalar parameters (Use actual BTL default values here!) --
    soilParams[idx].pore_index          = 0.005;
    soilParams[idx].max_z               = 2.0;
    soilParams[idx].MaxiGs              = 0.01;
    soilParams[idx].wilting_pt		    = 0.27;
    // -- Layered parameters (Using Clay - case 11 - as default from init_soil.c) --
    soilParams[idx].soil_b[0]			= 7.6;		soilParams[idx].soil_b[1]			= 7.8;		soilParams[idx].soil_b[2]			= 8.0;		soilParams[idx].soil_b[3]			= 8.2;		soilParams[idx].soil_b[4]			= 8.4;
    soilParams[idx].suction_head[0]	    = 0.37;		soilParams[idx].suction_head[1]	    = 0.38;		soilParams[idx].suction_head[2]	    = 0.39;		soilParams[idx].suction_head[3]	    = 0.40;		soilParams[idx].suction_head[4]	    = 0.42;
    soilParams[idx].soil_K0[0]		    = 0.014688;	soilParams[idx].soil_K0[1]		    = 0.0132192;soilParams[idx].soil_K0[2]		    = 0.0117504;soilParams[idx].soil_K0[3]		    = 0.0088128;soilParams[idx].soil_K0[4]		    = 0.0029376;
    // field_cap (theta_vfc) - now layered
    soilParams[idx].field_cap[0]        = 0.40;     soilParams[idx].field_cap[1]        = 0.40;     soilParams[idx].field_cap[2]        = 0.40;     soilParams[idx].field_cap[3]        = 0.40;     soilParams[idx].field_cap[4]        = 0.40;
    // porosity (fei) - now layered
    soilParams[idx].porosity[0]         = 0.475;    soilParams[idx].porosity[1]         = 0.475;    soilParams[idx].porosity[2]         = 0.475;    soilParams[idx].porosity[3]         = 0.475;    soilParams[idx].porosity[4]         = 0.475;
    for(int i=0; i<num_layers; ++i) soilParams[idx].soil_K0H[i] = 10.0;// CHECK BTL DEFAULT for Clay!

    // --- Texture 120 (Peat/Other) ---
    idx = 11;
    soilParams[idx].mytexture		    = 120;
    // -- Scalar parameters (Use actual BTL default values here!) --
    soilParams[idx].pore_index		    = 0.0;
    soilParams[idx].max_z			    = 2.0;
    soilParams[idx].MaxiGs			    = 0.01;
    soilParams[idx].wilting_pt		    = 0.27;
    // -- Layered parameters (Using Clay - case 11 - as default from init_soil.c) --
    soilParams[idx].soil_b[0]			= 7.6;		soilParams[idx].soil_b[1]			= 7.8;		soilParams[idx].soil_b[2]			= 8.0;		soilParams[idx].soil_b[3]			= 8.2;		soilParams[idx].soil_b[4]			= 8.4;
    soilParams[idx].suction_head[0]	    = 0.37;		soilParams[idx].suction_head[1]	    = 0.38;		soilParams[idx].suction_head[2]	    = 0.39;		soilParams[idx].suction_head[3]	    = 0.40;		soilParams[idx].suction_head[4]	    = 0.42;
    soilParams[idx].soil_K0[0]		    = 0.014688;	soilParams[idx].soil_K0[1]		    = 0.0132192;soilParams[idx].soil_K0[2]		    = 0.0117504;soilParams[idx].soil_K0[3]		    = 0.0088128;soilParams[idx].soil_K0[4]		    = 0.0029376;
    // field_cap (theta_vfc) - now layered
    soilParams[idx].field_cap[0]        = 0.40;     soilParams[idx].field_cap[1]        = 0.40;     soilParams[idx].field_cap[2]        = 0.40;     soilParams[idx].field_cap[3]        = 0.40;     soilParams[idx].field_cap[4]        = 0.40;
    // porosity (fei) - now layered
    soilParams[idx].porosity[0]         = 0.475;    soilParams[idx].porosity[1]         = 0.475;    soilParams[idx].porosity[2]         = 0.475;    soilParams[idx].porosity[3]         = 0.475;    soilParams[idx].porosity[4]         = 0.475;
    for(int i=0; i<num_layers; ++i) soilParams[idx].soil_K0H[i] = 10.0;// CHECK BTL DEFAULT for Peat!



    //set biology parameters

    BH_SubParams2->iMinConifer=1;
    BH_SubParams2->iMaxConifer=1;
    BH_SubParams2->iMinDecidious=2;
    BH_SubParams2->iMaxDecidious=2;
    BH_SubParams2->iMinMixed=3;
    BH_SubParams2->iMaxMixed=3;
    BH_SubParams2->iMinAgricultural=4;
    BH_SubParams2->iMaxAgricultural=4;
    BH_SubParams2->iMinOpen=6;
    BH_SubParams2->iMaxOpen=6;
    BH_SubParams2->iMinUrban=7;
    BH_SubParams2->iMaxUrban=7;
    BH_SubParams2->iMinWater=0;
    BH_SubParams2->iMaxWater=0;



    printf("StartDay:%d\n",BH_SubParams1->iDayStart);
    printf("EndDay:%d\n",BH_SubParams1->iDayEnd);
    printf("iNumLines:%d\n",BH_SubParams1->iNumLines);
    printf("iNumPixels:%d\n",BH_SubParams1->iNumPixels);

    //***********************************************end of input parameters **********************************************

    //***********************************************start of output parameters **********************************************

    strcpy(BH_SubParams1a->szOutDirName,ss15);

    strcpy(BH_SubParams1a->szOutFileNameClimateRAD_r,ss15);
    strcpy(BH_SubParams1a->szOutFileNameClimateRAD_f,ss15);
    strcpy(BH_SubParams1a->szOutFileNameClimateTi,ss15);
    strcpy(BH_SubParams1a->szOutFileNameClimateTm,ss15);
    strcpy(BH_SubParams1a->szOutFileNameClimateTmean,ss15);      //自行添加
    strcpy(BH_SubParams1a->szOutFileNameClimateDew,ss15);
    strcpy(BH_SubParams1a->szOutFileNameClimateWind,ss15);
    strcpy(BH_SubParams1a->szOutFileNameClimatePrec,ss15);

    strcat(BH_SubParams1a->szOutFileNameClimateRAD_r,"climate/climate_Rad_r.bin");
    strcat(BH_SubParams1a->szOutFileNameClimateRAD_f,"climate/climate_Rad_f.bin");
    strcat(BH_SubParams1a->szOutFileNameClimateTi,"climate/climate_Ti.bin");
    strcat(BH_SubParams1a->szOutFileNameClimateTm,"climate/climate_Tm.bin");
    strcat(BH_SubParams1a->szOutFileNameClimateTmean,"climate/climate_Tmean.bin"); //自行添加
    strcat(BH_SubParams1a->szOutFileNameClimatePrec,"climate/climate_Prec.bin");
    strcat(BH_SubParams1a->szOutFileNameClimateDew,"climate/climate_Dew.bin");
    strcat(BH_SubParams1a->szOutFileNameClimateWind,"climate/climate_Wind.bin");

    // printf("Outfile:%s\n",BH_SubParams1a->szOutFileNameClimateRAD_r);
    strcpy(BH_SubParams1a->szOutFileNameWaterIn,ss15);      //water infiltration
    strcpy(BH_SubParams1a->szOutFileNameSoilTemp,ss15); // 2nov2006
    strcpy(BH_SubParams1a->szOutFileNameNitrogen,ss15);
    strcpy(BH_SubParams1a->szOutFileNamePool1,ss15);  // to avoid confusion, szOutFileNameCarbonPool1 renamed as szOutFileNamePool1
    strcpy(BH_SubParams1a->szOutFileNamePool2,ss15);  // szOutFileNameSoilTemp is diff from szOutFileNameSoilInitTemp
    strcpy(BH_SubParams1a->szOutFileNamePool3,ss15);
    strcpy(BH_SubParams1a->szOutFileNamePool4,ss15);
    strcpy(BH_SubParams1a->szOutFileNamePool5,ss15);
    strcpy(BH_SubParams1a->szOutFileNamePool6,ss15);
    strcpy(BH_SubParams1a->szOutFileNamePool7,ss15);
    strcpy(BH_SubParams1a->szOutFileNamePool8,ss15);
    strcpy(BH_SubParams1a->szOutFileNamePool9,ss15);
    strcpy(BH_SubParams1a->szOutFileNameB_Pool1,ss15);
    strcpy(BH_SubParams1a->szOutFileNameB_Pool2,ss15);
    strcpy(BH_SubParams1a->szOutFileNameB_Pool3,ss15);
    strcpy(BH_SubParams1a->szOutFileNameB_Pool4,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCNcd,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCNssd,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCNsmd,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCNfsd,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCNfmd,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCNsm,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCNm,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCNs,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCNp,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCNw,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCNfr,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCNl,ss15);
    strcpy(BH_SubParams1a->szOutFileNameST_Ly1,ss15);
    strcpy(BH_SubParams1a->szOutFileNameST_Ly2,ss15);
    strcpy(BH_SubParams1a->szOutFileNameST_Ly3,ss15);
    strcpy(BH_SubParams1a->szOutFileNameST_Ly4,ss15);
    strcpy(BH_SubParams1a->szOutFileNameST_Ly5,ss15);
    strcpy(BH_SubParams1a->szOutFileNameST_Ly6,ss15);
    strcpy(BH_SubParams1a->szOutFileNameSoilMaxDepthZ,ss15);
    strcpy(BH_SubParams1a->szOutFileNameSoilK0DecayM,ss15);    //Hydrolic conductivity decay rate
    strcpy(BH_SubParams1a->szOutFileNameSoilB,ss15);			// B value
    strcpy(BH_SubParams1a->szOutFileNameSoilSatSuction,ss15);	// suction at saturation
    strcpy(BH_SubParams1a->szOutFileNameSoilSatKv,ss15);        // saturated hydrolic conductivity
    strcpy(BH_SubParams1a->szOutFileNameSoilSatKh,ss15);        // saturated hydrolic conductivity
    strcpy(BH_SubParams1a->szOutFileNameCanopyET,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCanopyEvaporation,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCanopyIntercepted,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCanopyLitterEvaporation,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCanopyMossTransp,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCanopySoilEvaporation,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCanopyTranspSat,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCanopyTranspUnsat,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCanopyUT,ss15);
    strcpy(BH_SubParams1a->szOutFileNameCanopyStomata,ss15);
    strcpy(BH_SubParams1a->szOutFileNameSensibleHeatFlux,ss15);
    strcpy(BH_SubParams1a->szOutFileNameLatentHeatFlux,ss15);
    strcpy(BH_SubParams1a->szOutFileNameNRFlux,ss15);
    strcpy(BH_SubParams1a->szOutFileNameGPP,ss15);
    strcpy(BH_SubParams1a->szOutFileNameNPP,ss15);
    strcpy(BH_SubParams1a->szOutFileNameNEP,ss15);
    strcpy(BH_SubParams1a->szOutFileNameRa,ss15);
    strcpy(BH_SubParams1a->szOutFileNameRh,ss15);
    strcpy(BH_SubParams1a->szOutFileNameRunoffTotal,ss15);
    strcpy(BH_SubParams1a->szOutFileNameRunoffBaseflow,ss15);
    strcpy(BH_SubParams1a->szOutFileNameRunoffTotalInflow,ss15);
    strcpy(BH_SubParams1a->szOutFileNameRunoffTotalOutflow,ss15);
    strcpy(BH_SubParams1a->szOutFileNameSoilCapillaryRise,ss15);
    strcpy(BH_SubParams1a->szOutFileNameSoilPercolation,ss15);
    strcpy(BH_SubParams1a->szOutFileNameSoilSatDeficit,ss15);
    strcpy(BH_SubParams1a->szOutFileNameSoilUnsatStorage,ss15);
    strcpy(BH_SubParams1a->szOutFileNameSoilthetam,ss15);
    strcpy(BH_SubParams1a->szOutFileNameSoilWaterTable,ss15);
    strcpy(BH_SubParams1a->szOutFileNameSoilPondWater,ss15);
    strcpy(BH_SubParams1a->szOutFileNameSnowdepth,ss15);
    strcpy(BH_SubParams1a->szOutFileNameSnowdensity,ss15);
    strcpy(BH_SubParams1a->szOutFileNameSnowswe,ss15);
    strcpy(BH_SubParams1a->szOutFileNameET,ss15);

    strcat(BH_SubParams1a->szOutFileNamePool1,"soilcarbon/Ccd.bin");  // to avoid confusion, szOutFileNameCarbonPool1 renamed as szOutFileNamePool1
    strcat(BH_SubParams1a->szOutFileNamePool2,"soilcarbon/Cssd.bin");  // szOutFileNameSoilTemp is diff from szOutFileNameSoilInitTemp
    strcat(BH_SubParams1a->szOutFileNamePool3,"soilcarbon/Csmd.bin");
    strcat(BH_SubParams1a->szOutFileNamePool4,"soilcarbon/Cfmd.bin");
    strcat(BH_SubParams1a->szOutFileNamePool5,"soilcarbon/Cfsd.bin");
    strcat(BH_SubParams1a->szOutFileNamePool6,"soilcarbon/Cm.bin");
    strcat(BH_SubParams1a->szOutFileNamePool7,"soilcarbon/Cs.bin");
    strcat(BH_SubParams1a->szOutFileNamePool8,"soilcarbon/Cp.bin");
    strcat(BH_SubParams1a->szOutFileNamePool9,"soilcarbon/Csm.bin");
    strcat(BH_SubParams1a->szOutFileNameB_Pool1,"soilcarbon/Bio_Wood-.bin");
    strcat(BH_SubParams1a->szOutFileNameB_Pool2,"soilcarbon/Bio_C.Root-.bin");
    strcat(BH_SubParams1a->szOutFileNameB_Pool3,"soilcarbon/Bio_Leafs-.bin");
    strcat(BH_SubParams1a->szOutFileNameB_Pool4,"soilcarbon/Bio_F.Root-.bin");
    strcat(BH_SubParams1a->szOutFileNameCNcd,"cn_Ratio/cncd-.bin");
    strcat(BH_SubParams1a->szOutFileNameCNssd,"cn_Ratio/cnssd-.bin");
    strcat(BH_SubParams1a->szOutFileNameCNsmd,"cn_Ratio/cnsmd-.bin");
    strcat(BH_SubParams1a->szOutFileNameCNfsd,"cn_Ratio/cnfsd-.bin");
    strcat(BH_SubParams1a->szOutFileNameCNfmd,"cn_Ratio/cnfmd-.bin");
    strcat(BH_SubParams1a->szOutFileNameCNsm,"cn_Ratio/cnsm-.bin");
    strcat(BH_SubParams1a->szOutFileNameCNm,"cn_Ratio/cnm-.bin");
    strcat(BH_SubParams1a->szOutFileNameCNs,"cn_Ratio/cns-.bin");
    strcat(BH_SubParams1a->szOutFileNameCNp,"cn_Ratio/cnp-.bin");
    strcat(BH_SubParams1a->szOutFileNameCNw,"cn_Ratio/cnw-.bin");
    strcat(BH_SubParams1a->szOutFileNameCNfr,"cn_Ratio/cnfr-.bin");
    strcat(BH_SubParams1a->szOutFileNameCNl,"cn_Ratio/cnl-.bin");
    strcat(BH_SubParams1a->szOutFileNameNitrogen,"cn_Ratio/Nitrogen-.bin");

    strcat(BH_SubParams1a->szOutFileNameST_Ly1,"soiltemp/ST_Lyr1_.bin");
    strcat(BH_SubParams1a->szOutFileNameST_Ly2,"soiltemp/ST_Lyr2_.bin");
    strcat(BH_SubParams1a->szOutFileNameST_Ly3,"soiltemp/ST_Lyr3_.bin");
    strcat(BH_SubParams1a->szOutFileNameST_Ly4,"soiltemp/ST_Lyr4_.bin");
    strcat(BH_SubParams1a->szOutFileNameST_Ly5,"soiltemp/ST_Lyr5_.bin");
    strcat(BH_SubParams1a->szOutFileNameST_Ly6,"soiltemp/ST_Lyr6_.bin");
    strcat(BH_SubParams1a->szOutFileNameSoilTemp,"soiltemp/Surface_Temp-.bin"); // 2nov2006

    strcat(BH_SubParams1a->szOutFileNameSoilMaxDepthZ,"soilwaterflux/Soil_MaxDepthZ.bin");
    strcat(BH_SubParams1a->szOutFileNameSoilK0DecayM,"soilwaterflux/Soil_K0DecayM.bin");    //Hydrolic conductivity decay rate
    strcat(BH_SubParams1a->szOutFileNameSoilB,"soilwaterflux/Soil_B.bin");			// B value
    strcat(BH_SubParams1a->szOutFileNameSoilSatSuction,"soilwaterflux/Soil_SatSuction.bin");	// suction at saturation
    strcat(BH_SubParams1a->szOutFileNameSoilSatKv,"soilwaterflux/Soil_SatKv.bin");        // saturated hydrolic conductivity
    strcat(BH_SubParams1a->szOutFileNameSoilSatKh,"soilwaterflux/Soil_SatKh.bin");        // saturated hydrolic conductivity

    strcat(BH_SubParams1a->szOutFileNameSoilCapillaryRise,"soilwaterflux/Soil_CapillaryRise.bin");
    strcat(BH_SubParams1a->szOutFileNameSoilPercolation,"soilwaterflux/Soil_Percolation.bin");
    strcat(BH_SubParams1a->szOutFileNameSoilSatDeficit,"soilwaterflux/Soil_SatDeficit.bin");
    strcat(BH_SubParams1a->szOutFileNameSoilUnsatStorage,"soilwaterflux/Soil_UnsatStorage.bin");
    strcat(BH_SubParams1a->szOutFileNameSoilthetam,"soilwaterflux/Soil_thetam.bin");
    strcat(BH_SubParams1a->szOutFileNameSoilWaterTable,"soilwaterflux/Soil_WaterTable.bin");
    strcat(BH_SubParams1a->szOutFileNameSoilPondWater,"soilwaterflux/PondWater-.bin");
    strcat(BH_SubParams1a->szOutFileNameWaterIn,"soilwaterflux/Climate_WaterIn.bin");      //water infiltration
    strcat(BH_SubParams1a->szOutFileNameRunoffTotal,"soilwaterflux/Runoff_Total.bin");
    strcat(BH_SubParams1a->szOutFileNameRunoffBaseflow,"soilwaterflux/Runoff_Baseflow.bin");
    strcat(BH_SubParams1a->szOutFileNameRunoffTotalInflow,"soilwaterflux/Runoff_TotalInflow.bin");
    strcat(BH_SubParams1a->szOutFileNameRunoffTotalOutflow,"soilwaterflux/Runoff_TotalOutflow.bin");

    strcat(BH_SubParams1a->szOutFileNameCanopyET,"canopywaterflux/ET.bin");
    strcat(BH_SubParams1a->szOutFileNameCanopyEvaporation,"canopywaterflux/Canopy_Evap.bin");
    strcat(BH_SubParams1a->szOutFileNameCanopyIntercepted,"canopywaterflux/Canopy_Intercepted.bin");
    strcat(BH_SubParams1a->szOutFileNameCanopyLitterEvaporation,"canopywaterflux/Canopy_LitterEvap.bin");
    strcat(BH_SubParams1a->szOutFileNameCanopyMossTransp,"canopywaterflux/Canopy_MossTransp.bin");
    strcat(BH_SubParams1a->szOutFileNameCanopySoilEvaporation,"canopywaterflux/Canopy_SoilEvap.bin");
    strcat(BH_SubParams1a->szOutFileNameCanopyTranspSat,"canopywaterflux/Canopy_TranspSat.bin");
    strcat(BH_SubParams1a->szOutFileNameCanopyTranspUnsat,"canopywaterflux/Canopy_TranspUnsat.bin");
    strcat(BH_SubParams1a->szOutFileNameCanopyUT,"canopywaterflux/UT.bin");

    strcat(BH_SubParams1a->szOutFileNameSensibleHeatFlux,"energyflux/SensibleHeatFlux.bin");
    strcat(BH_SubParams1a->szOutFileNameLatentHeatFlux,"energyflux/LatentHeatFlux.bin");
    strcat(BH_SubParams1a->szOutFileNameNRFlux,"energyflux/NR.bin");

    strcat(BH_SubParams1a->szOutFileNameGPP,"carbonflux/Daily_GPP.bin");
    strcat(BH_SubParams1a->szOutFileNameNPP,"carbonflux/Daily_NPP.bin");
    strcat(BH_SubParams1a->szOutFileNameNEP,"carbonflux/Daily_NEP.bin");
    strcat(BH_SubParams1a->szOutFileNameRa,"carbonflux/Daily_Ra.bin");
    strcat(BH_SubParams1a->szOutFileNameRh,"carbonflux/Daily_Rh.bin");

    strcat(BH_SubParams1a->szOutFileNameSnowdepth,"snow/Climate_SnowDepth.bin");
    strcat(BH_SubParams1a->szOutFileNameSnowdensity,"snow/Climate_SnowDensity.bin");
    strcat(BH_SubParams1a->szOutFileNameSnowswe,"snow/Climate_SnowSWE.bin");

    //careful
    strcat(BH_SubParams1a->szOutFileNameET,"energyflux/XTTET.bin");
    strcat(BH_SubParams1a->szOutFileNameCanopyStomata,"energyflux/XTTstoma.bin");


    //printf("%s",BH_SubParams1a->szOutFileNameClimateRAD_r);
//***********************************************end of output parameters **********************************************


}
