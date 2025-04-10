#ifndef __TMWDC_HIT_DATA_BUILDER_HPP__
#define __TMWDC_HIT_DATA_BUILDER_HPP__
#include "TDataBuilderBase.hpp"
#include "TMWDCHitData.h"
#include <TClonesArray.h>
#include <TIterator.h>
#include <arrow/type.h>
#include <parquet/arrow/writer.h>

namespace art
{
    class TMWDCHitDataBuilder;
}

class art::TMWDCHitDataBuilder : public art::TDataBuilderBase
{
public:
    TMWDCHitDataBuilder(const std::string &name);
    ~TMWDCHitDataBuilder() {};

    void FillArrow(const TClonesArray &input) override;

    /**
     * @brief Finalize arrow builders and append fields and arrays
     *
     * @param fields reference to the FieldVector for generating data schema
     * @param arrays reference to the ArrayVector for generating data table
     */
    void Finalize(arrow::FieldVector &fields, arrow::ArrayVector &arrays) override;

    // Arrow Builders

    std::shared_ptr<arrow::FloatBuilder> charge_builder_;
    std::shared_ptr<arrow::ListBuilder> list_charge_builder_;
    std::shared_ptr<arrow::FloatBuilder> timing_builder_;
    std::shared_ptr<arrow::ListBuilder> list_timing_builder_;
    std::shared_ptr<arrow::Int32Builder> id_builder_;
    std::shared_ptr<arrow::ListBuilder> list_id_builder_;
    std::shared_ptr<arrow::FloatBuilder> drift_length_builder_;
    std::shared_ptr<arrow::ListBuilder> list_drift_length_builder_;
};
#endif /*__TTIMING_CHARGE_DATA_BUILDER_HPP__*/