#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#define ERROR_CODE_1    QString::fromLocal8Bit("设置文件路径错误：文件名称为空 ") 
// update [2/12/2023]
#define ERROR_CODE_2    QString::fromLocal8Bit("设置权重文件路径错误：没有找到权重文件夹 ") 
#define ERROR_CODE_3    QString::fromLocal8Bit("设置权重文件路径错误：没有找到权重文件 ") 
#define ERROR_CODE_4    QString::fromLocal8Bit("设置类别文件路径错误：没有找到类别文件夹 ") 
#define ERROR_CODE_5    QString::fromLocal8Bit("设的类别文件路径错误：没有找到类别文件 ") 
#define ERROR_CODE_6    QString::fromLocal8Bit("加载权重文件错误：没有找到权重文件 ") 
#define ERROR_CODE_7    QString::fromLocal8Bit("加载类别文件错误：没有找到类别名称文件 ") 
#define ERROR_CODE_8    QString::fromLocal8Bit("ONNX检测器加载失败 ") 
#define ERROR_CODE_9    QString::fromLocal8Bit("图片路径错误 ") 
#define ERROR_CODE_10    QString::fromLocal8Bit("创建项目文件夹失败 ") 

// 成功信息 [2/4/2023]
#define SUCCEED_CODE_1    QString::fromLocal8Bit("ONNX检测器初始化成功 ")
#define SUCCEED_CODE_2    QString::fromLocal8Bit("创建项目文件夹成功 ") 

#endif