// RDataFrameAnalysis.cpp created by Rin Yokoyama on \date April 18, 2023
// This program generates root files with a tree containing a branch of the ExampleTwoDataClass.
// named "ExampleData". ExampleData.data1_ and data2_ will be filled with random Gaussian events.
#include <iostream>
#include "TROOT.h"
#include "ROOT/RDataFrame.hxx"
#include "TClonesArray.h"
#include "TEventHeader.h"
#include "TTimingChargeData.h"

/** prints usage **/
void usage(char *argv0)
{
    std::cout << "[RDataFrameAnalysis]: Usage: "
              << argv0 << "-c [config_file] -n [n_workers] -o [output_file]"
              << std::endl;
}

// Main function
int main(int argc, char **argv)
{
    std::string input_file_name;
    std::string output_file_name = "output.root";
    Int_t n_workers = 1;

    /** parsing commandline arguments **/
    int opt = 0;
    while ((opt = getopt(argc, argv, "o:n:i:")) != -1)
    {
        switch (opt)
        {
        case 'o':
            output_file_name = optarg;
            break;
        case 'n':
            n_workers = std::stoi(optarg);
            break;
        case 'i':
            input_file_name = optarg;
            break;
        default:
            usage(argv[0]);
            return 1;
            break;
        }
    }

    // Enable multithreading
    //    ROOT::EnableImplicitMT(n_workers);

    // Create RDataFrame from a tree, "exampleTree" in the "example.root" file.
    ROOT::RDataFrame d("tree", input_file_name);

    // Pick up the first N entries
    auto dn = d.Range(0, 30);

    // A function to loop over TClonesArray and fill a data by getfunc
    const auto getVector = [](const TClonesArray &input)
    {
        std::vector<art::TTimingChargeData *> vec;
        TIter next(&input);
        TObject *obj;
        while ((obj = next()))
        {
            vec.emplace_back((art::TTimingChargeData *)obj);
        }
        return vec;
    };

    // Function to change TOT to charge
    const auto TOT2Charge = [](std::vector<art::TTimingChargeData *> &input)
    {
        for (const auto &data : input)
        {
            auto TOT = data->GetCharge();
            double charge;
            if (TOT < 20)
            {
                charge = 0.004667 * TOT + 0.006667;
            }
            else
            {
                charge = 0.000469 * TOT * TOT - 0.01415 * TOT + 0.19722;
            }
            data->SetCharge(charge);
        }
        return input;
    };

    std::map<int, double> calib_factors;
    // Function to calibrate energy
    auto calibrateVec = [&calib_factors](std::vector<art::TTimingChargeData *> &input)
    {
        for (auto &data : input)
        {
            // data->SetCharge(data->GetCharge() * calib_factors[data->GetID()]);
        }
        return input;
    };

    //    // Function to sort vector
    //  const auto sortVec = [](std::vector<art::TTimingChargeData *> &input)
    // {
    //   std::sort(input.begin(), input.end(), [](const art::TTimingChargeData *x, const art::TTimingChargeData *y)
    //                  { return x->GetCharge() > y->GetCharge(); });
    // };

    // Function to sort vector
    const auto sortVec = [](std::vector<art::TTimingChargeData *> &input)
    {
        std::sort(input.begin(), input.end(), [](const art::TTimingChargeData *x, const art::TTimingChargeData *y)
                  { return x->GetCharge() < y->GetCharge(); });
        return input;
    };

    // Function to define charge
    const auto getCharge = [](const std::vector<art::TTimingChargeData *> &input)
    {
        std::vector<double> charge;
        for (const auto &data : input)
        {
            charge.emplace_back(data->GetCharge());
        }
        return charge;
    };

    // Function to define ID
    const auto getId = [](const std::vector<art::TTimingChargeData *> &input)
    {
        std::vector<double> id;
        for (const auto &data : input)
        {
            id.emplace_back(data->GetID());
        }
        return id;
    };

    // Process tree
    //    auto output = d.Define("vector", getVector, {"sr91_x_cal"});
    auto output = dn.Define("vector", getVector, {"sr91_x_cal"})
                      .Define("charge_vec", TOT2Charge, {"vector"})
                      .Define("calibrated_vec", calibrateVec, {"charge_vec"})
                      .Define("sorted_vec", sortVec, {"calibrated_vec"});
    auto outdata = output.Define("charge", getCharge, {"sorted_vec"})
                       .Define("id", getId, {"sorted_vec"});

    // save new branches to output_file_name tree
    outdata.Snapshot("tree", output_file_name, {"id", "charge"});

    // Fill the histogram
    // auto hist = output.Histo2D({"ET", "ET", 1000, 0, 1000, 1000, -1e6, 1e6}, "energy", "time");

    // TFile output_file(output_file_name.c_str(), "UPDATE");
    // hist->Write();
    // output_file.Close();
    return 0;
}
