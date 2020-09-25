#include<iostream>
#include<string>
#include<fstream>
#include<vector>

#define W_SIZE 320

using namespace std;

int main()
{
	ifstream infile;
	ofstream outfile;
	ofstream outfile1;
	infile.open("yesSample.txt");
	outfile.open("outputyes.txt");
	outfile1.open("extractYes.txt");
	if(infile.is_open())
	{
		int windowNumber=0;
		int WordStarted=0;
		while(!infile.eof())
		{
			double meanSqWindow=0;
			vector<double> WindowSamples;

			while(WindowSamples.size()<320 && !infile.eof())
			{
				int sampleValue;
				infile >> sampleValue;
				WindowSamples.push_back(sampleValue);
				meanSqWindow += (sampleValue*sampleValue)/320.0;
			}

			int currWsize = WindowSamples.size();
			if(currWsize<320)
			{
				if(WordStarted==1)
				{
					for(int i=0;i<currWsize;i++)
					{
						outfile1 << WindowSamples[i] << endl;
					}
					WordStarted=0;
					outfile<< "yes ended" << endl;
				}
				break;
			}
			else
			{
				if(WordStarted==0)
				{
					if(meanSqWindow>3000)
					{

						outfile<< "yes started" << endl;
						WordStarted=1;
						for(int i=0;i<currWsize;i++)
						{
							outfile1 << WindowSamples[i] << endl;
						}	
					}
				}
				else
				{
					if(meanSqWindow<3000)
					{
						WordStarted=0;
						outfile<< "yes ended" << endl;
					}
					else
					{
						for(int i=0;i<currWsize;i++)
						{
							outfile1 << WindowSamples[i] << endl;
						}
					}
				}
				windowNumber++;
				outfile << windowNumber << "th window:- " << meanSqWindow << endl;
				WindowSamples.clear();
			}
		}
		infile.close();
		outfile.close();
		outfile1.close();
	}
	return 0;
}