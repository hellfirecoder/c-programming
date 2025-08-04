#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define l 0
#define u 9

int gen_rand_nos()
{
    int r=rand()%(u-l+1)+l;
    return r;
}

int ** store_data_M(FILE *fp, int r, int c)
{
    int ** m=(int ** )calloc(r,sizeof(int));
    if(m==NULL)
    {
        printf("Error!\n");
        exit(0);
    }
    int i,j;
    for(i=0;i<r;i++)
    {
        m[i]=(int *)calloc(c,sizeof(int));
    }
    //storing in array
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            m[i][j]=gen_rand_nos();
            fprintf(fp,"%d  ",m[i][j]);
        }
        fprintf(fp,"%s","\n");
    }
    return m;
}

int main()
{
    srand(time(0));
    FILE *fp1, *fp2, *fp3;
    int n;
    printf("Enter the value of n:\n");
    scanf("%d",&n);
    int r1=n,c1=n,r2=n,c2=n;
    fp1=fopen("Matrix 1.txt","w");
    fp2=fopen("Matrix 2.txt","w");
    fp3=fopen("Matrix 3.txt","w");
    if(fp1==NULL||fp2==NULL||fp3==NULL)
    {
        printf("Error opening the file!\n");
        exit(0);
    }
    clock_t start,end;
    start=clock();
    int ** m1=store_data_M(fp1,r1,c1);
    printf("Data stored successfully in Matrix 1\n");
    int ** m2=store_data_M(fp2,r2,c2);
    printf("Data stored successfully in Matrix 2\n");
    
    int ** m3=(int ** )calloc(r1,sizeof(int));
    if(m3==NULL)
    {
        printf("Error!\n");
        exit(0);
    }
    int i,j,k;
    for(i=0;i<r1;i++)
    {
        m3[i]=(int *)calloc(c2,sizeof(int));
    }
    for(i=0;i<r1;i++)
    {
        for(j=0;j<c2;j++)
        {
            for(k=0;k<r2;k++)
            {
                m3[i][j]+=m1[i][k]*m2[k][j];
            }
            fprintf(fp3,"%d ",m3[i][j]);

        }
        fprintf(fp3,"%s","\n");
    }


    for (int i = 0; i < r1; i++)
        free(m3[i]);
    free(m3);

    end=clock();
    double elapsed_time=(double) (end-start)/CLOCKS_PER_SEC;
    printf("Data stored successfully in Matrix 3\n");
    printf("Time taken is %lfs\n",elapsed_time);
    for (int i = 0; i < r1; i++)
        free(m1[i]);
    free(m1);
    for (int i = 0; i < r2; i++)
        free(m2[i]);
    free(m2);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    return 0;
}