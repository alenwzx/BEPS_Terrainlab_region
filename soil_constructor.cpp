/**************************************************************************************************************
    1. soilindex[k] (k ∈ 0 ~ 11) ,该结构体数组规定了12种土壤的基本属性. 声明：BepsHydrScience.h line258; 赋值：readconf.cpp line127
    2. soil[j] (j ∈ 0 ~ pv->npixels) ，该结构体数组描述了一行像元的土壤属性. 声明：BepsHydrScience.h line207 赋值：soil_constructor.cpp
**************************************************************************************************************/
#include "stdafx.h"
#include "BepsHydrScience.h"
#include <math.h>

void Soil_constructor(pubv* pv, unsigned char* soil_texture,
                      float* soil_surf_kv,float* soil_surf_ks, float* soil_init_z, float* soil_init_temp,
                      float* carbon_pool1,float* carbon_pool2,float* carbon_pool3,float* carbon_pool4,float* carbon_pool5,float* carbon_pool6,float* carbon_pool7,float* carbon_pool8,float* carbon_pool9,
                      float* biomass_pool1,float* biomass_pool2,float* biomass_pool3,float* biomass_pool4,float* soil_depth,
                      Soil_index_t* soilindex, int iLine, Soil_t* soil, unsigned char* watershed,int line,float*buffer_nitrogen)
{

    short textureindex;

    float w,air_entry,z;
    // float bata =0.943f;

    // starts image loop 该循环遍历一行数据
    for (int j=0; j<pv->npixels; j++)
    {
        // 设置 textureindex(∈0-11) 映射 soil_texture[j](∈10-120)
        if(soil_texture[j]>0 && soil_texture[j]<=120)
            textureindex=soil_texture[j]/10-1;
        else
            textureindex=1;
        // 边界赋值
        if (watershed[j] == 0 ||soil_init_z[j]  <-10.0)
        {
            soil[j].K0_decay_m          =soilindex[3].pore_index;   // -99.0f;	//soil parameter for Kz calculation
            soil[j].soil_b              =soilindex[3].soil_b;       // -99.0f;
            soil[j].saturation_suction  =soilindex[3].suction_head;	// -99.0f;	//suction in meters when soil is saturation
            soil[j].saturated_Kv        =soilindex[3].soil_K0;      // -99.0f;	//at surface. m per day
            soil[j].saturated_Ks        =soilindex[3].soil_K0H;     // -99.0f;	//at surface. m per day
            soil[j].saturation_deficit  =0.2;                       // -99.0f;	//meter. Zero at saturation
            soil[j].water_table         =1.0;	                    //meter from soil surface
            soil[j].pondwater           =0.0;	                    //pond 为什么池塘水体设为0呢?这个设置应该针对的是研究区外的边界点
            soil[j].unsaturated_storage =soilindex[textureindex].field_cap*soil[j].water_table ;// -99.0f;	//meter	....MEM: of water in the unsaturated zone!!!
            soil[j].Max_depth_Z         =2.0;                       // -99.0f;	//meter	//ori 1.0 on 23jun
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
                    soil[j].soil_b				= (float)soilindex[k].soil_b;
                    soil[j].saturation_suction	= (float)soilindex[k].suction_head;
                    soil[j].saturated_Kv		= (float)soilindex[k].soil_K0;
                    soil[j].saturated_Ks		= (float)soilindex[k].soil_K0H;
                    /*土壤深度*/
                    if (soil_depth[j]	<= -9999.0f) //soil-depth.bin 设置成-9999.0f即可
                        soil[j].Max_depth_Z		= (float)soilindex[k].max_z;
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
                        soil[j].ST_Layer_1=0;//these should be using measured values土壤层深度以及水体应该用实测值
                        soil[j].ST_Layer_2=0;
                        soil[j].ST_Layer_3=0;
                        soil[j].ST_Layer_4=0;
                        soil[j].ST_Layer_5=0;
                        soil[j].ST_Layer_6=0;
                        soil[j].pondwater=0;
                    }

                }//end of if block
            }//end of k for loop

            w=0.92f;	//wetnees value between 0.9 and 1.0. See Clapp and Hornberger, 1978
            air_entry = soil[j].saturation_suction*(float)pow(w,(double)-soil[j].K0_decay_m);

            //不饱和区土壤深度Z
            z = MIN(soil[j].water_table, soil[j].Max_depth_Z);
            if (z > 0)//存在不饱和区
            {   //不饱和区土壤田间含水量
                soil[j].unsaturated_storage	= (float)soilindex[textureindex].field_cap*z;
                //土壤饱和差
                soil[j].saturation_deficit	= (float)(MIN(soilindex[textureindex].porosity,1))*z - soil[j].unsaturated_storage;
            }
            else//不存在不饱和区
            {
                soil[j].saturation_deficit = z;
                soil[j].unsaturated_storage=0.0;
            }
        }//end of if-else block within the for loop

    }//end of j loop 结束行像元的遍历

}//end of the function
