#include <iostream>
#include <string>

using namespace std;

#define MAX 1000

typedef struct
{
    string m_Name;
    int m_Sex;
    int m_Age;
    string m_Phone;
    string m_Addr;
} Person;

typedef struct
{
    Person personArray[MAX];
    int m_Size;
} AddressLists;

//显示主菜单
void showMenu()
{
    cout << "**********************************" << endl;
    cout << "*****  1. Add a new person   *****" << endl;
    cout << "*****  2. Print all persons  *****" << endl;
    cout << "*****  3. Delete one person  *****" << endl;
    cout << "*****  4. Sesearch for one   *****" << endl;
    cout << "*****  5. Modify one person  *****" << endl;
    cout << "*****  6. Clear all persons  *****" << endl;
    cout << "*****  0. Exit the Lists     *****" << endl;
    cout << "**********************************" << endl;
}

void writePerson(AddressLists *als, int num)
{
    //姓名
    cout << "Please input name : " << endl;
    string name;
    cin >> name;
    als->personArray[num].m_Name = name;

    //性别
    cout << "Please input gender : " << endl;
    cout << "1 --- Male " << endl;
    cout << "2 --- Female " << endl;
    int sex = 0;
    while (true)
    {
        cin >> sex;
        if (sex == 1 || sex == 2)
        {
            als->personArray[num].m_Sex = sex;
            break;
        }
        cout << "No Valid Input, Do it again! " << endl;
        cin.clear();
        cin.sync();
    }

    //年龄
    cout << "Please input age : " << endl;
    int age;
    while (true)
    {
        cin >> age;
        if (age > 0 && age < 120)
        {
            als->personArray[num].m_Age = age;
            break;
        }
        cout << "No Valid Input, Do it again! " << endl;
        cin.clear();
        cin.sync();
    }

    //电话
    cout << "Please input Phone number : " << endl;
    string phone;
    cin >> phone;
    als->personArray[num].m_Phone = phone;

    //地址
    cout << "Please input the Address : " << endl;
    string address;
    cin >> address;
    als->personArray[num].m_Addr = address;
}

//添加联系人
void addPerson(AddressLists * als)
{
    if (als->m_Size >= MAX)
    {
        cout << "Can not add! Lists are FULL!" << endl;
        return;
    }
    
    writePerson(als, als->m_Size);
    als->m_Size++;
    cout << "Added Success !" << endl;
     system("pause");
     system("cls");
}


void showOnePerson(AddressLists * als, int i)
{
    cout << "Name:" << als->personArray[i].m_Name << "\t"
                 << "Gender:" << (als->personArray[i].m_Sex == 1 ? "Male" : "FeMale") << "\t"
                 << "Age:" << als->personArray[i].m_Age << "\t"
                 << "Phone:" << als->personArray[i].m_Phone << "\t"
                 << "Address:" << als->personArray[i].m_Addr << endl;
}


void showPerson(AddressLists * als)
{
    if (als->m_Size == 0)
    {
        cout << " Empty Lists! " << endl;
    }
    else
    {
        for (int i = 0; i < als->m_Size; i++)
            showOnePerson(als, i);           
    }
}

//查找输入的联系人是否存在
int isExist(AddressLists * als, string name)
{
    for (int i = 0; i < als->m_Size; ++i)
    {
        if(als->personArray[i].m_Name == name)
            return i;
    }
    return -1;
}

//删除一个联系人
void deletePerson(AddressLists * als)
{
    cout << "Please input the person's name to delete : " << endl;
    string name;
    cin >> name;
    int flag = isExist(als, name);
    if (-1 == flag)
    {
        cout << "Not Found!" << endl;
        return;
    }
    for (int i = flag; i < als->m_Size - 1; ++i)
    {
        als->personArray[i] = als->personArray[i+1];
    }
    als->m_Size--;
    cout << "Success delete the person " << name << endl;
     system("pause");
     system("cls");
}

//查找一个联系人
void findPerson(AddressLists *pals)
{
    cout << "Please input the person's name you find :" << endl;
    string name;
    cin >> name;
    int flag = isExist(pals, name);
    if (-1 == flag)
    {
        cout << "Not Found!" << endl;
        return;
    }
    showOnePerson(pals, flag);
     system("pause");
     system("cls");
}

//修改指定的联系人信息
void modifyPerson(AddressLists * pals)
{
    cout << "Please input the person's name you modify :" << endl;
    string name;
    cin >> name;
    int flag = isExist(pals, name);
    if (-1 == flag)
    {
        cout << "Not Found!" << endl;
        return;
    }
    
    writePerson(pals, flag);
     system("pause");
     system("cls");
}

//清空通讯录
void clearLists(AddressLists * pals)
{
    pals->m_Size = 0;
    cout << "Clear Done!" << endl;
     system("pause");
     system("cls");
}

int main()
{
    AddressLists als;
    als.m_Size = 0;

    int select = 0;

    while (true)
    {
        showMenu();

        cin >> select;

        switch (select)
        {
            case 1:
                addPerson(&als);
                break;
            case 2:
                showPerson(&als);
                break;
            case 3:
                deletePerson(&als);
                break;
            case 4:
                findPerson(&als);
                break;
            case 5:
                modifyPerson(&als);
                break;
            case 6:
                clearLists(&als);
                break;
            case 0:
                cout << "See you nest time!" << endl;
                return 0;
            default:
                break;          
        }
    }

    return 0;
}