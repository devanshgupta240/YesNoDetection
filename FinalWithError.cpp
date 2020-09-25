#include<iostream>
#include<string>
#include<fstream>
#include<vector>

#define W_SIZE 320
#define P_W_SIZE 320
#define SILENCE_STE 5000

using namespace std;


bool ifYesOrNo(const vector<int> &word)
{
	long long int wordLength = word.size();

	long long int sampleNumberWindow = wordLength-1;
	long long int startW = sampleNumberWindow;
	long long int endW = sampleNumberWindow - 360;
	double meanSqW=0;

	while(sampleNumberWindow >= 0)
	{
		startW = sampleNumberWindow;
		endW = sampleNumberWindow - 360;
		meanSqW=0;

		for(long long int i= startW; i>endW; i--)
		{
			meanSqW += (word[i]*word[i])/360.0;
		}

		sampleNumberWindow -= 360;

		if(meanSqW>50000)
		{
			break;
		}
	}

	long long int startPreciseW = startW;
	long long int endPreciseW = startW - 100;
	int numPreciseW=0;
	double meanZCR =0;
	//double meanSqW=0;

	while(startW >= 0 && numPreciseW < 15)
	{
		startPreciseW = startW;
		endPreciseW = startW - 100;
		int preciseZCR=0;

		for(long long int i= startPreciseW; i>endPreciseW; i--)
		{
			if( (word[i]*word[i+1]) < 0)
			{
				preciseZCR++;
			}
		}
		meanZCR += preciseZCR/15.0;
		startW -= 100;
		numPreciseW++;
	}
	if(meanZCR>10)
	{
		return true;
	}
	else
	{
		return false;
	}
}


int main()
{
	ifstream infile;
	ofstream outfile;
	ofstream outfile1;
	ofstream outfile2;
	infile.open("sirs_yes_no.txt");
	outfile.open("outputMultipleYes.txt");
	outfile1.open("extractMultipleYes.txt");
	//outfile2.open("Result.txt");
	if(infile.is_open())
	{
		vector<int> word;
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
					int endPreciseW = sampleNumberWindow + 10;
					double meanSqPrecise=0;

					while(sampleNumberWindow < currWsize)
					{
						startPreciseW = sampleNumberWindow;
						endPreciseW = sampleNumberWindow + 10;
						meanSqPrecise=0;

						for(int i= startPreciseW; i<endPreciseW; i++)
						{
							meanSqPrecise += (WindowSamples[i]*WindowSamples[i])/10.0;
						}

						sampleNumberWindow += 10;

						if(meanSqPrecise<5000)
						{
							break;
						}

					}
					if(meanSqPrecise<5000)
					{
						for(int i= 0; i<startPreciseW; i++)
						{
							outfile1 << WindowSamples[i] << endl;
							word.push_back(WindowSamples[i]);
						}
					}
					else
					{
						for(int i= 0; i<currWsize; i++)
						{
							outfile1 << WindowSamples[i] << endl;
							word.push_back(WindowSamples[i]);
						}
						outfile << "last word incompletely recoreded" << endl;
					}


					/*for(int i=0;i<currWsize;i++)
					{
						outfile1 << WindowSamples[i] << endl;
					}*/
					word.clear();
					WordStarted=0;
					outfile<< "word ended" << endl;
				}

				break;
			}
			else
			{

				if(WordStarted==0)
				{

					if(meanSqWindow>5000)
					{
						//Refining data
					
						int sampleNumberWindow=0;
						int startPreciseW = sampleNumberWindow;
						int endPreciseW = sampleNumberWindow + 10;

						while(sampleNumberWindow < currWsize)
						{
							startPreciseW = sampleNumberWindow;
							endPreciseW = sampleNumberWindow + 10;
							double meanSqPrecise=0;

							for(int i= startPreciseW; i<endPreciseW; i++)
							{
								meanSqPrecise += (WindowSamples[i]*WindowSamples[i])/10.0;
							}

							sampleNumberWindow += 10;

							if(meanSqPrecise>5000)
							{
								break;
							}

						}

						for(int i= startPreciseW; i<currWsize; i++)
						{
							outfile1 << WindowSamples[i] << endl;
							word.push_back(WindowSamples[i]);
						}

						outfile<< "word started" << endl;
						WordStarted=1;

						/*for(int i=0;i<currWsize;i++)
						{
							outfile1 << WindowSamples[i] << endl;
						}*/

					}
				}

				else
				{

					if(meanSqWindow<5000)
					{

						int sampleNumberWindow=0;
						int startPreciseW = sampleNumberWindow;
						int endPreciseW = sampleNumberWindow + 10;
						double meanSqPrecise=0;

						while(sampleNumberWindow < currWsize)
						{
							startPreciseW = sampleNumberWindow;
							endPreciseW = sampleNumberWindow + 10;
							meanSqPrecise=0;

							for(int i= startPreciseW; i<endPreciseW; i++)
							{
								meanSqPrecise += (WindowSamples[i]*WindowSamples[i])/10.0;
							}

							sampleNumberWindow += 10;

							if(meanSqPrecise<5000)
							{
								break;
							}

						}

						for(int i= 0; i<startPreciseW; i++)
						{
							outfile1 << WindowSamples[i] << endl;
							word.push_back(WindowSamples[i]);
						}

						if(ifYesOrNo(word))
						{
							outfile << "Yes" << endl;
						}
						else
						{
							outfile << "No" << endl;
						}
						word.clear();
						outfile1 << endl;
						outfile1 << endl;
						outfile1 << endl;
						outfile1 << endl;
						WordStarted=0;
						outfile<< "word ended" << endl;

					}

					else
					{

						for(int i=0;i<currWsize;i++)
						{
							outfile1 << WindowSamples[i] << endl;
							word.push_back(WindowSamples[i]);
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
		//outfile2.close();

	}
	return 0;
}