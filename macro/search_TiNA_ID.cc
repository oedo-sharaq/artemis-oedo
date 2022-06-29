{
	gROOT->ProcessLine("fcd 0");
	
	TString yy1;
	for (Int_t i=0; i<96; i++){
		yy1.Form("yy1fraw.fID==%d",i);
		long long n_entry = tree->GetEntries(yy1.Data());
		if(n_entry == 0){
			cout << i << ",";
		}
	}
	cout << endl;
	cout << endl;
	
	TString front;
	for (Int_t i=0; i<512; i++){
		front.Form("ttt_front.fID==%d",i);
		long long n_entry = tree->GetEntries(front.Data());
		if(n_entry == 0){
			cout << i << ",";
		}
	}
	cout << endl;
	cout << endl;
	
	TString back;
	for (Int_t i=0; i<512; i++){
		back.Form("ttt_back.fID==%d",i);
		long long n_entry = tree->GetEntries(back.Data());
		if(n_entry == 0){
			cout << i << ",";
		}
	}
	cout << endl;
	cout << endl;
	
	TString csi;
	for (Int_t i=0; i<32; i++){
		csi.Form("csiraw.fID==%d",i);
		long long n_entry = tree->GetEntries(csi.Data());
		if(n_entry == 0){
			cout << i << ",";
		}
	}
	cout << endl;
	cout << endl;
}
