
//Define Constants:
#define DT_UNSIGNED_CHAR		0
#define DT_UNSIGNED_SHORT		1
#define DT_SIGNED_SHORT			2
#define DT_INT					3
#define DT_FLOAT				4
#define DT_DOUBLE				5

#define SOIL_TEXTURE_INDECES	12
#define BIO_PARAMS_NUMBER		36

#define NOPERROR				0
#define PERROR					1
#define PI						3.1415926
#define kstep                   86400
#define SIZEB					120
#define SIZEG 					120
#define SIZEX 					60	//11 nov ag inc to 50 from 40
#define SIZEZ 					60
//#define SIZEP 					10
#define RTIMES 					1
#define RPERIOD 				3600	/* in sec */

#define MAX_PATH				1000

#define DtoR					0.01745329
#define boltz 					5.67e-8
#define solar_constant			1367	// w per aquare meter
#define globe_radiation			342
#define INDEX(x,y,C)			((x)*C+(y)) //define a formula to convert 2-D index into 1-D
#define MAX(a,b) 				(a>b)?a:b
#define MIN(a,b)				(a<b)?a:b

//define structure used for writing output climate file
typedef struct
{
    float	rad;
    float	ti;
    float	tm;
    float	tmean;   //自行添加
    float	prec;
    float	dew;
    float	wind;
} Climate_t;

//define structure to hold the information of the first line of base weather station file
typedef struct
{
    double dLat;		//decimal degree of the Latitude of the base station
    double dLong;		//decimal degree of the Longitude of the base station. Negative for the West.
    double dElevation;	//meters
    double dLongref;	//The closest reference logitude for the base station
} baseline_t;

//define structure to hold the information of meteo. data in base weather station file
typedef struct
{
    int iday;
    double dTmax;
    double dTmin;
    double dTmean;				//degree C
    double dDewpoint;			//degree C
    double dPrecip;				//meter
    double dRadiation;			//w per m^2
    double dWind;

} base_t;

//Decla re structures:
struct fname
{
    char awcf[125];         /* Available water holding capacity file */
    char landcoverf[125];   /* Land cover file */
    char leafareaf[125];    /* Leaf area index file */
    char snowpackf[125];    /* Snow pack data file */
    char outf_name[125];
    char sBaseflowfile[125];
    char sDEM[125];
    char sWatershed[125];
    char cnpp_outf_name[125];
    char cet_outf_name[125];
    char tra_outf_name[125];
};

struct pubv
{
    int jday_start;    /* Year day start */
    int jday_end;      /* Year day end */
    int nlines;        /* Number of lines in study area */
    int npixels;       /* Number of pixels in study area */
    int iXsize;
    int iYsize;
    int factor;
    int output_interval;	/* MM 2005-Apr-18 allow output at intervals as well as daily */
    float ULLat;
    float ULLong;
    float LRLat;
    float LRLong;
    char output_NPP;
    char output_res;
    char output_eva;
    char output_tra;
    char output_site;
};

struct climatedata
{
    int pix;
    double tmax;
    double tmean;     //自行添加
    double tmin;
    double wind;
    double dewp;
    double srad;
    double frad;
    double precip;
};

struct xvalue
{
    int pix;
    double x1;		/* snow pack */
    double x2;		/* soil water */
    double x3;		/* out flow */
    double x4;		/* transpiration */
    double x5;		/* evaporation */
    double x6;		/* photosynthesis */
    double x7;		/* Rm */
    double x8;		/* leaf C */
    double x9;		/* stem C */
    double x10;		/* root C */
    double x11;		/* GPP */
    double x12;		/* ResSoil */
    double x13;		/* NEP */
    double x14;		/* M Res leaf */
    double x15;		/* M Res stem */
    double x16;		/* M Res root */
    double x17;		/* Number of days with rain */
    double x18;		/* under story Trans */
    double x19;     // water-table
    double x20;		// soil wilting point  MM 2005-Apr-25
    double x21;		// soil field capacity  MM 2005-Apr-25
    double x22;		// soil porosity  MM 2005-Apr-25
    double x23;	    //maximum soil surface conductance
    double x26;     //snow density
    double x27;     //snow depth
    double x28;     //water infiltration
    double x29;     //pond
    double x30;     //texture
    double x33;    //buff_soil_temp 自行添加
    double x36;     //nitrogen
    double x37;     //Ks
    double x38;      //prev_snowdepth 自行添加
    double x50;     //wood or stem
    double x51;    //coarse root
    double x52;    //leaf
    double x53;    //fine root

};

//Define Canopy Object
typedef struct
{
    float canopy_et;

    float canopy_evaporation;			//mm
    float canopy_transpiration_unsat;	//mm
    float canopy_transpiration_sat;		//mm
    float canopy_intercepted;
    float litter_evaporation;			//mm
    float moss_transpiration;			//mm
    float soil_evaporation;            //when water table <=0.01
    float canopy_ut;
    float canopy_stomata;
} Canopy_t;

//Define Climate Object
typedef struct
{
    float NRFlux;			//mm per day
    float sensibleHeatFlux;	// watts per square metre
    float latentHeatFlux;	// watts per square metre
} Energy;

//Define Snow Object
typedef struct
{
    float SWE;
    float Depth;
    float Density;
} Snow_t;

//Define Carbon Object
typedef struct
{
    float GPP;	//mm per day
    float NPP;	// watts per square metre
    float NEP;	// watts per square metre
    float Ra;
    float Rh;

} Carbon_t;


//Define Soil Object
typedef struct
{
    float K0_decay_m;					//soil parameter for Kz calculation
    float soil_b;
    float saturation_suction;			//suction in m when soil is saturation
    float saturated_Ks;					//at surface. m per day
    float saturated_Kv;
    float saturation_deficit;			//meter. Zero at saturation
    float unsaturated_storage;			//meter....MEM: of water in the unsaturated zone!!!
    float water_table;					//meter from soil surface measured below
    float soil_temp;//2nov2006
    float pondwater;						//meter from soil measured above
    float Max_depth_Z;					//meter
    //*****************
    float pool1;
    float pool2;
    float pool3;
    float pool4;
    float pool5;
    float pool6;
    float pool7;
    float pool8;
    float pool9;
    float poolb1;
    float poolb2;
    float poolb3;
    float poolb4;
    float soil_resp;
    float nitrogen;
    float CNcd_m;
    float CNssd_m;
    float CNsmd_m;
    float CNfsd_m;
    float CNfmd_m;
    float CNsm_m;
    float CNm_m;
    float CNs_m;
    float CNp_m;
    float CNw_m;
    float CNfr_m;
    float CNl_m;
    float ST_Layer_1;
    float ST_Layer_2;
    float ST_Layer_3;
    float ST_Layer_4;
    float ST_Layer_5;
    float ST_Layer_6;
    //*****************
} Soil_t;


typedef struct
{
    //coresponding the data columns of texture and default file
    int		mytexture;
    double	pore_index;				//m-1
    double	soil_b;					//unitless for b
    double	suction_head;			//meter
    double	soil_K0;
    double	max_z;
    double  wilting_pt;
    double  field_cap;
    double  porosity;
    double  MaxiGs;
    double  soil_K0H;
} Soil_index_t;

typedef struct
{
    double	dConifer;
    double	dDecidious;
    double	dMixed;
    double	dAgricultural;
    double	dPasture;
    double  dOpen;
    double	dWater;
    double  dUrban;
    double	dOther;
} Bio_params_t;

typedef struct
{
    int				iDayStart;
    int				iDayEnd;
    int				iNPPMultFactor;
    int				iNumLines;
    int				iNumPixels;
    int				iPixelX;
    int				iPixelY;
    float	        InitialSWE;
    float	        InitialSnowDEN;
    float			fULCLatitude;
    float			fULCLongitude;
    float			fLRCLatitude;
    float			fLRCLongitude;

    bool			bCalculateOrReadyAWC;
    int			    bCalculateClimate;
//	char			szInFileNameAWC[MAX_PATH];
    char			szInFileNameSand[MAX_PATH];
    char			szInFileNameSilt[MAX_PATH];
    char			szInFileNameClay[MAX_PATH];
    char			szInFileNameOM[MAX_PATH];

    char			szInFileNameLC[MAX_PATH];
    char			szInFileNameLAI[MAX_PATH];
    char			szInFileNameWatershed[MAX_PATH];
    char			szInFileNameDEM[MAX_PATH];
    char			szInFileNameSlope[MAX_PATH];
    char			szInFileNameAspect[MAX_PATH];

    char			szInFileNameBaseClimate[MAX_PATH];
    char			szInFileNameSoilTexture[MAX_PATH];
//	char			szInFileNameSoilSurfPorosity[MAX_PATH];
//	char			szInFileNameSoilSurfK0[MAX_PATH];
    char			szInFileNameSWE[MAX_PATH];
    char			szInFileNameSoilInitZ[MAX_PATH];
    char			szInFileNameSoilInitTemp[MAX_PATH]; /* 2nov2006*/
    char			szInFileNameSnowdensity[MAX_PATH];
    char			szInFileNameSoilDepth[MAX_PATH];
    //char			szInFileNameSoilInitTemp[MAX_PATH];
    char			szInFileNameCarbonPool1[MAX_PATH];
    char			szInFileNameCarbonPool2[MAX_PATH];
    char			szInFileNameCarbonPool3[MAX_PATH];
    char			szInFileNameCarbonPool4[MAX_PATH];
    char			szInFileNameCarbonPool5[MAX_PATH];
    char			szInFileNameCarbonPool6[MAX_PATH];
    char			szInFileNameCarbonPool7[MAX_PATH];
    char			szInFileNameCarbonPool8[MAX_PATH];
    char			szInFileNameCarbonPool9[MAX_PATH];
    char			szInFileNameBiomassPool1[MAX_PATH];
    char			szInFileNameBiomassPool2[MAX_PATH];
    char			szInFileNameBiomassPool3[MAX_PATH];
    char			szInFileNameBiomassPool4[MAX_PATH];
    Soil_index_t	SoilTextureIndexVals[SOIL_TEXTURE_INDECES];

} BH_SubParams1_t;

typedef struct
{
    char			szOutDirName[MAX_PATH];

    char			szOutFileNameClimateRAD_r[MAX_PATH];   //radiation
    char			szOutFileNameClimateRAD_f[MAX_PATH];   //radiation
    char			szOutFileNameClimateTi[MAX_PATH];	 //minimum temeprature
    char			szOutFileNameClimateTm[MAX_PATH];	 //maximum temperature
    char			szOutFileNameClimateTmean[MAX_PATH];	 //mean temperature 自行添加
    char			szOutFileNameClimatePrec[MAX_PATH];  //precipitation
    char			szOutFileNameClimateDew[MAX_PATH];	 //dew temperature
    char			szOutFileNameClimateWind[MAX_PATH];   //wind speed

    char			szOutFileNameWaterIn[MAX_PATH];      //water infiltration
    char            szOutFileNameSoilTemp[MAX_PATH]; // 2nov2006
    char            szOutFileNameNitrogen[MAX_PATH];
    char            szOutFileNamePool1[MAX_PATH];  // to avoid confusion, szOutFileNameCarbonPool1 renamed as szOutFileNamePool1
    char            szOutFileNamePool2[MAX_PATH];// szOutFileNameSoilTemp is diff from szOutFileNameSoilInitTemp
    char            szOutFileNamePool3[MAX_PATH];
    char            szOutFileNamePool4[MAX_PATH];
    char            szOutFileNamePool5[MAX_PATH];
    char            szOutFileNamePool6[MAX_PATH];
    char            szOutFileNamePool7[MAX_PATH];
    char            szOutFileNamePool8[MAX_PATH];
    char            szOutFileNamePool9[MAX_PATH];
    char            szOutFileNameB_Pool1[MAX_PATH];
    char            szOutFileNameB_Pool2[MAX_PATH];
    char            szOutFileNameB_Pool3[MAX_PATH];
    char            szOutFileNameB_Pool4[MAX_PATH];
    char            szOutFileNameCNcd[MAX_PATH];
    char            szOutFileNameCNssd[MAX_PATH];
    char            szOutFileNameCNsmd[MAX_PATH];
    char            szOutFileNameCNfsd[MAX_PATH];
    char            szOutFileNameCNfmd[MAX_PATH];
    char            szOutFileNameCNsm[MAX_PATH];
    char            szOutFileNameCNm[MAX_PATH];
    char            szOutFileNameCNs[MAX_PATH];
    char            szOutFileNameCNp[MAX_PATH];
    char            szOutFileNameCNw[MAX_PATH];
    char            szOutFileNameCNfr[MAX_PATH];
    char            szOutFileNameCNl[MAX_PATH];
    char            szOutFileNameST_Ly1[MAX_PATH];
    char            szOutFileNameST_Ly2[MAX_PATH];
    char            szOutFileNameST_Ly3[MAX_PATH];
    char            szOutFileNameST_Ly4[MAX_PATH];
    char            szOutFileNameST_Ly5[MAX_PATH];
    char            szOutFileNameST_Ly6[MAX_PATH];

    char			szOutFileNameSoilMaxDepthZ[MAX_PATH];
    char			szOutFileNameSoilK0DecayM[MAX_PATH];    //Hydrolic conductivity decay rate
    char			szOutFileNameSoilB[MAX_PATH];			// B value
    char			szOutFileNameSoilSatSuction[MAX_PATH];	// suction at saturation
    char			szOutFileNameSoilSatKv[MAX_PATH];        // saturated hydrolic conductivity
    char			szOutFileNameSoilSatKh[MAX_PATH];        // saturated hydrolic conductivity
    char			szOutFileNameCanopyET[MAX_PATH];

    char			szOutFileNameCanopyEvaporation[MAX_PATH];
    char			szOutFileNameCanopyIntercepted[MAX_PATH];
    char			szOutFileNameCanopyLitterEvaporation[MAX_PATH];
    char			szOutFileNameCanopyMossTransp[MAX_PATH];
    char			szOutFileNameCanopySoilEvaporation[MAX_PATH];
    char			szOutFileNameCanopyTranspSat[MAX_PATH];
    char			szOutFileNameCanopyTranspUnsat[MAX_PATH];
    char			szOutFileNameCanopyUT[MAX_PATH];
    char			szOutFileNameCanopyStomata[MAX_PATH];


    char			szOutFileNameSensibleHeatFlux[MAX_PATH];
    char			szOutFileNameLatentHeatFlux[MAX_PATH];
    char			szOutFileNameNRFlux[MAX_PATH];

    char			szOutFileNameGPP[MAX_PATH];
    char			szOutFileNameNPP[MAX_PATH];
    char			szOutFileNameNEP[MAX_PATH];
    char			szOutFileNameRa[MAX_PATH];
    char			szOutFileNameRh[MAX_PATH];

    char			szOutFileNameRunoffTotal[MAX_PATH];
    char			szOutFileNameRunoffBaseflow[MAX_PATH];
    char			szOutFileNameRunoffTotalInflow[MAX_PATH];
    char			szOutFileNameRunoffTotalOutflow[MAX_PATH];
    char			szOutFileNameSoilCapillaryRise[MAX_PATH];
    char			szOutFileNameSoilPercolation[MAX_PATH];
    char			szOutFileNameSoilSatDeficit[MAX_PATH];
    char			szOutFileNameSoilUnsatStorage[MAX_PATH];
    char			szOutFileNameSoilWaterTable[MAX_PATH];
    char			szOutFileNameSoilPondWater[MAX_PATH];//pond
    char			szOutFileNameSnowdepth[MAX_PATH];
    char			szOutFileNameSnowdensity[MAX_PATH];
    char			szOutFileNameSnowswe[MAX_PATH];
    char			szOutFileNameET[MAX_PATH];

    // record output interval and boolean values for each output parameter
    // 0 - don't record
    // 1 - record daily
    // # - record at # period

    int             iIntET;        //output interval for evapotranspiration
    int				iIntCpyEvap;	// output interval for canopy evaporation
    int				iIntCpyIntc;	// output interval for canopy intercepted water
    int				iIntCpyLitEvap; // output interval for canopy litter evaporation
    int				iIntCpySoiEvap; // output interval for soil evaporation
    int				iIntCpyMosTran; // output interval for moss transpiration


    int				iIntCpySatTran; // output interval for saturated transpiration
    int				iIntCpyUnsTran; // output interval for unsaturated transpiration
    int             iIntCpyUTTran;      //transpiration of understory

    int             iIntNR;         //Net Radiation
    int				iIntClmLatent;	//output interval for latent heat flux
    int				iIntClmSensible;//output interval for sensible heat flux

    int             iIntGPP;        //output interval for GPP
    int				iIntNPP;		//output interval for npp
    int             iIntNEP;        //output interval for NEP
    int             iIntRa;         //output interbal for Autotrophic respiration
    int             iIntRh;         //output interbal for heterotrophic respiration

    int				iIntRunTflow;	// output interval for runoff total flow
    int				iIntRunBflow;	// output interval for runoff baseflow
    int				iIntRunIflow;	// output interval for runoff inflow
    int				iIntRunOflow;	// output interval for runoff outflow

    int				iIntSoiCapl;	// output interval for soil capillary rise
    int				iIntSoiPerc;	// output interval for soil percolation
    int				iIntSoiSatd;	// output interval for soil saturated deficit
    int				iIntSoiUnsat;	// output interval for soil unsaturated storage
    int				iIntSoiWatr;	// output interval for soil water table
    int             iIntSWE;        // Output interval for Snow equivelent water
    int             iIntSnowDEP;     //Output interval for Snow depth
    int             iIntSnowDEN;     //Output interval for Snow density




} BH_SubParams1a_t;

typedef struct
{
    int				iMinConifer;
    int				iMaxConifer;

    int				iMinDecidious;
    int				iMaxDecidious;

    int				iMinMixed;
    int				iMaxMixed;

    int				iMinAgricultural;
    int				iMaxAgricultural;

    int				iMinPasture;
    int				iMaxPasture;

    int				iMinOpen;
    int				iMaxOpen;

    int				iMinUrban;
    int				iMaxUrban;

    int				iMinWater;
    int				iMaxWater;
    Bio_params_t	BioParamsBasedOnLC[BIO_PARAMS_NUMBER];

} BH_SubParams2_t;


void insert_day_number(char * szFileName,const char* szInFileName, int iDayNumber);
void remove_day_number(char* szFileName,const char* szInFileName, int iDayNumber);

void AssembleSoilArray(int iLength,float* K0_decay_m,float* soil_b,float* saturation_suction,
                       float* saturated_Kv,float* saturated_Ks,float* saturation_deficit,float* unsaturated_storage,
                       float* water_table,float* soil_temp, float* pondwater,float* Max_depth_Z,
                       float*pool1,float*pool2,float*pool3,float*pool4,float*pool5,float*pool6,float*pool7,float*pool8,float*pool9,
                       float*poolb1,float*poolb2,float*poolb3,float*poolb4,float* nitrogen,
                       float* CNcd_m,float* CNssd_m,float* CNsmd_m,float* CNfsd_m,float* CNfmd_m,
                       float* CNsm_m,float* CNm_m,float* CNs_m,float* CNp_m,float* CNw_m,float* CNfr_m,
                       float* CNl_m,
                       float*ST_Layer_1,float*ST_Layer_2,float*ST_Layer_3,float*ST_Layer_4,float*ST_Layer_5,float*ST_Layer_6,
                       Soil_t* soil);
void DisassembleSoilArray(int iLength,float* K0_decay_m,float* soil_b,float* saturation_suction,
                          float* saturated_Kv,		float* saturated_Ks,float* saturation_deficit,float* unsaturated_storage,
                          float* water_table,float* soil_temp,float* pondwater,float* Max_depth_Z,
                          float*pool1,float*pool2,float*pool3,float*pool4,float*pool5,float*pool6,float*pool7,float*pool8,float*pool9,
                          float*poolb1,float*poolb2,float*poolb3,float*poolb4,float* nitrogen,
                          float* CNcd_m,float* CNssd_m,float* CNsmd_m,float* CNfsd_m,float* CNfmd_m,
                          float* CNsm_m,float* CNm_m,float* CNs_m,float* CNp_m,float* CNw_m,float* CNfr_m,
                          float* CNl_m,
                          float*ST_Layer_1,float*ST_Layer_2,float*ST_Layer_3,float*ST_Layer_4,float*ST_Layer_5,float*ST_Layer_6,
                          Soil_t* soil);

void    AssembleCanopyArray(int iLength,float* canopy_evaporation,
                            float* canopy_transpiration_unsat,float* canopy_transpiration_sat,
                            float* canopy_intercepted,float* litter_evaporation,
                            float* moss_transpiration,float* soil_evaporation,float* canopy_stomata,Canopy_t* canopy);

void	DisassembleCanopyArray(int iLength,float* canopy_evaporation,
                               float* canopy_transpiration_unsat,float* canopy_transpiration_sat,
                               float* canopy_intercepted,float* litter_evaporation,
                               float* moss_transpiration,float* soil_evaporation,float* canopy_stomata,Canopy_t* canopy);

void	DisassembleSnowArray(int iLength,
                             float* swe,
                             float* depth,
                             float* density,
                             Snow_t * snow );
void	AssembleSnowArray(int iLength,
                          float*   swe,
                          float*   depth,
                          float*   desnity,
                          Snow_t * snow);

void	DisassembleEnergyArray(int iLength,
                               float* NRFlux,
                               float* sensibleHeatFlux,
                               float* latentHeatFlux,
                               Energy * energy );
void	AssembleEnergyArray(int iLength,
                            float *NRFlux,
                            float* sensibleHeatFlux,
                            float* latentHeatFlux,
                            Energy * energy);

void readconf(char *conf,BH_SubParams1_t*,BH_SubParams1a_t*,BH_SubParams2_t* BH_SubParams2,int *rcode);

void ClimateCalculate(BH_SubParams1_t* BH_SubParams1,BH_SubParams1a_t* BH_SubParams1a);

double  radiation_ratio(baseline_t *, unsigned int, double, double,double,double*, double* );
double	compute_daylength(baseline_t*,unsigned int);
double	compute_solar_zenith(baseline_t*,unsigned int);


void BepsHydrCalculate(BH_SubParams1_t* BH_SubParams1,BH_SubParams1a_t* BH_SubParams1a,BH_SubParams2_t* BH_SubParams2);

void Soil_constructor(pubv* pv, unsigned char* soil_texture,
                      float* soil_surf_kv,float* soil_surf_ks, float* soil_init_z, float* soil_init_temp,
                      float* carbon_pool1,float* carbon_pool2,float* carbon_pool3,float* carbon_pool4,float* carbon_pool5,float* carbon_pool6,float* carbon_pool7,float* carbon_pool8,float* carbon_pool9,
                      float* biomass_pool1,float* biomass_pool2,float* biomass_pool3,float* biomass_pool4,float* soil_depth,
                      Soil_index_t* soilindex, int iLine, Soil_t* soil, unsigned char* watershed,int line,float*buffer_nitrogen);

void zeroxx(int,double *,xvalue *);
void writexx(int pix,double *x,xvalue *xx);
void readxx(int pix,double *x,xvalue *xx);

void readclim(int,float,short int*,short int*,short int*,short int*,short int*,
              short int*,short int*,climatedata*);
void readlc(int,unsigned char*);
void readawc(bool,int,unsigned char*,float*,float*,float*,float*,double*);
void readlai(int,unsigned char*,double*);


void readb(double *b,unsigned char lc_p,BH_SubParams2_t* pBH_SubParams2);
void setx(unsigned char lc_p,double *x,double *b,BH_SubParams2_t* pBH_SubParams2);


void model(double soilt,double snow_acc,double snow_today,float T_m,int jday,double sad,int pix,int day_start,double lat_p,double lai_p,
           double soil_depth,unsigned char lc_p,double *x,double *b,climatedata *sdat,
           xvalue *xx,Canopy_t *canopy,double* g, double* z,BH_SubParams2_t* pBH_SubParams2);
void zcomp(int jday,int pix,double lat_p,unsigned char lc_p,double soil_depth,
           double lai_p,double *b,double *x,double *z,climatedata *sdat,
           BH_SubParams2_t* pBH_SubParams2);
int net_longwave(double lai_o,double lai_u,double omega,double es,double ta,
                 double *m_lnet_o,double *m_lnet_u,double *lnet_g);
int net_shortwave(double sg_r,double sg_f,double cos_theta,double lai_p,double omega,
                  double *ssun,double *sshade,double lai_u,double *n_ssun,double *n_sshade,
                  double *n_sunder,double *n_sground);
int rad_ssl(double sg_r,double sg_f,double cos_theta,double lai_p,double omega,double *ssun,double *sshade);
void doflux(int jday,float T_m,double sad, double soilt,double snow_acc,double snow_today,
            double *b,double *g,double *x,double *z,unsigned char lc_p,
            BH_SubParams2_t* pBH_SubParams2);

void melt(int jday,double sad,double snow_acc, double *b,double *g,double *x,double *z);

void inter(double *b,double *g,double *x,double *z);

void ra(double *b,double *g,double *x,double *z);

void rs(int jday,double *b,double *g,double *x,double *z, BH_SubParams2_t* pBH_SubParams2);

void rsoil(double *b,double *g,double *x,double *z);

int farq_psn_under(double *b,double *z,double *x,double *g,BH_SubParams2_t* pBH_SubParams2);

int farq_psn(double *b,double *z,double *x,double *g,BH_SubParams2_t* pBH_SubParams2);

void carbon(int jday,float T_m,double *b,double *g,double *x,double *z,BH_SubParams2_t* pBH_SubParams2);


double penmon(double tair,double vpd,double wrad, double acond, double scond);
int farq_psn_moss(double *b,double *z,double *x,double *g,BH_SubParams2_t* pBH_SubParams2);


void SolveTriDiagM(int Topa,int Bota,double * super,double *main,double *sub, double * right,double * TempNext );

void FormTriDiagM(int Top, int Bot, double DampDepth, double TempAnnAver, double TempSurf, double *AppVolHeatCap,
                  double *ThermCon, double *Thick, double *TempCurrent, double *TempNext);
void soil_temp(pubv* start, Soil_t* soil, unsigned char* soil_texture,float*prev_snowdepth, int jday,
               unsigned char* lc, unsigned char* watershed_ptr, short int* climate_tm );
void base_flow(pubv* myseed,int iDay,int iLine,Soil_t* soil,unsigned char* watershed,float* baseflow,float* total_inflow,
               float* total_outflow,float* Array_Ele,int* Array_Label,unsigned char* soil_texture,
               Soil_index_t* soilindex,Soil_t* Soil_Array_3r);	//***added by Andriy***

void	ReadInSoil(Soil_t*,Soil_t*,unsigned int,unsigned int,pubv*);

void soil_water_balance2(pubv* start,float* runoff_baseflow,float * waterin,float* runoff_total,unsigned char* soil_texture,
                         Soil_index_t* soilindex,Soil_t* soil,float* soil_capillary_rise,float* soil_percolation,
                         Canopy_t* canopy_ptr,unsigned char* lc, unsigned char* watershed_ptr,
                         int iDay,double dDaylength,int iTestCurrentLine);
void soil_water_balance1(pubv* start,float* runoff_baseflow,float * waterin,float* runoff_total,unsigned char* soil_texture,
                         Soil_index_t* soilindex,Soil_t* soil,float* soil_capillary_rise,float* soil_percolation,
                         Canopy_t* canopy_ptr,unsigned char* lc, unsigned char* watershed_ptr,
                         int iDay,double dDaylength,int iTestCurrentLine);

void soil_resp(int jday,int iLine, pubv* start, Soil_t* soil,Canopy_t* canopy_ptr, unsigned char* soil_texture,
               float * waterin,float* Daily_NPP,
               unsigned char* lc,short int* climate_tm, unsigned char* watershed_ptr,float*daily_nep);

void	Current_Tz(unsigned int,unsigned int,Soil_t[],Soil_t*,double[],pubv*);

double	compute_unsat_zone_drainage(unsigned char textureindext, Soil_t soils2,
                                    double threthod,double fieldcapacity,double por );
double	compute_cap_rise(Soil_t soils2, double por);

