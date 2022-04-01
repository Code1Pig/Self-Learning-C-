#pragma once
#include <iostream>
#include <fstream>
#include "worker.h"
#include "employee.h"
using namespace std;

#define FILENAME "D://CodePig//C++//Stage_2 C++ Core//empFile.txt"

class WorkerManager
{
public:
    WorkerManager();  //构造函数

    void ShowMenu();  //显示 菜单

    void ExitSystem(); //退出系统

    void Add_Emp();    //添加职工

    void saveFile();   //保存函数

    int get_EmpNum();  //统计文件中的人数

    void Init_Emp();   //初始化员工

    void Show_Emp();   //显示职工

    int IsExist(int id); //查找职工是否存在，存在返回位置，不存在返回-1
    void Del_Emp();    //删除职工

    void Mod_Emp();    //修改职工

    void Find_Emp();   //查找职工

    void Sort_Emp();   //排序职工

    void Clear_Emp();  //清空所有数据

    ~WorkerManager();  //析构函数


    int m_EmpNum;     //记录职工人数

    Worker ** m_EmpArray;  //职工数组指针

    bool m_FileIsEmpty;    //标志文件是否为空
};