#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command; //command를 입력받을 변수 선언
	int *array = NULL; //array 초기화
	int *hashtable = NULL; // hashtable 초기화
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
		case 'z': case 'Z': //z를 입렫받은 경우
			initialize(&array); //initialize 함수 실행
			break;
		case 'q': case 'Q': //q를 입력받은 경우
			freeArray(array); //freeArray 함수 실행
			break;
		case 's': case 'S'://s를 입력받은 경우
			selectionSort(array);//selectionSort 함수 실행
			break;
		case 'i': case 'I'://i를 입력받은 경우
			insertionSort(array);//insertionSort 함수 실행
			break;
		case 'b': case 'B': //b를 입력받은 경우
			bubbleSort(array); //bubbleSort 함수 실행
			break;
		case 'l': case 'L': //l을 입력받은 경우
			shellSort(array);//shellsort 함수 실행
			break;
		case 'k': case 'K': //k를 입력받은 경우
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //정렬 전 배열 출력
			quickSort(array, MAX_ARRAY_SIZE); //퀵정렬 실행
			printf("----------------------------------------------------------------\n");
			printArray(array);//정렬 후 배열 출력

			break;

		case 'h': case 'H': //h를 입력받은 경우
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //배열 출력
			hashing(array, &hashtable);//해싱 함수 실행
			printArray(hashtable);//해시 테이블 출력
			break;

		case 'e': case 'E'://e를 입력받은 경우
			printf("Your Key = ");
			scanf("%d", &key);//key값 입력
			printArray(hashtable); //해시테이블 출력
			index = search(hashtable, key);//index에 헤시테이블에서 찾은 키값의 주소 입력
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P': //p를 입력받은 경우
			printArray(array);//배열 출력
			break;
		default://오류 메세지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q를 입력받은 경우 반복문 종료

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);//배열의 크기만큼 동적할당
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE; 

	return 0;
}

int freeArray(int *a) //메모리해제 함수
{
	if(a != NULL)
		free(a);//a가 NULL이 될 때까지 메모리 해제
	return 0;
}

void printArray(int *a) //배열을 출력하는 함수
{
	if (a == NULL) { //a가 NULL인 경우
		printf("nothing to print.\n"); //메세지 출력
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i); //배열의 인덱스 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]); //배열의 값 출력
	printf("\n");
}


int selectionSort(int *a)//선택정렬 함수
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; //minindex의 i 대입
		min = a[i]; //min 최소값에 a[i] 대입
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j]) //min의 값이 a[j]보다 크다면
			{
				min = a[j]; //min의 값 변경
				minindex = j;//minindex를 j로 변경
			}
		}
		a[minindex] = a[i];//a[minindex]에 a[i]값 대입
		a[i] = min;//a[i]의 min(최솟값)대입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//배열 출력
	return 0;
}

int insertionSort(int *a)//삽입정렬 함수
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//배열 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];//t에 a[i]대입
		j = i;//j에 i대입
		while (a[j-1] > t && j > 0)//앞 인덱스의 값이 다음 인덱스 값보다 크고 , j>0일 때 반복
		{
			a[j] = a[j-1]; //a[j]에 a[j-1] 복사
			j--;//j를 -1 
		}
		a[j] = t; //a[j]에 t 복사
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a) //버블 정렬 함수
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++) //1번 정렬할 때 마다 맨 끝 자료는 비교하지 않는다
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++) //배열의 크기 만큼 비교 
		{
			if (a[j-1] > a[j])// 앞 인덱스의 값이 뒤 인덱스의 값 보다 큰 경우 스왑
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

int shellSort(int *a)//shell 정렬
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) // 부분 리스트를 만들어서 각각의 부분 리스트를 삽입정렬로 정렬한다 
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v) //삽입정렬 실행
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

int quickSort(int *a, int n) //퀵정렬 함수
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

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
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



