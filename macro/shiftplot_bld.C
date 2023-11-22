void shiftplot_bld(const std::string &runname, const std::string &runnum, 
		   const std::string &maxevt,
		   const bool print = false)
{
  gROOT->ProcessLine(".! mkdir figs/shift_bld 2>> /dev/null");
  
  gROOT->SetBatch();
   {
     //std::string cmd = "add steering/chkbld.yaml NAME=" + runname + " NUM=" + runnum;
     std::string cmd = "add steering/chkbld_maxevt.yaml NAME=" + runname + " NUM=" + runnum + " MAX=" + maxevt;
      gROOT->ProcessLine(cmd.c_str());
      std::cout << "Starting the loop... " << std::endl;
      art::TLoopManager::Instance()->GetLoop()->Resume();
   }

   gROOT->ProcessLine(".! mkdir figs/shift_bld 2>> /dev/null");
   std::string file_name_prefix = "figs/shift_bld/bld";
   std::string run_name = "0000";
   int print_counter = 1;

   // function to print the artcanv
   auto print_canv = [&file_name_prefix, &runname, &runnum, &print_counter]()
   {
      std::string count_str = to_string(print_counter);
      auto form_count_str = std::string(2 - std::min(2, int(count_str.length())), '0') + count_str;
      std::string png_name = file_name_prefix + "_" + runname + runnum + "_" + form_count_str;
      std::string pdf_name = png_name + ".pdf";
      png_name = png_name + ".png";
      gROOT->FindObject("artcanvas")->Print(png_name.c_str());
      print_counter++;
   };

   TObjArray *array = new TObjArray();
   array->Add(new TText(0.1, 0.92, ""));
   array->Add(new TText(0.1, 0.45, ""));
   array->Add(new TText(0.1, 0.60, ""));
   array->Add(new TText(0.1, 0.30, ""));
   TIter next(array);
   while (auto obj = (TText *)next())
   {
      obj->SetTextAlign(11);
      obj->SetTextColor(kRed + 2);
      obj->SetTextFont(43);
      obj->SetTextSize(40);
   }

   // function to draw label
   auto draw_label = [&array](std::string txt, int n)
   {
      TText *t = (TText *)array->At(n);
      t->SetTitle(txt.c_str());
      t->Draw("same");
      return t;
   };

   gStyle->SetStatW(0.3);

   gROOT->ProcessLine("zone");
   auto artcanv = (TCanvas *)gROOT->FindObject("artcanvas");
   //{
      auto height = artcanv->GetWh();
      auto width = artcanv->GetWw();
      artcanv->SetCanvasSize(width, 1.8 * height);
      //}
   auto p = (TPaveLabel *)artcanv->GetListOfPrimitives()->At(1);
   std::string title = p->GetTitle();
   run_name = title.substr(20, 6);
   
   // 
//   gROOT->ProcessLine("fcd 0");
//   gROOT->ProcessLine("tree->Draw(\"sr91_x_cal@.GetEntriesFast()>>hx91(20,0.5,20.5)\")");
//   gROOT->ProcessLine("tree->Draw(\"sr92_x_cal@.GetEntriesFast()>>hx92(20,0.5,20.5)\")");
//   gROOT->ProcessLine("tree->Draw(\"sr91_y_cal@.GetEntriesFast()>>hy91(20,0.5,20.5)\")");
//   gROOT->ProcessLine("tree->Draw(\"sr92_y_cal@.GetEntriesFast()>>hy92(20,0.5,20.5)\")");
//   gROOT->ProcessLine("tree->Draw(\"src1_x_cal@.GetEntriesFast()>>hxc1(20,0.5,20.5)\")");
//   gROOT->ProcessLine("tree->Draw(\"src2_x_cal@.GetEntriesFast()>>hxc2(20,0.5,20.5)\")");
//   gROOT->ProcessLine("tree->Draw(\"src1_y_cal@.GetEntriesFast()>>hyc1(20,0.5,20.5)\")");
//   gROOT->ProcessLine("tree->Draw(\"src2_y_cal@.GetEntriesFast()>>hyc2(20,0.5,20.5)\")");
//   gROOT->ProcessLine("tree->Draw(\"sr11_x_cal@.GetEntriesFast()>>hx11(20,0.5,20.5)\")");
//   gROOT->ProcessLine("tree->Draw(\"sr12_x_cal@.GetEntriesFast()>>hx12(20,0.5,20.5)\")");
//   gROOT->ProcessLine("tree->Draw(\"sr11_y_cal@.GetEntriesFast()>>hy11(20,0.5,20.5)\")");
//   gROOT->ProcessLine("tree->Draw(\"sr12_y_cal@.GetEntriesFast()>>hy12(20,0.5,20.5)\")");


   // FE9 Charge
   gROOT->ProcessLine("cd");
   gROOT->ProcessLine("zone 2 4");
   gROOT->ProcessLine("cd chksrppacsr91");
   gROOT->ProcessLine("ht sr91_x_idq colz");
   gROOT->ProcessLine("ht sr91_y_idq colz");
   gROOT->ProcessLine("ht sr91_x_q0");
   gROOT->ProcessLine("ht sr91_y_q0");
   gROOT->ProcessLine("cd ..");
   gROOT->ProcessLine("cd chksrppacsr92");
   gROOT->ProcessLine("ht sr92_x_idq colz");
   gROOT->ProcessLine("ht sr92_y_idq colz");
   gROOT->ProcessLine("ht sr92_x_q0");
   gROOT->ProcessLine("ht sr92_y_q0");
   gROOT->ProcessLine("cd ..");
   artcanv->cd();
   draw_label("SRPPAC FE9 Charge", 0);
   print_canv();
//   artcanv->Update();
//   gSystem->ProcessEvents();
//   getchar();

   // FE9 Multiplicity
   gROOT->ProcessLine("zone 2 2");
   artcanv->SetCanvasSize(width, height);
   gROOT->ProcessLine("ht chksrppacsr91/sr91_x_ent");
   gROOT->ProcessLine("ht chksrppacsr91/sr91_y_ent");
   gROOT->ProcessLine("ht chksrppacsr92/sr92_x_ent");
   gROOT->ProcessLine("ht chksrppacsr92/sr92_y_ent");
   artcanv->cd();
   draw_label("SRPPAC FE9 Multiplicity", 0);
   print_canv();
//   artcanv->Update();
//   gSystem->ProcessEvents();
//   getchar();

   // FE12 Charge
   gROOT->ProcessLine("zone 2 4");
   artcanv->SetCanvasSize(width, 1.8 * height);
   gROOT->ProcessLine("cd chksrppacsrc1");
   gROOT->ProcessLine("ht src1_x_idq colz");
   gROOT->ProcessLine("ht src1_y_idq colz");
   gROOT->ProcessLine("ht src1_x_q0");
   gROOT->ProcessLine("ht src1_y_q0");
   gROOT->ProcessLine("cd ..");
   gROOT->ProcessLine("cd chksrppacsrc2");
   gROOT->ProcessLine("ht src2_x_idq colz");
   gROOT->ProcessLine("ht src2_y_idq colz");
   gROOT->ProcessLine("ht src2_x_q0");
   gROOT->ProcessLine("ht src2_y_q0");
   gROOT->ProcessLine("cd ..");
   artcanv->cd();
   draw_label("SRPPAC FE12", 0);
   print_canv();
//   artcanv->Update();
//   gSystem->ProcessEvents();
//   getchar();
   
   // FE12 Multiplicity
   gROOT->ProcessLine("zone 2 2");
   artcanv->SetCanvasSize(width, height);
   gROOT->ProcessLine("ht chksrppacsrc1/src1_x_ent");
   gROOT->ProcessLine("ht chksrppacsrc1/src1_y_ent");
   gROOT->ProcessLine("ht chksrppacsrc2/src2_x_ent");
   gROOT->ProcessLine("ht chksrppacsrc2/src2_y_ent");
   artcanv->cd();
   draw_label("SRPPAC FE12 Multiplicity", 0);
   print_canv();
//   artcanv->Update();
//   gSystem->ProcessEvents();
//   getchar();

   // S1 Charge
   gROOT->ProcessLine("zone 2 4");
   artcanv->SetCanvasSize(width, 1.8*height);
   gROOT->ProcessLine("cd chksrppacsr11");
   gROOT->ProcessLine("ht sr11_x_idq colz");
   gROOT->ProcessLine("ht sr11_y_idq colz");
   gROOT->ProcessLine("ht sr11_x_q0");
   gROOT->ProcessLine("ht sr11_y_q0");
   gROOT->ProcessLine("cd ..");
   gROOT->ProcessLine("cd chksrppacsr12");
   gROOT->ProcessLine("ht sr12_x_idq colz");
   gROOT->ProcessLine("ht sr12_y_idq colz");
   gROOT->ProcessLine("ht sr12_x_q0");
   gROOT->ProcessLine("ht sr12_y_q0");
   gROOT->ProcessLine("cd ..");
   artcanv->cd();
   draw_label("SRPPAC S1 Charge", 0);
   print_canv();
//   artcanv->Update();
//   gSystem->ProcessEvents();
//   getchar();

   // S1 Multiplicity
   gROOT->ProcessLine("zone 2 2");
   artcanv->SetCanvasSize(width, height);
   gROOT->ProcessLine("ht chksrppacsr11/sr11_x_ent");
   gROOT->ProcessLine("ht chksrppacsr11/sr11_y_ent");
   gROOT->ProcessLine("ht chksrppacsr12/sr12_x_ent");
   gROOT->ProcessLine("ht chksrppacsr12/sr12_y_ent");
   artcanv->cd();
   draw_label("SRPPAC S1 Multiplicity", 0);
   print_canv();
//   artcanv->Update();
//   gSystem->ProcessEvents();
//   //getchar();

   //gROOT->ProcessLine("fcd 0");
   //gROOT->ProcessLine(".x macro/setalias.C");

   // Pid
   // gROOT->ProcessLine("zone 2 3");
   // gROOT->ProcessLine("ht pid/coin col");
   // gROOT->ProcessLine("ht pid/diae col");
   // gROOT->ProcessLine("ht pid/diat col");
   // gROOT->ProcessLine("ht pid/pid39 col");
   // gROOT->ProcessLine("ht pid/pids0s1 col");
   // gROOT->ProcessLine("ht pid/targetxy col");

   // artcanv->cd();
   // draw_label("PID", 0);
   // print_canv();

   std::string pdf_name_prefix = file_name_prefix + "_" + runname + runnum;
   std::string print_cmd = ".! convert " + pdf_name_prefix + "*.png " + pdf_name_prefix + ".pdf";
   gROOT->ProcessLine(print_cmd.c_str());
   if (print)
   {
      print_cmd = ".! lpr -o fit-to-page -o media=A4 -o sides=two-sided-long-edge " + pdf_name_prefix + ".pdf";
      gROOT->ProcessLine(print_cmd.c_str());
   }

   // Getting mean values
   gROOT->ProcessLine("cd");
   gROOT->ProcessLine("cd chksrppacsr91");
   auto sr91_x_q0 = (TH1D *)gROOT->FindObject("sr91_x_q0");
   auto sr91_y_q0 = (TH1D *)gROOT->FindObject("sr91_y_q0");
   auto sr91_x_ent = (TH1D *)gROOT->FindObject("sr91_x_ent");
   auto sr91_y_ent = (TH1D *)gROOT->FindObject("sr91_y_ent");
   gROOT->ProcessLine("cd");
   gROOT->ProcessLine("cd chksrppacsr92");
   auto sr92_x_q0 = (TH1D *)gROOT->FindObject("sr92_x_q0");
   auto sr92_y_q0 = (TH1D *)gROOT->FindObject("sr92_y_q0");
   auto sr92_x_ent = (TH1D *)gROOT->FindObject("sr92_x_ent");
   auto sr92_y_ent = (TH1D *)gROOT->FindObject("sr92_y_ent");
   gROOT->ProcessLine("cd");
   gROOT->ProcessLine("cd chksrppacsrc1");
   auto src1_x_q0 = (TH1D *)gROOT->FindObject("src1_x_q0");
   auto src1_y_q0 = (TH1D *)gROOT->FindObject("src1_y_q0");
   auto src1_x_ent = (TH1D *)gROOT->FindObject("src1_x_ent");
   auto src1_y_ent = (TH1D *)gROOT->FindObject("src1_y_ent");
   gROOT->ProcessLine("cd");
   gROOT->ProcessLine("cd chksrppacsrc2");
   auto src2_x_q0 = (TH1D *)gROOT->FindObject("src2_x_q0");
   auto src2_y_q0 = (TH1D *)gROOT->FindObject("src2_y_q0");
   auto src2_x_ent = (TH1D *)gROOT->FindObject("src2_x_ent");
   auto src2_y_ent = (TH1D *)gROOT->FindObject("src2_y_ent");
   gROOT->ProcessLine("cd");
   gROOT->ProcessLine("cd chksrppacsr11");
   auto sr11_x_q0 = (TH1D *)gROOT->FindObject("sr11_x_q0");
   auto sr11_y_q0 = (TH1D *)gROOT->FindObject("sr11_y_q0");
   auto sr11_x_ent = (TH1D *)gROOT->FindObject("sr11_x_ent");
   auto sr11_y_ent = (TH1D *)gROOT->FindObject("sr11_y_ent");
   gROOT->ProcessLine("cd");
   gROOT->ProcessLine("cd chksrppacsr12");
   auto sr12_x_q0 = (TH1D *)gROOT->FindObject("sr12_x_q0");
   auto sr12_y_q0 = (TH1D *)gROOT->FindObject("sr12_y_q0");
   auto sr12_x_ent = (TH1D *)gROOT->FindObject("sr12_x_ent");
   auto sr12_y_ent = (TH1D *)gROOT->FindObject("sr12_y_ent");
   
   double sr91_x_q0_mean = sr91_x_q0->GetMean();   
   double sr91_y_q0_mean = sr91_y_q0->GetMean();
   double sr92_x_q0_mean = sr92_x_q0->GetMean();   
   double sr92_y_q0_mean = sr92_y_q0->GetMean();   
   double src1_x_q0_mean = src1_x_q0->GetMean();   
   double src1_y_q0_mean = src1_y_q0->GetMean();   
   double src2_x_q0_mean = src2_x_q0->GetMean();   
   double src2_y_q0_mean = src2_y_q0->GetMean();   
   double sr11_x_q0_mean = sr11_x_q0->GetMean();   
   double sr11_y_q0_mean = sr11_y_q0->GetMean();   
   double sr12_x_q0_mean = sr12_x_q0->GetMean();   
   double sr12_y_q0_mean = sr12_y_q0->GetMean();

   double sr91_x_ent_mean = sr91_x_ent->GetMean();   
   double sr91_y_ent_mean = sr91_y_ent->GetMean();
   double sr92_x_ent_mean = sr92_x_ent->GetMean();   
   double sr92_y_ent_mean = sr92_y_ent->GetMean();   
   double src1_x_ent_mean = src1_x_ent->GetMean();   
   double src1_y_ent_mean = src1_y_ent->GetMean();   
   double src2_x_ent_mean = src2_x_ent->GetMean();   
   double src2_y_ent_mean = src2_y_ent->GetMean();   
   double sr11_x_ent_mean = sr11_x_ent->GetMean();   
   double sr11_y_ent_mean = sr11_y_ent->GetMean();   
   double sr12_x_ent_mean = sr12_x_ent->GetMean();   
   double sr12_y_ent_mean = sr12_y_ent->GetMean();

   // Please edit below as you like
   std::cout << std::endl;
   std::cout << std::fixed << std::setprecision(3); 
   std::cout << std::setw(11) << ""
	     << std::setw(11) << "x_q0_mean"
	     << std::setw(11) << "y_q0_mean"
	     << std::setw(11) << "x_ent_mean"
	     << std::setw(11) << "x_ent_mean" << std::endl;
   std::cout << std::setw(11) << "sr91"
	     << std::setw(11) << sr91_x_q0_mean 
	     << std::setw(11) << sr91_y_q0_mean
	     << std::setw(11) << sr91_x_ent_mean 
	     << std::setw(11) << sr91_y_ent_mean << std::endl;
   std::cout << std::setw(11) << "sr92"
	     << std::setw(11) << sr92_x_q0_mean 
	     << std::setw(11) << sr92_y_q0_mean
	     << std::setw(11) << sr92_x_ent_mean 
	     << std::setw(11) << sr92_y_ent_mean << std::endl;

   std::cout << std::setw(11) << "src1"
	     << std::setw(11) << src1_x_q0_mean 
	     << std::setw(11) << src1_y_q0_mean
	     << std::setw(11) << src1_x_ent_mean 
	     << std::setw(11) << src1_y_ent_mean << std::endl;
   std::cout << std::setw(11) << "src2"
	     << std::setw(11) << src2_x_q0_mean 
	     << std::setw(11) << src2_y_q0_mean
	     << std::setw(11) << src2_x_ent_mean 
	     << std::setw(11) << src2_y_ent_mean << std::endl;

   std::cout << std::setw(11) << "sr11"
	     << std::setw(11) << sr11_x_q0_mean 
	     << std::setw(11) << sr11_y_q0_mean
	     << std::setw(11) << sr11_x_ent_mean 
	     << std::setw(11) << sr11_y_ent_mean << std::endl;
   std::cout << std::setw(11) << "sr12"
	     << std::setw(11) << sr12_x_q0_mean 
	     << std::setw(11) << sr12_y_q0_mean
	     << std::setw(11) << sr12_x_ent_mean 
	     << std::setw(11) << sr12_y_ent_mean << std::endl;

}
