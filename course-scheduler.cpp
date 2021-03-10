#include <iostream>
#include<fstream>
#include<string>
#include<vector>
#include <map>
#include<fstream>
#include <stdlib.h>
using namespace std;
typedef struct course course;
struct course
{
	string name;
	string number;
	string days[3];
	string hours[3];
	float begining_hours[3];
	float ending_hours[3];
	string overlap_days[3];
};

void read_file(map<string, string> &info , string address)
{
	ifstream file;
	string line, save;
	file.open(address, ios::in);
	while (!file.eof())
	{
		getline(file, line, ',');
		save = line;
		info.insert(pair<string, string>(line, ""));

		getline(file, line, '\n');
		info.find(save)->second = line;
	}

}

float begining_hour(string word)
{
	string save;
	for (int i = 0; i < 2; i++)
		save += word[i];
	if (word[3] == '0')
		return stof(save);
	return stof(save) + 0.5;
}
float ending_hour(string word)
{
	string save;
	for (int i = 6; i < 8; i++)
		save += word[i];
	if (word[9] == '0')
		return stof(save);
	return stof(save) + 0.5;
}

void input(vector<course>&v_course, map<string, string> info)
{
	string line;
	course get_input;
	while (getline(cin, line))
	{
		int i = 0;
		int j = 0;
		string word = "";
		while (line[i] != '-')
		{
			word += line[i];
			i++;
		}
		get_input.name =  info.find(word)->second;
		word = "";
		get_input.number = line[i + 2];
		for (j = i + 4; j < i + 7; j++)
			word += line[j];
		get_input.days[0] = word;
		word = "";
		for (j = i + 8; j < i + 19; j++)
			word += line[j];
		get_input.hours[0] = word;
		get_input.begining_hours[0] = begining_hour(word);
		get_input.ending_hours[0] = ending_hour(word);
		word = "";
		if (j < line.size())
		{
			for (j = i + 20; j < i + 23; j++)
				word += line[j];
			get_input.days[1] = word;
			word = "";

			for (j = i + 24; j < i + 35; j++)
				word += line[j];
			get_input.hours[1] = word;
			get_input.begining_hours[1] = begining_hour(word);
			get_input.ending_hours[1] = ending_hour(word);
			word = "";
		}
		else
		{
			get_input.days[1] = "";
			get_input.hours[1] = "";
			get_input.begining_hours[1] =0;
			get_input.ending_hours[1] =0;
			get_input.days[2] = "";
			get_input.hours[2] = "";

		}
		if (j < line.size())
		{
			for (j = i + 36; j < i + 39; j++)
				word += line[j];
			get_input.days[2] = word;
			word = "";
			for (j = i + 40; j < i + 51; j++)
				word += line[j];
			get_input.hours[2] = word;
			get_input.begining_hours[2] = begining_hour(word);
			get_input.ending_hours[2] = ending_hour(word);
		}
		else
		{
			get_input.days[2] = "";
			get_input.hours[2] = "";
			get_input.begining_hours[2] = 0;
			get_input.ending_hours[2] = 0;
		}
		get_input.overlap_days[0] = "";
		get_input.overlap_days[1] = "";
		get_input.overlap_days[2] = "";

		v_course.push_back(get_input);
	}
}

int overlap(course &a,course &b)
{
	int counter = 0,n=0;
			for(int k=0;k<3;k++)
				for(int m=0;m<3;m++)
					if (a.days[k] == b.days[m] && a.days[k] != "" && b.days[m] != "")
					{
						if (a.begining_hours[k] <= b.begining_hours[m] && b.begining_hours[m] < a.ending_hours[k])
						{
									a.overlap_days[0]= ( a.days[k]);
									b.overlap_days[0]= ( b.days[m]);

							counter++;
						}
						else if (a.begining_hours[k] >= b.begining_hours[m] && a.begining_hours[k] < b.ending_hours[m])
						{

							a.overlap_days[0] = (a.days[k]);
							b.overlap_days[0] = (b.days[m]);
							counter++;
						}
					}
	return counter;
}
int number_of_needed_overlaps(vector<course>&v_course)
{
	vector<course> save_1;
	vector<course> save_2;
	int sum = 0;
	int fault = 0;
	for (int i = 0; i < v_course.size(); i++)
		for (int j = i + 1; j < v_course.size(); j++)
			if (overlap(v_course[i], v_course[j]) != 0)
			{
				save_1.push_back(v_course[i]);
				save_2.push_back(v_course[j]);
				sum += overlap(v_course[i], v_course[j]);
			}
			
	for (int i = 0; i < save_1.size(); i++)
		for (int j = 0; j < save_2.size(); j++)
			if (i != j && save_1[i].overlap_days[0] == save_2[j].overlap_days[0] && save_1[i].overlap_days[0]!="" && save_2[j].overlap_days[0]!="")
				fault++;

	return sum-fault/2;
}
void find_the_days(vector<course>v_course,int week[])
{
	int day_counter = 0;
	for (int i = 0; i < v_course.size(); i++)
		for (int j = 0; j < 3; j++)
		{
			if (v_course[i].days[j] == "SUN")
				week[0] = 1;
			if (v_course[i].days[j] == "MON")
				week[1] = 1;
			if (v_course[i].days[j] == "TUE")
				week[2] = 1;
			if (v_course[i].days[j] == "WED")
				week[3] = 1;
			if (v_course[i].days[j] == "THU")
				week[4] = 1;
			if (v_course[i].days[j] == "FRI")
				week[5] = 1;
			if (v_course[i].days[j] == "SAT")
				week[6] = 1;
		}
}
int number_of_columns(vector<course>&v_course)
{
	int week[7] = { 0 };				
	int day_counter=0;
	int overlap = number_of_needed_overlaps(v_course);
	find_the_days(v_course, week);
	for (int k = 0; k < 7; k++)
		if (week[k] == 1)
			day_counter++;

	return 3 * (day_counter + overlap) + 37;
}
string print_line()
{
	string line;
	for (int i = 0; i < 275; i++)
		line += "_";
	return line;
}
string print_hour()
{
	string hour="";
	for (int i = 7; i < 10; i++)
		hour += "0" + to_string(i) + ":00     0" + to_string(i) + ":30     ";
	for (int i = 10; i < 20; i++)
		hour += to_string(i) + ":00     " + to_string(i) + ":30     ";
	hour += "20:00     20:30";
	return hour;
}
void print_the_course(vector<string> &column,vector<course> v_course,int i ,int j,int &row)
{
	int courselength, hourlength, distance, k;

	distance = (v_course[i].begining_hours[j] - 7) * 20 + 2;
	for (int k = 0; k < 273; k++)
	{
		column[row] += ' ';
		column[row+1] += ' ';
		column[row+2] += ' ';
	}

	column[row][distance] = '+';
	column[row+1][distance] = '|';
	column[row+2][distance] = '+';
	hourlength = (v_course[i].ending_hours[j] - v_course[i].begining_hours[j]) * 20 - 1;
	for (int k = distance + 1; k < distance + hourlength; k++)
	{
		column[row][k] = '-';
		column[row+2][k] = '-';
	}
	column[row][distance + hourlength] = '+';
	column[row+1][distance + hourlength] = '|';
	column[row+2][distance + hourlength] = '+';
	courselength = (hourlength - v_course[i].name.size() - 4) / 2;
	for (k = courselength + distance + 1; k < distance + courselength + v_course[i].name.size() + 1; k++)
		column[row+1][k] = v_course[i].name[k - distance - courselength - 1];
	column[row+1][k + 2] = '(';
	column[row+1][k + 3] = v_course[i].number[0];
	column[row+1][k + 4] = ')';
}
void print_the_day(vector<string> &column, vector<course> v_course,string day,string short_day,int &row)
{
	int first_row = row + 6;
	int second_row = row + 9;
	int third_row = row + 12;
	column[row + 2] += "## " + day;
	column[row + 4] += print_hour();
	column[row + 5] += print_line();
	row = row + 5;
	for (int i = 0; i < v_course.size(); i++)
		for (int j = 0; j < 3; j++)
		{
			if (v_course[i].days[j] == short_day&& v_course[i].overlap_days[0] != short_day)
			{
				print_the_course(column, v_course, i, j, first_row);
				row = first_row+1;
			}
			else if (v_course[i].days[j] == short_day&& v_course[i].overlap_days[0] == short_day)
			{
				if (row + 9 < 64) {
					if (column[row + 9].size() == 0)
					{
						print_the_course(column, v_course, i, j, second_row);
						row = second_row+4;
					}
					else
					{
						print_the_course(column, v_course, i, j, third_row);
						row = third_row+4;
					}
				}
			}
		}
	
}
void print_the_map(vector<course>v_course,string name)
{
	vector<string> column;
	int courselength, hourlength, distance, k,row=0;
	for (int i = 0; i < number_of_columns(v_course); i++)
		column.push_back("");
	int  row1=row + 1,row2=row + 2,row3=row + 3,row4=row + 4,row5=row + 5,row6=row + 6 ;
	column[row] += "# ";
	column[0] += name;
	print_the_day(column, v_course,"Saturday","SAT",row);
	print_the_day(column, v_course, "Sunday", "SUN", row);
	print_the_day(column, v_course, "Monday", "MON", row);
	print_the_day(column, v_course, "Tuesday", "TUE", row);
	print_the_day(column, v_course, "Wednesday", "WED", row);
	print_the_day(column, v_course, "Thursday", "THU", row);
	print_the_day(column, v_course, "Friday", "FRI", row);

	for (int i = 0; i < number_of_columns(v_course); i++)
		cout << column[i] << endl;

}
int main(int argc, char *argv[])
{
	vector<course>v_course;
	map<string, string> info;
	read_file(info, argv[1]);
	input(v_course, info);
	print_the_map(v_course,argv[2]);
	return 0;
}
