# @mainpage BEPS-Terrainlab daily Region Version(v2.0)
The user guide for the BEPS-terrainlab-v2.0, which originated from the Boreal Ecosystem Productivity Simulator (Liu et al., 1997) that was developed during the Boreal Ecosystem–Atmosphere Study (BOREAS).  

The BEPS-Terrainlab daily Region Version(v2.0) requires a minimum 3.17 CMake version and is based on the C99 standard.It is recommended to use CLion(https://www.jetbrains.com/clion/) and MingW (https://www.mingw-w64.org/) to compile and run the model.  

Make sure the driver file (.con) address in the main function is correct.  

Make sure the "input" and "output" folder addresses in the driver file are correct, and other parameters are consistent with the attributes of the input file.  



Driver file structure：

jday_start----The beginning ordinal number of the year   

jday_end----The ending ordinal number of the year   

nlines----number of rows   

npixels----number of columns   

iXsize----Pixel size in the X direction

iYsize----Pixel size in the Y direction

factor----Scaling Factor

ULLat----left latitude of Upper  

ULLong----Longitude of Upper left   

LRLat----latitude of lower right   

LRLong----Longitude of lower right   

InitialSnowDEN----Initial snow density   

InitialSWE----Initial snow water equivalent   

inputpath----Enter the address of the folder where the input data is stored  

outpath----Enter the address of the folder where the output data will be stored  

caculatePattern---- 0, only difference the meteorological data; 1, only perform beps simulation; 2, perform both  

Reference：

Chen, Jing M., Xiaoyong Chen, Weimin Ju, and Xiaoyuan Geng. “Distributed Hydrological Model for Mapping Evapotranspiration Using Remote Sensing Inputs.” Journal of Hydrology 305, no. 1–4 (April 2005): 15–39. https://doi.org/10.1016/j.jhydrol.2004.08.029.

Govind, Ajit, Jing Ming Chen, Hank Margolis, Weimin Ju, Oliver Sonnentag, and Marc-André Giasson. “A Spatially Explicit Hydro-Ecological Modeling Framework (BEPS-TerrainLab V2.0): Model Description and Test in a Boreal Ecosystem in Eastern North America.” Journal of Hydrology 367, no. 3–4 (April 2009): 200–216. https://doi.org/10.1016/j.jhydrol.2009.01.006.

Liu, J. “A Process-Based Boreal Ecosystem Productivity Simulator Using Remote Sensing Inputs.” Remote Sensing of Environment 62, no. 2 (November 1997): 158–75. https://doi.org/10.1016/S0034-4257(97)00089-8.

Liu, Jane. “BOREAL ECOSYSTEM PRODUCTIVITY SIMULATOR,” n.d.

