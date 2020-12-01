# define MAX(x,y) (x)>(y)?(x):(y)
# include<stdio.h>
void main()
{
	int a[5] = {0,1,2,3,4};
	int i = 0, k = 0;
	while(i<4){
		k = MAX(a[i],a[i++]);
		printf("%d\n",k);
	}
} 
