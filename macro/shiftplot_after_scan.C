
void shiftplot_after_scan(const std::string &runname, const std::string &runnum, const std::string &getnum, const bool print = true)
{

   gROOT->SetBatch();
/*
   {
      std::string cmd = "add steering/shift.yaml NAME=" + runname + " NUM=" + runnum + " GET=" + getnum;
      gROOT->ProcessLine(cmd.c_str());
      std::cout << "Starting the loop... " << std::endl;
      art::TLoopManager::Instance()->GetLoop()->Resume();
   }
*/

   gROOT->ProcessLine(".! mkdir shift_figures 2>> /dev/null");
   std::string file_name_prefix = "shift_figures/shift";
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

   auto artcanv = (TCanvas *)gROOT->FindObject("artcanvas");
   {
      auto height = artcanv->GetWh();
      auto width = artcanv->GetWw();
      artcanv->SetCanvasSize(width, 1.8 * height);
   }
   auto p = (TPaveLabel *)artcanv->GetListOfPrimitives()->At(1);
   std::string title = p->GetTitle();
   run_name = title.substr(23, 4);
   artcanv->cd();
   draw_label("SRPPAC FE9", 0);
   print_canv();

   gROOT->ProcessLine("zone 2 4");
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

   gROOT->ProcessLine("zone 2 4");
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
   draw_label("SRPPAC S1", 0);
   print_canv();

   // S0
   gROOT->ProcessLine("zone 2 3");
   gROOT->ProcessLine("cd chk_ttt");
   gROOT->ProcessLine("ht ttt_front_id");
   gROOT->ProcessLine("ht ttt_front_m");
   gROOT->ProcessLine("ht ttt_front_hit_c");
   gROOT->ProcessLine("ht ttt_front_maxsample_charge colz");
   gROOT->ProcessLine("ht ttt_front_sample_clock colz");
   gROOT->ProcessLine("ht ttt_front_pulse_clock colz");

   artcanv->cd();
   draw_label("TTT_front", 0);
   print_canv();

   gROOT->ProcessLine("zone 2 3");
   gROOT->ProcessLine("ht ttt_back_id");
   gROOT->ProcessLine("ht ttt_back_m");
   gROOT->ProcessLine("ht ttt_back_hit_c");
   gROOT->ProcessLine("ht ttt_back_maxsample_charge colz");
   gROOT->ProcessLine("ht ttt_back_sample_clock colz");
   gROOT->ProcessLine("ht ttt_back_pulse_clock colz");

   artcanv->cd();
   draw_label("TTT_back", 0);
   print_canv();

   gROOT->ProcessLine("zone 2 3");
   gROOT->ProcessLine("ht ttt_front_id_vs_ttt_back_id colz");
   gStyle->SetStatY(0.5);
   gROOT->ProcessLine("ht ttt_front_m_vs_ttt_back_m colz");
   gStyle->SetStatY(0.94);
   gROOT->ProcessLine("cd ..");

   artcanv->cd();
   draw_label("TTT", 0);
   print_canv();

   gROOT->ProcessLine("cd chk_s0vme");
   gROOT->ProcessLine("zone 2 2");
   gROOT->ProcessLine("ht yy1fraw_id_q colz");
   gROOT->ProcessLine("ht csiraw_pre_id_q colz");
   gROOT->ProcessLine("ht tinat_id_t colz");
   gROOT->ProcessLine("cd ..");

   artcanv->cd();
   draw_label("S0 VME", 0);
   print_canv();

#if 0
   gROOT->ProcessLine("cd chk_correlation_ttt_csi");
   gROOT->ProcessLine("zone 4 4");

   gROOT->ProcessLine("ht t_c1_qq colz");
   gROOT->ProcessLine("ht t_c2_qq colz");
   gROOT->ProcessLine("ht t_c3_qq colz");
   gROOT->ProcessLine("ht t_c4_qq colz");
   gROOT->ProcessLine("ht t_c5_qq colz");
   gROOT->ProcessLine("ht t_c6_qq colz");
   gROOT->ProcessLine("ht t_c7_qq colz");
   gROOT->ProcessLine("ht t_c8_qq colz");
   gROOT->ProcessLine("ht t_c9_qq colz");
   gROOT->ProcessLine("ht t_c10_qq colz");
   gROOT->ProcessLine("ht t_c11_qq colz");
   gROOT->ProcessLine("ht t_c12_qq colz");
   gROOT->ProcessLine("ht t_c13_qq colz");
   gROOT->ProcessLine("ht t_c14_qq colz");
   gROOT->ProcessLine("ht t_c15_qq colz");
   gROOT->ProcessLine("ht t_c16_qq colz");
   gROOT->ProcessLine("cd ..");

   artcanv->cd();
   draw_label("S0 Correlation", 0);
   print_canv();
#endif

#if 1
   // S1 IC
   gROOT->ProcessLine("zone 2 2");
   gROOT->ProcessLine("ht ic/s1ic_chargecal col");
   gROOT->ProcessLine("ht ic/s1ic_chargecal_xy col");
   gROOT->ProcessLine("ht ic/s1ic_timing col");

   artcanv->cd();
   draw_label("S1IC", 0);
   print_canv();

#endif
#if 0
   // Pid
   gROOT->ProcessLine("zone 2 3");
   gROOT->ProcessLine("ht pid/coin col");
   gROOT->ProcessLine("ht pid/diae col");
   gROOT->ProcessLine("ht pid/diat col");
   gROOT->ProcessLine("ht pid/pid39 col");
   gROOT->ProcessLine("ht pid/pids0s1 col");
   gROOT->ProcessLine("ht pid/targetxy col");

   artcanv->cd();
   draw_label("PID", 0);
   print_canv();
#endif

   std::string pdf_name_prefix = file_name_prefix + "_" + runname + runnum;
   std::string print_cmd = ".! convert " + pdf_name_prefix + "*.png " + pdf_name_prefix + ".pdf";
   gROOT->ProcessLine(print_cmd.c_str());
   if (print)
   {
      print_cmd = ".! lpr -o fit-to-page -o media=A4 -o sides=two-sided-long-edge " + pdf_name_prefix + ".pdf";
      gROOT->ProcessLine(print_cmd.c_str());
   }
}
