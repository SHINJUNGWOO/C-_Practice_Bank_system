#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#define NAME_SIZE 10
#define MAX 100
#define DATA_SIZE 4
using std::cout;
using std::cin;
using namespace std;


class data_set
{
private:
	unsigned int address = 0000;
	unsigned int password = 0000;
	
	int cash = 0000;
public:
	char name[NAME_SIZE] = "";
	int data_line = 0;
	int data_set::int_show(int command);
	void data_set::input(int command, int value);
	void data_set::input(char *_name);
	void data_set::input(string _name);
	void data_set::pop_all_data_set();
	int data_set::password_show();
};

int data_set::int_show(int command)
{
	switch (command)
	{
	case 0:
		return address;
		break;
	case 1:
		return cash;
	default:
		break;
	}
}

void data_set::input(int command, int value)
{
	switch (command)
	{
	case 0:
		address = value;
		break;
	case 1:
		cash = value;
		break;
	case 2:
		password = value;
		break;
	default:
		break;
	}
}

void data_set::input(char *_name)
{
	
	for (int i = 0;i<=NAME_SIZE; i++)
	{
		name[i] = _name[i];
	}
	
}

void data_set::input(string _name)
{

	for (int i = 0; i <= _name.size(); i++)
	{
		name[i] = _name[i];
	}

}

void data_set::pop_all_data_set(void)
{
	std::cout <<name<< std::endl;
	std::cout << address << std::endl;
	std::cout << cash << std::endl;
}

int data_set::password_show()
{
	return password;
}

void First_UI(data_set& test);
void Cash_Input_UI(data_set& object);
void Cash_Output_UI(data_set& object);
int selection();
void Make_Account(data_set& data);
bool Read_Acount(data_set& set);
void Change_Data(data_set& set);

int main()
{
	data_set set = data_set();
	
	int mode = 0;
	while (mode == 0)
	{
		bool address_correct = false;
		mode=selection();
		switch (mode)
		{
		case 1:
			Make_Account(set);
			mode = 0;
			break;
		case 2:
			
			if (Read_Acount(set) == true)
			{
				Cash_Input_UI(set);
				Change_Data(set);
			}
			else
			{
				system("cls");
				cout << "Name or PassWord Err" << endl;
			}
			break;
		case 3:

			if (Read_Acount(set) == true)
			{
				Cash_Output_UI(set);
				Change_Data(set);
			}
			else
			{
				system("cls");
				cout << "Name or PassWord Err" << endl;
			}
			break;
		case 4:

			if (Read_Acount(set) == true)
			{
				set.pop_all_data_set();
			}
			else
			{
				system("cls");
				cout << "Name or PassWord Err" << endl;
			}
			break;
		}
		mode = 0;
	}
	
}

int selection()
{
	int mode = 0;
	cout << "계좌 등록은 1" << std::endl;
	cout << "  돈 입금은 2" << std::endl;
	cout << "  돈 출금은 3" << std::endl;
	cout << "거래 조회는 4" << std::endl;
	cout << " 값을 입력해 주세요:";
	cin >> mode;
	if (mode < 1 || mode>4)
	{
		cout << "err" << std::endl;
		return 0;
	}
	return mode;
}

void Make_Account(data_set& set)
{
	
	First_UI(set);
	std::ofstream data_Input("address_data.txt", ios::app);
	data_Input << set.name << ',' << set.password_show() << ',' << set.int_show(0) << ',' << set.int_show(1) << endl;

	data_Input.close();
}

bool Read_Acount(data_set& set)
{
	system("cls");

	char finding_name[NAME_SIZE] = {};
	int finding_password = 0;
	//이름, 비밀번호의 변수 선언
	cin.ignore();
	cout << "이름을 입력해주세요:";
	cin.getline(finding_name, NAME_SIZE);
	cout << "비밀번호를 입력해 주세요:";
	cin >> finding_password;
	cin.ignore();

	//입력
	char read_data[MAX];


	ifstream read_file("address_data.txt");

	//버퍼 오픈
	bool correct_check = 0;
	for (int line_num=0;!read_file.eof();line_num++)
	{
		read_file.getline(read_data, MAX);
		string temp_data[DATA_SIZE];
		char *ptr = strtok(read_data, ",");
		//슬라이싱 한 문자열의 포인터를 반환
		for (int i=0;ptr != NULL;i++)
		{
			temp_data[i] = ptr;
			ptr = strtok(NULL, ",");
		}
		if (finding_name==temp_data[0]&&finding_password== atoi(temp_data[1].c_str()))
		{
			cout << "ok"<<endl;
			set.input(temp_data[0]);
			set.input(0, atoi(temp_data[2].c_str()));
			set.input(1, atoi(temp_data[3].c_str()));
			set.input(2, atoi(temp_data[1].c_str()));
			set.data_line = line_num;
			
			//0 address, 1 cash 2 password
			correct_check++;
			break;
		}
		else
		{
			correct_check = 0;
		}
		
	}
	
	read_file.close();
return correct_check;

}

void Change_Data(data_set& set)
{
	ifstream read_data("address_data.txt");
	char temp_name[MAX];
	string write_string;
	for(int i=0;!read_data.eof();i++)
	{
		
		read_data.getline(temp_name, MAX);
		if (i < set.data_line)
		{
			write_string.append(temp_name);
			write_string.append("\n");
		}
		else if (i == set.data_line)
		{
			char temp_send_data[MAX];
			sprintf(temp_send_data, "%s,%d,%d,%d", set.name, set.password_show(), set.int_show(0), set.int_show(1));
			write_string.append(temp_send_data);
			write_string.append("\n");
		}
		else
		{
			write_string.append(temp_name);
			write_string.append("\n");
		}
	}
	read_data.close();
	ofstream write_data("address_data.txt");
	write_data << write_string;
	write_data.close();
}

void First_UI(data_set& object)
{
	system("cls");
	unsigned int temp_address = 0;
	char temp_data[NAME_SIZE] = "";
	unsigned int password = 0;
	cout << "Input Address Number" << std::endl;
	cin >> temp_address;
	cout << "Input Name" << std::endl;
	cin.ignore();
	cin.getline(temp_data, 10);
	cout << "Input Password" << std::endl;
	cin >> password;
	object.input(0, temp_address);
	object.input(temp_data);
	object.input(2, password);

}

void Cash_Input_UI(data_set& object)
{
	system("cls");
	unsigned input_money = 0;
	cout << "입금할 돈을 넣어주세요" << std::endl;
	cin >> input_money;
	unsigned int left_money = object.int_show(1);
	object.input(1, (left_money + input_money));
}

void Cash_Output_UI(data_set& object)
{
	system("cls");
	unsigned output_money = 0;
	cout << "출금할 돈을 넣어주세요" << std::endl;
	cin >> output_money;
	unsigned int left_money = object.int_show(1);
	if ((left_money - output_money) < 0)
	{
		cout << "err" << std::endl;
	}
	else
	{
		object.input(1, output_money);
	}
}
