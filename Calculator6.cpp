#include <iostream>
#include <stack>
#include <windows.h> 
using namespace std;

struct lexema //in order to set flex meanings for stacks
{
	char type; //0  for integers, + - * / for operands
	double value; //meaning, 0 for operations
};

bool operational_LOGIC(stack <lexema>& stack_Integers, stack <lexema>& stack_Operations, lexema& item) // links to stacks
{
	double top_of_stack, second_of_stack, summary_result, minory_result, power_result, divide_result;
	top_of_stack = stack_Integers.top().value; //top point for int
	stack_Integers.pop();//delete top num from stack 

	switch (stack_Operations.top().type) //top point for operation
	{
	case '+':
		second_of_stack = stack_Integers.top().value;
		stack_Integers.pop();//delete used num from stack
		summary_result = top_of_stack + second_of_stack;
		item.type = '0';
		item.value = summary_result;
		stack_Integers.push(item); //put summ result back to stack	
		stack_Operations.pop(); //delete used operation
		break;

	case '-':
		second_of_stack = stack_Integers.top().value;
		stack_Integers.pop();//delete used num from stack
		minory_result = second_of_stack - top_of_stack; //for minory and divide operations FIRST comes second num
		item.type = '0';
		item.value = minory_result;
		stack_Integers.push(item); //put minory result back to stack
		stack_Operations.pop();//delete used operation
		break;

	case '*':
		second_of_stack = stack_Integers.top().value;
		stack_Integers.pop();//delete used num from stack
		power_result = top_of_stack * second_of_stack;
		item.type = '0';
		item.value = power_result;
		stack_Integers.push(item); //put powering result back to stack
		stack_Operations.pop();//delete used operation
		break;

	case '/':
		second_of_stack = stack_Integers.top().value;
		if (top_of_stack == 0) {
			cerr << "\nError\n";
			return false;
		}
		else {
			stack_Integers.pop();//delete used num from stack
			divide_result = second_of_stack / top_of_stack;
			item.type = '0';
			item.value = divide_result;
			stack_Integers.push(item); //put divide result back to stack
			stack_Operations.pop(); //delete used operation
			break;
		}
	default:
		
		cout << "\nError\n";
		return false;
	}
	return true;
}

int get_priorityRank(char some_symbol)
{
	if (some_symbol == '+' || some_symbol == '-') return 1;
	if (some_symbol == '*' || some_symbol == '/') return 2;
	else return 0;
}

void gotoxy(int x, int y) //coords to place dialog with Bender
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void print_BenderMENU()
{
	cout << "	 * **\n";
	cout << "	 *__*\n";
	cout << "	 *__*\n";
	cout << "	 *__* \n";
	cout << "	 *__*\n";
	cout << "      **_ *_**\n";
	cout << "    *__***__***\n";
	cout << "   **___*******__*\n";
	cout << "   *_______________*\n";
	cout << "  *_________________*\n";
	cout << "  *_________________*\n";
	cout << "  *_____***************\n";
	cout << "  *____*_______________*\n";
	cout << "  *   *   *************\n";
	cout << "  *___*___*___________***\n";
	cout << "  *___*___*_***___***__**\n";
	cout << "  *___*___*_***___***__**\n";
	cout << "  *___*___*___________***\n";
	cout << "  *____*___*************\n";
	cout << "  *_____***************\n";
	cout << "  *_________________*\n";
	cout << "  *____***************\n";
	cout << "  *___*__*__*__*__*\n";
	cout << "  *__**************\n";
	cout << "  *__*___*__*__*__*\n";
	cout << "  *___***************\n";
	cout << "  ***_______________***\n"<< endl;
	gotoxy(40, 11);
	cout << "Hello, u Skin bag!" << endl;
	gotoxy(40, 14);
	cout << "Welcome to ASK BENDER prgrm!" << endl;
	gotoxy(40, 16);
	cout << "I give u chance to get the answer for any expression." << endl;
	gotoxy(40, 18);
	cout << "U can use any common operation, like + - * / and even ( )." << endl;
	gotoxy(40, 19);
	cout << "Negative numbers are included. Go ahead!" << endl;
	gotoxy(40, 21);
}

int main()
{
	

		print_BenderMENU();

		char some_symbol; //current operating symbol
		double value; // to get the whole number
		bool flag = 1; //if -detected with an integer (not as an operation, operation's flag =0)
		stack <lexema> stack_integers;
		stack <lexema> stack_operations;
		lexema item; //type for elents of steck, object
		while (1) {
			some_symbol = cin.peek();

		//		gotoxy(40, 23);
		//		cout << some_symbol << " " << endl;    //CHECKPOINT FOR OBVIOUS MISTAKES: SHOWS HOW SYMBOLS ARE READING

			if (some_symbol == '\n') break; //if the last element of string reached
			if (some_symbol == ' ') //if SPACE found in expression it would be ignored and not causing error, otherwise prgrm err
			{
				cin.ignore();
				continue;
			}
			if (some_symbol > '0' && some_symbol < '9' || some_symbol == '-' && flag == 1) //for integers: if prgrm detects symbol with flag =1 and - is keeps it as -integer
			{
				cin >> value;
				item.type = '0';
				item.value = value;
				stack_integers.push(item); //place integer to stack
				flag = 0;
				continue;
			}
			if (some_symbol == '+' || some_symbol == '-' && flag == 0 || some_symbol == '*' || some_symbol == '/') //for operations
			{
				if (stack_operations.size() == 0)
				{
					item.type = some_symbol;
					item.value = 0;
					stack_operations.push(item);
					cin.ignore();//1 symbol will be ignored
					continue;
				}
				if (stack_operations.size() != 0 && get_priorityRank(some_symbol) > get_priorityRank(stack_operations.top().type))
				{
					item.type = some_symbol;
					item.value = 0;
					stack_operations.push(item);
					cin.ignore();//1 symbol will be ignored
					continue;
				}
				if (stack_operations.size() != 0 && get_priorityRank(some_symbol) <= get_priorityRank(stack_operations.top().type))
				{
					if (operational_LOGIC(stack_integers, stack_operations, item) == false) //if smth goes wrong, system stops
					{
						system("pause");
						return 0;
					}
					continue;
				}
			}
			if (some_symbol == '(')
			{
				item.type = some_symbol;
				item.value = 0;
				stack_operations.push(item);
				cin.ignore();//1 symbol will be ignored
				continue;
			}
			if (some_symbol == ')')
			{
				while (stack_operations.top().type != '(')
				{
					if (operational_LOGIC(stack_integers, stack_operations, item) == false) //if smth goes wrong, system stops
					{
						system("pause");
						return 0;
					}
					else continue;
				}
				stack_operations.pop();
				cin.ignore();
				continue;
			}
			else
			{
				gotoxy(40, 23);
				cout << "What the hell ?! i sad COMMON opertions! i don't get ur abracadabra!";
				gotoxy(40, 25);
				cout << "Cya Skin bag!\n\n\n";
				system("pause");
				return 0;
			}
		}
		while (stack_operations.size() != 0)
		{
			if (operational_LOGIC(stack_integers, stack_operations, item) == false) //if smth goes wrong, system stops
			{
				system("pause");
				return 0;
			}
			else continue;
		}

		gotoxy(40, 23);
		cout << "answer: " << stack_integers.top().value << endl;
		gotoxy(40, 25);
		cout << "That's too easy! Give me complicated expression next time!" << endl;
		gotoxy(40, 26);
		cout << "Cya, Skin bag!" << endl << endl;
		gotoxy(40, 27);
//	Sleep(5000);
//	system("cls");
	return 0;
	
}

