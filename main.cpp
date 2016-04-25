#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <map>
#include <vector>
#include <ctime>
#include <stdlib.h>
//#include <windows.h>

using namespace std;
//const int ERROR_RANGE = 8;
//const int COUNT_RANGE = 15;


inline  int string2int(std::string s)
{
    int n = atoi(s.c_str());
	return n;
}

inline float string2float(std::string str)
{
	float result = atof(str.c_str());
	return result;
}


inline long string2long(std::string str)
{
   long result = atol(str.c_str());
   return result;
}


inline void cutstring(std::string s ,int a[])
{
	std::string flag = ":";
	std::string::size_type position=0;
	int i=0;
	while((position=s.find_first_of(flag,position)) != std::string::npos)
	{
		//	  std::cout<< "position  " << i << " : " << position << std::endl;
		a[i] = position;
		position++;
		i++;
	}
}

//const int ERROR_RANGE = 8;
//const int COUNT_RANGE = 15;
double Solve(int ERROR_RANGE, int COUNT_RANGE,std::string filename)//¶¯Ì¬¹æ»®Æ¥Åä
{
	int TTTTT = 0;
	ifstream xsens;
	ifstream laser;
	std::map<string , string> recorder;

	clock_t start , finish;
	// xsens.open("D:\\1448246245-Xsnes.txt");
	// laser.open("D:\\test.txt");
	//laser.open("D:\\binding\\1460536243-laser.txt");
	//xsens.open("D:\\binding\\1460536243-Xsnes.txt");

	laser.open((filename + "-laser.txt").c_str());
	xsens.open((filename + "-Xsnes.txt").c_str());


	if (laser.is_open() && xsens.is_open())
	{
		start = clock();
		string str;
		vector<string> log;

		while ( getline(laser,str) )
		{
			if (str.find("x86isnice") != std::string::npos)
			{
				string xx;
				getline(laser,str);
				int laser_signal[5] = {0};
				cutstring(str,laser_signal);
				int laser_result = string2int(str.substr(laser_signal[1]+5,laser_signal[2] - laser_signal[1] - 5));//@@@@@@@@@@@@@@@@@@@@
				//	int laser_result = string2int(str.substr(laser_signal[1]+4,laser_signal[2] - laser_signal[1] - 5));
				int xsens_signal[10] = {0};
				int xsens_result = 0;
				int count = 0;

				bool flag = 0;

				if ( !log.empty() )
				{
					for (vector<string>::iterator it = log.begin(); it != log.end(); it++)
					{
						cutstring(*it ,xsens_signal);
						xsens_result = string2int(it->substr( 4, 10));
						if ( abs(laser_result - xsens_result) <= ERROR_RANGE)
						{
							recorder.insert(pair<string,string>(str.substr(laser_signal[1]+1,laser_signal[2] - laser_signal[1] - 1), it->substr(0,13)));
							flag = 1;
							break;
						}
					}
					if ( flag == 1)
					{
						//	  log.clear();
						//	  vector<string>().swap(log);

						vector<string>::iterator it = log.begin();
						//while (it != log.end() && it->compare(xx.substr(0,13)) < 0)
						while (it != log.end() && it->compare(str.substr(laser_signal[1]+1,laser_signal[2] - laser_signal[1] - 1)) < 0)
							it = log.erase(it);
					}
				}

				if ( flag == 0 )
				{
					bool tag = 0;
					do
					{
						count++;

						getline( xsens, xx);

						if ( xx == "")
						{
							tag = 1;
							break;
						}

						cutstring( xx, xsens_signal);
						log.push_back(xx.substr(0,13));

						xsens_result = string2int(xx.substr( 4, 10));
					} while (abs(laser_result - xsens_result) > ERROR_RANGE  && !xsens.eof() && count < COUNT_RANGE);

					//	if (count < COUNT_RANGE )
					if (count < COUNT_RANGE && tag != 1)
					{
						//while (it != log.end() && it->compare(xx.substr(0,13)) < 0)
						vector<string>::iterator it = log.begin();
						while (it != log.end() && it->compare(str.substr(laser_signal[1]+1,laser_signal[2] - laser_signal[1] - 1)) < 0)
							it = log.erase(it);

						recorder.insert(pair<string,string>(str.substr(laser_signal[1]+1,laser_signal[2] - laser_signal[1] - 1), xx.substr(0,13)));
					}
					else
					{
						TTTTT++;
						recorder.insert(pair<string,string>(str.substr(laser_signal[1]+1,laser_signal[2] - laser_signal[1] - 1),"ERROR"));
					}
				}
				str.clear();
			}
			else
			{
				str.clear();
				continue;
			}
		}

	}
	else
	{
		std::cerr << "one of the file is not Open ,please check!" << endl;
		exit(EXIT_FAILURE);
	}

	laser.close();
	xsens.close();
	/*
	for (map<string,string>::iterator it = recorder.begin(); it != recorder.end(); it++)
	{
		std::cout << it->first << " <--> " << it->second<< endl;
	}
	*/
	finish = clock();
	cout <<"recorder.size()::"<< recorder.size()<<"   "<<"命中率" <<static_cast<double>(recorder.size() - TTTTT)/recorder.size() <<"  The Cost Of Time is:"<<finish - start<<" ms"<<endl;

	return (static_cast<double>(recorder.size() - TTTTT)/recorder.size());
}

int main()
{
  std::multimap<int,int>logt;
  std::vector<string> file_list;
  /*file_list.push_back("/home/x86isnice/Music/binding/1460535439");
  file_list.push_back("/home/x86isnice/Music/binding/1460535517");
  file_list.push_back("/home/x86isnice/Music/binding/1460535985");
  file_list.push_back("/home/x86isnice/Music/binding/1460536091");
  file_list.push_back("/home/x86isnice/Music/binding/1460536175");
  file_list.push_back("/home/x86isnice/Music/binding/1460536243");
  file_list.push_back("/home/x86isnice/Music/binding/1460537201");
  file_list.push_back("/home/x86isnice/Music/binding/1460537278");
  file_list.push_back("/home/x86isnice/Music/binding/1460537373");
*/
/*
  file_list.push_back("/home/x86isnice/Music/binding1/1453367107");
  file_list.push_back("/home/x86isnice/Music/binding1/1453367176");
  file_list.push_back("/home/x86isnice/Music/binding1/1453367246");
  file_list.push_back("/home/x86isnice/Music/binding1/1453367339");
  file_list.push_back("/home/x86isnice/Music/binding1/1453367436");
  file_list.push_back("/home/x86isnice/Music/binding1/1453367901");
  file_list.push_back("/home/x86isnice/Music/binding1/1453367962");
*/
    file_list.push_back("/home/x86isnice/Music/binding2/1460959128");
    file_list.push_back("/home/x86isnice/Music/binding2/1460959214");
    file_list.push_back("/home/x86isnice/Music/binding2/1460959324");
    file_list.push_back("/home/x86isnice/Music/binding2/1460959367");
    file_list.push_back("/home/x86isnice/Music/binding2/1460959493");
    file_list.push_back("/home/x86isnice/Music/binding2/1460959534");
    file_list.push_back("/home/x86isnice/Music/binding2/1460959569");
    file_list.push_back("/home/x86isnice/Music/binding2/1460959622");
    file_list.push_back("/home/x86isnice/Music/binding2/1460959686");
    file_list.push_back("/home/x86isnice/Music/binding2/1460959786");
    file_list.push_back("/home/x86isnice/Music/binding2/1460959826");
    file_list.push_back("/home/x86isnice/Music/binding2/1460959890");
    file_list.push_back("/home/x86isnice/Music/binding2/1460960065");
    file_list.push_back("/home/x86isnice/Music/binding2/1460960165");
    file_list.push_back("/home/x86isnice/Music/binding2/1460960206");
    file_list.push_back("/home/x86isnice/Music/binding2/1460960273");
    file_list.push_back("/home/x86isnice/Music/binding2/1460960363");
    file_list.push_back("/home/x86isnice/Music/binding2/1460960482");

  logt.insert(std::pair<int,int>(2,5));
  logt.insert(std::pair<int,int>(3,5));
  logt.insert(std::pair<int,int>(5,5));
  logt.insert(std::pair<int,int>(2,10));
  logt.insert(std::pair<int,int>(3,10));
  logt.insert(std::pair<int,int>(5,10));
  logt.insert(std::pair<int,int>(8,10));
  logt.insert(std::pair<int,int>(5,15));
  logt.insert(std::pair<int,int>(8,15));
  logt.insert(std::pair<int,int>(10,15));
  logt.insert(std::pair<int,int>(8,20));
  logt.insert(std::pair<int,int>(10,20));
  logt.insert(std::pair<int,int>(15,20));
  logt.insert(std::pair<int,int>(20,20));

  std::cout << logt.size()<<"  "<<file_list.size() << std::endl;
  //std::cout << "    ";
  for (std::multimap<int,int>::iterator it  = logt.begin(); it != logt.end(); it++)
  {
      std::cout << it->first<<"/"<<it->second << ",";
  }
std::cout << "\n";

  for (std::vector<string>::iterator loc = file_list.begin(); loc != file_list.end(); loc++ )
  {
     // std::cout << *loc << ":";
      for (std::multimap<int,int>::iterator it  = logt.begin(); it != logt.end(); it++)
      {
         // std::cout << it->first <<","<<it->second << ":";
            std::cout << Solve(it->first, it->second,*loc)<< ",";
      }
      std::cout <<"\n";
  }
 return 0;
}
