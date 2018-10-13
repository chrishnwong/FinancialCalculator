#ifndef Calculator_H
#define Calculator_H

double NPW(double* para, double* RevGrowth, double* OpCGrowth);
double NFW(double* para, double* RevGrowth, double* OpCGrowth);
double AEW(double* para, double* RevGrowth, double* OpCGrowth);
double BC(double* para, double* RevGrowth, double* OpCGrowth);
void startup(double i);
double percentGrowth(double ann, double growth, double i, double n);

#endif
