#include "workerManager.h"

WorkerManager::WorkerManager()
{
	//1.文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //读文件
	
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
	
		//初始化属性
		m_EmpNum = 0;    //初始化记录人数
		m_EmpArray = NULL;  //初始化数组指针
		m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2.文件存在，数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空！"  << endl;
		
		//初始化属性
		m_EmpNum = 0;    //初始化记录人数
		m_EmpArray = NULL;  //初始化数组指针
		m_FileIsEmpty = true;
		ifs.close();
		return;		
	}

	//3.当文件存在，且有数据
	m_FileIsEmpty = false;
	ifs.close();

	int num = get_EmpNum();
	cout << "职工人数为：" << num << endl;
	m_EmpNum = num;
	//开辟空间
	m_EmpArray = new Worker*[m_EmpNum];
	//将文件中的数据，存到数组中
	Init_Emp();
}

// 菜单展示
void WorkerManager:: ShowMenu()
{   cout << "********************************************" << endl;
	cout << "*********** 欢迎使用职工管理系统！**********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;

}

// 退出系统 
void WorkerManager :: ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	exit(0);
}

void WorkerManager::Add_Emp()
{
	cout << "请输入添加职工的数量：" << endl;
	
	int addNum = 0;
	cin >> addNum;
	if (addNum <= 0)
	{
		cout << "输入有误！" << endl;
		return;
	}

	//添加
	//计算新空间的大小
	int newSize = m_EmpNum + addNum;
	
	//开辟新空间
	Worker ** newSpace = new Worker * [newSize];

	//将原来空间下的数据，拷贝到新的空间下
	if (m_EmpArray != NULL)
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			newSpace[i] = m_EmpArray[i];
		}
	}

	//批量添加新数据
	for (int i = 0; i < addNum; i++)
	{
		int id = 0;
		string name = "";
		int did = 0;
		
		while(true)
		{
			cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
			cin >> id;
			if (IsExist(id) != -1)
			{
				cout << "职工编号已被占用！" << endl;
			}
			else
			{
				break;
			}
		}
		
		cout << "请输入第" << i + 1 << "个新职工姓名：" << endl;
		cin >> name;
		cout << "请选择职工岗位：" << endl;
		cout << "1. 普通员工" << endl;
		cout << "2. 经理" << endl;
		cout << "3. 老板" << endl;
		cin >> did;

		Worker * worker = NULL;
		switch(did)
		{
		case 1:
		    worker = new Employee(id, name, did);
			break;
		case 2:
		    worker = new Manager(id, name, did);
			break;
		case 3:
		    worker = new Boss(id, name, did);
			break;
		default:
		    break;
		}
		newSpace[m_EmpNum + i] = worker;
	}
		//释放原空间
		delete[] m_EmpArray;
		
		//更改新空间指向
		m_EmpArray = newSpace;

		//更新职工人数
		m_EmpNum = newSize;

		//保存数据到文件中
		saveFile();

		//更新职工不为空标识
		m_FileIsEmpty = false;

		//提示添加成功
		cout << "成功添加" << addNum << "名新职工" << endl;
}

//保存函数
void WorkerManager::saveFile()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < m_EmpNum; ++i)
	{
		ofs << m_EmpArray[i]->m_Id << "\t"
		    << m_EmpArray[i]->m_Name << "\t"
			<< m_EmpArray[i]->m_DeptId << endl;
	}

	ofs.close();
}

int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int num = 0;
	while(ifs >> id && ifs >> name && ifs >> did)
	{
		num++;
	}

	ifs.close();     // 第一遍开始忘记了！！！
	return num;
}

void WorkerManager::Init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int Index = 0;
	while(ifs >> id && ifs >> name && ifs >> did)
	{
		Worker * worker = NULL;
		if (did == 1)
		{
			worker = new Employee(id, name, did);
		}
		else if (did == 2)
		{
			worker = new Manager(id, name, did);
		}
		else if (did == 3)
		{
			worker = new Boss(id, name, did);
		}

		m_EmpArray[Index] = worker;
		Index++;
	}

	ifs.close();
}

void WorkerManager::Show_Emp()
{
	//判断文件是否为空
	if (m_FileIsEmpty)
	{
		cout << "文件不存在！" << endl;
	}
	else if(0 == m_EmpNum)
	{
		cout << "记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; ++i)
		{
			m_EmpArray[i]->showInfo();
		}
	}
}

//查找职工是否存在，存在返回位置，不存在返回-1
int WorkerManager::IsExist(int id)
{
	int Index = -1;

	for (int i = 0; i < m_EmpNum; ++i)
	{
		if (m_EmpArray[i]->m_Id == id)
		{
			Index = i;
			break;
		}
	}

	return Index;
}

//删除职工
void WorkerManager::Del_Emp()
{
	if (m_FileIsEmpty)
	{
		cout << "文件不存在！" << endl;
	}
	else if(0 == m_EmpNum)
	{
		cout << "记录为空！" << endl;
	}
	else
	{
		cout << "请输入要删除的职工编号：" << endl;
		int id = 0;
		cin >> id;
		int flag = IsExist(id);
		if (flag == -1)
		{
			cout << "您输入的职工不存在！" << endl;
			return;
		}

		for (int i = flag; i < m_EmpNum - 1; ++i)
		{
			m_EmpArray[i] = m_EmpArray[i+1];
		}
		m_EmpNum--;
		saveFile();
		cout << "删除成功！" << endl;
	}
}

void WorkerManager::Mod_Emp()
{
	if (m_FileIsEmpty)
	{
		cout << "文件不存在！" << endl;
	}
	else if(0 == m_EmpNum)
	{
		cout << "记录为空！" << endl;
	}
	else
	{
		cout << "请输入要修改的职工编号：" << endl;
		int id = 0;
		cin >> id;
		int flag = IsExist(id);
		if (flag == -1)
		{
			cout << "您输入的职工不存在！" << endl;
			return;
		}

		delete m_EmpArray[flag];

		string name = "";
		int did = 0;
		
		cout << "查到第" << id << "号" << "职工" << endl;
		cout << "请输入新的职工编号：" << endl;
		cin >> id;
		cout << "请输入新的职工姓名：" << endl;
		cin >> name;
		cout << "请选择职工岗位：" << endl;
		cout << "1. 普通员工" << endl;
		cout << "2. 经理" << endl;
		cout << "3. 老板" << endl;
		cin >> did;

		Worker * worker = NULL;
		switch (did)
		{
		case 1:
			worker = new Employee(id, name, did);
			break;
		case 2:
			worker = new Manager(id, name, did);
			break;
		case 3:
			worker = new Boss(id, name, did);
			break;
		default:
			break;
		}

		m_EmpArray[flag] = worker;
		cout << "修改成功！" << endl;
		saveFile();
	}

}

void WorkerManager::Find_Emp()
{
	if (m_FileIsEmpty)
	{
		cout << "文件不存在！" << endl;
	}
	else if(0 == m_EmpNum)
	{
		cout << "记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找方式：" << endl;
		cout <<"1.按职工编号查找"  << endl;
		cout <<"2.按职工姓名查找"  << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			cout << "请输入要查找的职工编号：" << endl;
			int id = 0;
			cin >> id;

			int ret = IsExist(id);
			if (ret == -1)
			{
				cout << "查无此人！" << endl;
			}
			else
			{
				cout << "查找成功：该职工信息如下：" << endl;
				m_EmpArray[ret]->showInfo();
			}
		}
		else if (select == 2)
		{
			cout << "请输入要查找的姓名：" << endl;
			string name;
			cin >> name;

			bool flag = false;

			for (int i = 0; i < m_EmpNum; ++i)
			{
				if(m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功：该职工信息如下：" << endl;
					m_EmpArray[i]->showInfo();

					flag = true;
				}

			}
			if (flag == false)
			{
				cout << "查无此人！" << endl;
			}
		}
		else
		{
			cout << "输入有误！" << endl;
		}
	}
}

void WorkerManager::Sort_Emp()
{
	if (m_FileIsEmpty)
	{
		cout << "文件不存在！" << endl;
	}
	else if(0 == m_EmpNum)
	{
		cout << "记录为空！" << endl;
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1. 按职工号升序" << endl;
		cout << "2. 按职工号降序" << endl;

		int select = 0;
		cin >> select;

		for (int i = 0; i < m_EmpNum - 1; ++i)
		{
			int minOrmax = i;
			for (int j = i + 1; j < m_EmpNum; ++j)
			{
				if (select == 1)
				{
					if (m_EmpArray[minOrmax]->m_Id > m_EmpArray[j]->m_Id)
					{
						minOrmax = j;
					}
				}

				if (select == 2)
				{
					if (m_EmpArray[minOrmax]->m_Id < m_EmpArray[j]->m_Id)
					{
						minOrmax = j;
					}
				}
			}

			if (i != minOrmax)
			{
				Worker * temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrmax];
				m_EmpArray[minOrmax] = temp;
			}
		}

		cout << "排序成功！排序后的结果为：" << endl;
		saveFile();
		Show_Emp();
	}
}

void WorkerManager::Clear_Emp()
{
	cout << "确定清空文件数据？" << endl;
	cout << "1. 确定" << endl;
	cout << "2. 返回" << endl;
	int select = 0;
	cin >> select;

	if (1 == select)
	{
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);
		ofs.close();

		if (m_EmpArray != NULL)
	    {
			for (int i = 0; i < m_EmpNum; ++i)
			{
				if (m_EmpArray[i] != NULL)
				{
					delete m_EmpArray[i];
					m_EmpArray[i] = NULL;
				}
			}
			delete[] m_EmpArray;
			m_EmpArray = NULL;
			m_EmpNum = 0;
			m_FileIsEmpty = true;
	    }

		cout << "清空成功！" << endl;		
	}
}

WorkerManager::~WorkerManager()
{
	if (m_EmpArray != NULL)
	{
		for (int i = 0; i < m_EmpNum; ++i)
		{
			if (m_EmpArray[i] != NULL)
			{
				delete m_EmpArray[i];
				m_EmpArray[i] = NULL;
			}
		}
		delete[] m_EmpArray;
		m_EmpArray = NULL;
	}
}