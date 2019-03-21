#include<iostream>
#include<cmath>
#include<string>
#include"exc_mean.h"

class demo
{
private:
	std::string word;

public:
	demo(const std::string & str)
	{
		word = str;
		std::cout << "demo " << word << " created\n";
	}
	~demo()
	{
		std::cout << "demo " << word << " destroyed\n";
	}

	void show() const
	{
		std::cout << "demo " << word << " lives!\n";
	}
};

double hmean(double a, double b);
double gmean(double a, double b);
double means(double a, double b);

int main(void)
{
	double x, y, z;
	{
		demo d1("found in block in main()");

		std::cout << "Enter two numbers: ";
		while (std::cin >> x >> y)
		{
			try
			{
				z = means(x, y);
				std::cout << "The mean mean of " << x << " and " << "y"
					<< " is " << z << std::endl;
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
		d1.show();
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

double means(double a, double b)
{
	double am, hm, gm;
	demo d2("found in means() ");
	am = (a + b) / 2.0;
	try
	{
		hm = hmean(a, b);
		gm = gmean(a, b);
	}
	catch (bad_hmean & bg)
	{
		bg.mesg();
		std::cout << "Caught in means()\n";
		throw;
	}
	d2.show();
	return (am + hm + gm) / 3.0;
}