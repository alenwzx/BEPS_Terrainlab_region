/****************************************************************************
 	method -->2
*/

#include "stdafx.h"
#include "BepsHydrScience.h"
#include <math.h>


void soil_water_balance2(pubv* start,float* runoff_baseflow,float * waterin,float* runoff_total,unsigned char* soil_texture,
                         Soil_index_t* soilindex,Soil_t* soil,float* soil_capillary_rise,float* soil_percolation,
                         Canopy_t* canopy_ptr,unsigned char* lc, unsigned char* watershed_ptr,
                         int iDay,double dDaylength,int iTestCurrentLine)



{
    int		counter=0;
//	int temp;
    float	p1, q1, soilFC, unsattemp = 0.0f;
    float	retention = 0.00;//0.020;				//retention height is 0cm above the surface-->  持水高度？

    float	soilET,soilET_un ;
    float	a=0.0f, b=0.0f, d =0.0f, q2=0.0f, wc=0.0f;

    float	capillaryrise, precip;			//meters 这个是降雨还是下渗？确定一下
    float	Delta_water			= 0.0;
    float	Delta_water_table	= 0.0;		//meters
    float	porosity			= 0.0;
    float	unsat_available		= 0.0;
    float	unsat_delta			= 0.0;
    float	depth=0.0f, c =0.0f, extraWater = 0.0f;
    int		j;//,k;
    float   soil_porosity,soil_capacity,soil_point;	// MM 2005-Apr-28
    short   textureindext;
    int kkk;
    float Ksat_z, tp, air_entry, sorptivity, inf_cap, wetting_suction;
    float runoff;

    for(j=0; j<start->npixels; j++)
    {

        if(soil_texture[j]>0 && soil_texture[j]<=120)
        {
            textureindext=soil_texture[j]/10-1;
        }
        else
            textureindext=1;


        unsat_delta					= 0.0;
        a							= 0.0;
        b							= 0.0;
        d							= 0.0;
        wc							= 0.0;
        p1							= 0.0;
        soilET						= 0.0;
        soilFC						= 0.0;
        q1							= 0.0;
        Delta_water					= 0.0;
        Delta_water_table			= 0.0;	// m
        extraWater					= 0.0;
        //	runoff_total[j]				= 0.0f;

        float epsilon= runoff_total[j]*0.35;//new
        runoff_total[j]=runoff_total[j]-runoff_total[j]*0.75;//new   有径流参数runoff_total[j]*0.35

        precip	= (float)waterin[j];     //这里定义了waterin
        precip=precip+epsilon; //new   precip = waterin[j] + runoff_total[j]*0.35

        //for (iDay = 60 )

        soil_porosity	 =  (float)	soilindex[textureindext].porosity;
        soil_capacity    =(float)soilindex[textureindext].field_cap;
        soil_point    =(float)soilindex[textureindext].wilting_pt;



        Ksat_z = soil[j].saturated_Kv * exp( -1.0 * (soil[j].water_table * soil[j].K0_decay_m ));

        air_entry = soil[j].saturation_suction/(pow((soil[j].unsaturated_storage/(soil[j].water_table*soil_porosity)),-soil[j].K0_decay_m));


        wetting_suction = ((2 + 3*soil[j].soil_b) / (1 + 3*soil[j].soil_b)) * (air_entry/2); //Beckers et al. (2004)


        inf_cap = Ksat_z * (1 + (((soil_porosity - (soil[j].unsaturated_storage/soil[j].water_table)) * wetting_suction) / (precip)));
        //OS(12/9/2006) I used half the total daily precipitation here instead of cumulative infilitration which is calculated when using the Beckers et al. (2004) approach on a daily time-step...
        //这里使用了precip，与waterin相关



        if ((watershed_ptr[j] == 0)||(lc[j] == 0))//MEM         不处理像元的变量赋值，如果河流作为不处理像元呢？
        {
            runoff_total[j]						= -999.0f;		//***Added by Andriy  地表径流
            runoff_baseflow[j]					= -999.0f;      //                     基流
            unsat_available						= -999.0f;      //                     不饱和层可获水量（不饱和层蓄水量）
            soil_capillary_rise[j]				= -999.0f;		//***Added by Andriy   毛细管上升量
            soil_percolation[j]					= -999.0f;		//***Added by Andriy   渗透的量
            soil[j].water_table					= -999.0f;      //                     地下水位深度
        }
        else
        {



            p1 = precip;
            //这里使用了precip，与waterin相关






        }
        soilET		=	(canopy_ptr[j].canopy_transpiration_unsat) +
                        (canopy_ptr[j].canopy_transpiration_sat)   +
                        (canopy_ptr[j].litter_evaporation)         +
                        (canopy_ptr[j].moss_transpiration)         +
                        (canopy_ptr[j].soil_evaporation);


        /*soilET is the water consumed from soil*/

        soilET_un =	(canopy_ptr[j].canopy_transpiration_unsat) +
                    //(1000*(canopy_ptr[j].canopy_UT))           +
                    (canopy_ptr[j].litter_evaporation)         +
                    (canopy_ptr[j].moss_transpiration)         +
                    (canopy_ptr[j].soil_evaporation);

        soilET                                   /= 1000.0; //OS: this is done to get water in m instead of mm!!!?!?!?!?
        soilET_un                                /= 1000.0;
        canopy_ptr[j].canopy_evaporation         /= 1000.0;
        canopy_ptr[j].canopy_transpiration_unsat /= 1000.0;
        canopy_ptr[j].canopy_transpiration_sat   /= 1000.0;
        canopy_ptr[j].litter_evaporation         /= 1000.0;
        canopy_ptr[j].moss_transpiration           /= 1000.0;
        canopy_ptr[j].soil_evaporation           /= 1000.0;
        //	canopy_ptr[j].canopy_UT		             /= 1000.0;
        //	canopy_ptr[j].canopy_uts		         /= 1000.0;


        if(soil[j].unsaturated_storage== 0.0||soil[j].water_table== 0.01) //本来是0，自行设置阈值为0.01，参考其它工作
            d = 0.0;
        else
        {

            // d 应该是不饱和带的饱和度
            d = soil[j].unsaturated_storage	/(soil_porosity*soil[j].water_table);	//***Added by Andriy
            /* d is the degree of saturation of the unsaturated zone --> "soil[j].unsaturated_storage/soil[j].water_table" is the "volumetric water content of the unsaturated zone"*/
        }// d --> OS: I think this should be the saturation deficit????


        //1.当地下水位接近地表
        if(soil[j].water_table <= 0.01)
            //water_table is near the surface --> Ajit set this to 0.00....it works for him
            //这个阈值应该可以自行设定一下叭
        {
            // MEM: retention is the puddled water!! 水坑的水
            //OS(13/9/2006): I added the few lines equation below to account for the situation where precip > inf_capacity
            //Pn（净降水）超过土壤最大水分容量，会发生径流
            b = retention - (soil[j].water_table);
            Delta_water = (-runoff_baseflow[j] +MAX(0, b)+ soilET - p1);//地下水位当日变化量
            soil[j].water_table += Delta_water;                         //更新地下水位
            b = retention - (soil[j].water_table);//new                 //更新径流
            soil[j].water_table	 =MAX(retention,soil[j].water_table);  //计算地下水位
            runoff_total[j]+= (MAX(0, b));//*1000;	//new              //计算径流
            capillaryrise				= 0.0;
            q1							= 0.0; //no unsaturated flow q1是不饱和层的水流？
            soil[j].unsaturated_storage	= 0.0;
            //
            soil[j].saturation_deficit	= 0.0;


        } /*the end of soil[j].water_table <= 0.01*/

        //2.当地下水位不出露
        // soil[j].water_table>0.01
        else
        {
            //一、 soilFC代表在田间持水量下的水量
            soilFC =(float) (soil[j].water_table * soilindex[textureindext].field_cap);

            // OS(10/6/2006): what does that mean????? According to Ajit the amount of water in mm at field capacity...makes kinda sense to me
            //	 soil[j].unsaturated_storage= soil[j].unsaturated_storage+p1-soilET_un;

            //2.1 不饱和层储水量>田间储水量,会发生渗透（不饱和层->饱和层）
            if(soil[j].unsaturated_storage > soilFC)
            //OS: i.e. unsaturated storage is higher than the amount of water at field capacity

            {

                extraWater					= soil[j].unsaturated_storage - soilFC;     //额外的水，渗透的量？
                soil[j].unsaturated_storage = soilFC;
                soil[j].water_table			-= extraWater/(soil_porosity-soil_capacity);//地下水位当日变化量
                soil[j].water_table=MAX(retention,soil[j].water_table);                 //更新地下水位

                soil[j].unsaturated_storage=MAX(0,soil_capacity*soil[j].water_table);   //不饱和层蓄水量
                d=soil_capacity;                                                        //土壤含水量

            }

            //2.2 不饱和层储水量 < 田间储水量
            else     //OS: this is the case where unsaturated storage is less than storage at field capacity...
            {

                extraWater					= 0.0;                                  ////额外的水为0

                //计算不饱和层的水量饱和亏损
                soil[j].saturation_deficit	=	soil_porosity*soil[j].water_table - //***Added by Andriy
                                                soil[j].unsaturated_storage;

                if(soil[j].saturation_deficit	<=0.0)
                    soil[j].saturation_deficit	= 0.0;


                //2.21 如果土壤含水量 > 凋萎点，出现不饱和层水流,q1代表渗透的量
                if(d>soil_point)

                    //	q1=(float)compute_unsat_zone_drainage(textureindext, soil[j], soil_point,soil_capacity,soil_porosity );//这里涉及到了土壤质地耶
                    q1=MAX(0,(float)compute_unsat_zone_drainage(textureindext, soil[j],soil_point,soil_capacity,soil_porosity ));

                //如果土壤含水量 < 凋萎点，渗透的量为0
                else

                    q1=0;

                // make sure the rise is converted into water height
                //2.22 如果土壤含水量 < 田间持水量，发生毛细管上升
                if(d<soil_capacity) // OS)10/6/2006): is soil_capacity the field capacity? seems like ....
                {

                    capillaryrise = (float)compute_cap_rise(soil[j], soil_porosity);
                    capillaryrise=MIN((soil_capacity-d)* soil[j].water_table,capillaryrise);

                }
                    //如果土壤含水量 > 田间持水量，没有毛细管上升
                else
                {

                    capillaryrise=0;

                }


                // 二、a 代表在凋萎点下的水量
                a= (float) (soil[j].water_table * soilindex[textureindext].wilting_pt);

                // 如果不饱和层储水量 > 凋萎点下储水量
                // unsat_available 代表不饱和层可获得的水量
                if(soil[j].unsaturated_storage >= a)
                    unsat_available = soil[j].unsaturated_storage - a;       //计算不饱和层可获得的水量
                else
                    unsat_available = 0.00000f;

                // unsat_delta 代表不饱和层的土壤水分变化
                unsat_delta =	(p1 + capillaryrise)						-
                                (canopy_ptr[j].canopy_transpiration_unsat	+ //unsaturated trees
                                 canopy_ptr[j].litter_evaporation			+
                                 canopy_ptr[j].soil_evaporation				+
                                 q1);                                        //计算不饱和层的土壤水分变化

                                 //p1是净降水，q1是不饱和层水流（渗透的量？），没有考虑地表径流，因为地下水位不出露

                // unsat_delta =	(capillaryrise-q1);


                //1. 如果不饱和层的土壤水分变化 < 0, 输入 < 输出项（饱和层->不饱和层）
                if(unsat_delta<=0.0) // input is lower than output (-), water is taken from sat_ and unsat_ zones
                {
                //	unsat_delta *= -1; // unsat_delta is changed to be positive (+)....MEM: why???


                    //1.1 如果不饱和层可获得的水量 > 不饱和层的土壤水分变化（更多可用的土壤水）
                    if(unsat_available > unsat_delta)
                    {
                    //	soil[j].unsaturated_storage -= unsat_delta; //water losses
                    //	unsat_delta = q1;//unsat_delta indicates the change in unsaturation zone


                        // Delta_water 代表饱和层的土壤水分变化？
                        Delta_water = -1*(runoff_baseflow[j]+q1	-
                                          canopy_ptr[j].canopy_transpiration_sat	-
                                          //canopy_ptr[j].canopy_uts	-
                                          capillaryrise);							//saturated zone

                        // Delta_water < 0 可以说明？
                        if( Delta_water<0)
                        {
                            Delta_water_table = Delta_water/
                                                (soil_porosity	-
                                                 soil[j].unsaturated_storage/soil[j].water_table);  //it is a %, not a really Delta_water_table
                                                                                                    //地下水位深度的变化量
                            d = soil[j].water_table;

                            //地下水位的更新
                            soil[j].water_table += Delta_water_table ;
                            //不饱和层蓄水量的更新
                            soil[j].unsaturated_storage=soil[j].unsaturated_storage*soil[j].water_table/d+unsat_delta;
                        }

                        // Delta_water > 0 可以说明？
                        else
                        {
                            Delta_water_table = Delta_water/
                                                (soil_porosity-
                                                 soil_capacity);  //it is a %, not a really Delta_water_table
                                                                  //地下水位深度的变化量

                            d = soil[j].water_table;

                            //地下水位的更新
                            soil[j].water_table =soil[j].water_table+ Delta_water_table;
                            //不饱和层蓄水量的更新
                            soil[j].unsaturated_storage=soil[j].unsaturated_storage+unsat_delta+Delta_water_table*(soil_porosity-
                                                        soil_capacity);

                        }



                        if(soil[j].unsaturated_storage <=0.0)
                            soil[j].unsaturated_storage =0.0;

                        //更新田间持水量下的水量（soilFC）
                        soilFC=soil_capacity*soil[j].water_table; // OS(I don't really understand what soilFC is....
                        //更新不饱和层的土壤含水量
                        d=soil[j].unsaturated_storage/soil[j].water_table;

                        //如果土壤含水量 > 田间持水量
                        if(d > soil_capacity)
                        {


                            extraWater					= soil[j].unsaturated_storage -soilFC;        //额外的蓄水量
                            //	soil[j].unsaturated_storage = soilFC;
                            soil[j].water_table			-= extraWater/(soil_porosity-soil_capacity);
                            soil[j].water_table=MAX(retention,soil[j].water_table);                   //更新地下水位

                            soil[j].unsaturated_storage=MAX(0,soil_capacity*soil[j].water_table);     //更新不饱和层蓄水量
                            d=soil_capacity;                                                          //更新土壤含水量
                            soilFC=soil_capacity*soil[j].water_table;                                 //更新田间持水量下的水量


                        }
                        //如果土壤含水量 < 田间持水量
                        else
                            extraWater = 0.0;

                        //计算不饱和层的水量饱和亏损
                        soil[j].saturation_deficit = soil_porosity*soil[j].water_table -	//***Added by Andriy
                                                     soil[j].unsaturated_storage;
                        if(soil[j].saturation_deficit <= 0.0)
                            soil[j].saturation_deficit = 0.0;
                        else
                            soil[j].saturation_deficit *=1;

                    }

                    //1.2 如果不饱和层可获得的水量 < 不饱和层的土壤水分变化（不饱和层没有足够的水）
                    else //unsat_delta > unsat_available,  no enough water at unsat_ zone
                    {
                        soil[j].unsaturated_storage = a;    //不饱和层的土壤蓄水量 = 在凋萎点下的水量
                        wc = soil[j].unsaturated_storage;

                        //	unsat_delta -= unsat_available; //water will be drawn from saturation zone
                        d = soil[j].water_table;

                        //Delta_water 代表饱和层的土壤水分变化？多减去了一项不饱和层的土壤水分变化
                        Delta_water = -1*(runoff_baseflow[j]	+
                                          q1 - unsat_delta	-
                                          canopy_ptr[j].canopy_transpiration_sat -
                                          //canopy_ptr[j].canopy_uts -
                                          capillaryrise );//////// -

                        // Delta_water < 0 可以说明？
                        if( Delta_water<0)
                        {
                            Delta_water_table = Delta_water/
                                                (soil_porosity	-
                                                 soil[j].unsaturated_storage/soil[j].water_table);  //it is a %, not a really Delta_water_table
                                                                                                    //地下水位深度的变化量
                            d = soil[j].water_table;
                            //地下水位的更新
                            soil[j].water_table += Delta_water_table ;
                            //不饱和层蓄水量的更新
                            soil[j].unsaturated_storage=soil[j].unsaturated_storage*soil[j].water_table/d+unsat_delta;
                        }
                        // Delta_water < 0 可以说明？
                        else
                        {
                            Delta_water_table = Delta_water/
                                                (soil_porosity-
                                                 soil_capacity);  //it is a %, not a really Delta_water_table
                                                                  //地下水位深度的变化量
                            d = soil[j].water_table;
                            //地下水位的更新
                            soil[j].water_table += Delta_water_table;
                            //不饱和层蓄水量的更新
                            soil[j].unsaturated_storage=soil[j].unsaturated_storage+unsat_delta+Delta_water_table*(soil_porosity-
                                                        soil_capacity);

                        }


                        if(soil[j].unsaturated_storage <=0.0)
                            soil[j].unsaturated_storage =0.0;
                        //更新田间持水量下的水量（soilFC）
                        soilFC=soil_capacity*soil[j].water_table;


                        //如果不饱和层蓄水量 > 田间持水量下的水量（soilFC）
                        if(soil[j].unsaturated_storage > soilFC)
                        {

                            d=soil[j].unsaturated_storage/soil[j].water_table;                     //不饱和层的土壤含水量

                            extraWater					= soil[j].unsaturated_storage -soilFC;     //额外的蓄水量
                            //	soil[j].unsaturated_storage = soilFC;
                            soil[j].water_table			-= extraWater/(soil_porosity-soil_capacity);
                            soil[j].water_table=MAX(retention,soil[j].water_table);                 //更新地下水位

                            soil[j].unsaturated_storage=MAX(0,soil_capacity*soil[j].water_table);   //更新不饱和层蓄水量
                            d=soil_capacity;                                                        //更新土壤含水量
                                                                                                    //soilFC没有更新？？

                        }

                        //如果不饱和层蓄水量 < 田间持水量下的水量（soilFC）
                        else
                            extraWater = 0.0;


                        //计算不饱和层的水量饱和亏损
                        soil[j].saturation_deficit = soil_porosity	*		//***Added by Andriy
                                                     soil[j].water_table	-
                                                     soil[j].unsaturated_storage;
                        if(soil[j].saturation_deficit<=0.0)
                            soil[j].saturation_deficit=0.0;
                        else
                            soil[j].saturation_deficit *=1;
                    }   // end of unsat_delta > unsat_available
                }


                // 2. 如果不饱和层的土壤水分变化 > 0,(不饱和层->饱和层），输入 > 输出项（降雨或者毛细管上升多，也可能是ET小）
                else // (unsat_delta>0), input is larger than output, heavy rainfall, or quite small ET, or larger capillaryrise.
                     //这里要注意一下，表明强降雨时候的变量情况
                {

                    // 2.1 如果不饱和层的土壤水分变化 > 不饱和层的水量饱和亏损
                    if(unsat_delta > soil[j].saturation_deficit)
                    {
                        d =  -1*( unsat_delta - soil[j].saturation_deficit);   //这里d是不饱和层水量变化？ 应该是个负值，表示不饱和层有足够的水
                        soil[j].water_table =MAX(retention,d);                 //应该是0 = retention
                        soil[j].unsaturated_storage = 0.0;                     //不饱和层有足够的水为什么这里是零呢
                        soil[j].saturation_deficit=0.0;                        //这意味着没有饱和亏损 !!!!
                                                                               //整个土壤剖面被水填满，此时非饱和储量重置为零

                        //更新不饱和层水量变化， d = p1?
                        d = p1- soil[j].saturation_deficit-retention;			//original

                        //	d = precip - inf_cap - soil[j].saturation_deficit-retention;

                        float  ppp;
                        if (soil[j].water_table>0.01)  //改变了注释
                            ppp=0;
                        //如果地下水位 <=0,快接近地表了
                        else
                            ppp=-1*(soil[j].water_table-d);  //径流的量几乎等于不饱和层水量变化，即净降雨量

                        runoff_total[j] = ppp*1000;          //original ppp ppp;//MAX(0,d);//*(start->iXsize)*(start->iYsize); //this is some unit per area!!!! why?
                        //不懂耶，为什么径流要注释掉呢
                        d = 0;	//OS(18/6/2006): why? 这里为什么赋值0呢

                    }

                    // 2.2  如果不饱和层的土壤水分变化 < 不饱和层的水量饱和亏损
                    else  //(unsat_delta <= soil[j].saturation_deficit)

                    {
                        soil[j].unsaturated_storage += unsat_delta;  //more water added        //更新不饱和层蓄水量
                        unsat_delta					 = q1;                                     //不饱和向饱和层渗透的量


                        //Delta_water 代表饱和层的土壤水分变化
                        Delta_water =	-1*(runoff_baseflow[j]+unsat_delta
                                            - canopy_ptr[j].canopy_transpiration_sat
                                            //- canopy_ptr[j].canopy_uts
                                            - capillaryrise);

                        //2.2.1 Delta_water < 0 可以说明？
                        if( Delta_water<0)  //2006
                        {
                            Delta_water_table = Delta_water/
                                                (soil_porosity	-
                                                 soil[j].unsaturated_storage/soil[j].water_table);  //it is a %, not a really Delta_water_table
                                                                                                    //地下水位深度的变化量
                            d = soil[j].water_table;
                            //地下水位的更新
                            soil[j].water_table += Delta_water_table ;
                            //不饱和层蓄水量的更新
                            soil[j].unsaturated_storage=soil[j].unsaturated_storage*soil[j].water_table/d+unsat_delta;
                        }

                        //2.2.1 Delta_water > 0 可以说明？
                        else
                        {
                            Delta_water_table = Delta_water/
                                                (soil_porosity-
                                                 soil_capacity);  //it is a %, not a really Delta_water_table
                                                                  //地下水位深度的变化量

                            d = soil[j].water_table;
                            //地下水位的更新
                            soil[j].water_table += Delta_water_table;
                            //不饱和层蓄水量的更新
                            soil[j].unsaturated_storage=soil[j].unsaturated_storage+unsat_delta+Delta_water_table*(soil_porosity-
                                                        soil_capacity);

                        }


                        if(soil[j].unsaturated_storage <=0.0)
                            soil[j].unsaturated_storage =0.0;

                        if(soil[j].water_table<=0.01) //同样的修改
                            soilFC=0.0;
                        else
                            //更新田间持水量下的水量（soilFC）
                            soilFC = soil_capacity*soil[j].water_table;

                        //如果不饱和层蓄水量 > 田间持水量下的水量（soilFC）
                        if(soil[j].unsaturated_storage > soilFC)
                        {

                            d=soil[j].unsaturated_storage/soil[j].water_table;

                            extraWater					= soil[j].unsaturated_storage -soilFC;
                            //	soil[j].unsaturated_storage = soilFC;
                            soil[j].water_table			-= extraWater/(soil_porosity-soil_capacity);
                            soil[j].unsaturated_storage=soil_capacity*soil[j].water_table;
                            d=soil_capacity;

                        }
                        else
                            extraWater = 0.0;

                        //soil[j].saturation_deficit = soil[j].soil_porosity*soil[j].water_table -	//***Removed by Andriy
                        //							 soil[j].unsaturated_storage;
                        soil[j].saturation_deficit = soil_porosity*soil[j].water_table -	//***Added by Andriy
                                                     soil[j].unsaturated_storage;
                        if(soil[j].saturation_deficit <=0.0)
                            soil[j].saturation_deficit =0.0;
                        else
                            soil[j].saturation_deficit *=1;

                    }    //end of if(unsat_delta > soil[j].saturation_deficit)
                }   //end of if(unsat_delta<0)


                // 1. 如果地下水位不出露
                if(	soil[j].water_table>0.01)
                    //这里同样的进行修改
                {

                    soil[j].unsaturated_storage =MIN(soil[j].unsaturated_storage, soil_capacity* soil[j].Max_depth_Z);  //更新不饱和层蓄水量
                    soil[j].water_table =MIN( soil[j].water_table, soil[j].Max_depth_Z);                                //更新地下水位

                }
                //2. 如果地下水位出露
                else
                {
                    soil[j].water_table=MAX(retention, soil[j].water_table);
                    soil[j].unsaturated_storage =0;

                }


            } //end of if(soil[j].water_table >= 0.01)
            //结束地下水位不出露的循环


            soil_capillary_rise[j]				= capillaryrise;
            soil_percolation[j]					= q1;

        }//end of if(watershed_ptr ==0 || soil[j].texture <= 0)

    }//end of the for j loop


}
