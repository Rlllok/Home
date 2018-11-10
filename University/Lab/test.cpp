#include <ctime>
#include <iostream>

using namespace std;

main()
{
	int A[4];
	char B[10];

	int x = sizeof(A);
	int y = sizeof(B);

	size_t sizea = sizeof(A);
	size_t sizeb = sizeof(B);

	cout <<	x << ' ' << y << endl;
	cout << sizea << ' ' << sizeb << endl;

	return 0;
}
