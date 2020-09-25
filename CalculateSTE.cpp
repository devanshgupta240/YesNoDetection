#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

int main()
{
	/*ofstream myfile;
	myfile.open ("OutputSilence.txt");
	myfile << "Writing this to a file.\n";
	myfile.close();*/
	ifstream infile;
	ofstream outfile;
	ofstream outfile1;
	infile.open("yesSample.txt");
	outfile.open("outputyes.txt");
	outfile1.open("extractYes.txt");
	if(infile.is_open())
	{
		cout << "entered file" <<endl;
		int sn=0;
		int flag=0;
		while(!infile.eof())
		{
			int no=0;
			double sumsq=0;
			//double si=0;
			vector<double> vec;
			while(no<320 && !infile.eof())
			{
				int a;
				infile >> a;
				vec.push_back(a);
				sumsq += (a*a)/320.0;
				no++;
			}
			if(no<320)
			{
				if(flag==1)
				{
					for(int a=0;a<vec.size();a++)
					{
						outfile1 << vec[a] << endl;
					}
					flag=0;
					outfile<< "yes ended" << endl;
				}
				break;
			}
			else
			{
				if(flag==0)
				{
					if(sumsq>3000)
					{
						//int a=0;
						/*int tempsize=vec.size();
						int starti=0;
						int endi =0;
						while(a<tempsize)
						{
							double hsumsq = 0;
							starti =a;
							endi = a+20;
							for(int b=starti;b<endi;b++)
							{
								hsumsq += vec[b]*vec[b];
							}
							a += 20;
							if(hsumsq>3000)
							{
								break;
							}
						}*/
						outfile<< "yes started" << endl;
						/*while(starti<tempsize)
						{
							outfile1 << vec[starti] << endl;
							starti++;
						}*/
						flag=1;
						for(int a=0;a<vec.size();a++)
						{
							outfile1 << vec[a] << endl;
						}	
					}
				}
				else
				{
					if(sumsq<3000)
					{
						flag=0;
						outfile<< "yes ended" << endl;
					}
					else
					{
						for(int a=0;a<vec.size();a++)
						{
							outfile1 << vec[a] << endl;
						}
					}
				}
				sn++;
				outfile << sn << "th window:- " << sumsq << endl;
				//si += 320;
				vec.clear();
			}
		}
		infile.close();
		outfile.close();
		outfile1.close();
	}
	return 0;
}