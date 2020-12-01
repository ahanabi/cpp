#include <stdio.h>
int func(int m){
	if(m<2)
		return m;
	return func(m -1)+func(m-2);
} 
int main(){
	printf("%d\n",func(7));
	return 0;
}

