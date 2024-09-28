cmake_minimum_required(VERSION 3.29)
project(BEPS_Terrainlab)

set(CMAKE_CXX_STANDARD 11)

add_executable(BEPS_Terrainlab base_flow.cpp bepshydr.cpp carbon.cpp ClimateCal.cpp compute_cap_rise.cpp
  compute_daylength.cpp compute_solar_zenith.cpp compute_unsat_zone_drainage.cpp current_tz.cpp
  doflux.cpp doxx.cpp insert_day_number.cpp inter.cpp main.cpp melt.cpp model.cpp penmon.cpp ra.cpp
  radiation_ratio.cpp readb.cpp readclim.cpp readconf.cpp readinsoil.cpp readlai.cpp rs.cpp rsoil.cpp
  soil_constructor.cpp soil_temp.cpp soil_water_balance2.cpp soilresp.cpp soilwater_balance1.cpp StdAfx.cpp zcomp.cpp
        base_flow.cpp
)
