/**
 * @file DumpParquet.cpp
 * @author Rin Yokoyama (yokoyama@cns.s.u-tokyo.ac.jp)
 * @brief Dump artemis output objects to a parquet file
 * @version 0.1
 * @date 2024-01-17
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
#include "TROOT.h"
#include "ROOT/RDataFrame.hxx"
#include "TClonesArray.h"
#include "TEventHeader.h"
#include "TTimingChargeData.h"
#include <arrow/api.h>
#include <arrow/io/api.h>
#include <arrow/pretty_print.h>
#include <arrow/record_batch.h>
#include <arrow/type.h>
#include <parquet/arrow/writer.h>
#include <vector>
#include <functional>
#include "DumpParquet.hpp"

/** prints usage **/
void usage(char *argv0)
{
    std::cout << "[DumpParquet]: Usage: "
              << argv0 << "-c [config_file] -n [n_workers] -o [output_file]"
              << std::endl;
}

// Main function
int main(int argc, char **argv)
{
    std::string input_file_name;
    std::string output_file_name = "output.parquet";
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

    if (input_file_name.empty())
    {
        usage(argv[0]);
        return 1;
    }

    // Enable multithreading
    // ROOT::EnableImplicitMT(n_workers);

    // Create RDataFrame from a tree.
    ROOT::RDataFrame d("tree", input_file_name);

    // Define builder objects
    TTimingChargeDataBuilder sr91x("sr91x");
    TTimingChargeDataBuilder sr91y("sr91y");
    TTimingChargeDataBuilder diapad("diapad");

    // Define the memory pool
    auto pool = arrow::default_memory_pool();

    // Process tree
    auto output = d.Define("sr91x_vec", [&](const TClonesArray &input)
                           { return sr91x.GetVector(input); },
                           {"sr91_x_cal"})
                      .Define("sr91y_vec", [&](const TClonesArray &input)
                              { return sr91y.GetVector(input); },
                              {"sr91_y_cal"})
                      .Define("diapad_vec", [&](const TClonesArray &input)
                              { return diapad.GetVector(input); },
                              {"diapad"});
    output.Foreach([&](const std::vector<art::TTimingChargeData *> &input)
                   { sr91x.FillArrow(input); },
                   {"sr91x_vec"});
    output.Foreach([&](const std::vector<art::TTimingChargeData *> &input)
                   { sr91y.FillArrow(input); },
                   {"sr91y_vec"});
    output.Foreach([&](const std::vector<art::TTimingChargeData *> &input)
                   { diapad.FillArrow(input); },
                   {"diapad_vec"});

    // Finalize the arrays
    arrow::FieldVector fieldVector;
    arrow::ArrayVector arrayVector;
    sr91x.Finalize(fieldVector, arrayVector);
    sr91y.Finalize(fieldVector, arrayVector);
    diapad.Finalize(fieldVector, arrayVector);

    // Create the table
    std::shared_ptr<arrow::Schema> schema = arrow::schema(fieldVector);
    auto table = arrow::Table::Make(schema, arrayVector);

    // Write to file
    std::shared_ptr<arrow::io::FileOutputStream> outfile;
    PARQUET_ASSIGN_OR_THROW(
        outfile,
        arrow::io::FileOutputStream::Open(output_file_name));

    PARQUET_THROW_NOT_OK(
        parquet::arrow::WriteTable(*table, pool, outfile));

    return 0;
}