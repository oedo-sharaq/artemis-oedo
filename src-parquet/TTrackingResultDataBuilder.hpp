#ifndef __TTRACKING_RESULT_DATA_BUILDER_HPP__
#define __TTRACKING_RESULT_DATA_BUILDER_HPP__
#include "TDataBuilderBase.hpp"
#include "TMWDCTrackingResult.h"
#include <TClonesArray.h>
#include <TIterator.h>
#include <arrow/type.h>
#include <parquet/arrow/writer.h>

namespace art
{
    class TTrackingResultDataBuilder;
}

class art::TTrackingResultDataBuilder : public art::TDataBuilderBase
{
public:
    TTrackingResultDataBuilder(const std::string &name);
    ~TTrackingResultDataBuilder() {};

    void FillArrow(const TClonesArray &input) override;

    /**
     * @brief Finalize arrow builders and append fields and arrays
     *
     * @param fields reference to the FieldVector for generating data schema
     * @param arrays reference to the ArrayVector for generating data table
     */
    void Finalize(arrow::FieldVector &fields, arrow::ArrayVector &arrays) override;

    // Arrow Builders
    std::shared_ptr<arrow::FloatBuilder> ssr_builder_;
    std::shared_ptr<arrow::FloatBuilder> var0_builder_;
    std::shared_ptr<arrow::FloatBuilder> var1_builder_;
    std::shared_ptr<arrow::FloatBuilder> x_builder_;
    std::shared_ptr<arrow::FloatBuilder> y_builder_;
};
#endif /*__TTIMING_CHARGE_DATA_BUILDER_HPP__*/