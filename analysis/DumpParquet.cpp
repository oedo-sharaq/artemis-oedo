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
#include "TTimingChargeData.h"
#include <arrow/api.h>
#include <arrow/io/api.h>
#include <arrow/pretty_print.h>
#include <arrow/record_batch.h>
#include <arrow/type.h>
#include <parquet/arrow/writer.h>
#include <vector>
#include <functional>
#include <TSystem.h>
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
        TString dypath = gSystem->GetDynamicPath();
        TString incpath = gSystem->GetIncludePath();
        incpath.Append(gSystem->GetFromPipe("artemis-config --cflags"));
        dypath.Append(gSystem->GetFromPipe("artemis-config --dypaths"));

        dypath.Append(":/home/sh12s24/art_analysis/user/srppac_newproc/install/lib");
        incpath.Append(" -I/home/sh12s24/art_analysis/user/srppac_newproc/install/include");

        // dypath.Append(":/opt/GETDecoder/lib");
        // incpath.Append(" -I/opt/GETDecoder/include");

        gSystem->SetDynamicPath(dypath);
        gSystem->SetIncludePath(incpath);
        // gSystem->Load("libGETDecoder");
        // gSystem->Load("libMinuit");
        // gSystem->Load("libGenetic");
        // gSystem->Load("libartshare");
        // gSystem->Load("libCAT");
        gSystem->Load("liboedo");
        gSystem->Load("libartget_sh12");

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
        TTimingChargeDataBuilder sr91x_raw("sr91x_raw");
        TTimingChargeDataBuilder sr91y_raw("sr91y_raw");
        TTimingChargeDataBuilder sr92x_raw("sr92x_raw");
        TTimingChargeDataBuilder sr92y_raw("sr92y_raw");
        TTimingChargeDataBuilder src1x_raw("src1x_raw");
        TTimingChargeDataBuilder src1y_raw("src1y_raw");
        TTimingChargeDataBuilder src2x_raw("src2x_raw");
        TTimingChargeDataBuilder src2y_raw("src2y_raw");
        TTimingChargeDataBuilder sr11x_raw("sr11x_raw");
        TTimingChargeDataBuilder sr11y_raw("sr11y_raw");
        TTimingChargeDataBuilder sr12x_raw("sr12x_raw");
        TTimingChargeDataBuilder sr12y_raw("sr12y_raw");
        TSRPPACPlaneDataBuilder src1x("src1x");
        TSRPPACPlaneDataBuilder src1y("src1y");
        TSRPPACPlaneDataBuilder src2x("src2x");
        TSRPPACPlaneDataBuilder src2y("src2y");
        TSRPPACPlaneDataBuilder src1x_qt("src1x_qt");
        TSRPPACPlaneDataBuilder src1y_qt("src1y_qt");
        TSRPPACPlaneDataBuilder src2x_qt("src2x_qt");
        TSRPPACPlaneDataBuilder src2y_qt("src2y_qt");
        TSRPPACPlaneDataBuilder src1x_gl("src1x_gl");
        TSRPPACPlaneDataBuilder src1y_gl("src1y_gl");
        TSRPPACPlaneDataBuilder src2x_gl("src2x_gl");
        TSRPPACPlaneDataBuilder src2y_gl("src2y_gl");
        TTimingChargeDataBuilder activeslit("activeslit");
        // TTimingChargeDataBuilder diapad("diapad");

        // Define the memory pool
        auto pool = arrow::default_memory_pool();

        // Process tree
        auto output = d.Define("sr91x_raw_vec", [&](const TClonesArray &input)
                               { return sr91x_raw.GetVector(input); },
                               {"sr91_x_cal"})
                          .Define("sr91y_raw_vec", [&](const TClonesArray &input)
                                  { return sr91y_raw.GetVector(input); },
                                  {"sr91_y_cal"})
                          .Define("sr92x_raw_vec", [&](const TClonesArray &input)
                                  { return sr92x_raw.GetVector(input); },
                                  {"sr92_x_cal"})
                          .Define("sr92y_raw_vec", [&](const TClonesArray &input)
                                  { return sr92y_raw.GetVector(input); },
                                  {"sr92_y_cal"})
                          .Define("src1x_raw_vec", [&](const TClonesArray &input)
                                  { return src1x_raw.GetVector(input); },
                                  {"src1_x_cal"})
                          .Define("src1y_raw_vec", [&](const TClonesArray &input)
                                  { return src1y_raw.GetVector(input); },
                                  {"src1_y_cal"})
                          .Define("src2x_raw_vec", [&](const TClonesArray &input)
                                  { return src2x_raw.GetVector(input); },
                                  {"src2_x_cal"})
                          .Define("src2y_raw_vec", [&](const TClonesArray &input)
                                  { return src2y_raw.GetVector(input); },
                                  {"src2_y_cal"})
                          .Define("sr11x_raw_vec", [&](const TClonesArray &input)
                                  { return sr11x_raw.GetVector(input); },
                                  {"sr11_x_cal"})
                          .Define("sr11y_raw_vec", [&](const TClonesArray &input)
                                  { return sr11y_raw.GetVector(input); },
                                  {"sr11_y_cal"})
                          .Define("sr12x_raw_vec", [&](const TClonesArray &input)
                                  { return sr12x_raw.GetVector(input); },
                                  {"sr12_x_cal"})
                          .Define("sr12y_raw_vec", [&](const TClonesArray &input)
                                  { return sr12y_raw.GetVector(input); },
                                  {"sr12_y_cal"})
                          .Define("src1x_vec", [&](const TClonesArray &input)
                                  { return src1x.GetVector(input); },
                                  {"src1_x"})
                          .Define("src1y_vec", [&](const TClonesArray &input)
                                  { return src1y.GetVector(input); },
                                  {"src1_y"})
                          .Define("src2x_vec", [&](const TClonesArray &input)
                                  { return src2x.GetVector(input); },
                                  {"src2_x"})
                          .Define("src2y_vec", [&](const TClonesArray &input)
                                  { return src2y.GetVector(input); },
                                  {"src2_y"})
                          .Define("src1x_qt_vec", [&](const TClonesArray &input)
                                  { return src1x_qt.GetVector(input); },
                                  {"src1_x_qt"})
                          .Define("src1y_qt_vec", [&](const TClonesArray &input)
                                  { return src1y_qt.GetVector(input); },
                                  {"src1_y_qt"})
                          .Define("src2x_qt_vec", [&](const TClonesArray &input)
                                  { return src2x_qt.GetVector(input); },
                                  {"src2_x_qt"})
                          .Define("src2y_qt_vec", [&](const TClonesArray &input)
                                  { return src2y_qt.GetVector(input); },
                                  {"src2_y_qt"})
                          .Define("src1x_gl_vec", [&](const TClonesArray &input)
                                  { return src1x_gl.GetVector(input); },
                                  {"src1_x_gl"})
                          .Define("src1y_gl_vec", [&](const TClonesArray &input)
                                  { return src1y_gl.GetVector(input); },
                                  {"src1_y_gl"})
                          .Define("src2x_gl_vec", [&](const TClonesArray &input)
                                  { return src2x_gl.GetVector(input); },
                                  {"src2_x_gl"})
                          .Define("src2y_gl_vec", [&](const TClonesArray &input)
                                  { return src2y_gl.GetVector(input); },
                                  {"src2_y_gl"})
                          .Define("activeslit_vec", [&](const TClonesArray &input)
                                  { return activeslit.GetVector(input); },
                                  {"coin_activeslit"});
        //                  .Define("diapad_vec", [&](const TClonesArray &input)
        //                          { return diapad.GetVector(input); },
        //                          {"diapad"});
        output.Foreach([&](const std::vector<art::TTimingChargeData *> &input)
                       { sr91x_raw.FillArrow(input); },
                       {"sr91x_raw_vec"});
        output.Foreach([&](const std::vector<art::TTimingChargeData *> &input)
                       { sr91y_raw.FillArrow(input); },
                       {"sr91y_raw_vec"});
        output.Foreach([&](const std::vector<art::TTimingChargeData *> &input)
                       { sr92x_raw.FillArrow(input); },
                       {"sr92x_raw_vec"});
        output.Foreach([&](const std::vector<art::TTimingChargeData *> &input)
                       { sr92y_raw.FillArrow(input); },
                       {"sr92y_raw_vec"});
        output.Foreach([&](const std::vector<art::TTimingChargeData *> &input)
                       { src1x_raw.FillArrow(input); },
                       {"src1x_raw_vec"});
        output.Foreach([&](const std::vector<art::TTimingChargeData *> &input)
                       { src1y_raw.FillArrow(input); },
                       {"src1y_raw_vec"});
        output.Foreach([&](const std::vector<art::TTimingChargeData *> &input)
                       { src2x_raw.FillArrow(input); },
                       {"src2x_raw_vec"});
        output.Foreach([&](const std::vector<art::TTimingChargeData *> &input)
                       { src2y_raw.FillArrow(input); },
                       {"src2y_raw_vec"});
        output.Foreach([&](const std::vector<art::TTimingChargeData *> &input)
                       { sr11x_raw.FillArrow(input); },
                       {"sr11x_raw_vec"});
        output.Foreach([&](const std::vector<art::TTimingChargeData *> &input)
                       { sr11y_raw.FillArrow(input); },
                       {"sr11y_raw_vec"});
        output.Foreach([&](const std::vector<art::TTimingChargeData *> &input)
                       { sr12x_raw.FillArrow(input); },
                       {"sr12x_raw_vec"});
        output.Foreach([&](const std::vector<art::TTimingChargeData *> &input)
                       { sr12y_raw.FillArrow(input); },
                       {"sr12y_raw_vec"});
        output.Foreach([&](const std::vector<art::TSRPPACPlaneData *> &input)
                       { src1x.FillArrow(input); },
                       {"src1x_vec"});
        output.Foreach([&](const std::vector<art::TSRPPACPlaneData *> &input)
                       { src1y.FillArrow(input); },
                       {"src1y_vec"});
        output.Foreach([&](const std::vector<art::TSRPPACPlaneData *> &input)
                       { src2x.FillArrow(input); },
                       {"src2x_vec"});
        output.Foreach([&](const std::vector<art::TSRPPACPlaneData *> &input)
                       { src2y.FillArrow(input); },
                       {"src2y_vec"});
        output.Foreach([&](const std::vector<art::TSRPPACPlaneData *> &input)
                       { src1x_qt.FillArrow(input); },
                       {"src1x_qt_vec"});
        output.Foreach([&](const std::vector<art::TSRPPACPlaneData *> &input)
                       { src1y_qt.FillArrow(input); },
                       {"src1y_qt_vec"});
        output.Foreach([&](const std::vector<art::TSRPPACPlaneData *> &input)
                       { src2x_qt.FillArrow(input); },
                       {"src2x_qt_vec"});
        output.Foreach([&](const std::vector<art::TSRPPACPlaneData *> &input)
                       { src2y_qt.FillArrow(input); },
                       {"src2y_qt_vec"});
        output.Foreach([&](const std::vector<art::TSRPPACPlaneData *> &input)
                       { src1x_gl.FillArrow(input); },
                       {"src1x_gl_vec"});
        output.Foreach([&](const std::vector<art::TSRPPACPlaneData *> &input)
                       { src1y_gl.FillArrow(input); },
                       {"src1y_gl_vec"});
        output.Foreach([&](const std::vector<art::TSRPPACPlaneData *> &input)
                       { src2x_gl.FillArrow(input); },
                       {"src2x_gl_vec"});
        output.Foreach([&](const std::vector<art::TSRPPACPlaneData *> &input)
                       { src2y_gl.FillArrow(input); },
                       {"src2y_gl_vec"});
        output.Foreach([&](const std::vector<art::TTimingChargeData *> &input)
                       { activeslit.FillArrow(input); },
                       {"activeslit_vec"});
        // output.Foreach([&](const std::vector<art::TTimingChargeData *> &input)
        //                { diapad.FillArrow(input); },
        //                {"diapad_vec"});

        // Finalize the arrays
        arrow::FieldVector fieldVector;
        arrow::ArrayVector arrayVector;
        sr91x_raw.Finalize(fieldVector, arrayVector);
        sr91y_raw.Finalize(fieldVector, arrayVector);
        sr92x_raw.Finalize(fieldVector, arrayVector);
        sr92y_raw.Finalize(fieldVector, arrayVector);
        src1x_raw.Finalize(fieldVector, arrayVector);
        src1y_raw.Finalize(fieldVector, arrayVector);
        src2x_raw.Finalize(fieldVector, arrayVector);
        src2y_raw.Finalize(fieldVector, arrayVector);
        sr11x_raw.Finalize(fieldVector, arrayVector);
        sr11y_raw.Finalize(fieldVector, arrayVector);
        sr12x_raw.Finalize(fieldVector, arrayVector);
        sr12y_raw.Finalize(fieldVector, arrayVector);
        src1x.Finalize(fieldVector, arrayVector);
        src1y.Finalize(fieldVector, arrayVector);
        src2x.Finalize(fieldVector, arrayVector);
        src2y.Finalize(fieldVector, arrayVector);
        src1x_qt.Finalize(fieldVector, arrayVector);
        src1y_qt.Finalize(fieldVector, arrayVector);
        src2x_qt.Finalize(fieldVector, arrayVector);
        src2y_qt.Finalize(fieldVector, arrayVector);
        src1x_gl.Finalize(fieldVector, arrayVector);
        src1y_gl.Finalize(fieldVector, arrayVector);
        src2x_gl.Finalize(fieldVector, arrayVector);
        src2y_gl.Finalize(fieldVector, arrayVector);
        activeslit.Finalize(fieldVector, arrayVector);
        // diapad.Finalize(fieldVector, arrayVector);

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
