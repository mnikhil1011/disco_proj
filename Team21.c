//Nikhil Mogalapalli 2020B1A72398H
//Divyanshu Kumar 2020B5A72367H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//global variables
int node;
int mat1[20][20];
int mat2[20][20];

//checks if mat is same as mat1
int matches(int mat3[node+1][node+1],int seq[node+1])
{
	int i,j;
	for(i=1;i<=node;i++)
    {
        for( j = 1;j<=node;j++)
        {
            if(mat1[i][j] != mat3[i][j])
            {
                return 0;
            }
        }
    }
    
    //if code reaches this point the mat formed by interchanging mat2 with seq in recursion is same
    printf("isomorphic");

    for(i=1;i<=node;i++)
    {
    	printf("\n %d %d ",i,seq[i]);
	}

    return 1;
}

// makes a mat using the seq provided by recursion
int makemat(int seq[node+1])
{
	int mat3[node+1][node+1];
	int mat4[node+1][node+1];

	int i,j;
	for(i=1;i<=node;i++)
    {
        for(j=1;j<=node;j++)
        {
            mat3[i][j]=0;
        }
    }
    
    for(i=1;i<=node;i++)
    {
    	for(j=1;j<=node;j++)
        {
            mat3[i][j]=mat2[seq[i]][j];
        }
	}
	
	for(i=1;i<=node;i++)
    {
    	for(j=1;j<=node;j++)
        {
            mat4[i][j]=mat3[i][seq[j]];
        }
	}
	
	// sends the mat and also the seq , the seq is sent so the code can print seq if it matches with mat1
	return matches(mat4,seq);
	
}

//rec function this function makes all sequences possible with n(no of nodes) numbers
int rec(int seq[node+1],int layer)
{
	if(layer==node+1)
	{
		int j,i,unique;
		unique=0;
		for(j=1;j<node;j++)
		{
			for(i=j+1;i<=node;i++)
			{
				if(seq[j] ==seq[i])
				{
					unique++;
				}
			}
			
		}
		
	
		if(unique==0)
		return makemat(seq);
		
		return 0;
		
	}
	int i;
	for(i=1;i<=node;i++)
	{
		seq[layer]=i;
		if( rec(seq, ++layer))
		return 1;
		--layer;
	}
	return 0;
}

//main fn takes 2 args 1 is of input file of graph a other is of input file of graph b
int main(int argc ,char *argv[])
{
	
    int node1, edge1;
    int node2, edge2;

    FILE *fp1=fopen(argv[1],"r");
    FILE *fp2=fopen(argv[2],"r");

    fscanf(fp1,"%d",&node1);fscanf(fp2,"%d",&node2);
    fscanf(fp1,"%d",&edge1);fscanf(fp2,"%d",&edge2);
    
    if(node1 != node2)
    {
    	printf("Not isomorphic, number of nodes are different");
    	return 0;
	}
	if(edge1 != edge2)
    {
    	printf("Not isomorphic, number of edges are different");
    	return 0;
	}
	 node =node1;
	int edge= edge1;
    
     mat1[node+1 ][node+1 ];
     mat2[node+1 ][node+1 ];

    int i,j;
    for(i=0;i<=node1;i++)
    {
        for(j=0;j<=node1;j++)
        {
            mat1[i][j]=0;
            mat2[i][j]=0;

        }
    }
    
    int ed1,ed2;
    for(i=1;i<=edge;i++)
    {	
		fscanf(fp1,"%d",&ed1);
        fscanf(fp1,"%d",&ed2);
        mat1[ed1][ed2] = 1;
        mat1[ed2][ed1] = 1;
        
		fscanf(fp2,"%d",&ed1);
        fscanf(fp2,"%d",&ed2);
        mat2[ed1][ed2] = 1;
        mat2[ed2][ed1] = 1;
    }
    int degree1[node+1];
    int degree2[node+1];

   
    for(i=1;i<=node;i++)
    {
        int check1 = 0;
        int check2 = 0;

        for( j = 1;j<=node;j++)
        {
            if(mat1[i][j]==1)
            {
                check1++;
                if(i==j)check1++;
            }
            
            if(mat2[i][j]==1)
            {
                check2++;
                if(i==j)check2++;
            }
        }
        degree1[i]=check1;
        degree2[i]=check2;
    }
    
    int temp;
    for (i=1;i<=node;i++) 
	{     
        for (j=i+1;j<=node;j++) 
		{     
           if(degree1[i]<degree1[j]) 
		   {    
               temp=degree1[i];
               degree1[i]=degree1[j];    
               degree1[j]=temp;    
           }     
        }    
	}
       
    fclose(fp1);
    for (i=1;i<=node;i++) 
	{     
        for (j=i+1;j<=node;j++) 
		{     
           if(degree2[i]<degree2[j]) 
		   {    
               temp=degree2[i];
               degree2[i]=degree2[j];    
               degree2[j]=temp;    
           }     
        }    
	}
	 
    fclose(fp2);
    
    //if degree seq is different its not isomorphic
    for(i=1;i<=node;i++)
	{
		if(degree1[i] != degree2[i])
		{
		printf(" not isomeric,degree of vertexes differ");
		return 0; 
		}
	}
    
   	int seq[20];
   	for(i=1;i<=node;i++) 
	   seq[i]=0;

    //call recursion function
    if(rec(seq,1))
    {
	return 0; 
	}
    
    printf(" Not Isomorphic, no bijection found ");
	return 0; 
    
} 