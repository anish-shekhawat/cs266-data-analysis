#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>

using namespace std;

void main()
{
	int m, n, i;
	float input;
	char dupMatch, dupNomatch;

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

	// Sort both vectors
	sort(match.begin(), match.end());
	sort(nomatch.begin(), nomatch.end());

	
	float ctr = 0, mctr = 0, nctr = 0;
	float tnr, temp;

	vector<float> tpr;
	vector<float> fpr;

	//Calculate values for TPR and FPR
	while (mctr < match.size() && nctr < nomatch.size())
	{
		if (ctr == 0)
		{
			tpr.push_back(1);
			fpr.push_back(1);
			ctr++;
		}
		else if (match.at((int)mctr) < nomatch.at((int)nctr))
		{
			mctr++;
			temp = (match.size() - mctr) / match.size();
			tpr.push_back(temp);
			tnr = nctr / nomatch.size();
			fpr.push_back(1 - tnr);
			ctr++;
		}
		else if (nomatch.at((int)nctr) < match.at((int)mctr))
		{
			nctr++;
			tnr = nctr / nomatch.size();
			fpr.push_back(1 - tnr);
			temp = (match.size() - mctr) / match.size();
			tpr.push_back(temp);
			ctr++;
		}
	}

	while (mctr < match.size())
	{
		mctr++;
		temp = (match.size() - mctr) / match.size();
		tpr.push_back(temp);
		tnr = nctr / nomatch.size();
		fpr.push_back(1 - tnr);
		ctr++;
	}

	while (nctr < nomatch.size())
	{
		nctr++;
		tnr = nctr / nomatch.size();
		fpr.push_back(1 - tnr);
		temp = (match.size() - mctr) / match.size();
		tpr.push_back(temp);
		ctr++;
	} 

	for (i = 0; i < ctr; i++)
	{
		cout << endl;
		cout << fpr[i] << ' ' << tpr[i];
	}

}
