void missingID(Int_t num, Int_t get)
{
	{
		TString cmd;
		cmd.Form("add steering/missingID.yaml NAME=ni58phys NUM=%04d GET=%04d",num,get);
		gROOT->ProcessLine(cmd.Data());
		art::TLoopManager::Instance()->GetLoop()->Resume();
	}

	cout << num << endl;
	cout << endl;
	gROOT->ProcessLine(".x macro/search_TiNA_ID.cc");
//	gROOT->ProcessLine("cd");
//	gROOT->ProcessLine("zone");
//	gROOT->ProcessLine("ht missing_ID/csiraw_id_q colz");
//	gROOT->ProcessLine("lgy");
//	gROOT->ProcessLine("lgz");
//	gROOT->ProcessLine("csiraw_id_q->SetStats(0)");
}
