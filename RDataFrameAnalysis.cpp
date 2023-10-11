// RDataFrameAnalysis.cpp created by Rin Yokoyama on \date April 18, 2023
// This program generates root files with a tree containing a branch of the ExampleTwoDataClass.
// named "ExampleData". ExampleData.data1_ and data2_ will be filled with random Gaussian events.
#include <iostream>
#include "TROOT.h"
#include "ROOT/RDataFrame.hxx"
#include "TClonesArray.h"
#include "TEventHeader.h"
#include "TAPV8008Data.h"

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
    ROOT::EnableImplicitMT(n_workers);

    // Create RDataFrame from a tree, "exampleTree" in the "example.root" file.
    ROOT::RDataFrame d("tree", input_file_name);

    // A function to loop over TClonesArray and fill a data by getfunc
    auto fillVector = [](const TClonesArray &array, double (*func)(art::TAPV8008Data *))
    {
        std::vector<double> vec;
        TIter next(&array);
        TObject *obj;
        while ((obj = next()))
        {
            auto data = func((art::TAPV8008Data *)obj);
            vec.emplace_back(data);
        }
        return vec;
    };

    // Function to define energy
    const auto getCharge = [&fillVector](const TClonesArray &input)
    {
        return fillVector(input, [](art::TAPV8008Data *x)
                          { return x->GetCharge(); });
    };

    // Function to define timeing
    const auto getTiming = [&fillVector](const TClonesArray &input)
    {
        return fillVector(input, [](art::TAPV8008Data *x)
                          { return x->GetTiming(); });
    };

    // Process tree
    auto output = d.Define("time", getTiming, {"rawdata"})
                      .Define("energy", getCharge, {"rawdata"});

    // save new branches to output_file_name tree
    output.Snapshot("tree", output_file_name, {"time", "energy"});

    // Fill the histogram
    auto hist = output.Histo2D({"ET", "ET", 1000, 0, 1000, 1000, -1e6, 1e6}, "energy", "time");

    TFile output_file(output_file_name.c_str(), "UPDATE");
    hist->Write();
    output_file.Close();
    return 0;
}