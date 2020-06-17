#include <stdio.h>
#include <stdlib.h>

int a = 0;

void MergeTwoArea(int arr[], int left, int mid, int right) {
	int fldx = left;
	int rldx = mid + 1;
	int i;
	int * sortArr = (int*)malloc(sizeof(int)*(right+1));
	int sldx = left;
	while(fldx <= mid && rldx <= right) {
		if(arr[fldx] <= arr[rldx])
			sortArr[sldx] = arr[fldx++];
		else
			sortArr[sldx] = arr[rldx++];
		sldx++;
	} 
	if(fldx > mid) {
		for(i=rldx; i <= right; i++, sldx++)
			sortArr[sldx] = arr[i];
	} else {
		for(i=fldx; i <= mid; i++, sldx++)
			sortArr[sldx] = arr[i];
		}
	for(i=left; i <= right; i++)
		arr[i] = sortArr[i];
	free(sortArr);
}

void MergeSort(int arr[], int left, int right) {
	int mid;
	if(left<right)
	{
		mid = (left+right)/2;
		a++;

		MergeSort(arr, left, mid);
		MergeSort(arr, mid+1, right);


		MergeTwoArea(arr, left, mid, right);
	}
}

int main(void) {
	int * arr;
	int k;
	int i;

	printf("입력크기: ");
	scanf("%d", &k);

	arr = (int *)malloc(sizeof(int)*k);

	printf("숫자입력: ");
	for(i=0; i<k; i++) {
		scanf("%d", &arr[i]);
	}


	MergeSort(arr, 0, k-1);

	for(i=0; i<k; i++){
		printf("%d", arr[i]);
	}
	printf("\n");
	printf("분할 횟수=%d", a);

	free(arr);
	return 0;
}



