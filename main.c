#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define MAX_ROWS 506    // Maximum number of rows in the CSV file
#define MAX_COLS 14    // Maximum number of columns in the CSV file
#define x_vals 13

int p = 0;


double cost(double w[x_vals], float b, int COUNT, float train[MAX_ROWS][MAX_COLS])
{
    double result = 0, y_p=0;
    for (int i = 0; i < COUNT; i++)
    {
        y_p=0;
        for (int j=0; j<x_vals;j++)
        {
        y_p += w[j] * train[i][j];
        }
        y_p+=b;
        float t =y_p - train[i][13];
        result+=t*t;
    }
    double tmp = result/COUNT;
    return tmp;
}

double rmse(double w[x_vals], float b, int COUNT, float train[MAX_ROWS][MAX_COLS])
{
    double result = 0, y_p=0;
    for (int i = 0; i < COUNT; i++)
    {
        y_p=0;
        for (int j=0; j<x_vals;j++)
        {
        y_p += w[j] * train[i][j];
        }
        y_p+=b;
        float t =y_p - train[i][13];
        result+=t*t;
    }
    double tmp = result/COUNT;
    return pow(tmp,.5);
}

double acc(double w[x_vals], float b, int COUNT, float train[MAX_ROWS][MAX_COLS])
{
    double result = 0, y_p=0,t;
    for (int i = 0; i < COUNT; i++)
    {
        y_p=0;
        for (int j=0; j<x_vals;j++)
        {
        y_p += w[j] * train[i][j];
        }
        y_p+=b;
        t =fabs(y_p - train[i][13])/train[i][13];
        result+=t;
    }
    double tmp = result/COUNT;
    return (100-tmp*100);
}


void gradiant(float train[MAX_ROWS][MAX_COLS], int COUNT,double w[MAX_COLS], double b,double rate)
{
    double x[x_vals],y;
    double dw[x_vals];
    for (int i=0;i<x_vals;i++)
    {
        dw[i]=0;
    }
    double db = 0;
    double y_p = 0;
    //double* tmp = (double*)malloc(11 * sizeof(double));

    for (int i =0; i < COUNT; i++)
    {
        y_p = 0;
        for (int j=0; j<x_vals;j++)
        {
            x[j] = (train[i][j]);
        }
        
        y = (train[i][x_vals]);
        for ( int k =0; k<x_vals; k++)
        {        
            y_p += w[k] * x[k];
        }
        y_p += b;
        for ( int k =0; k<x_vals; k++)
        {
            double dj_dw_i = (y_p - y) * x[k];
            dw[k]+= dj_dw_i;
        }
        double dj_db_i = y_p - y;

        db+=dj_db_i;
    }
    for (int i = 0; i<x_vals; i++){
        w[i] -= (dw[i]/COUNT)*rate; //dw
    }
    
    p++;
    if (p%10000 == 0 || p == 1 )
    {
        printf("c : %lf\n", cost(w,b,COUNT,train));
        
        printf("--%lf\n", acc(w,b,COUNT,train));
    }
}


void csvopener(float train[MAX_ROWS][MAX_COLS], char filename[])
{
    filename = "data.csv";
    FILE *csvFile;
    char line[1000];
    char *token;
    int rows = 0;
    int cols = 0;

    csvFile = fopen(filename, "r");
    if (csvFile == NULL) {
        perror("Error opening file");
        return;
    }

    // Read lines from the CSV file and parse them into the 2D array
    while (fgets(line, sizeof(line), csvFile)) {
        token = strtok(line, ",");
        cols = 0;
        while (token != NULL) {
            train[rows][cols] = atof(token);
            cols++;
            token = strtok(NULL, ",");
        }
        rows++;
    }

    fclose(csvFile);
}


int main()
{
    float train[MAX_ROWS][MAX_COLS];

    csvopener(train,"data.csv");

    int COUNT = sizeof(train)/sizeof(train[0]);

    srand(10);
    double w[MAX_COLS];
    for (int i=0; i < MAX_COLS;i++)
    {
        w[i] = 0;
    }
    double b = (rand()/RAND_MAX);
    int epoch = 1000000;
    //double h = 1e-5;
    double rate = 1e-8;

    /*
    for (int i = 0; i < epoch; i++)
    {
        float acc = cost(w,b);
        double dw = (cost(w + h, b) - acc);
        double db = (cost(w , b+h) - acc);

        w -= dw;
        b -= db;
    }
    */



    for (int i = 0; i < epoch; i++)
    {
        gradiant(train,COUNT,w,b,rate);
        if (p%5000 == 0)
        {
            rate = 1e-6;
        }
    }
    double xyz=0;
    for (int l = 0; l<x_vals; l++)
    {
    printf("w%i = %lf \n",l, w[l]);
        xyz+= w[l]*train[0][l];
    }
    xyz+=b;
    printf("b = %lf \n", b);

    
    printf("--%lf", acc(w,b,COUNT,train));

}