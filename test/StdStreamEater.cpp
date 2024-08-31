#include "StdStreamEater.h"

StdStreamEater::StdStreamEater(std::ostream& stream) : stream_(stream)
{
    stream_.rdbuf(fakeOutput_.rdbuf());
}

StdStreamEater::~StdStreamEater() { stream_.rdbuf(stdBuffer_); }

std::string StdStreamEater::getOutput() const { return fakeOutput_.str(); }
