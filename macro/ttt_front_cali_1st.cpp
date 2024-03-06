#include <iostream>
#include <vector>

void ttt_front_cali(TH2F *hin)
{
    ofstream myfile;
    myfile.open("test/ttt_front_para.txt");
    std::vector<double> Ealpha = {3.18269, 5.48556, 5.80477};
    std::vector<double> Ealpha1 = {3.18269, 0.5*(5.48556+5.80477)};
    std::vector<double> ch;
    const int N = hin->GetNbinsX();
    const int Ny = hin->GetNbinsY();
    const double ymin = all->GetYaxis()->GetXmin();
    const double ymax = all->GetYaxis()->GetXmax();
    TSpectrum *spec = new TSpectrum();
    // std::vector <double> peakpos;
    int Npeak;
    int Npeak_nomarkov;
    double *peakposition;
    double *count;
    double *para;
    Int_t num = 0;
    // TH1F *hit = new TH1F();
    // TF1 *f1 = new TF1("f1", "gaus(0)+gaus(3)+gaus(6)");
    // TF1 *f3 = new TF1("f3", "pol1");
    TH1D* h[2000];
    for (int i = 1; i <= N; i++)
    {
        //TH1D *hpy = hin->ProjectionY("hpy", i, i);
        h[i] = hin->ProjectionY(Form("h%d",i), i, i);
        if (i>128){
            //h[i]->Rebin(2);
        }
        // hpy->Draw();
        // Npeak = spec->Search(hpy, 0, "", 0.2);
        Npeak = spec->Search(h[i], 0, "", 0.35);
        Npeak_nomarkov = spec->Search(h[i], 0, "noMarkov", 0.35);
        TF1 *f1 = new TF1("f1", "gaus(0)+gaus(3)+gaus(6)");
        TF1 *f2 = new TF1("f2", "gaus(0)+gaus(3)");
        TF1 *f3 = new TF1("f3", "pol1");
        
        if (Npeak == 3 || Npeak_nomarkov == 3)
        {
            if (Npeak == 3){
                Npeak = spec->Search(h[i], 0, "", 0.35);
            }
            else{
                Npeak_nomarkov = spec->Search(h[i], 0, "noMarkov", 0.35);
            }
            peakposition = spec->GetPositionX();
            // std::sort(peakposition, peakposition + 3);
            count = spec->GetPositionY();
            // std::sort(count, count + 3);
            f1->SetParameters(count[0], peakposition[0], 10, count[1], peakposition[1], 10, count[2], peakposition[2], 10);
            // hpy->Fit("f1", "", "", ymin, ymax);
            h[i]->Fit("f1", "", "", ymin, ymax);
            ch.push_back(f1->GetParameter(1));
            ch.push_back(f1->GetParameter(4));
            ch.push_back(f1->GetParameter(7));
            std::sort(ch.begin(), ch.end());
            TGraph *g = new TGraph(3, &ch[0], &Ealpha[0]);
            g->Draw("ap*");
            g->Fit("f3", "", "", 1000, 8000);
            para = f3->GetParameters();
            // myfile << i - 1 << " " << para[0] << " " << para[1] << endl;
            myfile << para[0] << " " << para[1] << endl;
            cout << "ID: " << i - 1 << endl;
            // cout << peakposition[0] << " " << count[0] << endl;
            // cout << peakposition[1] << " " << count[1] << endl;
            // cout << peakposition[2] << " " << count[2] << endl;
            ch.clear();
            g->Delete();
            //hpy->Delete();
        }
        else if (Npeak == 2 || Npeak_nomarkov == 2 || Npeak > 3 || Npeak_nomarkov > 3){
            h[i]->Rebin(2);
            if (i == 281){
                h[i]->Rebin(2);
            }
            Npeak_nomarkov = spec->Search(h[i], 0, "noMarkov", 0.35);
            if (Npeak_nomarkov == 3){
            peakposition = spec->GetPositionX();
            // std::sort(peakposition, peakposition + 3);
            count = spec->GetPositionY();
            // std::sort(count, count + 3);
            f1->SetParameters(count[0], peakposition[0], 10, count[1], peakposition[1], 10, count[2], peakposition[2], 10);
            // hpy->Fit("f1", "", "", ymin, ymax);
            h[i]->Fit("f1", "", "", ymin, ymax);
            ch.push_back(f1->GetParameter(1));
            ch.push_back(f1->GetParameter(4));
            ch.push_back(f1->GetParameter(7));
            std::sort(ch.begin(), ch.end());
            TGraph *g = new TGraph(3, &ch[0], &Ealpha[0]);
            g->Draw("ap*");
            g->Fit("f3", "", "", 1000, 8000);
            para = f3->GetParameters();
            // myfile << i - 1 << " " << para[0] << " " << para[1] << endl;
            myfile << para[0] << " " << para[1] << endl;
            cout << "ID: " << i - 1 << endl;
            // cout << peakposition[0] << " " << count[0] << endl;
            // cout << peakposition[1] << " " << count[1] << endl;
            // cout << peakposition[2] << " " << count[2] << endl;
            ch.clear();
            g->Delete();
            }
            else if (Npeak_nomarkov == 2){
            peakposition = spec->GetPositionX();
            // std::sort(peakposition, peakposition + 3);
            count = spec->GetPositionY();
            // std::sort(count, count + 3);
            f2->SetParameters(count[0], peakposition[0], 10, count[1], peakposition[1], 10);
            // hpy->Fit("f1", "", "", ymin, ymax);
            h[i]->Fit("f2", "", "", ymin, ymax);
            ch.push_back(f2->GetParameter(1));
            ch.push_back(f2->GetParameter(4));
            std::sort(ch.begin(), ch.end());
            TGraph *g = new TGraph(2, &ch[0], &Ealpha1[0]);
            g->Draw("ap*");
            g->Fit("f3", "", "", 1000, 8000);
            para = f3->GetParameters();
            // myfile << i - 1 << " " << para[0] << " " << para[1] << endl;
            myfile << para[0] << " " << para[1] << endl;
            cout << "ID: " << i - 1 << endl;
            // cout << peakposition[0] << " " << count[0] << endl;
            // cout << peakposition[1] << " " << count[1] << endl;
            // cout << peakposition[2] << " " << count[2] << endl;
            ch.clear();
            g->Delete(); 
            }
            else if (i == 393){
                Npeak_nomarkov = spec->Search(h[i], 0, "noMarkov", 0.1);
                peakposition = spec->GetPositionX();
            // std::sort(peakposition, peakposition + 3);
                count = spec->GetPositionY();
            // std::sort(count, count + 3);
                f1->SetParameters(count[0], peakposition[0], 10, count[1], peakposition[1], 10, count[1], peakposition[1]+200, 10);
            // hpy->Fit("f1", "", "", ymin, ymax);
            h[i]->Fit("f1", "", "", ymin, ymax);
            ch.push_back(f1->GetParameter(1));
            ch.push_back(f1->GetParameter(4));
            ch.push_back(f1->GetParameter(7));
            std::sort(ch.begin(), ch.end());
            TGraph *g = new TGraph(3, &ch[0], &Ealpha[0]);
            g->Draw("ap*");
            g->Fit("f3", "", "", 1000, 8000);
            para = f3->GetParameters();
            // myfile << i - 1 << " " << para[0] << " " << para[1] << endl;
            myfile << para[0] << " " << para[1] << endl;
            cout << "ID: " << i - 1 << endl;
            // cout << peakposition[0] << " " << count[0] << endl;
            // cout << peakposition[1] << " " << count[1] << endl;
            // cout << peakposition[2] << " " << count[2] << endl;
            ch.clear();
            g->Delete();
            }
            else {
                num++;
               myfile << 0 << " " << 1 << endl; 
            }
        }
        else
        {
            num++;
            // myfile << i - 1 << " " << 0 << " " << 1 << endl;
            myfile << 0 << " " << 1 << endl;
            //hpy->Delete();
        }
        f1->Delete();
        f3->Delete();
    }
    myfile.close();
    cout << "abnormal: " << num  << endl;
}


