
#include "stdafx.h"
#include "BepsHydrScience.h"
#include "string.h"
#include "malloc.h"
#include "stdio.h"
#include "math.h"
void BepsHydrCalculate(BH_SubParams1_t* BH_SubParams1,BH_SubParams1a_t* BH_SubParams1a,BH_SubParams2_t* BH_SubParams2)
{

    char
    szClimateDailyLAI[MAX_PATH],
                      szClimateDailyFileNameRAD_r[MAX_PATH],
                      szClimateDailyFileNameRAD_f[MAX_PATH],
                      szClimateDailyFileNameTI[MAX_PATH],
                      szClimateDailyFileNameTM[MAX_PATH],
                      szClimateDailyFileNamePREC[MAX_PATH],
                      szClimateDailyFileNameDEW[MAX_PATH],
                      szClimateDailyFileNameWIND[MAX_PATH],
                      szCanopyDailyFileNameET[MAX_PATH],

                      szCanopyDailyFileNameEvaporation[MAX_PATH],
                      szCanopyDailyFileNameTranspUnsat[MAX_PATH],
                      szCanopyDailyFileNameTranspSat[MAX_PATH],
                      szCanopyDailyFileNameIntercepted[MAX_PATH],
                      szCanopyDailyFileNameLitterEvaporation[MAX_PATH],
                      szCanopyDailyFileNameMossTransp[MAX_PATH],
                      szCanopyDailyFileNameSoilEvaporation[MAX_PATH],
                      szCanopyDailyFileNameUT[MAX_PATH],
                      szCanopyDailyFileNameStomata[MAX_PATH],

                      szEnergyDailyFileNameNRFlux[MAX_PATH],
                      szEnergyDailyFileNameSensibleHeatFlux[MAX_PATH],
                      szEnergyDailyFileNameLatentHeatFlux[MAX_PATH],

                      SoilSatSuctionFileName[MAX_PATH],
                      SoilSatKvFileName[MAX_PATH],
                      SoilSatKhFileName[MAX_PATH],
                      SoilK0DecayMFileName[MAX_PATH],

                      szGPPDailyFileName[MAX_PATH],
                      szNPPDailyFileName[MAX_PATH],
                      szNEPDailyFileName[MAX_PATH],
                      szRaDailyFileName[MAX_PATH],
                      szRhDailyFileName[MAX_PATH],


                      szRunoffDailyFileNameTotal[MAX_PATH],
                      szRunoffDailyFileNameBaseflow[MAX_PATH],
                      szRunoffDailyFileNameTotalInflow[MAX_PATH],
                      szRunoffDailyFileNameTotalOutflow[MAX_PATH],


                      szPrevDaySoilSatDeficitFileName[MAX_PATH],
                      szPrevDaySoilUnsatStorageFileName[MAX_PATH],

                      szPrevDaySoilWaterTableFileName[MAX_PATH],   //Water table
                      szPrevDaySoilTempFileName[MAX_PATH],   // 2nov2006
                      szPrevDayNitrogenFileName[MAX_PATH],
                      szPrevDayPool1FileName[MAX_PATH],
                      szPrevDayPool2FileName[MAX_PATH],
                      szPrevDayPool3FileName[MAX_PATH],
                      szPrevDayPool4FileName[MAX_PATH],  //pool
                      szPrevDayPool5FileName[MAX_PATH],
                      szPrevDayPool6FileName[MAX_PATH],
                      szPrevDayPool7FileName[MAX_PATH],
                      szPrevDayPool8FileName[MAX_PATH],
                      szPrevDayPool9FileName[MAX_PATH],
                      szPrevDayCNcdFileName[MAX_PATH],
                      szPrevDayCNssdFileName[MAX_PATH],
                      szPrevDayCNsmdFileName[MAX_PATH],
                      szPrevDayCNfsdFileName[MAX_PATH],
                      szPrevDayCNfmdFileName[MAX_PATH],
                      szPrevDayCNsmFileName[MAX_PATH],
                      szPrevDayCNmFileName[MAX_PATH],
                      szPrevDayCNsFileName[MAX_PATH],
                      szPrevDayCNpFileName[MAX_PATH],
                      szPrevDayCNwFileName[MAX_PATH],
                      szPrevDayCNfrFileName[MAX_PATH],
                      szPrevDayCNlFileName[MAX_PATH],
                      szPrevDayST_Ly1FileName[MAX_PATH],
                      szPrevDayST_Ly2FileName[MAX_PATH],
                      szPrevDayST_Ly3FileName[MAX_PATH],
                      szPrevDayST_Ly4FileName[MAX_PATH],
                      szPrevDayST_Ly5FileName[MAX_PATH],
                      szPrevDayST_Ly6FileName[MAX_PATH],
                      szPrevDayBiomassPool1FileName[MAX_PATH],
                      szPrevDayBiomassPool2FileName[MAX_PATH],
                      szPrevDayBiomassPool3FileName[MAX_PATH],
                      szPrevDayBiomassPool4FileName[MAX_PATH],
                      szPrevDaySoilPondWaterFileName[MAX_PATH],   //pond
                      szPrevDaySnowdepthFileName[MAX_PATH],
                      szPrevDaySWEFileName[MAX_PATH],
                      szPrevDaySnowdensityFileName[MAX_PATH],
                      szCurrDaySoilPercolationFileName[MAX_PATH],
                      szCurrDaySoilCapillaryRiseFileName[MAX_PATH],
                      szCurrDaySoilWaterTableFileName[MAX_PATH],
                      szCurrDaySoilTempFileName[MAX_PATH],/* 2nov2006*/
                      szCurrDayNitrogenFileName[MAX_PATH],
                      szCurrDayCNcdFileName[MAX_PATH],
                      szCurrDayCNssdFileName[MAX_PATH],
                      szCurrDayCNsmdFileName[MAX_PATH],
                      szCurrDayCNfsdFileName[MAX_PATH],
                      szCurrDayCNfmdFileName[MAX_PATH],
                      szCurrDayCNsmFileName[MAX_PATH],
                      szCurrDayCNmFileName[MAX_PATH],
                      szCurrDayCNsFileName[MAX_PATH],
                      szCurrDayCNpFileName[MAX_PATH],
                      szCurrDayCNwFileName[MAX_PATH],
                      szCurrDayCNfrFileName[MAX_PATH],
                      szCurrDayCNlFileName[MAX_PATH],
                      szCurrDayST_Ly1FileName[MAX_PATH],
                      szCurrDayST_Ly2FileName[MAX_PATH],
                      szCurrDayST_Ly3FileName[MAX_PATH],
                      szCurrDayST_Ly4FileName[MAX_PATH],
                      szCurrDayST_Ly5FileName[MAX_PATH],
                      szCurrDayST_Ly6FileName[MAX_PATH],
                      szCurrDayPool1FileName[MAX_PATH], //pool
                      szCurrDayPool2FileName[MAX_PATH],
                      szCurrDayPool3FileName[MAX_PATH],
                      szCurrDayPool4FileName[MAX_PATH], //pool
                      szCurrDayPool5FileName[MAX_PATH],
                      szCurrDayPool6FileName[MAX_PATH],
                      szCurrDayPool7FileName[MAX_PATH], //pool
                      szCurrDayPool8FileName[MAX_PATH],
                      szCurrDayPool9FileName[MAX_PATH],
                      szCurrDayBiomassPool1FileName[MAX_PATH],
                      szCurrDayBiomassPool2FileName[MAX_PATH],
                      szCurrDayBiomassPool3FileName[MAX_PATH],
                      szCurrDayBiomassPool4FileName[MAX_PATH],
                      szCurrDaySoilPondWaterFileName[MAX_PATH],//pond
                      szCurrDaySWEFileName[MAX_PATH],
                      szCurrDaySnowdepthFileName[MAX_PATH],
                      szCurrDaySnowdensityFileName[MAX_PATH],
                      szCurrDaySoilUnsatStorageFileName[MAX_PATH],
                      szGPPTotalFileName[MAX_PATH],
                      szNEPTotalFileName[MAX_PATH],	// MM
                      szNPPTotalFileName[MAX_PATH],
                      szETTotalFileName[MAX_PATH],	// MM
                      szTemporaryTextureName[MAX_PATH],
                      szCurrDaySoilSatDeficitFileName[MAX_PATH],
                      szWaterInFileName[MAX_PATH];
    int modisday;

    double soilt;
    double gdd=0;
    double sad=0;
    double snow_acc=0;
    double snow_today;
    double T_m;
    double T_five[5];
    double a1,a2,a3,a4,a5;
    float temp_a;
    int i,ii,nl,np,i2;						// Counters: j for output counter
    int pix,lin;						// Counters
    int line;							// Position of line,pixel in Canada, referenced to 0,0 NOT 1,1
    int jday;							// Julian day
    int rcode;							// Error code
    int soil_index;						// index into soil parameters MM 2005-Apr-25
    double b[SIZEB];					// Biological parameters
    unsigned char* temp_uc_buff;		// Temporary Buffer
    float*	    temp_sand_buff;				// Temporary Sand Buffer
    float*	    temp_silt_buff;				// Temporary Silt Buffer
    float*	    temp_clay_buff;				// Temporary Clay Buffer
    float*	    temp_om_buff;				// Temporary OM Buffer
    short int*	climate_rad_r;			// Output Climate Buffer juw
    short int*	climate_rad_f;			// Output Climate Buffer juw
    short int*	climate_ti;				// Output Climate Buffer
    short int*	climate_tm;				// Output Climate Buffer
    short int*	climate_prec;			// Output Climate Buffer

    short int*	climate_dew;			// Output Climate Buffer
    short int*	climate_wind;			// Output Climate Buffer,
    float *waterin;
    unsigned char* lc;					// Land cover for a line in a given study area
    double* lai;						// LAI for a line in a given study area
    double* lon,*lat;					// Long, lat values for a line in study area
    double* xSoil;						// X variables

    float* pFloatOutput;				// For output images
    struct xvalue *xx;					// X variables for a line in a given study area
    struct climatedata *sdat;			// climate data
    double *	g_model;					// buffer utilized by model()
    double* z_model;					// buffer utilized by model()
    float*	Array_Elevation_3r;			// array for elevation values

    int kk;
    float*	Array_WElevation_3r;			// array for elevation values
    int*	Array_Label_3r;				// array of marker for processed pixels:
    // 9999 for processed, -9999 for unprocessed
    unsigned char* watershed;			// pointer to point to a line of watershed data

    float* temp_total;					// for summing data

    Soil_t*  soil;
    Soil_t*  soil_3r;
    //Soil_index_t* soilindex;			//structure array pointer

    //input buffers containing data previously contained in soil survey structure:
    unsigned char* soil_texture;		//input buffer
    float* soil_surf_k0v;				//input buffer
    float* soil_surf_k0h;				//input buffer
    float* soil_init_z;					//input buffer
    float* soil_init_temp;					//input buffer
    float* carbon_pool1;
    float* carbon_pool2;
    float* carbon_pool3;
    float* carbon_pool4;  //pools
    float* carbon_pool5;
    float* carbon_pool6;
    float* carbon_pool7;
    float* carbon_pool8;
    float* carbon_pool9;
    float* biomass_pool1;
    float* biomass_pool2;
    float* biomass_pool3;
    float* biomass_pool4;
    float* soil_depth;					//input buffer
    //soil output buffers:
    float* soil_K0_decay_m;
    float* soil_saturation_suction;
    float* soil_saturated_Kv;
    float* soil_saturated_Kh;
    float* soil_saturation_deficit;
    float* soil_unsaturated_storage;
    float* soil_water_table;
    float* buff_soil_temp;//2nov2006
    float* soil_pondwater; //pond
    float* soil_Max_depth_Z;
    float* soil_b;
    float* buffer_nitrogen;
    float* buffer_CNcd;
    float* buffer_CNssd;
    float* buffer_CNsmd;
    float* buffer_CNfsd;
    float* buffer_CNfmd;
    float* buffer_CNsm;
    float* buffer_CNm;
    float* buffer_CNs;
    float* buffer_CNp;
    float* buffer_CNw;
    float* buffer_CNfr;
    float* buffer_CNl;
    float* buff_ST_Ly1;
    float* buff_ST_Ly2;
    float* buff_ST_Ly3;
    float* buff_ST_Ly4;
    float* buff_ST_Ly5;
    float* buff_ST_Ly6;
    //**********pools buffers**********
    float* buff_pool1;
    float* buff_pool2;
    float* buff_pool3;
    float* buff_pool4;
    float* buff_pool5;
    float* buff_pool6;
    float* buff_pool7;
    float* buff_pool8;
    float* buff_pool9;
    float* bio_pool1;
    float* bio_pool2;
    float* bio_pool3;
    float* bio_pool4;
    //*********************************
    //float * daily_soil_resp;
    //soil intermediate processing buffers:
    float* soil_K0_decay_m_3r;
    float* soil_saturation_suction_3r;
    float* soil_saturated_Kv_3r;
    float* soil_saturated_Kh_3r;
    float* soil_saturation_deficit_3r;
    float* soil_unsaturated_storage_3r;
    float* soil_water_table_3r;
    float* soil_temp_3r;//2nov2006
    float* soil_nitrogen_3r;
    float* soil_CNcd_3r;
    float* soil_CNssd_3r;
    float* soil_CNsmd_3r;
    float* soil_CNfsd_3r;
    float* soil_CNfmd_3r;
    float* soil_CNsm_3r;
    float* soil_CNm_3r;
    float* soil_CNs_3r;
    float* soil_CNp_3r;
    float* soil_CNw_3r;
    float* soil_CNfr_3r;
    float* soil_CNl_3r;
    float* soil_ST_Ly1_3r;
    float* soil_ST_Ly2_3r;
    float* soil_ST_Ly3_3r;
    float* soil_ST_Ly4_3r;
    float* soil_ST_Ly5_3r;
    float* soil_ST_Ly6_3r;
    //float* land_3r;
    float* soil_pool1_3r; //pools 3 rows
    float* soil_pool2_3r;
    float* soil_pool3_3r;
    float* soil_pool4_3r;
    float* soil_pool5_3r;
    float* soil_pool6_3r;
    float* soil_pool7_3r;
    float* soil_pool8_3r;
    float* soil_pool9_3r;
    float* soil_bio_pool1_3r;
    float* soil_bio_pool2_3r;
    float* soil_bio_pool3_3r;
    float* soil_bio_pool4_3r;
    float* soil_pondwater_3r;	//pond
    float* soil_Max_depth_Z_3r;
    float* soil_b_3r;
    int kkk;

    struct pubv		v;					//public variables
    struct pubv*	pv = &v;
    Canopy_t*		canopy;				//pointer to array of structures of type Canopy_t
    Energy*	    energy;			// pointer to array of structures to save climate values
    Snow_t*	        snow;			   // pointer to array of structures to save climate values

    float*	canopy_ET;			//canopy data buffer

    float*	canopy_evaporation;			//canopy data buffer
    float*	canopy_transpiration_unsat;	//canopy data buffer
    float*	canopy_transpiration_sat;	//canopy data buffer
    float*	canopy_intercepted;			//canopy data buffer
    float*	canopy_litter_evaporation;	//canopy data buffer
    float*	canopy_moss_transpiration;	//canopy data buffer
    float*	canopy_soil_evaporation;	//canopy data buffer
    float*	canopy_UT;	              	//canopy data buffer
    float*  canopy_stomata;					// for any varaiable //4 may 2006

    float*  sensibleHeatFlux;
    float*  latentHeatFlux;
    float*  NRFlux;

    float* Daily_GPP;
    float* Daily_NPP;
    float* Daily_NEP;
    float* Daily_Ra;
    float* Daily_Rh;
    float* runoff_total;
    float* soil_resp_x;
    float* runoff_baseflow;
    float* runoff_total_inflow;
    float* runoff_total_outflow;
    float* soil_capillary_rise;
    float* soil_percolation;



    float*	curr_snowdepth;
    float*  curr_snowdensity;
    float*  curr_snowSWE;
    float*	prev_snowdepth;
    float*  prev_snowdensity;
    float*  prev_snowSWE;

    float* gpp_total;					// for summing NPP data
    float* npp_total;					// for summing NPP data
    float* nep_total;					// for summing NPP data
    float* et_total;					// for summing ET data


    FILE*	canopy_ET_ptr;		         	//ET file pointer
    FILE*	canopy_Stomata_ptr;		         	// 4 may 2006 file pointer
    FILE*	canopy_evaporation_ptr;			//canopy evaporation data file pointer
    FILE*	canopy_transpiration_unsat_ptr;	//canopy transpiration from unsaturated zone file pointer 非饱和带冠层蒸腾作用
    FILE*	canopy_transpiration_sat_ptr;	//canopy transpiration from saturated zonedata file pointer 饱和区冠层蒸腾作用
    FILE*	canopy_intercepted_ptr;			//canopy intercepted water data file pointer 树冠拦截水
    FILE*	canopy_litter_evaporation_ptr;	//canopy litter evaporation file pointer 树冠凋落物蒸发
    FILE*	canopy_moss_transpiration_ptr;	//canopy moss evaporation file pointer 树冠苔藓蒸发
    FILE*	canopy_soil_evaporation_ptr;	//canopy soil evaporation file pointer 树冠土壤蒸发
    FILE*	canopy_UT_ptr;	                 //canopy understorey transpiration file pointer 树冠下层木蒸腾


    FILE*	NRFlux_ptr;             //net radiation file pointer
    FILE*	sensibleHeatFlux_ptr;	//sensible heat flux file pointer
    FILE*	latentHeatFlux_ptr;		//latent heat flux file pointer

    FILE*   Daily_GPP_ptr;
    FILE*   Daily_NPP_ptr;
    FILE*   Daily_NEP_ptr;
    FILE*   Daily_Ra_ptr;
    FILE*   Daily_Rh_ptr;


    FILE*	soil_Max_depth_Z_ptr;
    FILE*	soil_b_ptr;
    FILE*	soil_texture_file_ptr;		//soil survey data file pointer
    FILE*	soil_init_z_file_ptr;		//soil survey data file pointer
    FILE*	soil_init_temp_file_ptr;		//soil survey data file pointer
    FILE*	carbon_pool1_file_ptr;
    FILE*	carbon_pool2_file_ptr;
    FILE*	carbon_pool3_file_ptr;
    FILE*	carbon_pool4_file_ptr;
    FILE*	carbon_pool5_file_ptr;
    FILE*	carbon_pool6_file_ptr;
    FILE*	carbon_pool7_file_ptr;
    FILE*	carbon_pool8_file_ptr;
    FILE*	carbon_pool9_file_ptr;
    FILE*	biomass_pool1_file_ptr;
    FILE*	biomass_pool2_file_ptr;
    FILE*	biomass_pool3_file_ptr;
    FILE*	biomass_pool4_file_ptr;
    FILE*	soil_depth_file_ptr;		//soil survey data file pointer
    FILE*	soil_K0_decay_m_ptr;
    FILE*	soil_saturation_suction_ptr;
    FILE*	soil_saturated_Kv_ptr;
    FILE*	soil_saturated_Kh_ptr;
    FILE*	prev_day_soil_saturation_deficit_ptr;
    FILE*	prev_day_soil_unsaturated_storage_ptr;
    FILE*	prev_day_soil_water_table_ptr;
    FILE*	prev_day_soil_temp_ptr; //2nov2006
    FILE*	prev_day_nitrogen_ptr; //2nov2006
    FILE*	prev_day_CNcd_ptr;
    FILE*	prev_day_CNssd_ptr;
    FILE*	prev_day_CNsmd_ptr;
    FILE*	prev_day_CNfsd_ptr;
    FILE*	prev_day_CNfmd_ptr;
    FILE*	prev_day_CNsm_ptr;
    FILE*	prev_day_CNm_ptr;
    FILE*	prev_day_CNs_ptr;
    FILE*	prev_day_CNp_ptr;
    FILE*	prev_day_CNw_ptr;
    FILE*	prev_day_CNfr_ptr;
    FILE*	prev_day_CNl_ptr;
    FILE*	prev_day_ST_Ly1_ptr;
    FILE*	prev_day_ST_Ly2_ptr;
    FILE*	prev_day_ST_Ly3_ptr;
    FILE*	prev_day_ST_Ly4_ptr;
    FILE*	prev_day_ST_Ly5_ptr;
    FILE*	prev_day_ST_Ly6_ptr;
    FILE*	prev_day_pool1_ptr; //pools
    FILE*	prev_day_pool2_ptr;
    FILE*	prev_day_pool3_ptr;
    FILE*	prev_day_pool4_ptr;
    FILE*	prev_day_pool5_ptr;
    FILE*	prev_day_pool6_ptr;
    FILE*	prev_day_pool7_ptr;
    FILE*	prev_day_pool8_ptr;
    FILE*	prev_day_pool9_ptr;
    FILE*	prev_day_bio_pool1_ptr;
    FILE*	prev_day_bio_pool2_ptr;
    FILE*	prev_day_bio_pool3_ptr;
    FILE*	prev_day_bio_pool4_ptr;
    FILE*	prev_day_soil_pondwater_ptr; //24june//pond
    FILE*   prev_day_snow_swe_ptr;
    FILE*   prev_day_snow_depth_ptr;
    FILE*   prev_day_snow_density_ptr;
    FILE*	curr_day_soil_saturation_deficit_ptr;
    FILE*	curr_day_soil_unsaturated_storage_ptr;
    FILE*	curr_day_soil_water_table_ptr;
    FILE*	curr_day_soil_temp_ptr; //2nov2006
    FILE*	curr_day_nitrogen_ptr;
    FILE*	curr_day_CNcd_ptr;
    FILE*	curr_day_CNssd_ptr;
    FILE*	curr_day_CNsmd_ptr;
    FILE*	curr_day_CNfsd_ptr;
    FILE*	curr_day_CNfmd_ptr;
    FILE*	curr_day_CNsm_ptr;
    FILE*	curr_day_CNm_ptr;
    FILE*	curr_day_CNs_ptr;
    FILE*	curr_day_CNp_ptr;
    FILE*	curr_day_CNw_ptr;
    FILE*	curr_day_CNfr_ptr;
    FILE*	curr_day_CNl_ptr;
    FILE*	curr_day_ST_Ly1_ptr;
    FILE*	curr_day_ST_Ly2_ptr;
    FILE*	curr_day_ST_Ly3_ptr;
    FILE*	curr_day_ST_Ly4_ptr;
    FILE*	curr_day_ST_Ly5_ptr;
    FILE*	curr_day_ST_Ly6_ptr;
    FILE*	curr_day_pool1_ptr; //pools
    FILE*	curr_day_pool2_ptr;
    FILE*	curr_day_pool3_ptr;
    FILE*	curr_day_pool4_ptr;
    FILE*	curr_day_pool5_ptr;
    FILE*	curr_day_pool6_ptr;
    FILE*	curr_day_pool7_ptr;
    FILE*	curr_day_pool8_ptr;
    FILE*	curr_day_pool9_ptr;
    FILE*	curr_day_bio_pool1_ptr;
    FILE*	curr_day_bio_pool2_ptr;
    FILE*	curr_day_bio_pool3_ptr;
    FILE*	curr_day_bio_pool4_ptr;
    FILE*	curr_day_soil_pondwater_ptr; //pond
    FILE*   curr_day_snow_swe_ptr;
    FILE*   curr_day_snow_depth_ptr;
    FILE*   curr_day_snow_density_ptr;
    FILE*	curr_day_soil_capillary_rise_ptr;
    FILE*	curr_day_soil_percolation_ptr;
    FILE*	climate_rad_r_ptr;	//climate data file pointer		// juw
    FILE*	climate_rad_f_ptr;	//climate data file pointer		// juw
    FILE*	climate_ti_ptr;		//climate data file pointer
    FILE*	climate_tm_ptr;		//climate data file pointer
    FILE*	climate_prec_ptr;	//climate data file pointer
    FILE*	climate_dew_ptr;	//climate data file pointer
    FILE*	climate_wind_ptr;	//climate data file pointer	...................
    FILE*	lcfile_ptr;			//land cover file pointer
    FILE*	laifile_ptr;		//leaf area index file pointer
    FILE*	Dem_ptr;			//DEM file pointer
    FILE*	fwatershed;
    FILE*	runoff_total_ptr; // cancelled 24jun
    FILE*	runoff_baseflow_ptr;
    FILE*	runoff_total_inflow_ptr;
    FILE*	runoff_total_outflow_ptr;
    FILE*	gpp_total_out_ptr;	// MM
    FILE*	npp_total_out_ptr;	// MM
    FILE*	nep_total_out_ptr;	// MM
    FILE*	et_total_out_ptr;   //MM
    FILE*   waterin_ptr;

    rcode= NOPERROR;

    v.jday_start	= BH_SubParams1->iDayStart;		//150
    v.jday_end		= BH_SubParams1->iDayEnd;			//152
    v.nlines		= BH_SubParams1->iNumLines;
    v.npixels		= BH_SubParams1->iNumPixels;
    v.iXsize		= BH_SubParams1->iPixelX;
    v.iYsize		= BH_SubParams1->iPixelY;
    v.factor		= BH_SubParams1->iNPPMultFactor;
    v.output_interval = 1;
    v.ULLat			= BH_SubParams1->fULCLatitude;
    v.ULLong		= BH_SubParams1->fULCLongitude;
    v.LRLat			= BH_SubParams1->fLRCLatitude;
    v.LRLong		= BH_SubParams1->fLRCLongitude;

    //分配内存

    nl=pv->nlines;
    np=pv->npixels;
    if (	((temp_uc_buff		    =(unsigned char*)malloc(np*sizeof(unsigned char)))	==NULL)
            ||	((climate_rad_r		=(short int*)malloc(np*sizeof(short int)))			==NULL)
            ||	((climate_rad_f		=(short int*)malloc(np*sizeof(short int)))			==NULL)
            ||	((climate_ti		=(short int*)malloc(np*sizeof(short int)))			==NULL)
            ||	((climate_tm		=(short int*)malloc(np*sizeof(short int)))			==NULL)
            ||	((climate_prec		=(short int*)malloc(np*sizeof(short int)))			==NULL)
            ||	((climate_dew		=(short int*)malloc(np*sizeof(short int)))			==NULL)
            ||	((climate_wind		=(short int*)malloc(np*sizeof(short int)))			==NULL)
            ||	((waterin        	=(float*)    malloc(np*sizeof( float)))			    ==NULL)
            ||	((lc				=(unsigned char*)malloc(np*sizeof(unsigned char)))	==NULL)
            ||	((lai				=(double*)malloc(np*sizeof(double)))				==NULL)
            ||	((lon				=(double*)malloc(np*sizeof(double)))				==NULL)
            ||	((lat				=(double*)malloc(np*sizeof(double)))				==NULL)
            ||	((pFloatOutput		=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((xSoil				=(double*)malloc(SIZEX*sizeof(double)))				==NULL)
            ||	((xx				=(struct xvalue*)malloc(np*sizeof(struct xvalue)))				==NULL)
            ||	((sdat				=(struct climatedata*)malloc(np*sizeof(struct climatedata)))	==NULL)
            ||	((canopy				    =(Canopy_t*)malloc(np*sizeof(Canopy_t)))			==NULL)
            ||	((canopy_ET         		=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((canopy_stomata         	=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((canopy_evaporation		=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((canopy_transpiration_unsat=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((canopy_transpiration_sat	=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((canopy_intercepted		=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((canopy_litter_evaporation	=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((canopy_moss_transpiration	=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((canopy_soil_evaporation	=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((canopy_UT	                 =(float*)malloc(np*sizeof(float)))				    ==NULL)
            ||	((energy					=(Energy*)malloc(np*sizeof(Energy)))	            ==NULL)
            ||	((NRFlux		            =(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((sensibleHeatFlux	        =(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((latentHeatFlux	       	=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((Daily_GPP		                =(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((Daily_NPP		         	    =(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((Daily_NEP		            	=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((Daily_Ra		         	    =(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((Daily_Rh		            	=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((soil_texture					=(unsigned char*)malloc(np*sizeof(unsigned char)))	==NULL)
            ||	((soil_surf_k0v					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((soil_surf_k0h					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((soil_init_z					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((soil_init_temp				=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((carbon_pool1					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((carbon_pool2					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((carbon_pool3					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((carbon_pool4					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((carbon_pool5					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((carbon_pool6					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((carbon_pool7					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((carbon_pool8					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((carbon_pool9					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((biomass_pool1					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((biomass_pool2					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((biomass_pool3					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((biomass_pool4					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((soil_depth					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((soil							=(Soil_t*)malloc(np*sizeof(Soil_t)))				==NULL)
            ||	((soil_3r						=(Soil_t*)malloc(3*np*sizeof(Soil_t)))				==NULL)
            ||	((soil_K0_decay_m				=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((soil_b						=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((soil_saturation_suction		=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((soil_saturated_Kv				=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((soil_saturated_Kh				=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((soil_saturation_deficit		=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((soil_unsaturated_storage		=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((soil_water_table				=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buff_soil_temp				=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buffer_nitrogen				=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buffer_CNcd					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buffer_CNssd					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buffer_CNsmd					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buffer_CNfsd					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buffer_CNfmd					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buffer_CNsm					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buffer_CNm					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buffer_CNs					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buffer_CNp					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buffer_CNw					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buffer_CNfr					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buffer_CNl					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buff_ST_Ly1					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buff_ST_Ly2					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buff_ST_Ly3					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buff_ST_Ly4					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buff_ST_Ly5					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buff_ST_Ly6					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buff_pool1					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buff_pool2					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buff_pool3					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buff_pool4					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buff_pool5					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buff_pool6					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buff_pool7					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buff_pool8					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((buff_pool9					=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((bio_pool1						=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((bio_pool2						=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((bio_pool3						=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((bio_pool4						=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((soil_pondwater				=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((soil_Max_depth_Z				=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((soil_capillary_rise			=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((soil_percolation				=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((soil_K0_decay_m_3r			=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_b_3r						=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_saturation_suction_3r	=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_saturated_Kv_3r			=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_saturated_Kh_3r			=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_saturation_deficit_3r	=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_unsaturated_storage_3r	=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_water_table_3r			=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_temp_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_nitrogen_3r				=(float*)malloc(3*np*sizeof(float)))			    ==NULL)
            ||	((soil_pool1_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_CNcd_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_CNssd_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_CNsmd_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_CNfsd_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_CNfmd_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_CNsm_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_CNm_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_CNs_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_CNp_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_CNw_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_CNfr_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_CNl_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_ST_Ly1_3r				=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_ST_Ly2_3r				=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_ST_Ly3_3r				=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_ST_Ly4_3r				=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_ST_Ly5_3r				=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_ST_Ly6_3r				=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_pool2_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_pool3_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_pool4_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_pool5_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_pool6_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_pool7_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_pool8_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_pool9_3r					=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((soil_bio_pool1_3r					=(float*)malloc(3*np*sizeof(float)))			==NULL)
            ||	((soil_bio_pool2_3r					=(float*)malloc(3*np*sizeof(float)))			==NULL)
            ||	((soil_bio_pool3_3r					=(float*)malloc(3*np*sizeof(float)))			==NULL)
            ||	((soil_bio_pool4_3r					=(float*)malloc(3*np*sizeof(float)))			==NULL)
            ||	((soil_pondwater_3r			=(float*)malloc(3*np*sizeof(float)))				    ==NULL)
            ||	((soil_Max_depth_Z_3r			=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((g_model						=(double *)malloc(SIZEG*sizeof(double)))			==NULL)
            ||	((z_model						=(double *)malloc(SIZEZ*sizeof(double)))			==NULL)
            ||	((Array_Elevation_3r			=(float*)malloc(3*np*sizeof(float)))				==NULL)
            ||	((Array_WElevation_3r			=(float*)malloc(3*np*sizeof(float)))				==NULL)// 19June2006, updating WT with previous WT
            ||	((Array_Label_3r				=(int*)malloc(3*np*sizeof(int)))					==NULL)
            ||	((watershed						=(unsigned char*)malloc(np*sizeof(unsigned char)))	==NULL)
            ||	((runoff_total					=(float*)malloc(np*sizeof(float)))					==NULL)	 // cancelled 24 jun
            ||	((runoff_baseflow				=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((runoff_total_inflow			=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((runoff_total_outflow			=(float*)malloc(np*sizeof(float)))					==NULL)
            ||	((soil_resp_x				=(float*)malloc(np*sizeof(float)))					    ==NULL)
            ||	(( snow				=(Snow_t*)malloc(np*sizeof(Snow_t)))	                        ==NULL)
            ||	(( curr_snowdepth     	=(float*)malloc(np*sizeof(float)))							==NULL)
            ||	(( curr_snowdensity     =(float*)malloc(np*sizeof(float)))							==NULL)
            ||	(( curr_snowSWE      	=(float*)malloc(np*sizeof(float)))							==NULL)
            ||	(( prev_snowdepth     	=(float*)malloc(np*sizeof(float)))							==NULL)
            ||	(( prev_snowdensity     =(float*)malloc(np*sizeof(float)))							==NULL)
            ||	(( prev_snowSWE      	=(float*)malloc(np*sizeof(float)))							==NULL))
    {
        printf("\n Error in allocating memory");
        exit(0);
    }





    /*=========================Start Soil_constructor() block====================================*/
    /*=========================Start Soil_constructor() block====================================*/
    printf("Creating initial Soil Data input file..\n");
//    printf("unnormal!!!");

    strcpy(SoilK0DecayMFileName		,BH_SubParams1a->szOutFileNameSoilK0DecayM);
    strcpy(SoilSatSuctionFileName,BH_SubParams1a->szOutFileNameSoilSatSuction);
    strcpy(SoilSatKvFileName	,BH_SubParams1a->szOutFileNameSoilSatKv);
    strcpy(SoilSatKhFileName	,BH_SubParams1a->szOutFileNameSoilSatKh);

    insert_day_number(szPrevDaySoilSatDeficitFileName	,BH_SubParams1a->szOutFileNameSoilSatDeficit	,pv->jday_start-1);
    insert_day_number(szPrevDaySoilUnsatStorageFileName	,BH_SubParams1a->szOutFileNameSoilUnsatStorage	,pv->jday_start-1);
    insert_day_number(szPrevDaySoilWaterTableFileName	,BH_SubParams1a->szOutFileNameSoilWaterTable	,pv->jday_start-1);
    insert_day_number(szPrevDaySoilTempFileName	,BH_SubParams1a->szOutFileNameSoilTemp      	,pv->jday_start-1);
    insert_day_number(szPrevDayNitrogenFileName	,BH_SubParams1a->szOutFileNameNitrogen      	,pv->jday_start-1);
    insert_day_number(szPrevDayCNcdFileName	,BH_SubParams1a->szOutFileNameCNcd      	,pv->jday_start-1);
    insert_day_number(szPrevDayCNssdFileName,BH_SubParams1a->szOutFileNameCNssd      	,pv->jday_start-1);
    insert_day_number(szPrevDayCNsmdFileName,BH_SubParams1a->szOutFileNameCNsmd      	,pv->jday_start-1);
    insert_day_number(szPrevDayCNfsdFileName,BH_SubParams1a->szOutFileNameCNfsd      	,pv->jday_start-1);
    insert_day_number(szPrevDayCNfmdFileName,BH_SubParams1a->szOutFileNameCNfmd      	,pv->jday_start-1);
    insert_day_number(szPrevDayCNsmFileName,BH_SubParams1a->szOutFileNameCNsm      	    ,pv->jday_start-1);
    insert_day_number(szPrevDayCNmFileName,BH_SubParams1a->szOutFileNameCNm      		,pv->jday_start-1);
    insert_day_number(szPrevDayCNsFileName,BH_SubParams1a->szOutFileNameCNs      		,pv->jday_start-1);
    insert_day_number(szPrevDayCNpFileName,BH_SubParams1a->szOutFileNameCNp      		,pv->jday_start-1);
    insert_day_number(szPrevDayCNwFileName,BH_SubParams1a->szOutFileNameCNw      		,pv->jday_start-1);
    insert_day_number(szPrevDayCNfrFileName,BH_SubParams1a->szOutFileNameCNfr      	    ,pv->jday_start-1);
    insert_day_number(szPrevDayCNlFileName,BH_SubParams1a->szOutFileNameCNl      		,pv->jday_start-1);
    insert_day_number(szPrevDayST_Ly1FileName,BH_SubParams1a->szOutFileNameST_Ly1      	,pv->jday_start-1);
    insert_day_number(szPrevDayST_Ly2FileName,BH_SubParams1a->szOutFileNameST_Ly2      	,pv->jday_start-1);
    insert_day_number(szPrevDayST_Ly3FileName,BH_SubParams1a->szOutFileNameST_Ly3      	,pv->jday_start-1);
    insert_day_number(szPrevDayST_Ly4FileName,BH_SubParams1a->szOutFileNameST_Ly4      	,pv->jday_start-1);
    insert_day_number(szPrevDayST_Ly5FileName,BH_SubParams1a->szOutFileNameST_Ly5      	,pv->jday_start-1);
    insert_day_number(szPrevDayST_Ly6FileName,BH_SubParams1a->szOutFileNameST_Ly6      	,pv->jday_start-1);
    insert_day_number(szPrevDayPool1FileName	,BH_SubParams1a->szOutFileNamePool1      	,pv->jday_start-1);
    insert_day_number(szPrevDayPool2FileName	,BH_SubParams1a->szOutFileNamePool2      	,pv->jday_start-1);
    insert_day_number(szPrevDayPool3FileName	,BH_SubParams1a->szOutFileNamePool3      	,pv->jday_start-1);
    insert_day_number(szPrevDayPool4FileName	,BH_SubParams1a->szOutFileNamePool4      	,pv->jday_start-1);
    insert_day_number(szPrevDayPool5FileName	,BH_SubParams1a->szOutFileNamePool5      	,pv->jday_start-1);
    insert_day_number(szPrevDayPool6FileName	,BH_SubParams1a->szOutFileNamePool6      	,pv->jday_start-1);
    insert_day_number(szPrevDayPool7FileName	,BH_SubParams1a->szOutFileNamePool7      	,pv->jday_start-1);
    insert_day_number(szPrevDayPool8FileName	,BH_SubParams1a->szOutFileNamePool8      	,pv->jday_start-1);
    insert_day_number(szPrevDayPool9FileName	,BH_SubParams1a->szOutFileNamePool9      	,pv->jday_start-1);
    insert_day_number(szPrevDayBiomassPool1FileName	,BH_SubParams1a->szOutFileNameB_Pool1      	,pv->jday_start-1);
    insert_day_number(szPrevDayBiomassPool2FileName	,BH_SubParams1a->szOutFileNameB_Pool2      	,pv->jday_start-1);
    insert_day_number(szPrevDayBiomassPool3FileName	,BH_SubParams1a->szOutFileNameB_Pool3      	,pv->jday_start-1);
    insert_day_number(szPrevDayBiomassPool4FileName	,BH_SubParams1a->szOutFileNameB_Pool4      	,pv->jday_start-1);
    insert_day_number(szPrevDaySoilPondWaterFileName	,BH_SubParams1a->szOutFileNameSoilPondWater	,pv->jday_start-1);
    insert_day_number(szPrevDaySWEFileName	,BH_SubParams1a->szOutFileNameSnowswe	,pv->jday_start-1);
    insert_day_number(szPrevDaySnowdepthFileName	,BH_SubParams1a->szOutFileNameSnowdepth	,pv->jday_start-1);
    insert_day_number(szPrevDaySnowdensityFileName	,BH_SubParams1a->szOutFileNameSnowdensity,pv->jday_start-1);
// printf("%s",BH_SubParams1->szInFileNameSoilTexture);

    if(((soil_K0_decay_m_ptr			        =fopen(SoilK0DecayMFileName							,"wb"))	==NULL)
            ||	((soil_saturation_suction_ptr	=fopen(SoilSatSuctionFileName						,"wb"))	==NULL)
            ||	((soil_saturated_Kv_ptr			        =fopen(SoilSatKvFileName								,"wb"))	==NULL)
            ||	((soil_saturated_Kh_ptr			        =fopen(SoilSatKhFileName								,"wb"))	==NULL)
            ||	((soil_Max_depth_Z_ptr					=fopen(BH_SubParams1a->szOutFileNameSoilMaxDepthZ		,"wb"))	==NULL)
            ||	((soil_b_ptr							=fopen(BH_SubParams1a->szOutFileNameSoilB				,"wb"))	==NULL)
            ||  ((prev_day_soil_saturation_deficit_ptr	=fopen(szPrevDaySoilSatDeficitFileName		,"wb"))	==NULL)
            ||	((prev_day_soil_unsaturated_storage_ptr	=fopen(szPrevDaySoilUnsatStorageFileName	,"wb"))	==NULL)
            ||	((prev_day_soil_water_table_ptr			=fopen(szPrevDaySoilWaterTableFileName		,"wb"))	==NULL)
            ||	((prev_day_soil_temp_ptr			=fopen(szPrevDaySoilTempFileName		,"wb"))	==NULL)
            ||	((prev_day_nitrogen_ptr			=fopen(szPrevDayNitrogenFileName		,"wb"))	==NULL)
            ||	((prev_day_CNcd_ptr		=fopen(szPrevDayCNcdFileName				,"wb"))	==NULL)
            ||	((prev_day_CNssd_ptr		=fopen(szPrevDayCNssdFileName			,"wb"))	==NULL)
            ||	((prev_day_CNsmd_ptr		=fopen(szPrevDayCNsmdFileName			,"wb"))	==NULL)
            ||	((prev_day_CNfsd_ptr		=fopen(szPrevDayCNfsdFileName			,"wb"))	==NULL)
            ||	((prev_day_CNfmd_ptr		=fopen(szPrevDayCNfmdFileName			,"wb"))	==NULL)
            ||	((prev_day_CNsm_ptr			=fopen(szPrevDayCNsmFileName			,"wb"))	==NULL)
            ||	((prev_day_CNm_ptr			=fopen(szPrevDayCNmFileName				,"wb"))	==NULL)
            ||	((prev_day_CNs_ptr			=fopen(szPrevDayCNsFileName				,"wb"))	==NULL)
            ||	((prev_day_CNp_ptr			=fopen(szPrevDayCNpFileName				,"wb"))	==NULL)
            ||	((prev_day_CNw_ptr			=fopen(szPrevDayCNwFileName				,"wb"))	==NULL)
            ||	((prev_day_CNfr_ptr			=fopen(szPrevDayCNfrFileName			,"wb"))	==NULL)
            ||	((prev_day_CNl_ptr			=fopen(szPrevDayCNlFileName				,"wb"))	==NULL)
            ||	((prev_day_ST_Ly1_ptr			=fopen(szPrevDayST_Ly1FileName			,"wb"))	==NULL)
            ||	((prev_day_ST_Ly2_ptr			=fopen(szPrevDayST_Ly2FileName			,"wb"))	==NULL)
            ||	((prev_day_ST_Ly3_ptr			=fopen(szPrevDayST_Ly3FileName			,"wb"))	==NULL)
            ||	((prev_day_ST_Ly4_ptr			=fopen(szPrevDayST_Ly4FileName			,"wb"))	==NULL)
            ||	((prev_day_ST_Ly5_ptr			=fopen(szPrevDayST_Ly5FileName			,"wb"))	==NULL)
            ||	((prev_day_ST_Ly6_ptr			=fopen(szPrevDayST_Ly6FileName			,"wb"))	==NULL)
            ||	((prev_day_pool1_ptr				=fopen(szPrevDayPool1FileName		,"wb"))	==NULL)
            ||	((prev_day_pool2_ptr				=fopen(szPrevDayPool2FileName		,"wb"))	==NULL)
            ||	((prev_day_pool3_ptr				=fopen(szPrevDayPool3FileName		,"wb"))	==NULL)
            ||	((prev_day_pool4_ptr				=fopen(szPrevDayPool4FileName		,"wb"))	==NULL)
            ||	((prev_day_pool5_ptr				=fopen(szPrevDayPool5FileName		,"wb"))	==NULL)
            ||	((prev_day_pool6_ptr				=fopen(szPrevDayPool6FileName		,"wb"))	==NULL)
            ||	((prev_day_pool7_ptr				=fopen(szPrevDayPool7FileName		,"wb"))	==NULL)
            ||	((prev_day_pool8_ptr				=fopen(szPrevDayPool8FileName		,"wb"))	==NULL)
            ||	((prev_day_pool9_ptr				=fopen(szPrevDayPool9FileName		,"wb"))	==NULL)
            ||	((prev_day_bio_pool1_ptr				=fopen(szPrevDayBiomassPool1FileName		,"wb"))	==NULL)
            ||	((prev_day_bio_pool2_ptr				=fopen(szPrevDayBiomassPool2FileName		,"wb"))	==NULL)
            ||	((prev_day_bio_pool3_ptr				=fopen(szPrevDayBiomassPool3FileName		,"wb"))	==NULL)
            ||	((prev_day_bio_pool4_ptr				=fopen(szPrevDayBiomassPool4FileName		,"wb"))	==NULL)
            ||	((prev_day_soil_pondwater_ptr		    =fopen(szPrevDaySoilPondWaterFileName		,"wb"))	==NULL)
            ||	((prev_day_snow_swe_ptr	                =fopen(szPrevDaySWEFileName	,"wb"))	==NULL)
            ||	((prev_day_snow_depth_ptr			    =fopen(szPrevDaySnowdepthFileName		,"wb"))	==NULL)
            ||	((prev_day_snow_density_ptr		        =fopen(szPrevDaySnowdensityFileName		,"wb"))	==NULL)
 //open 2 files corresponding to original soil survey binary file for reading
            ||	((soil_texture_file_ptr			=fopen(BH_SubParams1->szInFileNameSoilTexture					,"rb"))	==NULL)
            ||	((soil_init_z_file_ptr			=fopen(BH_SubParams1->szInFileNameSoilInitZ					,"rb"))	==NULL)
            ||	((soil_init_temp_file_ptr		=fopen(BH_SubParams1->szInFileNameSoilInitTemp					,"rb"))	==NULL)
            ||	((carbon_pool1_file_ptr     	=fopen(BH_SubParams1->szInFileNameCarbonPool1					,"rb"))	==NULL)
            ||	((carbon_pool2_file_ptr			=fopen(BH_SubParams1->szInFileNameCarbonPool2					,"rb"))	==NULL)
            ||	((carbon_pool3_file_ptr			=fopen(BH_SubParams1->szInFileNameCarbonPool3					,"rb"))	==NULL)
            ||	((carbon_pool4_file_ptr			=fopen(BH_SubParams1->szInFileNameCarbonPool4					,"rb"))	==NULL)
            ||	((carbon_pool5_file_ptr			=fopen(BH_SubParams1->szInFileNameCarbonPool5					,"rb"))	==NULL)
            ||	((carbon_pool6_file_ptr			=fopen(BH_SubParams1->szInFileNameCarbonPool6					,"rb"))	==NULL)
            ||	((carbon_pool7_file_ptr			=fopen(BH_SubParams1->szInFileNameCarbonPool7					,"rb"))	==NULL)
            ||	((carbon_pool8_file_ptr			=fopen(BH_SubParams1->szInFileNameCarbonPool8					,"rb"))	==NULL)
            ||	((carbon_pool9_file_ptr			=fopen(BH_SubParams1->szInFileNameCarbonPool9					,"rb"))	==NULL)
            ||	((biomass_pool1_file_ptr		=fopen(BH_SubParams1->szInFileNameBiomassPool1					,"rb"))	==NULL)
            ||	((biomass_pool2_file_ptr		=fopen(BH_SubParams1->szInFileNameBiomassPool2					,"rb"))	==NULL)
            ||	((biomass_pool3_file_ptr		=fopen(BH_SubParams1->szInFileNameBiomassPool3					,"rb"))	==NULL)
            ||	((biomass_pool4_file_ptr		=fopen(BH_SubParams1->szInFileNameBiomassPool4					,"rb"))	==NULL)
            ||	((soil_depth_file_ptr			=fopen(BH_SubParams1->szInFileNameSoilDepth				    	,"rb"))	==NULL)
            ||	((fwatershed                    =fopen(BH_SubParams1->szInFileNameWatershed						,"rb"))	==NULL)
           )
    {
        printf("\n Error in openfile");
        exit(0);
    }


    for (i=0; i<nl; i++)
    {
        //printf("ok1 %d %d\n",i,nl);

        memset(soil_texture					,0,np*sizeof(unsigned char));
        memset(soil_surf_k0v					,0,np*sizeof(float));
        memset(soil_surf_k0h					,0,np*sizeof(float));
        memset(soil_init_z					,0,np*sizeof(float));
        memset(soil_init_temp					,0,np*sizeof(float));
        memset(carbon_pool1					,0,np*sizeof(float));
        memset(carbon_pool2					,0,np*sizeof(float));
        memset(carbon_pool3					,0,np*sizeof(float));
        memset(carbon_pool4					,0,np*sizeof(float));
        memset(carbon_pool5					,0,np*sizeof(float));
        memset(carbon_pool6					,0,np*sizeof(float));
        memset(carbon_pool7					,0,np*sizeof(float));
        memset(carbon_pool8					,0,np*sizeof(float));
        memset(carbon_pool9					,0,np*sizeof(float));
        memset(biomass_pool1					,0,np*sizeof(float));
        memset(biomass_pool2					,0,np*sizeof(float));
        memset(biomass_pool3					,0,np*sizeof(float));
        memset(biomass_pool4					,0,np*sizeof(float));
        memset(soil_depth					,0,np*sizeof(float));
        memset(soil							,0,np*sizeof(Soil_t));
        memset(prev_snowSWE  				,0,np*sizeof(float));
        memset(prev_snowdepth  				,0,np*sizeof(float));
        memset(prev_snowdensity				,0,np*sizeof(float));

        if ((fread(soil_texture				,sizeof(unsigned char)	,np,soil_texture_file_ptr))			!=(size_t)np)
            rcode = PERROR;
        else if ((fread(soil_init_z		,sizeof(float)		,np,soil_init_z_file_ptr))			!=(size_t)np)
            rcode = PERROR;
        else if ((fread(soil_init_temp		,sizeof(float)		,np,soil_init_temp_file_ptr))			!=(size_t)np)
            rcode = PERROR;
        else if ((fread(carbon_pool1		,sizeof(float)		,np,carbon_pool1_file_ptr))			!=(size_t)np)
            rcode = PERROR;
        else if ((fread(carbon_pool2		,sizeof(float)		,np,carbon_pool2_file_ptr))			!=(size_t)np)
            rcode = PERROR;
        else if ((fread(carbon_pool3		,sizeof(float)		,np,carbon_pool3_file_ptr))			!=(size_t)np)
            rcode = PERROR;
        else if ((fread(carbon_pool4		,sizeof(float)		,np,carbon_pool4_file_ptr))			!=(size_t)np)
            rcode = PERROR;
        else if ((fread(carbon_pool5		,sizeof(float)		,np,carbon_pool5_file_ptr))			!=(size_t)np)
            rcode = PERROR;
        else if ((fread(carbon_pool6		,sizeof(float)		,np,carbon_pool6_file_ptr))			!=(size_t)np)
            rcode = PERROR;
        else if ((fread(carbon_pool7		,sizeof(float)		,np,carbon_pool7_file_ptr))			!=(size_t)np)
            rcode = PERROR;
        else if ((fread(carbon_pool8		,sizeof(float)		,np,carbon_pool8_file_ptr))			!=(size_t)np)
            rcode = PERROR;
        else if ((fread(carbon_pool9		,sizeof(float)		,np,carbon_pool9_file_ptr))			!=(size_t)np)
            rcode = PERROR;
        else if ((fread(biomass_pool1		,sizeof(float)		,np,biomass_pool1_file_ptr))			!=(size_t)np)
            rcode = PERROR;
        else if ((fread(biomass_pool2		,sizeof(float)		,np,biomass_pool2_file_ptr))			!=(size_t)np)
            rcode = PERROR;
        else if ((fread(biomass_pool3		,sizeof(float)		,np,biomass_pool3_file_ptr))			!=(size_t)np)
            rcode = PERROR;
        else if ((fread(biomass_pool4		,sizeof(float)		,np,biomass_pool4_file_ptr))			!=(size_t)np)
            rcode = PERROR;
        else if ((fread(soil_depth			,sizeof(float)			,np,soil_depth_file_ptr))			!=(size_t)np)
            rcode = PERROR;
        else if(fread(watershed				,sizeof(unsigned char)	,np,fwatershed)						!=(size_t)np)
            rcode = PERROR;

        for(ii=0; ii<np; ii++)
        {
            prev_snowdensity[ii]=BH_SubParams1->InitialSnowDEN;
            prev_snowdepth[ii]  =BH_SubParams1->InitialSWE*1000.0/prev_snowdensity[ii];
        }

        if (rcode!=PERROR)
        {
            //printf("ok2\n");
            Soil_constructor(pv,soil_texture,soil_surf_k0v,soil_surf_k0h,soil_init_z,soil_init_temp,
                             carbon_pool1,carbon_pool2,carbon_pool3,carbon_pool4,carbon_pool5,carbon_pool6,carbon_pool7,carbon_pool8,carbon_pool9,
                             biomass_pool1,biomass_pool2,biomass_pool3,biomass_pool4,soil_depth,
                             BH_SubParams1->SoilTextureIndexVals,i,soil,watershed,i,buffer_nitrogen);
            DisassembleSoilArray(np,soil_K0_decay_m,soil_b,soil_saturation_suction,soil_saturated_Kv,soil_saturated_Kh,
                                 soil_saturation_deficit,soil_unsaturated_storage,soil_water_table,buff_soil_temp,soil_pondwater,
                                 soil_Max_depth_Z, buff_pool1,buff_pool2,buff_pool3,buff_pool4,buff_pool5,buff_pool6,buff_pool7,buff_pool8,buff_pool9,
                                 bio_pool1,bio_pool2,bio_pool3,bio_pool4,buffer_nitrogen,buffer_CNcd,buffer_CNssd,buffer_CNsmd,
                                 buffer_CNfsd,buffer_CNfmd,buffer_CNsm,buffer_CNm,buffer_CNs,buffer_CNp,buffer_CNw,buffer_CNfr,buffer_CNl,
                                 buff_ST_Ly1,buff_ST_Ly2,buff_ST_Ly3,buff_ST_Ly4,buff_ST_Ly5,buff_ST_Ly6,soil);


            for(ii=0; ii<np; ii++)
            {
                if(soil_water_table[ii]<-10)        //WTD
                    soil_water_table[ii]=0.5;
            }


            if(fwrite(soil_K0_decay_m				,sizeof(float)	,np,soil_K0_decay_m_ptr)
                    !=(size_t)np)
                rcode = PERROR;
            else if(fwrite(soil_saturation_suction		,sizeof(float)	,np,soil_saturation_suction_ptr)
                    !=(size_t)np)
                rcode = PERROR;
            else if(fwrite(soil_saturated_Kv,sizeof(float)	,np,soil_saturated_Kv_ptr)!=(size_t)np)
                rcode = PERROR;
            else if(fwrite(soil_saturated_Kh,sizeof(float)	,np,soil_saturated_Kh_ptr)!=(size_t)np)
                rcode = PERROR;
            else if(fwrite(soil_saturation_deficit,  sizeof(float), np,prev_day_soil_saturation_deficit_ptr)!=(size_t)np)
                rcode = PERROR;
            else if (fwrite(soil_unsaturated_storage,sizeof(float), np,prev_day_soil_unsaturated_storage_ptr)!=(size_t)np)
                rcode = PERROR;
            else if (fwrite(soil_water_table		,sizeof(float)	,np,prev_day_soil_water_table_ptr)!=(size_t)np)      //写了watertable
                rcode = PERROR;
            else if (fwrite(buff_soil_temp,sizeof(float),np,prev_day_soil_temp_ptr)!=(size_t)np)
                rcode = PERROR;
            else if (fwrite(buffer_nitrogen		,sizeof(float)	,np,prev_day_nitrogen_ptr)!=(size_t)np)
                rcode = PERROR;
            else if (fwrite(buffer_CNcd		,sizeof(float)	,np,prev_day_CNcd_ptr) !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(buffer_CNssd	,sizeof(float)	,np,prev_day_CNssd_ptr)!=(size_t)np)
                rcode = PERROR;
            else if (fwrite(buffer_CNsmd	,sizeof(float)	,np,prev_day_CNsmd_ptr)!=(size_t)np)
                rcode = PERROR;
            else if (fwrite(buffer_CNfsd	,sizeof(float)	,np,prev_day_CNfsd_ptr)!=(size_t)np)
                rcode = PERROR;
            else if (fwrite(buffer_CNfmd	,sizeof(float)	,np,prev_day_CNfmd_ptr)!=(size_t)np)
                rcode = PERROR;	/*2nov2006*/
            else if (fwrite(buffer_CNsm		,sizeof(float)	,np,prev_day_CNsm_ptr)!=(size_t)np)
                rcode = PERROR;	/*2nov2006*/
            else if (fwrite(buffer_CNm		,sizeof(float)	,np,prev_day_CNm_ptr)!=(size_t)np)
                rcode = PERROR;	/*2nov2006*/
            else if (fwrite(buffer_CNs		,sizeof(float)	,np,prev_day_CNs_ptr)!=(size_t)np)
                rcode = PERROR;	/*2nov2006*/
            else if (fwrite(buffer_CNp		,sizeof(float)	,np,prev_day_CNp_ptr)!=(size_t)np)
                rcode = PERROR;	/*2nov2006*/
            else if (fwrite(buffer_CNw		,sizeof(float)	,np,prev_day_CNw_ptr)!=(size_t)np)
                rcode = PERROR;	/*2nov2006*/
            else if (fwrite(buffer_CNfr		,sizeof(float)	,np,prev_day_CNfr_ptr)
                     !=(size_t)np)
                rcode = PERROR;	/*2nov2006*/
            else if (fwrite(buffer_CNl		,sizeof(float)	,np,prev_day_CNl_ptr)
                     !=(size_t)np)
                rcode = PERROR;	/*2nov2006*/
            else if (fwrite(buff_ST_Ly1		,sizeof(float)	,np,prev_day_ST_Ly1_ptr)
                     !=(size_t)np)
                rcode = PERROR;	/*2nov2006*/
            else if (fwrite(buff_ST_Ly2		,sizeof(float)	,np,prev_day_ST_Ly2_ptr)
                     !=(size_t)np)
                rcode = PERROR;	/*2nov2006*/
            else if (fwrite(buff_ST_Ly3		,sizeof(float)	,np,prev_day_ST_Ly3_ptr)
                     !=(size_t)np)
                rcode = PERROR;	/*2nov2006*/
            else if (fwrite(buff_ST_Ly4		,sizeof(float)	,np,prev_day_ST_Ly4_ptr)
                     !=(size_t)np)
                rcode = PERROR;	/*2nov2006*/
            else if (fwrite(buff_ST_Ly5		,sizeof(float)	,np,prev_day_ST_Ly5_ptr)
                     !=(size_t)np)
                rcode = PERROR;	/*2nov2006*/
            else if (fwrite(buff_ST_Ly6		,sizeof(float)	,np,prev_day_ST_Ly6_ptr)
                     !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(buff_pool1		,sizeof(float)	,np,prev_day_pool1_ptr)
                     !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(buff_pool2		,sizeof(float)	,np,prev_day_pool2_ptr)
                     !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(buff_pool3		,sizeof(float)	,np,prev_day_pool3_ptr)
                     !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(buff_pool4		,sizeof(float)	,np,prev_day_pool4_ptr)
                     !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(buff_pool5		,sizeof(float)	,np,prev_day_pool5_ptr)
                     !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(buff_pool6		,sizeof(float)	,np,prev_day_pool6_ptr)
                     !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(buff_pool7		,sizeof(float)	,np,prev_day_pool7_ptr)
                     !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(buff_pool8		,sizeof(float)	,np,prev_day_pool8_ptr)
                     !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(buff_pool9		,sizeof(float)	,np,prev_day_pool9_ptr)
                     !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(bio_pool1		,sizeof(float)	,np,prev_day_bio_pool1_ptr)
                     !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(bio_pool2		,sizeof(float)	,np,prev_day_bio_pool2_ptr)
                     !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(bio_pool3		,sizeof(float)	,np,prev_day_bio_pool3_ptr)
                     !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(bio_pool4		,sizeof(float)	,np,prev_day_bio_pool4_ptr)
                     !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(soil_pondwater		,sizeof(float)	,np,prev_day_soil_pondwater_ptr)
                     !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(soil_Max_depth_Z		,sizeof(float)	,np,soil_Max_depth_Z_ptr)
                     !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(soil_b					,sizeof(float)	,np,soil_b_ptr)
                     !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(prev_snowSWE					,sizeof(float)	,np,prev_day_snow_swe_ptr)
                     !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(prev_snowdepth				,sizeof(float)	,np,prev_day_snow_depth_ptr)
                     !=(size_t)np)
                rcode = PERROR;
            else if (fwrite(prev_snowdensity				,sizeof(float)	,np,prev_day_snow_density_ptr)
                     !=(size_t)np)
                rcode = PERROR;
        }

    }//end of loop




    if (soil_init_z_file_ptr)
        fclose(soil_init_z_file_ptr);
    soil_init_z_file_ptr= (FILE*)NULL;

    if (soil_init_temp_file_ptr)
        fclose(soil_init_temp_file_ptr);
    soil_init_temp_file_ptr		= (FILE*)NULL;

    if (carbon_pool1_file_ptr)
        fclose(carbon_pool1_file_ptr);
    carbon_pool1_file_ptr		= (FILE*)NULL;

    if (carbon_pool2_file_ptr)
        fclose(carbon_pool2_file_ptr);
    carbon_pool2_file_ptr		= (FILE*)NULL;

    if (carbon_pool3_file_ptr)
        fclose(carbon_pool3_file_ptr);
    carbon_pool3_file_ptr		= (FILE*)NULL;

    if (carbon_pool4_file_ptr)
        fclose(carbon_pool4_file_ptr);
    carbon_pool4_file_ptr		= (FILE*)NULL;

    if (carbon_pool5_file_ptr)
        fclose(carbon_pool5_file_ptr);
    carbon_pool5_file_ptr		= (FILE*)NULL;

    if (carbon_pool6_file_ptr)
        fclose(carbon_pool6_file_ptr);
    carbon_pool6_file_ptr		= (FILE*)NULL;

    if (carbon_pool7_file_ptr)
        fclose(carbon_pool7_file_ptr);
    carbon_pool7_file_ptr		= (FILE*)NULL;

    if (carbon_pool8_file_ptr)
        fclose(carbon_pool8_file_ptr);
    carbon_pool8_file_ptr		= (FILE*)NULL;

    if (carbon_pool9_file_ptr)
        fclose(carbon_pool9_file_ptr);
    carbon_pool9_file_ptr		= (FILE*)NULL;

    if (biomass_pool1_file_ptr)
        fclose(biomass_pool1_file_ptr);
    biomass_pool1_file_ptr		= (FILE*)NULL;

    if (biomass_pool2_file_ptr)
        fclose(biomass_pool2_file_ptr);
    biomass_pool2_file_ptr		= (FILE*)NULL;

    if (biomass_pool3_file_ptr)
        fclose(biomass_pool3_file_ptr);
    biomass_pool3_file_ptr		= (FILE*)NULL;

    if (biomass_pool4_file_ptr)
        fclose(biomass_pool4_file_ptr);
    biomass_pool4_file_ptr		= (FILE*)NULL;

    if (soil_depth_file_ptr)
        fclose(soil_depth_file_ptr);
    soil_depth_file_ptr			= (FILE*)NULL;

    if (soil_Max_depth_Z_ptr)
        fclose(soil_Max_depth_Z_ptr);
    soil_Max_depth_Z_ptr = (FILE*)NULL;
    if (soil_b_ptr)
        fclose(soil_b_ptr);
    soil_b_ptr = (FILE*)NULL;
    if (fwatershed)
        fclose(fwatershed);
    fwatershed = (FILE*)NULL;

    if (soil_K0_decay_m_ptr)
        fclose(soil_K0_decay_m_ptr);
    soil_K0_decay_m_ptr = (FILE*)NULL;

    if (soil_saturation_suction_ptr)
        fclose(soil_saturation_suction_ptr);
    soil_saturation_suction_ptr = (FILE*)NULL;

    if (soil_saturated_Kv_ptr)
        fclose(soil_saturated_Kv_ptr);
    soil_saturated_Kv_ptr = (FILE*)NULL;

    if (soil_saturated_Kh_ptr)
        fclose(soil_saturated_Kh_ptr);
    soil_saturated_Kh_ptr = (FILE*)NULL;

    if (prev_day_soil_saturation_deficit_ptr)
        fclose(prev_day_soil_saturation_deficit_ptr);
    prev_day_soil_saturation_deficit_ptr = (FILE*)NULL;

    if (prev_day_soil_unsaturated_storage_ptr)
        fclose(prev_day_soil_unsaturated_storage_ptr);
    prev_day_soil_unsaturated_storage_ptr = (FILE*)NULL;

    if (prev_day_soil_water_table_ptr)
        fclose(prev_day_soil_water_table_ptr);
    prev_day_soil_water_table_ptr = (FILE*)NULL;

    if (prev_day_soil_temp_ptr)
        fclose(prev_day_soil_temp_ptr);
    prev_day_soil_temp_ptr = (FILE*)NULL; //2nov2006

    if (prev_day_nitrogen_ptr)
        fclose(prev_day_nitrogen_ptr);
    prev_day_nitrogen_ptr = (FILE*)NULL; //2nov2006

    if (prev_day_CNcd_ptr)
        fclose(prev_day_CNcd_ptr);
    prev_day_CNcd_ptr = (FILE*)NULL;

    if (prev_day_CNssd_ptr)
        fclose(prev_day_CNssd_ptr);
    prev_day_CNssd_ptr = (FILE*)NULL;

    if (prev_day_CNsmd_ptr)
        fclose(prev_day_CNsmd_ptr);
    prev_day_CNsmd_ptr = (FILE*)NULL;

    if (prev_day_CNfsd_ptr)
        fclose(prev_day_CNfsd_ptr);
    prev_day_CNfsd_ptr = (FILE*)NULL;

    if (prev_day_CNfmd_ptr)
        fclose(prev_day_CNfmd_ptr);
    prev_day_CNfmd_ptr = (FILE*)NULL;

    if (prev_day_CNsm_ptr)
        fclose(prev_day_CNsm_ptr);
    prev_day_CNsm_ptr = (FILE*)NULL;

    if (prev_day_CNm_ptr)
        fclose(prev_day_CNm_ptr);
    prev_day_CNm_ptr = (FILE*)NULL;

    if (prev_day_CNs_ptr)
        fclose(prev_day_CNs_ptr);
    prev_day_CNs_ptr = (FILE*)NULL;

    if (prev_day_CNp_ptr)
        fclose(prev_day_CNp_ptr);
    prev_day_CNp_ptr= (FILE*)NULL;

    if (prev_day_CNw_ptr)
        fclose(prev_day_CNw_ptr);
    prev_day_CNw_ptr = (FILE*)NULL;

    if (prev_day_CNfr_ptr)
        fclose(prev_day_CNfr_ptr);
    prev_day_CNfr_ptr = (FILE*)NULL;

    if (prev_day_CNl_ptr)
        fclose(prev_day_CNl_ptr);
    prev_day_CNl_ptr = (FILE*)NULL;


    if (prev_day_ST_Ly1_ptr)
        fclose(prev_day_ST_Ly1_ptr);
    prev_day_ST_Ly1_ptr = (FILE*)NULL;

    if (prev_day_ST_Ly2_ptr)
        fclose(prev_day_ST_Ly2_ptr);
    prev_day_ST_Ly2_ptr = (FILE*)NULL;

    if (prev_day_ST_Ly3_ptr)
        fclose(prev_day_ST_Ly3_ptr);
    prev_day_ST_Ly3_ptr = (FILE*)NULL;

    if (prev_day_ST_Ly4_ptr)
        fclose(prev_day_ST_Ly4_ptr);
    prev_day_ST_Ly4_ptr = (FILE*)NULL;

    if (prev_day_ST_Ly5_ptr)
        fclose(prev_day_ST_Ly5_ptr);
    prev_day_ST_Ly5_ptr = (FILE*)NULL;

    if (prev_day_ST_Ly6_ptr)
        fclose(prev_day_ST_Ly6_ptr);
    prev_day_ST_Ly6_ptr = (FILE*)NULL;

    if (prev_day_pool1_ptr)
        fclose(prev_day_pool1_ptr);
    prev_day_pool1_ptr = (FILE*)NULL;

    if (prev_day_pool2_ptr)
        fclose(prev_day_pool2_ptr);
    prev_day_pool2_ptr = (FILE*)NULL;

    if (prev_day_pool3_ptr)
        fclose(prev_day_pool3_ptr);
    prev_day_pool3_ptr = (FILE*)NULL;

    if (prev_day_pool4_ptr)
        fclose(prev_day_pool4_ptr);
    prev_day_pool4_ptr = (FILE*)NULL;

    if (prev_day_pool5_ptr)
        fclose(prev_day_pool5_ptr);
    prev_day_pool5_ptr = (FILE*)NULL;

    if (prev_day_pool6_ptr)
        fclose(prev_day_pool6_ptr);
    prev_day_pool6_ptr = (FILE*)NULL;

    if (prev_day_pool7_ptr)
        fclose(prev_day_pool7_ptr);
    prev_day_pool7_ptr = (FILE*)NULL;

    if (prev_day_pool8_ptr)
        fclose(prev_day_pool8_ptr);
    prev_day_pool8_ptr = (FILE*)NULL;

    if (prev_day_pool9_ptr)
        fclose(prev_day_pool9_ptr);
    prev_day_pool9_ptr = (FILE*)NULL;

    if (prev_day_bio_pool1_ptr)
        fclose(prev_day_bio_pool1_ptr);
    prev_day_bio_pool1_ptr = (FILE*)NULL;

    if (prev_day_bio_pool2_ptr)
        fclose(prev_day_bio_pool2_ptr);
    prev_day_bio_pool2_ptr = (FILE*)NULL;

    if (prev_day_bio_pool3_ptr)
        fclose(prev_day_bio_pool3_ptr);
    prev_day_bio_pool3_ptr = (FILE*)NULL;

    if (prev_day_bio_pool4_ptr)
        fclose(prev_day_bio_pool4_ptr);
    prev_day_bio_pool4_ptr = (FILE*)NULL;

    if (prev_day_soil_pondwater_ptr) //pond
        fclose(prev_day_soil_pondwater_ptr);//pond
    prev_day_soil_pondwater_ptr = (FILE*)NULL;//pond

    if (prev_day_snow_swe_ptr)
        fclose(prev_day_snow_swe_ptr);
    prev_day_snow_swe_ptr = (FILE*)NULL;

    if (prev_day_snow_depth_ptr)
        fclose(prev_day_snow_depth_ptr);
    prev_day_snow_depth_ptr = (FILE*)NULL;

    if (prev_day_snow_density_ptr)
        fclose(prev_day_snow_density_ptr);
    prev_day_snow_density_ptr = (FILE*)NULL;

    /*=========================END Soil_constructor() block====================================*/
    /*=========================END Soil_constructor() block====================================*/

    // 打开 LC LAI DEM watershed maxdepthZ soilB 常数文件
    if (rcode!=PERROR)
    {
        if(	((lcfile_ptr=fopen(BH_SubParams1->szInFileNameLC									,"rb")) == NULL)
                ||	((fwatershed=fopen(BH_SubParams1->szInFileNameWatershed						,"rb"))	== NULL)
                ||	((Dem_ptr=fopen(BH_SubParams1->szInFileNameDEM								,"rb"))	== NULL)
                ||	((soil_Max_depth_Z_ptr=fopen(BH_SubParams1a->szOutFileNameSoilMaxDepthZ		,"rb"))	== NULL)
                ||	((soil_b_ptr=fopen(BH_SubParams1a->szOutFileNameSoilB						,"rb"))	== NULL)
                ||  ((soil_K0_decay_m_ptr			        =fopen(SoilK0DecayMFileName			,"rb"))	==NULL)
                ||	((soil_saturation_suction_ptr	        =fopen(SoilSatSuctionFileName		,"rb"))	==NULL)
                ||	((soil_saturated_Kv_ptr		    	    =fopen(SoilSatKvFileName			,"rb"))	==NULL)
                ||	((soil_saturated_Kh_ptr		    	    =fopen(SoilSatKhFileName			,"rb"))	==NULL)
          )
            rcode=PERROR;
    }


    /*================================== Begin of Day cycle ===========================*/

    for (jday=pv->jday_start; (jday<=pv->jday_end)&&(rcode!=PERROR); jday++)
    {

        insert_day_number(szPrevDaySoilSatDeficitFileName		,BH_SubParams1a->szOutFileNameSoilSatDeficit			,jday-1);
        insert_day_number(szPrevDaySoilUnsatStorageFileName		,BH_SubParams1a->szOutFileNameSoilUnsatStorage		,jday-1);
        insert_day_number(szPrevDaySoilWaterTableFileName		,BH_SubParams1a->szOutFileNameSoilWaterTable			,jday-1);
        insert_day_number(szPrevDaySoilTempFileName		,BH_SubParams1a->szOutFileNameSoilTemp			,jday-1);
        insert_day_number(szPrevDayST_Ly1FileName			,BH_SubParams1a->szOutFileNameST_Ly1		,jday-1);
        insert_day_number(szPrevDayST_Ly2FileName			,BH_SubParams1a->szOutFileNameST_Ly2		,jday-1);
        insert_day_number(szPrevDayST_Ly3FileName			,BH_SubParams1a->szOutFileNameST_Ly3		,jday-1);
        insert_day_number(szPrevDayST_Ly4FileName			,BH_SubParams1a->szOutFileNameST_Ly4		,jday-1);
        insert_day_number(szPrevDayST_Ly5FileName			,BH_SubParams1a->szOutFileNameST_Ly5		,jday-1);
        insert_day_number(szPrevDayST_Ly6FileName			,BH_SubParams1a->szOutFileNameST_Ly6		,jday-1);
        insert_day_number(szPrevDaySoilPondWaterFileName		,BH_SubParams1a->szOutFileNameSoilPondWater			,jday-1);
        insert_day_number(szPrevDaySWEFileName		,BH_SubParams1a->szOutFileNameSnowswe	    	,jday-1);
        insert_day_number(szPrevDaySnowdepthFileName		,BH_SubParams1a->szOutFileNameSnowdepth			,jday-1);
        insert_day_number(szPrevDaySnowdensityFileName		,BH_SubParams1a->szOutFileNameSnowdensity			,jday-1);

        //this work focus on GPP
        insert_day_number(szPrevDayNitrogenFileName		,BH_SubParams1a->szOutFileNameNitrogen		,pv->jday_start-1);
        insert_day_number(szPrevDayCNcdFileName			,BH_SubParams1a->szOutFileNameCNcd			,pv->jday_start-1);
        insert_day_number(szPrevDayCNssdFileName		,BH_SubParams1a->szOutFileNameCNssd			,pv->jday_start-1);
        insert_day_number(szPrevDayCNsmdFileName		,BH_SubParams1a->szOutFileNameCNsmd			,pv->jday_start-1);
        insert_day_number(szPrevDayCNfsdFileName		,BH_SubParams1a->szOutFileNameCNfsd			,pv->jday_start-1);
        insert_day_number(szPrevDayCNfmdFileName		,BH_SubParams1a->szOutFileNameCNfmd			,pv->jday_start-1);
        insert_day_number(szPrevDayCNsmFileName			,BH_SubParams1a->szOutFileNameCNsm			,pv->jday_start-1);
        insert_day_number(szPrevDayCNmFileName			,BH_SubParams1a->szOutFileNameCNm			,pv->jday_start-1);
        insert_day_number(szPrevDayCNsFileName			,BH_SubParams1a->szOutFileNameCNs			,pv->jday_start-1);
        insert_day_number(szPrevDayCNpFileName			,BH_SubParams1a->szOutFileNameCNp			,pv->jday_start-1);
        insert_day_number(szPrevDayCNwFileName			,BH_SubParams1a->szOutFileNameCNw			,pv->jday_start-1);
        insert_day_number(szPrevDayCNfrFileName			,BH_SubParams1a->szOutFileNameCNfr			,pv->jday_start-1);
        insert_day_number(szPrevDayCNlFileName			,BH_SubParams1a->szOutFileNameCNl			,pv->jday_start-1);
        insert_day_number(szPrevDayPool1FileName		,BH_SubParams1a->szOutFileNamePool1			,pv->jday_start-1);
        insert_day_number(szPrevDayPool2FileName		,BH_SubParams1a->szOutFileNamePool2			,pv->jday_start-1);
        insert_day_number(szPrevDayPool3FileName		,BH_SubParams1a->szOutFileNamePool3			,pv->jday_start-1);
        insert_day_number(szPrevDayPool4FileName		,BH_SubParams1a->szOutFileNamePool4			,pv->jday_start-1);
        insert_day_number(szPrevDayPool5FileName		,BH_SubParams1a->szOutFileNamePool5			,pv->jday_start-1);
        insert_day_number(szPrevDayPool6FileName		,BH_SubParams1a->szOutFileNamePool6			,pv->jday_start-1);
        insert_day_number(szPrevDayPool7FileName		,BH_SubParams1a->szOutFileNamePool7			,pv->jday_start-1);
        insert_day_number(szPrevDayPool8FileName		,BH_SubParams1a->szOutFileNamePool8			,pv->jday_start-1);
        insert_day_number(szPrevDayPool9FileName		,BH_SubParams1a->szOutFileNamePool9			,pv->jday_start-1);
        insert_day_number(szPrevDayBiomassPool1FileName		,BH_SubParams1a->szOutFileNameB_Pool1	,pv->jday_start-1);
        insert_day_number(szPrevDayBiomassPool2FileName		,BH_SubParams1a->szOutFileNameB_Pool2	,pv->jday_start-1);
        insert_day_number(szPrevDayBiomassPool3FileName		,BH_SubParams1a->szOutFileNameB_Pool3	,pv->jday_start-1);
        insert_day_number(szPrevDayBiomassPool4FileName		,BH_SubParams1a->szOutFileNameB_Pool4	,pv->jday_start-1);
//  原始注释
//        insert_day_number(szPrevDayNitrogenFileName		,BH_SubParams1a->szOutFileNameNitrogen			,jday-1);
//        insert_day_number(szPrevDayCNcdFileName			,BH_SubParams1a->szOutFileNameCNcd			,jday-1);
//        insert_day_number(szPrevDayCNssdFileName		,BH_SubParams1a->szOutFileNameCNssd			,jday-1);
//        insert_day_number(szPrevDayCNsmdFileName		,BH_SubParams1a->szOutFileNameCNsmd			,jday-1);
//        insert_day_number(szPrevDayCNfsdFileName		,BH_SubParams1a->szOutFileNameCNfsd			,jday-1);
//        insert_day_number(szPrevDayCNfmdFileName		,BH_SubParams1a->szOutFileNameCNfmd			,jday-1);
//        insert_day_number(szPrevDayCNsmFileName			,BH_SubParams1a->szOutFileNameCNsm				,jday-1);
//        insert_day_number(szPrevDayCNmFileName			,BH_SubParams1a->szOutFileNameCNm				,jday-1);
//        insert_day_number(szPrevDayCNsFileName			,BH_SubParams1a->szOutFileNameCNs				,jday-1);
//        insert_day_number(szPrevDayCNpFileName			,BH_SubParams1a->szOutFileNameCNp				,jday-1);
//        insert_day_number(szPrevDayCNwFileName			,BH_SubParams1a->szOutFileNameCNw				,jday-1);
//        insert_day_number(szPrevDayCNfrFileName			,BH_SubParams1a->szOutFileNameCNfr				,jday-1);
//        insert_day_number(szPrevDayCNlFileName			,BH_SubParams1a->szOutFileNameCNl				,jday-1);
//        insert_day_number(szPrevDayPool1FileName		,BH_SubParams1a->szOutFileNamePool1			,jday-1);
//        insert_day_number(szPrevDayPool2FileName		,BH_SubParams1a->szOutFileNamePool2			,jday-1);
//        insert_day_number(szPrevDayPool3FileName		,BH_SubParams1a->szOutFileNamePool3			,jday-1);
//        insert_day_number(szPrevDayPool4FileName		,BH_SubParams1a->szOutFileNamePool4			,jday-1);
//        insert_day_number(szPrevDayPool5FileName		,BH_SubParams1a->szOutFileNamePool5			,jday-1);
//        insert_day_number(szPrevDayPool6FileName		,BH_SubParams1a->szOutFileNamePool6			,jday-1);
//        insert_day_number(szPrevDayPool7FileName		,BH_SubParams1a->szOutFileNamePool7			,jday-1);
//        insert_day_number(szPrevDayPool8FileName		,BH_SubParams1a->szOutFileNamePool8			,jday-1);
//        insert_day_number(szPrevDayPool9FileName		,BH_SubParams1a->szOutFileNamePool9			,jday-1);
//        insert_day_number(szPrevDayBiomassPool1FileName		,BH_SubParams1a->szOutFileNameB_Pool1			,jday-1);
//        insert_day_number(szPrevDayBiomassPool2FileName		,BH_SubParams1a->szOutFileNameB_Pool2			,jday-1);
//        insert_day_number(szPrevDayBiomassPool3FileName		,BH_SubParams1a->szOutFileNameB_Pool3			,jday-1);
//        insert_day_number(szPrevDayBiomassPool4FileName		,BH_SubParams1a->szOutFileNameB_Pool4			,jday-1);
//  原始注释
        insert_day_number(szCurrDaySoilSatDeficitFileName		,BH_SubParams1a->szOutFileNameSoilSatDeficit		,jday);
        insert_day_number(szCurrDaySoilUnsatStorageFileName		,BH_SubParams1a->szOutFileNameSoilUnsatStorage		,jday);
        insert_day_number(szCurrDaySoilWaterTableFileName		,BH_SubParams1a->szOutFileNameSoilWaterTable		,jday);
        insert_day_number(szCurrDaySoilTempFileName		,BH_SubParams1a->szOutFileNameSoilTemp		,jday);
        insert_day_number(szCurrDayNitrogenFileName		,BH_SubParams1a->szOutFileNameNitrogen		,jday);
        insert_day_number(szCurrDayCNcdFileName		,BH_SubParams1a->szOutFileNameCNcd		,jday);
        insert_day_number(szCurrDayCNssdFileName		,BH_SubParams1a->szOutFileNameCNssd		,jday);
        insert_day_number(szCurrDayCNsmdFileName		,BH_SubParams1a->szOutFileNameCNsmd		,jday);
        insert_day_number(szCurrDayCNfsdFileName		,BH_SubParams1a->szOutFileNameCNfsd		,jday);
        insert_day_number(szCurrDayCNfmdFileName		,BH_SubParams1a->szOutFileNameCNfmd		,jday);
        insert_day_number(szCurrDayCNsmFileName		,BH_SubParams1a->szOutFileNameCNsm		,jday);
        insert_day_number(szCurrDayCNmFileName		,BH_SubParams1a->szOutFileNameCNm		,jday);
        insert_day_number(szCurrDayCNsFileName		,BH_SubParams1a->szOutFileNameCNs		,jday);
        insert_day_number(szCurrDayCNpFileName		,BH_SubParams1a->szOutFileNameCNp		,jday);
        insert_day_number(szCurrDayCNwFileName		,BH_SubParams1a->szOutFileNameCNw		,jday);
        insert_day_number(szCurrDayCNfrFileName		,BH_SubParams1a->szOutFileNameCNfr		,jday);
        insert_day_number(szCurrDayCNlFileName		,BH_SubParams1a->szOutFileNameCNl		,jday);
        insert_day_number(szCurrDayPool1FileName		,BH_SubParams1a->szOutFileNamePool1		,jday);
        insert_day_number(szCurrDayPool2FileName		,BH_SubParams1a->szOutFileNamePool2		,jday);
        insert_day_number(szCurrDayPool3FileName		,BH_SubParams1a->szOutFileNamePool3		,jday);
        insert_day_number(szCurrDayPool4FileName		,BH_SubParams1a->szOutFileNamePool4		,jday);
        insert_day_number(szCurrDayPool5FileName		,BH_SubParams1a->szOutFileNamePool5		,jday);
        insert_day_number(szCurrDayPool6FileName		,BH_SubParams1a->szOutFileNamePool6		,jday);
        insert_day_number(szCurrDayPool7FileName		,BH_SubParams1a->szOutFileNamePool7		,jday);
        insert_day_number(szCurrDayPool8FileName		,BH_SubParams1a->szOutFileNamePool8		,jday);
        insert_day_number(szCurrDayPool9FileName		,BH_SubParams1a->szOutFileNamePool9		,jday);
        insert_day_number(szCurrDayBiomassPool1FileName		,BH_SubParams1a->szOutFileNameB_Pool1		,jday);
        insert_day_number(szCurrDayBiomassPool2FileName		,BH_SubParams1a->szOutFileNameB_Pool2		,jday);
        insert_day_number(szCurrDayBiomassPool3FileName		,BH_SubParams1a->szOutFileNameB_Pool3		,jday);
        insert_day_number(szCurrDayBiomassPool4FileName		,BH_SubParams1a->szOutFileNameB_Pool4		,jday);

        insert_day_number(szCurrDaySoilPondWaterFileName		,BH_SubParams1a->szOutFileNameSoilPondWater		,jday);
        insert_day_number(szCurrDaySWEFileName		,BH_SubParams1a->szOutFileNameSnowswe	    	,jday);
        insert_day_number(szCurrDaySnowdepthFileName	    	,BH_SubParams1a->szOutFileNameSnowdepth			,jday);
        insert_day_number(szCurrDaySnowdensityFileName		,BH_SubParams1a->szOutFileNameSnowdensity			,jday);
        insert_day_number(szCurrDaySoilCapillaryRiseFileName	,BH_SubParams1a->szOutFileNameSoilCapillaryRise		,jday);
        insert_day_number(szCurrDaySoilPercolationFileName		,BH_SubParams1a->szOutFileNameSoilPercolation			,jday);
        insert_day_number(szClimateDailyFileNameRAD_r	,BH_SubParams1a->szOutFileNameClimateRAD_r	,jday);
        insert_day_number(szClimateDailyFileNameRAD_f	,BH_SubParams1a->szOutFileNameClimateRAD_f	,jday);
        insert_day_number(szClimateDailyFileNameTI				,BH_SubParams1a->szOutFileNameClimateTi			,jday);
        insert_day_number(szClimateDailyFileNameTM				,BH_SubParams1a->szOutFileNameClimateTm				,jday);
        insert_day_number(szClimateDailyFileNamePREC			,BH_SubParams1a->szOutFileNameClimatePrec				,jday);
        insert_day_number(szClimateDailyFileNameDEW				,BH_SubParams1a->szOutFileNameClimateDew				,jday);
        insert_day_number(szClimateDailyFileNameWIND	,BH_SubParams1a->szOutFileNameClimateWind	,jday);
        insert_day_number(szCanopyDailyFileNameET		,BH_SubParams1a->szOutFileNameCanopyET	            	,jday);
        insert_day_number(szCanopyDailyFileNameEvaporation		,BH_SubParams1a->szOutFileNameCanopyEvaporation		,jday);
        insert_day_number(szCanopyDailyFileNameTranspUnsat		,BH_SubParams1a->szOutFileNameCanopyTranspUnsat		,jday);
        insert_day_number(szCanopyDailyFileNameTranspSat		,BH_SubParams1a->szOutFileNameCanopyTranspSat			,jday);
        insert_day_number(szCanopyDailyFileNameIntercepted		,BH_SubParams1a->szOutFileNameCanopyIntercepted		,jday);
        insert_day_number(szCanopyDailyFileNameLitterEvaporation,BH_SubParams1a->szOutFileNameCanopyLitterEvaporation	,jday);
        insert_day_number(szCanopyDailyFileNameMossTransp		,BH_SubParams1a->szOutFileNameCanopyMossTransp	,jday);
        insert_day_number(szCanopyDailyFileNameSoilEvaporation	,BH_SubParams1a->szOutFileNameCanopySoilEvaporation	,jday);
        insert_day_number(szCanopyDailyFileNameUT	,BH_SubParams1a->szOutFileNameCanopyUT	,jday);
        insert_day_number(szCanopyDailyFileNameStomata	,BH_SubParams1a->szOutFileNameCanopyStomata	,jday);
        insert_day_number(szEnergyDailyFileNameNRFlux   		,BH_SubParams1a->szOutFileNameNRFlux		,jday);
        insert_day_number(szEnergyDailyFileNameSensibleHeatFlux,BH_SubParams1a->szOutFileNameSensibleHeatFlux,jday);
        insert_day_number(szEnergyDailyFileNameLatentHeatFlux	,BH_SubParams1a->szOutFileNameLatentHeatFlux,jday);
        insert_day_number(szGPPDailyFileName                	,BH_SubParams1a->szOutFileNameGPP						,jday);
        insert_day_number(szNPPDailyFileName	,BH_SubParams1a->szOutFileNameNPP						,jday);
        insert_day_number(szNEPDailyFileName                	,BH_SubParams1a->szOutFileNameNEP						,jday);
        insert_day_number(szRaDailyFileName		,BH_SubParams1a->szOutFileNameRa						,jday);
        insert_day_number(szRhDailyFileName		,BH_SubParams1a->szOutFileNameRh						,jday);
        insert_day_number(szWaterInFileName	,BH_SubParams1a->szOutFileNameWaterIn,jday);
        insert_day_number(szRunoffDailyFileNameTotal		,BH_SubParams1a->szOutFileNameRunoffTotal				,jday);
        insert_day_number(szRunoffDailyFileNameBaseflow		,BH_SubParams1a->szOutFileNameRunoffBaseflow			,jday);
        insert_day_number(szRunoffDailyFileNameTotalInflow	,BH_SubParams1a->szOutFileNameRunoffTotalInflow			,jday);
        insert_day_number(szRunoffDailyFileNameTotalOutflow	,BH_SubParams1a->szOutFileNameRunoffTotalOutflow		,jday);

        insert_day_number(szCurrDayST_Ly1FileName		,BH_SubParams1a->szOutFileNameST_Ly1		,jday);
        insert_day_number(szCurrDayST_Ly2FileName		,BH_SubParams1a->szOutFileNameST_Ly2		,jday);
        insert_day_number(szCurrDayST_Ly3FileName		,BH_SubParams1a->szOutFileNameST_Ly3		,jday);
        insert_day_number(szCurrDayST_Ly4FileName		,BH_SubParams1a->szOutFileNameST_Ly4		,jday);
        insert_day_number(szCurrDayST_Ly5FileName		,BH_SubParams1a->szOutFileNameST_Ly5		,jday);
        insert_day_number(szCurrDayST_Ly6FileName		,BH_SubParams1a->szOutFileNameST_Ly6		,jday);


        modisday=floor((jday-1)/8)*8+1;
        insert_day_number(szClimateDailyLAI	,BH_SubParams1->szInFileNameLAI	,modisday);
        //printf("rcode1:%d\n",rcode);

        if(	((prev_day_soil_saturation_deficit_ptr=fopen(szPrevDaySoilSatDeficitFileName,"rb"))	==NULL)
                ||	((prev_day_soil_unsaturated_storage_ptr=fopen(szPrevDaySoilUnsatStorageFileName,"rb"))	==NULL)
                ||	((prev_day_soil_water_table_ptr=fopen(szPrevDaySoilWaterTableFileName,"rb"))	==NULL)
                ||	((prev_day_soil_temp_ptr=fopen(szPrevDaySoilTempFileName,"rb"))==NULL)
                ||	((prev_day_nitrogen_ptr=fopen(szPrevDayNitrogenFileName,"rb"))==NULL)
                ||	((prev_day_CNcd_ptr		=fopen(szPrevDayCNcdFileName							,"rb"))	==NULL)
                ||	((prev_day_CNssd_ptr	=fopen(szPrevDayCNssdFileName							,"rb"))	==NULL)
                ||	((prev_day_CNsmd_ptr	=fopen(szPrevDayCNsmdFileName							,"rb"))	==NULL)
                ||	((prev_day_CNfsd_ptr	=fopen(szPrevDayCNfsdFileName							,"rb"))	==NULL)
                ||	((prev_day_CNfmd_ptr	=fopen(szPrevDayCNfmdFileName							,"rb"))	==NULL)
                ||	((prev_day_CNsm_ptr		=fopen(szPrevDayCNsmFileName							,"rb"))	==NULL)
                ||	((prev_day_CNm_ptr		=fopen(szPrevDayCNmFileName								,"rb"))	==NULL)
                ||	((prev_day_CNs_ptr		=fopen(szPrevDayCNsFileName								,"rb"))	==NULL)
                ||	((prev_day_CNp_ptr		=fopen(szPrevDayCNpFileName								,"rb"))	==NULL)
                ||	((prev_day_CNw_ptr		=fopen(szPrevDayCNwFileName								,"rb"))	==NULL)
                ||	((prev_day_CNfr_ptr		=fopen(szPrevDayCNfrFileName							,"rb"))	==NULL)
                ||	((prev_day_CNl_ptr		=fopen(szPrevDayCNlFileName								,"rb"))	==NULL)
                ||	((prev_day_ST_Ly1_ptr		=fopen(szPrevDayST_Ly1FileName						,"rb"))	==NULL)
                ||	((prev_day_ST_Ly2_ptr		=fopen(szPrevDayST_Ly2FileName						,"rb"))	==NULL)
                ||	((prev_day_ST_Ly3_ptr		=fopen(szPrevDayST_Ly3FileName						,"rb"))	==NULL)
                ||	((prev_day_ST_Ly4_ptr		=fopen(szPrevDayST_Ly4FileName						,"rb"))	==NULL)
                ||	((prev_day_ST_Ly5_ptr		=fopen(szPrevDayST_Ly5FileName						,"rb"))	==NULL)
                ||	((prev_day_ST_Ly6_ptr		=fopen(szPrevDayST_Ly6FileName						,"rb"))	==NULL)
                ||	((prev_day_pool1_ptr				=fopen(szPrevDayPool1FileName							,"rb"))	==NULL)
                ||	((prev_day_pool2_ptr				=fopen(szPrevDayPool2FileName							,"rb"))	==NULL)
                ||	((prev_day_pool3_ptr				=fopen(szPrevDayPool3FileName							,"rb"))	==NULL)
                ||	((prev_day_pool4_ptr				=fopen(szPrevDayPool4FileName							,"rb"))	==NULL)
                ||	((prev_day_pool5_ptr				=fopen(szPrevDayPool5FileName							,"rb"))	==NULL)
                ||	((prev_day_pool6_ptr				=fopen(szPrevDayPool6FileName							,"rb"))	==NULL)
                ||	((prev_day_pool7_ptr				=fopen(szPrevDayPool7FileName							,"rb"))	==NULL)
                ||	((prev_day_pool8_ptr				=fopen(szPrevDayPool8FileName							,"rb"))	==NULL)
                ||	((prev_day_pool9_ptr				=fopen(szPrevDayPool9FileName							,"rb"))	==NULL)
                ||	((prev_day_bio_pool1_ptr				=fopen(szPrevDayBiomassPool1FileName							,"rb"))	==NULL)
                ||	((prev_day_bio_pool2_ptr				=fopen(szPrevDayBiomassPool2FileName							,"rb"))	==NULL)
                ||	((prev_day_bio_pool3_ptr				=fopen(szPrevDayBiomassPool3FileName							,"rb"))	==NULL)
                ||	((prev_day_bio_pool4_ptr				=fopen(szPrevDayBiomassPool4FileName							,"rb"))	==NULL)
                ||	((prev_day_soil_pondwater_ptr			=fopen(szPrevDaySoilPondWaterFileName							,"rb"))	==NULL)
                ||	((prev_day_snow_swe_ptr      	        =fopen(szPrevDaySWEFileName						,"rb"))	==NULL)
                ||	((prev_day_snow_depth_ptr		        =fopen(szPrevDaySnowdepthFileName							,"rb"))	==NULL)
                ||	((prev_day_snow_density_ptr		        =fopen(szPrevDaySnowdensityFileName							,"rb"))	==NULL)
                ||	((waterin_ptr   			            =fopen(szWaterInFileName							,"wb"))	==NULL)

                ||	((curr_day_soil_saturation_deficit_ptr	=fopen(szCurrDaySoilSatDeficitFileName							,"wb"))	==NULL)
                ||	((curr_day_soil_unsaturated_storage_ptr	=fopen(szCurrDaySoilUnsatStorageFileName						,"wb"))	==NULL)
                ||	((curr_day_soil_water_table_ptr			=fopen(szCurrDaySoilWaterTableFileName							,"wb"))	==NULL)
                ||	((curr_day_soil_temp_ptr				=fopen(szCurrDaySoilTempFileName							,"wb"))	==NULL)
                ||	((curr_day_ST_Ly1_ptr		=fopen(szCurrDayST_Ly1FileName								,"wb"))	==NULL)
                ||	((curr_day_ST_Ly2_ptr		=fopen(szCurrDayST_Ly2FileName								,"wb"))	==NULL)
                ||	((curr_day_ST_Ly3_ptr		=fopen(szCurrDayST_Ly3FileName								,"wb"))	==NULL)
                ||	((curr_day_ST_Ly4_ptr		=fopen(szCurrDayST_Ly4FileName								,"wb"))	==NULL)
                ||	((curr_day_ST_Ly5_ptr		=fopen(szCurrDayST_Ly5FileName								,"wb"))	==NULL)
                ||	((curr_day_ST_Ly6_ptr		=fopen(szCurrDayST_Ly6FileName								,"wb"))	==NULL)

// //取消注释
//                ||	((curr_day_nitrogen_ptr				=fopen(szCurrDayNitrogenFileName							,"wb"))	==NULL)
//                ||	((curr_day_CNcd_ptr		=fopen(szCurrDayCNcdFileName							,"wb"))	==NULL)
//                ||	((curr_day_CNssd_ptr	=fopen(szCurrDayCNssdFileName							,"wb"))	==NULL)
//                ||	((curr_day_CNsmd_ptr	=fopen(szCurrDayCNsmdFileName							,"wb"))	==NULL)
//                ||	((curr_day_CNfsd_ptr	=fopen(szCurrDayCNfsdFileName							,"wb"))	==NULL)
//                ||	((curr_day_CNfmd_ptr	=fopen(szCurrDayCNfmdFileName							,"wb"))	==NULL)
//                ||	((curr_day_CNsm_ptr		=fopen(szCurrDayCNsmFileName							,"wb"))	==NULL)
//                ||	((curr_day_CNm_ptr		=fopen(szCurrDayCNmFileName								,"wb"))	==NULL)
//                ||	((curr_day_CNs_ptr		=fopen(szCurrDayCNsFileName								,"wb"))	==NULL)
//                ||	((curr_day_CNp_ptr		=fopen(szCurrDayCNpFileName								,"wb"))	==NULL)
//                ||	((curr_day_CNw_ptr		=fopen(szCurrDayCNwFileName								,"wb"))	==NULL)
//                ||	((curr_day_CNfr_ptr		=fopen(szCurrDayCNfrFileName							,"wb"))	==NULL)
//                ||	((curr_day_CNl_ptr		=fopen(szCurrDayCNlFileName								,"wb"))	==NULL)
//                ||	((curr_day_pool1_ptr				=fopen(szCurrDayPool1FileName							,"wb"))	==NULL)
//                ||	((curr_day_pool2_ptr				=fopen(szCurrDayPool2FileName							,"wb"))	==NULL)
//                ||	((curr_day_pool3_ptr				=fopen(szCurrDayPool3FileName							,"wb"))	==NULL)
//                ||	((curr_day_pool4_ptr				=fopen(szCurrDayPool4FileName							,"wb"))	==NULL)
//                ||	((curr_day_pool5_ptr				=fopen(szCurrDayPool5FileName							,"wb"))	==NULL)
//                ||	((curr_day_pool6_ptr				=fopen(szCurrDayPool6FileName							,"wb"))	==NULL)
//                ||	((curr_day_pool7_ptr				=fopen(szCurrDayPool7FileName							,"wb"))	==NULL)
//                ||	((curr_day_pool8_ptr				=fopen(szCurrDayPool8FileName							,"wb"))	==NULL)
//                ||	((curr_day_pool9_ptr				=fopen(szCurrDayPool9FileName							,"wb"))	==NULL)
//                ||	((curr_day_bio_pool1_ptr				=fopen(szCurrDayBiomassPool1FileName							,"wb"))	==NULL)
//                ||	((curr_day_bio_pool2_ptr				=fopen(szCurrDayBiomassPool2FileName							,"wb"))	==NULL)
//                ||	((curr_day_bio_pool3_ptr				=fopen(szCurrDayBiomassPool3FileName							,"wb"))	==NULL)
//                ||	((curr_day_bio_pool4_ptr				=fopen(szCurrDayBiomassPool4FileName							,"wb"))	==NULL)
//  //取消注释

                ||	((curr_day_soil_pondwater_ptr			=fopen(szCurrDaySoilPondWaterFileName							,"wb"))	==NULL)
                ||	((curr_day_snow_swe_ptr             	=fopen(szCurrDaySWEFileName						,"wb"))	==NULL)
                ||	((curr_day_snow_depth_ptr		        =fopen(szCurrDaySnowdepthFileName							,"wb"))	==NULL)
                ||	((curr_day_snow_density_ptr		        =fopen(szCurrDaySnowdensityFileName							,"wb"))	==NULL)
                ||	((curr_day_soil_capillary_rise_ptr		=fopen(szCurrDaySoilCapillaryRiseFileName						,"wb"))	==NULL)
                ||	((curr_day_soil_percolation_ptr			=fopen(szCurrDaySoilPercolationFileName							,"wb"))	==NULL)
                ||	((canopy_ET_ptr			            	=fopen(szCanopyDailyFileNameET					,"wb")) ==NULL)
                ||	((canopy_evaporation_ptr				=fopen(szCanopyDailyFileNameEvaporation							,"wb")) ==NULL)
                ||	((canopy_transpiration_unsat_ptr		=fopen(szCanopyDailyFileNameTranspUnsat							,"wb")) ==NULL)
                ||	((canopy_transpiration_sat_ptr			=fopen(szCanopyDailyFileNameTranspSat							,"wb")) ==NULL)
                ||	((canopy_intercepted_ptr				=fopen(szCanopyDailyFileNameIntercepted							,"wb")) ==NULL)
                ||	((canopy_litter_evaporation_ptr			=fopen(szCanopyDailyFileNameLitterEvaporation					,"wb")) ==NULL)
                ||	((canopy_moss_transpiration_ptr			=fopen(szCanopyDailyFileNameMossTransp							,"wb")) ==NULL)
                ||	((canopy_soil_evaporation_ptr			=fopen(szCanopyDailyFileNameSoilEvaporation						,"wb")) ==NULL)
                ||	((canopy_UT_ptr			                =fopen(szCanopyDailyFileNameUT						,"wb")) ==NULL)
                ||	((canopy_Stomata_ptr			        =fopen(szCanopyDailyFileNameStomata					,"wb")) ==NULL)
                ||	(( NRFlux_ptr			        =fopen(szEnergyDailyFileNameNRFlux						,"wb")) ==NULL)
                ||	(( sensibleHeatFlux_ptr			=fopen(szEnergyDailyFileNameSensibleHeatFlux			,"wb")) ==NULL)
                ||	(( latentHeatFlux_ptr			=fopen(szEnergyDailyFileNameLatentHeatFlux				,"wb")) ==NULL)
                ||  ((Daily_GPP_ptr=fopen(szGPPDailyFileName				,"wb"))== NULL)
                ||  ((Daily_NPP_ptr=fopen(szNPPDailyFileName				,"wb"))== NULL)
                ||  ((Daily_Ra_ptr =fopen(szRaDailyFileName				,"wb"))== NULL)
                ||  ((Daily_Rh_ptr =fopen(szRhDailyFileName				,"wb"))== NULL)
                ||  ((runoff_total_ptr			=fopen(szRunoffDailyFileNameTotal		,"wb"))== NULL)
                ||	((runoff_baseflow_ptr		=fopen(szRunoffDailyFileNameBaseflow	,"wb"))== NULL)
                ||	((runoff_total_inflow_ptr	=fopen(szRunoffDailyFileNameTotalInflow	,"wb"))== NULL)
                ||	((Daily_NEP_ptr				=fopen(szNEPDailyFileName					,"wb"))== NULL)
                ||	((runoff_total_outflow_ptr	=fopen(szRunoffDailyFileNameTotalOutflow,"wb"))== NULL)
                ||	((laifile_ptr						=fopen(szClimateDailyLAI								,"rb")) ==NULL)
                ||	((climate_rad_r_ptr						=fopen(szClimateDailyFileNameRAD_r								,"rb")) ==NULL)
                ||	((climate_rad_f_ptr						=fopen(szClimateDailyFileNameRAD_f								,"rb")) ==NULL)
                ||	((climate_ti_ptr						=fopen(szClimateDailyFileNameTI									,"rb")) ==NULL)
                ||	((climate_tm_ptr						=fopen(szClimateDailyFileNameTM									,"rb")) ==NULL)
                ||	((climate_prec_ptr						=fopen(szClimateDailyFileNamePREC								,"rb")) ==NULL)
                ||	((climate_dew_ptr						=fopen(szClimateDailyFileNameDEW								,"rb")) ==NULL)
                ||	((climate_wind_ptr						=fopen(szClimateDailyFileNameWIND								,"rb")) ==NULL)

          )
            rcode = PERROR;


        //***********************START OF BEPS PART EXECUTION**********************************************
        //***********************START OF BEPS PART EXECUTION**********************************************
        fseek(soil_texture_file_ptr,0,SEEK_SET);

        if (rcode != PERROR)
        {
            if (	((fseek(lcfile_ptr               	,0,SEEK_SET))!=0)//fseek函数运行成功返回零，否则返回非零
                    ||	((fseek(fwatershed	,0,SEEK_SET))!=0)
                    ||	((fseek(laifile_ptr	,0,SEEK_SET))!=0)
                    ||	((fseek(soil_K0_decay_m_ptr	,0,SEEK_SET))!=0)              //这几个土壤项可能需要注意一下
                    ||	((fseek(soil_saturation_suction_ptr	,0,SEEK_SET))!=0)
                    ||	((fseek(soil_saturated_Kv_ptr	,0,SEEK_SET))!=0)
                    ||	((fseek(soil_saturated_Kh_ptr	,0,SEEK_SET))!=0)
               )
                rcode = PERROR;
        }


        //*--------------------------------For each line in Study Area--------------------------------
        //*--------------------------------For each line in Study Area--------------------------------
        //printf("ok2");
        printf("Running Ecophysiology and Photosynthesis：day %d \n",jday);
        //printf("U N N O R M A !!!");
        for (lin=0; (lin<nl)&&(rcode!=PERROR); lin++)
        {
            line=lin;
            if (rcode != PERROR)
            {
                for (pix=0; pix<np; pix++)
                {
                    lon[pix] = pv->ULLong-((pv->ULLong-pv->LRLong)/(float) np)*(pix+1);
                    lat[pix] =  pv->ULLat-((pv->ULLat-pv->LRLat)/   (float) nl)*(lin+1);
                }

                //Clean memory:
                memset(Daily_GPP	,0,np*sizeof(float));
                memset(Daily_NPP	,0,np*sizeof(float));
                memset(Daily_Ra 	,0,np*sizeof(float));
                memset(Daily_Rh 	,0,np*sizeof(float));
                memset(pFloatOutput	,0,np*sizeof(float));
                memset(waterin  	,0,np*sizeof(float));

                for(pix=0; pix<np; pix++)
                    zeroxx(pix,xSoil,xx);
            }

            //读取土壤相关数据文件
            if (rcode != PERROR)
            {
                if ((fread(soil_texture	,     sizeof(char)	,np,soil_texture_file_ptr) !=(size_t)np)
                        || (fread(soil_unsaturated_storage	,sizeof(float)	,np,prev_day_soil_unsaturated_storage_ptr)!=(size_t)np)
                        || (fread(soil_water_table		,sizeof(float)	,np,prev_day_soil_water_table_ptr)!=(size_t)np)
                        || (fread(buff_soil_temp		,sizeof(float)	,np,prev_day_soil_temp_ptr)!=(size_t)np)
                        || (fread(buffer_nitrogen	,sizeof(float)	,np,prev_day_nitrogen_ptr)!=(size_t)np)
                        || (fread(buffer_CNcd	,sizeof(float)	,np,prev_day_CNcd_ptr)!=(size_t)np)
                        || (fread(buffer_CNssd	,sizeof(float)	,np,prev_day_CNssd_ptr)!=(size_t)np)
                        || (fread(buffer_CNsmd	,sizeof(float)	,np,prev_day_CNsmd_ptr)!=(size_t)np)
                        || (fread(buffer_CNfsd	,sizeof(float)	,np,prev_day_CNfsd_ptr)!=(size_t)np)
                        || (fread(buffer_CNfmd	,sizeof(float)	,np,prev_day_CNfmd_ptr)!=(size_t)np)
                        || (fread(buffer_CNsm	,sizeof(float)	,np,prev_day_CNsm_ptr)!=(size_t)np)
                        || (fread(buffer_CNm	,sizeof(float)	,np,prev_day_CNm_ptr)!=(size_t)np)
                        || (fread(buffer_CNs	,sizeof(float)	,np,prev_day_CNs_ptr)!=(size_t)np)
                        || (fread(buffer_CNp	,sizeof(float)	,np,prev_day_CNp_ptr)!=(size_t)np)
                        || (fread(buffer_CNw	,sizeof(float)	,np,prev_day_CNw_ptr)!=(size_t)np)
                        || (fread(buffer_CNfr	,sizeof(float)	,np,prev_day_CNfr_ptr)!=(size_t)np)
                        || (fread(buffer_CNl	,sizeof(float)	,np,prev_day_CNl_ptr)!=(size_t)np)
                        || (fread(buff_ST_Ly1	,sizeof(float)	,np,prev_day_ST_Ly1_ptr) !=(size_t)np)
                        || (fread(buff_ST_Ly2	,sizeof(float)	,np,prev_day_ST_Ly2_ptr)!=(size_t)np)
                        || (fread(buff_ST_Ly3	,sizeof(float)	,np,prev_day_ST_Ly3_ptr)!=(size_t)np)
                        || (fread(buff_ST_Ly4	,sizeof(float)	,np,prev_day_ST_Ly4_ptr)!=(size_t)np)
                        || (fread(buff_ST_Ly5	,sizeof(float)	,np,prev_day_ST_Ly5_ptr)!=(size_t)np)
                        || (fread(buff_ST_Ly6	,sizeof(float)	,np,prev_day_ST_Ly6_ptr)!=(size_t)np)
                        || (fread(buff_pool1		,sizeof(float)	,np,prev_day_pool1_ptr) !=(size_t)np)
                        || (fread(buff_pool2		,sizeof(float)	,np,prev_day_pool2_ptr)!=(size_t)np)
                        || (fread(buff_pool3		,sizeof(float)	,np,prev_day_pool3_ptr)!=(size_t)np)
                        || (fread(buff_pool4		,sizeof(float)	,np,prev_day_pool4_ptr)!=(size_t)np)
                        || (fread(buff_pool5		,sizeof(float)	,np,prev_day_pool5_ptr)!=(size_t)np)
                        || (fread(buff_pool6		,sizeof(float)	,np,prev_day_pool6_ptr)!=(size_t)np)
                        || (fread(buff_pool7		,sizeof(float)	,np,prev_day_pool7_ptr) !=(size_t)np)
                        || (fread(buff_pool8		,sizeof(float)	,np,prev_day_pool8_ptr)!=(size_t)np)
                        || (fread(buff_pool9		,sizeof(float)	,np,prev_day_pool9_ptr)!=(size_t)np)
                        || (fread(bio_pool1		,sizeof(float)	,np,prev_day_bio_pool1_ptr)!=(size_t)np)
                        || (fread(bio_pool2		,sizeof(float)	,np,prev_day_bio_pool2_ptr)!=(size_t)np)
                        || (fread(bio_pool3		,sizeof(float)	,np,prev_day_bio_pool3_ptr)!=(size_t)np)
                        || (fread(bio_pool4		,sizeof(float)	,np,prev_day_bio_pool4_ptr)!=(size_t)np)
                        || (fread(soil_pondwater		,sizeof(float)	,np,prev_day_soil_pondwater_ptr) !=(size_t)np)
                        || (fread(prev_snowSWE		,sizeof(float)	,np,prev_day_snow_swe_ptr)!=(size_t)np)
                        || (fread(prev_snowdepth	,sizeof(float)	,np,prev_day_snow_depth_ptr) !=(size_t)np)
                        || (fread(prev_snowdensity		,sizeof(float)	,np,prev_day_snow_density_ptr)!=(size_t)np)
                   )
                    rcode = PERROR;
                else
                {
                    for (pix=0; pix<np; pix++)
                    {
                        xx[pix].x1 = prev_snowSWE[pix];                  //这里xx是啥呀
                        xx[pix].x26= prev_snowdensity[pix];
                        xx[pix].x27= prev_snowdepth[pix];
                        xx[pix].x33= buff_soil_temp[pix];
                        xx[pix].x36= buffer_nitrogen[pix];
                        xx[pix].x12= soil_resp_x[pix];
                        xx[pix].x38= prev_snowdepth[pix];
                        xx[pix].x50= bio_pool1[pix];
                        xx[pix].x51= bio_pool2[pix];
                        xx[pix].x52= bio_pool3[pix];
                        xx[pix].x53= bio_pool4[pix];

                        if(soil_texture[pix]>0 && soil_texture[pix]<=120)
                            soil_index	= (int)soil_texture[pix]/10-1;
                        else
                            soil_index=1;

                        xx[pix].x30=(int)soil_texture[pix];

                        if(soil_index <0 )
                            soil_index = 1;
                        if(soil_index > SOIL_TEXTURE_INDECES)
                            soil_index = SOIL_TEXTURE_INDECES;

                        xx[pix].x20 = BH_SubParams1->SoilTextureIndexVals[soil_index].wilting_pt;
                        xx[pix].x21 = BH_SubParams1->SoilTextureIndexVals[soil_index].field_cap;
                        xx[pix].x22 = BH_SubParams1->SoilTextureIndexVals[soil_index].porosity;
                        xx[pix].x23 = BH_SubParams1->SoilTextureIndexVals[soil_index].MaxiGs;
                        xx[pix].x37 = BH_SubParams1->SoilTextureIndexVals[soil_index].soil_K0H;

                    }   //*the end of pix loop

                } //*the end of else

            }//end


            //读取LAI、LC、流域和气象数据
            if (rcode != PERROR)
            {
                if ((fread(lc,sizeof(unsigned char),np,lcfile_ptr))!=(size_t)np)
                    rcode = PERROR;
            }

            if (rcode != PERROR)
            {
                if (fread(watershed,sizeof(unsigned char),np,fwatershed)!=(size_t)np)
                    rcode = PERROR;
            }

            if (rcode != PERROR)
            {
                if ((fread(temp_uc_buff,sizeof(unsigned char),np,laifile_ptr))!=(size_t)np)
                    rcode = PERROR;
                else
                    readlai(np,temp_uc_buff,lai);
            }

            if (rcode != PERROR)
            {
                //***Read a line of climate data:
                if (	((fread(climate_rad_r	,sizeof(short int),np,climate_rad_r_ptr))	!=(size_t)np)
                        ||	((fread(climate_rad_f	,sizeof(short int),np,climate_rad_f_ptr))	!=(size_t)np)
                        ||	((fread(climate_ti		,sizeof(short int),np,climate_ti_ptr))	!=(size_t)np)
                        ||	((fread(climate_tm		,sizeof(short int),np,climate_tm_ptr))	!=(size_t)np)
                        ||	((fread(climate_prec	,sizeof(short int),np,climate_prec_ptr))!=(size_t)np)
                        ||	((fread(climate_dew		,sizeof(short int),np,climate_dew_ptr))	!=(size_t)np)
                        ||	((fread(climate_wind	,sizeof(short int),np,climate_wind_ptr))!=(size_t)np)
                   )
                    rcode = PERROR;
                else
                    readclim(np,temp_a,climate_rad_r,climate_rad_f,climate_ti,climate_tm,climate_prec,climate_dew,
                             climate_wind,sdat);

            }

            if (jday<=5)   //为什么要对温度这样处理呢
            {
                T_five[jday-1]=climate_tm[137]/10.0;
                T_m=T_five[jday-1];//(T_five[0]+T_five[1]+T_five[2]+T_five[3]+T_five[4])/5;
            }
            else
            {
                a1=T_five[jday-jday];
                a2=T_five[(jday+1)-jday];
                a3=T_five[(jday+2)-jday];
                a4=T_five[(jday+3)-jday];
                a5=T_five[(jday+4)-jday];
                T_five[(jday+4)-jday]=climate_tm[137]/10.0;
                T_five[(jday)-jday]=a2;
                T_five[(jday+1)-jday]=a3;
                T_five[(jday+2)-jday]=a4;
                T_five[(jday+3)-jday]=a5;
                T_m= (T_five[(jday)-jday]+T_five[(jday+1)-jday]+T_five[(jday+2)-jday]+T_five[(jday+3)-jday]+T_five[(jday+4)-jday])/5;
            }

            //*------------------------------------Satrt pixel loop------------------------------
            //printf("ok1");
            //printf("U N N O R M A !!!");


            if (rcode != PERROR)
            {

                for (pix=0; pix<np; pix++)
                {
                    if((lc[pix]==0)||(watershed[pix]==0))	// MEM
                    {
                        canopy[pix].canopy_et			        	= -99.0f;
                        canopy[pix].canopy_evaporation				= -99.0f;
                        canopy[pix].canopy_transpiration_unsat		= -99.0f;
                        canopy[pix].canopy_transpiration_sat		= -99.0f;
                        canopy[pix].canopy_intercepted				= -99.0f;
                        canopy[pix].litter_evaporation				= -99.0f;
                        canopy[pix].moss_transpiration				= -99.0f;
                        canopy[pix].soil_evaporation				= -99.0f;
                        canopy[pix].canopy_ut			        	= -99.0f;
                        canopy[pix].canopy_stomata			        = -99.0f;
                        energy[pix].NRFlux			               	= -99.0f;
                        energy[pix].sensibleHeatFlux				= -99.0f;
                        energy[pix].latentHeatFlux  				= -99.0f;
                        snow[pix].SWE			               	    = -99.0f;
                        snow[pix].Density			               	= -99.0f;
                        snow[pix].Depth 		               	    = -99.0f;
                        Daily_GPP[pix]		               	        = -99.0f;
                        Daily_NPP[pix]		               	        = -99.0f;
                        Daily_NEP[pix]		               	        = -99.0f;
                        Daily_Ra[pix]		               	        = -99.0f;
                        Daily_Rh[pix]		               	        = -99.0f;
                        waterin[pix]                               = -99.0f;
                    }
                    else
                    {
                        xx[pix].x2			= soil_unsaturated_storage[pix];
                        xx[pix].x19			= soil_water_table[pix];  //这里有赋值WTD,初始？
                        xx[pix].x29			= soil_pondwater[pix];
                        xx[pix].x12			= soil_resp_x[pix];
                        xx[pix].x33			= buff_soil_temp[pix];
                        xx[pix].x36			= buffer_nitrogen[pix];
                        xx[pix].x38			= prev_snowdepth[pix];
                        xx[pix].x50			= bio_pool1[pix];
                        xx[pix].x51			= bio_pool2[pix];
                        xx[pix].x52			= bio_pool3[pix];
                        xx[pix].x53			= bio_pool4[pix];

                        readb(b,lc[pix],BH_SubParams2);                      //读取土地覆盖数据
                        // printf("this:%d\n",BH_SubParams2->iMaxAgricultural);
                        //模拟一天中单个像素的碳循环和水循环。
                        model(soilt,snow_acc,snow_today,T_m,jday,sad,pix,pv->jday_start,lat[pix],lai[pix],
                              soil_depth[pix],lc[pix],xSoil,b,sdat,xx,&canopy[pix],g_model,z_model,BH_SubParams2);

//   自行修改后的参数     Daily_GPP[pix]=(float)xx[pix].x11;
//                        Daily_NPP[pix]=(float)xx[pix].x6;
//                        Daily_NEP[pix]=(float)xx[pix].x13;
//                        Daily_Ra[pix] =(float)xx[pix].x16;
//                        Daily_Rh[pix] =(float)xx[pix].x12;
                        Daily_GPP[pix]=(float)xx[pix].x14;        //原始设置的参数
                        Daily_NPP[pix]=(float)xx[pix].x6;
                        Daily_NEP[pix]=(float)xx[pix].x15;
                        Daily_Ra[pix] =(float)xx[pix].x16;
                        Daily_Rh[pix] =(float)xx[pix].x17;
                        energy[pix].NRFlux	=(float) g_model[3];   // this needs to be checked
                        energy[pix].sensibleHeatFlux	= (float) g_model[8];// this needs to be checked
                        energy[pix].latentHeatFlux		=(float) g_model[9]; // this needs to be checked
                        snow[pix].SWE     =(float)xx[pix].x1;// this needs to be checked
                        snow[pix].Density =(float)xx[pix].x26;	// this needs to be checked
                        snow[pix].Depth   =(float)xx[pix].x27;	// this needs to be checked
                        waterin[pix]       =(float)xx[pix].x28; // this needs to be checked   这里入渗的量需要被检查,WATERIN的数据不太正确
                    }//end if lc=0


                } //*the end of pixel loop

            }//end of error
            //printf("U N N O R M A !!!");



//*------------------------------------Satrt pixel output each line ------------------------------


            for(pix=0; pix<np; pix++)
            {
                if((lc[pix]!=0)&&(watershed[pix]!=0))							// MEM
                    canopy_ET[pix] = (float)((xx[pix].x4+xx[pix].x5));//*pv->factor);	// MEM: in mm
                else
                    canopy_ET[pix] = -999.0f;

                if((lc[pix]!=0)&&(watershed[pix]!=0))							// MEM
                    canopy_UT[pix]=0;// (float)((xx[pix].x18)*pv->factor/10.0);	// MEM: in mm  //UT全部变成了0？
                else
                    canopy_UT[pix] = -999.0f;
            }

            if(rcode != PERROR)
            {
                DisassembleCanopyArray(np,canopy_evaporation,canopy_transpiration_unsat,
                                       canopy_transpiration_sat,canopy_intercepted,canopy_litter_evaporation,
                                       canopy_moss_transpiration,canopy_soil_evaporation,canopy_stomata,canopy);

                if (    (fwrite(canopy_evaporation			,sizeof(float),np,canopy_evaporation_ptr)			!=(size_t)np)

                        ||	(fwrite(canopy_transpiration_unsat	,sizeof(float),np,canopy_transpiration_unsat_ptr)	!=(size_t)np)

                        ||	(fwrite(canopy_transpiration_sat	,sizeof(float),np,canopy_transpiration_sat_ptr)		!=(size_t)np)
                        ||	(fwrite(canopy_intercepted			,sizeof(float),np,canopy_intercepted_ptr)			!=(size_t)np)
                        ||	(fwrite(canopy_litter_evaporation	,sizeof(float),np,canopy_litter_evaporation_ptr)	!=(size_t)np)
                        ||	(fwrite(canopy_moss_transpiration	,sizeof(float),np,canopy_moss_transpiration_ptr)	!=(size_t)np)
                        ||	(fwrite(canopy_stomata				,sizeof(float),np,canopy_Stomata_ptr)			!=(size_t)np)
                        ||	(fwrite(canopy_soil_evaporation		,sizeof(float),np,canopy_soil_evaporation_ptr)		!=(size_t)np)
                   )
                    rcode = PERROR;
            }

            if(rcode != PERROR)
            {
                DisassembleEnergyArray(np, NRFlux,sensibleHeatFlux,	 latentHeatFlux, energy);

                if ((fwrite( sensibleHeatFlux	,sizeof(float),np, sensibleHeatFlux_ptr)	!=(size_t)np)
                        ||(fwrite( latentHeatFlux	,sizeof(float),np, latentHeatFlux_ptr)		!=(size_t)np)
                        ||(fwrite( NRFlux	,sizeof(float),np, NRFlux_ptr)		!=(size_t)np)
                   )
                    rcode = PERROR;
            }



            if(rcode != PERROR)
            {
                //write snow variables
                DisassembleSnowArray(np, curr_snowSWE,curr_snowdepth,curr_snowdensity, snow);
                if  ((fwrite( curr_snowSWE	,sizeof(float),np, curr_day_snow_swe_ptr)   !=(size_t)np)
                        ||(fwrite( curr_snowdepth,sizeof(float),np, curr_day_snow_depth_ptr) !=(size_t)np)
                        ||(fwrite( curr_snowdensity,sizeof(float),np, curr_day_snow_density_ptr)!=(size_t)np)
                    )
                    rcode = PERROR;
            }

            // for  GPP
            if((rcode != PERROR))
            {
                for(pix=0; pix<np; pix++)
                {
                    if((lc[pix]!=0)&&(watershed[pix]!=0))
                        pFloatOutput[pix] = (float)(Daily_GPP[pix]*pv->factor);
                    else
                        pFloatOutput[pix] = -999.0f;
                }
                if (fwrite(pFloatOutput,sizeof(float),np,Daily_GPP_ptr)!=(size_t)np)
                    rcode = PERROR;
            }

            // for  NPP
            if((rcode != PERROR))
            {
                for(pix=0; pix<np; pix++)
                {

                    if((lc[pix]!=0)&&(watershed[pix]!=0))

                        pFloatOutput[pix] = (float)(Daily_NPP[pix]*pv->factor);

                    else
                        pFloatOutput[pix] = -999.0f;
                }
                if (fwrite(pFloatOutput,sizeof(float),np,Daily_NPP_ptr)!=(size_t)np)
                    rcode = PERROR;
            }
            if((rcode != PERROR))
            {
                for(pix=0; pix<np; pix++)
                {
                    if((lc[pix]!=0)&&(watershed[pix]!=0))
                        pFloatOutput[pix] = (float)(Daily_Ra[pix]*pv->factor);
                    else
                        pFloatOutput[pix] = -999.0f;
                }
                if (fwrite(pFloatOutput,sizeof(float),np,Daily_Ra_ptr)!=(size_t)np)
                    rcode = PERROR;
            }


            // for  Rh
            if((rcode != PERROR))
            {
                for(pix=0; pix<np; pix++)
                {
                    if((lc[pix]!=0)&&(watershed[pix]!=0))
                        pFloatOutput[pix] = (float)(Daily_Rh[pix]*pv->factor);
                    else
                        pFloatOutput[pix] = -999.0f;
                }
                if (fwrite(pFloatOutput,sizeof(float),np,Daily_Rh_ptr)!=(size_t)np)
                    rcode = PERROR;
            }



            // for  ET
            if((rcode != PERROR))
            {
                for(pix=0; pix<np; pix++)
                {
                    if((lc[pix]!=0)&&(watershed[pix]!=0))
                        pFloatOutput[pix] = (float)(canopy_ET[pix]*pv->factor);
                    else
                        pFloatOutput[pix] = -999.0f;
                }
                if (fwrite(pFloatOutput,sizeof(float),np,canopy_ET_ptr)!=(size_t)np)
                    rcode = PERROR;
            }


            // for UT
            if((rcode != PERROR))
            {
                for(pix=0; pix<np; pix++)
                {
                    if((lc[pix]!=0)&&(watershed[pix]!=0))
                        pFloatOutput[pix] = (float)(canopy_UT[pix]*pv->factor);
                    else
                        pFloatOutput[pix] = -999.0f;
                }
                if (fwrite(pFloatOutput,sizeof(float),np,canopy_UT_ptr)!=(size_t)np)
                    rcode = PERROR;
            }

            if((rcode != PERROR))
            {
                if (fwrite(waterin,sizeof(float),np,waterin_ptr)!=(size_t)np)   //这里写了入渗的变量
                {
                    rcode = PERROR;
                }
            }

// printf("ok1");
        }//end of lines
        //printf("ok3");
        //printf("U N N O R M A !!!");

//*--------------The end of line loop----------------

        if (climate_tm_ptr)
            fclose(climate_tm_ptr);
        climate_tm_ptr			= (FILE*)NULL;

        //Energy fluxes
        if ( NRFlux_ptr)
            fclose( NRFlux_ptr);
        NRFlux_ptr			= (FILE*)NULL;
        if (sensibleHeatFlux_ptr)
            fclose( sensibleHeatFlux_ptr);
        sensibleHeatFlux_ptr			= (FILE*)NULL;
        if ( latentHeatFlux_ptr)
            fclose( latentHeatFlux_ptr);
        latentHeatFlux_ptr			= (FILE*)NULL;

        if (canopy_ET_ptr)
            fclose(canopy_ET_ptr);
        canopy_ET_ptr			= (FILE*)NULL;

        if (canopy_evaporation_ptr)
            fclose(canopy_evaporation_ptr);
        canopy_evaporation_ptr			= (FILE*)NULL;

        if (canopy_transpiration_unsat_ptr)
            fclose(canopy_transpiration_unsat_ptr);
        canopy_transpiration_unsat_ptr	= (FILE*)NULL;

        if (canopy_transpiration_sat_ptr)
            fclose(canopy_transpiration_sat_ptr);
        canopy_transpiration_sat_ptr	= (FILE*)NULL;

        if (canopy_intercepted_ptr)
            fclose(canopy_intercepted_ptr);
        canopy_intercepted_ptr			= (FILE*)NULL;

        if (canopy_litter_evaporation_ptr)
            fclose(canopy_litter_evaporation_ptr);
        canopy_litter_evaporation_ptr	= (FILE*)NULL;

        if (canopy_moss_transpiration_ptr)
            fclose(canopy_moss_transpiration_ptr);
        canopy_moss_transpiration_ptr	= (FILE*)NULL;

        if (canopy_soil_evaporation_ptr)
            fclose(canopy_soil_evaporation_ptr);
        canopy_soil_evaporation_ptr		= (FILE*)NULL;

        if (canopy_UT_ptr)
            fclose(canopy_UT_ptr);
        canopy_UT_ptr = (FILE*)NULL;

        if (canopy_Stomata_ptr)
            fclose(canopy_Stomata_ptr);
        canopy_Stomata_ptr	= (FILE*)NULL;

        //carbon flux files
        if(Daily_GPP_ptr)
            fclose(Daily_GPP_ptr);
        Daily_GPP_ptr = (FILE*)NULL;

        if(Daily_NPP_ptr)
            fclose(Daily_NPP_ptr);
        Daily_NPP_ptr = (FILE*)NULL;


        if(Daily_Ra_ptr)
            fclose(Daily_Ra_ptr);
        Daily_Ra_ptr = (FILE*)NULL;

        if(Daily_Rh_ptr)
            fclose(Daily_Rh_ptr);
        Daily_Rh_ptr			= (FILE*)NULL;

        //snow
        if (curr_day_snow_swe_ptr)
            fclose(curr_day_snow_swe_ptr);
        curr_day_snow_swe_ptr	= (FILE*)NULL;

        if (curr_day_snow_depth_ptr)
            fclose(curr_day_snow_depth_ptr);
        curr_day_snow_depth_ptr	= (FILE*)NULL;

        if (curr_day_snow_density_ptr)
            fclose(curr_day_snow_density_ptr);
        curr_day_snow_density_ptr = (FILE*)NULL;

        if (prev_day_snow_swe_ptr)
            fclose(prev_day_snow_swe_ptr);
        prev_day_snow_swe_ptr	= (FILE*)NULL;

        if (prev_day_snow_depth_ptr)
            fclose(prev_day_snow_depth_ptr);
        prev_day_snow_depth_ptr = (FILE*)NULL;

        if (prev_day_snow_density_ptr)
            fclose(prev_day_snow_density_ptr);
        prev_day_snow_density_ptr = (FILE*)NULL;

        if (waterin_ptr)
            fclose(waterin_ptr);
        waterin_ptr	= (FILE*)NULL;
        //printf("ok3");      //运行正常

        //------------------------------START TERRAINLAB PART OF EXECUTION---------------------------
        //------------------------------START TERRAINLAB PART OF EXECUTION---------------------------

        if ( ((canopy_evaporation_ptr		 =fopen(szCanopyDailyFileNameEvaporation	,"rb")) ==NULL)
                || 	((canopy_transpiration_unsat_ptr =fopen(szCanopyDailyFileNameTranspUnsat	,"rb")) ==NULL)
                ||	((canopy_transpiration_sat_ptr	 =fopen(szCanopyDailyFileNameTranspSat		,"rb")) ==NULL)
                ||	((canopy_intercepted_ptr		 =fopen(szCanopyDailyFileNameIntercepted	,"rb")) ==NULL)
                ||	((canopy_litter_evaporation_ptr	 =fopen(szCanopyDailyFileNameLitterEvaporation,"rb")) ==NULL)
                ||	((canopy_moss_transpiration_ptr	 =fopen(szCanopyDailyFileNameMossTransp		,"rb")) ==NULL)
                ||	((canopy_soil_evaporation_ptr	 =fopen(szCanopyDailyFileNameSoilEvaporation,"rb")) ==NULL)
                ||	((waterin_ptr	                 =fopen(szWaterInFileName,"rb")) ==NULL)                      //打开waterin
                ||	((climate_tm_ptr	             =fopen(szClimateDailyFileNameTM,"rb")) ==NULL)
                ||	((Daily_NPP_ptr	                 =fopen(szNPPDailyFileName,"rb")) ==NULL)
                ||	((prev_day_snow_depth_ptr             =fopen(szPrevDaySnowdepthFileName,"rb")) ==NULL)
           )
            rcode = PERROR;

        if (	((fseek(lcfile_ptr								,0,SEEK_SET))!=0)
                ||	((fseek(fwatershed								,0,SEEK_SET))!=0)
                ||	((fseek(climate_prec_ptr						,0,SEEK_SET))!=0)           //当天prec
                ||	((fseek(waterin_ptr					        	,0,SEEK_SET))!=0)           //当天waterin
                ||	((fseek(prev_day_snow_depth_ptr				        	,0,SEEK_SET))!=0)   //前一天Snow
                ||	((fseek(Daily_NPP_ptr					,0,SEEK_SET))!=0)      //nppto tl
                ||	((fseek(Daily_NEP_ptr					,0,SEEK_SET))!=0)      // EPHYSE addition
                ||	((fseek(Dem_ptr									,0,SEEK_SET))!=0)
                ||	((fseek(soil_texture_file_ptr					,0,SEEK_SET))!=0)
                ||	((fseek(soil_K0_decay_m_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(soil_saturation_suction_ptr	,    0,SEEK_SET))!=0)
                ||	((fseek(soil_saturated_Kv_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(soil_saturated_Kh_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_soil_saturation_deficit_ptr	,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_soil_unsaturated_storage_ptr	,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_soil_water_table_ptr			,0,SEEK_SET))!=0)           //前一天WTD
                ||	((fseek(prev_day_soil_temp_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_nitrogen_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_CNcd_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_CNssd_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_CNsmd_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_CNfsd_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_CNfmd_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_CNsm_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_CNm_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_CNs_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_CNp_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_CNw_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_CNfr_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_CNl_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_ST_Ly1_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_ST_Ly2_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_ST_Ly3_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_ST_Ly4_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_ST_Ly5_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_ST_Ly6_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_pool1_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_pool2_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_pool3_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_pool4_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_pool5_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_pool6_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_pool7_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_pool8_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_pool9_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_bio_pool1_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_bio_pool2_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_bio_pool3_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_bio_pool4_ptr			,0,SEEK_SET))!=0)
                ||	((fseek(prev_day_soil_pondwater_ptr				,0,SEEK_SET))!=0)         //前一天pondwater
                ||	((fseek(soil_Max_depth_Z_ptr					,0,SEEK_SET))!=0)
                ||	((fseek(soil_b_ptr								,0,SEEK_SET))!=0))
            rcode = PERROR;

        //---------------------------------- LLLLLLLLLL	Start of lin_cycle LLLLLLLLLL
        //---------------------------------- LLLLLLLLLL	Start of lin_cycle LLLLLLLLLL
        //printf("ok3");
        //printf("U N N O R M A !!!");
        for (lin=0; (lin<nl)&&(rcode!=PERROR); lin++)
        {
            line = lin;
            if (line==0)
            {

                if (fread(soil_K0_decay_m_3r				,sizeof(float)	,2*np,soil_K0_decay_m_ptr)
                        !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_saturation_suction_3r	,sizeof(float)	,2*np,soil_saturation_suction_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_saturated_Kv_3r			,sizeof(float)	,2*np,soil_saturated_Kv_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_saturated_Kh_3r			,sizeof(float)	,2*np,soil_saturated_Kh_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_saturation_deficit_3r	,sizeof(float)	,2*np,prev_day_soil_saturation_deficit_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_unsaturated_storage_3r	,sizeof(float)	,2*np,prev_day_soil_unsaturated_storage_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_water_table_3r			,sizeof(float)	,2*np,prev_day_soil_water_table_ptr)         //WTD
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_temp_3r			,sizeof(float)	,2*np,prev_day_soil_temp_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_nitrogen_3r			,sizeof(float)	,2*np,prev_day_nitrogen_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_CNcd_3r			,sizeof(float)	,2*np,prev_day_CNcd_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_CNssd_3r			,sizeof(float)	,2*np,prev_day_CNssd_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_CNsmd_3r			,sizeof(float)	,2*np,prev_day_CNsmd_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_CNfsd_3r			,sizeof(float)	,2*np,prev_day_CNfsd_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_CNfmd_3r			,sizeof(float)	,2*np,prev_day_CNfmd_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_CNsm_3r			,sizeof(float)	,2*np,prev_day_CNsm_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_CNm_3r			,sizeof(float)	,2*np,prev_day_CNm_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_CNs_3r			,sizeof(float)	,2*np,prev_day_CNs_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_CNp_3r			,sizeof(float)	,2*np,prev_day_CNp_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_CNw_3r			,sizeof(float)	,2*np,prev_day_CNw_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_CNfr_3r			,sizeof(float)	,2*np,prev_day_CNfr_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_CNl_3r			,sizeof(float)	,2*np,prev_day_CNl_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_ST_Ly1_3r			,sizeof(float)	,2*np,prev_day_ST_Ly1_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_ST_Ly2_3r			,sizeof(float)	,2*np,prev_day_ST_Ly2_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_ST_Ly3_3r			,sizeof(float)	,2*np,prev_day_ST_Ly3_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_ST_Ly4_3r			,sizeof(float)	,2*np,prev_day_ST_Ly4_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_ST_Ly5_3r			,sizeof(float)	,2*np,prev_day_ST_Ly5_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_ST_Ly6_3r			,sizeof(float)	,2*np,prev_day_ST_Ly6_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_pool1_3r			,sizeof(float)	,2*np,prev_day_pool1_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_pool2_3r			,sizeof(float)	,2*np,prev_day_pool2_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_pool3_3r			,sizeof(float)	,2*np,prev_day_pool3_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_pool4_3r			,sizeof(float)	,2*np,prev_day_pool4_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_pool5_3r			,sizeof(float)	,2*np,prev_day_pool5_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_pool6_3r			,sizeof(float)	,2*np,prev_day_pool6_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_pool7_3r			,sizeof(float)	,2*np,prev_day_pool7_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_pool8_3r			,sizeof(float)	,2*np,prev_day_pool8_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_pool9_3r			,sizeof(float)	,2*np,prev_day_pool9_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_bio_pool1_3r			,sizeof(float)	,2*np,prev_day_bio_pool1_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_bio_pool2_3r			,sizeof(float)	,2*np,prev_day_bio_pool2_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_bio_pool3_3r			,sizeof(float)	,2*np,prev_day_bio_pool3_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_bio_pool4_3r			,sizeof(float)	,2*np,prev_day_bio_pool4_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_pondwater_3r			,sizeof(float)	,2*np,prev_day_soil_pondwater_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_Max_depth_Z_3r			,sizeof(float)	,2*np,soil_Max_depth_Z_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else if (fread(soil_b_3r					,sizeof(float)	,2*np,soil_b_ptr)
                         !=(size_t)2*np)
                    rcode = PERROR;
                else
                {
                    //***assemble soil_t array from corresponding float arrays:
                    AssembleSoilArray(3*np,soil_K0_decay_m_3r,soil_b_3r,soil_saturation_suction_3r,soil_saturated_Kv_3r,soil_saturated_Kh_3r,
                                      soil_saturation_deficit_3r,soil_unsaturated_storage_3r,soil_water_table_3r,soil_temp_3r,soil_pondwater_3r,
                                      soil_Max_depth_Z_3r,
                                      soil_pool1_3r,soil_pool2_3r,soil_pool3_3r,soil_pool4_3r,soil_pool5_3r,soil_pool6_3r,soil_pool7_3r,soil_pool8_3r,soil_pool9_3r,
                                      soil_bio_pool1_3r,soil_bio_pool2_3r, soil_bio_pool3_3r,soil_bio_pool4_3r,soil_nitrogen_3r,
                                      soil_CNcd_3r,soil_CNssd_3r,soil_CNsmd_3r,soil_CNfsd_3r,soil_CNfmd_3r,soil_CNsm_3r,soil_CNm_3r,
                                      soil_CNs_3r,soil_CNp_3r,soil_CNw_3r,soil_CNfr_3r,soil_CNl_3r,
                                      soil_ST_Ly1_3r,soil_ST_Ly2_3r,soil_ST_Ly3_3r,soil_ST_Ly4_3r,soil_ST_Ly5_3r,soil_ST_Ly6_3r,
                                      soil_3r); //pond and 2nov2006

                    //***prepare current (1st) row of soil data as input for soil_water_balance() function:
                    memcpy(soil,soil_3r,np*sizeof(Soil_t));
                }

                //***read in first two Dem data rows:                            读取DEM数据
                if (rcode!=PERROR)
                {
                    if (fread(Array_Elevation_3r,sizeof(float),2*np,Dem_ptr)!=(size_t)(2*np))
                        rcode = PERROR;
                }

                //***set Array_Label_3r according to values in Array_Elevation_3r:
                if (rcode!=PERROR)
                {
                    for (pix=0; pix<2*np; pix++)
                    {
                        if(Array_Elevation_3r[pix] >= (int) 9999.0f)
                            Array_Label_3r[pix]= (int)9999.0;
                        else
                            Array_Label_3r[pix]= (int)-9999.0;//这样子来看-9999是正常高程值的标签
                    }
                }

                //*************Waterslope*********************
                for(i2=0; i2<np*2; i2++)
                {
                    if (Array_Elevation_3r[i2] > 0 && Array_Elevation_3r[i2] < 2000 && soil_water_table_3r[i2]<10.0&& soil_water_table_3r[i2]>-10.0)

                    //为什么要取阈值2000呢,这里修改成了2200
                    {
                        Array_WElevation_3r[i2] =MIN( Array_Elevation_3r[i2]- soil_water_table_3r[i2],Array_Elevation_3r[i2]);
                    }
                    else
                        Array_WElevation_3r[i2]=Array_Elevation_3r[i2];

                }

                //*************Waterslope*********************
            } // the end of the first line

            //printf("ok3");
            else if (line<nl-1)
            {
                //*dealing with any other lines, except the last,
                //	prepare 3 lines of data: shift previously 2nd and 3rd up and copy one new line
                //	  to the tail
                //no shift required if dealing with 2nd Dem /Soil /Soil Maximum Depth data row;
                //the 3rd Dem /Soil data row should just be uppended to the tail of the initial two
                if (line!=1)
                {
                    //shift 2nd and 3rd Dem and soil data lines up to make them 1st and 2nd:
                    memmove(Array_Elevation_3r			,Array_Elevation_3r+(int)np			,2*np*sizeof(float));
                    memmove(Array_Label_3r				,Array_Label_3r+(int)np				,2*np*sizeof(int));
                    memmove(soil_K0_decay_m_3r			,soil_K0_decay_m_3r+(int)np			,2*np*sizeof(float));
                    memmove(soil_b_3r					,soil_b_3r+(int)np					,2*np*sizeof(float));
                    memmove(soil_saturation_suction_3r	,soil_saturation_suction_3r+(int)np	,2*np*sizeof(float));
                    memmove(soil_saturated_Kv_3r		,soil_saturated_Kv_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_saturated_Kh_3r		,soil_saturated_Kh_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_saturation_deficit_3r	,soil_saturation_deficit_3r+(int)np	,2*np*sizeof(float));
                    memmove(soil_unsaturated_storage_3r	,soil_unsaturated_storage_3r+(int)np,2*np*sizeof(float));
                    memmove(soil_water_table_3r			,soil_water_table_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_temp_3r			,soil_temp_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_nitrogen_3r			,soil_nitrogen_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_CNcd_3r	,soil_CNcd_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_CNssd_3r	,soil_CNssd_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_CNsmd_3r	,soil_CNsmd_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_CNfsd_3r	,soil_CNfsd_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_CNfmd_3r	,soil_CNfmd_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_CNsm_3r	,soil_CNsm_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_CNm_3r		,soil_CNm_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_CNs_3r		,soil_CNs_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_CNp_3r		,soil_CNp_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_CNw_3r		,soil_CNw_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_CNfr_3r	,soil_CNfr_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_CNl_3r		,soil_CNl_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_ST_Ly1_3r		,soil_ST_Ly1_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_ST_Ly2_3r		,soil_ST_Ly2_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_ST_Ly3_3r		,soil_ST_Ly3_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_ST_Ly4_3r		,soil_ST_Ly4_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_ST_Ly5_3r		,soil_ST_Ly5_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_ST_Ly6_3r		,soil_ST_Ly6_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_pool1_3r			,soil_pool1_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_pool2_3r			,soil_pool2_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_pool3_3r			,soil_pool3_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_pool4_3r			,soil_pool4_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_pool5_3r			,soil_pool5_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_pool6_3r			,soil_pool6_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_pool7_3r			,soil_pool7_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_pool8_3r			,soil_pool8_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_pool9_3r			,soil_pool9_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_bio_pool1_3r		,soil_bio_pool1_3r+(int)np	,2*np*sizeof(float));
                    memmove(soil_bio_pool2_3r		,soil_bio_pool2_3r+(int)np	,2*np*sizeof(float));
                    memmove(soil_bio_pool3_3r		,soil_bio_pool3_3r+(int)np	,2*np*sizeof(float));
                    memmove(soil_bio_pool4_3r		,soil_bio_pool4_3r+(int)np	,2*np*sizeof(float));
                    memmove(soil_pondwater_3r			,soil_pondwater_3r+(int)np		,2*np*sizeof(float));
                    memmove(soil_Max_depth_Z_3r			,soil_Max_depth_Z_3r+(int)np		,2*np*sizeof(float));
                } //end of line !=1


                if (fread(soil_K0_decay_m_3r+(int)(2*np)				,sizeof(float)	,np,soil_K0_decay_m_ptr)
                        !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_saturation_suction_3r+(int)(2*np)	,sizeof(float)	,np,soil_saturation_suction_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_saturated_Kv_3r+(int)(2*np)			,sizeof(float)	,np,soil_saturated_Kv_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_saturated_Kh_3r+(int)(2*np)			,sizeof(float)	,np,soil_saturated_Kh_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_saturation_deficit_3r+(int)(2*np)	,sizeof(float)	,np,prev_day_soil_saturation_deficit_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_unsaturated_storage_3r+(int)(2*np)	,sizeof(float)	,np,prev_day_soil_unsaturated_storage_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_water_table_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_soil_water_table_ptr)   //WTD
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_temp_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_soil_temp_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_nitrogen_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_nitrogen_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_CNcd_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_CNcd_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_CNssd_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_CNssd_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_CNsmd_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_CNsmd_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_CNfsd_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_CNfsd_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_CNfmd_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_CNfmd_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_CNsm_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_CNsm_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_CNm_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_CNm_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_CNs_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_CNs_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_CNp_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_CNp_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_CNw_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_CNw_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_CNfr_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_CNfr_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_CNl_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_CNl_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_ST_Ly1_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_ST_Ly1_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_ST_Ly2_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_ST_Ly2_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_ST_Ly3_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_ST_Ly3_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_ST_Ly4_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_ST_Ly4_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_ST_Ly5_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_ST_Ly5_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_ST_Ly6_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_ST_Ly6_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_pool1_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_pool1_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_pool2_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_pool2_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_pool3_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_pool3_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_pool4_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_pool4_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_pool5_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_pool5_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_pool6_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_pool6_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_pool7_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_pool7_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_pool8_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_pool8_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_pool9_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_pool9_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_bio_pool1_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_bio_pool1_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_bio_pool2_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_bio_pool2_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_bio_pool3_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_bio_pool3_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_bio_pool4_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_bio_pool4_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_pondwater_3r+(int)(2*np)			,sizeof(float)	,np,prev_day_soil_pondwater_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_Max_depth_Z_3r+(int)(2*np)			,sizeof(float)	,np,soil_Max_depth_Z_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fread(soil_b_3r+(int)(2*np)					,sizeof(float)	,np,soil_b_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else
                {
                    //***assemble soil_t array from corresponding float arrays:
                    AssembleSoilArray(3*np,soil_K0_decay_m_3r,soil_b_3r,soil_saturation_suction_3r,soil_saturated_Kv_3r,
                                      soil_saturated_Kh_3r,soil_saturation_deficit_3r,soil_unsaturated_storage_3r,soil_water_table_3r,soil_temp_3r,soil_pondwater_3r,
                                      soil_Max_depth_Z_3r,
                                      soil_pool1_3r,soil_pool2_3r,soil_pool3_3r,soil_pool4_3r,soil_pool5_3r,soil_pool6_3r,soil_pool7_3r,soil_pool8_3r,soil_pool9_3r,
                                      soil_bio_pool1_3r,soil_bio_pool2_3r,soil_bio_pool3_3r,soil_bio_pool4_3r,soil_nitrogen_3r,
                                      soil_CNcd_3r,soil_CNssd_3r,soil_CNsmd_3r,soil_CNfsd_3r,soil_CNfmd_3r,soil_CNsm_3r,soil_CNm_3r,
                                      soil_CNs_3r,soil_CNp_3r,soil_CNw_3r,soil_CNfr_3r,soil_CNl_3r,
                                      soil_ST_Ly1_3r,soil_ST_Ly2_3r,soil_ST_Ly3_3r,soil_ST_Ly4_3r,soil_ST_Ly5_3r,soil_ST_Ly6_3r,
                                      soil_3r);  //pond  2nov2006 //pool

                    //***prepare current (2nd) row of soil data as input for soil_water_balance() function:
                    memcpy(soil,soil_3r+(int)np,np*sizeof(Soil_t));
                }


                if (rcode!=PERROR)
                {
                    if (fread(Array_Elevation_3r+(int)(2*np),sizeof(float),np,Dem_ptr)!=(size_t)np)
                        rcode = PERROR;

                }

                if (rcode!=PERROR)
                {
                    //***set Array_Label_3r according to values in Array_Elevation_3r:
                    for (pix=0; pix<np; pix++)
                    {
                        if(Array_Elevation_3r[2*np+pix] >= (int) 9999.0f)
                            Array_Label_3r[2*np+pix]=(int) 9999.0;
                        else
                            Array_Label_3r[2*np+pix]=(int) -9999.0;//这样子来看-9999是正常高程值的标签
                    }
                }

                for(i2=0; i2<np*3; i2++)
                {
                    if (Array_Elevation_3r[i2] > 0 && Array_Elevation_3r[i2] < 2000 && soil_water_table_3r[i2]<10.0&& soil_water_table_3r[i2]>-10.0)
                         //为什么要取阈值2000呢,这里修改成了2200
                    {
                        Array_WElevation_3r[i2] =MIN( Array_Elevation_3r[i2]- soil_water_table_3r[i2],Array_Elevation_3r[i2]);
                    }

                    else
                        Array_WElevation_3r[i2]=Array_Elevation_3r[i2];  // 9999
                }


            }//end of  line>0 and line<line-1
            else if (line<nl-1)
            {
                //if dealing with the last Dem /Soil data lines, no more file reading is required;
                //the last line was already read in during the previous loop run;
                //only setting proper input for soil_water_balance() function is necessary
                //***prepare current (3rd) row of soil data as input for soil_water_balance() function:
                memcpy(soil,soil_3r+(int)(2*np),np*sizeof(Soil_t));
            }//end of the last line


            //printf("ok3"); 运行正常
            //printf("U N N O R M A !!!");

            if (rcode!=PERROR)
            {
                //***read climate line of input data for soil_water_balance() function:          读取waterin
                if(fread(waterin,sizeof(float),np,waterin_ptr)!=(size_t)np)
                    rcode = PERROR;
            }


            if (rcode!=PERROR)
            {
                //***read climate line of input data for soil_water_balance() function:         读取雪深度
                if(fread(prev_snowdepth,sizeof(float),np,prev_day_snow_depth_ptr)!=(size_t)np)
                    rcode = PERROR;
            }

            if (rcode!=PERROR)
            {
                //***read npp function: npp to tl                                              读取NPP
                if(fread(Daily_NPP,sizeof(float),np,Daily_NPP_ptr)!=(size_t)np)
                    rcode = PERROR;
            }


            if (rcode!=PERROR)
            {
                //***read climate line of input data for soil_water_balance() function:       读取最高温
                if(fread(climate_tm,sizeof(short int),np,climate_tm_ptr)!=(size_t)np)
                    rcode = PERROR;
            }

            if (rcode!=PERROR)
            {
                //***read canopy line of input data for soil_water_balance() function:         读取ET各分量
                if ((fread(canopy_evaporation		,sizeof(float),np,canopy_evaporation_ptr)			!=(size_t)np)
                        ||  (fread(canopy_transpiration_unsat	,sizeof(float),np,canopy_transpiration_unsat_ptr)	!=(size_t)np)
                        ||	(fread(canopy_transpiration_sat		,sizeof(float),np,canopy_transpiration_sat_ptr)		!=(size_t)np)
                        ||	(fread(canopy_intercepted			,sizeof(float),np,canopy_intercepted_ptr)			!=(size_t)np)
                        ||	(fread(canopy_litter_evaporation	,sizeof(float),np,canopy_litter_evaporation_ptr)	!=(size_t)np)
                        ||	(fread(canopy_moss_transpiration	,sizeof(float),np,canopy_moss_transpiration_ptr)	!=(size_t)np)
                        ||	(fread(canopy_soil_evaporation		,sizeof(float),np,canopy_soil_evaporation_ptr)		!=(size_t)np)
                   )
                    rcode = PERROR;
                else
                {
                    AssembleCanopyArray(np,canopy_evaporation,canopy_transpiration_unsat,
                                        canopy_transpiration_sat,canopy_intercepted,canopy_litter_evaporation,
                                        canopy_moss_transpiration,canopy_soil_evaporation,canopy_stomata,canopy);
                }

            }

            if (rcode!=PERROR)
            {
                //***read watershed line of input data for soil_water_balance() function:            读取流域边界
                if(fread(watershed,sizeof(unsigned char),np,fwatershed)!=(size_t)np)
                    rcode = PERROR;
            }

            if (rcode!=PERROR)
            {
                //***read soil texture data to be used in soil_water_balance() function:             读取土壤质地
                if ((fread(soil_texture,sizeof(unsigned char),np,soil_texture_file_ptr))!=(size_t)np)
                    rcode = PERROR;
            }

            if (rcode != PERROR)
            {
                //***read a line of Land Cover values:                                               读取土地覆盖
                if ((fread(lc,sizeof(unsigned char),np,lcfile_ptr))!=(size_t)np)
                    rcode = PERROR;
            }


            //printf("ok3");
            if (rcode != PERROR)
            {
                //Base Flow Function:
                //Inputs:	Array_Elevation_3r, Array_Label_3r, and soil_3r 3-row data arrays;
                //Outputs:	baseflow 1-row array
                memset(runoff_baseflow		,0,np*sizeof(float));
                memset(Daily_NEP		,0,np*sizeof(float)); //deleted in EPHYSE
                memset(runoff_total_inflow	,0,np*sizeof(float));
                memset(runoff_total_outflow	,0,np*sizeof(float));
                memset(runoff_total,		0,np*sizeof(float));
                memset(soil_resp_x		,0,np*sizeof(float));

                soil_temp(pv, soil,soil_texture,prev_snowdepth, jday,lc, watershed, climate_tm); //calls soil temperature

                base_flow(pv,jday,line,soil,watershed,runoff_baseflow,runoff_total_inflow,
                          runoff_total_outflow,Array_WElevation_3r,Array_Label_3r,soil_texture,
                          BH_SubParams1->SoilTextureIndexVals,soil_3r);

                soil_water_balance2(pv,runoff_baseflow,waterin,runoff_total,
                                    soil_texture,BH_SubParams1->SoilTextureIndexVals,
                                    soil,soil_capillary_rise,soil_percolation,canopy,lc,
                                    watershed,jday,b[99],line);

                soil_resp(jday,line, pv, soil,canopy, soil_texture,waterin,Daily_NPP, lc, climate_tm, watershed,Daily_NEP);

                DisassembleSoilArray(np,soil_K0_decay_m,soil_b,soil_saturation_suction,soil_saturated_Kv,soil_saturated_Kh,
                                     soil_saturation_deficit,soil_unsaturated_storage,soil_water_table,buff_soil_temp,soil_pondwater,
                                     soil_Max_depth_Z,
                                     buff_pool1,buff_pool2,buff_pool3,buff_pool4,buff_pool5,buff_pool6,buff_pool7,buff_pool8,buff_pool9,
                                     bio_pool1,bio_pool2,bio_pool3,bio_pool4,buffer_nitrogen,
                                     buffer_CNcd,buffer_CNssd,buffer_CNsmd,buffer_CNfsd,buffer_CNfmd,buffer_CNsm,
                                     buffer_CNm,buffer_CNs,buffer_CNp,buffer_CNw,buffer_CNfr,buffer_CNl,
                                     buff_ST_Ly1,buff_ST_Ly2,buff_ST_Ly3,buff_ST_Ly4,buff_ST_Ly5,buff_ST_Ly6,soil);

                for(ii=0; ii<np; ii++)
                {
                    if(soil_water_table[ii]>0 & soil_water_table[ii]<1) {}  //这里并没有筛选掉大于1m
                    //soil_water_table[ii]=soil_water_table[ii];
                    //else{soil_water_table[ii]=soil_water_table_3r[np+ii];}
                    else
                    {
                        soil_water_table[ii]=soil_water_table_3r[np+ii];
                    }
                }
//                printf("U N N O R M A !!!");


                if (fwrite(soil_saturation_deficit	,sizeof(float)	,np,curr_day_soil_saturation_deficit_ptr)
                        !=(size_t)np)
                    rcode = PERROR;
                else if (fwrite(soil_unsaturated_storage,sizeof(float)	,np,curr_day_soil_unsaturated_storage_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fwrite(soil_water_table		,sizeof(float)	,np,curr_day_soil_water_table_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fwrite(buff_soil_temp		,sizeof(float)	,np,curr_day_soil_temp_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
////取消注释
//                else if (fwrite(buffer_nitrogen		,sizeof(float)	,np,curr_day_nitrogen_ptr)
//                         !=(size_t)np)
//                    rcode = PERROR;
//                else if (fwrite(buffer_CNcd		,sizeof(float)	,np,curr_day_CNcd_ptr)
//                         !=(size_t)np)
//                    rcode = PERROR;
//                else if (fwrite(buffer_CNssd		,sizeof(float)	,np,curr_day_CNssd_ptr)
//                         !=(size_t)np)
//                    rcode = PERROR;
//                else if (fwrite(buffer_CNsmd		,sizeof(float)	,np,curr_day_CNsmd_ptr)
//                         !=(size_t)np)
//                    rcode = PERROR;
//                else if (fwrite(buffer_CNfsd		,sizeof(float)	,np,curr_day_CNfsd_ptr)
//                         !=(size_t)np)
//                    rcode = PERROR;
//                else if (fwrite(buffer_CNfmd		,sizeof(float)	,np,curr_day_CNfmd_ptr)
//                         !=(size_t)np)
//                    rcode = PERROR;
//                else if (fwrite(buffer_CNsm		,sizeof(float)	,np,curr_day_CNsm_ptr)
//                         !=(size_t)np)
//                    rcode = PERROR;
//                else if (fwrite(buffer_CNm		,sizeof(float)	,np,curr_day_CNm_ptr)
//                         !=(size_t)np)
//                    rcode = PERROR;
//                else if (fwrite(buffer_CNs		,sizeof(float)	,np,curr_day_CNs_ptr)
//                         !=(size_t)np)
//                    rcode = PERROR;
//                else if (fwrite(buffer_CNp		,sizeof(float)	,np,curr_day_CNp_ptr)
//                         !=(size_t)np)
//                    rcode = PERROR;
//                else if (fwrite(buffer_CNw		,sizeof(float)	,np,curr_day_CNw_ptr)
//                         !=(size_t)np)
//                    rcode = PERROR;
//                else if (fwrite(buffer_CNfr		,sizeof(float)	,np,curr_day_CNfr_ptr)
//                         !=(size_t)np)
//                    rcode = PERROR;
//                else if (fwrite(buffer_CNl		,sizeof(float)	,np,curr_day_CNl_ptr)
//                         !=(size_t)np)
//                    rcode = PERROR;
////取消注释
                else if (fwrite(buff_ST_Ly1		,sizeof(float)	,np,curr_day_ST_Ly1_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fwrite(buff_ST_Ly2		,sizeof(float)	,np,curr_day_ST_Ly2_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fwrite(buff_ST_Ly3		,sizeof(float)	,np,curr_day_ST_Ly3_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fwrite(buff_ST_Ly4		,sizeof(float)	,np,curr_day_ST_Ly4_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fwrite(buff_ST_Ly5		,sizeof(float)	,np,curr_day_ST_Ly5_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fwrite(buff_ST_Ly6		,sizeof(float)	,np,curr_day_ST_Ly6_ptr)
                         !=(size_t)np)
                    rcode = PERROR;

////  取消注释
//                else if (fwrite(buff_pool1		,sizeof(float)	,np,curr_day_pool1_ptr)
//                           !=(size_t)np)
//                    rcode = PERROR;
//                else if (fwrite(buff_pool2		,sizeof(float)	,np,curr_day_pool2_ptr)
//                           !=(size_t)np)
//                    rcode = PERROR;
//                else if (fwrite(buff_pool3		,sizeof(float)	,np,curr_day_pool3_ptr)
//                           !=(size_t)np)
//                    rcode = PERROR;
//                else if (fwrite(buff_pool4		,sizeof(float)	,np,curr_day_pool4_ptr)
//                           !=(size_t)np)
//                    rcode = PERROR;
//                else if (fwrite(buff_pool5		,sizeof(float)	,np,curr_day_pool5_ptr)
//                           !=(size_t)np)
//                    rcode = PERROR;
//                  else if (fwrite(buff_pool6		,sizeof(float)	,np,curr_day_pool6_ptr)
//                           !=(size_t)np)
//                      rcode = PERROR;
//                  else if (fwrite(buff_pool7		,sizeof(float)	,np,curr_day_pool7_ptr)
//                           !=(size_t)np)
//                      rcode = PERROR;
//                  else if (fwrite(buff_pool8		,sizeof(float)	,np,curr_day_pool8_ptr)
//                           !=(size_t)np)
//                      rcode = PERROR;
//                  else if (fwrite(buff_pool9		,sizeof(float)	,np,curr_day_pool9_ptr)
//                           !=(size_t)np)
//                      rcode = PERROR;
//                  else if (fwrite(bio_pool1		,sizeof(float)	,np,curr_day_bio_pool1_ptr)
//                           !=(size_t)np)
//                      rcode = PERROR;
//                  else if (fwrite(bio_pool2		,sizeof(float)	,np,curr_day_bio_pool2_ptr)
//                           !=(size_t)np)
//                      rcode = PERROR;
//                  else if (fwrite(bio_pool3		,sizeof(float)	,np,curr_day_bio_pool3_ptr)
//                           !=(size_t)np)
//                      rcode = PERROR;
//                  else if (fwrite(bio_pool4		,sizeof(float)	,np,curr_day_bio_pool4_ptr)
//                           !=(size_t)np)
//                      rcode = PERROR;
////取消注释


                else if (fwrite(soil_pondwater		,sizeof(float)	,np,curr_day_soil_pondwater_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fwrite(soil_capillary_rise		,sizeof(float)	,np,curr_day_soil_capillary_rise_ptr)
                         !=(size_t)np)
                    rcode = PERROR;
                else if (fwrite(soil_percolation		,sizeof(float)	,np,curr_day_soil_percolation_ptr)
                         !=(size_t)np)
                    rcode = PERROR;

                if (	(fwrite(runoff_total			,sizeof(float),np,runoff_total_ptr)			!=(size_t)np)  //24jun
                        ||	(fwrite(runoff_baseflow			,sizeof(float),np,runoff_baseflow_ptr)		!=(size_t)np)
                        ||	(fwrite(Daily_NEP				,sizeof(float),np,Daily_NEP_ptr)	!=(size_t)np)  // deleted in EPHYSE
                        ||	(fwrite(runoff_total_inflow		,sizeof(float),np,runoff_total_inflow_ptr)	!=(size_t)np)
                        ||	(fwrite(runoff_total_outflow	,sizeof(float),np,runoff_total_outflow_ptr)	!=(size_t)np))
                    rcode = PERROR;
            }



        } //end of line

        //printf("ok3");  正常
//        printf("U N N O R M A !!!");


        if (prev_day_soil_saturation_deficit_ptr)
            fclose(prev_day_soil_saturation_deficit_ptr);
        prev_day_soil_saturation_deficit_ptr = (FILE*)NULL;

        if (prev_day_soil_unsaturated_storage_ptr)
            fclose(prev_day_soil_unsaturated_storage_ptr);
        prev_day_soil_unsaturated_storage_ptr = (FILE*)NULL;

        if (prev_day_soil_water_table_ptr)
            fclose(prev_day_soil_water_table_ptr);
        prev_day_soil_water_table_ptr = (FILE*)NULL;

        if (prev_day_soil_temp_ptr)
            fclose(prev_day_soil_temp_ptr);
        prev_day_soil_temp_ptr = (FILE*)NULL;

        if (prev_day_nitrogen_ptr)
            fclose(prev_day_nitrogen_ptr);
        prev_day_nitrogen_ptr = (FILE*)NULL;


        if (prev_day_snow_depth_ptr)
            fclose(prev_day_snow_depth_ptr);
        prev_day_snow_depth_ptr= (FILE*)NULL;


        if (prev_day_CNcd_ptr)
            fclose(prev_day_CNcd_ptr);
        prev_day_CNcd_ptr = (FILE*)NULL;

        if (prev_day_CNssd_ptr)
            fclose(prev_day_CNssd_ptr);
        prev_day_CNssd_ptr = (FILE*)NULL;

        if (prev_day_CNsmd_ptr)
            fclose(prev_day_CNsmd_ptr);
        prev_day_CNsmd_ptr = (FILE*)NULL;

        if (prev_day_CNfsd_ptr)
            fclose(prev_day_CNfsd_ptr);
        prev_day_CNfsd_ptr = (FILE*)NULL;

        if (prev_day_CNfmd_ptr)
            fclose(prev_day_CNfmd_ptr);
        prev_day_CNfmd_ptr = (FILE*)NULL;

        if (prev_day_CNsm_ptr)
            fclose(prev_day_CNsm_ptr);
        prev_day_CNsm_ptr = (FILE*)NULL;

        if (prev_day_CNm_ptr)
            fclose(prev_day_CNm_ptr);
        prev_day_CNm_ptr = (FILE*)NULL;

        if (prev_day_CNs_ptr)
            fclose(prev_day_CNs_ptr);
        prev_day_CNs_ptr = (FILE*)NULL;

        if (prev_day_CNp_ptr)
            fclose(prev_day_CNp_ptr);
        prev_day_CNp_ptr = (FILE*)NULL;

        if (prev_day_CNw_ptr)
            fclose(prev_day_CNw_ptr);
        prev_day_CNw_ptr = (FILE*)NULL;

        if (prev_day_CNfr_ptr)
            fclose(prev_day_CNfr_ptr);
        prev_day_CNfr_ptr = (FILE*)NULL;

        if (prev_day_CNl_ptr)
            fclose(prev_day_CNl_ptr);
        prev_day_CNl_ptr = (FILE*)NULL;

        //printf("ok3");    运行正常

        if (prev_day_ST_Ly1_ptr)
            fclose(prev_day_ST_Ly1_ptr);
        prev_day_ST_Ly1_ptr = (FILE*)NULL;

        if (prev_day_ST_Ly2_ptr)
            fclose(prev_day_ST_Ly2_ptr);
        prev_day_ST_Ly2_ptr = (FILE*)NULL;

        if (prev_day_ST_Ly3_ptr)
            fclose(prev_day_ST_Ly3_ptr);
        prev_day_ST_Ly3_ptr = (FILE*)NULL;

        if (prev_day_ST_Ly4_ptr)
            fclose(prev_day_ST_Ly4_ptr);
        prev_day_ST_Ly4_ptr = (FILE*)NULL;

        if (prev_day_ST_Ly5_ptr)
            fclose(prev_day_ST_Ly5_ptr);
        prev_day_ST_Ly5_ptr = (FILE*)NULL;

        if (prev_day_ST_Ly6_ptr)
            fclose(prev_day_ST_Ly6_ptr);
        prev_day_ST_Ly6_ptr = (FILE*)NULL;

        //printf("ok3");  运行正常

        if (prev_day_pool1_ptr)
            fclose(prev_day_pool1_ptr);
        prev_day_pool1_ptr = (FILE*)NULL;
        if (prev_day_pool2_ptr)
            fclose(prev_day_pool2_ptr);
        prev_day_pool2_ptr = (FILE*)NULL;
        if (prev_day_pool3_ptr)
            fclose(prev_day_pool3_ptr);
        prev_day_pool3_ptr = (FILE*)NULL;
        if (prev_day_pool4_ptr)
            fclose(prev_day_pool4_ptr);
        prev_day_pool4_ptr = (FILE*)NULL;
        if (prev_day_pool5_ptr)
            fclose(prev_day_pool5_ptr);
        prev_day_pool5_ptr = (FILE*)NULL;
        if (prev_day_pool6_ptr)
            fclose(prev_day_pool6_ptr);
        prev_day_pool6_ptr = (FILE*)NULL;
        if (prev_day_pool7_ptr)
            fclose(prev_day_pool7_ptr);
        prev_day_pool7_ptr = (FILE*)NULL;
        if (prev_day_pool8_ptr)
            fclose(prev_day_pool8_ptr);
        prev_day_pool8_ptr = (FILE*)NULL;
        if (prev_day_pool9_ptr)
            fclose(prev_day_pool9_ptr);
        prev_day_pool9_ptr = (FILE*)NULL;

        if (prev_day_bio_pool1_ptr)
            fclose(prev_day_bio_pool1_ptr);
        prev_day_bio_pool1_ptr = (FILE*)NULL;


        if (prev_day_bio_pool2_ptr)
            fclose(prev_day_bio_pool2_ptr);
        prev_day_bio_pool2_ptr = (FILE*)NULL;

        if (prev_day_bio_pool3_ptr)
            fclose(prev_day_bio_pool3_ptr);
        prev_day_bio_pool3_ptr = (FILE*)NULL;

        if (prev_day_bio_pool4_ptr)
            fclose(prev_day_bio_pool4_ptr);
        prev_day_bio_pool4_ptr = (FILE*)NULL;

        if (prev_day_soil_pondwater_ptr)
            fclose(prev_day_soil_pondwater_ptr);
        prev_day_soil_pondwater_ptr = (FILE*)NULL;

        if (curr_day_soil_saturation_deficit_ptr)
            fclose(curr_day_soil_saturation_deficit_ptr);
        curr_day_soil_saturation_deficit_ptr = (FILE*)NULL;
        if (curr_day_soil_unsaturated_storage_ptr)
            fclose(curr_day_soil_unsaturated_storage_ptr);
        curr_day_soil_unsaturated_storage_ptr = (FILE*)NULL;
        if (curr_day_soil_water_table_ptr)
            fclose(curr_day_soil_water_table_ptr);
        curr_day_soil_water_table_ptr = (FILE*)NULL;

        if (curr_day_soil_temp_ptr)
            fclose(curr_day_soil_temp_ptr);
        curr_day_soil_temp_ptr = (FILE*)NULL;

//// 取消过注释
//        if (curr_day_nitrogen_ptr)
//            fclose(curr_day_nitrogen_ptr);
//        curr_day_nitrogen_ptr = (FILE*)NULL;
//        //printf("ok3"); //运行正常
//        //printf("U N N O R M A !!!");
//
//        if (curr_day_CNcd_ptr)
//            fclose(curr_day_CNcd_ptr);
//        curr_day_CNcd_ptr = (FILE*)NULL;
//        //printf("ok3"); //运行正常
//
//        if (curr_day_CNssd_ptr)
//            fclose(curr_day_CNssd_ptr);
//        curr_day_CNssd_ptr = (FILE*)NULL;
//        //printf("ok3"); //运行正常
//
//        if (curr_day_CNsmd_ptr)
//            fclose(curr_day_CNsmd_ptr);
//        curr_day_CNsmd_ptr = (FILE*)NULL;
//        //printf("ok3"); //运行正常
//        //printf("U N N O R M A !!!");
//
//        if (curr_day_CNfsd_ptr)
//            fclose(curr_day_CNfsd_ptr);
//        curr_day_CNfsd_ptr = (FILE*)NULL;
       //printf("ok3"); //运行正常
//        printf("U N N O R M A !!!");
//// 取消过注释

//// 取消过注释
//        if (curr_day_CNfmd_ptr)
//            fclose(curr_day_CNfmd_ptr);
//        curr_day_CNfmd_ptr = (FILE*)NULL;
//        //printf("ok3"); //运行正常
//        //printf("U N N O R M A !!!");   //新增注释
//        if (curr_day_CNsm_ptr)          //注释
//            fclose(curr_day_CNsm_ptr);
//        curr_day_CNsm_ptr = (FILE*)NULL;
//        if (curr_day_CNm_ptr)
//            fclose(curr_day_CNm_ptr);
//        curr_day_CNm_ptr = (FILE*)NULL;
//        if (curr_day_CNs_ptr)
//            fclose(curr_day_CNs_ptr);
//        curr_day_CNs_ptr = (FILE*)NULL;
//        if (curr_day_CNp_ptr)
//            fclose(curr_day_CNp_ptr);
//        curr_day_CNp_ptr = (FILE*)NULL;
//        if (curr_day_CNw_ptr)
//            fclose(curr_day_CNw_ptr);
//        curr_day_CNw_ptr = (FILE*)NULL;
//        if (curr_day_CNfr_ptr)
//            fclose(curr_day_CNfr_ptr);
//        curr_day_CNfr_ptr = (FILE*)NULL;
//        if (curr_day_CNl_ptr)
//            fclose(curr_day_CNl_ptr);
//        curr_day_CNl_ptr = (FILE*)NULL;
//        //printf("ok3");  //运行错误
//// 取消过注释

        if (curr_day_ST_Ly1_ptr)
            fclose(curr_day_ST_Ly1_ptr);
        curr_day_ST_Ly1_ptr = (FILE*)NULL;

        if (curr_day_ST_Ly2_ptr)
            fclose(curr_day_ST_Ly2_ptr);
        curr_day_ST_Ly2_ptr = (FILE*)NULL;

        if (curr_day_ST_Ly3_ptr)
            fclose(curr_day_ST_Ly3_ptr);
        curr_day_ST_Ly3_ptr = (FILE*)NULL;

        if (curr_day_ST_Ly4_ptr)
            fclose(curr_day_ST_Ly4_ptr);
        curr_day_ST_Ly4_ptr = (FILE*)NULL;

        if (curr_day_ST_Ly5_ptr)
            fclose(curr_day_ST_Ly5_ptr);
        curr_day_ST_Ly5_ptr = (FILE*)NULL;

        if (curr_day_ST_Ly6_ptr)
            fclose(curr_day_ST_Ly6_ptr);
        curr_day_ST_Ly6_ptr = (FILE*)NULL;

//// 取消过注释
//        if (curr_day_pool1_ptr)
//            fclose(curr_day_pool1_ptr);
//        curr_day_pool1_ptr = (FILE*)NULL;
//
//        if (curr_day_pool2_ptr)
//            fclose(curr_day_pool2_ptr);
//        curr_day_pool2_ptr = (FILE*)NULL;
//
//        if (curr_day_pool3_ptr)
//            fclose(curr_day_pool3_ptr);
//        curr_day_pool3_ptr = (FILE*)NULL;
//
//        if (curr_day_pool4_ptr)
//            fclose(curr_day_pool4_ptr);
//        curr_day_pool4_ptr = (FILE*)NULL;
//
//        if (curr_day_pool5_ptr)
//            fclose(curr_day_pool5_ptr);
//        curr_day_pool5_ptr = (FILE*)NULL;
//
//        if (curr_day_pool6_ptr)
//            fclose(curr_day_pool6_ptr);
//        curr_day_pool6_ptr = (FILE*)NULL;
//
//        if (curr_day_pool7_ptr)
//            fclose(curr_day_pool7_ptr);
//        curr_day_pool7_ptr = (FILE*)NULL;
//
//        if (curr_day_pool8_ptr)
//            fclose(curr_day_pool8_ptr);
//        curr_day_pool8_ptr = (FILE*)NULL;
//
//        if (curr_day_pool9_ptr)
//            fclose(curr_day_pool9_ptr);
//        curr_day_pool9_ptr = (FILE*)NULL;
//
//        if (curr_day_bio_pool1_ptr)
//            fclose(curr_day_bio_pool1_ptr);
//        curr_day_bio_pool1_ptr = (FILE*)NULL;
//
//        if (curr_day_bio_pool2_ptr)
//            fclose(curr_day_bio_pool2_ptr);
//        curr_day_bio_pool2_ptr = (FILE*)NULL;
//
//        if (curr_day_bio_pool3_ptr)
//            fclose(curr_day_bio_pool3_ptr);
//        curr_day_bio_pool3_ptr = (FILE*)NULL;
//
//        if (curr_day_bio_pool4_ptr)
//            fclose(curr_day_bio_pool4_ptr);
//        curr_day_bio_pool4_ptr = (FILE*)NULL;
//// 取消过注释

        if (curr_day_soil_pondwater_ptr)
            fclose(curr_day_soil_pondwater_ptr);
        curr_day_soil_pondwater_ptr = (FILE*)NULL;

        if (curr_day_soil_capillary_rise_ptr)
            fclose(curr_day_soil_capillary_rise_ptr);
        curr_day_soil_capillary_rise_ptr = (FILE*)NULL;

        if (curr_day_soil_percolation_ptr)
            fclose(curr_day_soil_percolation_ptr);
        curr_day_soil_percolation_ptr = (FILE*)NULL;

        //printf("ok3");     // 运行正常

        if (climate_rad_r_ptr)
            fclose(climate_rad_r_ptr);
        climate_rad_r_ptr					= (FILE*)NULL;

        if (climate_rad_f_ptr)
            fclose(climate_rad_f_ptr);
        climate_rad_f_ptr					= (FILE*)NULL;

        if (climate_ti_ptr)
            fclose(climate_ti_ptr);
        climate_ti_ptr					= (FILE*)NULL;

        if (climate_tm_ptr)
            fclose(climate_tm_ptr);
        climate_tm_ptr					= (FILE*)NULL;

        if (climate_prec_ptr)
            fclose(climate_prec_ptr);
        climate_prec_ptr				= (FILE*)NULL;

        //printf("ok3");       运行正常

        if (laifile_ptr)
            fclose(laifile_ptr);
        laifile_ptr				= (FILE*)NULL;

        if (waterin_ptr)
            fclose(waterin_ptr);
        waterin_ptr				= (FILE*)NULL;

        if (curr_day_snow_depth_ptr)
            fclose(curr_day_snow_depth_ptr);
        curr_day_snow_depth_ptr= (FILE*)NULL;

        if (Daily_NPP_ptr)   //npp to tl
            fclose(Daily_NPP_ptr);
        Daily_NPP_ptr				= (FILE*)NULL;

        if (climate_dew_ptr)
            fclose(climate_dew_ptr);
        climate_dew_ptr					= (FILE*)NULL;

        if (climate_wind_ptr)
            fclose(climate_wind_ptr);
        climate_wind_ptr					= (FILE*)NULL;

        if (canopy_evaporation_ptr)
            fclose(canopy_evaporation_ptr);
        canopy_evaporation_ptr			= (FILE*)NULL;

        if (canopy_Stomata_ptr)
            fclose(canopy_Stomata_ptr);
        canopy_Stomata_ptr			= (FILE*)NULL;

        //printf("ok3");      运行正常

        if (canopy_transpiration_unsat_ptr)
            fclose(canopy_transpiration_unsat_ptr);
        canopy_transpiration_unsat_ptr	= (FILE*)NULL;
        if (canopy_transpiration_sat_ptr)
            fclose(canopy_transpiration_sat_ptr);
        canopy_transpiration_sat_ptr	= (FILE*)NULL;
        if (canopy_intercepted_ptr)
            fclose(canopy_intercepted_ptr);
        canopy_intercepted_ptr			= (FILE*)NULL;
        if (canopy_litter_evaporation_ptr)
            fclose(canopy_litter_evaporation_ptr);
        canopy_litter_evaporation_ptr	= (FILE*)NULL;
        if (canopy_moss_transpiration_ptr)
            fclose(canopy_moss_transpiration_ptr);
        canopy_moss_transpiration_ptr	= (FILE*)NULL;
        if (canopy_soil_evaporation_ptr)
            fclose(canopy_soil_evaporation_ptr);
        canopy_soil_evaporation_ptr		= (FILE*)NULL;

        if (runoff_total_ptr)
            fclose(runoff_total_ptr);
        runoff_total_ptr				=(FILE*)NULL;
        if (runoff_baseflow_ptr)
            fclose(runoff_baseflow_ptr);
        runoff_baseflow_ptr				=(FILE*)NULL;

        //  printf("ok3");  运行正常

        if (Daily_NEP_ptr)
            fclose(Daily_NEP_ptr);
        Daily_NEP_ptr				=(FILE*)NULL;

        if (runoff_total_inflow_ptr)
            fclose(runoff_total_inflow_ptr);
        runoff_total_inflow_ptr			=(FILE*)NULL;
        if (runoff_total_outflow_ptr)
            fclose(runoff_total_outflow_ptr);
        runoff_total_outflow_ptr		=(FILE*)NULL;

        //printf("ok3");  //运行正常


    }//end of daily
    //printf("ok3");         // 运行正常




//free memory:
    if (temp_uc_buff)
        free(temp_uc_buff);
    //printf("ok3");
    if (temp_sand_buff)
        free(temp_sand_buff);
    //printf("ok3");

//    if (temp_silt_buff)           //注释
//        free(temp_silt_buff);
//

//    if (temp_clay_buff)
//        free(temp_clay_buff);
//   //printf("ok3");  出错

//    if (temp_om_buff)
//        free(temp_om_buff);
//    //printf("ok3");  出错

    if (lc)
        free(lc);
//    if (awc)
//        free(awc);
    if (lai)
        free(lai);



    if (lon)
        free(lon);
    if (lat)
        free(lat);

    if (pFloatOutput)
        free(pFloatOutput);
    if (xSoil)
        free(xSoil);
    if (xx)
        free(xx);
    if (sdat)
        free(sdat);

    if (canopy)
        free(canopy);
    if (canopy_evaporation)
        free(canopy_evaporation);

    if (canopy_transpiration_unsat)
        free(canopy_transpiration_unsat);
    if (canopy_transpiration_sat)
        free(canopy_transpiration_sat);
    if (canopy_intercepted)
        free(canopy_intercepted);
    if (canopy_litter_evaporation)
        free(canopy_litter_evaporation);
    if (canopy_moss_transpiration)
        free(canopy_moss_transpiration);
    if (canopy_soil_evaporation)
        free(canopy_soil_evaporation);

    if (canopy_stomata)
        free(canopy_stomata);

    printf("ok3");

    if (g_model)
        free(g_model);
    if (z_model)
        free(z_model);

    if (climate_rad_r)
        free(climate_rad_r);

    if (climate_rad_f)
        free(climate_rad_f);
    if (climate_ti)
        free(climate_ti);
    if (climate_tm)
        free(climate_tm);
    if (climate_prec)
        free(climate_prec);
    if (climate_dew)
        free(climate_dew);

    if (climate_wind)
        free(climate_wind);

    if (soil)
        free(soil);
    if (soil_3r)
        free(soil_3r);
    if (soil_K0_decay_m)
        free(soil_K0_decay_m);
    if (soil_b)
        free(soil_b);
    if (soil_saturation_suction)
        free(soil_saturation_suction);
    if (soil_saturated_Kv)
        free(soil_saturated_Kv);
    if (soil_saturated_Kh)
        free(soil_saturated_Kh);

    if (soil_saturation_deficit)
        free(soil_saturation_deficit);
    if (soil_unsaturated_storage)
        free(soil_unsaturated_storage);
    if (soil_water_table)
        free(soil_water_table);

    if (buff_soil_temp) /* 2nov2006 */
        free(buff_soil_temp);

    if (buffer_nitrogen) /* 2nov2006 */
        free(buffer_nitrogen);



    if (buffer_CNcd)
        free(buffer_CNcd);

    if (buffer_CNssd)
        free(buffer_CNssd);

    if (buffer_CNsmd)
        free(buffer_CNsmd);

    if (buffer_CNfsd)
        free(buffer_CNfsd);

    if (buffer_CNfmd)
        free(buffer_CNfmd);

    if (buffer_CNsm)
        free(buffer_CNsm);

    if (buffer_CNm)
        free(buffer_CNm);

    if (buffer_CNs)
        free(buffer_CNs);

    if (buffer_CNp)
        free(buffer_CNp);

    if (buffer_CNw)
        free(buffer_CNw);

    if (buffer_CNfr)
        free(buffer_CNfr);

    if (buffer_CNl)
        free(buffer_CNl);

    if (buff_ST_Ly1)
        free(buff_ST_Ly1);

    if (buff_ST_Ly2)
        free(buff_ST_Ly2);

    if (buff_ST_Ly3)
        free(buff_ST_Ly3);



    if (buff_ST_Ly4)
        free(buff_ST_Ly4);

    if (buff_ST_Ly5)
        free(buff_ST_Ly5);


    if (buff_ST_Ly6)
        free(buff_ST_Ly6);


//    if (daily_soil_resp) /* 27 jan2007 */
//        free(daily_soil_resp);

    if (buff_pool1) /* pool */
        free(buff_pool1);

    if (buff_pool2)
        free(buff_pool2);

    if (buff_pool3)
        free(buff_pool3);

    if (buff_pool4)
        free(buff_pool4);

    if (buff_pool5)
        free(buff_pool5);

    if (buff_pool6)
        free(buff_pool6);

    if (buff_pool7)
        free(buff_pool7);

    if (buff_pool8)
        free(buff_pool8);

    if (buff_pool9)
        free(buff_pool9);

    if (bio_pool1)
        free(bio_pool1);

    if (bio_pool2)
        free(bio_pool2);

    if (bio_pool3)
        free(bio_pool3);

    if (bio_pool4)
        free(bio_pool4);

    if (soil_pondwater)  //pond//
        free(soil_pondwater);

    if (soil_Max_depth_Z)
        free(soil_Max_depth_Z);

    if (soil_capillary_rise)
        free(soil_capillary_rise);
    if (soil_percolation)
        free(soil_percolation);

    if (soil_K0_decay_m_3r)
        free(soil_K0_decay_m_3r);
    if (soil_b_3r)
        free(soil_b_3r);
    if (soil_saturation_suction_3r)
        free(soil_saturation_suction_3r);
    if (soil_saturated_Kv_3r)
        free(soil_saturated_Kv_3r);
    if (soil_saturated_Kh_3r)
        free(soil_saturated_Kh_3r);

    if (soil_saturation_deficit_3r)
        free(soil_saturation_deficit_3r);
    if (soil_unsaturated_storage_3r)
        free(soil_unsaturated_storage_3r);
    if (soil_water_table_3r)
        free(soil_water_table_3r);

    if (soil_temp_3r)
        free(soil_temp_3r); /* 2nov2006 */


    if (soil_nitrogen_3r)
        free(soil_nitrogen_3r); /* 2nov2006 */



    if (soil_CNcd_3r)
        free(soil_CNcd_3r);

    if (soil_CNssd_3r)
        free(soil_CNssd_3r);

    if (soil_CNsmd_3r)
        free(soil_CNsmd_3r);

    if (soil_CNfsd_3r)
        free(soil_CNfsd_3r);

    if (soil_CNfmd_3r)
        free(soil_CNfmd_3r);

    if (soil_CNsm_3r)
        free(soil_CNsm_3r);

    if (soil_CNm_3r)
        free(soil_CNm_3r);

    if (soil_CNs_3r)
        free(soil_CNs_3r);

    if (soil_CNp_3r)
        free(soil_CNp_3r);

    if (soil_CNw_3r)
        free(soil_CNw_3r);

    if (soil_CNfr_3r)
        free(soil_CNfr_3r);

    if (soil_CNl_3r)
        free(soil_CNl_3r);


    if (soil_ST_Ly1_3r)
        free(soil_ST_Ly1_3r);

    if (soil_ST_Ly2_3r)
        free(soil_ST_Ly2_3r);

    if (soil_ST_Ly3_3r)
        free(soil_ST_Ly3_3r);

    if (soil_ST_Ly4_3r)
        free(soil_ST_Ly4_3r);

    if (soil_ST_Ly5_3r)
        free(soil_ST_Ly5_3r);

    if (soil_ST_Ly6_3r)
        free(soil_ST_Ly6_3r);


    if (soil_pool1_3r)
        free(soil_pool1_3r);

    if (soil_pool2_3r)
        free(soil_pool2_3r);

    if (soil_pool3_3r)
        free(soil_pool3_3r);

    if (soil_pool4_3r)
        free(soil_pool4_3r);

    if (soil_pool5_3r)
        free(soil_pool5_3r);

    if (soil_pool6_3r)
        free(soil_pool6_3r);

    if (soil_pool7_3r)
        free(soil_pool7_3r);

    if (soil_pool8_3r)
        free(soil_pool8_3r);

    if (soil_pool9_3r)
        free(soil_pool9_3r);

    if (soil_bio_pool1_3r)
        free(soil_bio_pool1_3r);

    if (soil_bio_pool2_3r)
        free(soil_bio_pool2_3r);

    if (soil_bio_pool3_3r)
        free(soil_bio_pool3_3r);

    if (soil_bio_pool4_3r)
        free(soil_bio_pool4_3r);

    if (soil_pondwater_3r) //pond
        free(soil_pondwater_3r);

    if (soil_Max_depth_Z_3r)
        free(soil_Max_depth_Z_3r);

    if (soil_texture)
        free(soil_texture);


//    if (soil_surf_porosity)
//        free(soil_surf_porosity);
    if (soil_surf_k0v)
        free(soil_surf_k0v);
    if (soil_surf_k0h)
        free(soil_surf_k0h);
    if (soil_init_z)
        free(soil_init_z);

    if (soil_init_temp)
        free(soil_init_temp);

    if (carbon_pool1)
        free(carbon_pool1);

    if (carbon_pool2)
        free(carbon_pool2);

    if (carbon_pool3)
        free(carbon_pool3);

    if (carbon_pool4)
        free(carbon_pool4);

    if (carbon_pool5)
        free(carbon_pool5);

    if (carbon_pool6)
        free(carbon_pool6);

    if (carbon_pool7)
        free(carbon_pool7);

    if (carbon_pool8)
        free(carbon_pool8);

    if (carbon_pool9)
        free(carbon_pool9);


    if (biomass_pool1)
        free(biomass_pool1);

    if (biomass_pool2)
        free(biomass_pool2);

    if (biomass_pool3)
        free(biomass_pool3);

    if (biomass_pool4)
        free(biomass_pool4);


    if (soil_depth)
        free(soil_depth);

//    if (soilindex)
//        free(soilindex);
    if (Array_Elevation_3r)
        free(Array_Elevation_3r);
    if (Array_WElevation_3r)
        free(Array_WElevation_3r);

//    if (PondWater)
//        free(PondWater);
    if (Array_Label_3r)
        free(Array_Label_3r);
    if (watershed)
        free(watershed);

    if (runoff_total)/*cancelled 24jun*/
        free(runoff_total);/*cancelled 24jun*/
    if (runoff_baseflow)
        free(runoff_baseflow);

    if (Daily_NEP)
        free(Daily_NEP);

    if (soil_resp_x)
        free(soil_resp_x);


    if (runoff_total_inflow)
        free(runoff_total_inflow);
    if (runoff_total_outflow)
        free(runoff_total_outflow);

//close file pointers:
    if (soil_texture_file_ptr)
        fclose(soil_texture_file_ptr);
//    if (soil_surf_porosity_file_ptr)
//        fclose(soil_surf_porosity_file_ptr);
//    if (soil_surf_k0_file_ptr)
//        fclose(soil_surf_k0_file_ptr);
    if (soil_init_z_file_ptr)
        fclose(soil_init_z_file_ptr);
    if (soil_init_temp_file_ptr)
        fclose(soil_init_temp_file_ptr);

    if (carbon_pool1_file_ptr)
        fclose(carbon_pool1_file_ptr);

    if (carbon_pool2_file_ptr)
        fclose(carbon_pool2_file_ptr);

    if (carbon_pool3_file_ptr)
        fclose(carbon_pool3_file_ptr);

    if (carbon_pool4_file_ptr)
        fclose(carbon_pool4_file_ptr);

    if (carbon_pool5_file_ptr)
        fclose(carbon_pool5_file_ptr);

    if (carbon_pool6_file_ptr)
        fclose(carbon_pool6_file_ptr);

    if (carbon_pool7_file_ptr)
        fclose(carbon_pool7_file_ptr);

    if (carbon_pool8_file_ptr)
        fclose(carbon_pool8_file_ptr);

    if (carbon_pool9_file_ptr)
        fclose(carbon_pool9_file_ptr);


    if (biomass_pool1_file_ptr)
        fclose(biomass_pool1_file_ptr);


    if (biomass_pool2_file_ptr)
        fclose(biomass_pool2_file_ptr);


    if (biomass_pool3_file_ptr)
        fclose(biomass_pool3_file_ptr);


    if (biomass_pool4_file_ptr)
        fclose(biomass_pool4_file_ptr);



    if (soil_depth_file_ptr)
        fclose(soil_depth_file_ptr);


    if (curr_day_soil_saturation_deficit_ptr)
        fclose(curr_day_soil_saturation_deficit_ptr);
    if (curr_day_soil_unsaturated_storage_ptr)
        fclose(curr_day_soil_unsaturated_storage_ptr);
    if (curr_day_soil_water_table_ptr)
        fclose(curr_day_soil_water_table_ptr);

    if (curr_day_soil_temp_ptr)
        fclose(curr_day_soil_temp_ptr); /* 2nov2006  */

    if (curr_day_nitrogen_ptr)
        fclose(curr_day_nitrogen_ptr);


    if (curr_day_CNcd_ptr)
        fclose(curr_day_CNcd_ptr);

    if (curr_day_CNssd_ptr)
        fclose(curr_day_CNssd_ptr);

    if (curr_day_CNsmd_ptr)
        fclose(curr_day_CNsmd_ptr);

    if (curr_day_CNfsd_ptr)
        fclose(curr_day_CNfsd_ptr);

    if (curr_day_CNfmd_ptr)
        fclose(curr_day_CNfmd_ptr);

    if (curr_day_CNsm_ptr)
        fclose(curr_day_CNsm_ptr);

    if (curr_day_CNm_ptr)
        fclose(curr_day_CNm_ptr);

    if (curr_day_CNs_ptr)
        fclose(curr_day_CNs_ptr);

    if (curr_day_CNp_ptr)
        fclose(curr_day_CNp_ptr);

    if (curr_day_CNw_ptr)
        fclose(curr_day_CNw_ptr);

    if (curr_day_CNfr_ptr)
        fclose(curr_day_CNfr_ptr);

    if (curr_day_CNl_ptr)
        fclose(curr_day_CNl_ptr);

    if (curr_day_ST_Ly1_ptr)
        fclose(curr_day_ST_Ly1_ptr);

    if (curr_day_ST_Ly2_ptr)
        fclose(curr_day_ST_Ly2_ptr);


    if (curr_day_ST_Ly3_ptr)
        fclose(curr_day_ST_Ly3_ptr);


    if (curr_day_ST_Ly4_ptr)
        fclose(curr_day_ST_Ly4_ptr);

    if (curr_day_ST_Ly5_ptr)
        fclose(curr_day_ST_Ly5_ptr);

    if (curr_day_ST_Ly6_ptr)
        fclose(curr_day_ST_Ly6_ptr);


    if (curr_day_pool1_ptr)
        fclose(curr_day_pool1_ptr);

    if (curr_day_pool2_ptr)
        fclose(curr_day_pool2_ptr);

    if (curr_day_pool3_ptr)
        fclose(curr_day_pool3_ptr);

    if (curr_day_pool4_ptr)
        fclose(curr_day_pool4_ptr);

    if (curr_day_pool5_ptr)
        fclose(curr_day_pool5_ptr);

    if (curr_day_pool6_ptr)
        fclose(curr_day_pool6_ptr);

    if (curr_day_pool7_ptr)
        fclose(curr_day_pool7_ptr);

    if (curr_day_pool8_ptr)
        fclose(curr_day_pool8_ptr);

    if (curr_day_pool9_ptr)
        fclose(curr_day_pool9_ptr);

    if (curr_day_bio_pool1_ptr)
        fclose(curr_day_bio_pool1_ptr);

    if (curr_day_bio_pool2_ptr)
        fclose(curr_day_bio_pool2_ptr);

    if (curr_day_bio_pool3_ptr)
        fclose(curr_day_bio_pool3_ptr);

    if (curr_day_bio_pool4_ptr)
        fclose(curr_day_bio_pool4_ptr);


    if (curr_day_soil_pondwater_ptr)
        fclose(curr_day_soil_pondwater_ptr); //pond

    if ( soil_K0_decay_m_ptr)
        fclose( soil_K0_decay_m_ptr);
    if ( soil_saturation_suction_ptr)
        fclose( soil_saturation_suction_ptr);
    if ( soil_saturated_Kv_ptr)
        fclose( soil_saturated_Kv_ptr);
    if ( soil_saturated_Kh_ptr)
        fclose( soil_saturated_Kh_ptr);

    if (prev_day_soil_saturation_deficit_ptr)
        fclose(prev_day_soil_saturation_deficit_ptr);
    if (prev_day_soil_unsaturated_storage_ptr)
        fclose(prev_day_soil_unsaturated_storage_ptr);
    if (prev_day_soil_water_table_ptr)
        fclose(prev_day_soil_water_table_ptr);

    if (prev_day_soil_temp_ptr)
        fclose(prev_day_soil_temp_ptr); /* 2nov2006 */

    if (prev_day_nitrogen_ptr)
        fclose(prev_day_nitrogen_ptr);

    if (prev_day_CNcd_ptr)
        fclose(prev_day_CNcd_ptr);

    if (prev_day_CNssd_ptr)
        fclose(prev_day_CNssd_ptr);

    if (prev_day_CNsmd_ptr)
        fclose(prev_day_CNsmd_ptr);

    if (prev_day_CNfsd_ptr)
        fclose(prev_day_CNfsd_ptr);

    if (prev_day_CNfmd_ptr)
        fclose(prev_day_CNfmd_ptr);

    if (prev_day_CNsm_ptr)
        fclose(prev_day_CNsm_ptr);

    if (prev_day_CNm_ptr)
        fclose(prev_day_CNm_ptr);

    if (prev_day_CNs_ptr)
        fclose(prev_day_CNs_ptr);

    if (prev_day_CNp_ptr)
        fclose(prev_day_CNp_ptr);

    if (prev_day_CNw_ptr)
        fclose(prev_day_CNw_ptr);

    if (prev_day_CNfr_ptr)
        fclose(prev_day_CNfr_ptr);

    if (prev_day_CNl_ptr)
        fclose(prev_day_CNl_ptr);

    if (prev_day_ST_Ly1_ptr)
        fclose(prev_day_ST_Ly1_ptr);

    if (prev_day_ST_Ly2_ptr)
        fclose(prev_day_ST_Ly2_ptr);

    if (prev_day_ST_Ly3_ptr)
        fclose(prev_day_ST_Ly3_ptr);

    if (prev_day_ST_Ly4_ptr)
        fclose(prev_day_ST_Ly4_ptr);

    if (prev_day_ST_Ly5_ptr)
        fclose(prev_day_ST_Ly5_ptr);

    if (prev_day_ST_Ly6_ptr)
        fclose(prev_day_ST_Ly6_ptr);

    if (prev_day_pool1_ptr)
        fclose(prev_day_pool1_ptr);

    if (prev_day_pool2_ptr)
        fclose(prev_day_pool2_ptr);

    if (prev_day_pool3_ptr)
        fclose(prev_day_pool3_ptr);

    if (prev_day_pool4_ptr)
        fclose(prev_day_pool4_ptr);

    if (prev_day_pool5_ptr)
        fclose(prev_day_pool5_ptr);

    if (prev_day_pool6_ptr)
        fclose(prev_day_pool6_ptr);

    if (prev_day_pool7_ptr)
        fclose(prev_day_pool7_ptr);

    if (prev_day_pool8_ptr)
        fclose(prev_day_pool8_ptr);

    if (prev_day_pool9_ptr)
        fclose(prev_day_pool9_ptr);

    if (prev_day_bio_pool1_ptr)
        fclose(prev_day_bio_pool1_ptr);

    if (prev_day_bio_pool2_ptr)
        fclose(prev_day_bio_pool2_ptr);

    if (prev_day_bio_pool3_ptr)
        fclose(prev_day_bio_pool3_ptr);

    if (prev_day_bio_pool4_ptr)
        fclose(prev_day_bio_pool4_ptr);


    if (prev_day_soil_pondwater_ptr) //pond
        fclose(prev_day_soil_pondwater_ptr);

    if (soil_Max_depth_Z_ptr)
        fclose(soil_Max_depth_Z_ptr);
    if (soil_b_ptr)
        fclose(soil_b_ptr);

    if (curr_day_soil_capillary_rise_ptr)
        fclose(curr_day_soil_capillary_rise_ptr);
    if (curr_day_soil_percolation_ptr)
        fclose(curr_day_soil_percolation_ptr);

    if (climate_rad_r_ptr)
        fclose(climate_rad_r_ptr);
    if (climate_rad_f_ptr)
        fclose(climate_rad_f_ptr);
    if (climate_ti_ptr)
        fclose(climate_ti_ptr);
    if (climate_tm_ptr)
        fclose(climate_tm_ptr);
    if (climate_prec_ptr)
        fclose(climate_prec_ptr);
    if (climate_dew_ptr)
        fclose(climate_dew_ptr);
    if (climate_wind_ptr)
        fclose(climate_wind_ptr);
//    if (climate_snowdepth_ptr)
//        fclose(climate_snowdepth_ptr);
//    if (climate_watertable_ptr)
//       fclose(climate_watertable_ptr);


    if (canopy_evaporation_ptr)
        fclose(canopy_evaporation_ptr);


    if (canopy_transpiration_unsat_ptr)
        fclose(canopy_transpiration_unsat_ptr);
    if (canopy_transpiration_sat_ptr)
        fclose(canopy_transpiration_sat_ptr);
    if (canopy_intercepted_ptr)
        fclose(canopy_intercepted_ptr);
    if (canopy_litter_evaporation_ptr)
        fclose(canopy_litter_evaporation_ptr);
    if (canopy_moss_transpiration_ptr)
        fclose(canopy_moss_transpiration_ptr);

    if (canopy_soil_evaporation_ptr)
        fclose(canopy_soil_evaporation_ptr);
    if (canopy_Stomata_ptr)
        fclose(canopy_Stomata_ptr);
    if ( NRFlux_ptr)
        fclose( NRFlux_ptr);
    if ( sensibleHeatFlux_ptr)
        fclose( sensibleHeatFlux_ptr);
    if ( latentHeatFlux_ptr)
        fclose( latentHeatFlux_ptr);

    if (runoff_total_ptr)/*cancelled 24jun*/
        fclose(runoff_total_ptr);/*cancelled 24jun*/

    if (runoff_baseflow_ptr)
        fclose(runoff_baseflow_ptr);

    if (Daily_NEP_ptr)
        fclose(Daily_NEP_ptr);

//    if (soil_resp_ptr)
//       fclose(soil_resp_ptr);

    if (runoff_total_inflow_ptr)
        fclose(runoff_total_inflow_ptr);
    if (runoff_total_outflow_ptr)
        fclose(runoff_total_outflow_ptr);

    if (lcfile_ptr)
        fclose(lcfile_ptr);
    if (Dem_ptr)
        fclose(Dem_ptr);
    if (Daily_NPP_ptr)
        fclose(Daily_NPP_ptr);
    if (canopy_ET_ptr)
        fclose(canopy_ET_ptr);
    if (canopy_UT_ptr)
        fclose(canopy_UT_ptr);


    if (canopy_Stomata_ptr)	//29nov2006
        fclose(canopy_Stomata_ptr);


    if (fwatershed)
        fclose(fwatershed);

    printf("end of main");




}	//end of main


