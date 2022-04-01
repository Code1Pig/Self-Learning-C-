#include "employee.h"

/*------------普通员工------------*/
  //构造函数
Employee :: Employee(int id, string name, int did)
{
    m_Id = id;
    m_Name = name;
    m_DeptId = did;
} 

//显示个人信息
void Employee::showInfo()
{
    cout << "职工编号:" << m_Id << "\t"
         << "职工姓名:" << m_Name << "\t"
         << "岗位:" << getDeptName()
         << "  岗位职责: 完成经理交给的任务" << endl;
}

string Employee :: getDeptName()
{
    return string("员工");
}

/*------------经理类------------*/
Manager :: Manager(int id, string name, int did)
{
    m_Id = id;
    m_Name = name;
    m_DeptId = did;
} 

//显示个人信息
void Manager::showInfo()
{
    cout << "职工编号:" << m_Id << "\t"
         << "职工姓名:" << m_Name << "\t"
         << "岗位:" << getDeptName()
         << "  岗位职责: 完成老板交的,下发员工任务" << endl;
}

string Manager :: getDeptName()
{
    return string("经理");
}

/*------------老板类------------*/
Boss :: Boss(int id, string name, int did)
{
    m_Id = id;
    m_Name = name;
    m_DeptId = did;
} 

//显示个人信息
void Boss::showInfo()
{
    cout << "职工编号:" << m_Id << "\t"
         << "职工姓名:" << m_Name << "\t"
         << "岗位:" << getDeptName()
         << "  岗位职责: 管理公司所有事务" << endl;
}

string Boss :: getDeptName()
{
    return string("老板");
}