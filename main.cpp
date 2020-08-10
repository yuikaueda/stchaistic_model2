#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define N     50
//#define Pon   0.8
//#define Poff  0.5

//#define Koff   0.5
//#define Kon    0.5

//#define f      2.0
//#define Ks     0.1
//#define Kc     100

#define l      1.5
#define Iter   10000.0
#define Dt     1.0
#define St     0.3
//#define w      1.0
#define kin    0.35
#define kout   0.20

#define Lmax   150

#define dw     0.01
#define Iter2  1000


double Uniform(){
  return ((double)rand()+1.0)/((double)RAND_MAX+2.0);
}


int main()
{

  //FILE *date, *gp;
  //char *date_file;

  int   countOn = N;

  double   ran;
  double   L = N*l;
  double   w;
  double   t;

  w=0;
  t=0;

   FILE* fp;
    fp=fopen("c_out50_St-0.3.dat", "w");
     if(fp==NULL){
      printf("File open faild.");
      }
                          
  //date_file="out.dat";
  //date = fopen(date_file,"w");
  

  //fprintf(fp, "%5f\t%5d\n", t, countOn);
  srand((unsigned)time(NULL));
  
 for(int iter2 = 0; iter2 < Iter2+1.0; iter2++){
 double   Sum_N = N;
  for(int iter = 0; iter < Iter; iter++){

      ran=(double)rand()/RAND_MAX;

      while(ran==0||ran==1){
          ran=(double)rand()/RAND_MAX;
       }
         	
    //fprintf("gp: %5d %5d\n", iter, countOn); 
      double Stra_t = -St*(1 - cos(w*t));
      //double Stra_t = -St;
      double DStra_t = -St*w;
      //double DStra_t = -St*w*sin(w*t);

//      double Kon = kin*exp((L*(1 + Stra_t) - countOn*l)/l+DStra_t);
//      double Koff = kout*exp((-L*(1 + Stra_t) + countOn*l)/l-DStra_t);
      double Kon = kin*(L*(1 + Stra_t))*exp((L*(1 + Stra_t) - countOn*l)/(countOn*l)+DStra_t);
      double Koff = kout*(L*(1 + Stra_t))*exp((-L*(1 + Stra_t) + countOn*l)/(countOn*l)-DStra_t);


      double value = Uniform();

      t += log(1/ran)/(Kon+Koff);  

	if(value < Koff / (Koff + Kon) ) {countOn--;
        }
      else{countOn++;
        }
    //printf("number of springs: %5d %5d\n", countOn, N - countOn); 
    //double t = iter*Dt;
    //fprintf(fp, "%5f\t%5d\n", t, countOn);
    Sum_N += countOn;
     
    if(countOn==0)
     break;
    }     
//fclose(fp);

 double Onave = Sum_N / ((double)Iter + 1.0);
 
        
 fprintf(fp, "%5f\t%5f\n", (double)w , Onave); 
 w += dw;

 }

fclose(fp);

//fp = popen("gnuplot -persist","w");
//fprintf(fp,"plot 'out.dat'\n");

//pclose(fp);

  return 0;
}









