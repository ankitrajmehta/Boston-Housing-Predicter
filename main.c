#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


#define TRAIN_ROWS 456    // Maximum number of rows in the CSV file
#define MAX_COLS 14    // Maximum number of columns in the CSV file
#define x_vals (MAX_COLS-1)
#define TEST_ROWS 50

int p = 0;


double cost(double w[x_vals], float b, float test[TEST_ROWS][MAX_COLS])
{
    double result = 0, y_p=0;
    for (int i = 0; i < TEST_ROWS; i++)
    {
        y_p=0;
        for (int j=0; j<x_vals;j++)
        {
        y_p += w[j] * test[i][j];
        }
        y_p+=b;
        float t =y_p - test[i][13];
        result+=t*t;
    }
    double tmp = result/TEST_ROWS;
    return tmp;
}

double rmse(double w[x_vals], float b, float test[TEST_ROWS][MAX_COLS])
{
    double result = 0, y_p=0;
    for (int i = 0; i < TEST_ROWS; i++)
    {
        y_p=0;
        for (int j=0; j<x_vals;j++)
        {
        y_p += w[j] * test[i][j];
        }
        y_p+=b;
        float t =y_p - test[i][13];
        result+=t*t;
    }
    double tmp = result/TEST_ROWS;
    return pow(tmp,.5);
}

double acc(double w[x_vals], float b, float test[TEST_ROWS][MAX_COLS])
{
    double result = 0, y_p=0,t;
    for (int i = 0; i < TEST_ROWS; i++)
    {
        y_p=0;
        for (int j=0; j<x_vals;j++)
        {
        y_p += w[j] * test[i][j];
        }
        y_p+=b;
        t =fabs(y_p - test[i][13])/test[i][13];
        result+=t;
    }
    double tmp = result/TEST_ROWS;
    return (100-tmp*100);
}


void gradiant(float train[TRAIN_ROWS][MAX_COLS],double w[MAX_COLS], double b,double rate, float test[TEST_ROWS][MAX_COLS])
{
    double x[x_vals],y;
    double dw[x_vals];
    for (int i=0;i<x_vals;i++)
    {
        dw[i]=0;
    }
    double db = 0;
    double y_p = 0;

    for (int i =0; i < TRAIN_ROWS; i++)
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
        w[i] -= (dw[i]/TRAIN_ROWS)*rate; //dw
    }
    
    p++;
    if (p%10000 == 0 || p == 1 )
    {
        printf("Epoch: %d\n", p);
        printf("Cost : %lf\n", cost(w,b,test));
        printf("Accuracy: %lf\n", acc(w,b,test));
    }
}


void csvopener(float train[TRAIN_ROWS][MAX_COLS],float test[TEST_ROWS][MAX_COLS])
{
    char filename[] = "data.csv";
    char testname[] = "test.csv";
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

    // Read lines from the train CSV file and parse them into the 2D array
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

    csvFile = fopen(testname, "r");
    if (csvFile == NULL) {
        perror("Error opening file");
        return;
    }

    // Read lines from the test CSV file and parse them into the 2D array
    rows=0;
    cols=0;
    while (fgets(line, sizeof(line), csvFile)) {
        token = strtok(line, ",");
        cols = 0;
        while (token != NULL) {
            test[rows][cols] = atof(token);
            cols++;
            token = strtok(NULL, ",");
        }
        rows++;
    }
    fclose(csvFile);
}


int main()
{
    float train[TRAIN_ROWS][MAX_COLS];
    float test[TEST_ROWS][MAX_COLS];

    csvopener(train,test);


    srand(time(NULL));
    double w[MAX_COLS];
    for (int i=0; i < MAX_COLS;i++)
    {
        w[i] = (rand()/RAND_MAX)/2;
    }
    double b = (rand()/RAND_MAX);
    int epoch = 1000000;
    double rate = 1e-6;


    for (int i = 0; i < epoch; i++)
    {
        gradiant(train,w,b,rate,test);
    }

    for (int l = 0; l<x_vals; l++)
    {
    printf("w%i = %lf \n",l, w[l]);
    }
    printf("b = %lf \n", b);

    
    printf("Accuracy: %lf\n", acc(w,b,test));
    printf("RMSE: %lf\n", rmse(w,b,test));

}