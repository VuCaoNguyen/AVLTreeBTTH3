#include <iostream>
using namespace std;
#include <string>


#define LH -1
#define EH 0
#define RH 1

struct MAYTINH
{
	string Key;
	int Gia;
};

struct AVLNode {
	int balFactor; // chỉ số cân bằng
	MAYTINH Data;
	AVLNode *pLeft, *pRight;
};
typedef AVLNode *AVLTREE;


// Đưa Data vao Node
AVLNode * CreateAVLNode(MAYTINH x) {
	AVLNode *p = new AVLNode;
	if (p == NULL) return NULL;
	if (p)
	{
		p->balFactor = EH;
		p->Data = x;
		p->pLeft = NULL;
		p->pRight = NULL;
	}
	return p;
}


void CreateAVLTree(AVLTREE &T)
{
	T = NULL;
}


void RightRotate(AVLTREE &T) {
	AVLNode *T1 = T->pLeft;
	T->pLeft = T1->pRight;
	T1->pRight = T;
	T = T1;
}

void LeftRotate(AVLTREE &T)
{
	AVLNode *T1 = T->pRight;
	T->pRight = T1->pLeft;
	T1->pLeft = T;
	T = T1;
}

//Phép xoay trong các trường hợp
void LL(AVLTREE &T) {
	switch (T->pLeft->balFactor) {
	case LH: T->balFactor = EH;
		T->pLeft->balFactor = EH; break;
	case EH: T->balFactor = LH;
		T->pLeft->balFactor = RH; break;
	}
	RightRotate(T);
}

void RR(AVLTREE &T) {
	switch (T->pRight->balFactor) {
	case RH: T->balFactor = EH;
		T->pRight->balFactor = EH; break;
	case EH: T->balFactor = RH;
		T->pRight->balFactor = LH; break;
	}
	LeftRotate(T);
}

void LR(AVLTREE &T) {
	switch (T->pLeft->pRight->balFactor) {
	case LH: T->balFactor = RH;
		T->pLeft->balFactor = EH; break;
	case EH: T->balFactor = EH;
		T->pLeft->balFactor = EH; break;
	case RH: T->balFactor = EH;
		T->pLeft->balFactor = LH; break;
	}
	T->pLeft->pRight->balFactor = EH;
	LeftRotate(T->pLeft); RightRotate(T);
}

void RL(AVLTREE &T) {
	switch (T->pRight->pLeft->balFactor)
	{
	case RH: T->balFactor = LH;
		T->pRight->balFactor = EH; break;
	case EH: T->balFactor = EH;
		T->pRight->balFactor = EH; break;
	case LH: T->balFactor = EH;
		T->pRight->balFactor = RH; break;
	}
	T->pRight->pLeft->balFactor = EH;
	RightRotate(T->pRight); LeftRotate(T);
}
int BalanceLeft(AVLTREE &T) {
	switch (T->pLeft->balFactor) {
	case LH: LL(T); return 2;
	case EH: LL(T); return 1;
	case RH: LR(T); return 2;
	}
	return 0;
}

int BalanceRight(AVLTREE &T) {
	switch (T->pRight->balFactor) {
	case LH: RL(T); return 2;
	case EH: RR(T); return 1;
	case RH: RR(T); return 2;
	}
	return 0;
}




int Compare(MAYTINH x, MAYTINH y)
{
	if (x.Key == y.Key) return 0;
	return x.Key > y.Key ? 1 :  -1;
}

int AddAVLNode(AVLTREE &T, MAYTINH x) {
	int ret;
	if (T == NULL) {
		T = CreateAVLNode(x);
		if (T == NULL) return -1; else return 2;
	}
	if (T->Data.Key ==  x.Key) return 0;
	if (T->Data.Key  > x.Key) {
		ret = AddAVLNode(T->pLeft, x);
		if (ret < 2) return ret;
		switch (T->balFactor) {
		case RH: T->balFactor = EH; return 1;
		case EH: T->balFactor = LH; return 2;
		case LH: BalanceLeft(T); return 1;
		}
	}
	else {
		ret = AddAVLNode(T->pRight, x);
		if (ret < 2) return ret;
		switch (T->balFactor) {
		case LH: T->balFactor = EH; return 1;
		case EH: T->balFactor = RH; return 2;
		case RH: BalanceRight(T); return 1;
		}
	}
	return 0;
}
	

	 //Them Phan tu vao cay
void InSert(AVLTREE &root, MAYTINH x)
{

	if (root == NULL)
	{
		AVLNode * q = new AVLNode;
		q->Data = x; // Đưa dữ liệu vào Node
		q->pLeft = q->pRight = NULL;
		root = q;

	}
	else

	{
		if (root->Data.Key > x.Key)

		{
			InSert(root->pLeft, x);
		
			}

			else if (x.Key > root->Data.Key)
			{
				InSert(root->pRight, x);
			}

		}

	}
	

	void CreateTree (AVLTREE &root, MAYTINH a[], int n)
	{
		
		CreateAVLTree(root);
		for (int i = 0; i < n; i++)
		{
		

			InSert(root, a[i]);


		}

	}

	

	void LNR(AVLTREE root)
	{
		if (root != NULL)
		{
			LNR(root->pLeft);
			cout << "    " << root->Data.Key;
			LNR(root->pRight);
		}
	}

	
	int main()
	{
	
		AVLTREE root;
		// Tao cây với Mang a[] có n phần tử
		MAYTINH A[] = { { "Acer", 90 },{ "Apple", 240 },{ "Asus", 190 },{ "Compaq", 200 },{ "Dell", 150 },{ "Fujitsu", 210 },{ "Lenovo", 180 },{ "Samsung", 150 },{ "Sony", 180 },{ "Toshiba", 210 } };
		int n = 10;
	
		CreateTree(root, A, n);
		// Duyệt cây
		
		
		cout << "\nLNR: ";
		LNR(root);

		system("color e");
		system("pause");
		return 0;
	}
