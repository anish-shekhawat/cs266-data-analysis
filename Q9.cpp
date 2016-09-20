#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>

using namespace std;

void main()
{
	int m, n, i;
	float input, ndupFactor = 1.0;
	char dupNomatch;

	cout << "\nEnter number of unique match scores: ";
	cin >> m;

	vector<float> match;

	cout << "\nEnter unique match scores: ";
	for (i = 0; i < m; i++)
	{
		cin >> input;
		match.push_back(input);
	}

	cout << "\nEnter number of unique nomatch scores: ";
	cin >> n;

	vector<float> nomatch;

	cout << "\nEnter unique nomatch scores: ";
	for (i = 0; i < n; i++)
	{
		cin >> input;
		nomatch.push_back(input);
	}

	cout << "\nDo you wish to duplicate the nomatch scores? (Y/N) ";
	cin >> dupNomatch;

	if (dupNomatch == 'y' || dupNomatch == 'Y')
	{
		cout << "\nEnter the duplication factor: ";
		cin >> ndupFactor;
	}

	// Sort both vectors
	sort(match.begin(), match.end());
	sort(nomatch.begin(), nomatch.end());

	
	float ctr = 0, mctr = 0, nctr = 0;
	float tnr, temp;

	vector<float> tpr;
	vector<float> fpr;
	vector<float> precision;

	//Calculate values for TPR and FPR
	while (mctr < match.size() && nctr < nomatch.size())
	{
		if (ctr == 0)
		{
			tpr.push_back(1);
			fpr.push_back(1);
			temp = (match.size() - mctr) + ((nomatch.size() - nctr) * ndupFactor);
			temp = (match.size() - mctr) / temp;
			precision.push_back(temp);
			ctr++;
		}
		else if (match.at((int)mctr) < nomatch.at((int)nctr))
		{
			mctr++;

			//TPR
			temp = (match.size() - mctr) / match.size();
			tpr.push_back(temp);
			
			//FPR
			tnr = nctr / nomatch.size();
			fpr.push_back(1 - tnr);

			//Precision
			if (match.size() == mctr && nomatch.size() == nctr)
			{
				temp = 0;
			}
			else 
			{
				temp = (match.size() - mctr) + ((nomatch.size() - nctr) * ndupFactor);
				temp = (match.size() - mctr) / temp;
			}
			precision.push_back(temp);
		}
		else if (nomatch.at((int)nctr) < match.at((int)mctr))
		{
			nctr++;

			//FPR
			tnr = nctr / nomatch.size();
			fpr.push_back(1 - tnr);

			//TPR
			temp = (match.size() - mctr) / match.size();
			tpr.push_back(temp);

			//Precision
			if (match.size() == mctr && nomatch.size() == nctr)
			{
				temp = 0;
			}
			else
			{
				temp = (match.size() - mctr) + ((nomatch.size() - nctr) * ndupFactor);
				temp = (match.size() - mctr) / temp;
			}
		
			precision.push_back(temp);

		}
	}

	while (mctr < match.size())
	{
		mctr++;

		//TPR
		temp = (match.size() - mctr) / match.size();
		tpr.push_back(temp);

		//FPR
		tnr = nctr / nomatch.size();
		fpr.push_back(1 - tnr);
		
		//Precision
		if (match.size() == mctr && nomatch.size() == nctr)
		{
			temp = 0;
		}
		else
		{
			temp = (match.size() - mctr) + ((nomatch.size() - nctr) * ndupFactor);
			temp = (match.size() - mctr) / temp;
		}

		precision.push_back(temp);
	}

	while (nctr < nomatch.size())
	{
		nctr++;

		//FPR
		tnr = nctr / nomatch.size();
		fpr.push_back(1 - tnr);
		
		//TPR
		temp = (match.size() - mctr) / match.size();
		tpr.push_back(temp);
		
		//Precision
		if (match.size() == mctr && nomatch.size() == nctr)
		{
			temp = 0;
		}
		else
		{
			temp = (match.size() - mctr) + ((nomatch.size() - nctr) * ndupFactor);
			temp = (match.size() - mctr) / temp;
		}

		precision.push_back(temp);
	} 

	cout << "FPR " << "--" << " TPR " << "--" << " Precision";

	for (i = 0; i < fpr.size(); i++)
	{
		cout << endl;
		cout << fpr[i] <<  " -- " << tpr[i] << " -- " << precision[i];
	}
	cout << endl;
}
