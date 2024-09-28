/****************************************************************************

	NNAME: soilwater_balance.cpp	method-->1


*****************************************************************************/

#include "stdafx.h"
#include "BepsHydrScience.h"
#include <math.h>


void soil_water_balance1(pubv* start,float* runoff_baseflow,float * waterin,float* runoff_total,unsigned char* soil_texture,
						Soil_index_t* soilindex,Soil_t* soil,float* soil_capillary_rise,float* soil_percolation,
						Canopy_t* canopy_ptr,unsigned char* lc, unsigned char* watershed_ptr,
						int iDay,double dDaylength,int iTestCurrentLine)



{
	int		counter=0;
//	int temp;
	float	p1, q1, soilFC, unsattemp = 0.0f;
	float	retention = 0.00;//0.020;
	float	soilET,soilET_un ;
	float	a=0.0f, b=0.0f, d =0.0f, q2=0.0f, wc=0.0f;
	float	capillaryrise, precip;			//meters
	float	Delta_water			= 0.0;
	float	Delta_water_table	= 0.0;		//meters
	float	porosity			= 0.0;
	float	unsat_available		= 0.0;
	float	unsat_delta			= 0.0;
	float	depth=0.0f, c =0.0f, extraWater = 0.0f;
	int		j;//,k;
	float   soil_porosity,soil_capacity,soil_point;	//2005-Apr-28
    short   textureindext;
	 int kkk;
	float Ksat_z, tp, air_entry, sorptivity, inf_cap, wetting_suction; // saturated hydraulic conductivity with depth, time to ponding
	float runoff;

     for(j=0;j<start->npixels;j++)
	{

	if(soil_texture[j]>0 && soil_texture[j]<=120){
    textureindext=soil_texture[j]/10-1;
	}
    else textureindext=1;


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

        float epsilon= runoff_total[j];//new


		precip	= (float)waterin[j];


		soil_porosity	 =  (float)	soilindex[textureindext].porosity;
     	soil_capacity    =(float)soilindex[textureindext].field_cap;
		soil_point    =(float)soilindex[textureindext].wilting_pt;

		/*convert precipitation value into unit mm */
//****** infiltration capacity after Beckers et al. 2004

	Ksat_z = soil[j].saturated_Kv * exp( -1.0 * (soil[j].water_table * soil[j].K0_decay_m ));

	air_entry = soil[j].saturation_suction/(pow((soil[j].unsaturated_storage/(soil[j].water_table*soil_porosity)),-soil[j].K0_decay_m));


	wetting_suction = ((2 + 3*soil[j].soil_b) / (1 + 3*soil[j].soil_b)) * (air_entry/2); //Beckers et al. (2004)


	inf_cap = Ksat_z * (1 + (((soil_porosity - (soil[j].unsaturated_storage/soil[j].water_table)) * wetting_suction) / (precip)));//OS(12/9/2006) I used half the total daily precipitation here instead of cumulative infilitration which is calculated when using the Beckers et al. (2004) approach on a daily time-step...


		if (watershed_ptr[j] == 0)//MEM
		{runoff_total[j]						= -999;}
		else if(lc[j] == 0)
		{runoff_total[j]						= 0;}

		if ((watershed_ptr[j] == 0)||(lc[j] == 0))//MEM
		{
					//***Added by Andriy
			runoff_baseflow[j]					= -999.0f;
			unsat_available						= -999.0f;
			soil_capillary_rise[j]				= -999.0f;
			soil_percolation[j]					= -999.0f;
		//	soil[j].water_table					= -999.0f;
		}
		else
		{




			p1 = precip;



			}
soilET		=	(canopy_ptr[j].canopy_transpiration_unsat) +
							(canopy_ptr[j].canopy_transpiration_sat)   +
							(canopy_ptr[j].litter_evaporation)         +
							(canopy_ptr[j].moss_transpiration)         +
							(canopy_ptr[j].soil_evaporation);


			/*soilET is the water consumed from soil*/

              soilET_un =	(canopy_ptr[j].canopy_transpiration_unsat) +
							(canopy_ptr[j].litter_evaporation)         +
							(canopy_ptr[j].moss_transpiration)         +
							(canopy_ptr[j].soil_evaporation);

            soilET                                   /= 1000.0;
			soilET_un                                /= 1000.0;
			canopy_ptr[j].canopy_evaporation         /= 1000.0;
			canopy_ptr[j].canopy_transpiration_unsat /= 1000.0;
			canopy_ptr[j].canopy_transpiration_sat   /= 1000.0;
			canopy_ptr[j].litter_evaporation         /= 1000.0;
			canopy_ptr[j].moss_transpiration         /= 1000.0;
			canopy_ptr[j].soil_evaporation           /= 1000.0;
		//	canopy_ptr[j].canopy_UT		             /= 1000.0;
		//	canopy_ptr[j].canopy_uts		         /= 1000.0;


					if(soil[j].unsaturated_storage== 0.0||soil[j].water_table== 0.0)
						d = 0.0;
					else{

				d = soil[j].unsaturated_storage	/(soil_porosity*soil[j].water_table);
			/* d is the degree of saturation of the unsaturated zone --> "soil[j].unsaturated_storage/soil[j].water_table" is the "volumetric water content of the unsaturated zone"*/
			}

  	float ee,ff,gg;

	if(soil[j].water_table <= 0.00  ) //water_table is near the surface
			{

				Delta_water = (-runoff_baseflow[j] -soil[j].pondwater+ soilET - p1);
				if ((Delta_water>soil[j].pondwater)&& (Delta_water>0))
				{ee=Delta_water-soil[j].pondwater;
				soil[j].pondwater=0;
				soil[j].water_table+=ee;
				}
	 			else if ((Delta_water<soil[j].pondwater) && (Delta_water>0) )
				{
				ff=soil[j].pondwater-Delta_water;
				soil[j].pondwater=Delta_water;//ff;
				soil[j].pondwater=MAX(0,Delta_water/*soil[j].pondwater*/);
				soil[j].water_table=0;
				}
				else if ((Delta_water<0) )
				{

				soil[j].pondwater=-1*Delta_water;
				soil[j].water_table=0;
				}



				capillaryrise				= 0.0;
				q1							= 0.0;
				soil[j].unsaturated_storage	= 0.0;
				soil[j].saturation_deficit	= 0.0;


			} /*the end of soil[j].water_table <= 0.01*/
	else   // soil[j].water_table>0.01
			{



			  soilFC =(float) (soil[j].water_table * soilindex[textureindext].field_cap); // OS(10/6/2006): what does that mean????? According to Ajit the amount of water in mm at field capacity...makes kinda sense to me

				//	 soil[j].unsaturated_storage= soil[j].unsaturated_storage+p1-soilET_un;

			  if(soil[j].unsaturated_storage > soilFC) { //OS: i.e. unsaturated storage is higher than amount of water at field capacity

					extraWater					= soil[j].unsaturated_storage - soilFC;
					soil[j].unsaturated_storage = soilFC;
					soil[j].water_table			-= extraWater/(soil_porosity-soil_capacity);
			        soil[j].water_table=MAX(retention,soil[j].water_table);

					soil[j].unsaturated_storage=MAX(0,soil_capacity*soil[j].water_table);
			        d=soil_capacity;

				} else {

					extraWater					= 0.0;

					soil[j].saturation_deficit	=	soil_porosity*soil[j].water_table -
												soil[j].unsaturated_storage;

					if(soil[j].saturation_deficit	<=0.0) 	soil[j].saturation_deficit	= 0.0;



					if(d>soil_point)


		         	q1=MAX(0,(float)compute_unsat_zone_drainage(textureindext, soil[j],soil_point,soil_capacity,soil_porosity ));
					else

						q1=0;



			if(d<soil_capacity){

				capillaryrise = (float)compute_cap_rise(soil[j], soil_porosity);
                capillaryrise=MIN((soil_capacity-d)* soil[j].water_table,capillaryrise);

			} else {

                capillaryrise=0;

			}


				a= (float) (soil[j].water_table * soilindex[textureindext].wilting_pt);

				if(soil[j].unsaturated_storage >= a)
					unsat_available = soil[j].unsaturated_storage - a;
				else
					unsat_available = 0.00000f;


			unsat_delta =	(p1 + capillaryrise+soil[j].pondwater /*epsilon*/)						-
								(canopy_ptr[j].canopy_transpiration_unsat	+ //unsaturated trees
								 canopy_ptr[j].litter_evaporation			+
								 canopy_ptr[j].soil_evaporation				+
																 q1);

soil[j].pondwater=0;
              // unsat_delta =	(capillaryrise-q1);

				if(unsat_delta<=0.0) // input is lower than output (-), water is taken from sat_ and unsat_ zones
				{


					if(unsat_available > unsat_delta)   //more soil water avaiable
					{


						Delta_water = -1*(runoff_baseflow[j]+q1	-
										canopy_ptr[j].canopy_transpiration_sat	-
								 		//canopy_ptr[j].canopy_uts	-
										capillaryrise);							//saturated zone

						if( Delta_water<0){
						Delta_water_table = Delta_water/
												(soil_porosity	-
												soil[j].unsaturated_storage/soil[j].water_table);
						d = soil[j].water_table;

				  //here the watertable is updated....

						soil[j].water_table += Delta_water_table ;

					soil[j].unsaturated_storage=soil[j].unsaturated_storage*soil[j].water_table/d+unsat_delta;
						}
						else{
					  Delta_water_table = Delta_water/
												(soil_porosity-
												soil_capacity);

						d = soil[j].water_table;

					soil[j].water_table =soil[j].water_table+ Delta_water_table;

					soil[j].unsaturated_storage=soil[j].unsaturated_storage+unsat_delta+Delta_water_table*(soil_porosity-
												soil_capacity);

						}



						if(soil[j].unsaturated_storage <=0.0)
							soil[j].unsaturated_storage =0.0;

						soilFC=soil_capacity*soil[j].water_table;





	 d=soil[j].unsaturated_storage/soil[j].water_table;

						if(d > soil_capacity)
						{

					extraWater					= soil[j].unsaturated_storage -soilFC;
				//	soil[j].unsaturated_storage = soilFC;
					soil[j].water_table			-= extraWater/(soil_porosity-soil_capacity);
			        soil[j].water_table=MAX(retention,soil[j].water_table);

					soil[j].unsaturated_storage=MAX(0,soil_capacity*soil[j].water_table);
			        d=soil_capacity;



	soilFC=soil_capacity*soil[j].water_table;


						}
						else
							extraWater = 0.0;


						soil[j].saturation_deficit = soil_porosity*soil[j].water_table -
													 soil[j].unsaturated_storage;
						if(soil[j].saturation_deficit <= 0.0)
							soil[j].saturation_deficit = 0.0;
						else
							soil[j].saturation_deficit *=1;

					}
					else //unsat_delta > unsat_available,  no enough water at unsat_ zone
					{
						soil[j].unsaturated_storage = a;
						wc = soil[j].unsaturated_storage;

					//	unsat_delta -= unsat_available; //water will be drawn from saturation zone
						d = soil[j].water_table;

						Delta_water = -1*(runoff_baseflow[j]	+
										q1 - unsat_delta	-
										canopy_ptr[j].canopy_transpiration_sat -
										//canopy_ptr[j].canopy_uts -
										capillaryrise );//////// -


						if( Delta_water<0){
						Delta_water_table = Delta_water/
												(soil_porosity	-
												soil[j].unsaturated_storage/soil[j].water_table);  //it is a %, not a really Delta_water_table
						d = soil[j].water_table;

						soil[j].water_table += Delta_water_table ;

					soil[j].unsaturated_storage=soil[j].unsaturated_storage*soil[j].water_table/d+unsat_delta;
						}
						else{
					  Delta_water_table = Delta_water/
												(soil_porosity-
												soil_capacity);  //it is a %, not a really Delta_water_table

						d = soil[j].water_table;

					soil[j].water_table += Delta_water_table;

					soil[j].unsaturated_storage=soil[j].unsaturated_storage+unsat_delta+Delta_water_table*(soil_porosity-
												soil_capacity);

						}


                        if(soil[j].unsaturated_storage <=0.0)
							soil[j].unsaturated_storage =0.0;

						soilFC=soil_capacity*soil[j].water_table;



						if(soil[j].unsaturated_storage > soilFC)
						{

					  d=soil[j].unsaturated_storage/soil[j].water_table;

					extraWater					= soil[j].unsaturated_storage -soilFC;
				//	soil[j].unsaturated_storage = soilFC;
					soil[j].water_table			-= extraWater/(soil_porosity-soil_capacity);
			        soil[j].water_table=MAX(retention,soil[j].water_table);

					soil[j].unsaturated_storage=MAX(0,soil_capacity*soil[j].water_table);
			        d=soil_capacity;

						}
						else
							extraWater = 0.0;



						soil[j].saturation_deficit = soil_porosity	*		//***Added by Andriy
													 soil[j].water_table	-
													 soil[j].unsaturated_storage;
						if(soil[j].saturation_deficit<=0.0)
							soil[j].saturation_deficit=0.0;
						else
							soil[j].saturation_deficit *=1;
					}   // end of unsat_delta > unsat_available
				}
				else // (unsat_delta>0), input is larger than output, heavy rainfall, or quite small ET, or larger capillaryrise.
				{


					if(unsat_delta > soil[j].saturation_deficit)
					{
						d =  -1*( unsat_delta - soil[j].saturation_deficit);
						soil[j].pondwater= (retention -d);
						soil[j].water_table =MAX(retention,d);
						soil[j].unsaturated_storage = 0.0;

						soil[j].saturation_deficit=0.0;
						//this means that there's no saturation deficit !!!!

						d = p1- soil[j].saturation_deficit-retention;			//original


						d = 0;

					}

					else  //(unsat_delta <= soil[j].saturation_deficit)

					{


						soil[j].unsaturated_storage += unsat_delta;  //more water added
						unsat_delta					 = q1;

						Delta_water =	-1*(runoff_baseflow[j]+unsat_delta
										- canopy_ptr[j].canopy_transpiration_sat
										//- canopy_ptr[j].canopy_uts
										- capillaryrise);

						if( Delta_water<0){ //2006
						Delta_water_table = Delta_water/
												(soil_porosity	-
												soil[j].unsaturated_storage/soil[j].water_table);  //it is a %, not a really Delta_water_table
						d = soil[j].water_table;

						soil[j].water_table += Delta_water_table ;

					soil[j].unsaturated_storage=soil[j].unsaturated_storage*soil[j].water_table/d+unsat_delta;
						}
						else{
					  Delta_water_table = Delta_water/
												(soil_porosity-
												soil_capacity);  //it is a %, not a really Delta_water_table

						d = soil[j].water_table;

					soil[j].water_table += Delta_water_table;

					soil[j].unsaturated_storage=soil[j].unsaturated_storage+unsat_delta+Delta_water_table*(soil_porosity-
												soil_capacity);

						}


						if(soil[j].unsaturated_storage <=0.0)
							soil[j].unsaturated_storage =0.0;

						if(soil[j].water_table<=0.0)
							soilFC=0.0;
						else
							soilFC = soil_capacity*soil[j].water_table;



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


						soil[j].saturation_deficit = soil_porosity*soil[j].water_table -	//***Added by Andriy
													 soil[j].unsaturated_storage;
						if(soil[j].saturation_deficit <=0.0)
						   soil[j].saturation_deficit =0.0;
						else
							soil[j].saturation_deficit *=1;

					}    //end of if(unsat_delta > soil[j].saturation_deficit)
				}   //end of if(unsat_delta<0)

				if(	soil[j].water_table>0){

                soil[j].unsaturated_storage =MIN(soil[j].unsaturated_storage, soil_capacity* soil[j].Max_depth_Z);
               	soil[j].water_table =MIN( soil[j].water_table, soil[j].Max_depth_Z);

				}
				 else{
				soil[j].water_table=MAX(retention, soil[j].water_table);
				soil[j].unsaturated_storage =0;

				 }


			} //end of if(soil[j].water_table >= 0.01)


			soil_capillary_rise[j]				= capillaryrise;
			soil_percolation[j]					= q1;

	}//end of if(watershed_ptr ==0 || soil[j].texture <= 0)

	}//end of the for j loop

}
