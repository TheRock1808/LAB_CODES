#include <stdio.h>
#include <string.h>
#define MAX 10

int main()
{
    char iden[MAX][MAX]; 
    char root[MAX];
    int w[MAX][MAX], c[MAX][MAX], r[MAX][MAX]; //weight, cost, root
	int p[MAX], q[MAX]; //successfull search probab, unsucc search probab
    int temp = 0, min, min1, n;
    int i, j, k, b;
    
    printf("Enter the number of elements: ");
    scanf("%d",&n);
    
    for (i = 1; i <= n; i++){
        printf("Enter identifier %d: ",i);
        fflush(stdin);
        gets(iden[i]); //stores the string in ith row
    }    

    for (i = 1; i <= n; i++) {
        printf("Enter success probability of %d: ",i);
        scanf("%d",&p[i]);
    }

    for (i = 0; i <= n; i++) {
        printf("Enter unsuccess probability of %d: ",i);
        scanf("%d",&q[i]);
    }
    
    printf("\nW\tC\tR\n");
    //OBST ALGORITHM
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= n; j++) { //w00, w11, w22, w33, w44
            if (j - i == 0) { 
                w[i][j] = q[j];
                c[i][j] = 0;
                r[i][j] = 0;

                //cout << i << i << "\t" << w[i][j] << "\t" << c[i][j] << "\t" << r[i][j] << "\n";
                printf("%d %d \t %d \t %d \t %d\n",i, j, w[i][j], c[i][j], r[i][j]);
            }
            else if(j - i == 1) { //w01, w12, w23, w34
            	w[i][j] = p[j] + q[j] + w[i][j-1];
                c[i][j] = w[i][j];
                r[i][j] = j;                
			}
        }
    }

    printf("\n");
    for (b = 1; b <= n; b++) { 
        for (i = 0, j = b; j <= n; i++, j++) { //j - i = b
            if (i != j && j - i != 1) { //don't calculate for j-i = 0 and j - i = 1
                w[i][j] = p[j] + q[j] + w[i][j - 1];
                min = 30000;
                for (k = i + 1; k <= j; k++) { //i < k <= j
                    min1 = c[i][k - 1] + c[k][j];
                    if (min1 < min) { //find which k gives min and that min value
                        min = min1;
                        temp = k;
                    }
                }
                c[i][j] = min + w[i][j];
                r[i][j] = temp;
            }
            printf("%d %d \t %d \t %d \t %d\n",i, j, w[i][j], c[i][j], r[i][j]);
        }
        printf("\n");
    }
    
    printf("\nMinimum cost = %d\n",c[0][n]);
    strcpy(root, iden[r[0][n]]);
    printf("Root = %d = %s\n",r[0][n],root);

    return 0;
}

//3 3 1 1
//2 3 1 1 1
