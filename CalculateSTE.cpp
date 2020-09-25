#include<iostream>
#include<string>
#include<fstream>
#include<vector>

#define W_SIZE 320
#define P_W_SIZE 320
#define SILENCE_STE 3000

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

					int sampleNumberWindow=0;
					int startPreciseW = sampleNumberWindow;
					int endPreciseW = sampleNumberWindow + 20;
					double meanSqPrecise=0;

					while(sampleNumberWindow < currWsize)
					{
						startPreciseW = sampleNumberWindow;
						endPreciseW = sampleNumberWindow + 20;
						meanSqPrecise=0;

						for(int i= startPreciseW; i<endPreciseW; i++)
						{
							meanSqPrecise += (WindowSamples[i]*WindowSamples[i])/20.0;
						}

						sampleNumberWindow += 20;

						if(meanSqPrecise<3000)
						{
							break;
						}

					}

					for(int i= 0; i<startPreciseW; i++)
					{
						outfile1 << WindowSamples[i] << endl;
					}


					/*for(int i=0;i<currWsize;i++)
					{
						outfile1 << WindowSamples[i] << endl;
					}*/

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

						//Refining data
					
						int sampleNumberWindow=0;
						int startPreciseW = sampleNumberWindow;
						int endPreciseW = sampleNumberWindow + 20;

						while(sampleNumberWindow < currWsize)
						{
							startPreciseW = sampleNumberWindow;
							endPreciseW = sampleNumberWindow + 20;
							double meanSqPrecise=0;

							for(int i= startPreciseW; i<endPreciseW; i++)
							{
								meanSqPrecise += (WindowSamples[i]*WindowSamples[i])/20.0;
							}

							sampleNumberWindow += 20;

							if(meanSqPrecise>3000)
							{
								break;
							}

						}

						for(int i= startPreciseW; i<currWsize; i++)
						{
							outfile1 << WindowSamples[i] << endl;
						}

						outfile<< "yes started" << endl;
						WordStarted=1;

						/*for(int i=0;i<currWsize;i++)
						{
							outfile1 << WindowSamples[i] << endl;
						}*/

					}
				}

				else
				{

					if(meanSqWindow<3000)
					{

						int sampleNumberWindow=0;
						int startPreciseW = sampleNumberWindow;
						int endPreciseW = sampleNumberWindow + 20;
						double meanSqPrecise=0;

						while(sampleNumberWindow < currWsize)
						{
							startPreciseW = sampleNumberWindow;
							endPreciseW = sampleNumberWindow + 20;
							meanSqPrecise=0;

							for(int i= startPreciseW; i<endPreciseW; i++)
							{
								meanSqPrecise += (WindowSamples[i]*WindowSamples[i])/20.0;
							}

							sampleNumberWindow += 20;

							if(meanSqPrecise<3000)
							{
								break;
							}

						}

						for(int i= 0; i<startPreciseW; i++)
						{
							outfile1 << WindowSamples[i] << endl;
						}

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