#include "Individual.h"

class Population
{
public:
	Population();
	~Population();
	void alternate();	// �����������
	void printResult();	// ���ʂ�\������

	Individual **ind;	// ������̌̌Q�̃����o

private:
	void evaluate();			// �̂�]������
	int rankingSelect1();		// �e�̂�I������
	int rankingSelect2();		// �e�̂�I������
	int rouletteSelect();		// �e�̂�I������
	int tournamentSelect();		// �e�̂�I������
	void sort(int lb, int ub);	// �̂�ǂ����ɕ��ёւ���

	Individual **nextInd;		// ������̌̌Q�̃����o
	double trFit[POP_SIZE];		// �K���x��ϊ������l
	double denom;				// ���[���b�g�I���̊m�������߂�Ƃ��̕���
};
