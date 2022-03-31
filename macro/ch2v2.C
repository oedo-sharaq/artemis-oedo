void ch2v2(TH2* hist, int IDsta=1, TString opt=""){
  /*
    ROOT Macro for TDC calibration from 2d histogram (ID vs Traw)
    input: 2d-hist
           option="nstop" -> wait is skipped
	   option="pedskip" -> pedestal skipped
    output: ch2ns.txt  -> calibration values
  */

  // modify this line if ypou need
  //  const double initamp=0.10;//initial pulser amp. (V)
  const double initamp=0.05;//initial pulser amp. (V)
  const double period=0.1;// period of pulser amp. (V)
  const double pedestal=0.0;

  Int_t nbin=hist->GetXaxis()->GetNbins();
  Int_t num=0;
  vector<double> prm1;
  vector<double> prm2;
  vector<double> prm3;

  hist->Draw();
  gPad->GetCanvas()->Clear();
  gPad->GetCanvas()->Divide(1,3);
  for (Int_t i=IDsta-1;i<nbin;i++){// begin of loop ------->
    num++;
    Int_t ID = i+1;
    TH1 *h=MakeBanY(hist,ID);

    gPad->GetCanvas()->cd(1);
    h->Draw();
    gPad->GetCanvas()->cd(2);

//    double val=GetPrmFromHist(h,period,initamp);

//___________________________________________________________________________
//double GetPrmFromHist(TH1 *h, double period, double initamp){
  double calval1;// calibration value
  double calval2;// calibration value
  double calval3;// calibration value
  int thre = h->GetMaximum()*0.15;// threshold for peak search
  int nbin = h->GetXaxis()->GetNbins();
  Double_t xmin,xmax;
  double p[3];
  int nP=0; // number of peaks
  vector<double> peaks;
  vector<double> tvals;

  int OverThre=0;
  for(int ibin=1;ibin<nbin+1;ibin++){
    if( OverThre==0 && h->GetBinContent(ibin)>thre ){
      OverThre=1;
      xmin=h->GetXaxis()->GetBinCenter(ibin);
    }else if ( OverThre==1 && h->GetBinContent(ibin)<thre*0.4){
      OverThre=2;
      xmax=h->GetXaxis()->GetBinCenter(ibin);
    }
    if (OverThre==2){
      OverThre=0;
      nP=nP+1;
      TF1 *func = new TF1("myfunc","gaus");
      double mean = 0.5*(xmin+xmax);
      double rms = 0.5*0.3*(xmax-xmin);
      func->SetParameters( h->GetMaximum(),
			   h->GetMean(),
			   h->GetRMS()      );
      h->Fit(func,"Q","",xmin,xmax);
      func->GetParameters(p);
      cout<<"peak value is "<<p[1]<< "number"<<nP<<endl;
      if(nP<68){
	peaks.push_back(p[1]);}

      if (opt=="pedskip"){
	tvals.push_back(initamp+period*(peaks.size()-1));
	continue;
      }

      if (peaks.size()==1){
	tvals.push_back(pedestal);	
      }else{
	tvals.push_back(initamp+period*(peaks.size()-2));
      }      

    }
  }

  double* xpointer=&(peaks.at(0));
  double* ypointer=&(tvals.at(0));
  TGraph* tg=new TGraph(peaks.size(),xpointer,ypointer);
  tg->Fit("pol2","Q");
  TString title=h->GetName();
  tg->SetTitle(title);
  tg->GetXaxis()->SetLimits(h->GetXaxis()->GetXmin(),
			       h->GetXaxis()->GetXmax());
  tg->SetMinimum(0.0);
  tg->SetMaximum(nP*period+initamp);
  tg->Draw("AP*");
  calval1=tg->GetFunction("pol2")->GetParameter(2);
  calval2=tg->GetFunction("pol2")->GetParameter(1);
  calval3=tg->GetFunction("pol2")->GetParameter(0);


  gPad->GetCanvas()->cd(3);
  vector<double> tvals2;
  for (int j=0;j<peaks.size();j++){
    tvals2.push_back(tvals[j]-tg->GetFunction("pol2")->Eval(peaks[j]));
  }
  double* xpointer2=&(peaks.at(0));
  double* ypointer2=&(tvals2.at(0));
  TGraph* tg2=new TGraph(peaks.size(),xpointer2,ypointer2);
  tg2->GetXaxis()->SetLimits(h->GetXaxis()->GetXmin(),
			       h->GetXaxis()->GetXmax());
  tg2->Draw("AP*");

//}
//___________________________________________________________________________

    // Draw
    gPad->GetCanvas()->Update();
    cout<<"ID="<<ID<<" prm="<<calval1<<", "<<calval2<<endl;
    
    prm1.push_back(calval1);
    prm2.push_back(calval2);
    prm3.push_back(calval3);

    if (opt!="nstop")
      if(Wait()) break;

  }// end of loop <--------------
                                                        
  ofstream ofs1;
  ofs1.open("ch2v_tina2.txt");
  vector<double>::iterator it1=prm1.begin();
  vector<double>::iterator it2=prm2.begin();
  vector<double>::iterator it3=prm3.begin();
  while(it1!=prm1.end()){
    ofs1<<*it3<<"\t"<<*it2<<"\t"<<*it1<<endl;
    it1++;
    it2++;
    it3++;
  }
  ofs1.close();
                       
  cout<<"parameters are writen in \"ch2v.txt\""<<endl;

  cout<<num<<" channels are fitted, END"<<endl;
}
//--------------------------------------------------------------------------
TH1* MakeBanY(TH2* hist, Int_t id){
  TString str=hist->GetName();
  ostringstream oss;
  oss<<id;
  str+="_bny"+oss.str();
  return hist->ProjectionY(str.Data(),id,id);
}
//___________________________________________________________________________
bool Wait(){
  //check and quit if q is typed
  printf("[enter]:continue, [q]:quit >");
  char s[1];
  gets(s);
  if(s[0]=='q') {
    cout<<"Break fit loop"<<endl;
    return true;
  }
  return false;
}
//___________________________________________________________________________
