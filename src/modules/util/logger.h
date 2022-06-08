/*
 * Copyright (c) 2020-2021. Uniontech Software Ltd. All rights reserved.
 *
 * Author:     Iceyer <me@iceyer.net>
 *
 * Maintainer: Iceyer <me@iceyer.net>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef LINGLONG_BOX_SRC_UTIL_LOGGER_H_
#define LINGLONG_BOX_SRC_UTIL_LOGGER_H_

#include "util.h"

#include <unistd.h>

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <utility>

namespace linglong {
namespace util {
std::string errnoString();
std::string RetErrString(int);

class Logger
{
public:
    enum Level {
        Debug,
        Info,
        Warring,
        Error,
        Fatal,
    };

    explicit Logger(Level l, const char *fn, int line)
        : level(l)
        , function(fn)
        , line(line) {};

    ~Logger()
    {
        std::string prefix;
        if (level < LOGLEVEL) {
            return;
        }
        switch (level) {
        case Debug:
            prefix = "[DBG |";
            std::cout << prefix << getpid() << " | " << function << ":" << line << " ] " << ss.str() << std::endl;
            break;
        case Info:
            prefix = "[IFO |";
            std::cout << "\033[1;96m";
            std::cout << prefix << getpid() << " | " << function << ":" << line << " ] " << ss.str();
            std::cout << "\033[0m" << std::endl;
            break;
        case Warring:
            prefix = "[WAN |";
            std::cout << "\033[1;93m";
            std::cout << prefix << getpid() << " | " << function << ":" << line << " ] " << ss.str();
            std::cout << "\033[0m" << std::endl;
            break;
        case Error:
            prefix = "[ERR |";
            std::cout << "\033[1;31m";
            std::cout << prefix << getpid() << " | " << function << ":" << line << " ] " << ss.str();
            std::cout << "\033[0m" << std::endl;
            break;
        case Fatal:
            prefix = "[FAL |";
            std::cout << "\033[1;91m";
            std::cout << prefix << getpid() << " | " << function << ":" << line << " ] " << ss.str();
            std::cout << "\033[0m" << std::endl;
            exit(-1);
            break;
        }
    }

    template<class T>
    Logger &operator<<(const T &x)
    {
        ss << x << " ";
        return *this;
    }

private:
    static Level LOGLEVEL;
    Level level = Debug;
    const char *function;
    int line;
    std::ostringstream ss;
};
} // namespace util
} // namespace linglong

#define logDbg() (linglong::util::Logger(linglong::util::Logger::Debug, __FUNCTION__, __LINE__))
#define logWan() (linglong::util::Logger(linglong::util::Logger::Warring, __FUNCTION__, __LINE__))
#define logInf() (linglong::util::Logger(linglong::util::Logger::Info, __FUNCTION__, __LINE__))
#define logErr() (linglong::util::Logger(linglong::util::Logger::Error, __FUNCTION__, __LINE__))
#define logFal() (linglong::util::Logger(linglong::util::Logger::Fatal, __FUNCTION__, __LINE__))

#endif /* LINGLONG_BOX_SRC_UTIL_LOGGER_H_ */