/*
simulates the unsteady one-dimensional heat conduction in a soil colum

 *******************************************************************************************/

#include "stdafx.h"
#include "BepsHydrScience.h"
#include <math.h>
#define N 6
void soil_temp(pubv* start, Soil_t* soil, unsigned char* soil_texture,float*prev_snowdepth, int jday, unsigned char* lc, unsigned char* watershed_ptr, short int* climate_tm )
{

    int j;
    float tm;
    for (j = 0; j < start->npixels; j++)
    {
        int i,k;
        int Top1=0;
        int Bot1=N-1;
        double	TempCurrent[N]; //Temperature at the current timestep
        double TempNext[N]; //Temperature at the next timestep
        double	ThermCon[N];
        double	AppVolHeatCap[N];
        double Thick[N];
        double T_a_a;
        double T_s;
        double damp;
        if ((watershed_ptr[j] == 0) || (lc[j] == 0))
        {
            soil[j].soil_temp = -999;
            soil[j].ST_Layer_1=-999;
            soil[j].ST_Layer_2=-999;
            soil[j].ST_Layer_3=-999;
            soil[j].ST_Layer_4=-999;
            soil[j].ST_Layer_5=-999;
            soil[j].ST_Layer_6=-999;

        }

        else
        {
            float L;
            if(lc[j]==1)
                L=3.0;
            if(lc[j]==2)
                L=4.5;
            if(lc[j]==3)
                L=3.0;
            if(lc[j]==4)
                L=4.5;
            if(lc[j]==5)
                L=4.0;
            if(lc[j]==6)
                L=1.5;
            if(lc[j]==7)
                L=1.5;
            else
                L=2.5;

            /*if(lc[j]==1) L=3.0;
            if(lc[j]==2) L=4.5;
            if(lc[j]==3) L=4.0;
            if(lc[j]==5) L=1.5;
            else L=2.5;*/
//calculating the surface temp------------->
//if (prev_snowdepth[j]>0) tm= (float) ((climate_tm[j]/10)+0);
            /*else*/ tm = (float) climate_tm[j]/10;
//soil[j].soil_temp=tm+((-0.11+(0.96*tm)-(0.00008*pow(tm,3)))-tm)+(log(1+L)/log(1+L));//(0.89* soil[j].soil_temp) + (0.1 * tm);
//_________________________________________________________


//Parameters for Volumetric heat capacity(these are constants for all layers)

            float thickm;


            if( prev_snowdepth[j]<=0.02)
            {
                thickm=0.05;
                Thick[0] = thickm;
            }
            else
            {
                Thick[0] = prev_snowdepth[j];
            }
            AppVolHeatCap[0] = (3.0)*(1000000);
            ThermCon[0] = 0.75;
            TempCurrent[0] = soil[j].ST_Layer_1;



            /*  MINERAL SOIL THERMAL PROPERTIES AND HEAT TRANSFER FOLLOWS*/  //Change this with time and depth in future
//2. Layer2 Depth=
            TempCurrent[1] = soil[j].ST_Layer_2;
            Thick[1] = 0.05;
            ThermCon[1] = 2.8;
            AppVolHeatCap[1]=2.1*1000000;

//3. Layer3 Depth=

            TempCurrent[2] = soil[j].ST_Layer_3;
            Thick[2] = 0.10;
            ThermCon[2] =3.1;
            AppVolHeatCap[2]=2.1*1000000;

//4. Layer4 Depth=
            TempCurrent[3] = soil[j].ST_Layer_4;
            Thick[3] = 0.20;
            ThermCon[3] = 2.5;
            AppVolHeatCap[3]=2.2*1000000;

//5. Layer5 Depth=

            TempCurrent[4] = soil[j].ST_Layer_5;
            Thick[4] = 0.50;
            ThermCon[4] = 2.5;
            AppVolHeatCap[4]=2.3*1000000;


//6. Layer6 Depth=

            TempCurrent[5] = soil[j].ST_Layer_6;

            Thick[5] = 1.5;
            ThermCon[5] = 2.6;
            AppVolHeatCap[5]=2.2*1000000;



            T_a_a = 0;
            T_s= tm+((-0.11+(0.96*tm)-(0.00008*pow(tm,3)))-tm)+(log(1+L)/log(1+4.5));
            damp =1.5;



            FormTriDiagM(Top1, Bot1, damp, T_a_a, T_s,AppVolHeatCap, ThermCon, Thick,TempCurrent, TempNext);

            soil[j].ST_Layer_1=TempNext[0];
            soil[j].ST_Layer_2=TempNext[1];
            soil[j].ST_Layer_3=TempNext[2];
            soil[j].ST_Layer_4=TempNext[3];
            soil[j].ST_Layer_5=TempNext[4];
            soil[j].ST_Layer_6=TempNext[5];
            soil[j].soil_temp=TempNext[1];      //土壤温度和土壤第二层温度一样




        } //end of else for watershed boundary criteria

    }//end of for-pixel loop


}//end of this sub routine



//<yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy>

void FormTriDiagM(int Top, int Bot, double DampDepth, double TempAnnAver, double TempSurf, double *AppVolHeatCap,
                  double *ThermCon, double *Thick, double *TempCurrent, double *TempNext)
{

    int j; //counter variable
    double f;  //weighting factor between 0 and 1 defining the fractions of explicit (f=0) vs. implicit (f=1)
    double alpha;//  ratio: (daily time-step) / Thick
    double eps[20];
    double super[20], main[20], sub[20], right[20];
    double T_depth;

    f=1;

    T_depth=0;
    for(j=Top; j<=Bot; j++)
        T_depth=T_depth+Thick[j];


    //eps calculated for Top
    eps[Top] =ThermCon[Top]*2/Thick[Top]; //(0.5 * Thick[Top]) / ThermCon[Top];

    //eps calculated for Top+1
    for(j = Top + 1; j <= Bot; j++)
    {
        eps[j] = 1 / (0.5 * Thick[j-1] / ThermCon[j-1] + 0.5 * Thick[j] / ThermCon[j]);
    }

    //eps calculated for Bot+1 --> needed to get eps[j+1] for the bottom layer...

    j = Bot+1;
    eps[j]=1 / (0.5 * Thick[j-1] / ThermCon[j-1] +
                0.5 * (3 * DampDepth -T_depth)/ThermCon[j-1]);


    //the "major for-loop for the right hand-side and the matrix coefficients
    for(j = Top; j <= Bot; j++)
    {

        //getting the ratio (daily time-step)/ Thick

        alpha = (3600.00 * 24.00) / Thick[j];

        //putting the right-hand side together ....
        // reference: see numerical heat transfer and fluid flow book on page 55...

        if(j == Top) // uppermost layer
        {
            //
            right[j] = AppVolHeatCap[j]*TempCurrent[j]
                       + alpha*(1-f)*(eps[j]*(TempSurf-TempCurrent[j])
                                      -eps[j+1]*(TempCurrent[j]-TempCurrent[j+1]))+alpha*f*eps[j]*TempSurf;
        }

        else if(j == Bot) // lowest layer
        {
            right[j] = AppVolHeatCap[j]*TempCurrent[j]
                       + alpha*(1-f)*(eps[j]*(TempCurrent[j-1]-TempCurrent[j])-
                                      eps[j+1]*(TempCurrent[j]-TempAnnAver))+alpha*f*eps[j+1]*TempAnnAver;
        }

        else if(j != Top && j != Bot) // all the stuff in the middle
        {
            right[j] = AppVolHeatCap[j]*TempCurrent[j]
                       + alpha*(1-f) *(eps[j]*(TempCurrent[j-1]-TempCurrent[j])
                                       -eps[j+1]*(TempCurrent[j]-TempCurrent[j+1]));
        }


        //putting the coefficients of the tridiagonal matrix together --> using three 1D arrays: super-, main-, and sub-diagonal
        // reference: see numerical heat transfer and fluid flow book on page 55...
        main[j]  = AppVolHeatCap[j]+ alpha*f * (eps[j] + eps[j+1]);
        super[j] = -f * alpha * eps[j+1];
        sub[j]   = -f * alpha * eps[j];


        if(j == Top)
        {
            sub[j] = 0;
        }

        super[j] = -f * alpha * eps[j+1];


        if(j == Bot)
        {
            super[j] = 0;
        }



    }// end of the foor loop

    SolveTriDiagM(Top, Bot, super, main, sub, right, TempNext);
//solution1(Top,Bot,sub,main,super,right,TempNext); OS (10/5/2006): this is WeiMin's code
}



/*****************************************************************************
  Function name: SolveTridiagM()

  Purpose      : 31.1.2006: Solve the tridiagonal matrix with LU decomposition as provided by "Numerical recipies in C"...

  Required     :


/*****************************************************************************/

void SolveTriDiagM(int Topa,int Bota,double * super,double *main,double *sub, double * right,double * TempNext )
{
    int i,j;
    double alpha[10],gamma[10],a[10],b[10],c[10];


    for(i=Topa; i<=Bota; i++)
    {
        a[i]=super[i];
        b[i]=main[i];
        c[i]=sub[i];
    }

    alpha[Topa]=1/b[Topa];
    gamma[Topa]=c[Topa]*alpha[Topa];

    for(i=Topa+1; i<Bota; i++)
    {
        alpha[i]=1/(b[i]-a[i]*gamma[i-1]);
        gamma[i]=c[i]*alpha[i];
    }


    TempNext[Topa]=right[Topa]*alpha[Topa];

    for(i=Topa+1; i<Bota; i++)
        TempNext[i]=(right[i]-a[i]*TempNext[i-1])*alpha[i];

    TempNext[Bota]=(right[Bota]-a[Bota]*TempNext[Bota-1])/(b[Bota]-a[Bota]*gamma[Bota-1]);

    for(i=Topa; i<Bota; i++)
    {
        j=Bota-i+Topa-1;
        TempNext[j]=TempNext[j]-gamma[j]*TempNext[j+1];
    }
}


