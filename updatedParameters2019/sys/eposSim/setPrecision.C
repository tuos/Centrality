#include <stdio.h>
void setPrecision(){

const int nN=5;
double numbers[nN] = {105.2356, 1123.939340, 1.384345, 0.23001, 0.0128809};
double numbers2[nN] = {1.2356, 1.9329340, 0.84345, 0.023001, 0.00128809};
char out_string[5][200];
int lengthdigits[5];
float cvtvalue[5];
char out_string0[5][200];
for(int i=0; i<nN; i++) { 
sprintf(out_string0[i], "%#.5g", (numbers[i]));
cvtvalue[i] = atof(out_string0[i]);
//sprintf(out_string[i], "%.*f", strlen(out_string0[i])-2, (cvtvalue[i]-int(cvtvalue[i])));
sprintf(out_string[i], "%d", int( atof(out_string0[i]) ));
//sprintf(out_string[i], "%d", int(cvtvalue[i]));

//cout<<numbers[i]<<endl;
//printf("%0.4f\n", numbers[i]);
//printf("%0.3g\n", numbers[i]);
//printf("%0.3G\n", numbers[i]);
lengthdigits[i] = strlen(out_string[i])-2;
printf("%#.5g  %s   %#.*f \n", numbers[i], out_string[i], strlen(out_string0[i])-strlen(out_string[i])-1, numbers2[i]);
//float f = 1234.56789;
//printf("%d.%.0f", f, 1000*(f-(int)f));


}

}


