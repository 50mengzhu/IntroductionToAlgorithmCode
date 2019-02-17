#include <iostream>

#define Length(A, B) (sizeof(A) / sizeof(B))


void insert_sort(int *, int);
void merge_sort(int *, int, int);
void merge_sort(int *, int);
void swap(int &, int &);
void display(int *, int);

int main(int argc, char const *argv[])
{
	int A[] = {3, 2, 5, 4, 10, 17, 8, 9, 7, 6, 20, 78, 62, 84, 30, 95, 58, 76, 1, 0};
	int length = Length(A, int);

	display(A, length);

	std::cout << "game of throne" << std::endl;
	// insert_sort(A, length);
	// merge_sort(A, 0, length);
	merge_sort(A, length);

	display(A, length);
	return 0;
}

void insert_sort(int A[], int length)
{
	if (A == nullptr || length <= 0)
		return;

	for (int i = 1; i < length; ++ i)
	{
		for (int j = i; j > 0; -- j)
		{
			if (A[j] < A[j - 1])
				swap(A[j], A[j - 1]);
		}
	}
}

void swap(int &num1, int &num2)
{
	int temp_num = num1;
	num1 = num2;
	num2 = temp_num;
}

void display(int A[], int length)
{
	for (int i = 0; i < length; ++i)
	{
		std::cout << A[i] <<std::endl;
	}
}

void merge_sort(int A[], int left, int length)
{
	if (length == 1 || A == nullptr)
		return;

	int interval = length / 2;
	/***
	*	将原数组等距离二分
	*/
	int n_left = left, n_right = left + interval;
	merge_sort(A, n_left, interval);
	merge_sort(A, n_right, length - interval);


	/***
	*	将原数组二分完成之后，再对两部分已排好序的数组进行合并
	*/
	
	int *temp_array = new int[length]; 

	int count = 0;
	
	/***
	*	构造临时数组，先存在临时数组，然后再复制给原来的数组
	*/
	while (n_right < length + left && n_left < interval + left)
	{
		temp_array[count ++] = A[n_left] <= A[n_right] ? A[n_left ++] : A[n_right ++];
	}

	/***
	*	若左边数组的数组已经完成合并，右边的数组还未合并完
	*	这样就可以直接将临时数组的前count个数复制回原来的数组
	*/
	if (n_left == interval + left && n_right <= left + length)
	{
		for (int i = 0; i < count; ++ i)
		{
			A[i + left] = temp_array[i];
		}
	}

	/***
	*	若右边数组的数组已经完成合并，左边的数组还未合并完
	*	这样就先将左边的最大数先放到原数组的右边，
	*	然后将临时数组的前count个数复制回原来的数组
	*/
	if (n_left <= interval + left && n_right == left + length)
	{
		for (int i = left + interval - 1; i >= n_left; -- i)
		{
			A[length + i - interval] = A[i];
		}

		for (int i = 0; i < count; ++ i)
		{
			A[i + left] = temp_array[i];
		}
	}

	delete []temp_array;
}


void merge_sort(int A[], int length)
{
	if (A == nullptr || length <= 1)
		return;

	int interval = length / 2;

	merge_sort(A, interval);
	merge_sort(A + interval, length - interval);

	int left = 0, right = interval;
	int *temp_array = new int[length];
	int count = 0;

	while (left < interval && right < length)
		temp_array[count ++] = A[left] <= A[right] ? A[left ++] : A[right ++];

	if (left == interval && right <= length)
	{
		for (int i = 0; i < count; ++ i)
		{
			A[i] = temp_array[i];
		}
	}

	if (right == length && left <= interval)
	{
		for (int i = interval - 1; i >= left ; -- i)
		{
			A[i + length - interval] = A[i];
		}

		for (int i = 0; i < count; ++ i)
		{
			A[i] = temp_array[i];
		}
	}

	delete []temp_array;
}