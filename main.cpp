#include "stdafx.h"
#include "BepsHydrScience.h"
#include "string.h"
#include "malloc.h"
#include "stdio.h"
#include "math.h"
int main(int argc, char* argv[])
{
    int rcode;
    BH_SubParams1_t BH_SubParams1;
    BH_SubParams1a_t BH_SubParams1a;
    BH_SubParams2_t BH_SubParams2;

    //readconf("C:/00XXY/2-DataWS/011BEPSTerrainLab/0_BTLWS30/Conf/33_2009_Climate&BTL.con",&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2,&rcode);
    //readconf("C:/00XXY/2-DataWS/011BEPSTerrainLab/0_BTLWS30/Conf/xxy_test.con",&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2,&rcode);
    //readconf("C:/00XXY/2-DataWS/011BEPSTerrainLab/0_ARunWS/38_120_Climate&BTL.con",&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2,&rcode);
    readconf("E:/BTL/model/BTLforWang/BTLrun.con",&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2,&rcode);

    //readconf("BTLrun.con",&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2,&rcode);

    if (BH_SubParams1.bCalculateClimate==0)
    {
        printf("----------Step 2: Climate Calculation ---------\n\n");
        ClimateCalculate(&BH_SubParams1,&BH_SubParams1a);
        printf("----------End--------\n\n");
    }

    if (BH_SubParams1.bCalculateClimate==1)
    {
        printf("----------Step 3: BTL Main --------\n\n");
        BepsHydrCalculate(&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2);
        printf("----------End--------\n\n");
    }

    if (BH_SubParams1.bCalculateClimate==2)
    {

        printf("----------Step 2: Climate Calculation ---------\n\n");
        ClimateCalculate(&BH_SubParams1,&BH_SubParams1a);
        printf("----------End--------\n\n");

        printf("----------Step 3: BTL Main --------\n\n");
        BepsHydrCalculate(&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2);
        printf("----------End--------\n\n");
    }
    return 0;
}
