#include "TMWDCHitDataBuilder.hpp"

art::TMWDCHitDataBuilder::TMWDCHitDataBuilder(const std::string &name) : TDataBuilderBase(name)
{
    charge_builder_ = std::make_shared<arrow::FloatBuilder>(pool_);
    list_charge_builder_ = std::make_shared<arrow::ListBuilder>(pool_, charge_builder_);
    timing_builder_ = std::make_shared<arrow::FloatBuilder>(pool_);
    list_timing_builder_ = std::make_shared<arrow::ListBuilder>(pool_, timing_builder_);
    id_builder_ = std::make_shared<arrow::Int32Builder>(pool_);
    list_id_builder_ = std::make_shared<arrow::ListBuilder>(pool_, id_builder_);
    drift_length_builder_ = std::make_shared<arrow::FloatBuilder>(pool_);
    list_drift_length_builder_ = std::make_shared<arrow::ListBuilder>(pool_, drift_length_builder_);
}

void art::TMWDCHitDataBuilder::FillArrow(const TClonesArray &input)
{
    PARQUET_THROW_NOT_OK(list_charge_builder_->Append());
    PARQUET_THROW_NOT_OK(list_timing_builder_->Append());
    PARQUET_THROW_NOT_OK(list_id_builder_->Append());
    PARQUET_THROW_NOT_OK(list_drift_length_builder_->Append());
    if (!input.GetEntriesFast())
        return;
    TIter next(&input);
    while (auto obj = next())
    {
        auto data = (art::TMWDCHitData *)obj;
        PARQUET_THROW_NOT_OK(charge_builder_->Append(data->GetCharge()));
        PARQUET_THROW_NOT_OK(timing_builder_->Append(data->GetTiming()));
        PARQUET_THROW_NOT_OK(id_builder_->Append(data->GetID()));
        PARQUET_THROW_NOT_OK(drift_length_builder_->Append(data->GetDriftLength()));
    }
}

void art::TMWDCHitDataBuilder::Finalize(arrow::FieldVector &fields, arrow::ArrayVector &arrays)
{

    std::shared_ptr<arrow::Array> list_charge_array;
    std::shared_ptr<arrow::Array> list_timing_array;
    std::shared_ptr<arrow::Array> list_id_array;
    std::shared_ptr<arrow::Array> list_drift_length_array;
    PARQUET_THROW_NOT_OK(list_charge_builder_->Finish(&list_charge_array));
    PARQUET_THROW_NOT_OK(list_timing_builder_->Finish(&list_timing_array));
    PARQUET_THROW_NOT_OK(list_id_builder_->Finish(&list_id_array));
    PARQUET_THROW_NOT_OK(list_drift_length_builder_->Finish(&list_drift_length_array));

    fields.emplace_back(arrow::field(name_ + "_charge", arrow::list(arrow::float32())));
    fields.emplace_back(arrow::field(name_ + "_timing", arrow::list(arrow::float32())));
    fields.emplace_back(arrow::field(name_ + "_id", arrow::list(arrow::int32())));
    fields.emplace_back(arrow::field(name_ + "_dlength", arrow::list(arrow::float32())));
    arrays.emplace_back(list_charge_array);
    arrays.emplace_back(list_timing_array);
    arrays.emplace_back(list_id_array);
    arrays.emplace_back(list_drift_length_array);
    return;
}
