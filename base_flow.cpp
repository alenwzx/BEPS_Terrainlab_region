#include "stdafx.h"
#include "BepsHydrScience.h"
#include "math.h"

//void base_flow(pubv *myseed,fname *myfilename, char *pathName, int iDay)						//***removed by Andriy***
void base_flow(pubv* myseed,int iDay,int iLine,Soil_t* soil,unsigned char* watershed,float* baseflow,float* total_inflow,
			   float* total_outflow,float* Array_Ele,int* Array_Label,unsigned char* soil_texture,Soil_index_t* soilindex,Soil_t* Soil_Array_3r)	//***added by Andriy***
{
	//local variable definition
	int iX, iY;						//for maximum dimensions of current image. k is a for loop variable
	int iOutRoute					= 0;		//counter of number of drainage pixels
	int iInRoute					= 0, iCount;//counter of number of the drainage pixels
	int iNumberDonePixel			= 0;		//counter of pixels have been processed
	double TotalOutflow				= 0;		//total number of drainage
	double TotalInflow				= 0;		//total number of subsurface inflow
	double dDX2 = 1.0/(1.414*(float)(myseed->iXsize));	//contour length of diangnal neighbors. Assume
	double dDX1 = 1.0/(float)(myseed->iXsize);			//contour length of cardinal neighbors
	double dSUMDrainage				= 0;		//variable for sum of drainage of neighbor pixels
	double Baseflow;							//pointer points to an array of double type

	double Tz[9];								//pointer will point to 9 element array. K value at depth of z
	double TAB=0;									//pointer will point to 9 elment array . Gradient between two neighbour pixels
    double  bid=0;
	Soil_t	current_soil[9];					//current 9 pixels of soil data

	int i,j,i1;
    double Inf[10],Outf[10];
	short   textureindext;

	//initialization:
	iX	= myseed->nlines;
	iY	= myseed->npixels;
//_______________
	     for(j=0;j<iY;j++)
	{

	if(soil_texture[j]>0 && soil_texture[j]<=120){
    textureindext=soil_texture[j]/10-1;
	}
    else textureindext=2;}
//_______________




	//determine whether dealing with 1st, 2nd or 3rd line of 3-line Array_Ele array
	if (iLine == 0)
		i = 0;
	else if (iLine == iX-1)
		i = 2;
	else
		i = 1;





 	for(j=0;j<iY;j++)
	{


	for(i1=0;i1<=9;i1++){
Inf[i1]=0;Outf[i1]=0;
	}


		TotalInflow	 = 0.0;
		TotalOutflow = 0.0;


		//if((Array_Ele[i*iY+j]>=9999.0f)||(Array_Label[i*iY+j]==9999)) //***Removed by Andriy
		if ((Array_Ele[i*iY+j]>=9999.0f)||(Array_Label[i*iY+j]==9999)||(watershed[j]==0))//***Added by Andriy//�����ų��˱�����Ԫ�ļ���
		{
			//Baseflow		= 0.0;		//***Removed by Andriy  //
			Baseflow		= -777.0;	//***Added by Andriy   //
			TotalInflow		= -999.0;	//***Added by Andriy
			TotalOutflow	= -999.0;	//***Added by Andriy
		}

		else
		{
			for (iCount = 0; iCount<9; iCount++)
			{
				//current_soil[iCount].soil_ID				= 0;
				//current_soil[iCount].texture				= 0;
				current_soil[iCount].K0_decay_m				= 0;
				//current_soil[iCount].soil_porosity		= 0;
				current_soil[iCount].saturation_suction		= 0;
				current_soil[iCount].saturated_Ks			= 0;

				current_soil[iCount].saturation_deficit		= 0;
				current_soil[iCount].unsaturated_storage	= 0;
				current_soil[iCount].water_table			= 0;
				current_soil[iCount].Max_depth_Z			= 0;
				Tz[iCount]									= 0;
			}

			//***Modified by Andriy:
			ReadInSoil(Soil_Array_3r,current_soil,iLine,j,myseed);



			//***Modified by Andriy:


	if (Array_Ele[i*iY+j] < 0) {
//if (Array_Ele[i*iY+j] < 0)
				Current_Tz(iLine,j,current_soil,soil, Tz, myseed);

				Tz[0] =Tz[4];
				Tz[1] = Tz[4];
				Tz[2] = Tz[4];
				Tz[3] = Tz[4];
				Tz[5] = Tz[4];
				Tz[6] = Tz[4];
				Tz[7] = Tz[4];
				Tz[8] = Tz[4];




			} else

				Current_Tz(iLine,j,current_soil, soil,Tz, myseed);




		//	}

			if(iLine==0)
			{
				if(j==0)
				{


 				if( Array_Ele[i*iY+j]>=9999.0)
					{
						TotalInflow  += 0;
						TotalOutflow += 0;
					}
					else
					{
						if(Array_Ele[i*iY+(j+1)]>=9999.0) bid=0;                //5
						else bid=1.0;
						if(Array_Ele[i*iY+(j+1)]<Array_Ele[i*iY+j])
						{
							TAB =(Array_Ele[i*iY+j]-Array_Ele[i*iY+(j+1)])*dDX1; //###
						    Outf[5] =  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
							iOutRoute++;
						}
						else
                                {TAB=(Array_Ele[i*iY+(j+1)]-Array_Ele[i*iY+j])*dDX1;
                                    //	TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[5]*bid;
                            //if(Array_Label[i*iY+(j+1)]!=9999)                    //ע��
                                Inf[5]= 0.5*(myseed->iXsize)*TAB*Tz[5]*bid;
                                iInRoute++;
                                }


                        if(Array_Ele[(i+1)*iY+(j+1)]>=9999.0) bid=0;           //8
                        else bid=1.0;
						if(Array_Ele[(i+1)*iY+(j+1)]<Array_Ele[i*iY+j])
						{
							TAB=(Array_Ele[i*iY+j]-Array_Ele[(i+1)*iY+(j+1)])*dDX2;//###
						//	TotalOutflow += 0.354*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
                            Outf[8] = 0.398*(myseed->iXsize)*TAB*Tz[4]*bid;
							iOutRoute++;
						}
						else
						{
								TAB=(Array_Ele[(i+1)*iY+(j+1)]-Array_Ele[i*iY+j])*dDX2;
								//TotalInflow += 0.354*(myseed->iXsize)*TAB*Tz[8]*bid;
                           //if(Array_Label[(i+1)*iY+(j+1)]!=9999)                    //ע��
								Inf[8]= 0.398*(myseed->iXsize)*TAB*Tz[8]*bid;
                                iInRoute++;
						}

                         if(Array_Ele[(i+1)*iY+j]>=9999.0) bid=0;                //7
						 else bid=1.0;
						if(Array_Ele[(i+1)*iY+j]<Array_Ele[i*iY+j])
						{
							TAB=(Array_Ele[i*iY+j]-Array_Ele[(i+1)*iY+j])*dDX1;//### earlier dDX2
							//TotalOutflow += 0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
                            Outf[7]=0.5*(myseed->iXsize)*TAB*Tz[4]*bid;
							iOutRoute++;
						}
						else
						{
								TAB=(Array_Ele[(i+1)*iY+j]-Array_Ele[i*iY+j])*dDX1;//### earlier dDX2
								//TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[7]*bid;
                            //if(Array_Label[(i+1)*iY+j]!=9999)                              //��������������¼ӵġ�HJ
								Inf[7]= 0.5*(myseed->iXsize)*TAB*Tz[7]*bid;
								iInRoute++;
////finihed***********
						}
					}//end of if(elevation >= 9999) block
				}//end of if(j==0) block

				if(j+1==iY)
				{
// MEM added this instead of the line just below...
// to improve the computational effeciency.

 			if( Array_Ele[i*iY+j]>=9999.0)

							{
						TotalInflow += 0;
						TotalOutflow += 0;
					}
					else
					{

						if(Array_Ele[i*iY+(j-1)]>=9999.0) bid=0;                     //3
						 else bid=1.0;
						if(Array_Ele[i*iY+(j-1)]<Array_Ele[i*iY+j])
						{
							TAB =(Array_Ele[i*iY+j]-Array_Ele[i*iY+(j-1)])*dDX1;//###
						//	TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
                            Outf[3]=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
							iOutRoute++;
						}
						else
						{
								TAB=(Array_Ele[i*iY+(j-1)]-Array_Ele[i*iY+j])*dDX1;
								//TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[3]*bid;
                            //if(Array_Label[i*iY+(j-1)]!=9999)                //�¼ӵ�����
                                Inf[3]= 0.5*(myseed->iXsize)*TAB*Tz[3]*bid;
                                iInRoute++;
						}


						if(Array_Ele[(i+1)*iY+(j-1)]>=9999.0) bid=0;         //6
						 else bid=1.0;
						if(Array_Ele[(i+1)*iY+(j-1)]<Array_Ele[i*iY+j])//###
						{
							TAB =(Array_Ele[i*iY+j]-Array_Ele[(i+1)*iY+(j-1)])*dDX2;
						//	TotalOutflow +=  0.354*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
                            Outf[6]=  0.398*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
							iOutRoute++;
						}
						else
						{
								TAB=(Array_Ele[(i+1)*iY+(j-1)]-Array_Ele[i*iY+j])*dDX2;
							//	TotalInflow += 0.354*(myseed->iXsize)*TAB*Tz[6]*bid;
                            //if(Array_Label[(i+1)*iY+(j-1)]!=9999)               //�¼ӵ�����
                                Inf[6]= 0.398*(myseed->iXsize)*TAB*Tz[6]*bid;
								iInRoute++;
						}


                       if(Array_Ele[(i+1)*iY+j]>=9999.0) bid=0;       //7
						 else bid=1.0;
						if(Array_Ele[(i+1)*iY+j]<Array_Ele[i*iY+j])
						{
							TAB =(Array_Ele[i*iY+j]-Array_Ele[(i+1)*iY+j])*dDX1;//### earlier dDX2
						//	TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
							Outf[7]=0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
							iOutRoute++;
						}
						else
						{
								TAB=(Array_Ele[(i+1)*iY+j]-Array_Ele[i*iY+j])*dDX1;//### earlier dDX2
							//	TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[7]*bid;
                            //if(Array_Label[(i+1)*iY+j]!=9999)               //�¼ӵ�����
								Inf[7]= 0.5*(myseed->iXsize)*TAB*Tz[7]*bid;
								iInRoute++;
//
						}
					}//end of if(elevation >= 9999) block
				}//end of if(j+1 == iY)

				if((j>0)&&(j+1<iY))
				{
// MEM added this instead of the line just below...
// to improve the computational effeciency.

 			if( Array_Ele[i*iY+j]>=9999.0)
								{
						TotalInflow  += 0;
						TotalOutflow += 0;
					}
					else
					{
                       if(Array_Ele[i*iY+(j-1)]>=9999.0) bid=0;     //3
						 else bid=1.0;

						if(Array_Ele[i*iY+(j-1)]<Array_Ele[i*iY+j])
						{
							TAB =(Array_Ele[i*iY+j]-Array_Ele[i*iY+(j-1)])*dDX1;//###
						//	TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
                            Outf[3]=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
							iOutRoute++;
						}
						else
						{
							   TAB=(Array_Ele[i*iY+(j-1)]-Array_Ele[i*iY+j])*dDX1;
								//TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[3]*bid;
                            //if(Array_Label[i*iY+(j-1)]!=9999)               //�¼ӵ�����
                               Inf[3]= 0.5*(myseed->iXsize)*TAB*Tz[3]*bid;
							   iInRoute++;
						}


                         if(Array_Ele[(i+1)*iY+(j-1)]>=9999.0) bid=0;      //6
						 else bid=1.0;

						if(Array_Ele[(i+1)*iY+(j-1)]<Array_Ele[i*iY+j])
						{
							TAB =(Array_Ele[i*iY+j]-Array_Ele[(i+1)*iY+(j-1)])*dDX2;//###
						//	TotalOutflow +=  0.354*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
                            Outf[6]=  0.398*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
							iOutRoute++;
						}
						else
						{
								TAB=(Array_Ele[(i+1)*iY+(j-1)]-Array_Ele[i*iY+j])*dDX2;
							//	TotalInflow += 0.354*(myseed->iXsize)*TAB*Tz[6]*bid;
							//if(Array_Label[(i+1)*iY+(j-1)]!=9999)               //�¼ӵ�����
								Inf[6]=0.398*(myseed->iXsize)*TAB*Tz[6]*bid;
								iInRoute++;
							}


                       if(Array_Ele[(i+1)*iY+j]>=9999.0) bid=0;        //7
						 else bid=1.0;
						if(Array_Ele[(i+1)*iY+j]<Array_Ele[i*iY+j])
						{
							TAB =(Array_Ele[i*iY+j]-Array_Ele[(i+1)*iY+j])*dDX1;//### earlier dDX2
							//TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
                            Outf[7]=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
							iOutRoute++;
						}
						else
						{
								TAB=(Array_Ele[(i+1)*iY+j]-Array_Ele[i*iY+j])*dDX1;//### earlier dDX2
							//	TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[7]*bid;
							//if(Array_Label[(i+1)*iY+j]!=9999)               //�¼ӵ�����
								Inf[7] = 0.5*(myseed->iXsize)*TAB*Tz[7]*bid;
								iInRoute++;
						}


						if(Array_Ele[(i+1)*iY+(j+1)]>=9999.0) bid=0;       //8
						 else bid=1.0;

						if(Array_Ele[(i+1)*iY+(j+1)]<Array_Ele[i*iY+j])
						{
							TAB=(Array_Ele[i*iY+j]-Array_Ele[(i+1)*iY+(j+1)])*dDX2;//###
						//	TotalOutflow += 0.354*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
                            Outf[8]=0.398*(myseed->iXsize)*TAB*Tz[4]*bid;
							iOutRoute++;
						}
						else
						{
								TAB=(Array_Ele[(i+1)*iY+(j+1)]-Array_Ele[i*iY+j])*dDX2;
								//TotalInflow += 0.354*(myseed->iXsize)*TAB*Tz[8]*bid;
                            //if(Array_Label[(i+1)*iY+(j+1)]!=9999)               //�¼ӵ�����
                                Inf[8]= 0.398*(myseed->iXsize)*TAB*Tz[8]*bid;
								iInRoute++;
							}


                       if(Array_Ele[i*iY+(j+1)]>=9999.0) bid=0;           //5
						 else bid=1.0;

						if(Array_Ele[i*iY+(j+1)]<Array_Ele[i*iY+j])
						{
							TAB=(Array_Ele[i*iY+j]-Array_Ele[i*iY+(j+1)])*dDX1;//###
						//	TotalOutflow += 0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
                            Outf[5]= 0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
							iOutRoute++;
						}
						else
						{

								TAB=(Array_Ele[i*iY+(j+1)]-Array_Ele[i*iY+j])*dDX1;
								//TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[5]*bid;
                            //if(Array_Label[i*iY+(j+1)]!=9999)               //�¼ӵ�����
								Inf[5] = 0.5*(myseed->iXsize)*TAB*Tz[5]*bid;
								iInRoute++;
//
						}
					}//end of if(elevation >=9999) block
				}//end of if(j>0 && j+1<iY) block
			}//end of i==0 block

			if(iLine+1==iX)
			{
				if(j==0)
				{
// MEM added this instead of the line just below...
// to improve the computational effeciency.

 				if( Array_Ele[i*iY+j]>=9999.0)
					{
						TotalInflow  += 0;
						TotalOutflow += 0;
					}
					else
					{

                       if(Array_Ele[(i-1)*iY+j]>=9999.0) bid=0;                 //1
						 else bid=1.0;
						if(Array_Ele[(i-1)*iY+j]<Array_Ele[i*iY+j])
						{
							TAB =(Array_Ele[i*iY+j]-Array_Ele[(i-1)*iY+j])*dDX1;//###
							//TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
                            Outf[1]= 0.5*(myseed->iXsize)*TAB*Tz[4]*bid;
							iOutRoute++;
						}
						else
						{
							TAB=(Array_Ele[(i-1)*iY+j]-Array_Ele[i*iY+j])*dDX1;
								//TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[1]*bid;
                        //if(Array_Label[(i-1)*iY+j]!=9999)               //�¼ӵ�����
							Inf[1]= 0.5*(myseed->iXsize)*TAB*Tz[1]*bid;
                            iInRoute++;

						}


                       if(Array_Ele[(i-1)*iY+(j+1)]>=9999.0) bid=0;          //2
						 else bid=1.0;

						if(Array_Ele[(i-1)*iY+(j+1)]<Array_Ele[i*iY+j])
						{
							TAB =(Array_Ele[i*iY+j]-Array_Ele[(i-1)*iY+(j+1)])*dDX2;//###
							//TotalOutflow +=  0.354*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
                            Outf[2]=  0.398*(myseed->iXsize)*TAB*Tz[4]*bid;
							iOutRoute++;
						}
						else
						{
							TAB=(Array_Ele[(i-1)*iY+(j+1)]-Array_Ele[i*iY+j])*dDX2;
								//TotalInflow += 0.354*(myseed->iXsize)*TAB*Tz[2]*bid;
                        //if(Array_Label[(i-1)*iY+(j+1)]!=9999)               //�¼ӵ�����
                            Inf[2]= 0.398*(myseed->iXsize)*TAB*Tz[2]*bid;
                            iInRoute++;
						}


                      if(Array_Ele[i*iY+(j+1)]>=9999.0) bid=0;         //5
						 else bid=1.0;

						if(Array_Ele[i*iY+(j+1)]<Array_Ele[i*iY+j])
						{
							TAB =(Array_Ele[i*iY+j]-Array_Ele[i*iY+(j+1)])*dDX1;//###
							//TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
                            Outf[5]=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid;
							iOutRoute++;
						}
						else
						{

								TAB=(Array_Ele[i*iY+(j+1)]-Array_Ele[i*iY+j])*dDX1;
								//TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[5]*bid;
                            //if(Array_Label[i*iY+(j+1)]!=9999)               //�¼ӵ�����
                                Inf[5]= 0.5*(myseed->iXsize)*TAB*Tz[5]*bid;
								iInRoute++;
//
						}
					}//end if(elevation>=9999) block
				}//end of if(j==0)

				if(j+1==iY)
				{
// MEM added this instead of the line just below...
// to improve the computational effeciency.

 				if( Array_Ele[i*iY+j]>=9999.0)
					{
						TotalInflow += 0;
						TotalOutflow += 0;
					}
					else
					{

                         if(Array_Ele[(i-1)*iY+(j-1)]>=9999.0) bid=0;        //0
						 else bid=1.0;

						if(Array_Ele[(i-1)*iY+(j-1)]<Array_Ele[i*iY+j])
						{
							TAB =(Array_Ele[i*iY+j]-Array_Ele[(i-1)*iY+(j-1)])*dDX2;//###
							//TotalOutflow +=  0.354*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
                            Outf[0]=  0.398*(myseed->iXsize)*TAB*Tz[4]*bid;
							iOutRoute++;
						}
						else
						{
								TAB=(Array_Ele[(i-1)*iY+(j-1)]-Array_Ele[i*iY+j])*dDX2;
								//TotalInflow += 0.354*(myseed->iXsize)*TAB*Tz[0]*bid;
                            //if(Array_Label[(i-1)*iY+(j-1)]!=9999)               //�¼ӵ�����
                                Inf[0]= 0.398*(myseed->iXsize)*TAB*Tz[0]*bid;
								iInRoute++;
							}



                         if(Array_Ele[i*iY+(j-1)]>=9999.0) bid=0;        //3
						 else bid=1.0;

						if(Array_Ele[i*iY+(j-1)]<Array_Ele[i*iY+j])
						{
							TAB =(Array_Ele[i*iY+j]-Array_Ele[i*iY+(j-1)])*dDX1;//###
							//TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
                            Outf[3]=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid;
							iOutRoute++;
						}
						else
						{
                                TAB =(Array_Ele[i*iY+(j-1)]-Array_Ele[i*iY+j])*dDX1;
								//TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[3]*bid;
                            //if(Array_Label[i*iY+(j-1)]!=9999)               //�¼ӵ�����
                                Inf[3]= 0.5*(myseed->iXsize)*TAB*Tz[3]*bid;
								iInRoute++;
						}


                        if(Array_Ele[(i-1)*iY+j]>=9999.0) bid=0;          //1
						 else bid=1.0;
						if(Array_Ele[(i-1)*iY+j]<Array_Ele[i*iY+j])
						{
							TAB =(Array_Ele[i*iY+j]-Array_Ele[(i-1)*iY+j])*dDX1;//###
							//TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
                            Outf[1]=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid;
							iOutRoute++;
						}
						else
						{
								TAB=(Array_Ele[(i-1)*iY+j]-Array_Ele[i*iY+j])*dDX1;
								//TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[1]*bid;
                            //if(Array_Label[(i-1)*iY+j]!=9999)               //�¼ӵ�����
                                Inf[1]= 0.5*(myseed->iXsize)*TAB*Tz[1]*bid;
								iInRoute++;
								}
					}//end of if(elevation>=9999)
				}//end of if(j+1==iY) block

				if(j>0 && j+1<iY)
				{


// MEM added this instead of the line just below...
// to improve the computational effeciency.

 				if( Array_Ele[i*iY+j]>=9999.0)
					{
						TotalInflow += 0;
						TotalOutflow += 0;
					}
					else
					{
                       if(Array_Ele[(i-1)*iY+(j-1)]>=9999.0) bid=0;          //0
						 else bid=1.0;

						if(Array_Ele[(i-1)*iY+(j-1)]<Array_Ele[i*iY+j])

						{
							TAB =(Array_Ele[i*iY+j]-Array_Ele[(i-1)*iY+(j-1)])*dDX2;//###
						//	TotalOutflow +=  0.354*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
							Outf[0]       = 0.398*(myseed->iXsize)*TAB*Tz[4]*bid;
							iOutRoute++;
						}
						else
						{
                            TAB=(Array_Ele[(i-1)*iY+(j-1)]-Array_Ele[i*iY+j])*dDX2;
							//	TotalInflow += 0.354*(myseed->iXsize)*TAB*Tz[0]*bid;
                        //if(Array_Label[(i-1)*iY+(j-1)]!=9999)               //�¼ӵ�����
						     Inf[0]      = 0.398*(myseed->iXsize)*TAB*Tz[0]*bid;
							 iInRoute++;
						}



                       if(Array_Ele[(i-1)*iY+j]>=9999.0) bid=0;            //1
						 else bid=1.0;

						if(Array_Ele[(i-1)*iY+j]<Array_Ele[i*iY+j])
						{
							 TAB =(Array_Ele[i*iY+j]-Array_Ele[(i-1)*iY+j])*dDX1;//###
							//TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
						     Outf[1]= 0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
							 iOutRoute++;
						}
						else
						{
								TAB=(Array_Ele[(i-1)*iY+j]-Array_Ele[i*iY+j])*dDX1;
							//	TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[1]*bid;
							//if(Array_Label[(i-1)*iY+j]!=9999)               //�¼ӵ�����
					/*XXX*/		Inf[1] = 0.5*(myseed->iXsize)*TAB*Tz[1]*bid;              //�����ǲ���Ӧ�������⣬��ʼ��0���ĳ���1
								iInRoute++;
                        }

                        if(Array_Ele[(i-1)*iY+(j+1)]>=9999.0) bid=0;               //2
						 else bid=1.0;
						if(Array_Ele[(i-1)*iY+(j+1)]<Array_Ele[i*iY+j])
						{
							TAB =(Array_Ele[i*iY+j]-Array_Ele[(i-1)*iY+(j+1)])*dDX2;//###
							//TotalOutflow +=  0.354*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
							Outf[2]=  0.398*(myseed->iXsize)*TAB*Tz[4]*bid;
							iOutRoute++;
						}
						else
						{

								TAB=(Array_Ele[(i-1)*iY+(j+1)]-Array_Ele[i*iY+j])*dDX2;
							//	TotalInflow += 0.354*(myseed->iXsize)*TAB*Tz[2]*bid;
							//if(Array_Label[(i-1)*iY+(j+1)]!=9999)               //�¼ӵ�����
								Inf[2]= 0.398*(myseed->iXsize)*TAB*Tz[2]*bid;
								iInRoute++;
						}


                        if(Array_Ele[i*iY+(j-1)]>=9999.0) bid=0;         //3
						 else bid=1.0;

						if(Array_Ele[i*iY+(j-1)]<Array_Ele[i*iY+j])
						{
							TAB =(Array_Ele[i*iY+j]-Array_Ele[i*iY+(j-1)])*dDX1;//###
							//TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
							Outf[3]=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base
							iOutRoute++;
						}
						else
						{
								TAB=(Array_Ele[i*iY+(j-1)]-Array_Ele[i*iY+j])*dDX1;
								//TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[3]*bid;
                            //if(Array_Label[i*iY+(j-1)]!=9999)               //�¼ӵ�����
								Inf[3]= 0.5*(myseed->iXsize)*TAB*Tz[3]*bid;
								iInRoute++;
                        }


                       if(Array_Ele[i*iY+(j+1)]>=9999.0) bid=0;              //5
						 else bid=1.0;
						if(Array_Ele[i*iY+(j+1)]<Array_Ele[i*iY+j])
						{
							TAB =(Array_Ele[i*iY+j]-Array_Ele[i*iY+(j+1)])*dDX1;//###
						//	TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
							Outf[5]= 0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
							iOutRoute++;
						}
						else
						{
								TAB=(Array_Ele[i*iY+(j+1)]-Array_Ele[i*iY+j])*dDX1;
							//	TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[5]*bid;
							//if(Array_Label[i*iY+(j+1)]!=9999)               //�¼ӵ�����
							    Inf[5]= 0.5*(myseed->iXsize)*TAB*Tz[5]*bid;
								iInRoute++;
//
						}
					}//end of if(elevation>=9999)
				}//end of if(j>0&&j+1<iY) block
			}//end of if(i+1)==iX block*/

			if(j==0 && iLine>0 && (iLine+1)<iX)
			{

// MEM added this instead of the line just below...
// to improve the computational effeciency.

 			if( Array_Ele[i*iY+j]>=9999.0)
				{
					TotalInflow += 0;
					TotalOutflow += 0;
				}
				else
				{

                   if(Array_Ele[(i-1)*iY+j]>=9999.0) bid=0;           //1
						 else bid=1.0;
					if(Array_Ele[(i-1)*iY+j]<Array_Ele[i*iY+j])
					{
						TAB			 =(Array_Ele[i*iY+j]-Array_Ele[(i-1)*iY+j])*dDX1;//###
						//TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid;
						//OS(19/6/2006): the missing "*bid" was the reason why there was too much baseflow produced at the outlet: it was all coming from the pixel with the highest elevation, just south of the outlet --> by multiplying with "*bid" (which in cae of 9999, i.e. for being outside the watershed boundary) T[z] is multiplied with 0, i.e. no contribution from the surrounding 9999 pixel....--> this was a very important bug fix!!!!!!!!
						Outf[1]=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid;         //֮ǰ��4�������޸�Ϊ1
						//OS(19/6/2006): the missing "*bid" was the reason why there was too much baseflow produced at the outlet:
						//it was all coming from the pixel with the highest elevation, just south of the outlet
						//--> by multiplying with "*bid" (which in cae of 9999, i.e. for being outside the watershed boundary)
						//T[z] is multiplied with 0, i.e. no contribution from the surrounding 9999 pixel....--> this was a very important bug fix!!!!!!!!
						iOutRoute++; //base flow in cubic meters
					}
					else
					{

							TAB=(Array_Ele[(i-1)*iY+j]-Array_Ele[i*iY+j])*dDX1;
						//	TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[1]*bid;
						//if(Array_Label[(i-1)*iY+j]!=9999)               //�¼ӵ�����
				/*XXX 4??*/	Inf[1]= 0.5*(myseed->iXsize)*TAB*Tz[1]*bid;
							iInRoute++;
					}

                    if(Array_Ele[(i-1)*iY+(j+1)]>=9999.0) bid=0;             //2
						 else bid=1.0;

					if(Array_Ele[(i-1)*iY+(j+1)]<Array_Ele[i*iY+j])
					{
						TAB =(Array_Ele[i*iY+j]-Array_Ele[(i-1)*iY+(j+1)])*dDX2;//###
						//TotalOutflow +=  0.354*(myseed->iXsize)*TAB*Tz[4]*bid;//
					    Outf[2] =  0.398*(myseed->iXsize)*TAB*Tz[4]*bid;//
						iOutRoute++; //base flow in cubic meters
					}
					else
					{
							TAB=(Array_Ele[(i-1)*iY+(j+1)]-Array_Ele[i*iY+j])*dDX2;
						//	TotalInflow += 0.354*(myseed->iXsize)*TAB*Tz[2]*bid;
						//if(Array_Label[(i-1)*iY+(j+1)]!=9999)               //�¼ӵ�����
					    	Inf[2] = 0.398*(myseed->iXsize)*TAB*Tz[2]*bid;
							iInRoute++;
					}


                   if(Array_Ele[i*iY+(j+1)]>=9999.0) bid=0;                  //5
						 else bid=1.0;

					if(Array_Ele[i*iY+(j+1)]<Array_Ele[i*iY+j])
					{
						TAB =(Array_Ele[i*iY+j]-Array_Ele[i*iY+(j+1)])*dDX1;//###
					//	TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
						Outf[5]=0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
						iOutRoute++;
					}
					else
					{
							TAB=(Array_Ele[i*iY+(j+1)]-Array_Ele[i*iY+j])*dDX1;
							//TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[5]*bid;
                        //if(Array_Label[i*iY+(j+1)]!=9999)               //�¼ӵ�����
							Inf[5] = 0.5*(myseed->iXsize)*TAB*Tz[5]*bid;
							iInRoute++;
					}



                    if(Array_Ele[(i+1)*iY+j]>=9999.0) bid=0;             //7
						 else bid=1.0;

					if(Array_Ele[(i+1)*iY+j]<Array_Ele[i*iY+j])
					{
						TAB =(Array_Ele[i*iY+j]-Array_Ele[(i+1)*iY+j])*dDX1;//###
						//TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
						Outf[7]=0.5*(myseed->iXsize)*TAB*Tz[4]*bid;
						iOutRoute++;
					}
					else
					{
						TAB=(Array_Ele[(i+1)*iY+j]-Array_Ele[i*iY+j])*dDX1;
						//TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[7]*bid;
                    //if(Array_Label[(i+1)*iY+j]!=9999)               //�¼ӵ�����
                        Inf[7]= 0.5*(myseed->iXsize)*TAB*Tz[7]*bid;
						iInRoute++;
//
					}


                    if(Array_Ele[(i+1)*iY+(j+1)]>=9999.0) bid=0;                //8
						 else bid=1.0;

					if(Array_Ele[(i+1)*iY+(j+1)]<Array_Ele[i*iY+j])
					{
						TAB=(Array_Ele[i*iY+j]-Array_Ele[(i+1)*iY+(j+1)])*dDX2;//###
						//TotalOutflow += 0.354*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
					    Outf[8]=0.398*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
						iOutRoute++;
					}
					else
					{
							TAB=(Array_Ele[(i+1)*iY+(j+1)]-Array_Ele[i*iY+j])*dDX2;
                            //TotalInflow += 0.354*(myseed->iXsize)*TAB*Tz[8]*bid;
                        //if(Array_Label[(i+1)*iY+(j+1)]!=9999)               //�¼ӵ�����
							Inf[8]= 0.398*(myseed->iXsize)*TAB*Tz[8]*bid;
							iInRoute++;
//
					}


				  }//end of if elevation>= 9999 block
			}//end of if(j==0 && i>0 && (i+1)<iX)

			if((j+1)==iY && iLine>0 && (iLine+1)< iX)
			{
// MEM added this instead of the line just below...
// to improve the computational effeciency.

 				if( Array_Ele[i*iY+j]>=9999.0)
				{
					TotalInflow	+= 0;
					TotalOutflow += 0;
				}
				else
				{

				if(Array_Ele[(i-1)*iY+(j-1)]>=9999.0) bid=0;                 //0
						 else bid=1.0;


					if(Array_Ele[(i-1)*iY+(j-1)]<Array_Ele[i*iY+j])
					{
						TAB =(Array_Ele[i*iY+j]-Array_Ele[(i-1)*iY+(j-1)])*dDX2;//###
					//	TotalOutflow +=  0.354*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
					    Outf[0]= 0.398*(myseed->iXsize)*TAB*Tz[4]*bid;
						iOutRoute++;
					}
					else
					{

							TAB=(Array_Ele[(i-1)*iY+(j-1)]-Array_Ele[i*iY+j])*dDX2;
							//TotalInflow += 0.354*(myseed->iXsize)*TAB*Tz[0]*bid;
                        //if(Array_Label[(i-1)*iY+(j-1)]!=9999)               //�¼ӵ�����
							Inf[0]= 0.398*(myseed->iXsize)*TAB*Tz[0]*bid;
							iInRoute++;
                    }



                   if(Array_Ele[(i-1)*iY+j]>=9999.0) bid=0;                 //1
						 else bid=1.0;

					if(Array_Ele[(i-1)*iY+j]<Array_Ele[i*iY+j])
					{
						TAB =(Array_Ele[i*iY+j]-Array_Ele[(i-1)*iY+j])*dDX1;//###
					//	TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
					    Outf[1]=0.5*(myseed->iXsize)*TAB*Tz[4]*bid;
                        iOutRoute++;
					}
					else
					{
							TAB=(Array_Ele[(i-1)*iY+j]-Array_Ele[i*iY+j])*dDX1;
						//	TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[1]*bid;
						//if(Array_Label[(i-1)*iY+j]!=9999)               //�¼ӵ�����
                            Inf[1]= 0.5*(myseed->iXsize)*TAB*Tz[1]*bid;
                            iInRoute++;                                   //�������һ��

					}


                     if(Array_Ele[i*iY+(j-1)]>=9999.0) bid=0;            //3
						 else bid=1.0;

					if(Array_Ele[i*iY+(j-1)]<Array_Ele[i*iY+j])
					{
                        TAB =(Array_Ele[i*iY+j]-Array_Ele[i*iY+(j-1)])*dDX1;//###
                        //TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
                        Outf[3]=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid;
                        iOutRoute++;
					}
					else
					{
							TAB=(Array_Ele[i*iY+(j-1)]-Array_Ele[i*iY+j])*dDX1;
						//	TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[3]*bid;
						//if(Array_Label[i*iY+(j-1)]!=9999)               //�¼ӵ�����
						    Inf[3] = 0.5*(myseed->iXsize)*TAB*Tz[3]*bid;
							iInRoute++;
					}


					if(Array_Ele[(i+1)*iY+(j-1)]>=9999.0) bid=0;            //6
						 else bid=1.0;

					if(Array_Ele[(i+1)*iY+(j-1)]<Array_Ele[i*iY+j])
					{
						TAB =(Array_Ele[i*iY+j]-Array_Ele[(i+1)*iY+(j-1)])*dDX2;//###
						//TotalOutflow +=  0.354*(myseed->iXsize)*TAB*Tz[4]; //base flow in cubic meters
						Outf[6]=0.398*(myseed->iXsize)*TAB*Tz[4]*bid;             //����©*bid
						iOutRoute++;
					}
					else
					{

							TAB=(Array_Ele[(i+1)*iY+(j-1)]-Array_Ele[i*iY+j])*dDX2;
							//TotalInflow += 0.354*(myseed->iXsize)*TAB*Tz[6];
                        //if(Array_Label[(i+1)*iY+(j-1)]!=9999)               //�¼ӵ�����
							Inf[6]= 0.398*(myseed->iXsize)*TAB*Tz[6]*bid;        //����©*bid
						    iInRoute++;
					}


                   if(Array_Ele[(i+1)*iY+j]>=9999.0) bid=0;             //7
						 else bid=1.0;

					if(Array_Ele[(i+1)*iY+j]<Array_Ele[i*iY+j])
					{
						TAB =(Array_Ele[i*iY+j]-Array_Ele[(i+1)*iY+j])*dDX1;//###
					//	TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
						Outf[7]=0.5*(myseed->iXsize)*TAB*Tz[4]*bid;
						iOutRoute++;
					}
					else
					{

							TAB=(Array_Ele[(i+1)*iY+j]-Array_Ele[i*iY+j])*dDX1;
						//	TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[7]*bid;
						//if(Array_Label[(i+1)*iY+j]!=9999)               //�¼ӵ�����
						    Inf[7] = 0.5*(myseed->iXsize)*TAB*Tz[7]*bid;
							iInRoute++;
//						}
					}
				}//end of if elevation >= 9999
			}//end of if((j+1)==iY && i>0 && (i+1)< iX)


// MEM: now the central pixel is away from the database edges

			if(iLine>0 && (iLine+1)<iX && j>0 && (j+1)<iY)

			{



// MEM added this instead of the line just below...
// to improve the computational effeciency.


				if( Array_Ele[i*iY+j]>=9999.0)
				{
					TotalInflow		+= 0;
					TotalOutflow	+= 0;
				}
				else
				{

                  if(Array_Ele[(i-1)*iY+(j-1)]>=9999.0) bid=0;     //0
						 else bid=1.0;

					if(Array_Ele[(i-1)*iY+(j-1)]<Array_Ele[i*iY+j])
					{
						TAB =(Array_Ele[i*iY+j]-Array_Ele[(i-1)*iY+(j-1)])*dDX2;//###
					//	TotalOutflow +=  0.354*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
						Outf[0]  =  0.398*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
						iOutRoute++;
					}
					else
					{
						TAB=(Array_Ele[(i-1)*iY+(j-1)]-Array_Ele[i*iY+j])*dDX2;
						//TotalInflow += 0.354*(myseed->iXsize)*TAB*Tz[0]*bid;
                    //if(Array_Label[(i-1)*iY+j]!=-9999)                   //�¼ӵ�����
						Inf[0] = 0.398*(myseed->iXsize)*TAB*Tz[0]*bid;
						iInRoute++;
					}

                    if(Array_Ele[(i-1)*iY+j]>=9999.0) bid=0;            //1
						 else bid=1.0;

					if(Array_Ele[(i-1)*iY+j]<Array_Ele[i*iY+j])
					{
						TAB =(Array_Ele[i*iY+j]-Array_Ele[(i-1)*iY+j])*dDX1;//###
						//TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
						Outf[1]  =  0.5*(myseed->iXsize)*TAB*Tz[4]*bid;
						iOutRoute++;
					}
					else
					{
							TAB=(Array_Ele[(i-1)*iY+j]-Array_Ele[i*iY+j])*dDX1;
							//TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[1]*bid;
                       //if(Array_Label[(i-1)*iY+j]!=-9999)                   //ԭ����-9999
							Inf[1]= 0.5*(myseed->iXsize)*TAB*Tz[1]*bid;
							iInRoute++;
							}


                   if(Array_Ele[(i-1)*iY+(j+1)]>=9999.0) bid=0;           //2
						 else bid=1.0;

					if(Array_Ele[(i-1)*iY+(j+1)]<Array_Ele[i*iY+j])
					{
						TAB =(Array_Ele[i*iY+j]-Array_Ele[(i-1)*iY+(j+1)])*dDX2;//###
						//TotalOutflow +=  0.354*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
					    Outf[2]=0.398*(myseed->iXsize)*TAB*Tz[4]*bid;
						iOutRoute++;
					}
					else
					{

							TAB=(Array_Ele[(i-1)*iY+(j+1)]-Array_Ele[i*iY+j])*dDX2;
						//	TotalInflow += 0.354*(myseed->iXsize)*TAB*Tz[2]*bid;
						//if(Array_Label[(i-1)*iY+(j+1)]!=-9999)                   //ע��
							Inf[2] = 0.398*(myseed->iXsize)*TAB*Tz[2]*bid;
							iInRoute++;
					}


                     if(Array_Ele[i*iY+(j-1)]>=9999.0) bid=0;                      //3  ��ʼ-9999�����Ǵ�����ж�
						 else bid=1.0;

					if(Array_Ele[i*iY+(j-1)]<Array_Ele[i*iY+j])
					{
                        TAB =(Array_Ele[i*iY+j]-Array_Ele[i*iY+(j-1)])*dDX1;//###
                            //TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
                        Outf[3] =  0.5*(myseed->iXsize)*TAB*Tz[4]*bid;
                        iOutRoute++;
					}
					else
					{

							TAB=(Array_Ele[i*iY+(j-1)]-Array_Ele[i*iY+j])*dDX1;
							//TAB=(65.1-Array_Ele[i*iY+j])*dDX1;
							//TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[3]*bid;
                       //if(Array_Label[i*iY+(j-1)]!=-9999)                  //ע��
							Inf[3] = 0.5*(myseed->iXsize)*TAB*Tz[3]*bid;
							iInRoute++;
//
					}

                      if(Array_Ele[i*iY+(j+1)]>=9999.0) bid=0;         //5
						 else bid=1.0;

					if(Array_Ele[i*iY+(j+1)]<Array_Ele[i*iY+j])
					{
						TAB =(Array_Ele[i*iY+j]-Array_Ele[i*iY+(j+1)])*dDX1;//###
					//	TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
					    Outf[5]=0.5*(myseed->iXsize)*TAB*Tz[4]*bid;
						iOutRoute++;
					}
					else
					{

							TAB=(Array_Ele[i*iY+(j+1)]-Array_Ele[i*iY+j])*dDX1;
						//	TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[5]*bid;
					//if(Array_Label[i*iY+(j+1)]!=-9999)                 //ԭ����-9999
							Inf[5]= 0.5*(myseed->iXsize)*TAB*Tz[5]*bid;
							iInRoute++;
//
					}


                   if(Array_Ele[(i+1)*iY+(j-1)]>=9999.0) bid=0;    //6
						 else bid=1.0;

					if(Array_Ele[(i+1)*iY+(j-1)]<Array_Ele[i*iY+j])
					{
						TAB =(Array_Ele[i*iY+j]-Array_Ele[(i+1)*iY+(j-1)])*dDX2;//###
					//	TotalOutflow +=  0.354*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
					    Outf[6]=  0.398*(myseed->iXsize)*TAB*Tz[4]*bid;
						iOutRoute++;
					}
					else
					{

						TAB=(Array_Ele[(i+1)*iY+(j-1)]-Array_Ele[i*iY+j])*dDX2;
						//TotalInflow += 0.354*(myseed->iXsize)*TAB*Tz[6]*bid;
					//if(Array_Label[(i+1)*iY+(j-1)]!=-9999)          //ԭ����-9999
						Inf[6] = 0.398*(myseed->iXsize)*TAB*Tz[6]*bid;
						iInRoute++;
					}


                   if(Array_Ele[(i+1)*iY+j]>=9999.0) bid=0;             //7
						 else bid=1.0;

					if(Array_Ele[(i+1)*iY+j]<Array_Ele[i*iY+j])
					{
						TAB =(Array_Ele[i*iY+j]-Array_Ele[(i+1)*iY+j])*dDX1;//###
						//TotalOutflow +=  0.5*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
						Outf[7] =  0.5*(myseed->iXsize)*TAB*Tz[4]*bid;
						iOutRoute++;
					}
					else
					{
							TAB=(Array_Ele[(i+1)*iY+j]-Array_Ele[i*iY+j])*dDX1;
							//TotalInflow += 0.5*(myseed->iXsize)*TAB*Tz[7]*bid;
					   //if(Array_Label[(i+1)*iY+j]!=-9999)            //ԭ����-9999
							Inf[7]= 0.5*(myseed->iXsize)*TAB*Tz[7]*bid;
							iInRoute++;
//
					}



                   if(Array_Ele[(i+1)*iY+(j+1)]>=9999.0) bid=0;            //8
						 else bid=1.0;

					if(Array_Ele[(i+1)*iY+(j+1)]<Array_Ele[i*iY+j])
					{
						TAB=(Array_Ele[i*iY+j]-Array_Ele[(i+1)*iY+(j+1)])*dDX2;//###
						//TotalOutflow += 0.354*(myseed->iXsize)*TAB*Tz[4]*bid; //base flow in cubic meters
						Outf[8]= 0.398*(myseed->iXsize)*TAB*Tz[4]*bid;
						iOutRoute++;
					}
					else
					{

							TAB=(Array_Ele[(i+1)*iY+(j+1)]-Array_Ele[i*iY+j])*dDX2;
							//TotalInflow += 0.354*(myseed->iXsize)*TAB*Tz[8]*bid;
						//if(Array_Label[(i+1)*iY+(j+1)]!=-9999)          //ԭ����-9999
							Inf[8] = 0.398*(myseed->iXsize)*TAB*Tz[8]*bid;
							iInRoute++;
//
					}
				}//end of if elevation >= 9999 block
			}//end of if(i>0 && (i+1)<iX && j>0 && (j+1)<iY)

			if(iOutRoute==0 && iInRoute==0)
			{
				Baseflow			= 0.0;
				Array_Label[i*iY+j] = 9999;
			}
			else
			{
// Here the Baseflow has unit of meter
				  //Baseflow			= (TotalInflow-TotalOutflow);

//	TotalInflow =Inf[0]+Inf[1]+Inf[2]+Inf[3]+Inf[4]+Inf[5]+Inf[6]+Inf[7]+Inf[8];            //���������ƺ�û�м��㡾4����ʼΪ0
//	TotalOutflow=Outf[0]+Outf[1]+Outf[2]+Outf[3]+Outf[4]+Outf[5]+Outf[6]+Outf[7]+Outf[8];
	TotalInflow =Inf[0]+Inf[1]+Inf[2]+Inf[3]+Inf[5]+Inf[6]+Inf[7]+Inf[8];            //���������ƺ�û�м��㡾4��
    TotalOutflow=Outf[0]+Outf[1]+Outf[2]+Outf[3]+Outf[5]+Outf[6]+Outf[7]+Outf[8];

		        Baseflow			= (TotalInflow-TotalOutflow)/(myseed->iXsize*myseed->iYsize);
		        //OS: important: baseflow is calculated as the difference inflow-outlfow DIVIDED by the area --> i.e. results are in m and NOT in m^3
				Array_Label[i*iY+j] = 9999;
			}

		}//end of if else block


		baseflow[j]			=(float)Baseflow;
		total_inflow[j]		=(float)TotalInflow;	//***Added by Andriy
		total_outflow[j]	=(float)TotalOutflow;	//***Added by Andriy

	/*//################################################################
				// USE THIS AREA TO DO BASEFLOW SCHEMES
		if(soil[j].water_table > 0.15) //Mineral layer
		{
		baseflow[j]=-1*((soilindex[textureindext].porosity-soilindex[textureindext].field_cap)*1)*
		(soil[j].Max_depth_Z-soil[j].water_table);
		}
		else   //Peat layer
		{
		baseflow[j]=-1*((0.85-0.60)*1)*
		(soil[j].Max_depth_Z-soil[j].water_table);
		}

		//################################################################

	*/



}//end of for-j loop
}//end of the function

