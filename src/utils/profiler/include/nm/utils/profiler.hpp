#pragma once

#include "nm/utils/logger.hpp"
#include <cstddef>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace nm {

struct Scope {
    std::string fname;
    std::string loc;
};

inline Scope getScope(const std::string& _fname, const std::string& _loc) {
    Scope s{ _fname, _loc };
    return s;
}

#define GET_CURRENT_SCOPE() getScope(std::string(__FUNCTION__), std::string(__FILE__) + std::string("#") + std::to_string(__LINE__))

class Timer {
private:
    double duration;
    size_t clocks;
    std::clock_t start = std::clock();
    Timer* t = nullptr;

    Timer(Timer* _t) {
        t = _t;
    }

public:

    void stop() {
        if (t == nullptr) return;
        t->start = start;
        clocks = std::clock() - start;
        t->clocks = clocks;
        duration = static_cast<double>(clocks) / CLOCKS_PER_SEC;
        t->duration =  duration;
    }
    Timer() = default;
    ~Timer() {
        (*this).stop();
    }

    Timer(const Timer& _t) {
        duration = _t.duration;
        clocks = _t.clocks;
        start = _t.start;
        t = _t.t;
    }

    static Timer scopeTimer(Timer* root) {
        Timer t{ root };
        t.start = std::clock();
        return t;
    };

    double getDuration() const {
        return duration;
    }

    size_t getClocks() const {
        return clocks;
    }

    size_t getStart() const {
        return start;
    }

    Timer& operator=(const Timer& _timer) {
        duration = _timer.duration;
        clocks = _timer.clocks;
        start = _timer.start;
        t = _timer.t;

        return *this;
    }
};

struct ProfData {
    Timer time;
    Scope scope;
    size_t depth = 0;
    
    friend std::ostream& operator<<(std::ostream& os, const ProfData data) {
        std::string indent = "";
        for (int i = 0; i < data.depth; i++) {
            indent += "-";
        }


        double dispDuration = data.time.getDuration();
        std::string units;
        if (dispDuration <= 1e-4) {
            dispDuration *= 1'000'000.l;
            units = "us";
        } else if (dispDuration <= 1e-1) {
            dispDuration *= 1'000.l;
            units = "ms";
        } else {
            units = "s";
        }

        os << indent << "File: " << data.scope.loc << '\n'
           << indent << "Function: " <<  data.scope.fname << '\n'
           << indent << "Latency: " << dispDuration << " " + units << '\n'
           << indent << "Clocks: " << data.time.getClocks() << '\n';
        return os;
    }
};

class Profiler {
private:
    Profiler* par = nullptr;
    ProfData data;
    Timer localTimer;
    std::vector<ProfData> nested;

public:
    Profiler() = default;
    Profiler(Profiler* _p) {
        par = _p;
    }

    ~Profiler() {
        localTimer.stop();
        if (par == nullptr) return;
        nested.push_back(data);
        par->nested.insert(par->nested.end(), nested.begin(), nested.end());
    }

    Profiler(const Profiler& prof) {
        par = prof.par;
        data = prof.data;
        nested = prof.nested;
        localTimer = prof.localTimer;
    }

    Profiler nest(Scope s) {
        Profiler prof{ this};
        prof.data.scope = s;
        prof.data.depth = data.depth + 1;
        prof.localTimer = Timer::scopeTimer(&prof.data.time); 
        return prof;
    }

    std::vector<ProfData>& getAllData() {
        return nested;
    }

    Profiler& operator=(const Profiler& prof) {
        par = prof.par;
        data = prof.data;
        nested = prof.nested;
        localTimer = prof.localTimer;

        return *this;
    }
};
}  // namespace nm