void pulser_calib(TH2* h2,const int pulser=5 ,const int saveflag=0, const char* output="test/YY1.txt")
{
	TSpectrum spec(pulser,1);
	double zero=0;
	TString outputfilename = output;
	std::ofstream fout(outputfilename);
	
	int nmax = h2->GetNbinsX();
	std::vector<Double_t> V;
	if(pulser==6) { // for RUN1102
	V.push_back(0.25);
	V.push_back(0.5);
	V.push_back(0.75);
	V.push_back(1.0);
	V.push_back(1.25);
	V.push_back(1.5);
	}

	else { // for RUN1098
	V.push_back(0.1);
	V.push_back(0.2);
	V.push_back(0.4);
	V.push_back(0.6);
	V.push_back(0.8);
	}
	

	TGraphErrors *tge[nmax];
	//TF1* f = new TF1("gaus","gaus");
	
	for (Int_t i = 0, n = nmax; i < n;  ++i) {
		TH1* h1 = h2->ProjectionY(Form("h%03d",i),i+1,i+1);		
		h1->SetTitle(Form("%s (%03d)",h1->GetTitle(),i));
			
		std::vector<Double_t> mean; 
		std::vector<Double_t> mean_err; 

		if (h1->Integral()>100) {
			Int_t nfound = spec.Search(h1,3,"",0.05);
			Double_t *xpeaks = spec.GetPositionX();
			std::sort(xpeaks,xpeaks+pulser);
			for (int j=0; j<spec.GetNPeaks(); ++j) {
				h1->Fit("gaus","","",xpeaks[j]-50,xpeaks[j]+50);
		
					mean.push_back( h1->GetFunction("gaus")->GetParameter(1)  );
					mean_err.push_back( h1->GetFunction("gaus")->GetParError(1) );
			}

			if(saveflag==1){
		    	sleep(1);
				art::TCmdSave::Instance()->Run("");                       
			}

			tge[i] = new TGraphErrors(5,&V.at(0),&mean.at(0),NULL,&mean_err.at(0)); 
		} else{tge[i] = new TGraphErrors();}
	}


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
			fout << -tge[i]->GetFunction("f1")->GetParameter(1)/tge[i]->GetFunction("f1")->GetParameter(0) << " " << 1.0/tge[i]->GetFunction("f1")->GetParameter(0) << endl;
		}else{
		fout << zero << " " << 1 <<endl;	
		}
	}
fout.close();
}
