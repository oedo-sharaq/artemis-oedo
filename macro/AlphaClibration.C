struct data_t {
  Double_t ch;
  Double_t err;
};
bool comp(const data_t& left, const data_t& right){
  return left.ch < right.ch;
}

void AlphaClibration(TH2* h2,const int saveflag=0 ,const char* output="test/TTT.txt")
{
	TSpectrum spec(3,1);
	double zero=0;
	TString outputfilename = output;
	std::ofstream fout(outputfilename);
	
	int nmax = h2->GetNbinsX();
	std::vector<Double_t> MeV;
	MeV.push_back(3.271);
	MeV.push_back(5.486);
	MeV.push_back(5.805);
	
	TF1 *f = new TF1 ("Alpha", "[0]*TMath::Gaus(x,[1],[2])+[3]*TMath::Gaus(x,[4],[5])+[6]*TMath::Gaus(x,[7],[8])");

	TGraphErrors *tge[nmax];
	
	for (Int_t i = 0, n = nmax; i < n;  ++i) {
		TH1* h1 = h2->ProjectionY(Form("h%03d",i),i+1,i+1);		
		h1->SetTitle(Form("%s (%03d)",h1->GetTitle(),i));
			
		std::vector<Double_t> mean; 
		std::vector<Double_t> mean_err; 

	if (h1->Integral()>100) {
		Int_t nfound = spec.Search(h1,1,"",0.05);
		Double_t *xpeaks = spec.GetPositionX();
		std::sort(xpeaks,xpeaks+3);

		f->SetParameter(0,h1->GetBinContent(xpeaks[0]));
		f->SetParameter(1,xpeaks[0]);
		f->SetParameter(2,10);
		f->SetParameter(3,h1->GetBinContent(xpeaks[1]));
		f->SetParameter(4,xpeaks[1]);
		f->SetParameter(5,10);
		f->SetParameter(6,h1->GetBinContent(xpeaks[2]));
        f->SetParameter(7,xpeaks[2]);
        f->SetParameter(8,10);



		f->SetParLimits(2,0,50);
    	f->SetParLimits(5,0,50);
		f->SetParLimits(8,0,50);

		f->SetParLimits(0,0,100);
		f->SetParLimits(3,0,100);
		f->SetParLimits(6,0,100);

		h1->Fit("Alpha");
		if(i<88){gStyle->SetStatX(0.5);}else{gStyle->SetStatX(0.95);}
		
		if(saveflag==1){
    	sleep(1);
			art::TCmdSave::Instance()->Run("");                       
		}

			mean.push_back( h1->GetFunction("Alpha")->GetParameter(1)  );
			mean.push_back( h1->GetFunction("Alpha")->GetParameter(4)  );
			mean.push_back( h1->GetFunction("Alpha")->GetParameter(7)  );
			mean_err.push_back( h1->GetFunction("Alpha")->GetParError(1) );
			mean_err.push_back( h1->GetFunction("Alpha")->GetParError(4) );
			mean_err.push_back( h1->GetFunction("Alpha")->GetParError(7) );
		/*Double_t peak0 = h1->GetFunction("Alpha")->GetParameter(1);
		Double_t peak1 = h1->GetFunction("Alpha")->GetParameter(4);
		if(peak0<peak1){
			mean.push_back( h1->GetFunction("Alpha")->GetParameter(1)  );
			mean.push_back( h1->GetFunction("Alpha")->GetParameter(4)  );
			mean_err.push_back( h1->GetFunction("Alpha")->GetParError(1) );
			mean_err.push_back( h1->GetFunction("Alpha")->GetParError(4) );
		}else{
			mean.push_back( h1->GetFunction("Alpha")->GetParameter(4)  );
			mean.push_back( h1->GetFunction("Alpha")->GetParameter(1)  );
			mean_err.push_back( h1->GetFunction("Alpha")->GetParError(4) );
			mean_err.push_back( h1->GetFunction("Alpha")->GetParError(1) );
		}*/

		tge[i] = new TGraphErrors(3,&MeV.at(0),&mean.at(0),NULL,&mean_err.at(0)); 
	} else{tge[i] = new TGraphErrors();}
	}
	fout.close();


	std::ofstream fout1("test/TTT_calib.txt");
	std::ofstream fout2("test/TTT_param.txt");
	TF1 *f1 = new TF1("f1","[0]*x+[1]");
	for (Int_t i = 0, n = nmax; i < n;  ++i) {
		//cout<<i<<endl;
		if(tge[i]->GetN()>0){
		cout<<i<<endl;
			tge[i]->SetMarkerStyle(21);
			tge[i]->SetTitle(TString::Format("Calibration fID%d",i));
			tge[i]->Draw("ap");
			tge[i]->GetXaxis()->SetRangeUser(0.,7.);
			tge[i]->Fit("f1");
			if(saveflag==1){
				gStyle->SetStatY(0.34);
				gStyle->SetStatX(0.88);
				art::TCmdSave::Instance()->Run("");
				sleep(1);
			}
			fout1 << i << " " << tge[i]->GetFunction("f1")->GetParameter(0) << " "<< tge[i]->GetFunction("f1")->GetParError(0) << " "<< tge[i]->GetFunction("f1")->GetParameter(1) << " "<< tge[i]->GetFunction("f1")->GetParError(1) << endl;
			fout2 << -tge[i]->GetFunction("f1")->GetParameter(1)/tge[i]->GetFunction("f1")->GetParameter(0) << " " << 1.0/tge[i]->GetFunction("f1")->GetParameter(0) << endl;
		}else{
		fout2 << zero << " " << 1 <<endl;	
		}
	}
fout1.close();
fout2.close();
}
