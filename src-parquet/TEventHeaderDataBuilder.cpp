#include "TEventHeaderDataBuilder.hpp"

art::TEventHeaderDataBuilder::TEventHeaderDataBuilder(const std::string &name) : TDataBuilderBase(name)
{
    run_num_builder_ = std::make_shared<arrow::Int32Builder>(pool_);
    event_num_builder_ = std::make_shared<arrow::Int64Builder>(pool_);
    ts_builder_ = std::make_shared<arrow::Int64Builder>(pool_);
    use_clonesarray_ = false;
}

void art::TEventHeaderDataBuilder::FillEventHeader(art::TEventHeader &input)
{
    PARQUET_THROW_NOT_OK(run_num_builder_->Append(input.GetRunNumber()));
    PARQUET_THROW_NOT_OK(event_num_builder_->Append(input.GetEventNumber()));
    PARQUET_THROW_NOT_OK(ts_builder_->Append(input.GetTimestamp()));
}

void art::TEventHeaderDataBuilder::Finalize(arrow::FieldVector &fields, arrow::ArrayVector &arrays)
{
    std::shared_ptr<arrow::Array> run_num_array;
    std::shared_ptr<arrow::Array> event_num_array;
    std::shared_ptr<arrow::Array> ts_array;
    PARQUET_THROW_NOT_OK(run_num_builder_->Finish(&run_num_array));
    PARQUET_THROW_NOT_OK(event_num_builder_->Finish(&event_num_array));
    PARQUET_THROW_NOT_OK(ts_builder_->Finish(&ts_array));

    fields.emplace_back(arrow::field("run_num", arrow::int32()));
    fields.emplace_back(arrow::field("event_num", arrow::int64()));
    fields.emplace_back(arrow::field("ts", arrow::int64()));
    arrays.emplace_back(run_num_array);
    arrays.emplace_back(event_num_array);
    arrays.emplace_back(ts_array);
    return;
}
