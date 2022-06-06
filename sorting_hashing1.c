#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
	char command; //command�� �Է¹��� ���� ����
	int *array = NULL; //array �ʱ�ȭ
	int *hashtable = NULL; // hashtable �ʱ�ȭ
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) { 
		case 'z': case 'Z': //z�� �Ԏ����� ���
			initialize(&array); //initialize �Լ� ����
			break;
		case 'q': case 'Q': //q�� �Է¹��� ���
			freeArray(array); //freeArray �Լ� ����
			break;
		case 's': case 'S'://s�� �Է¹��� ���
			selectionSort(array);//selectionSort �Լ� ����
			break;
		case 'i': case 'I'://i�� �Է¹��� ���
			insertionSort(array);//insertionSort �Լ� ����
			break;
		case 'b': case 'B': //b�� �Է¹��� ���
			bubbleSort(array); //bubbleSort �Լ� ����
			break;
		case 'l': case 'L': //l�� �Է¹��� ���
			shellSort(array);//shellsort �Լ� ����
			break;
		case 'k': case 'K': //k�� �Է¹��� ���
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //���� �� �迭 ���
			quickSort(array, MAX_ARRAY_SIZE); //������ ����
			printf("----------------------------------------------------------------\n");
			printArray(array);//���� �� �迭 ���

			break;

		case 'h': case 'H': //h�� �Է¹��� ���
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //�迭 ���
			hashing(array, &hashtable);//�ؽ� �Լ� ����
			printArray(hashtable);//�ؽ� ���̺� ���
			break;

		case 'e': case 'E'://e�� �Է¹��� ���
			printf("Your Key = ");
			scanf("%d", &key);//key�� �Է�
			printArray(hashtable); //�ؽ����̺� ���
			index = search(hashtable, key);//index�� ������̺��� ã�� Ű���� �ּ� �Է�
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P': //p�� �Է¹��� ���
			printArray(array);//�迭 ���
			break;
		default://���� �޼��� ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q�� �Է¹��� ��� �ݺ��� ����

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);//�迭�� ũ�⸸ŭ �����Ҵ�
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else
		temp = *a;

	/* �������� �迭�� ������ ���� */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE; 

	return 0;
}

int freeArray(int *a) //�޸����� �Լ�
{
	if(a != NULL)
		free(a);//a�� NULL�� �� ������ �޸� ����
	return 0;
}

void printArray(int *a) //�迭�� ����ϴ� �Լ�
{
	if (a == NULL) { //a�� NULL�� ���
		printf("nothing to print.\n"); //�޼��� ���
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i); //�迭�� �ε��� ���
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]); //�迭�� �� ���
	printf("\n");
}


int selectionSort(int *a)//�������� �Լ�
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//�迭 ���

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; //minindex�� i ����
		min = a[i]; //min �ּҰ��� a[i] ����
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j]) //min�� ���� a[j]���� ũ�ٸ�
			{
				min = a[j]; //min�� �� ����
				minindex = j;//minindex�� j�� ����
			}
		}
		a[minindex] = a[i];//a[minindex]�� a[i]�� ����
		a[i] = min;//a[i]�� min(�ּڰ�)����
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//�迭 ���
	return 0;
}

int insertionSort(int *a)//�������� �Լ�
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//�迭 ���

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];//t�� a[i]����
		j = i;//j�� i����
		while (a[j-1] > t && j > 0)//�� �ε����� ���� ���� �ε��� ������ ũ�� , j>0�� �� �ݺ�
		{
			a[j] = a[j-1]; //a[j]�� a[j-1] ����
			j--;//j�� -1 
		}
		a[j] = t; //a[j]�� t ����
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a) //���� ���� �Լ�
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++) //1�� ������ �� ���� �� �� �ڷ�� ������ �ʴ´�
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++) //�迭�� ũ�� ��ŭ �� 
		{
			if (a[j-1] > a[j])// �� �ε����� ���� �� �ε����� �� ���� ū ��� ����
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)//shell ����
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) // �κ� ����Ʈ�� ���� ������ �κ� ����Ʈ�� �������ķ� �����Ѵ� 
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v) //�������� ����
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n) //������ �Լ�
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break;
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)
		return index;

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



