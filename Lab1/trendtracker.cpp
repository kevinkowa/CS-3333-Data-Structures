#include "trendtracker.h"
#include <iostream>
using namespace std;

Trendtracker::Trendtracker()
{
	S.clear();
	E.clear();
}

void Trendtracker::add_hashtag(string ht)
{
	int l = 0;
	int r = E.size()-1;
	int mid=0;
	while (l <= r)
	{
		mid = (l + r) / 2;
		if (E[S[mid]].hashtag == ht)
			return;
		if (E[S[mid]].hashtag > ht)
			r = mid - 1;
		else
			l = mid + 1;
	}

	Entry entry;
	entry.count = 0;
	entry.hashtag = ht;
	E.push_back(entry);
	S.push_back(S.size());
	int curr = S.size()-1;
	for (int i =S.size()-1; i>l; i--)
	{
        S[i]=S[i-1];
	}
	S[l] = S.size() - 1;
}

int Trendtracker::size()
{
	return E.size();
}

void Trendtracker::tweeted(string ht)
{
	int l = 0, r = E.size()-1;
	int loc = -1;
	Entry entry;
	while (l <= r)//finds the location and entry of the hashtag ht
	{
		int mid = (l + r) / 2;
		if (E[S[mid]].hashtag == ht)
		{
			entry = E[S[mid]];
			loc = mid;
			break;
		}
		else if (E[S[mid]].hashtag > ht)
			r = mid - 1;
		else
			l = mid + 1;
	}
	
	if (loc != -1)//It found the entry. It does exist.
	{
		l = 0, r = E.size()-1;
		entry.count++;
		while (l <= r)//find the rightmost entry that is greater than entry.count 
		{
			int mid = (l + r) / 2;
			if (E[mid].count < entry.count)
				r = mid - 1;
			else
				l = mid + 1;
		}
				
		if (r+1>= 0)
		{
			int start = 0, e = E.size() - 1;
			int pos = 0;
			while (start <= e)//find the position of the right-most entry>entry.count on S 
			{
				int mid = (start + e) / 2;
				if (E[S[mid]].hashtag == E[r+1].hashtag)
				{
					pos = mid;
					break;
				}
				else if (E[S[mid]].hashtag > E[r+1].hashtag)
				{
					e = mid - 1;
				}
				else
					start = mid + 1;
			}
			//swap them
			E[S[loc]] = E[r+1];
			E[r+1] = entry;
			S[pos] = S[loc];
			S[loc] = r+1;
		}
		else
		{		
			E[S[loc]] = entry;
		}

	}
}

int Trendtracker::popularity(string name)
{
	int l = 0, r = E.size() - 1;
	while (l <= r)
	{
		int mid = (l + r) / 2;
		if (E[S[mid]].hashtag == name)
			return E[S[mid]].count;
		else if (E[S[mid]].hashtag > name)
			r = mid - 1;
		else
			l = mid + 1;
	}
	return -1;
}

string Trendtracker::top_trend()
{
	if(E.size()!=0)
		return E[0].hashtag;
	return "";
}

void Trendtracker::trending(int k, vector<string>&t)
{
	t.clear();
	int size=E.size();
	if(size>k)
		size=k;
	for(int i=0;i<size;i++)
		t.push_back(E[i].hashtag);
}

int Trendtracker::S_index(string ht)
{
	int l=0,r=E.size()-1;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(E[S[mid]].hashtag==ht)
			return mid;
		else if(E[S[mid]].hashtag>ht)
			r=mid-1;
		else
			l=mid+1;
	}
	return -1;
}

int Trendtracker::lowest_E_index_with_count(int count)
{
	int l=0,r=E.size()-1;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(E[mid].count>count)
			r=mid-1;
		else
			l=mid+1;
	}
	return r-1;
}