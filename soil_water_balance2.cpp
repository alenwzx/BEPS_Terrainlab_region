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
    float	retention = 0.00;//0.020;				//retention height is 0cm above the surface-->  ��ˮ�߶ȣ�

    float	soilET,soilET_un ;
    float	a=0.0f, b=0.0f, d =0.0f, q2=0.0f, wc=0.0f;

    float	capillaryrise, precip;			//meters ����ǽ��껹��������ȷ��һ��
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
        runoff_total[j]=runoff_total[j]-runoff_total[j]*0.75;//new   �о�������runoff_total[j]*0.35

        precip	= (float)waterin[j];     //���ﶨ����waterin
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
        //����ʹ����precip����waterin���



        if ((watershed_ptr[j] == 0)||(lc[j] == 0))//MEM         ��������Ԫ�ı�����ֵ�����������Ϊ��������Ԫ�أ�
        {
            runoff_total[j]						= -999.0f;		//***Added by Andriy  �ر���
            runoff_baseflow[j]					= -999.0f;      //                     ����
            unsat_available						= -999.0f;      //                     �����Ͳ�ɻ�ˮ���������Ͳ���ˮ����
            soil_capillary_rise[j]				= -999.0f;		//***Added by Andriy   ëϸ��������
            soil_percolation[j]					= -999.0f;		//***Added by Andriy   ��͸����
            soil[j].water_table					= -999.0f;      //                     ����ˮλ���
        }
        else
        {



            p1 = precip;
            //����ʹ����precip����waterin���






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


        if(soil[j].unsaturated_storage== 0.0||soil[j].water_table== 0.01) //������0������������ֵΪ0.01���ο���������
            d = 0.0;
        else
        {

            // d Ӧ���ǲ����ʹ��ı��Ͷ�
            d = soil[j].unsaturated_storage	/(soil_porosity*soil[j].water_table);	//***Added by Andriy
            /* d is the degree of saturation of the unsaturated zone --> "soil[j].unsaturated_storage/soil[j].water_table" is the "volumetric water content of the unsaturated zone"*/
        }// d --> OS: I think this should be the saturation deficit????


        //1.������ˮλ�ӽ��ر�
        if(soil[j].water_table <= 0.01)
            //water_table is near the surface --> Ajit set this to 0.00....it works for him
            //�����ֵӦ�ÿ��������趨һ�°�
        {
            // MEM: retention is the puddled water!! ˮ�ӵ�ˮ
            //OS(13/9/2006): I added the few lines equation below to account for the situation where precip > inf_capacity
            //Pn������ˮ�������������ˮ���������ᷢ������
            b = retention - (soil[j].water_table);
            Delta_water = (-runoff_baseflow[j] +MAX(0, b)+ soilET - p1);//����ˮλ���ձ仯��
            soil[j].water_table += Delta_water;                         //���µ���ˮλ
            b = retention - (soil[j].water_table);//new                 //���¾���
            soil[j].water_table	 =MAX(retention,soil[j].water_table);  //�������ˮλ
            runoff_total[j]+= (MAX(0, b));//*1000;	//new              //���㾶��
            capillaryrise				= 0.0;
            q1							= 0.0; //no unsaturated flow q1�ǲ����Ͳ��ˮ����
            soil[j].unsaturated_storage	= 0.0;
            //
            soil[j].saturation_deficit	= 0.0;


        } /*the end of soil[j].water_table <= 0.01*/

        //2.������ˮλ����¶
        // soil[j].water_table>0.01
        else
        {
            //һ�� soilFC����������ˮ���µ�ˮ��
            soilFC =(float) (soil[j].water_table * soilindex[textureindext].field_cap);

            // OS(10/6/2006): what does that mean????? According to Ajit the amount of water in mm at field capacity...makes kinda sense to me
            //	 soil[j].unsaturated_storage= soil[j].unsaturated_storage+p1-soilET_un;

            //2.1 �����Ͳ㴢ˮ��>��䴢ˮ��,�ᷢ����͸�������Ͳ�->���Ͳ㣩
            if(soil[j].unsaturated_storage > soilFC)
            //OS: i.e. unsaturated storage is higher than the amount of water at field capacity

            {

                extraWater					= soil[j].unsaturated_storage - soilFC;     //�����ˮ����͸������
                soil[j].unsaturated_storage = soilFC;
                soil[j].water_table			-= extraWater/(soil_porosity-soil_capacity);//����ˮλ���ձ仯��
                soil[j].water_table=MAX(retention,soil[j].water_table);                 //���µ���ˮλ

                soil[j].unsaturated_storage=MAX(0,soil_capacity*soil[j].water_table);   //�����Ͳ���ˮ��
                d=soil_capacity;                                                        //������ˮ��

            }

            //2.2 �����Ͳ㴢ˮ�� < ��䴢ˮ��
            else     //OS: this is the case where unsaturated storage is less than storage at field capacity...
            {

                extraWater					= 0.0;                                  ////�����ˮΪ0

                //���㲻���Ͳ��ˮ�����Ϳ���
                soil[j].saturation_deficit	=	soil_porosity*soil[j].water_table - //***Added by Andriy
                                                soil[j].unsaturated_storage;

                if(soil[j].saturation_deficit	<=0.0)
                    soil[j].saturation_deficit	= 0.0;


                //2.21 ���������ˮ�� > ��ή�㣬���ֲ����Ͳ�ˮ��,q1������͸����
                if(d>soil_point)

                    //	q1=(float)compute_unsat_zone_drainage(textureindext, soil[j], soil_point,soil_capacity,soil_porosity );//�����漰���������ʵ�Ү
                    q1=MAX(0,(float)compute_unsat_zone_drainage(textureindext, soil[j],soil_point,soil_capacity,soil_porosity ));

                //���������ˮ�� < ��ή�㣬��͸����Ϊ0
                else

                    q1=0;

                // make sure the rise is converted into water height
                //2.22 ���������ˮ�� < ����ˮ��������ëϸ������
                if(d<soil_capacity) // OS)10/6/2006): is soil_capacity the field capacity? seems like ....
                {

                    capillaryrise = (float)compute_cap_rise(soil[j], soil_porosity);
                    capillaryrise=MIN((soil_capacity-d)* soil[j].water_table,capillaryrise);

                }
                    //���������ˮ�� > ����ˮ����û��ëϸ������
                else
                {

                    capillaryrise=0;

                }


                // ����a �����ڵ�ή���µ�ˮ��
                a= (float) (soil[j].water_table * soilindex[textureindext].wilting_pt);

                // ��������Ͳ㴢ˮ�� > ��ή���´�ˮ��
                // unsat_available �������Ͳ�ɻ�õ�ˮ��
                if(soil[j].unsaturated_storage >= a)
                    unsat_available = soil[j].unsaturated_storage - a;       //���㲻���Ͳ�ɻ�õ�ˮ��
                else
                    unsat_available = 0.00000f;

                // unsat_delta �������Ͳ������ˮ�ֱ仯
                unsat_delta =	(p1 + capillaryrise)						-
                                (canopy_ptr[j].canopy_transpiration_unsat	+ //unsaturated trees
                                 canopy_ptr[j].litter_evaporation			+
                                 canopy_ptr[j].soil_evaporation				+
                                 q1);                                        //���㲻���Ͳ������ˮ�ֱ仯

                                 //p1�Ǿ���ˮ��q1�ǲ����Ͳ�ˮ������͸����������û�п��ǵر�������Ϊ����ˮλ����¶

                // unsat_delta =	(capillaryrise-q1);


                //1. ��������Ͳ������ˮ�ֱ仯 < 0, ���� < �������Ͳ�->�����Ͳ㣩
                if(unsat_delta<=0.0) // input is lower than output (-), water is taken from sat_ and unsat_ zones
                {
                //	unsat_delta *= -1; // unsat_delta is changed to be positive (+)....MEM: why???


                    //1.1 ��������Ͳ�ɻ�õ�ˮ�� > �����Ͳ������ˮ�ֱ仯��������õ�����ˮ��
                    if(unsat_available > unsat_delta)
                    {
                    //	soil[j].unsaturated_storage -= unsat_delta; //water losses
                    //	unsat_delta = q1;//unsat_delta indicates the change in unsaturation zone


                        // Delta_water �����Ͳ������ˮ�ֱ仯��
                        Delta_water = -1*(runoff_baseflow[j]+q1	-
                                          canopy_ptr[j].canopy_transpiration_sat	-
                                          //canopy_ptr[j].canopy_uts	-
                                          capillaryrise);							//saturated zone

                        // Delta_water < 0 ����˵����
                        if( Delta_water<0)
                        {
                            Delta_water_table = Delta_water/
                                                (soil_porosity	-
                                                 soil[j].unsaturated_storage/soil[j].water_table);  //it is a %, not a really Delta_water_table
                                                                                                    //����ˮλ��ȵı仯��
                            d = soil[j].water_table;

                            //����ˮλ�ĸ���
                            soil[j].water_table += Delta_water_table ;
                            //�����Ͳ���ˮ���ĸ���
                            soil[j].unsaturated_storage=soil[j].unsaturated_storage*soil[j].water_table/d+unsat_delta;
                        }

                        // Delta_water > 0 ����˵����
                        else
                        {
                            Delta_water_table = Delta_water/
                                                (soil_porosity-
                                                 soil_capacity);  //it is a %, not a really Delta_water_table
                                                                  //����ˮλ��ȵı仯��

                            d = soil[j].water_table;

                            //����ˮλ�ĸ���
                            soil[j].water_table =soil[j].water_table+ Delta_water_table;
                            //�����Ͳ���ˮ���ĸ���
                            soil[j].unsaturated_storage=soil[j].unsaturated_storage+unsat_delta+Delta_water_table*(soil_porosity-
                                                        soil_capacity);

                        }



                        if(soil[j].unsaturated_storage <=0.0)
                            soil[j].unsaturated_storage =0.0;

                        //��������ˮ���µ�ˮ����soilFC��
                        soilFC=soil_capacity*soil[j].water_table; // OS(I don't really understand what soilFC is....
                        //���²����Ͳ��������ˮ��
                        d=soil[j].unsaturated_storage/soil[j].water_table;

                        //���������ˮ�� > ����ˮ��
                        if(d > soil_capacity)
                        {


                            extraWater					= soil[j].unsaturated_storage -soilFC;        //�������ˮ��
                            //	soil[j].unsaturated_storage = soilFC;
                            soil[j].water_table			-= extraWater/(soil_porosity-soil_capacity);
                            soil[j].water_table=MAX(retention,soil[j].water_table);                   //���µ���ˮλ

                            soil[j].unsaturated_storage=MAX(0,soil_capacity*soil[j].water_table);     //���²����Ͳ���ˮ��
                            d=soil_capacity;                                                          //����������ˮ��
                            soilFC=soil_capacity*soil[j].water_table;                                 //��������ˮ���µ�ˮ��


                        }
                        //���������ˮ�� < ����ˮ��
                        else
                            extraWater = 0.0;

                        //���㲻���Ͳ��ˮ�����Ϳ���
                        soil[j].saturation_deficit = soil_porosity*soil[j].water_table -	//***Added by Andriy
                                                     soil[j].unsaturated_storage;
                        if(soil[j].saturation_deficit <= 0.0)
                            soil[j].saturation_deficit = 0.0;
                        else
                            soil[j].saturation_deficit *=1;

                    }

                    //1.2 ��������Ͳ�ɻ�õ�ˮ�� < �����Ͳ������ˮ�ֱ仯�������Ͳ�û���㹻��ˮ��
                    else //unsat_delta > unsat_available,  no enough water at unsat_ zone
                    {
                        soil[j].unsaturated_storage = a;    //�����Ͳ��������ˮ�� = �ڵ�ή���µ�ˮ��
                        wc = soil[j].unsaturated_storage;

                        //	unsat_delta -= unsat_available; //water will be drawn from saturation zone
                        d = soil[j].water_table;

                        //Delta_water �����Ͳ������ˮ�ֱ仯�����ȥ��һ����Ͳ������ˮ�ֱ仯
                        Delta_water = -1*(runoff_baseflow[j]	+
                                          q1 - unsat_delta	-
                                          canopy_ptr[j].canopy_transpiration_sat -
                                          //canopy_ptr[j].canopy_uts -
                                          capillaryrise );//////// -

                        // Delta_water < 0 ����˵����
                        if( Delta_water<0)
                        {
                            Delta_water_table = Delta_water/
                                                (soil_porosity	-
                                                 soil[j].unsaturated_storage/soil[j].water_table);  //it is a %, not a really Delta_water_table
                                                                                                    //����ˮλ��ȵı仯��
                            d = soil[j].water_table;
                            //����ˮλ�ĸ���
                            soil[j].water_table += Delta_water_table ;
                            //�����Ͳ���ˮ���ĸ���
                            soil[j].unsaturated_storage=soil[j].unsaturated_storage*soil[j].water_table/d+unsat_delta;
                        }
                        // Delta_water < 0 ����˵����
                        else
                        {
                            Delta_water_table = Delta_water/
                                                (soil_porosity-
                                                 soil_capacity);  //it is a %, not a really Delta_water_table
                                                                  //����ˮλ��ȵı仯��
                            d = soil[j].water_table;
                            //����ˮλ�ĸ���
                            soil[j].water_table += Delta_water_table;
                            //�����Ͳ���ˮ���ĸ���
                            soil[j].unsaturated_storage=soil[j].unsaturated_storage+unsat_delta+Delta_water_table*(soil_porosity-
                                                        soil_capacity);

                        }


                        if(soil[j].unsaturated_storage <=0.0)
                            soil[j].unsaturated_storage =0.0;
                        //��������ˮ���µ�ˮ����soilFC��
                        soilFC=soil_capacity*soil[j].water_table;


                        //��������Ͳ���ˮ�� > ����ˮ���µ�ˮ����soilFC��
                        if(soil[j].unsaturated_storage > soilFC)
                        {

                            d=soil[j].unsaturated_storage/soil[j].water_table;                     //�����Ͳ��������ˮ��

                            extraWater					= soil[j].unsaturated_storage -soilFC;     //�������ˮ��
                            //	soil[j].unsaturated_storage = soilFC;
                            soil[j].water_table			-= extraWater/(soil_porosity-soil_capacity);
                            soil[j].water_table=MAX(retention,soil[j].water_table);                 //���µ���ˮλ

                            soil[j].unsaturated_storage=MAX(0,soil_capacity*soil[j].water_table);   //���²����Ͳ���ˮ��
                            d=soil_capacity;                                                        //����������ˮ��
                                                                                                    //soilFCû�и��£���

                        }

                        //��������Ͳ���ˮ�� < ����ˮ���µ�ˮ����soilFC��
                        else
                            extraWater = 0.0;


                        //���㲻���Ͳ��ˮ�����Ϳ���
                        soil[j].saturation_deficit = soil_porosity	*		//***Added by Andriy
                                                     soil[j].water_table	-
                                                     soil[j].unsaturated_storage;
                        if(soil[j].saturation_deficit<=0.0)
                            soil[j].saturation_deficit=0.0;
                        else
                            soil[j].saturation_deficit *=1;
                    }   // end of unsat_delta > unsat_available
                }


                // 2. ��������Ͳ������ˮ�ֱ仯 > 0,(�����Ͳ�->���Ͳ㣩������ > �����������ëϸ�������࣬Ҳ������ETС��
                else // (unsat_delta>0), input is larger than output, heavy rainfall, or quite small ET, or larger capillaryrise.
                     //����Ҫע��һ�£�����ǿ����ʱ��ı������
                {

                    // 2.1 ��������Ͳ������ˮ�ֱ仯 > �����Ͳ��ˮ�����Ϳ���
                    if(unsat_delta > soil[j].saturation_deficit)
                    {
                        d =  -1*( unsat_delta - soil[j].saturation_deficit);   //����d�ǲ����Ͳ�ˮ���仯�� Ӧ���Ǹ���ֵ����ʾ�����Ͳ����㹻��ˮ
                        soil[j].water_table =MAX(retention,d);                 //Ӧ����0 = retention
                        soil[j].unsaturated_storage = 0.0;                     //�����Ͳ����㹻��ˮΪʲô����������
                        soil[j].saturation_deficit=0.0;                        //����ζ��û�б��Ϳ��� !!!!
                                                                               //�����������汻ˮ��������ʱ�Ǳ��ʹ�������Ϊ��

                        //���²����Ͳ�ˮ���仯�� d = p1?
                        d = p1- soil[j].saturation_deficit-retention;			//original

                        //	d = precip - inf_cap - soil[j].saturation_deficit-retention;

                        float  ppp;
                        if (soil[j].water_table>0.01)  //�ı���ע��
                            ppp=0;
                        //�������ˮλ <=0,��ӽ��ر���
                        else
                            ppp=-1*(soil[j].water_table-d);  //���������������ڲ����Ͳ�ˮ���仯������������

                        runoff_total[j] = ppp*1000;          //original ppp ppp;//MAX(0,d);//*(start->iXsize)*(start->iYsize); //this is some unit per area!!!! why?
                        //����Ү��Ϊʲô����Ҫע�͵���
                        d = 0;	//OS(18/6/2006): why? ����Ϊʲô��ֵ0��

                    }

                    // 2.2  ��������Ͳ������ˮ�ֱ仯 < �����Ͳ��ˮ�����Ϳ���
                    else  //(unsat_delta <= soil[j].saturation_deficit)

                    {
                        soil[j].unsaturated_storage += unsat_delta;  //more water added        //���²����Ͳ���ˮ��
                        unsat_delta					 = q1;                                     //�������򱥺Ͳ���͸����


                        //Delta_water �����Ͳ������ˮ�ֱ仯
                        Delta_water =	-1*(runoff_baseflow[j]+unsat_delta
                                            - canopy_ptr[j].canopy_transpiration_sat
                                            //- canopy_ptr[j].canopy_uts
                                            - capillaryrise);

                        //2.2.1 Delta_water < 0 ����˵����
                        if( Delta_water<0)  //2006
                        {
                            Delta_water_table = Delta_water/
                                                (soil_porosity	-
                                                 soil[j].unsaturated_storage/soil[j].water_table);  //it is a %, not a really Delta_water_table
                                                                                                    //����ˮλ��ȵı仯��
                            d = soil[j].water_table;
                            //����ˮλ�ĸ���
                            soil[j].water_table += Delta_water_table ;
                            //�����Ͳ���ˮ���ĸ���
                            soil[j].unsaturated_storage=soil[j].unsaturated_storage*soil[j].water_table/d+unsat_delta;
                        }

                        //2.2.1 Delta_water > 0 ����˵����
                        else
                        {
                            Delta_water_table = Delta_water/
                                                (soil_porosity-
                                                 soil_capacity);  //it is a %, not a really Delta_water_table
                                                                  //����ˮλ��ȵı仯��

                            d = soil[j].water_table;
                            //����ˮλ�ĸ���
                            soil[j].water_table += Delta_water_table;
                            //�����Ͳ���ˮ���ĸ���
                            soil[j].unsaturated_storage=soil[j].unsaturated_storage+unsat_delta+Delta_water_table*(soil_porosity-
                                                        soil_capacity);

                        }


                        if(soil[j].unsaturated_storage <=0.0)
                            soil[j].unsaturated_storage =0.0;

                        if(soil[j].water_table<=0.01) //ͬ�����޸�
                            soilFC=0.0;
                        else
                            //��������ˮ���µ�ˮ����soilFC��
                            soilFC = soil_capacity*soil[j].water_table;

                        //��������Ͳ���ˮ�� > ����ˮ���µ�ˮ����soilFC��
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


                // 1. �������ˮλ����¶
                if(	soil[j].water_table>0.01)
                    //����ͬ���Ľ����޸�
                {

                    soil[j].unsaturated_storage =MIN(soil[j].unsaturated_storage, soil_capacity* soil[j].Max_depth_Z);  //���²����Ͳ���ˮ��
                    soil[j].water_table =MIN( soil[j].water_table, soil[j].Max_depth_Z);                                //���µ���ˮλ

                }
                //2. �������ˮλ��¶
                else
                {
                    soil[j].water_table=MAX(retention, soil[j].water_table);
                    soil[j].unsaturated_storage =0;

                }


            } //end of if(soil[j].water_table >= 0.01)
            //��������ˮλ����¶��ѭ��


            soil_capillary_rise[j]				= capillaryrise;
            soil_percolation[j]					= q1;

        }//end of if(watershed_ptr ==0 || soil[j].texture <= 0)

    }//end of the for j loop


}
