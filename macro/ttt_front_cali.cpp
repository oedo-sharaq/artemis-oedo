#include <iostream>
#include <vector>

std::vector <int> sort_permutation(std::vector <double> A, std::vector <double> B){
  std::vector<int> indices(B.size());
  std::iota(indices.begin(), indices.end(), 0);
  std::sort(indices.begin(), indices.end(),
            [&](int a, int b) -> bool {
              return A.at(a) < A.at(b);
            });
  return indices;
}


void ttt_front_cali(TH2F *hin)
{
    ofstream myfile;
    myfile.open("test/ttt_front_para.txt");
    std::vector<double> Ealpha = {3.18269, 5.48556, 5.80477};
    std::vector<double> ch;
    std::vector<double> ch_error;
    std::vector<double> ch0; //unsorted
    std::vector<double> ch0_error;
    const int N = hin->GetNbinsX();
    const int Ny = hin->GetNbinsY();
    const double ymin = front->GetYaxis()->GetXmin();
    const double ymax = front->GetYaxis()->GetXmax();
    TSpectrum *spec = new TSpectrum();
    // std::vector <double> peakpos;
    int Npeak;
    //int Npeak_nomarkov;
    double *peakposition;
    double *count;
    double *para;
    Int_t num = 0;
    TH1D* h[N+1];
    TGraphErrors* g[N+1];
    for (int i = 1; i <= N; i++)
    {
        //TH1D *hpy = hin->ProjectionY("hpy", i, i);
        h[i] = hin->ProjectionY(Form("h%d",i), i, i);
        // hpy->Draw();
        // Npeak = spec->Search(hpy, 0, "", 0.2);
        Npeak = spec->Search(h[i], 0, "", 0.35);
        //TF1 *f1 = new TF1("f1", gfit,0,7000,12);
        TF1 *f1 = new TF1("f1", "gaus(0)+gaus(3)+gaus(6)");
        TF1 *f2 = new TF1("f2", "gaus(0)+gaus(3)");
        TF1 *f3 = new TF1("f3", "pol1");
        if (Npeak == 3)
        {
            peakposition = spec->GetPositionX();
            //std::sort(peakposition,peakposition + 3);
            count = spec->GetPositionY();
            // std::sort(count, count + 3);
            for (int j = 1; j<=3; j++){
                f1->SetParameter(3*j-3,count[j-1]);
                f1->SetParLimits(3*j-3,0,count[j-1]);
                f1->SetParameter(3*j-2,peakposition[j-1]);
                f1->SetParLimits(3*j-2,peakposition[j-1]-50,peakposition[j-1]+50);
                f1->SetParameter(3*j-1,10);
                f1->SetParLimits(3*j-1,0,50);
            }
            h[i]->Fit("f1", "", "", ymin, ymax);
            ch0.push_back(f1->GetParameter(1));
            ch0.push_back(f1->GetParameter(4));
            ch0.push_back(f1->GetParameter(7));
            //ch0.push_back(f1->GetParameter(10));
            ch0_error.push_back(f1->GetParError(1));
            ch0_error.push_back(f1->GetParError(4));
            ch0_error.push_back(f1->GetParError(7));
            //ch0_error.push_back(f1->GetParError(10));
            std::vector <int> indices = sort_permutation(ch0,ch0_error);
            for (int i = 0; i < 3; i++){
                ch.push_back(ch0.at(indices.at(i)));
                ch_error.push_back(ch0_error.at(indices.at(i)));
                //cout << ch.at(i) << " " << ch_error.at(i) << endl;
            }

            g[i] = new TGraphErrors(3, &ch[0], &Ealpha[0],&ch_error[0],NULL);
            g[i]->SetMarkerColor(4);
            g[i]->SetMarkerStyle(21);
            g[i]->Draw("ap");
            f3->SetParameters(0.5,0.001);
            g[i]->Fit("f3", "", "", 1000, 8000);
            para = f3->GetParameters();
            // myfile << i - 1 << " " << para[0] << " " << para[1] << endl;
            myfile << para[0] << " " << para[1] << endl;
            cout << "ID: " << i - 1 << endl;
            // cout << peakposition[0] << " " << count[0] << endl;
            // cout << peakposition[1] << " " << count[1] << endl;
            // cout << peakposition[2] << " " << count[2] << endl;
            ch0.clear();
            ch0_error.clear();
            ch.clear();
            ch_error.clear();
            indices.clear();
            //g->Delete();
            //hpy->Delete();
        }
        else if (Npeak == 2)
        {
           peakposition = spec->GetPositionX();
            //std::sort(peakposition,peakposition + 3);
            count = spec->GetPositionY();
            // std::sort(count, count + 3);
            for (int j = 1; j<=3; j++){
                if (j<=2){
                f1->SetParameter(3*j-3,count[j-1]);
                f1->SetParLimits(3*j-3,0,count[j-1]);
                f1->SetParameter(3*j-2,peakposition[j-1]);
                f1->SetParLimits(3*j-2,peakposition[j-1]-50,peakposition[j-1]+50);
                f1->SetParameter(3*j-1,10);
                f1->SetParLimits(3*j-1,0,50);
                }
                else{
                f1->SetParameter(3*j-3,std::min(count[0],count[1]));
                f1->SetParLimits(3*j-3,0,std::min(count[0],count[1])*0.8);
                f1->SetParameter(3*j-2,std::max(peakposition[0],peakposition[1])+200);
                f1->SetParLimits(3*j-2,std::max(peakposition[0],peakposition[1])+150,std::max(peakposition[0],peakposition[1])+250);
                f1->SetParameter(3*j-1,10);
                f1->SetParLimits(3*j-1,0,50);
                }
            }
            h[i]->Fit("f1", "", "", ymin, ymax);
            ch0.push_back(f1->GetParameter(1));
            ch0.push_back(f1->GetParameter(4));
            ch0.push_back(f1->GetParameter(7));
            //ch0.push_back(f1->GetParameter(10));
            ch0_error.push_back(f1->GetParError(1));
            ch0_error.push_back(f1->GetParError(4));
            ch0_error.push_back(f1->GetParError(7));
            //ch0_error.push_back(f1->GetParError(10));
            std::vector <int> indices = sort_permutation(ch0,ch0_error);
            for (int i = 0; i < 3; i++){
                ch.push_back(ch0.at(indices.at(i)));
                ch_error.push_back(ch0_error.at(indices.at(i)));
                //cout << ch.at(i) << " " << ch_error.at(i) << endl;
            }

            g[i] = new TGraphErrors(3, &ch[0], &Ealpha[0],&ch_error[0],NULL);
            g[i]->SetMarkerColor(4);
            g[i]->SetMarkerStyle(21);
            g[i]->Draw("ap");
            f3->SetParameters(0.5,0.001);
            g[i]->Fit("f3", "", "", 1000, 8000);
            para = f3->GetParameters();
            // myfile << i - 1 << " " << para[0] << " " << para[1] << endl;
            myfile << para[0] << " " << para[1] << endl;
            cout << "ID: " << i - 1 << endl;
            // cout << peakposition[0] << " " << count[0] << endl;
            // cout << peakposition[1] << " " << count[1] << endl;
            // cout << peakposition[2] << " " << count[2] << endl;
            ch0.clear();
            ch0_error.clear();
            ch.clear();
            ch_error.clear();
            indices.clear();
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


