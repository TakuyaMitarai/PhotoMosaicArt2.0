#include "Individual.h"
#include <math.h>
#include <vector>
using namespace std;

extern vector<int> B, G, R;
extern vector<int> OB, OG, OR;

// �R���X�g���N�^
Individual::Individual()
{
	int i, ch;
	/*
	for(i = 0; i < N; i++) {
		chrom[i] = rand() % 2025;
	}
	*/
	for(i = 0; i < N; i++) {
		chrom[i] = -1;
	}

	for(i = 0; i < N; i++) {
		ch = rand() % (N - 1);
		do {
			if(chrom[ch] == -1) {
				chrom[ch] = i;
				break;
			} else {
				ch++;	
				if(ch == N) {
					ch = 0;
				}
			}
		}while(1);
		
	}
	fitness = 0.0;
}

// �f�X�g���N�^
Individual::~Individual()
{
}

// �K���x���Z�o����
void Individual::evaluate()
{
	int i;

	fitness = 0.0;
	for(i = 0; i < N; i++) {
		double dis = (B[chrom[i]] - OB[i]) * (B[chrom[i]] - OB[i]) + (G[chrom[i]] - OG[i]) * (G[chrom[i]] - OG[i]) + (R[chrom[i]] - OR[i]) * (R[chrom[i]] - OR[i]);
		dis = sqrt(dis);
		fitness += dis;
	}
	fitness = fabs(fitness);
}

// p1��p2�����_�����ō�����q�ɂ���
// p1: �e��1
// p2: �e��2
void Individual::mappingcrossover(Individual *p1, Individual *p2)
{
	int point1, point2, i, j, tmp;
	int flag = -1;

	point1 = rand() % (N - 1);
	point2 = (point1 + (rand() % (N - 2) + 1)) % (N - 1);
	if(point1 > point2) {
		tmp = point1;
		point1 = point2;
		point2 = tmp;
	}

	for(i = 0; i <= point1; i++) {
		for(j = point1 + 1; j <= point2; j++) {
			if(p1->chrom[i] == p2->chrom[j]) {
				flag = j;
				break;
			}
		}
		if(flag != -1) {
			do{
				for(j = point1 + 1; j <= point2; j++) {
					if(p2->chrom[j] == p1->chrom[flag]) {
						flag = j;
						break;
					}
				}
				if(j == point2 + 1) {
					chrom[i] = p1->chrom[flag];
					break;
				}
			} while(1);
		} else {
			chrom[i] = p1->chrom[i];
		}
		flag = -1;
	}
	for(; i <= point2; i++) {
		chrom[i] = p2->chrom[i];
	}
	for(; i < N; i++) {
		for(j = point1 + 1; j <= point2; j++) {
			if(p1->chrom[i] == p2->chrom[j]) {
				flag = j;
				break;
			}
		}
		if(flag != -1) {
			do{
				for(j = point1 + 1; j <= point2; j++) {
					if(p2->chrom[j] == p1->chrom[flag]) {
						flag = j;
						break;
					}
				}
				if(j == point2 + 1) {
					chrom[i] = p1->chrom[flag];
					break;
				}
			} while(1);
		} else {
			chrom[i] = p1->chrom[i];
		}
		flag = -1;
	}
}

void Individual::crossover1(Individual *p1, Individual *p2)
{
	int point, i;

	point = rand() % (N - 1);
	for(i = 0; i <= point; i++) {
		chrom[i] = p1->chrom[i];
	}
	for(; i < N; i++) {
		chrom[i] = p2->chrom[i];
	}
}

// p1��p2�����_�����ō�����q�ɂ���
// p1: �e��1
// p2: �e��2
void Individual::crossover2(Individual *p1, Individual *p2)
{
	int point1, point2, tmp, i;

	point1 = rand() % (N - 1);
	point2 = (point1 + (rand() % (N - 2) + 1)) % (N - 1);
	if(point1 > point2) {
		tmp = point1;
		point1 = point2;
		point2 = tmp;
	}
	for(i = 0; i <= point1; i++) {
		chrom[i] = p1->chrom[i];
	}
	for(; i <= point2; i++) {
		chrom[i] = p2->chrom[i];
	}
	for(; i < N; i++) {
		chrom[i] = p1->chrom[i];
	}
}

// p1��p2�����l�����ō�����q�ɂ���
// p1: �e��1
// p2: �e��2
void Individual::crossoveru(Individual *p1, Individual *p2)
{
	int i;

	for(i = 0; i < N; i++) {
		if(rand() % 2 == 1) {
			chrom[i] = p1->chrom[i];
		} else {
			chrom[i] = p2->chrom[i];
		}
	}
}

// �ˑR�ψق��N����
void Individual::mutate()
{
	int i, tmp, num1, num2;

	for(i = 0; i < N; i++) {
		if(RAND_01 < MUTATE_PROB) {
			num1 = rand() % N;
			num2 = rand() % N;
			tmp = chrom[num1];
			chrom[num1] = chrom[num2];
			chrom[num2] = tmp;
		}
	}
}
