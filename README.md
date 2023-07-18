# Boston Housing Price Prediction
This is a C program to predict the housing prices in Boston as per the Boston Hosing dataset. It also has functions to check RMSE, Accuracy (in %) and cost.


# Usage

### For MacOS/Linux:

To run the application, navigate to the root folder into which you have cloned this repo and execute the following command:  
```terminal
make
```

The makefile assumes the use of gcc to compile. If you use any other compiler, for example "clang", go into the <b>makefile</b> and change "CC = gcc" to:
```
CC = name-of-complier
```

### For Windows:
Makefile is not inherently supported in Windows. Instead of using a makefile, enter this into your terminal.

```terminal
gcc main.c -o main -lm
```

Note: Replace "gcc" with the name of your compiler if you are using a different compiler.

Then to run it, simply enter:
```terminal
main
```




# Files
* main.c: Contains all the C code

* data.csv: Contains the Boston Housing Data (For training)

* data.csv: Contains the Boston Housing Data (For testing)

* makefile: To compile the file(s)



