#ifndef __DUMP_PARQUET_HPP__
#define __DUMP_PARQUET_HPP__
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

class TDataBuilderBase
{
public:
    TDataBuilderBase(std::string name)
    {
        pool_ = arrow::default_memory_pool();
        name_ = name;
    }
    virtual ~TDataBuilderBase() {}

protected:
    arrow::MemoryPool *pool_;
    std::string name_;
};

class TTimingChargeDataBuilder : public TDataBuilderBase
{
public:
    TTimingChargeDataBuilder(std::string name) : TDataBuilderBase(name)
    {
        tot_builder_ = std::make_shared<arrow::FloatBuilder>(pool_);
        list_tot_builder_ = std::make_shared<arrow::ListBuilder>(pool_, tot_builder_);
        timing_builder_ = std::make_shared<arrow::FloatBuilder>(pool_);
        list_timing_builder_ = std::make_shared<arrow::ListBuilder>(pool_, timing_builder_);
        id_builder_ = std::make_shared<arrow::Int32Builder>(pool_);
        list_id_builder_ = std::make_shared<arrow::ListBuilder>(pool_, id_builder_);
    }
    ~TTimingChargeDataBuilder() {}

    // A function to loop over TClonesArray and fill a data by getfunc
    const std::vector<art::TTimingChargeData *> GetVector(const TClonesArray &input)
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

    void FillArrow(const std::vector<art::TTimingChargeData *> &input)
    {
        PARQUET_THROW_NOT_OK(list_tot_builder_->Append());
        PARQUET_THROW_NOT_OK(list_timing_builder_->Append());
        PARQUET_THROW_NOT_OK(list_id_builder_->Append());
        for (const auto data : input)
        {
            PARQUET_THROW_NOT_OK(tot_builder_->Append(data->GetCharge()));
            PARQUET_THROW_NOT_OK(timing_builder_->Append(data->GetTiming()));
            PARQUET_THROW_NOT_OK(id_builder_->Append(data->GetID()));
        }
    };

    void Finalize(arrow::FieldVector &fields, arrow::ArrayVector &arrays)
    {
        std::shared_ptr<arrow::Array> list_tot_array;
        std::shared_ptr<arrow::Array> list_timing_array;
        std::shared_ptr<arrow::Array> list_id_array;
        PARQUET_THROW_NOT_OK(list_tot_builder_->Finish(&list_tot_array));
        PARQUET_THROW_NOT_OK(list_timing_builder_->Finish(&list_timing_array));
        PARQUET_THROW_NOT_OK(list_id_builder_->Finish(&list_id_array));

        fields.emplace_back(arrow::field(name_ + "_tot", arrow::list(arrow::float32())));
        fields.emplace_back(arrow::field(name_ + "_timing", arrow::list(arrow::float32())));
        fields.emplace_back(arrow::field(name_ + "_id", arrow::list(arrow::int32())));
        arrays.emplace_back(list_tot_array);
        arrays.emplace_back(list_timing_array);
        arrays.emplace_back(list_id_array);
    }

    // Arrow Builders
    std::shared_ptr<arrow::FloatBuilder> tot_builder_;
    std::shared_ptr<arrow::ListBuilder> list_tot_builder_;
    std::shared_ptr<arrow::FloatBuilder> timing_builder_;
    std::shared_ptr<arrow::ListBuilder> list_timing_builder_;
    std::shared_ptr<arrow::Int32Builder> id_builder_;
    std::shared_ptr<arrow::ListBuilder> list_id_builder_;
};

#endif //__DUMP_PARQUET_HPP__