#include <stdio.h>

int main()
{
    unsigned n=60000;
    double Xa=0.5, Xb=2;
    double h=2*Xb/(n-1);
    double u[n+1], l[n+1];
    double a[n+1], c[n+1], d[n+1];
    double y[n+1], x[n+1], b[n+1], vn[n+1], vt[n+1];  
    
    for(int i=1; i<=n; i++){
        x[i]=-Xb+h*(i-1);
        }
 
    for(int i=1; i<=n; i++)
        d[i]=-2/(h*h);
        
    for(int i=1; i<=n; i++)
        a[i]=1/(h*h);
        
     for(int i=1; i<=n; i++)
        c[i]=1/(h*h); 
        
    for(int i=1; i<=n; i++){
     if(x[i]>=-Xb && x[i]<-Xa || x[i]==0 || x[i]>Xa   && x[i]<=Xb)
        b[i]=0;
        
     if(x[i]>=-Xa && x[i]<0) b[i]=-1;
     
     if(x[i]>0 && x[i]<=Xa) b[i]=1;
     }   
         
  
      d[1]=1;
      c[1]=0;
      b[1]=0;
        d[n]=1;
        a[n]=0;
        b[n]=0;
        
        
    u[1]=d[1];
    for(int i=2; i<=n; i++){
        l[i]=a[i]/u[i-1];
         u[i]=d[i]-l[i]*c[i-1];                
               
        }
        
        
        
     
     y[1]=b[1];
     for(int i=2; i<=n; i++)
        y[i]=b[i]-l[i]*y[i-1];
        
     vn[n]=y[n]/u[n];
    
     for(int i=n-1; i>=1; i--){
        vn[i]=(y[i]-c[i]*vn[i+1])/u[i];   
       
        }
     
     
     
     
      for(int i=0; i<=n; i++){
        if(x[i]>=-Xb && x[i]<=Xa) vt[i]=x[i]/16 + 1./8;
        if(x[i]>=-Xa && x[i]<=0) vt[i]=-(x[i]*x[i])/2 - (7*x[i])/16;
        if(x[i]>=0 && x[i]<=Xa) vt[i]=(x[i]*x[i])/2- (7*x[i])/16;
        if(x[i]>=Xa   && x[i]<=Xb) vt[i]=x[i]/16 - 1./8;
      }  
     
      FILE *fp;
      fp=fopen("V60000.dat","w");
      for(int i=1; i<=n; i++){
        fprintf(fp," %12.4g      %12.4g     %12.4g   \n",x[i], vn[i], vt[i]);
        }
       fclose(fp); 

return 0;
}
