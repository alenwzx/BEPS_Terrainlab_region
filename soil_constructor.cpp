/**************************************************************************************************************
    1. soilindex[k] (k ∈ 0 ~ 11) ,该结构体数组规定了12种土壤的基本属性. 声明：BepsHydrScience.h line258; 赋值：readconf.cpp line127
    2. soil[j] (j ∈ 0 ~ pv->npixels) ，该结构体数组描述了一行像元的土壤属性. 声明：BepsHydrScience.h line207 赋值：soil_constructor.cpp
**************************************************************************************************************/
#include <algorithm>
#include <cmath>
#include <cstdio>
#include "stdafx.h"
#include "BepsHydrScience.h"
#include <cstdio>
#include <cmath>
#include <stdio.h>

void Soil_constructor(pubv* pv, unsigned char* soil_texture,
                      float* soil_surf_kv,float* soil_surf_ks, float* soil_init_z, float* soil_init_temp,
                      float* carbon_pool1,float* carbon_pool2,float* carbon_pool3,float* carbon_pool4,float* carbon_pool5,float* carbon_pool6,float* carbon_pool7,float* carbon_pool8,float* carbon_pool9,
                      float* biomass_pool1,float* biomass_pool2,float* biomass_pool3,float* biomass_pool4,float* soil_depth,
                      Soil_index_t* soilindex, int iLine, Soil_t* soil, unsigned char* watershed,int line,float*buffer_nitrogen, float** initial_soil_moisture)
{
    short textureindex;
    float w,air_entry,z,depth = 0;

    for(int j=0; j<pv->npixels; j++)
    {
        // 设置 textureindex(∈0-11) 映射 soil_texture[j](∈10-120)
        if(soil_texture[j]>0 && soil_texture[j]<=120)
            textureindex=soil_texture[j]/10-1;
        else
            textureindex=1;
        // 边界赋值
        if (watershed[j] == 0 ||soil_init_z[j]  <-10.0)
        {
            soil[j].K0_decay_m          = soilindex[4].pore_index;      // -99.0f;	//soil parameter for Kz calculation
            soil[j].soil_b              = soilindex[4].soil_b[0];       // -99.0f;
            soil[j].saturation_suction  = soilindex[4].suction_head[0];	// -99.0f;	//suction in meters when soil is saturation
            soil[j].saturated_Kv        = soilindex[4].soil_K0[0];      // -99.0f;	//at surface. m per day
            soil[j].saturated_Ks        = soilindex[4].soil_K0H[0];     // -99.0f;	//at surface. m per day
            soil[j].saturation_deficit  = 0;                          // -99.0f;	//meter. Zero at saturation
            soil[j].water_table         = 2.0;	                        //meter from soil surface
            soil[j].pondwater           = 0.0;	                        //pond 为什么池塘水体设为0呢?这个设置应该针对的是研究区外的边界点
            soil[j].unsaturated_storage = 0.0;// -99.0f;	//meter	....MEM: of water in the unsaturated zone!!!
            soil[j].Max_depth_Z         = 2.0;                          // -99.0f;	//meter	//ori 1.0 on 23jun

            soil[j].thetam[0]                   = 0;
            soil[j].thetam[1]                   = 0;
            soil[j].thetam[2]                   = 0;
            soil[j].thetam[3]                   = 0;
            soil[j].thetam[4]                   = 0;

            soil[j].thetam_prev[0]              = 0;
            soil[j].thetam_prev[1]              = 0;
            soil[j].thetam_prev[2]              = 0;
            soil[j].thetam_prev[3]              = 0;
            soil[j].thetam_prev[4]              = 0;

        }
        //研究区内赋值
        else
        {
            //find a corresponding texture name, then calculate values for other items ,根据 mytexture(∈10-120),soil_texture[j](∈10-120) 的一致性，遍历寻找对应的土壤类型并为赋予土壤属性值
            for(int k=0; k<12; k++)
            {
                if ((int)soil_texture[j] == soilindex[k].mytexture)	//***Added by Andriy
                {
                    soil[j].K0_decay_m			= (float)soilindex[k].pore_index;
                    soil[j].soil_b				= (float)soilindex[k].soil_b[0];
                    soil[j].saturation_suction	= (float)soilindex[k].suction_head[0];
                    soil[j].saturated_Kv		= (float)soilindex[k].soil_K0[0];
                    soil[j].saturated_Ks		= (float)soilindex[k].soil_K0H[0];

                    // Check if the initial soil moisture data was passed in
                    bool has_initial_moisture = initial_soil_moisture != nullptr && initial_soil_moisture[0] != nullptr;
                    has_initial_moisture = false;
                    if (has_initial_moisture)
                    {
                        for (int layer = 0; layer < 5; layer++) {
                            soil[j].thetam[layer] = initial_soil_moisture[layer][j];
                            soil[j].thetam_prev[layer] = initial_soil_moisture[layer][j];
                        }
                    }
                    else
                    {
                        float dx;
                        dx = (15 - soil_init_z[j])/300;
                        // dx =0;
                        soil[j].thetam[0] = MIN((float)soilindex[k].field_cap[0] + dx,soilindex[k].porosity[0]);
                        soil[j].thetam[1] = MIN((float)soilindex[k].field_cap[1] + dx,soilindex[k].porosity[0]);
                        soil[j].thetam[2] = MIN((float)soilindex[k].field_cap[2] + dx,soilindex[k].porosity[0]);
                        soil[j].thetam[3] = MIN((float)soilindex[k].field_cap[3] + dx,soilindex[k].porosity[0]);
                        soil[j].thetam[4] = MIN((float)soilindex[k].field_cap[4] + dx,soilindex[k].porosity[0]);
                        // soil[j].thetam[0] = (float)soilindex[k].porosity[0] + dx;
                        // soil[j].thetam[1] = (float)soilindex[k].porosity[1] + dx;
                        // soil[j].thetam[2] = (float)soilindex[k].porosity[2] + dx;
                        // soil[j].thetam[3] = (float)soilindex[k].porosity[3] + dx;
                        // soil[j].thetam[4] = (float)soilindex[k].porosity[4] + dx;

                        soil[j].thetam_prev[0] = soil[j].thetam[0];
                        soil[j].thetam_prev[1] = soil[j].thetam[1];
                        soil[j].thetam_prev[2] = soil[j].thetam[2];
                        soil[j].thetam_prev[3] = soil[j].thetam[3];
                        soil[j].thetam_prev[4] = soil[j].thetam[4];
                    }

                    depth = 0;
                    soil[j].unsaturated_storage = 0;

                    soil[j].d_soil[0] = 0.10f; // 0-10cm
                    soil[j].d_soil[1] = 0.10f; //11-20cm(center:15cm)
                    soil[j].d_soil[2] = 0.20f; //21-40cm(center:30cm)
                    soil[j].d_soil[3] = 0.20f; //41-60cm(center:50cm)
                    soil[j].d_soil[4] = 4.20f;

                    for(int i=0;i<MAX_LAYERS-1;i++)
                    {
                        soil[j].unsaturated_storage += soil[j].thetam[i] * soil[j].d_soil[i];
                        depth += soil[j].d_soil[i];
                    }
                    soil[j].unsaturated_storage /= depth;


                    /*土壤深度*/
                    if (soil_depth[j]	<= -9999.0f) //soil-depth.bin 设置成-9999.0f即可
                    {
                        soil[j].Max_depth_Z		= (float)soilindex[k].max_z;
                    }
                    else
                        soil[j].Max_depth_Z		= (float)soil_depth[j];

                    /*初始地下水深度*/
                    if(soil_init_z[j] <= -9999.0f)   //if 9999, use the default
                        soil[j].water_table		= -999;//(float) (soil[j].Max_depth_Z/2.0);
                    else
                    {
                        soil[j].water_table		= (float)soil_init_z[j];
                        soil[j].soil_temp		= (float)soil_init_temp[j];
                        soil[j].pool1		= (float)carbon_pool1[j];
                        soil[j].pool2		= (float)carbon_pool2[j];
                        soil[j].pool3		= (float)carbon_pool3[j];
                        soil[j].pool4		= (float)carbon_pool4[j];
                        soil[j].pool5		= (float)carbon_pool5[j];
                        soil[j].pool6		= (float)carbon_pool6[j];
                        soil[j].pool7		= (float)carbon_pool7[j];
                        soil[j].pool8		= (float)carbon_pool8[j];
                        soil[j].pool9		= (float)carbon_pool9[j];
                        soil[j].poolb1	    = (float)biomass_pool1[j];
                        soil[j].poolb2	    = (float)biomass_pool2[j];
                        soil[j].poolb3	    = (float)biomass_pool3[j];
                        soil[j].poolb4	    = (float)biomass_pool4[j];
                        soil[j].nitrogen	= 0.013;//(float)buffer_nitrogen[j];
                        soil[j].CNcd_m=180.26;//these should be initialized using intec values
                        soil[j].CNssd_m=65.32;
                        soil[j].CNsmd_m=15.32;
                        soil[j].CNfsd_m=30.32;
                        soil[j].CNfmd_m=15.32;
                        soil[j].CNsm_m=12.00;
                        soil[j].CNm_m=12.00;
                        soil[j].CNs_m=38.74;
                        soil[j].CNp_m=30.32;
                        soil[j].CNw_m=100.32;
                        soil[j].CNfr_m=56.32;
                        soil[j].CNl_m=56.32;
                        soil[j].ST_Layer_1=5;//these should be using measured values
                        soil[j].ST_Layer_2=5;
                        soil[j].ST_Layer_3=5;
                        soil[j].ST_Layer_4=5;
                        soil[j].ST_Layer_5=5;
                        soil[j].ST_Layer_6=5;
                        soil[j].pondwater=0;
                    }

                }//end of if block
            }//end of k for loop

            // w=0.92f;	//wetnees value between 0.9 and 1.0. See Clapp and Hornberger, 1978
            // air_entry = soil[j].saturation_suction*(float)pow(w,(double)-soil[j].K0_decay_m);
        }//end of if-else block within the for loop

    }//end of j loop 结束行像元的遍历

}

void Init_Soil_Parameters(const pubv* pv, const unsigned  char* landcover, const Soil_index_t* soilindex,Soil_t* soil,const unsigned char* watershed, const unsigned char* soil_texture ,int line, int iDay , const Canopy_t* canopy_ptr, float* waterin, int CFL, Soil_t* Soil_Array_3r, float* Array_Ele)
{
    short textureindex;
    float Trans_o, Trans_u, Evap_soil, depth ;
    for (int j=0; j<pv->npixels; j++)
    {
        if (watershed[j] != 0)
        {
            // 设置 textureindex(∈0-11) 映射 soil_texture[j](∈10-120)
            if(soil_texture[j]>0 && soil_texture[j]<=120)
                textureindex=soil_texture[j]/10-1;
            else
                textureindex=1;

            Trans_o     = (float)canopy_ptr[j].canopy_transpiration_unsat/kstep/1000.0;
            Trans_u     = 0;
            Evap_soil   = (float)canopy_ptr[j].soil_evaporation/kstep/1000.0;
            soil[j].r_rain_g = waterin[j]/float(kstep);  // the rainfall rate, un--on understory g--on ground surface  m/s

            soil_water_factor_v2(&soil[j]);
            Soil_Water_Uptake(&soil[j],Trans_o,Trans_u,Evap_soil);

            for(int i=0;i<kstep/steps/CFL;i++)
            {
                soil[j].dz = soil[j].water_table;
                soil[j].Zp = soil[j].pondwater;
                UpdateSoilMoisture(&soil[j], float(steps));

                soil[j].pondwater = soil[j].Zp;
                soil[j].water_table = (float)soil[j].dz;
            }
            // if(soil[j].Zp > 0)printf("pond: %.8f\n", soil[j].Zp);
            depth = 0;
            soil[j].unsaturated_storage = 0;

            for(int i=0;i<MAX_LAYERS-1;i++)
            {
                soil[j].unsaturated_storage += soil[j].thetam[i] * soil[j].d_soil[i];
                depth += soil[j].d_soil[i];
            }
            soil[j].unsaturated_storage /= depth;

            // soil[j].unsaturated_storage = soil[j].f_soilwater;
        }
    }
}

void SoilRootFraction(Soil_t* soil)
{
    int i;
    float cum_depth[MAX_LAYERS];

    // for the 0 layer
    cum_depth[0] = soil->d_soil[0];
    soil->f_root[0] = 1 - std::pow(soil->r_root_decay, cum_depth[0] * 100);

    // for 1 to n_layer-1
    for (i = 1; i < soil->n_layer - 1; i++)
    {
        cum_depth[i] = cum_depth[i - 1] + soil->d_soil[i];
        soil->f_root[i] = std::pow(soil->r_root_decay, cum_depth[i - 1] * 100) - std::pow(soil->r_root_decay, cum_depth[i] * 100);
    }

    // for the last layer. Put all reminding roots to the last layer.
    // soil->Layer[layer].f_root = 1 - (1-pow(soil->r_root_decay, cum_depth[i-1] *100));
    soil->f_root[soil->n_layer - 1] = std::pow(soil->r_root_decay, cum_depth[soil->n_layer - 2] * 100);
}

void soil_water_factor_v2(Soil_t* soil)
{
    float	ft[MAX_LAYERS], fpsisr[MAX_LAYERS];
    float	dtt[MAX_LAYERS];
    float t1, t2;
//	double fw;
    int i;

    t1 = -0.02;
    t2 = 2.0;

    if (soil->psim[0] <= 0.000001) // just in case that this function is called before "updatesoilmoisture". LHE
        for (i = 0; i < soil->n_layer; i++)
        {
            soil->psim[i] = soil->psi_sat[i] * std::pow(soil->thetam[i] / soil->fei[i], -soil->b[i]);
            soil->psim[i] = MAX(soil->psi_sat[i], soil->psim[i]);  // I see no necessity to use this line unless thetam > fei. LHE May 20, 2015
        }

    for (i = 0; i < soil->n_layer; i++)
    {
        if (soil->psim[i] > soil->psi_min)  // changed 10.0 to psi_min. LHE. Feb. 13, 2013.
            fpsisr[i] = 1.0 / (1 + std::pow((soil->psim[i] - soil->psi_min) / soil->psi_min, soil->alpha));   //psi_sr in m H2O! This is the old version. LHE.
        else
            fpsisr[i] = 1.0;

        ft[i] = (float)(1.0 - std::exp(t1 * std::pow(soil->temp_soil_p[i], t2))); // 1/x

        // ft[i] = min(ft[i], 1.0);  // LHE.
        //ft[i] = max(0.001, ft[i]); //  changed 0.1 to 0.001. LHE.

        fpsisr[i] = fpsisr[i] * ft[i];
    }


    for (i = 0; i < soil->n_layer; i++)
        dtt[i] = soil->f_root[i] * fpsisr[i]; /* eq. 14 in Ju 2006 */

    //dtt[0] = 0.0;
    float dtt_sum = 0.0;
    // for (i = 0; i < soil->n_layer; i++)
    for (i = 0; i < soil->n_layer -1; i++)
        dtt_sum = dtt_sum + dtt[i];/* eq. 14 in JU2006 */

    if (dtt_sum < 0.000001)
        soil->f_soilwater = 0.1; // when soil temperatures in all layers are <=0. LHe
    else
    {
        // for (i = 0; i < soil->n_layer; i++)
        for (i = 0; i < soil->n_layer -1; i++)
        {
            soil->dt[i] = dtt[i] / dtt_sum;

            //if (p->dt[0] < 0.0000001)
            //printf("%f\n", p->dt[0]);

            if (std::isnan(soil->dt[i]))
                printf("dt0: %f\n", ft[0]);
        }


        //fpsisr[0] = 0;
        float fpsisr_sum = 0;
        // for (i = 0; i < soil->n_layer; i++)
        for (i = 0; i < soil->n_layer -1; i++)
        {
            fpsisr_sum = fpsisr_sum + fpsisr[i] * soil->dt[i]; /* eq. 12, in Chen 2012 GBC; eq 15 in JU */
        }

        soil->f_soilwater = MAX(0.1, fpsisr_sum);
    }


    // in-process value check
    //printf("fpsisr[0]=%f\n",fpsisr[0]);
}

/// @brief Function to calcualte soil water uptake from a layer
/// @param soil       soil variables struct
/// @param Trans_o    transpiration from overstory canopies
/// @param Trans_u    transpiration from understory canopies
/// @param Evap_soil  evaporation from soil
/// @return void
void Soil_Water_Uptake(Soil_t* soil, float Trans_o, float Trans_u, float Evap_soil)
{
    int i;
    float Source;

    Source = Trans_o + Trans_u;

    // for the top layer
    soil->Ett[0] = Source * soil->dt[0] + Evap_soil;

    // for each layer:
    for (i = 1; i < soil->n_layer; i++)
        soil->Ett[i] = Source * soil->dt[i];
}

/// @brief Function to update soil moisture using the original Brooks-Corey model
/// @param p       soil variables struct
/// @param step   the total seconds in this step (period), defined in beps.h
/// @note kkk (outside of the function): step within an hour or half hour measurement
/// @return void
void UpdateSoilMoisture(Soil_t* p, float step)
{
    double Inf, Inf_max; // infiltration, and Maximum infiltration
    int i;
    float this_step = 0; //LHE
    float total_t = 0; //LHE
    float max_Fb = 0; //LHE

    float n = p->b[0] + 1.0f;
    float m = 1.0f - 1.0f / n;

    // assign the current soil temperature to prev variables.
    for(i=0; i<=p->n_layer; i++) // save previous thetam. LHE.
        p->thetam_prev[i] = p->thetam[i];

    for(i=0; i<=p->n_layer; i++)
    {
        if( p->temp_soil_c[i] > 0.0)
            p->f_ice[i] = 1.0; // f_ice should be named as f_water? LHe
        else if( p->temp_soil_c[i] < -1.0)
            p->f_ice[i] = 0.1; // maybe f_ice should be zero? LHE.
        else p->f_ice[i] = 0.1 + 0.9 * ( p->temp_soil_c[i] + 1.0);
    }

    /*juweimin================================================*/
    // this part solve the upper boundary condition(Infiltration). LHE
    // the maximum Infiltration. Reference? The inf should be changing very fast during a precipitation because thetam is changing. LHE.

    Inf_max=p->f_ice[0] * p->Ksat[0] * (1 + (p->fei[0] - p->thetam_prev[0]) / p->d_soil[0] * p->psi_sat[0] * p->b[0] / p->fei[0]);
    // printf("Inf_max: %f\n", Inf_max);

    Inf = MAX(p->f_ice[0] * (p->Zp / step + p->r_rain_g), 0); // This should be unnecessary since tmp >=0; LHE.
    // printf("Inf: %f\n", Inf);

    Inf=MIN(Inf_max,Inf);
    Inf=MAX(0,Inf);  // This should be unnecessary since Inf_max >=0; LHE.

    p->Zp = (float)(p->Zp / step + p->r_rain_g - Inf) * step; // Ponded water after runoff. This one is related to runoff. LHe.
    p->Zp = MIN( 10 , p->Zp * 0.98);
    // if(p->Zp > 0)printf("pond: %.8f\n", p->Zp);
    /*==============juweimin----------------------------------------*/

    // begining of self-adaption step by LHE. Oct 16, 2012
    while(total_t < step)
    {
        for(i=0; i < p->n_layer; i++)
            p->km[i] = p->f_ice[i] * p->Ksat[i] * std::pow((p->thetam[i] / p->fei[i]), (2 * p->b[i] + 3));
        for(i=0; i < p->n_layer; i++)
        {
            if(i < p->n_layer - 1 )
                p->thetab[i] = (p->thetam[i + 1] / p->d_soil[i + 1] + p->thetam[i] / p->d_soil[i]) / (1 / p->d_soil[i] + 1 / p->d_soil[i + 1]);
            else { // the lowest p->n_layer
                double d1;
                d1 = (p->thetam[i] - p->thetab[i-1]) * 2.0 / p->d_soil[i];
                d1=MIN(d1,0);
                p->thetab[i] = p->thetam[i] + d1*p->d_soil[i] / 2.0;
                p->thetab[i] = MIN(p->thetab[i], p->fei[i]);
            }

        }

        for(i = 0; i < p->n_layer; i++)
        {
            if(i < p->n_layer - 1 )
            {
                // the unsaturated hydraulic conductivity at soil lower boundary.
                p->Kb[i] = p->f_ice[i] * (p->Ksat[i] * p->d_soil[i] + p->Ksat[i+1] * p->d_soil[i + 1]) / (p->d_soil[i] + p->d_soil[i + 1]) * \
                 std::pow(p->thetab[i] / p->fei[i], (2 * p->b[i] + 3)); // Note: Kb[0] to Kb[n_layer-1] are not used in the model. LHe.

            }

            else // when i == p->LAYER - 1
                p->Kb[i] = 0.5 * p->f_ice[i] * p->Ksat[i] * std::pow(p->thetab[i] / p->fei[i], (2 * p->b[i] + 3));
        }

        // the unsaturated soil water retention. LHe
        for(i = 0;i <= p->n_layer - 1;i++)

        {
            p->psim[i] = p->psi_sat[i] * std::pow(p->thetam[i] / p->fei[i], - p->b[i]);
            p->psim[i] = MAX(p->psi_sat[i], p->psim[i] );  // I see no necessity to use this line unless thetam > fei. LHE May 20, 2015
            // if (p->psim[i] > 300)  p->psim[i] = 300.0;      /*juweimin05   130->300 */
        }

        // the unsaturated soil water retention @ boundaries. LHe
        for(i=0; i < p->n_layer; i++)
        {
            p->psib[i] = p->psi_sat[i] * std::pow(p->thetab[i] / p->fei[i], - p->b[i]);
            p->psib[i] = MIN(p->psi_sat[i], p->psib[i]);
            // p->psib[i] = min(300,p->psib[i]);
        }

        // the unsaturated hydraulic conductivity of soil p->n_layer @ boundaries
        for(i=0; i < p->n_layer; i++)
        {
            if(i < p-> n_layer-1)
                p->KK[i] = (p->km[i] * p->psim[i] + p->km[i + 1] * p->psim[i + 1])  \
							/ (p->psim[i] + p->psim[i + 1]) * (p->b[i] + p->b[i + 1]) / (p->b[i] + p->b[i + 1] + 6);  /*See seller's*/
            else 	// when i == LAYER-1
                p->KK[i]  = (p->km[i] * p->psim[i] + p->Kb[i] * p->psib[i])    \
							/(p->psim[i] + p->psib[i]) * p->b[i] / (p->b[i] + 3);
        }

        float depth_soil = 0;
        float drainage_coeff;

        // Fb, flow speed. Dancy's law. LHE.
        for(i=0;i <= p->n_layer - 1; i++)
        {
            depth_soil += p->d_soil[i];
            if(i < p->n_layer - 1)
            {
                p->r_waterflow[i] = p->KK[i] * (2*(p->psim[i+1] - p->psim[i]) / (p->d_soil[i] + p->d_soil[i+1])+1); /* downwards, positive*/
                // +1 accounts for gravitational drainage. LHE
            }
            else
            {
                if(depth_soil < p->water_table)
                {

                    // drainage_coeff = calculate_exponential(p->water_table, -4);
                }
                else
                {
                    drainage_coeff =  0.01;
                }
                drainage_coeff = 1;
                // p->r_waterflow[i] = p->km[i] * (0+1) * drainage_coeff; // Seller's 1996. Eq. 37. simplified.
                p->r_waterflow[i] = 0; // from Ju.
            }

        }


        // check the r_waterflow further. LHE
        for(i=0;i<p->n_layer-1;i++)
        {
            p->r_waterflow[i] = MIN((p->fei[i+1] - p->thetam[i+1]) * p->d_soil[i+1] / step + p->Ett[i+1], p->r_waterflow[i]); // this line is supposed to confine the flux or flow speed but this is not enough. LHE Oct 16, 2012.

            if(std::fabs(p->r_waterflow[i]) > max_Fb) max_Fb = std::fabs(p->r_waterflow[i]); // find max_Fb for all p->LAYERSs.
        }

        if(max_Fb > 1.0e-5)
            this_step = 1.0; // determinte the sub-step according to order of Fb empirically .
        else if(max_Fb > 1.0e-6)
            this_step = 30.0;
        else this_step = 360.0;

        total_t = total_t + this_step;
        if(total_t > step) this_step = this_step - (total_t - step);

        // from there: step is replaced by this_step. LHE
        // for(i=0;i < p->n_layer;i++)
        // {
        //     if(i==0)
        //         p->thetam[i] = p->thetam[i] + (Inf * this_step - p->r_waterflow[i] * this_step - p->Ett[i] * this_step) / p->d_soil[i]; // step->this_step
        //     else
        //         p->thetam[i] = p->thetam[i] + (p->r_waterflow[i-1] * this_step - p->r_waterflow[i] * this_step - p->Ett[i] * this_step) / p->d_soil[i];	// step->this_step
        //
        //     /*  thetam[i][kkk]=max(theta_vwp[i]*0.25,thetam[i][kkk]); */
        //     p->thetam[i] = MAX(p->theta_vwp[i], p->thetam[i]);
        //     p->thetam[i] = MIN(p->fei[i],p->thetam[i]);
        // }

        for (i = 0; i < p->n_layer; i++) {
            if (i == 0) {
                p->thetam[i] = p->thetam[i] + (Inf * this_step - p->r_waterflow[i] * this_step - p->Ett[i] * this_step) / p->d_soil[i];
            } else {
                p->thetam[i] = p->thetam[i] + (p->r_waterflow[i-1] * this_step - p->r_waterflow[i] * this_step - p->Ett[i] * this_step) / p->d_soil[i];
            }

            // 限制不小于萎蔫点
            p->thetam[i] = MAX(p->theta_vwp[i], p->thetam[i]);

            // 检查是否超过孔隙度
            if (p->thetam[i] > p->fei[i]) {
                double excess = (p->thetam[i] - p->fei[i]) * p->d_soil[i];
                p->thetam[i] = p->fei[i];  // 限制到孔隙度

                if (i > 0) {
                    // 往上一层加
                    p->thetam[i-1] += excess / p->d_soil[i-1];
                } else {
                    // 表层 -> 加到地表储水 Zp
                    p->Zp += excess;
                }
            }
        }

        // printf("%.9f\n", p->water_table);
    } // end of while: the self-adaption step. by LHE.

    // for(i=0;i<p->n_layer;i++)
    // {  // ref?
    //     p->ice_ratio[i] = p->ice_ratio[i] * p->thetam_prev[i] / p->thetam[i];
    //     p->ice_ratio[i] = MIN(1.0, p->ice_ratio[i]);
    // }

}

static double calculate_single_layer_flow(
    pubv* myseed,
    int j, int iLine, int dir, int layer,
    Soil_t* current_soil,
    float* Array_Ele, unsigned char* watershed, double dx_val,
    Soil_index_t* soilindex, short textureindex, int CFL)
{
    int d_ni[] = {-1, -1, -1, 0, 0, 1, 1, 1}; // 行偏移
    int d_nj[] = {-1, 0, 1, -1, 1, -1, 0, 1}; // 列偏移
    int dir_to_index[8] = {0, 1, 2, 3, 5, 6, 7, 8};

    if (dir < 0 || dir > 8 || dir == 4) return 0.0;

    int iX = myseed->nlines;
    int iY = myseed->npixels;

    // 当前在缓冲区中的行号 i
    int i;
    if (iLine == 0) i = 0;
    else if (iLine == iX - 1) i = 2;
    else i = 1;

    // 边界约束：上下左右超出地图范围
    if ((iLine == 0      && d_ni[dir] == -1) ||  // 上边界不能往上
        (iLine == iX - 1 && d_ni[dir] == 1)  ||  // 下边界不能往下
        (j == 0          && d_nj[dir] == -1) ||  // 左边界不能往左
        (j == iY - 1     && d_nj[dir] == 1))     // 右边界不能往右
    {
        return 0.0;
    }

    // 邻居的列、行索引
    int nj = j + d_nj[dir];
    int n_buf_i = i + d_ni[dir];
    if (n_buf_i < 0 || n_buf_i >= 3)
        return 0.0;


    if (Array_Ele[i * iY + j] >= 9999.0f || Array_Ele[n_buf_i * iY + nj] >= 9999.0f)
        return 0.0;

    if (textureindex < 0 || textureindex >= 12 || layer < 0 || layer >= MAX_LAYERS)
        return 0.0;

    Soil_t* center_soil = &current_soil[4];
    Soil_t* neighbor_soil = &current_soil[dir_to_index[dir]];

    float Ks = soilindex[textureindex].soil_K0H[layer] / (float)CFL;
    float current_theta = center_soil->thetam[layer];
    float current_theta_s = center_soil->fei[layer];
    float current_layer_thickness = center_soil->d_soil[layer];
    float neighbor_theta = neighbor_soil->thetam[layer];
    float neighbor_theta_s = neighbor_soil->fei[layer];

    double current_layer_top = Array_Ele[i * iY + j];
    double neighbor_layer_top = Array_Ele[n_buf_i * iY + nj];

    if (current_theta < 0.12 || neighbor_theta < 0.12 || neighbor_layer_top == 0 || current_layer_top == 0)
        return 0.0;

    for (int l = 0; l < layer; l++) {
        current_layer_top -= center_soil->d_soil[l];
        neighbor_layer_top -= neighbor_soil->d_soil[l];
    }
    float psi_center = center_soil->psi_sat[layer] * pow(current_theta / current_theta_s, -center_soil->b[layer]);
    float psi_neighbor = neighbor_soil->psi_sat[layer] * pow(neighbor_theta / neighbor_theta_s, -neighbor_soil->b[layer]);
    float h_center = (float)(current_layer_top + psi_center);
    float h_neigh  = (float)(neighbor_layer_top + psi_neighbor);
    float dh = h_center - h_neigh ;
    // 判断上游单元
    Soil_t* donor_soil = (dh > 0) ? center_soil : neighbor_soil;

    // 使用 donor 的 kr
    float theta = donor_soil->thetam[layer];
    float theta_s = donor_soil->fei[layer];
    float b = donor_soil->b[layer];
    float kr = pow(theta / theta_s, 2 * b + 3);

    // 计算流量
    double gradient = dh / dx_val;

    double flow_rate_per_area = -Ks * kr * gradient;
    double contact_area = current_layer_thickness * dx_val;
    double flow_volume = flow_rate_per_area * contact_area;

    if (flow_volume > 0) {
        double available_water = MAX(current_theta - center_soil->theta_vwp[layer], 0) * center_soil->d_soil[layer] * dx_val;
        // double available_water2 = MAX(current_theta - center_soil->fei[layer], 0) * center_soil->d_soil[layer] * dx_val;
        flow_volume = MIN(flow_volume, available_water);
        // flow_volume = MIN(flow_volume, available_water2);
    } else {
        // double neighbor_receiving_capacity = MAX(neighbor_soil->fei[layer] - neighbor_theta, 0) * neighbor_soil->d_soil[layer] * dx_val;
        double center_giving_capacity = MAX(neighbor_theta - neighbor_soil->theta_vwp[layer], 0) * neighbor_soil->d_soil[layer] * dx_val;
        // flow_volume = MAX(flow_volume, -neighbor_receiving_capacity);
        flow_volume = MAX(flow_volume, -center_giving_capacity);
    }

    return flow_volume;
}

void UpdateSoilLateralFlow(pubv* myseed, int iLine, Soil_t* soil,
                          Soil_t* Soil_Array_3r, float* Array_Ele, unsigned char* watershed,
                          unsigned char* soil_texture, Soil_index_t* soilindex,float* baseflow, int CFL)
{
    int iX = myseed->nlines;
    int iY = myseed->npixels;
    double dx_cardinal = (double)(myseed->iXsize);
    double dx_diagonal = dx_cardinal * 1.414;
    int i;
    if (iLine == 0) i = 0;
    else if (iLine == iX - 1) i = 2;
    else i = 1;

    for(int j = 0; j < iY; j++)
    {
        // 安全检查
        if (!soil || !Soil_Array_3r || !Array_Ele || !watershed || !soil_texture || !soilindex) {
            continue;
        }

        if (watershed[j] == 0) {
            baseflow[j]  = -777.0;
            continue;
        }

        if (iLine < 0 || j < 0 || iLine >= iX || j >= iY) {
            continue;
        }

        float total_t = 0;
        float max_flow = 0;
        short textureindex;

        if(soil_texture[j] > 0 && soil_texture[j] <= 120) {
            textureindex = soil_texture[j]/10 - 1;
        } else {
            textureindex = 1;
        }

        Soil_t current_soil[9];
        double net_lateral_flow[MAX_LAYERS];
        ReadInSoil(Soil_Array_3r, current_soil, iLine, j, myseed);

        // 检查中心像元是否被正确初始化
        if (current_soil[4].thetam[0] < 0) {
            continue;
        }

        // 判断是否为出水口
        bool is_outlet = true;
        bool has_any_neighbor_outside_watershed = false;
        double center_elev = Array_Ele[i * iY + j];  // 正确访问当前缓冲区中像元的高程

        for (int dir = 0; dir < 8; dir++) {
            int d_ni[] = {-1, -1, -1, 0, 0, 1, 1, 1};
            int d_nj[] = {-1, 0, 1, -1, 1, -1, 0, 1};

            // int global_ni = iLine + d_ni[dir];
            int nj = j + d_nj[dir];
            int local_ni = i + d_ni[dir]; // 缓冲区中的行

            if (Array_Ele[local_ni * iY + nj] >= 9999.0f)
                continue;

            if (Array_Ele[local_ni * iY + nj] <= center_elev)
                is_outlet = false;
        }

        is_outlet = is_outlet && has_any_neighbor_outside_watershed;

        // 开始处理每一层
        for (int layer = 0; layer < MAX_LAYERS; layer++)
        {
            net_lateral_flow[layer] = 0.0;

            if (is_outlet)
            {
                // 出水口逻辑
                double theta = current_soil[4].thetam[layer];
                double fei = current_soil[4].fei[layer];
                double theta_vfc = current_soil[4].theta_vfc[layer];
                double available = MAX(theta - theta_vfc, 0.0);
                double d_soil = current_soil[4].d_soil[layer];

                if (available > 0.0)
                {
                    double max_outflow = available * d_soil * dx_cardinal;
                    net_lateral_flow[layer] = -MIN(0.01 / CFL, max_outflow);
                }
                else
                {
                    net_lateral_flow[layer] = 0.0;
                }

                continue; // 跳过邻居循环
            }

            for (int dir = 0; dir < 8; dir++) {
                double current_dx = (dir % 2 == 0) ? dx_diagonal : dx_cardinal;

                double flow = calculate_single_layer_flow(myseed, j, iLine, dir, layer,
                                                          current_soil, Array_Ele, watershed,
                                                          current_dx, soilindex, textureindex, CFL);

                net_lateral_flow[layer] += flow;
            }
        }

        // 更新中心像元的thetam
        // float total_lateral_flow = 0.0f;
        // for(int layer = 0; layer < MAX_LAYERS; layer++) {
        //     double dtheta = net_lateral_flow[layer] / (current_soil[4].d_soil[layer] * dx_cardinal);
        //     current_soil[4].thetam[layer] += dtheta;
        //     double theta_MIN = MIN(current_soil[4].thetam[layer], current_soil[4].fei[layer]);
        //     double theta_MAX = MAX(current_soil[4].theta_vwp[layer], theta_MIN);
        //     total_lateral_flow += (float)dtheta;
        //     soil[j].thetam[layer] = theta_MAX;
        // }
        // baseflow[j]  = total_lateral_flow;
        // printf("%f\n",baseflow[j]);

        float total_lateral_flow = 0.0f;
        float excess_depth_from_below = 0.0f; // This variable will carry the excess water upward

        // Iterate from the deepest layer (n_layer - 1) up to the surface (0)
        for (int layer = current_soil[4].n_layer - 1; layer >= 0; layer--) {
            double layer_volume = current_soil[4].d_soil[layer] * dx_cardinal;
            double dtheta = net_lateral_flow[layer] / layer_volume;

            // Calculate new moisture content, adding the incoming dtheta and any excess depth from the layer below
            double theta_new = current_soil[4].thetam[layer] + dtheta + (excess_depth_from_below / current_soil[4].d_soil[layer]);

            // Reset the excess depth for the next layer's calculation
            excess_depth_from_below = 0.0f;

            // Accumulate total lateral flow
            total_lateral_flow += (float)dtheta * current_soil[4].d_soil[layer];

            float theta_s  = current_soil[4].fei[layer];
            float theta_min = current_soil[4].theta_vwp[layer];

            if (theta_new < theta_min) {
                theta_new = theta_min;
            }

            if (theta_new > theta_s) {
                // Calculate excess water depth and store it to be passed up
                excess_depth_from_below = (float)(theta_new - theta_s) * current_soil[4].d_soil[layer];
                theta_new = theta_s;
            }
            soil[j].thetam[layer] = (float)theta_new;
        }

        // After the loop, any remaining excess water has reached the surface
        soil[j].pondwater += excess_depth_from_below;
        baseflow[j]  = total_lateral_flow;

        double depth = 0;
        soil[j].unsaturated_storage = 0;

        for(int i=0;i<MAX_LAYERS-1;i++)
        {
            soil[j].unsaturated_storage += soil[j].thetam[i] * soil[j].d_soil[i];
            depth += soil[j].d_soil[i];
        }
        soil[j].unsaturated_storage /= depth;
    }
}

// 地表水流动模块：显式有限差分浅水流动，曼宁糙率默认0.05
static double calculate_single_surface_flow(
    pubv* myseed,
    int j, int iLine, int dir,
    Soil_t* current_soil, // 注意：这是9个像元的局部缓冲区
    float* Array_Ele,
    double dx_val,
    float manning_n,
    int CFL)
{
    // 方向偏移量
    int d_ni[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int d_nj[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int dir_to_index[8] = {0, 1, 2, 3, 5, 6, 7, 8};

    if (dir < 0 || dir > 8 || dir == 4) return 0.0;

    int iX = myseed->nlines;
    int iY = myseed->npixels;
    int i;
    if (iLine == 0) i = 0;
    else if (iLine == iX - 1) i = 2;
    else i = 1;

    // 边界检查
    if ((iLine == 0      && d_ni[dir] == -1) ||
        (iLine == iX - 1 && d_ni[dir] == 1)  ||
        (j == 0          && d_nj[dir] == -1) ||
        (j == iY - 1     && d_nj[dir] == 1))
    {
        return 0.0;
    }
    int nj = j + d_nj[dir];
    int n_buf_i = i + d_ni[dir];
    if (n_buf_i < 0 || n_buf_i >= 3) return 0.0;

    // 使用传入的局部9像元数组获取数据
    Soil_t* center_soil = &current_soil[4];
    Soil_t* neighbor_soil = &current_soil[dir_to_index[dir]];

    // 获取高程和水深
    float h = center_soil->pondwater;
    float hn = neighbor_soil->pondwater;
    double z = Array_Ele[i * iY + j];
    double zn = Array_Ele[n_buf_i * iY + nj];

    // 水面高程
    double H = z + h;
    double Hn = zn + hn;
    double dh = H - Hn; // 水面高程差

    // 如果没有高程差，则流量为零
    if (fabs(dh) < 1e-8) {
        return 0.0;
    }

    // 根据曼宁公式计算流量
    double S = dh / dx_val; // 水力坡度
    double h_avg;

    // 流量方向由高程差决定
    if (dh > 0) { // 中心像元向邻居流出
        h_avg = (h + hn) / 2.0;
    } else { // 邻居向中心像元流入
        h_avg = (h + hn) / 2.0;
    }

    // 确保平均水深大于0
    if (h_avg <= 1e-6) {
        return 0.0;
    }

    double dt = 86400 / CFL; // 单步时间步长

    // 曼宁公式：v = (1/n) * R^(2/3) * S^(1/2)
    // 这里简化处理，R近似等于h_avg
    double v = (1.0 / manning_n) * pow(h_avg, 2.0/3.0) * sqrt(fabs(S));

    // 流量 Q = v * A
    double contact_area = h_avg * dx_val; // 流动断面面积
    double flow_volume = v * contact_area * dt;

    // 流量方向和可用水量约束
    if (dh > 0) {
        // 本像元向邻居流出
        flow_volume = -flow_volume; // 流量为负，表示流出
        // 确保流出量不超过本像元可用水量
        double available_water_vol = h * (double)myseed->iXsize;
        flow_volume = MAX(flow_volume, -available_water_vol);
    } else {
        // 邻居向本像元流入
        // 确保流入量不超过邻居可用水量
        double neighbor_available_water_vol = hn * (double)myseed->iXsize;
        flow_volume = MIN(flow_volume, neighbor_available_water_vol);
    }
    return flow_volume;
}

void UpdateSurfaceWaterFlow(
    pubv* myseed,
    int iLine,
    Soil_t* soil,
    Soil_t* Soil_Array_3r, // 传入三行缓冲区
    float* Array_Ele,
    unsigned char* watershed,
    int CFL,
    float manning_n
) {
    int i;
    int iX = myseed->nlines;
    int iY = myseed->npixels;
    float dx_cardinal = myseed->iXsize;
    float dx_diagonal = dx_cardinal * 1.4142136f;
    int d_ni[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int d_nj[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    if (iLine == 0) i = 0;
    else if (iLine == iX - 1) i = 2;
    else i = 1;

    for (int j = 0; j < iY; j++) {
        // 安全检查
        if (watershed[j] == 0 || Array_Ele[i * iY + j] >= 9999.0f) {
            continue;
        }

        // 获取9个像元的局部数据
        Soil_t current_soil[9];
        ReadInSoil(Soil_Array_3r, current_soil, iLine, j, myseed);

        // 1. 出水口逻辑
        bool is_outlet = true;
        bool has_any_neighbor_outside_watershed = false;
        double center_elev = Array_Ele[i * iY + j];

        for (int dir = 0; dir < 8; ++dir) {
            int ni = i + d_ni[dir];
            int nj = j + d_nj[dir];

            // 边界检查，确保邻居在缓冲区内
            if (ni < 0 || ni >= 3 || nj < 0 || nj >= iY) {
                has_any_neighbor_outside_watershed = true;
                continue; // 缓冲区外的邻居视为流域外
            }

            int n_idx = ni * iY + nj;

            // 如果邻居在流域内且高程更低，则不是出水口
            if (watershed[nj] != 0 && Array_Ele[n_idx] < center_elev) {
                is_outlet = false;
                break;
            }

            // 检查邻居是否在流域外
            if (watershed[nj] == 0) {
                has_any_neighbor_outside_watershed = true;
            }
        }

        // 最终出水口条件：所有内部邻居都更高，且至少有一个邻居位于流域外
        if (is_outlet && has_any_neighbor_outside_watershed) {
            // 出水口：恒定通量边界（如每日最大流量0.01m/天）
            // 流量分配到单个CFL步
            float dt_day = 1.0f / CFL; // 单步时间占一天的比例
            float max_outflow_depth = 0.5f * dt_day;

            float out_depth = MIN(soil[j].pondwater, max_outflow_depth);
            soil[j].pondwater -= out_depth;
            if (soil[j].pondwater < 0) soil[j].pondwater = 0;

            continue; // 跳过后续的流量计算，因为水已从出水口流出
        }

        // 2. 正常流量计算
        double net_lateral_flow = 0.0;
        for (int dir = 0; dir < 8; dir++) {
            double current_dx = (dir % 2 == 0) ? dx_diagonal : dx_cardinal;

            double flow = calculate_single_surface_flow(
                myseed, j, iLine, dir,
                current_soil,
                Array_Ele,
                current_dx,
                manning_n,
                CFL);

            net_lateral_flow += flow;
        }

        // 更新中心像元的地表积水
        double d_pondwater = net_lateral_flow / (dx_cardinal * dx_cardinal);
        soil[j].pondwater += (float)d_pondwater;
        if (soil[j].pondwater < 0) {
            soil[j].pondwater = 0;
        }
    }
}