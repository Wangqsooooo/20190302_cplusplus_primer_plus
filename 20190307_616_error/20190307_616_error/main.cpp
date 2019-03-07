#include<iostream>
#include<cmath>
#include"exc_mean.h"

double hmean(double a, double b);
double gmean(double a, double b);

int main(void)
{
	double x, y, z;

	std::cout << "Enter two numbers: ";
	while (std::cin >> x >> y)
	{
		try
		{
			z = hmean(x, y);
			std::cout << "Harmonic mean of " << x << " and " << y
				<< " is " << z << std::endl;
			std::cout << "Geometric mean of " << x << " and " << y
				<< " is " << gmean(x, y) << std::endl;
			std::cout << "Enter next set of numbers <q to quit>: ";
		}
		catch (bad_hmean & bg)
		{
			bg.mesg();
			std::cout << "Try again.\n";
			continue;
		}
		catch (bad_gmean & hg)
		{
			std::cout << hg.mesg();
			std::cout << "Values used: " << hg.v1 << ", " << hg.v2 << std::endl;
			std::cout << "Sorry, you don't get to play any more.\n";
			break;
		}
	}
	if (std::cin.fail())
	{
		// 输入'q'退出时
		// 退出时给int型的x赋值了char型数据'q',failbit置1,导致之后的输入流均无法正常工作
		std::cin.clear();	// failbit清零,但是char型数据'q'仍然存在于输入流中清除
							// 会导致之后程序读入发生错误
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		// 清除当前行输入流,这之后输入能够正常工作
		std::cout << "test";
	}
	else
		std::cin.get();		// 非错误退出,从输入流中读入回车符,以免影响后面的输入流
	std::cout << "Bye!\n";

	std::cin.get();
	//system("pause");
	return 0;
}

double hmean(double a, double b)
{
	if (a == -b)
		throw bad_hmean(a, b);
	return 2.0 * a * b / (a + b);
}

double gmean(double a, double b)
{
	if (a < 0 || b < 0)
		throw bad_gmean(a, b);
	return std::sqrt(a*b);
}