#include "stdafx.h"
#include "BepsHydrScience.h"
#include "string.h"
#include "malloc.h"
#include "stdio.h"
#include "math.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream> // Added for std::istringstream
#include <iomanip>
#include <chrono>
#include <set>

// 全局变量 - 支持多层土壤水分观测数据
std::vector<std::vector<double>> g_observed_soil_moisture_layers;  // 每层一个向量
int g_obs_pixel_x = 43;  // 观测点X坐标（列索引）
int g_obs_pixel_y = 22;   // 观测点Y坐标（行索引）
int g_num_obs_layers = 4; // 观测土层数量
int g_num_model_layers = 5; // 模型土层数量
int g_calibration_iteration = 0; // 校正迭代次数
bool g_show_model_output = false; // 是否显示模型运行时的输出

// 观测层到模型层的映射（观测层索引 -> 模型层索引）
// 例如：观测的第0层对应模型的第0层，观测的第1层对应模型的第1层，等等
std::vector<int> g_layer_mapping = {0, 1, 2, 3}; // 默认映射：观测层0->模型层0, 观测层1->模型层1, ...



// 创建临时输出目录的函数
std::string createTempOutputDir(BH_SubParams1a_t* p1a) {
    std::string base_dir = std::string(p1a->szOutDirName);
    
    // 去除base_dir末尾的斜杠，避免双斜杠问题
    if (!base_dir.empty() && (base_dir.back() == '/' || base_dir.back() == '\\')) {
        base_dir.pop_back();
    }
    
    std::string temp_dir = base_dir + "/calibration_temp_" + std::to_string(g_calibration_iteration);
    
    // 创建目录（如果不存在）
    #ifdef _WIN32
    std::string mkdir_cmd = "mkdir \"" + temp_dir + "\" 2>nul";
    #else
    std::string mkdir_cmd = "mkdir -p \"" + temp_dir + "\" 2>/dev/null";
    #endif
    
    system(mkdir_cmd.c_str());
    
    // 创建子目录
    std::string soilwaterflux_dir = temp_dir + "/soilwaterflux";
    #ifdef _WIN32
    std::string mkdir_sub_cmd = "mkdir \"" + soilwaterflux_dir + "\" 2>nul";
    #else
    std::string mkdir_sub_cmd = "mkdir -p \"" + soilwaterflux_dir + "\" 2>/dev/null";
    #endif
    
    system(mkdir_sub_cmd.c_str());
    
    return temp_dir;
}

// 清理临时输出目录的函数
void cleanupTempOutputDir(const std::string& temp_dir) {
    #ifdef _WIN32
    std::string cleanup_cmd = "rmdir /s /q \"" + temp_dir + "\" 2>nul";
    #else
    std::string cleanup_cmd = "rm -rf \"" + temp_dir + "\" 2>/dev/null";
    #endif
    
    system(cleanup_cmd.c_str());
}

// 从二维矩阵中提取指定点的数据 - 修复坐标定位逻辑
std::vector<double> extractPointDataFromDailyFiles(const std::string& base_dir, 
                                                   int pixel_x, int pixel_y, 
                                                   int nlines, int npixels,
                                                   int layer = 0) {
    std::vector<double> point_data;
    
    // 检查坐标是否有效
    if (pixel_y < 0 || pixel_y >= nlines || pixel_x < 0 || pixel_x >= npixels) {
        printf("Error: Coordinates (%d, %d) out of range [0,%d] x [0,%d]\n", 
               pixel_x, pixel_y, npixels-1, nlines-1);
        return point_data;
    }
    
    // 检查土层索引是否有效
    if (layer < 0 || layer >= MAX_LAYERS) {
        printf("Error: Layer index %d out of range [0,%d]\n", layer, MAX_LAYERS-1);
        return point_data;
    }
    
    // BEPS模型每天生成一个文件：Soil_thetam1.bin, Soil_thetam2.bin, ..., Soil_thetam365.bin
    // 每个文件包含一天的完整数据：nlines * npixels * MAX_LAYERS个float值
    
    // 计算指定像素和土层在每天数据中的偏移量（字节）
    long long pixel_offset_in_daily = (static_cast<long long>(pixel_y) * npixels * MAX_LAYERS + 
                                      pixel_x * MAX_LAYERS + layer) * sizeof(float);
    
    // 读取每天的该点数据
    // 根据观测数据的天数来确定读取范围
    int max_days = 366; // 默认最大天数
    if (!g_observed_soil_moisture_layers.empty() && !g_observed_soil_moisture_layers[0].empty()) {
        max_days = g_observed_soil_moisture_layers[0].size();
        printf("Will read %d days based on observation data\n", max_days);
    }
    
    int failed_count = 0;
    for (int day = 1; day <= max_days; day++) {
        std::string daily_file = base_dir + "/soilwaterflux/Soil_thetam" + std::to_string(day) + ".bin";
        // printf("Trying to open file: %s\n", daily_file.c_str()); // 不再每次输出
        std::ifstream file(daily_file, std::ios::binary);
        if (!file.is_open()) {
            // printf("Cannot open file: %s\n", daily_file.c_str());
            failed_count++;
            continue; // 失败不再break，继续尝试后续天数
        }
        // 移动到指定像素和土层位置
        file.seekg(pixel_offset_in_daily, std::ios::beg);
        float value;
        if (file.read(reinterpret_cast<char*>(&value), sizeof(float))) {
            point_data.push_back(static_cast<double>(value));
        } else {
            printf("Warning: Failed to read data from day %d\n", day);
        }
        file.close();
    }
    if (failed_count > 0) {
        printf("读取失败的bin文件数：%d\n", failed_count);
    }
    
    printf("Extracted %zu days of data from daily files\n", point_data.size());
    printf("Observation point: (%d, %d), Layer: %d\n", pixel_x, pixel_y, layer);
    
    // 检查观测数据大小
    if (layer < g_observed_soil_moisture_layers.size()) {
        printf("Observation data size for layer %d: %zu\n", layer, g_observed_soil_moisture_layers[layer].size());
    }
    
    return point_data;
}

// 读取观测数据的函数 - 支持多层土壤水分数据
bool loadObservationData(const std::string& data_path) {
    try {
        // 初始化多层数据结构
        g_observed_soil_moisture_layers.clear();
        g_observed_soil_moisture_layers.resize(g_num_obs_layers);
        
        // 读取观测土壤水分数据
        std::ifstream sm_file(data_path);
        if (!sm_file.is_open()) {
            std::cout << "Error: Cannot open observation soil moisture file " << data_path  << std::endl;
            return false;
        }
        
        std::string line;
        int day_count = 0;
        int line_number = 0;
        
        // 读取文件，每行包含观测层数量的数据
        while (std::getline(sm_file, line)) {
            line_number++;
            
            // 跳过空行和注释行
            if (line.empty() || line[0] == '#') {
                printf("Skipping line %d (empty or comment)\n", line_number);
                continue;
            }
            
            // 去除行首行尾的空白字符
            line.erase(0, line.find_first_not_of(" \t\r\n"));
            line.erase(line.find_last_not_of(" \t\r\n") + 1);
            
            // 如果去除空白后为空，跳过
            if (line.empty()) {
                continue;
            }
            
            std::istringstream iss(line);
            double sm_value;
            int layer = 0;
            
            // 读取每行的观测层数据
            while (iss >> sm_value && layer < g_num_obs_layers) {
                g_observed_soil_moisture_layers[layer].push_back(sm_value);
                layer++;
            }
            
            // 检查是否所有层都有数据
            if (layer != g_num_obs_layers) {
                std::cout << "Warning: Line " << day_count + 1 << " data incomplete, expected " 
                          << g_num_obs_layers << " layers, actual " << layer << " layers" << std::endl;
                std::cout << "  Line content: " << line << std::endl;
            }
            
            day_count++;
        }
        
        sm_file.close();
        
        printf("Successfully loaded observation data:\n");
        printf("  Observation days: %d\n", day_count);
        printf("  Observation layers: %d\n", g_num_obs_layers);
        printf("  Model layers: %d\n", g_num_model_layers);
        for (int i = 0; i < g_num_obs_layers; i++) {
            printf("  Observation layer %d -> Model layer %d: %zu observations\n", 
                   i, g_layer_mapping[i], g_observed_soil_moisture_layers[i].size());
        }
        printf("  Observation point coordinates: (%d, %d)\n", g_obs_pixel_x, g_obs_pixel_y);
        
        return true;
    }
    catch (const std::exception& e) {
        std::cout << "Error reading observation data: " << e.what() << std::endl;
        return false;
    }
}

// 计算Nash-Sutcliffe效率系数
double calculateNashSutcliffe(const std::vector<double>& simulated, const std::vector<double>& observed) {
    int skip_days = 50;
    if (simulated.size() != observed.size() || simulated.empty()) {
        printf("Error: Data size mismatch or empty data\n");
        return -std::numeric_limits<double>::max();
    }
    if (simulated.size() <= skip_days) {
        printf("Error: Not enough days for NSE calculation after skipping first 50 days\n");
        return -9999.0;
    }
    double mean_obs = 0.0;
    int n = simulated.size() - skip_days;
    for (size_t i = skip_days; i < observed.size(); i++) {
        mean_obs += observed[i];
    }
    mean_obs /= n;
    double numerator = 0.0;
    double denominator = 0.0;
    for (size_t i = skip_days; i < simulated.size(); i++) {
        double diff_sim = simulated[i] - observed[i];
        double diff_mean = observed[i] - mean_obs;
        numerator += diff_sim * diff_sim;
        denominator += diff_mean * diff_mean;
    }
    if (denominator == 0.0) {
        return 0.0;
    }
    return 1.0 - (numerator / denominator);
}

// 目标函数 - 支持多层土壤水分（只使用有观测数据的层）
double objectiveFunction(const std::vector<std::vector<double>>& simulated_soil_moisture_layers) {
    if (g_observed_soil_moisture_layers.empty()) {
        std::cout << "Error: No observation soil moisture data" << std::endl;
        return -std::numeric_limits<double>::max();
    }
    
    // 计算有观测数据的层的综合NSE
    double total_nse = 0.0;
    int valid_layers = 0;
    
    for (int obs_layer = 0; obs_layer < g_num_obs_layers; obs_layer++) {
        int model_layer = g_layer_mapping[obs_layer]; // 获取对应的模型层
        
        try {
            if (model_layer < simulated_soil_moisture_layers.size() && 
                obs_layer < g_observed_soil_moisture_layers.size() &&
                !simulated_soil_moisture_layers[model_layer].empty() &&
                !g_observed_soil_moisture_layers[obs_layer].empty()) {
                
                double layer_nse = calculateNashSutcliffe(simulated_soil_moisture_layers[model_layer], 
                                                        g_observed_soil_moisture_layers[obs_layer]);
                total_nse += layer_nse;
                valid_layers++;
                
                printf("Observation layer %d(Model layer %d) NSE: %.4f\n", obs_layer, model_layer, layer_nse);
            } else {
                printf("Warning: Missing data for observation layer %d(model layer %d)\n", obs_layer, model_layer);
            }
        } catch (...) {
            printf("Error: Failed to calculate NSE for observation layer %d(model layer %d)\n", obs_layer, model_layer);
        }
    }
    
    if (valid_layers == 0) {
        std::cout << "Error: No valid layer data" << std::endl;
        return -std::numeric_limits<double>::max();
    }
    
    double average_nse = total_nse / valid_layers;
    printf("Average NSE: %.4f (based on %d layers)\n", average_nse, valid_layers);
    
    return average_nse;  // 返回平均NSE值，越接近1越好
}

// 运行模型并获取指定点的多层土壤水分输出
std::vector<std::vector<double>> runModelAndGetPointOutput(BH_SubParams1_t* p1, BH_SubParams1a_t* p1a, BH_SubParams2_t* p2) {
    // 从二维矩阵中提取指定点的多层土壤水分数据
    std::vector<std::vector<double>> simulated_layers;
    simulated_layers.resize(g_num_model_layers); // 提取所有模型层的数据
    
    // 运行BEPS模型
    try { 
        BepsHydrCalculate(p1, p1a, p2); 
    } catch (...) { 
        printf("Error: Exception during BEPS model execution\n");
        return simulated_layers;
    }
    
    // 使用原始输出目录中的文件
    std::string base_dir = std::string(p1a->szOutDirName);
    
    printf("Output directory: %s\n", base_dir.c_str());
    
    // 去除base_dir末尾的斜杠，避免双斜杠问题
    if (!base_dir.empty() && (base_dir.back() == '/' || base_dir.back() == '\\')) {
        base_dir.pop_back();
    }
    
    printf("Trying to read from directory: %s\n", base_dir.c_str());
    printf("Will read daily files: Soil_thetam1.bin to Soil_thetam365.bin\n");
    
    // 从p1中获取网格尺寸信息
    int nlines = p1->iNumLines;
    int npixels = p1->iNumPixels;
    
    printf("Grid dimensions: %d lines x %d pixels\n", nlines, npixels);
    printf("Observation point: (%d, %d)\n", g_obs_pixel_x, g_obs_pixel_y);
    
    for (int layer = 0; layer < g_num_model_layers; layer++) {
        try {
            simulated_layers[layer] = extractPointDataFromDailyFiles(base_dir, g_obs_pixel_x, g_obs_pixel_y, 
                                                                   nlines, npixels, layer);
        } catch (...) {
            printf("Error: Failed to extract data for layer %d\n", layer);
            simulated_layers[layer].clear(); // 清空该层数据
        }
    }
    
    return simulated_layers;
}

// 读取需要参与校准的参数名
std::set<std::string> loadEnabledCalibrationParams(const std::string& filename) {
    std::set<std::string> enabled_params;
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        printf("Warning: Cannot open calibration params file: %s\n", filename.c_str());
        return enabled_params;
    }
    std::string line;
    while (std::getline(infile, line)) {
        // 去除注释和首尾空格
        size_t sharp = line.find('#');
        if (sharp != std::string::npos) line = line.substr(0, sharp);
        // 去除首尾空格
        size_t first = line.find_first_not_of(" \t\r\n");
        size_t last = line.find_last_not_of(" \t\r\n");
        if (first == std::string::npos || last == std::string::npos) continue;
        std::string param = line.substr(first, last - first + 1);
        if (!param.empty()) enabled_params.insert(param);
    }
    return enabled_params;
}

// 参数校正函数 - 区分共用参数和分层参数
bool performParameterCalibration(BH_SubParams1_t* p1, BH_SubParams1a_t* p1a, BH_SubParams2_t* p2) {
    printf("\n=== Starting Multi-layer Soil Moisture Parameter Calibration ===\n");
    printf("Model layers: %d, Observation layers: %d\n", g_num_model_layers, g_num_obs_layers);
    // 读取参数名配置
    std::set<std::string> enabled_params = loadEnabledCalibrationParams("H:/summer_2025/try/BEPS_Terrainlab_region5.2/Data/calibration_params.txt");
    if (enabled_params.empty()) {
        printf("All Param will calibrate\n");
    } else {
        printf("only calibrate following Param: \n");
        for (const auto& p : enabled_params) printf("  %s\n", p.c_str());
    }
    
    // 重置迭代计数器
    g_calibration_iteration = 0;
    
    std::vector<CalibrationParam> params;
    
    // 只校准观测点使用的土壤质地类型 (Silty Loam, texture_idx = 4)
    const int target_texture_idx = 4;
    printf("Calibrating parameters for soil texture type %d (Silty Loam) only\n", target_texture_idx);
    
    // 1. 添加共用参数 (只针对目标质地类型)
    if (enabled_params.empty() || enabled_params.count("water_table_change_limit"))
        params.push_back({"water_table_change_limit", target_texture_idx, -1, 0.05, 0.01, 0.20, 0.02, false}); // 地下水位变化限制
    if (enabled_params.empty() || enabled_params.count("wilting_pt"))
        params.push_back({"wilting_pt", target_texture_idx, -1, 0.12, 0.10, 0.30, 0.05, false});     // 萎蔫点
    if (enabled_params.empty() || enabled_params.count("pore_index"))
        params.push_back({"pore_index", target_texture_idx, -1, 0.05, 0.01, 0.10, 0.01, false});     // 孔隙指数
    if (enabled_params.empty() || enabled_params.count("soil_K0H"))
        params.push_back({"soil_K0H", target_texture_idx, -1, 0.72, 0.05, 2.0, 0.1, false});       // 水平饱和导水率（共用参数，使用第一层值）
    
    // 2. 添加分层参数 (只对有观测数据的层，只针对目标质地类型)
    for (int obs_layer = 0; obs_layer < g_num_obs_layers; obs_layer++) {
        int model_layer = g_layer_mapping[obs_layer]; // 获取对应的模型层
        
        printf("Adding layered parameters for observation layer %d(model layer %d)...\n", obs_layer, model_layer);
        
        // 分层参数 - 只校正有观测数据的层，只针对目标质地类型
        if (enabled_params.empty() || enabled_params.count("soil_b"))
            params.push_back({"soil_b", target_texture_idx, model_layer, 5.0, 3.0, 8.0, 0.5, true});             // 土壤b参数
        if (enabled_params.empty() || enabled_params.count("suction_head"))
            params.push_back({"suction_head", target_texture_idx, model_layer, 0.1, 0.05, 0.3, 0.02, true});     // 吸力水头
        if (enabled_params.empty() || enabled_params.count("soil_K0"))
            params.push_back({"soil_K0", target_texture_idx, model_layer, 10.0, 1.0, 100.0, 5.0, true});         // 垂直饱和导水率
        if (enabled_params.empty() || enabled_params.count("field_cap"))
            params.push_back({"field_cap", target_texture_idx, model_layer, 0.25, 0.15, 0.35, 0.02, true});      // 田间持水量 - now layered
        if (enabled_params.empty() || enabled_params.count("porosity"))
            params.push_back({"porosity", target_texture_idx, model_layer, 0.45, 0.35, 0.55, 0.02, true});       // 孔隙度 - now layered
    }
    
    // 初始化参数值
    for (auto& param : params) {
        if (param.is_layered) {
            // 分层参数
            if (param.name == "soil_b") {
                param.current_value = p1->SoilTextureIndexVals[param.texture_idx].soil_b[param.layer_idx];
            } else if (param.name == "suction_head") {
                param.current_value = p1->SoilTextureIndexVals[param.texture_idx].suction_head[param.layer_idx];
            } else if (param.name == "soil_K0") {
                param.current_value = p1->SoilTextureIndexVals[param.texture_idx].soil_K0[param.layer_idx];
            } else if (param.name == "field_cap") {
                param.current_value = p1->SoilTextureIndexVals[param.texture_idx].field_cap[param.layer_idx];
            } else if (param.name == "porosity") {
                param.current_value = p1->SoilTextureIndexVals[param.texture_idx].porosity[param.layer_idx];
            }
        } else {
            // 共用参数
            if (param.name == "wilting_pt") {
                param.current_value = p1->SoilTextureIndexVals[param.texture_idx].wilting_pt;
            } else if (param.name == "pore_index") {
                param.current_value = p1->SoilTextureIndexVals[param.texture_idx].pore_index;
            } else if (param.name == "soil_K0H") {
                param.current_value = p1->SoilTextureIndexVals[param.texture_idx].soil_K0H[0];  // 使用第一层值
            } else if (param.name == "water_table_change_limit") {
                param.current_value = p1->SoilTextureIndexVals[param.texture_idx].water_table_change_limit;
            }
        }
    }
    
    double best_objective = -std::numeric_limits<double>::max();
    std::vector<double> best_params;
    
    // 简单的网格搜索
    printf("Starting grid search...\n");
    printf("Total parameters to calibrate: %zu\n", params.size());
    
    // 先校准共用参数
    for (auto& param : params) {
        if (!param.is_layered) {
            std::string param_type = "Shared parameter";
            printf("\nCalibrating parameter: %s (%s", param.name.c_str(), param_type.c_str());
            printf(", texture index %d", param.texture_idx);
            printf(")\n");
            
            printf("Parameter range: [%.3f, %.3f], step: %.3f\n", param.min_value, param.max_value, param.step);
            
            double best_param_value = param.current_value;
            int param_iterations = 0;
            
            for (double value = param.min_value; value <= param.max_value; value += param.step) {
                g_calibration_iteration++; // 增加迭代计数器
                param_iterations++;
                
                printf("  Iteration %d (parameter iteration %d): parameter value = %.3f", g_calibration_iteration, param_iterations, value);
                
                // 更新参数值
                if (param.name == "wilting_pt") {
                    p1->SoilTextureIndexVals[param.texture_idx].wilting_pt = static_cast<float>(value);
                } else if (param.name == "pore_index") {
                    p1->SoilTextureIndexVals[param.texture_idx].pore_index = static_cast<float>(value);
                } else if (param.name == "soil_K0H") {
                    // 将第一层的值更新到所有层
                    for (int layer = 0; layer < MAX_LAYERS; layer++) {
                        p1->SoilTextureIndexVals[param.texture_idx].soil_K0H[layer] = static_cast<float>(value);
                    }
                } else if (param.name == "water_table_change_limit") {
                    p1->SoilTextureIndexVals[param.texture_idx].water_table_change_limit = static_cast<float>(value);
                }
                
                // 运行模型并获取输出
                std::vector<std::vector<double>> simulated_soil_moisture_layers = runModelAndGetPointOutput(p1, p1a, p2);
                
                if (!simulated_soil_moisture_layers.empty()) {
                    // 计算目标函数值
                    double objective = objectiveFunction(simulated_soil_moisture_layers);
                    
                    printf(", average NSE: %.4f\n", objective);
                    
                    // 更新最佳参数
                    if (objective > best_objective) {
                        best_objective = objective;
                        best_param_value = value;
                        printf("    *** New best value! ***\n");
                    }
                    
                    // 保存当前参数到进度文件（每次迭代都保存）
                    saveCurrentBestParameters(p1, objective, param.name, value);
                } else {
                    printf(", error: Cannot get simulation data\n");
                    // 即使模型运行失败也要保存进度信息
                    saveCurrentBestParameters(p1, -9999.0, param.name, value);
                }
            }
            
            // 使用最佳参数值
            if (param.name == "wilting_pt") {
                p1->SoilTextureIndexVals[param.texture_idx].wilting_pt = static_cast<float>(best_param_value);
            } else if (param.name == "pore_index") {
                p1->SoilTextureIndexVals[param.texture_idx].pore_index = static_cast<float>(best_param_value);
            } else if (param.name == "soil_K0H") {
                // 将最佳值设置到所有层
                for (int layer = 0; layer < MAX_LAYERS; layer++) {
                    p1->SoilTextureIndexVals[param.texture_idx].soil_K0H[layer] = static_cast<float>(best_param_value);
                }
            } else if (param.name == "water_table_change_limit") {
                p1->SoilTextureIndexVals[param.texture_idx].water_table_change_limit = static_cast<float>(best_param_value);
            }
        }
    }
    
    // 然后逐层校准分层参数
    for (int obs_layer = 0; obs_layer < g_num_obs_layers; obs_layer++) {
        int model_layer = g_layer_mapping[obs_layer]; // 获取对应的模型层
        
        printf("\n=== Calibrating parameters for observation layer %d (model layer %d) ===\n", obs_layer, model_layer);
        
        // 找到该层对应的所有分层参数
        std::vector<CalibrationParam> layer_params;
        for (auto& param : params) {
            if (param.is_layered && param.layer_idx == model_layer) {
                layer_params.push_back(param);
            }
        }
        
        printf("Found %zu layered parameters for this layer\n", layer_params.size());
        
        // 对该层的每个参数进行校准
        for (auto& param : layer_params) {
            std::string param_type = "Layered parameter";
            printf("\nCalibrating parameter: %s (%s", param.name.c_str(), param_type.c_str());
            printf(", texture index %d, model layer %d", param.texture_idx, param.layer_idx);
            printf(", corresponding observation layer %d", obs_layer);
            printf(")\n");
            
            printf("Parameter range: [%.3f, %.3f], step: %.3f\n", param.min_value, param.max_value, param.step);
            
            double best_param_value = param.current_value;
            int param_iterations = 0;
            
            for (double value = param.min_value; value <= param.max_value; value += param.step) {
                g_calibration_iteration++; // 增加迭代计数器
                param_iterations++;
                
                printf("  Iteration %d (parameter iteration %d): parameter value = %.3f", g_calibration_iteration, param_iterations, value);
                
                // 更新参数值
                if (param.name == "soil_b") {
                    p1->SoilTextureIndexVals[param.texture_idx].soil_b[param.layer_idx] = static_cast<float>(value);
                } else if (param.name == "suction_head") {
                    p1->SoilTextureIndexVals[param.texture_idx].suction_head[param.layer_idx] = static_cast<float>(value);
                } else if (param.name == "soil_K0") {
                    p1->SoilTextureIndexVals[param.texture_idx].soil_K0[param.layer_idx] = static_cast<float>(value);
                } else if (param.name == "field_cap") {
                    p1->SoilTextureIndexVals[param.texture_idx].field_cap[param.layer_idx] = static_cast<float>(value);
                } else if (param.name == "porosity") {
                    p1->SoilTextureIndexVals[param.texture_idx].porosity[param.layer_idx] = static_cast<float>(value);
                }
                
                // 运行模型并获取输出
                std::vector<std::vector<double>> simulated_soil_moisture_layers = runModelAndGetPointOutput(p1, p1a, p2);
                
                if (!simulated_soil_moisture_layers.empty()) {
                    // 计算目标函数值
                    double objective = objectiveFunction(simulated_soil_moisture_layers);
                    
                    printf(", average NSE: %.4f\n", objective);
                    
                    // 更新最佳参数
                    if (objective > best_objective) {
                        best_objective = objective;
                        best_param_value = value;
                        printf("    *** New best value! ***\n");
                    }
                    
                    // 保存当前参数到进度文件（每次迭代都保存）
                    saveCurrentBestParameters(p1, objective, param.name, value);
                } else {
                    printf(", error: Cannot get simulation data\n");
                    // 即使模型运行失败也要保存进度信息
                    saveCurrentBestParameters(p1, -9999.0, param.name, value);
                }
            }
            
            // 使用最佳参数值
            if (param.name == "soil_b") {
                p1->SoilTextureIndexVals[param.texture_idx].soil_b[param.layer_idx] = static_cast<float>(best_param_value);
            } else if (param.name == "suction_head") {
                p1->SoilTextureIndexVals[param.texture_idx].suction_head[param.layer_idx] = static_cast<float>(best_param_value);
            } else if (param.name == "soil_K0") {
                p1->SoilTextureIndexVals[param.texture_idx].soil_K0[param.layer_idx] = static_cast<float>(best_param_value);
            } else if (param.name == "field_cap") {
                p1->SoilTextureIndexVals[param.texture_idx].field_cap[param.layer_idx] = static_cast<float>(best_param_value);
            } else if (param.name == "porosity") {
                p1->SoilTextureIndexVals[param.texture_idx].porosity[param.layer_idx] = static_cast<float>(best_param_value);
            }
        }
    }
    
    printf("\n=== Multi-layer Parameter Calibration Complete ===\n");
    printf("Total iterations: %d\n", g_calibration_iteration);
    printf("Final average NSE: %.4f\n", best_objective);
    printf("Note: All calibrated parameters apply to soil texture type %d (Silty Loam) only\n", target_texture_idx);
    
    // 保存最终校准结果到文件
    saveFinalCalibratedParameters(p1, best_objective);
    
    return true;
}

// 保存当前最佳参数到文件（增量写入）
void saveCurrentBestParameters(BH_SubParams1_t* p1, double current_nse, const std::string& param_name, double param_value) {
    std::string output_file = "H:/summer_2025/try/BEPS_Terrainlab_region5.2/Data/calibration_progress.txt";
    std::ofstream file(output_file, std::ios::app); // 追加模式
    
    if (!file.is_open()) {
        printf("Error: Cannot open calibration progress file %s\n", output_file.c_str());
        return;
    }
    
    // 写入当前迭代信息
    file << "Iteration " << g_calibration_iteration << ": ";
    file << "Parameter=" << param_name << ", Value=" << std::fixed << std::setprecision(6) << param_value;
    if (current_nse > -9999.0) {
        file << ", NSE=" << std::fixed << std::setprecision(4) << current_nse << "\n";
    } else {
        file << ", NSE=ERROR (model failed)\n";
    }
    
    file.close();
}

// 保存最终校准结果到文件
void saveFinalCalibratedParameters(BH_SubParams1_t* p1, double final_nse) {
    std::string output_file = "calibrated_parameters_final.txt";
    std::ofstream file(output_file);
    
    if (!file.is_open()) {
        printf("Error: Cannot create final calibration output file %s\n", output_file.c_str());
        return;
    }
    
    file << "=== BEPS Model Parameter Calibration Final Results ===\n";
    file << "Calibration completed at: " << std::chrono::system_clock::now().time_since_epoch().count() << "\n";
    file << "Final average NSE: " << std::fixed << std::setprecision(4) << final_nse << "\n";
    file << "Total calibration iterations: " << g_calibration_iteration << "\n";
    file << "Observation point: (" << g_obs_pixel_x << ", " << g_obs_pixel_y << ")\n";
    file << "Number of observation layers: " << g_num_obs_layers << "\n";
    file << "Number of model layers: " << g_num_model_layers << "\n\n";
    
    file << "=== Final Calibrated Parameters ===\n";
    file << "Soil texture types: " << SOIL_TEXTURE_INDECES << "\n\n";
    
    // 保存所有土壤质地类型的参数
    for (int texture_idx = 0; texture_idx < SOIL_TEXTURE_INDECES; texture_idx++) {
        file << "--- Texture Index " << texture_idx << " ---\n";
        
        // 共用参数
        file << "Shared parameters:\n";
        file << "  wilting_pt: " << p1->SoilTextureIndexVals[texture_idx].wilting_pt << "\n";
        file << "  pore_index: " << p1->SoilTextureIndexVals[texture_idx].pore_index << "\n";
        file << "  soil_K0H: " << p1->SoilTextureIndexVals[texture_idx].soil_K0H[0] << " (applied to all layers)\n";
        file << "  water_table_change_limit: " << p1->SoilTextureIndexVals[texture_idx].water_table_change_limit << "\n";
        
        // 分层参数
        file << "Layered parameters:\n";
        for (int layer = 0; layer < MAX_LAYERS; layer++) {
            file << "  Layer " << layer << ":\n";
            file << "    soil_b: " << p1->SoilTextureIndexVals[texture_idx].soil_b[layer] << "\n";
            file << "    suction_head: " << p1->SoilTextureIndexVals[texture_idx].suction_head[layer] << "\n";
            file << "    soil_K0: " << p1->SoilTextureIndexVals[texture_idx].soil_K0[layer] << "\n";
            file << "    field_cap: " << p1->SoilTextureIndexVals[texture_idx].field_cap[layer] << "\n";
            file << "    porosity: " << p1->SoilTextureIndexVals[texture_idx].porosity[layer] << "\n";
        }
        file << "\n";
    }
    
    file << "=== Layer Mapping ===\n";
    file << "Observation layer -> Model layer mapping:\n";
    for (int i = 0; i < g_num_obs_layers; i++) {
        file << "  Obs layer " << i << " -> Model layer " << g_layer_mapping[i] << "\n";
    }
    
    file.close();
    printf("Final calibration results saved to: %s\n", output_file.c_str());
}

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

    // 直接设置参数（不使用命令行）
    bool enable_calibration = true;  // 启用参数校正
    // std::string config_file = "H:/summer_2025/config0/BTLrun_SanMing_12.5m_2021.con";
    std::string config_file = "H:/summer_2025/config0/BTLrun_Col_250m_2008.con";
    std::string data_path = "H:/summer_2025/try/BEPS_Terrainlab_region5.2/Data/observed_soil_moisture.txt";

    // 读取配置文件
    readconf(const_cast<char*>(config_file.c_str()), &BH_SubParams1, &BH_SubParams1a, &BH_SubParams2, &rcode);
    
    // 如果启用校准，先加载观测数据
    if (enable_calibration) {
        printf("Parameter calibration mode enabled\n");
        
        if (!loadObservationData(data_path)) {
            printf("Error: Cannot load observation data, exiting calibration mode\n");
            enable_calibration = false;
        }
    }

    // 执行气候计算
    if (BH_SubParams1.bCalculateClimate == 0 || BH_SubParams1.bCalculateClimate == 2)
    {
        printf("----------Step 2: Climate Calculation ---------\n\n");
        ClimateCalculate(&BH_SubParams1, &BH_SubParams1a);
        printf("----------End--------\n\n");
    }

    // 如果启用校准，执行参数校准
    if (enable_calibration) {
        if (!performParameterCalibration(&BH_SubParams1, &BH_SubParams1a, &BH_SubParams2)) {
            printf("Parameter calibration failed, continuing with original parameters\n");
        }
    }

    // 执行BEPS模型计算
    if (BH_SubParams1.bCalculateClimate == 1 || BH_SubParams1.bCalculateClimate == 2)
    {
        printf("----------Step 3: BTL Main --------\n\n");
        BepsHydrCalculate(&BH_SubParams1, &BH_SubParams1a, &BH_SubParams2);
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