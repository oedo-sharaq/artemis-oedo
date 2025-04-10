#ifndef __TEVENT_HEADER_DATA_BUILDER_HPP__
#define __TEVENT_HEADER_DATA_BUILDER_HPP__
#include "TDataBuilderBase.hpp"
#include "TEventHeader.h"
#include <TClonesArray.h>
#include <TIterator.h>
#include <arrow/type.h>
#include <parquet/arrow/writer.h>

namespace art
{
    class TEventHeaderDataBuilder;
}

class art::TEventHeaderDataBuilder : public art::TDataBuilderBase
{
public:
    TEventHeaderDataBuilder(const std::string &name);
    ~TEventHeaderDataBuilder() {};

    void FillArrow(const TClonesArray &input) override {};
    void FillEventHeader(art::TEventHeader &input);

    /**
     * @brief Finalize arrow builders and append fields and arrays
     *
     * @param fields reference to the FieldVector for generating data schema
     * @param arrays reference to the ArrayVector for generating data table
     */
    void Finalize(arrow::FieldVector &fields, arrow::ArrayVector &arrays) override;

    // Arrow Builders
    std::shared_ptr<arrow::Int32Builder> run_num_builder_;
    std::shared_ptr<arrow::Int64Builder> event_num_builder_;
    std::shared_ptr<arrow::Int64Builder> ts_builder_;

};
#endif /*__TEVENT_HEADER_DATA_BUILDER_HPP__*/
