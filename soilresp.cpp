/*************************************************************************
  Program:     soilresp.c

	Output soil respiration.
***************************************************************************

							--->Ajit Govind
*****************************************************************************/
#include "stdafx.h"
#include "BepsHydrScience.h"

#include <math.h>
void soil_resp(int jday,int iLine, pubv* start, Soil_t* soil,Canopy_t* canopy_ptr, unsigned char* soil_texture,float * waterin,float* Daily_NPP,
			   unsigned char* lc,short int* climate_tm , unsigned char* watershed_ptr ,float*daily_nep)
{
int j;
float tm;
for (j = 0; j < start->npixels; j++)
{
if ((watershed_ptr[j] == 0) || (lc[j] == 0))
{
soil[j].pool1 = -999;
soil[j].pool2 = -999;
soil[j].pool3 = -999;
soil[j].pool4 = -999;
soil[j].pool5 = -999;
soil[j].pool6 = -999;
soil[j].pool7 = -999;
soil[j].pool8 = -999;
soil[j].pool9 = -999;
soil[j].poolb1 = -999;
soil[j].poolb2 = -999;
soil[j].poolb3 = -999;
soil[j].poolb4 = -999;
soil[j].nitrogen= -999;
daily_nep[j]=-999;
soil[j].CNcd_m=-999;
soil[j].CNssd_m=-999;
soil[j].CNsmd_m=-999;
soil[j].CNfsd_m=-999;
soil[j].CNfmd_m=-999;
soil[j].CNsm_m=-999;
soil[j].CNm_m=-999;
soil[j].CNs_m=-999;
soil[j].CNp_m=-999;
soil[j].CNw_m=-999;
soil[j].CNfr_m=-999;
soil[j].CNl_m=-999;

}
else
{
double coef0,coef1,coef2,coef3,coef4,coef5,coef6,coef7,coef8,coef9,coef10,coef11,coef12,coef13,coef14,coef15,coef16,coef17;
double coef18,coef19,coef20,coef21,coef22,coef23,coef24,coef25,coef26,coef27,coef28,coef29,coef30;
double coef36=56.32; double coef37=56.32;
double lignion_leaf;
double lignion_fr;
double lignion_wd;
double lam_u,lam_d;
short num=0;
double theta;		/* average water content for root zone */
double por;
double tex;
double termA;
double f_Temp;
double wfps;
double f_Water;
double f_Tex;
float r;
double silt;
double clay1;
double clay_silt1;
double Respire;
double fw, fcr, fl, ffr;
int fy=10;
double kw_cd, kcr_cd;
double kl_sl, kfr_fl; //coeficients
double km_p, ks_p;
double kssd_a, kssd_sm, kssd_s, ksmd_a, ksmd_sm,kfsd_a, kfsd_m, kfsd_s, kfmd_a, kfmd_m;
double kcd_a, kcd_m;
double kcd_s,ksm_a,ksm_s, km_a, km_s, ks_a, ks_m,kp_a, kp_m;

double Cw1, Ccr1, Cl1, Cfr1,Ccd1,Cssd1,Csmd1,Cfsd1,Cfmd1;
double Cw2, Ccr2, Cl2, Cfr2,Ccd2,Cssd2,Csmd2,Cfsd2,Cfmd2;
double Cm1,Csm1,Cs1, Cp1; // carbon pools
double Cm2,Csm2,Cs2, Cp2; // carbon pools

double dCw1, dCcr1, dCl1, dCfr1,dCcd1,dCssd1,dCsmd1,dCfsd1,dCfmd1;
double dCw2, dCcr2, dCl2, dCfr2,dCcd2,dCssd2,dCsmd2,dCfsd2,dCfmd2;
double dCsm1, dCm1,dCs1, dCp1;
double dCsm2, dCm2,dCs2, dCp2;




float CNcd1,CNssd1,CNsmd1,CNfsd1,CNfmd1,CNsm1,CNm1,CNs1;
float CNp1,CNl1,CNfr1,CNw1,CNcr1;
float CNcd2,CNssd2,CNsmd2,CNfsd2,CNfmd2,CNsm2,CNm2,CNs2;
float CNp2,CNl2,CNfr2,CNw2,CNcr2;
float air_temp=climate_tm[j]/10;
double alpha1=pow(2.5,(air_temp/10));
double alpha2=pow(2,(soil[j].soil_temp/10));
r=alpha1*2.5;
double part1,part2;
double Fm;

	lignion_leaf=0.242/(0.15+0.018*0.6*coef36);
	lignion_fr=0.24/(0.15+0.018*0.6*coef37);
	lignion_wd=0.35;


//....................................Soil mositure status......................................

		if ( soil_texture[j]==120)
		{
		por=0.8;//soilindex[j].porosity;
		}
		if ( soil_texture[j]==40)
		{
		por=0.50;//soilindex[j].porosity;
		}
		if ( soil_texture[j]==30)
		{
		por=0.42;//soilindex[j].porosity;
		}
		else if ( soil_texture[j]==20)
		{
		por=0.35;//soilindex[j].porosity;
		}

		if(soil[j].water_table<=0)
		{
		theta=por;
		}
		else

		{
		theta=soil[j].unsaturated_storage/soil[j].water_table; // vol water content in unsat zone
		}



//******************************Calculation of Scalars*****************************


							// 1. Temperature Scalar
f_Temp=	exp(308.56*(1/(27.0+46.032)-1/(46.032+ soil[j].soil_temp)));
//...................................................................................
wfps=theta/por	;						//2. Soil water Scalar

double f_Water1=(5.44*wfps)-(5.03*(pow(wfps,2)))-0.472;
f_Water=MAX(0.4,f_Water1);
//

//...................................................................................
							//3. Soil Texture Scalar

if ( soil_texture[j]==120)
{
	silt = 0.3;
	clay1=0.05;
	clay_silt1=silt+clay1;
f_Tex=(1-0.75*tex);
	}

else if (soil_texture[j]==30) // Based on USDA soil textural classification
{
	silt = 0.2;
	clay1=0.1;
	clay_silt1=silt+clay1;
f_Tex=(1-0.75*tex);
}


else if (soil_texture[j]==40)
{
	silt = 0.90;
	clay1=0.05;
	clay_silt1=silt+clay1;
}

else tex=-999;

f_Tex=(1-0.75*tex);

clay_silt1=silt+clay1;
//.............................................................................................................

//.................................Pool turnover coeficients ................................


	if(lc[j]==1)
	{coef0=0.3010; coef1=0.1483; coef2=0.2128;coef3=0.3479;}
	else if (lc[j]==2)
	{coef0=0.4624; coef1=0.1190; coef2=0.2226;coef3=0.1960;}
	else if (lc[j]==3)
	{coef0=0.3817; coef1=0.1536; coef2=0.2077;coef3=0.2570;}
	else if (lc[j]==4)
	{coef0=0.3010; coef1=0.1483; coef2=0.2128;coef3=0.2570;}
	else if (lc[j]==5)
	{coef0=0.3010; coef1=0.1483; coef2=0.2128;coef3=0.3479;}

	if(lc[j]==1 )
	{coef4=0.0279;  coef5=0.0269;  coef6=0.1925;  coef7=0.548;}
	if(lc[j]==2 )
	{coef4=0.02888;  coef5=0.04488;  coef6=0.3552325;  coef7=0.5948;}
	if(lc[j]==3 )
	{coef4=0.0279;  coef5=0.02688;  coef6=0.3945;  coef7=0.5948;}
	if(lc[j]==4 )
	{coef4=0.0139;  coef5=0.04488;  coef6=0.3552325;  coef7=0.5948;} //5948



if(lc[j]==5) //to simulate wetland soil C
	{
			coef4=0.02888*0.01;  coef5=0.04488*0.01;  coef6=0.3552325*0.01;  coef7=0.5948*0.01;
	}

else if (lc[j]==7 || lc[j]==9)
{	coef4=0;  coef5=0;  coef6=0;  coef7=0; }

//................................................................................................................
		coef8=3.9*(exp(-3*lignion_leaf))*((1-lignion_leaf)*0.6+lignion_leaf*0.3);
        coef9=3.9*(exp(-3*lignion_leaf))*(1-lignion_leaf)*0.4;
         coef10=3.9*(exp(-3*lignion_leaf))*lignion_leaf*0.7;

		 coef11=14.8*0.6;
         coef12=14.8*0.4;



         coef13= 4.8*(exp(-3*lignion_fr))*((1-lignion_fr)*0.55+lignion_fr*0.3);
         coef14= 4.8*(exp(-3*lignion_fr))*(1-lignion_fr)*0.45;
         coef15= 4.8*(exp(-3*lignion_fr))*lignion_fr*0.7;




         coef16=18.5*0.5;  //18.5*0.5;
         coef17=18.5*0.5;  //18.5*0.5;


         coef18= 2.4*(exp(-3*lignion_wd))*((1-lignion_wd)*0.55+lignion_wd*0.45);
         coef19= 2.4*(exp(-3*lignion_wd))*(1-lignion_wd)*0.45;
         coef20= 2.4*(exp(-3*lignion_wd))*lignion_wd*0.55;



		coef21= 7.3*(1-0.75*clay_silt1)*(0.85-0.68*clay_silt1);
		coef22= 7.3*(1-0.75*clay_silt1)*(0.003+0.032*clay1);
		coef23= 7.3*(1-0.75*clay_silt1)
			     *(1-(0.003+0.032*clay1)-(0.85-0.68*clay_silt1)-5.0/18.0*(0.01+0.04*(1-clay_silt1)));



		coef24=6.0*0.6;
		coef25=6.0*0.4;



		coef29=0.0045*0.5*1.25;
		coef30=0.0045*0.5*1.25;


	    coef26=0.25*0.55;
		coef27=0.25*(0.003-0.009*clay1);
	if(coef27<0.00001)coef27=0.00001;
	if((0.003-0.009*clay1)>0.00001) coef28=0.25*(1-0.55-(0.003-0.009*clay1));
    else coef28=0.25*(1-0.55-0.00001);


//__________________________________________________________________________________________________



	lam_u= f_Temp*f_Water;
    lam_d= f_Temp*f_Water;



    fw = coef0;
	fcr = coef1;
	fl = coef2;
	ffr = coef3;

//Turn over coefficients


	if(lc[j]==5)  //wetland 5 has lower than forest rate
	{
	kw_cd =coef4*lam_u*0.75*0.25*1.0/365.0;
	kcr_cd =coef5*lam_u*0.25*1.0/365.0;
	kl_sl =coef6*lam_u*0.25*1.0/365.0;
	kfr_fl =coef7*lam_u*0.25*1.0/365.0;
	kssd_a = coef8*0.025*lam_u*1.0/365.0;
    kssd_sm = coef9*0.25*lam_u*1.0/365.0;
    kssd_s = coef10*0.25*lam_u*1.0/365.0;
	ksmd_a = coef11*0.25*lam_u*1.0/365.0;
	ksmd_sm = coef12*0.25*lam_u*1.0/365.0;
    kfsd_a = coef13*0.25*lam_u*1.0/365.0;
    kfsd_m = coef14*0.25*lam_u*1.0/365.0;
    kfsd_s = coef15*0.25*lam_u*1.0/365.0;
	kfmd_a = coef16*0.25*lam_u*1.0/365.0;
	kfmd_m = coef17*0.25*lam_u*1.0/365.0;
	kcd_a = coef18*0.25*lam_u*1.0/365.0;
    kcd_m = coef19*0.25*lam_u*1.0/365.0;
    kcd_s = coef20*0.25*lam_u*1.0/365.0;
    km_a = coef21*0.25*lam_u*1.0/365.0;
    km_p = coef22*0.25*lam_u*1.0/365.0;
	km_s = coef23*0.25*lam_u*1.0/365.0;
    ksm_a= coef24*0.25*lam_u*1.0/365.0;
	ksm_s= coef25*0.25*lam_u*1.0/365.0;
	ks_a = coef26*0.25*lam_u*1.0/365.0;
	ks_p = coef27*0.25*lam_u*1.0/365.0;
    ks_m = coef28*0.25*lam_u*1.0/365.0;
	kp_a = coef29*0.25*lam_u*1.0/365.0;
    kp_m = coef30*0.25*lam_u*1.0/365.0;
	}
	else
	{
	kw_cd =coef4*/*alpha1**/1.0/365.0; //saesonality added
	kcr_cd =coef5*/*(alpha1)**/1.0/365.0;//saesonality added alpha2
	kl_sl =coef6*1.0/365.0;//saesonality added
	kfr_fl =coef7*1.0/365.0;//saesonality added  alpha2
	kssd_a = coef8*lam_u*1.0/365.0;
    kssd_sm = coef9*lam_u*1.0/365.0;
    kssd_s = coef10*lam_u*1.0/365.0;
	ksmd_a = coef11*lam_u*1.0/365.0;
	ksmd_sm = coef12*lam_u*1.0/365.0;
    kfsd_a = coef13*lam_u*1.0/365.0;
    kfsd_m = coef14*lam_u*1.0/365.0;
    kfsd_s = coef15*lam_u*1.0/365.0;
	kfmd_a = coef16*lam_u*1.0/365.0;
	kfmd_m = coef17*lam_u*1.0/365.0;
	kcd_a = coef18*lam_u*1.0/365.0;
    kcd_m = coef19*lam_u*1.0/365.0;
    kcd_s = coef20*lam_u*1.0/365.0;
    km_a = coef21*lam_u*1.0/365.0;
    km_p = coef22*lam_u*1.0/365.0;
	km_s = coef23*lam_u*1.0/365.0;
    ksm_a= coef24*lam_u*1.0/365.0;
	ksm_s= coef25*lam_u*1.0/365.0;
	ks_a = coef26*lam_u*1.0/365.0;
	ks_p = coef27*lam_u*1.0/365.0;
    ks_m = coef28*lam_u*1.0/365.0;
	kp_a = coef29*lam_u*1.0/365.0;
    kp_m = coef30*lam_u*1.0/365.0;
	}

 //Previous day pool size
	Cw1   = soil[j].poolb1;
	Ccr1  = soil[j].poolb2;
	Cl1   = soil[j].poolb3;
	Cfr1  = soil[j].poolb4;//initialValues[4];
	Ccd1  = soil[j].pool1;
	Cssd1 = soil[j].pool2;
	Csmd1 = soil[j].pool3;
	Cfmd1 = soil[j].pool4;
	Cfsd1 = soil[j].pool5;
	Csm1  = soil[j].pool9;
    Cm1   = soil[j].pool6;
	Cs1   = soil[j].pool7;
	Cp1   = soil[j].pool8;



CNcd1=soil[j].CNcd_m;
CNssd1=soil[j].CNssd_m;
CNsmd1=soil[j].CNsmd_m;
CNfsd1=soil[j].CNfsd_m;
CNfmd1=soil[j].CNfmd_m;
CNsm1=soil[j].CNsm_m;
CNm1=soil[j].CNm_m;
CNs1=soil[j].CNs_m;
CNp1=soil[j].CNp_m;
CNl1=soil[j].CNl_m;
CNfr1=soil[j].CNfr_m;
CNw1=soil[j].CNw_m;









	Fm   = 0.85-0.018*40.5;//(soil[j].CNl_m+soil[j].CNfr_m); //

	dCw2  = ((fw * Daily_NPP[j]) - kw_cd  * Cw1);///(1+kw_cd) ;
	dCcr2 = ((fcr* Daily_NPP[j]) - kcr_cd * Ccr1);///(1+kcr_cd);
	dCl2  = ((fl * Daily_NPP[j]) - kl_sl  * Cl1);///(1+kl_sl) ;
    dCfr2 = ((ffr* Daily_NPP[j])- kfr_fl * Cfr1);///(1+kfr_fl);

	Cw2  =Cw1 + dCw2;


	Ccr2 =Ccr1 + dCcr2;
	Cl2  =Cl1 + dCl2;
	Cfr2 =Cfr1 + dCfr2;



  part1=(kw_cd * Cw1+kcr_cd * Ccr1)-(Ccd1 * (kcd_a + kcd_m + kcd_s));
  part2=(1+(kcd_a + kcd_m + kcd_s));
  dCcd2=part1/part2;
  Ccd2 = Ccd1 + dCcd2;


  part1=((1 - Fm)* kl_sl*Cl1) - (Cssd1* (kssd_a + kssd_sm + kssd_s));
//part1=(Fm)* kl_sl*Cl1/(1+(kssd_a + kssd_sm + kssd_s));
  part2=(1+(kssd_a + kssd_sm + kssd_s));
  ///(1+lam_u*(kssd_a + kssd_sm + kssd_s));
  dCssd2=part1/part2;
  Cssd2= Cssd1+dCssd2;      // for surface structural litter



  part1=(Fm* kl_sl * Cl1)- (Csmd1* (ksmd_a + ksmd_sm));
  part2= (1+(ksmd_a + ksmd_sm));
	//(1+lam_u*(ksmd_a + ksmd_sm));
  dCsmd2=part1/ part2;
  Csmd2= Csmd1+dCsmd2;         // for surface metabolic litter




	  part1=((1-Fm)* kfr_fl* Cfr1)- (Cfsd1* (kfsd_a + kfsd_m + kfsd_s));
	  part2=(1+(kfsd_a + kfsd_m + kfsd_s));
	  dCfsd2=part1/part2;
	  Cfsd2= Cfsd1+dCfsd2;          //for soil strutural litter pool



	part1=(Fm * kfr_fl * Cfr1)-((kfmd_a + kfmd_m)* Cfmd1);
	part2=(1+(kfmd_a + kfmd_m));
	dCfmd2=part1/part2;
	Cfmd2= Cfmd1+dCfmd2;       // for soil metabolic pool



	part1=(Cssd2*kssd_sm+Csmd2*ksmd_sm);
	part2=Csm1*(ksm_a+ksm_s);
	dCsm2=part1-part2;
	Csm2=Csm1+dCsm2;                     // for surface microbe pool


	part1=((kfsd_m * Cfsd2+kfmd_m*Cfmd2 + Ccd2 * kcd_m) +(Cs1*ks_m+Cp1 * kp_m));
	part2=Cm1 * (km_a +  km_s +km_p);
	dCm2=part1-part2;
	Cm2=Cm1+dCm2;                          // for soil microbe pool


	part1=((Cm2*km_s + Ccd2 * kcd_s +Cfsd2*kfsd_s )+ (Csm2*ksm_s + Cssd2*kssd_s));
	part2=Cs1*( ks_a + ks_p+ks_m);
	dCs2=part1-part2;
	Cs2=Cs1+dCs2;   // for slow carbon pool



	dCp2 =(( km_p * Cm2 + ks_p * Cs2)
		- (kp_m * Cp1	+ kp_a * Cp1));

	Cp2=Cp1+dCp2; 	 // for passive carbon pool.



//Updated pools
soil[j].poolb1=Cw2 ;
soil[j].poolb2=Ccr2 ;
soil[j].poolb3=Cl2  ;
soil[j].poolb4=Cfr2 ;
soil[j].pool1 =Ccd2 ;
soil[j].pool2 =Cssd2;
soil[j].pool3 =Csmd2;
soil[j].pool4 =Cfmd2;
soil[j].pool5 =Cfsd2;
soil[j].pool9 =Csm2;
soil[j].pool6 =Cm2 ;
soil[j].pool7 =Cs2 ;
soil[j].pool8 =Cp2 ;



// Respiration is sum of all pool's release to atmosphere

Respire=(Cssd1* kssd_a+Csmd1* ksmd_a+Csm1*ksm_a)
         +(Ccd1   *kcd_a+Cfsd1* kfsd_a+Cfmd1 * kfmd_a
         +Cm1*km_a+Cs1*ks_a+Cp1*kp_a);

//Calculate NEP right here itself
daily_nep[j]=(Daily_NPP[j])-Respire;	//Ajit
daily_nep[j]=MAX(-999,daily_nep[j]); //EPHYSE


               //<<<<<<<<<<<<Nitrogen Dynamics>>>>>>>>>>>>>>>>>>>>>>>>>


			double N_avble, N_min, N_fix,N_up,Ndepo;
			double Term1, Term2,Term3,Term4, Term5,Term6,Term7,Term8,Term9,Term10,Term11, Term12,Term13;


			//Nitrogen fixation based on Ju et al.,2007 (JEM)
			float c1=0.15/365;  // a coeffi determining fixation rate
			//double alpha=pow(2,(soil[j].soil_temp/10));
			float beta=(Csm1+Cm1)/200;
			N_fix=(alpha2*c1*(waterin[j]/0.45))*beta;
			Ndepo=0.3/365;
			//................................

			Term1=((kssd_sm+kssd_s+kssd_a )*Cssd1)/CNssd1;//ckd
			Term2=((ksmd_sm+ksmd_a )*Csmd1)/CNsmd1;//ckd
			Term3=((kfsd_m+kfsd_s + kfsd_a )*Cfsd1)/CNfsd1;//ckd
			Term4=((kfmd_m+kfmd_a )*Cfmd1)/CNfmd1; //ckd
		    Term5=((kcd_m+kcd_s+kcd_a )*Ccd1)/CNcd1;//ckd
			Term6=((ksm_s+ksm_a )*Csm1)/CNsm1;//ckd
			Term7=((km_s+km_p+km_a)*Cm1)/CNm1;//ckd
			Term8=((ks_m+ks_p+ks_a)*Cs1)/CNs1;//ckd
			Term9=((kp_m+/*kp_s*/+kp_a)*Cp1)/CNp1;//ckd
			Term10=((kssd_sm*Cssd1)+(ksmd_sm*Csmd1))/CNsm1;
			Term11=((ks_p*Cs1)+(km_p*Cm1))/CNp1;
			Term12=((kfsd_m*Cfsd1)+(kfmd_m*Cfmd1)+(kcd_m*Ccd1)+(ks_m*Cs1)+(kp_m*Cp1))/CNm1;
			Term13=((kfsd_s*Cfsd1)/*+(kfmd_s*Cfmd1)*/+(kcd_s*Ccd1)+(km_s*Cm1)/*+(kp_s*Cp1)*/)/CNs1;

			N_min=(Term1+Term2+Term3+Term4+Term5+Term6+Term7+Term8+Term9-Term10-Term11-Term12-Term13);
			N_avble=N_fix+N_min+Ndepo;


			N_up=MAX(0,((N_avble/(1+(0.35*N_avble/Cfr1)))*r));
			soil[j].nitrogen=N_up;


// Updating each C-pool's CN ratios
//1=========================================================================================
										//CNl  //changed
double term1,term2,term3;

term1= (((1-kl_sl)*Cl1)+ (fl*Daily_NPP[j]));
//term2=(((1-kl_sl)*Cl1)/CNl1)+(fl/CNl1);
term2=(((1-kl_sl)*Cl1)/CNl1);
term3=((fl/CNl1))*(N_up/((fl/CNl1)+(ffr/CNfr1)+((fw+fcr)/CNw1)));
CNl2=term1/(term2+term3);


//=========================================================================================
double term4,term5,term6;										//CNfr//changed
term4= (((1-kfr_fl)*Cfr1)+ (ffr*Daily_NPP[j]));
term5=(((1-kfr_fl)*Cfr1)/CNfr1);
term6=((ffr/CNfr1))*(N_up/((fl/CNl1)+(ffr/CNfr1)+((fw+fcr)/CNw1)));
CNfr2=term4/(term5+term6);

//=========================================================================================
double term7,term8,term9;										//CN`w//changed
term7= (Cw1+Ccr1+((fw+fcr)*Daily_NPP[j]));
term8=((Cw1+Ccr1)/CNw1);
term9=(((fw+fcr)/CNw1))*(N_up/((fl/CNl1)+(ffr/CNfr1)+((fw+fcr)/CNw1)));
CNw2=term7/(term8+term9);

//=========================================================================================
										//CNcd

double term10,term11,term12;
term10= Ccd2;
term11=((Ccd1/CNcd1)+(((kw_cd*Cw2)+(kcr_cd*Ccr2))/CNw2));
term12=((Ccd1*(kcd_m+kcd_s+kcd_a))/(CNcd1));
CNcd2=term10/(term11-term12);


//=========================================================================================
Fm=0;										//CNssd
double term13,term14,term15;
term13= (Cssd1/CNssd1);
term14=((kl_sl*Cl2)*(1-Fm))/CNl2;
term15=((Cssd1*(kssd_sm+kssd_s+kssd_a))/(CNssd1));
CNssd2=Cssd2/(term13+term14-term15);


//=========================================================================================
										//CNsmd

double term16,term17,term18;
term16= (Csmd1/CNsmd1);
term17=((kl_sl*Cl1)*(Fm))/CNl2;
term18=((Csmd1*(ksmd_sm+ksmd_a))/(CNsmd1));
CNsmd2=Csmd2/(term16+term17-term18);


//=========================================================================================
										//CNfsd
double term19,term20,term21;
term19= (Cfsd1/CNfsd1);
term20=((kfr_fl*Cfr2)*(1-Fm))/CNfr2;
term21=((Cfsd1*(kfsd_m+kfsd_s+kfsd_a))/(CNfsd1));
CNfsd2=Cfsd2/(term19+term20-term21);

//=========================================================================================
										//CNfmd

double term22,term23,term24;
term22= (Cfmd1/CNfmd1);
term23=((kfr_fl*Cfr2)*(Fm))/CNfr2;
term24=((Cfmd1*(kfmd_m+kfmd_a))/(CNfmd1));
CNfmd2=Cfmd2/(term22+term23-term24);


//=========================================================================================
										//CNs
double term25,term26,term27,term28,term29,term30,term31;
term25= (Cs1/CNs1);
term26= ((kssd_s*Cssd1)/CNssd2);
term27= ((kfsd_s*Cfsd1)/CNfsd2);
term28= ((kcd_s*Ccd1)/CNcd2);
term29= ((km_s*Cm1)/CNm2);
term30= ((ksm_s*Csm1)/CNsm2);
term31= (((km_s+ks_p+ks_a)*Cs1)/CNs1);
CNs2= Cs2/(term25+term26+term27+term28+term29+term30-term31);
//=========================================================================================
										//CNp
double term32,term33,term34,term35;
term32= (Cp1/CNp1);
term33= ((ks_p*Cs1)/CNs1);
term34= ((kcd_s*Cm1)/12);
term35= (((kp_m+kp_a)*Cp1)/CNp1);
CNp2= Cp2/(term32+term33+term34-term35);

//=========================================================================================

soil[j].CNcd_m=CNcd2;
soil[j].CNssd_m=CNssd2;
soil[j].CNsmd_m=CNsmd2;
soil[j].CNfsd_m=CNfsd2;
soil[j].CNfmd_m=CNfmd2;
soil[j].CNsm_m=12;//CNsm2;//living thing
soil[j].CNm_m=12;//CNm2;//living thing constant cn ratio
soil[j].CNs_m=CNs2;
soil[j].CNp_m=CNp2;
soil[j].CNl_m=CNl2;
soil[j].CNfr_m=CNfr2;
soil[j].CNw_m=CNw2;

} //else
}//j loop
}//end of soil_resp

