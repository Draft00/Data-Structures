#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long x = 5;

unsigned long long lkg(long long a, long long c, long long m)
{
	x = (a * x + c) % m;
	return x;
}
int main()
{
	long long a = 42949677, c = 1, m = 4294967296, per = 0, s = 1, nabor = 123456;
	unsigned long long current = 0, x0 = 0;
	long long i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0, i6 = 0, i7 = 0, i8 = 0, i9 = 0, i10 = 0, i11 = 0, i12 = 0, i13 = 0, i14 = 0, i15 = 0, i16 = 0;
	unsigned long long ans = a - 1;
	long long intervals1[16] = { 0 }, intervals2[64] = { 0 }, intervals3[32] = { 0 };
	long long length = 0;
	short index = 0;
	int p1_2 = 0, p3 = 0, p4 = 0, p5 = 0, mass[52] = { 0 }, pok = 0;

	x0 = lkg(a, c, m);
	printf("%llu\n", x0);
	x0 = lkg(a, c, m);
	printf("%llu\n", x0);
	/*
		do {
				current = lkg(a, c, m);
				//printf("ch is:  %llu\n", current);
				per++;

		} while (current != x0);
	*/
	printf("period is:  %lli\n", per);

	length = 268435456;
	//268435456
	x = time(0);
	long int raz = 0;
	long int ver = 16777216 / 16;
	float hi = 0;

	for (long long i = 0; i < 16777216; i++)
	{
		current = lkg(a, c, m);
		while (current > length)
		{
			length += 268435456;
			index++;
		}
		intervals3[index]++;
		length = 268435456;
		index = 0;
	}

	for (long long j = 0; j < 16; j++)
	{
		if (ver > intervals3[j])
			raz = (ver - intervals3[j]);
		else raz = (intervals3[j] - ver);
		hi += (float)raz * (float)raz / (float)ver;
		printf("%lli, %lli\n", intervals3[j], raz);
	}
	printf("hi is: %f\n", hi);

	//покер-критерий
	/*
	for (int i = 0; i < nabor; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			pok = lkg(a, c, m)%13;
			mass[pok]++;
		}

		for (int k = 0; k < 13; k++)
		{

			if (mass[k] == 5 || mass[k] == 4)
			{
				p1_2++;
				break;
			}
			if (mass[k] == 3)
			{
				int flag = 0;
				//printf("\n \n \n \n  3 \n\n\n\n");
				for (int l = k + 1; l < 13; l++)
				{
					if (mass[l] == 2)
					{
						p1_2++;
						flag = 1;
						k = l;
						break;
					}
				}
				if (!flag)
				{
					p3++;
					break;
				}

			}
			if (mass[k] == 2)
			{
				int flag = 0;
				for (int l = k + 1; l < 13; l++)
				{
					if (mass[l] == 3)
					{
						p1_2++;
						flag = 1;
						k = l;
						break;
					}
					if (mass[l] == 2)
					{
						p3++;
						flag = 1;
						k = l;
						break;
					}
				}
				if (!flag)
				{
					p4++;
					//break;
				}
			}

		}
		//for (int k = 0; k < 13; k++)
			//printf("%d ", mass[k]);
		for (int k = 0; k < 13; k++)
			mass[k] = 0;
		//printf("\n");

	}
	printf("%d\n", p1_2);
	//printf("%d\n", p2);
	printf("%d\n", p3);
	printf("%d\n", p4);
	printf("%d\n", nabor - p1_2 - p3 - p4);
	*/
	/*
	while (ans%m != 0)
	{
		ans*= (a - 1);
		s++;
	}
	printf("s is:  %lli\n", s);

	*/
	return 0;
}
