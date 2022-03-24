void IDSearch(TH2* h2,const char* output="outputtext/idlist.txt")
{
	
	TString outputfilename = output;
	std::ofstream fout(outputfilename);
	
	int nmax = h2->GetNbinsX();

	
	for (Int_t i = 0, n = nmax; i < n;  ++i) {
	
		TH1* h1 = h2->ProjectionY(Form("h%03d",i),i+1,i+1);		
		h1->SetTitle(Form("%s (%03d)",h1->GetTitle(),i));

		Double_t evts = h1->Integral();

		if(evts>0){
			fout << i << " " << evts << endl;	
		}else{
			fout << i << " " << "0" << endl;	
		}

	}
	fout.close();

}
