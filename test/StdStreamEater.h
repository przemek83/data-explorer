#pragma once

#include <iostream>
#include <sstream>

class StdStreamEater
{
public:
    explicit StdStreamEater(std::ostream& stream);
    ~StdStreamEater();

    std::string getOutput() const;

private:
    std::ostream& stream_;

    std::streambuf* stdBuffer_{stream_.rdbuf()};
    std::ostringstream fakeOutput_;
};
