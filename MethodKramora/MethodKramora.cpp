// MethodKramora.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>

#include<stdio.h>
#include<windows.h>

#define print std::cout <<

#define R_SUCCESS 0
#define R_DET_ZERO 1
#define R_ERROR -1

int Parse(std::string _array[3], int(*_result)[4][3][3])
{
	int numbers[3][4];
	try {
		for (int i = 0; i < 3; i++)
		{
			_array[i] += 'x';
			_array[i].erase(remove_if(_array[i].begin(), _array[i].end(), isspace), _array[i].end());
		}

		for (int i = 0; i < 3; i++)
		{
			int currentNum = 0;
			std::string number = "";

			for (unsigned int j = 0; j < _array[i].length(); j++)
			{
				if (_array[i][j] == '=')
					continue;
				else if ((j == 0 && (_array[i][j] == 'x' || _array[i][j] == 'y' || _array[i][j] == 'z')) ||
					((number.length() <= 1 && (_array[i][j] == 'x' || _array[i][j] == 'y' || _array[i][j] == 'z') && (number.length() == 1 && (number[0] == '+' || number[0] == '-')))))
					number += "1";
				else if (_array[i][j] != 'x' && _array[i][j] != 'z' && _array[i][j] != 'y')
					number += _array[i][j];

				if (_array[i][j] == 'x' || _array[i][j] == 'z' || _array[i][j] == 'y')
				{
					int num = std::stoi(number);
					numbers[i][currentNum] = num;
					number = "";

					currentNum++;
				}
			}
		}
	}
	catch (std::exception ex) {
		return R_ERROR;
	}

	{
		(*_result)[0][0][0] = numbers[0][0];
		(*_result)[0][0][1] = numbers[0][1];
		(*_result)[0][0][2] = numbers[0][2];

		(*_result)[0][1][0] = numbers[1][0];
		(*_result)[0][1][1] = numbers[1][1];
		(*_result)[0][1][2] = numbers[1][2];

		(*_result)[0][2][0] = numbers[2][0];
		(*_result)[0][2][1] = numbers[2][1];
		(*_result)[0][2][2] = numbers[2][2];
	}

	{
		(*_result)[1][0][0] = numbers[0][3];
		(*_result)[1][0][1] = numbers[0][1];
		(*_result)[1][0][2] = numbers[0][2];

		(*_result)[1][1][0] = numbers[1][3];
		(*_result)[1][1][1] = numbers[1][1];
		(*_result)[1][1][2] = numbers[1][2];

		(*_result)[1][2][0] = numbers[2][3];
		(*_result)[1][2][1] = numbers[2][1];
		(*_result)[1][2][2] = numbers[2][2];
	}

	{
		(*_result)[2][0][0] = numbers[0][0];
		(*_result)[2][0][1] = numbers[0][3];
		(*_result)[2][0][2] = numbers[0][2];

		(*_result)[2][1][0] = numbers[1][0];
		(*_result)[2][1][1] = numbers[1][3];
		(*_result)[2][1][2] = numbers[1][2];

		(*_result)[2][2][0] = numbers[2][0];
		(*_result)[2][2][1] = numbers[2][3];
		(*_result)[2][2][2] = numbers[2][2];
	}

	{
		(*_result)[3][0][0] = numbers[0][0];
		(*_result)[3][0][1] = numbers[0][1];
		(*_result)[3][0][2] = numbers[0][3];

		(*_result)[3][1][0] = numbers[1][0];
		(*_result)[3][1][1] = numbers[1][1];
		(*_result)[3][1][2] = numbers[1][3];

		(*_result)[3][2][0] = numbers[2][0];
		(*_result)[3][2][1] = numbers[2][1];
		(*_result)[3][2][2] = numbers[2][3];
	}

	return R_SUCCESS;
}

void Print(std::string _array[3], int(*_matrix)[4][3][3], double (*_nums)[4], double(*_result)[3])
{
	for (int j = 0; j < 4; j++) {
		std::string lines[3];
		if (j != 0) {
			lines[0] += "          | ";
			lines[1] += "Delta " + std::to_string(j) + " = | ";
			lines[2] += "          | ";
		}
		else {
			lines[0] += "          | ";
			lines[1] += "Delta   = | ";
			lines[2] += "          | ";
		}

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				lines[y] += std::to_string((*_matrix)[j][y][x]) + " ";
			}

			int len = 0;
			for (int y = 0; y < 3; y++)
			{
				if (lines[y].length() > len)
					len = lines[y].length();
			}

			for (int y = 0; y < 3; y++)
			{
				while (lines[y].length() < len)
				{
					lines[y] += " ";
				}
			}
		}

		for (int i = 0; i < 3; i++)
			lines[i] += "|";

		lines[1] += " = " + std::to_string((*_nums)[j]);

		for (int i = 0; i < 3; i++)
			print lines[i] << "\n";
		print "\n";
	}
	print "\n";

	std::string sym[3];
	sym[0] = 'x';
	sym[1] = 'y';
	sym[2] = 'z';


	for (int r = 0; r < 3; r++) {
		std::string to_print[3];

		to_print[0] += "      ";
		to_print[1] += " " + sym[r] + " = -";
		to_print[2] += "      ";
		to_print[0] += std::to_string((*_nums)[r + 1]);
		to_print[2] += std::to_string((*_nums)[0]);

		int len = 0;
		for (int i = 0; i < 3; i++)
			if (to_print[i].length() > len)
				len = to_print[i].length();

		while (to_print[1].length() < len)
			to_print[1] += "-";
		to_print[1] += "- = ";
		to_print[1] += std::to_string((*_result)[r]);

		for (int i = 0; i < 3; i++)
			print to_print[i] << "\n";
		print "\n";
	}
}

int Calculate(std::string _array[3], double (*_result)[3]) 
{
	int buffer[4][3][3];
	int(*buffer_items)[4][3][3] = &buffer;
	int error;

	error = Parse(_array, buffer_items);
	if (error == R_ERROR)
		return R_ERROR;

	double divideBy;
	double nums[4];
	double(*nums_buffer)[4] = &nums;

	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			divideBy =
				buffer[i][0][0] * buffer[i][1][1] * buffer[i][2][2] +
				buffer[i][0][1] * buffer[i][1][2] * buffer[i][2][0] +
				buffer[i][0][2] * buffer[i][1][0] * buffer[i][2][1] -
				buffer[i][0][2] * buffer[i][1][1] * buffer[i][2][0] -
				buffer[i][0][1] * buffer[i][1][0] * buffer[i][2][2] -
				buffer[i][0][0] * buffer[i][1][2] * buffer[i][2][1];
			nums[i] = divideBy;
			if (divideBy == 0)
				return R_DET_ZERO;
		}
		else 
		{
			double num_ =
				(buffer[i][0][0] * buffer[i][1][1] * buffer[i][2][2] +
				buffer[i][0][1] * buffer[i][1][2] * buffer[i][2][0] +
				buffer[i][0][2] * buffer[i][1][0] * buffer[i][2][1] -
				buffer[i][0][2] * buffer[i][1][1] * buffer[i][2][0] -
				buffer[i][0][1] * buffer[i][1][0] * buffer[i][2][2] -
				buffer[i][0][0] * buffer[i][1][2] * buffer[i][2][1]);
			(*_result)[i - 1] = num_ / divideBy;
			nums[i] = num_;
		}
	}

	Print(_array, buffer_items, nums_buffer, _result);

	return R_SUCCESS;
}

int main()
{

	double result[3];
	std::string args[3];

	//args[0] = "2x+5y+4z=30";
	//args[1] = "x+3y+2z=150";
	//args[2] = "2x+10y+9z=110";
	//int res = Calculate(args, &result);

	//return 0;
	while (true) {
		for (int i = 0; i < 3; i++)
		{
			print "Āāåäčņå " << i + 1 << "-óž ńņšīźó (xyz): ";
			std::cin >> args[i];
			print "\n";
		}

		int res = Calculate(args, &result);
		if (res == R_ERROR) {
			print "Īųčįźą, āāåäčņå źīššåźņķūå äąķķūå";
		}
		else if (res == R_SUCCESS) {
			print ">> x1 = " << result[0] << "\n";
			print ">> x2 = " << result[1] << "\n";
			print ">> x3 = " << result[2] << "\n";
		}
		else if (res == R_DET_ZERO) {
			print "Šåēóėüņąņ:\n";
			print ">> Äåņåšģčķąķņ ģąņščöū šąāåķ 0, šåųåķč˙ ķåņ";
		}

		print "\n\n";
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
