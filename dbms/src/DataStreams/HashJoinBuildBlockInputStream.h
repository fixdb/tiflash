#pragma once

#include <DataStreams/IProfilingBlockInputStream.h>
#include <Interpreters/ExpressionAnalyzer.h>
#include <Interpreters/Join.h>

namespace DB
{

class HashJoinBuildBlockInputStream : public IProfilingBlockInputStream
{
public:
    HashJoinBuildBlockInputStream(const BlockInputStreamPtr & input, JoinPtr join_,size_t stream_index_, const std::shared_ptr<LogWithPrefix> & log_ = nullptr)
        :stream_index(stream_index_), log(getLogWithPrefix(log_, getName()))
    {
        children.push_back(input);
        join = join_;
    }
    String getName() const override { return "HashJoinBuildBlockInputStream"; }
    Block getHeader() const override { return children.back()->getHeader(); }

protected:
    Block readImpl() override;

private:
    JoinPtr join;
    size_t stream_index;
    const std::shared_ptr<LogWithPrefix> log;
};

} // namespace DB