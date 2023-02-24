#include <iostream>
#include <stack>
#include <windows.h> //включает функции WinAPI sleep(), beep() и т.д

using namespace std;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

struct lexema //in order to set flex meanings for stacks
{
	char type; //0  for integers, + - * / for operands
	double value; //meaning, 0 for operations
};

bool operating(stack <lexema>& stack_Integers, stack <lexema>& stack_Operations, lexema& item) //tranlating ssylki to stacks
{
	double top_of_stack, second_of_stack, summary_result, minory_result, power_result, divide_result;
	top_of_stack = stack_Integers.top().value; //top point for int
	stack_Integers.pop();//delete top num from stack 

	switch (stack_Operations.top().type) //top point for operation
	{
	case '+':
		second_of_stack = stack_Integers.top().value;
		stack_Integers.pop();//delete 2nd num from 
		summary_result = top_of_stack + second_of_stack;
		item.type = '0';
		item.value = summary_result;
		stack_Integers.push(item); //put summ result back to stack	
		stack_Operations.pop(); //delete used operation
		break;

	case '-':
		second_of_stack = stack_Integers.top().value;
		stack_Integers.pop();//delete 2nd num from stack
		minory_result = second_of_stack - top_of_stack; //for minory and divide operations FIRST comes second num
		item.type = '0';
		item.value = minory_result;
		stack_Integers.push(item); //put minory result back to stack
		stack_Operations.pop();//delete used operation
		break;

	case '*':
		second_of_stack = stack_Integers.top().value;
		stack_Integers.pop();//delete 2nd num from 
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
			stack_Integers.pop();//delete 2nd num from 
			divide_result = second_of_stack / top_of_stack;
			item.type = '0';
			item.value = divide_result;
			stack_Integers.push(item); //put divide result back to stack
			stack_Operations.pop(); //delete used operation
			break;
		}
	default:
		cerr << "\nError\n";
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

void SetCursor(int x, int y) //функция для того чтобы устанавливать позицию курсора в консоли по оси Х и Y
{
	COORD myCoords = { x,y }; //инициализация координат
	SetConsoleCursorPosition(hStdOut, myCoords); //Способ перемещения курсора на нужные координаты
}

void print_Bender()
{
	SetCursor(24, 12);
	cout << "Hello, u skin bag!\nWelcome to ASK BENDER prgrm!\n";
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
	
}

int main()
{
	print_Bender();

	char some_symbol; //current operating symbol
	double value; // to get the whole number
	bool flag = 1; //if -detected with an integer (not as an operation, operation's flag =0)
	stack <lexema> stack_integers;
	stack <lexema> stack_operations;
	lexema item; //type for elents of steck, object
	while (1) {
		some_symbol = cin.peek();

	//	cout << some_symbol << endl;    //CHECKPOINT FOR OBVIOUS MISTAKES: SHOWS HOW SYMBOLS ARE READING

		if (some_symbol == '\n') break; //if the last element of string reached
		if (some_symbol == ' ') //if SPACE found in expression it ignores and not causing error, otherwise prgrm err
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
				if (operating(stack_integers, stack_operations, item) == false) //if smth goes wrong, system stops
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
				if (operating(stack_integers, stack_operations, item) == false) //if smth goes wrong, system stops
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
			cout << "Incorrect expression\n";
			system("pause");
			return 0;
		}
	}
	while (stack_operations.size() != 0)
	{
		if (operating(stack_integers, stack_operations, item) == false) //if smth goes wrong, system stops
		{
			system("pause");
			return 0;
		}
		else continue;
	}
	cout << "answer: " << stack_integers.top().value << endl;
	return 0;
}

