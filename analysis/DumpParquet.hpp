/**
 * @file DumpParquet.hpp
 * @author Rin Yokoyama (yokoyama@cns.s.u-tokyo.ac.jp)
 * @brief Definition of data builder classes for artemis objects
 * @version 0.1
 * @date 2024-01-17
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef __DUMP_PARQUET_HPP__
#define __DUMP_PARQUET_HPP__
#include "TClonesArray.h"
#include "TEventHeader.h"
#include "TTimingChargeData.h"
#include "TSRPPACPlaneData.h"
#include <arrow/api.h>
#include <arrow/io/api.h>
#include <arrow/pretty_print.h>
#include <arrow/record_batch.h>
#include <arrow/type.h>
#include <parquet/arrow/writer.h>
#include <vector>

/**
 * @brief Data builder base class for an artemis object
 *
 */
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

/**
 * @brief Data builder class for art::TTimingChargeData objects
 *
 */
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

    // A function to loop over TClonesArray and fill object to a vector
    const std::vector<art::TTimingChargeData *> GetVector(const TClonesArray &input)
    {
        std::vector<art::TTimingChargeData *> vec;
		if (!input.GetEntriesFast())
			return vec;
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

    /**
     * @brief Finalize arrow builders and append fields and arrays
     *
     * @param fields reference to the FieldVector for generating data schema
     * @param arrays reference to the ArrayVector for generating data table
     */
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

/**
 * @brief Data builder class for art::TSRPPACPlaneData objects
 *
 */
class TSRPPACPlaneDataBuilder : public TDataBuilderBase
{
public:
    TSRPPACPlaneDataBuilder(std::string name) : TDataBuilderBase(name)
    {
        position_builder_ = std::make_shared<arrow::FloatBuilder>(pool_);
        list_position_builder_ = std::make_shared<arrow::ListBuilder>(pool_, position_builder_);
    }
    ~TSRPPACPlaneDataBuilder() {}

    // A function to loop over TClonesArray and fill object to a vector
    const std::vector<art::TSRPPACPlaneData *> GetVector(const TClonesArray &input)
    {
        std::vector<art::TSRPPACPlaneData *> vec;
		if (!input.GetEntriesFast())
			return vec;
        TIter next(&input);
        TObject *obj;
        while ((obj = next()))
        {
            vec.emplace_back((art::TSRPPACPlaneData *)obj);
        }
        return vec;
    };

    void FillArrow(const std::vector<art::TSRPPACPlaneData *> &input)
    {
        PARQUET_THROW_NOT_OK(list_position_builder_->Append());
        for (const auto data : input)
        {
            PARQUET_THROW_NOT_OK(position_builder_->Append(data->GetPosition()));
        }
    };

    /**
     * @brief Finalize arrow builders and append fields and arrays
     *
     * @param fields reference to the FieldVector for generating data schema
     * @param arrays reference to the ArrayVector for generating data table
     */
    void Finalize(arrow::FieldVector &fields, arrow::ArrayVector &arrays)
    {
        std::shared_ptr<arrow::Array> list_position_array;
        PARQUET_THROW_NOT_OK(list_position_builder_->Finish(&list_position_array));

        fields.emplace_back(arrow::field(name_ + "_position", arrow::list(arrow::float32())));
        arrays.emplace_back(list_position_array);
    }

    // Arrow Builders
    std::shared_ptr<arrow::FloatBuilder> position_builder_;
    std::shared_ptr<arrow::ListBuilder> list_position_builder_;
};
#endif //__DUMP_PARQUET_HPP__
