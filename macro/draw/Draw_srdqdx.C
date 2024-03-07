#include <fstream>
#include <ostream>
#include <string>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

void loadtest(){

  double dx_tmp; 
  double dq_tmp; 
  std::vector<double> dx; 
  std::vector<double> dq; 
  std::string buff;
  std::ifstream fin("prm/dia/strip1/tof_offset_170.dat");
  if(!fin.is_open()){
	  cout << "Cannnot open file" << endl;
	  return;
  }
 
   while(getline(fin,buff)) {
	   stringstream ss(buff);
	   ss >> dx_tmp >> dq_tmp;
       Dx.push_back(dx_tmp);
       Dq.push_back(dq_tmp);
	  }
   fin.close();

  TH1D   





