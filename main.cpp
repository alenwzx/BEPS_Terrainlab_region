#include "stdafx.h"
#include "BepsHydrScience.h"
#include "string.h"
#include "malloc.h"
#include "stdio.h"
#include "math.h"
#include <time.h>
int main(int argc, char* argv[])
{
    int rcode;
    BH_SubParams1_t BH_SubParams1;
    BH_SubParams1a_t BH_SubParams1a;
    BH_SubParams2_t BH_SubParams2;

    time_t start, end;
    struct tm* tminfo;
    char timebuf[64];
    time(&start);
    tminfo = localtime(&start);
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tminfo);
    printf("start timestamp: %s\n", timebuf);

    //readconf("C:/00XXY/2-DataWS/011BEPSTerrainLab/0_BTLWS30/Conf/33_2009_Climate&BTL.con",&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2,&rcode);
    //readconf("C:/00XXY/2-DataWS/011BEPSTerrainLab/0_BTLWS30/Conf/xxy_test.con",&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2,&rcode);
    //readconf("C:/00XXY/2-DataWS/011BEPSTerrainLab/0_ARunWS/38_120_Climate&BTL.con",&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2,&rcode);
    // readconf("H:/summer_2025/config0/BTLrun_Col_250m_2008.con",&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2,&rcode);
    // readconf("H:/summer_2025/config0/BTLrun_WuY_250m_2001.con",&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2,&rcode);
    // readconf("H:/summer_2025/config0/BTLrun_ShangHang_5m_2024.con",&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2,&rcode);
    // readconf("H:/summer_2025/config0/BTLrun_ShangHang_5m_2020.con",&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2,&rcode);
    readconf("H:/summer_2025/config0/BTLrun_ShangHang_30m_2024.con",&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2,&rcode);
    // readconf("H:/summer_2025/config0/BTLrun_SanMing_12.5m_2021.con",&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2,&rcode);
    // readconf("H:/summer_2025/config0/BTLrun_Col_250m_2008.con",&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2,&rcode);
    // readconf("H:/summer_2025/config0/BTLrun_WangL_250m_2020.con",&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2,&rcode);
    // readconf("H:/summer_2025/config0/BTLrun_WuY_90m_2016.con",&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2,&rcode);
    // readconf("H:/summer_2025/config0/BTLrun_SSH_3m_2016.con",&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2,&rcode);
    // readconf("H:/summer_2025/config0/BTLrun_Cha_250m_2003.con",&BH_SubParams1,&BH_SubParams1a,&BH_SubParams2,&rcode);
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

    time(&end);
    tminfo = localtime(&end);
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tminfo);
    printf("end timestamp: %s\n", timebuf);
    int seconds = (int)difftime(end, start);
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int secs = seconds % 60;
    printf("total cost time: %02d:%02d:%02d\n", hours, minutes, secs);
    return 0;
}
