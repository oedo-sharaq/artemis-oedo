#include "TTrackingResultDataBuilder.hpp"

art::TTrackingResultDataBuilder::TTrackingResultDataBuilder(const std::string &name) : TDataBuilderBase(name)
{
    ssr_builder_ = std::make_shared<arrow::FloatBuilder>(pool_);
    var0_builder_ = std::make_shared<arrow::FloatBuilder>(pool_);
    var1_builder_ = std::make_shared<arrow::FloatBuilder>(pool_);
    x_builder_ = std::make_shared<arrow::FloatBuilder>(pool_);
    y_builder_ = std::make_shared<arrow::FloatBuilder>(pool_);
}

void art::TTrackingResultDataBuilder::FillArrow(const TClonesArray &input)
{
    if (!input.GetEntriesFast())
    {
        PARQUET_THROW_NOT_OK(ssr_builder_->AppendNull());
        PARQUET_THROW_NOT_OK(var0_builder_->AppendNull());
        PARQUET_THROW_NOT_OK(var1_builder_->AppendNull());
        PARQUET_THROW_NOT_OK(x_builder_->AppendNull());
        PARQUET_THROW_NOT_OK(y_builder_->AppendNull());
        return;
    }
    auto data = (art::TMWDCTrackingResult *)input.At(0);
    PARQUET_THROW_NOT_OK(ssr_builder_->Append(data->GetSSR()));
    PARQUET_THROW_NOT_OK(var0_builder_->Append(data->GetVar(0)));
    PARQUET_THROW_NOT_OK(var1_builder_->Append(data->GetVar(1)));
    PARQUET_THROW_NOT_OK(x_builder_->Append(data->GetTrack()->GetX()));
    PARQUET_THROW_NOT_OK(y_builder_->Append(data->GetTrack()->GetY()));
}

void art::TTrackingResultDataBuilder::Finalize(arrow::FieldVector &fields, arrow::ArrayVector &arrays)
{
    std::shared_ptr<arrow::Array> ssr_array;
    std::shared_ptr<arrow::Array> var0_array;
    std::shared_ptr<arrow::Array> var1_array;
    std::shared_ptr<arrow::Array> x_array;
    std::shared_ptr<arrow::Array> y_array;
    PARQUET_THROW_NOT_OK(ssr_builder_->Finish(&ssr_array));
    PARQUET_THROW_NOT_OK(var0_builder_->Finish(&var0_array));
    PARQUET_THROW_NOT_OK(var1_builder_->Finish(&var1_array));
    PARQUET_THROW_NOT_OK(x_builder_->Finish(&x_array));
    PARQUET_THROW_NOT_OK(y_builder_->Finish(&y_array));

    fields.emplace_back(arrow::field(name_ + "_SSR", arrow::float32()));
    fields.emplace_back(arrow::field(name_ + "_Var0", arrow::float32()));
    fields.emplace_back(arrow::field(name_ + "_Var1", arrow::float32()));
    fields.emplace_back(arrow::field(name_ + "_X", arrow::float32()));
    fields.emplace_back(arrow::field(name_ + "_Y", arrow::float32()));
    arrays.emplace_back(ssr_array);
    arrays.emplace_back(var0_array);
    arrays.emplace_back(var1_array);
    arrays.emplace_back(x_array);
    arrays.emplace_back(y_array);
    return;
}
