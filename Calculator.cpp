#include <iostream>
#include <cmath>

#include "Calculator.h"

double intr=0.1;
double PF[40];
double FP[40];
double AP[40];
double PA[40];
double AF[40];
double FA[40];
double PG[40];
double FG[40];
double AG[40];

using std::cout;
using std::endl;
using std::cin;

int main() {
    startup(intr);

    /*cout << "Select a function from below: " << endl;
    cout << "1)  NPW " << endl;
    cout << "2)  NFW" << endl;
    cout << "3)  AEW" << endl;
    cout << "4)  B/C" << endl;
    auto select = -1;
    while ( select<1 || select>4 ) {
      cout << "Enter your choice: "; cin >> select;
      cout << endl;
    }*/

    double para[5];
    double RevGrowth[2];
    double OpCGrowth[2];

    cout << "Enter parameter Initial Cost: "; cin >> para[0];
    cout << "Enter parameter Revenue: "; cin >> para[1];
    cout << "Enter parameter Revenue growth type (0 for none, 1 for percent, 2 for fixed): "; cin >> RevGrowth[0];
    if(RevGrowth[0]!=0){
      cout << "Enter parameter Revenue growth amount: "; cin >> RevGrowth[1];}
    cout << "Enter parameter Operating Cost: "; cin >> para[2];
    cout << "Enter parameter OperatingCost growth type (0 for none, 1 for percent, 2 for fixed): "; cin >> OpCGrowth[0];
    if(OpCGrowth[0]!=0){
      cout << "Enter parameter OperatingCost growth amount: "; cin >> OpCGrowth[1];}
    cout << "Enter parameter End of Life Salvage: "; cin >> para[3];
    cout << "Enter parameter Useful Life: "; cin >> para[4];

    /*cout<<para[0]<<endl;
    cout<<para[1]<<endl;
    cout<<para[2]<<endl;
    cout<<para[3]<<endl;
    cout<<para[4]<<endl;

    cout<<OpCGrowth[0]<<endl;
    cout<<OpCGrowth[1]<<endl;*/

    /*auto foo = &NPW;
    switch( select ) {
    case 2:
      foo = &NFW;
      break;
    case 3:
      foo = &AEW;
      break;
    case 4:
      foo = &BC;
      break;
    default:
      break;
  }*/

  /*auto result = foo( para, RevGrowth, OpCGrowth);
  cout << endl;
  cout << "Your answer is: " << result << endl;*/
  double result = NPW( para, RevGrowth, OpCGrowth);
  cout << endl;
  cout << "Your NPW is: " << result << endl;
  result = NFW( para, RevGrowth, OpCGrowth);
  cout << endl;
  cout << "Your NFW is: " << result << endl;
  result = AEW( para, RevGrowth, OpCGrowth);
  cout << endl;
  cout << "Your AEW is: " << result << endl;
  result = BC( para, RevGrowth, OpCGrowth);
  cout << endl;
  cout << "Your B/C is: " << result << endl;
}

double NPW(double* para, double* RevGrowth, double* OpCGrowth){
    double result=0;
    int n=para[4];

    //Initial Cost
    result-=para[0];

    //Revenue
    if(RevGrowth[0]==2)
        result+=para[1]*PA[n-1]+RevGrowth[1]*PG[n-1];
    else if(RevGrowth[0]==1)
        result+=percentGrowth(para[1],RevGrowth[1],intr,n);
    else
        result+=para[1]*PA[n-1];

    //Operating Cost
    if(OpCGrowth[0]==2)
        result-=(para[2]*PA[n-1]+OpCGrowth[1]*PG[n-1]);
    else if(OpCGrowth[0]==1)
        result-=percentGrowth(para[2],OpCGrowth[1],intr,n);
    else
        result-=para[2]*PA[n-1];

    //End of Life Salvage
    result+= para[3]*PF[n-1];

    return result;
}
double NFW(double* para, double* RevGrowth, double* OpCGrowth){
    double result=0;
    int n=para[4];

    //Initial Cost
    result-=para[0]*FP[n-1];

    //Revenue
    if(RevGrowth[0]==2)
        result+=para[1]*FA[n-1]+RevGrowth[1]*FG[n-1];
    else if(RevGrowth[0]==1)
        result+=percentGrowth(para[1],RevGrowth[1],intr,n)*FP[n-1];
    else
        result+=para[1]*FA[n-1];

    //Operating Cost
    if(OpCGrowth[0]==2)
        result-=(para[2]*FA[n-1]+OpCGrowth[1]*FG[n-1]);
    else if(OpCGrowth[0]==1)
        result-=percentGrowth(para[2],OpCGrowth[1],intr,n)*FP[n-1];
    else
        result-=para[2]*FA[n-1];

    //End of Life Salvage
    result+= para[3];

    return result;
}
double AEW(double* para, double* RevGrowth, double* OpCGrowth){
    double result=0;
    int n=para[4];

    //Initial Cost
    result-=para[0]*AP[n-1];

    //Revenue
    if(RevGrowth[0]==2)
        result+=para[1]+RevGrowth[1]*AG[n-1];
    else if(RevGrowth[0]==1)
        result+=percentGrowth(para[1],RevGrowth[1],intr,n)*AP[n-1];
    else
        result+=para[1];

    //Operating Cost
    if(OpCGrowth[0]==2)
        result-=(para[2]+OpCGrowth[1]*AG[n-1]);
    else if(OpCGrowth[0]==1)
        result-=percentGrowth(para[2],OpCGrowth[1],intr,n)*AP[n-1];
    else
        result-=para[2];

    //End of Life Salvage
    result+= para[3]*AF[n-1];

    return result;
}
//Para [0] - Initial cost
//Para [1] - Revenue
//Para [2] - Operating cost
//Para [3] - EOF
//Para [4] - Useful Life
double BC(double* para, double* RevGrowth, double* OpCGrowth){
    double result, benefits, costs, initial, salvage;
    int n=para[4];

    //Initial Cost
    initial=para[0]*AP[n-1];

    //Revenue
    if(RevGrowth[0]==2)
        benefits=para[1]+RevGrowth[1]*AG[n-1];
    else if(RevGrowth[0]==1)
        benefits=percentGrowth(para[1],RevGrowth[1],intr,n)*AP[n-1];
    else
        benefits=para[1];

    //Operating Cost
    if(OpCGrowth[0]==2)
        costs=(para[2]+OpCGrowth[1]*AG[n-1]);
    else if(OpCGrowth[0]==1)
        costs=percentGrowth(para[2],OpCGrowth[1],intr,n)*AP[n-1];
    else
        costs=para[2];

    //End of Life Salvage
    salvage=para[3]*AF[n-1];

    result=benefits/(costs+initial-salvage);

    return result;
}
void startup(double i){
    for(int x=0;x<40;x++){
        double ipow=pow((1+i),(x+1));
        PF[x]=1/ipow;
        FP[x]=ipow;
        PA[x]=(ipow-1)/(i*ipow);
        AP[x]=i*ipow/(ipow-1);
        AF[x]=i/(ipow-1);
        FA[x]=(ipow-1)/i;
        PG[x]=(1/i)*(PA[x]-(x+1)/ipow);
        FG[x]=(1/i)*(FA[x]-(x+1));
        AG[x]=FG[x]*AF[x];
    }
    AG[0]=0;
}
double percentGrowth(double ann, double growth, double i, double n){
    double result;
    result=(ann/(0.1-growth));
    result*=( 1-pow( (1+growth)/(1+i),n ) );
    return result;
}
