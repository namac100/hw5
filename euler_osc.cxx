#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

void euler_forward(double* const f, const int n, const double dt);
void euler_backward(double* const f, const int n, const double dt);
void write(double* const ff, double* const fb, const int n, const double dt, string filename);

int main(){
  double tstart = 0.0;
  double tend = 20.0*M_PI;
  double dt1 = M_PI/10.0;
  double dt2 = M_PI/100.0;
  int n1 = int((tend-tstart)/dt1);
  int n2 = int((tend-tstart)/dt2);
  
  double* ff10 = new double[2*n1];
  double* fb10 = new double[2*n1];
  double* ff100 = new double[2*n2];
  double* fb100 = new double[2*n2];
  
  string file1 = "euler10.dat";
  string file2 = "euler100.dat";
  
  euler_forward(ff10, n1, dt1);
  euler_backward(fb10, n1, dt1);
  write(ff10, fb10, n1, dt1, file1);
  
  euler_forward(ff100, n2, dt2);
  euler_backward(fb100, n2, dt2);
  write(ff100, fb100, n2, dt2, file2);
  
  delete[] ff10, fb10, ff100, fb100;

  
}

void euler_forward(double* const f, const int n, const double dt){
  f[0] = 1;
  f[n] = 0;
  
  for(int i=0; i<n; i++){
    f[i+1] = f[i] + f[n+i]*dt ;
    f[n+i+1] = f[n+i] - f[i]*dt;
  }
}

void euler_backward(double* const f, const int n, const double dt){
  f[0] = 1;
  f[n] = 0;
  
  for(int i=0; i<n; i++){
    f[i+1] = (f[i]+f[n+i]*dt)/(1.0+dt*dt);
    f[n+i+1] = (f[n+i]-f[i]*dt)/(1.0+dt*dt);
  }
}

void write(double* const ff, double* const fb, const int n, const double dt, string filename){
  ofstream out(filename.c_str());
  for(int i=0; i<n; i++){
    out << i*dt << "\t" << ff[i] << "\t" << fb[i] << endl;
  }
  out.close();
}
