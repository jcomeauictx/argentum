#include "options.h"
#include "util.h"
#include <stdexcept>
#include <boost/thread.hpp>

static std::unique_ptr<ArgGetter> Args;

struct DefaultGetter : public ArgGetter {
    virtual bool GetBool(const std::string& arg, bool def) {
        return ::GetBoolArg(arg, def);
    }
    virtual std::vector<std::string> GetMultiArgs(const std::string& arg) {
        if (!mapMultiArgs.count(arg))
            return std::vector<std::string>();

        return mapMultiArgs[arg];
    }
    virtual int64_t GetArg(const std::string& strArg, int64_t nDefault) {
        return ::GetArg(strArg, nDefault);
    }
};

Opt::Opt() {
    if (!bool(Args.get()))
        Args.reset(new DefaultGetter());
}

bool Opt::IsStealthMode() {
    return Args->GetBool("-stealth-mode", false);
}

bool Opt::HidePlatform() {
    return Args->GetBool("-hide-platform", false);
}

std::vector<std::string> Opt::UAComment(bool validate) {
    std::vector<std::string> uacomments = Args->GetMultiArgs("-uacomment");
    if (!validate)
        return uacomments;

    typedef std::vector<std::string>::const_iterator auto_;
    for (auto_ c = uacomments.begin(); c != uacomments.end(); ++c) {
        size_t pos = c->find_first_of("/:()");
        if (pos == std::string::npos)
            continue;
        std::stringstream ss;
        ss << "-uacomment '" << *c << "' contains the reserved character '"
            << c->at(pos) << "'.The following characters are reserved: / : ( )";
        throw std::invalid_argument(ss.str());
    }

    return uacomments;
}

int Opt::ScriptCheckThreads() {
    // -par=0 means autodetect, but nScriptCheckThreads==0 means no concurrency
    int nScriptCheckThreads = Args->GetArg("-par", DEFAULT_SCRIPTCHECK_THREADS);
    if (nScriptCheckThreads <= 0)
        nScriptCheckThreads += boost::thread::hardware_concurrency();
    if (nScriptCheckThreads <= 1)
        nScriptCheckThreads = 0;
    else if (nScriptCheckThreads > MAX_SCRIPTCHECK_THREADS)
        nScriptCheckThreads = MAX_SCRIPTCHECK_THREADS;
    return nScriptCheckThreads;
}

int64_t Opt::CheckpointDays() {
    int64_t def = DEFAULT_CHECKPOINT_DAYS * std::max(1, ScriptCheckThreads());
    return std::max(int64_t(1), Args->GetArg("-checkpoint-days", def));
}

std::unique_ptr<ArgReset> SetDummyArgGetter(std::unique_ptr<ArgGetter> getter) {
    Args.reset(getter.release());
    return std::unique_ptr<ArgReset>(new ArgReset);
}

ArgReset::~ArgReset() {
    Args.reset(new DefaultGetter());
}

