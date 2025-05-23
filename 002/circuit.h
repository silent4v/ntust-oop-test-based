#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstdarg>
#define print_f(...) stq::print_f_impl(__VA_ARGS__)

namespace stq {
void print_f_impl(const char* fmt, ...) {
    constexpr size_t BUF_SIZE = 1024;
    char buffer[BUF_SIZE];

    va_list args;
    va_start(args, fmt);
    std::vsnprintf(buffer, BUF_SIZE, fmt, args);
    va_end(args);

    std::cout << buffer;
}
}

namespace OnlineJudge {
/**
 * @brief Function pointer type for querying signal/gate state with a context pointer
 *
 * This typedef defines a function pointer type that can be used to query the state
 * of a signal or logic gate at a specific time point, with an optional context pointer.
 *
 * @param context Void pointer to the object context (Signal or LogicGate)
 * @param t Time point to query the state
 * @return bool State of the signal or gate at the given time point
 */
typedef bool (*QueryFunc)(void* context, float t);

/**
 * @brief Represents a digital signal with a time-based history of boolean values
 *
 * The Signal class allows setting and querying signal states at specific time points.
 * It maintains a map of time points and their corresponding boolean values.
 */
class Signal {
public:
    std::string name;
    std::map<float, bool> history; // Time-mapped values, sorted by time

    /**
     * @brief Constructor for Signal
     *
     * Initializes a signal with a given name and sets default initial state to false at time 0
     *
     * @param name Name of the signal
     */
    Signal(const std::string& name)
        : name(name) {
        history[0.0f] = false; // Default false state at time 0
    }

    /**
     * @brief Query the signal's state at a specific time point
     *
     * Finds the most recent state of the signal up to the given time point
     *
     * @param t Time point to query
     * @return bool Signal's state at the given time point
     */
    bool query(float t) {
        auto it = history.begin();
        // Find first entry with key greater than t
        while (it != history.end() && it->first <= t) {
            ++it;
        }
        // If iterator is at the beginning, no entries exist before t
        if (it == history.begin()) {
            return false;
        }
        --it;
        return it->second;
    }

    /**
     * @brief Set the signal's state at a specific time point
     *
     * @param t Time point to set the signal state
     * @param value Boolean state to set
     */
    void set(float t, bool value) {
        history[t] = value;
    }
};

/**
 * @brief Represents a digital logic gate with various logical operations
 *
 * LogicGate supports AND, OR, NOT, NAND, NOR, XOR, and XNOR gate types
 * with configurable propagation delays
 */
class LogicGate {
public:
    // Static map to store propagation delays for different gate types
    static std::map<std::string, float> propagation_delays;

    std::string name;
    std::string gate_type;

    // Function pointers and context for input pins
    QueryFunc pin0;
    void* pin0_context;
    QueryFunc pin1;
    void* pin1_context;

    // Function pointer for logical operation
    bool (*logic)(bool, bool);

    /**
     * @brief Constructor for LogicGate
     *
     * Initializes a logic gate with a name and type, setting default propagation delay
     * and mapping the appropriate logical operation
     *
     * @param name Name of the logic gate
     * @param gate_type Type of logic gate (AND, OR, NOT, etc.)
     */
    LogicGate(const std::string& name, const std::string& gate_type)
        : name(name)
        , gate_type(gate_type)
        , pin0(nullptr)
        , pin0_context(nullptr)
        , pin1(nullptr)
        , pin1_context(nullptr) {
        // Set default propagation delay to 3.0 if not specified
        if (propagation_delays.find(gate_type) == propagation_delays.end()) {
            propagation_delays[gate_type] = 3.0f;
        }
        // Map gate types to their corresponding logical operations
        if (gate_type == "AND") {
            logic = &LogicGate::and_gate;
        } else if (gate_type == "OR") {
            logic = &LogicGate::or_gate;
        } else if (gate_type == "NOT") {
            logic = &LogicGate::not_gate;
        } else if (gate_type == "NAND") {
            logic = &LogicGate::nand_gate;
        } else if (gate_type == "NOR") {
            logic = &LogicGate::nor_gate;
        } else if (gate_type == "XOR") {
            logic = &LogicGate::xor_gate;
        } else if (gate_type == "XNOR") {
            logic = &LogicGate::xnor_gate;
        }
    }

    /**
     * @brief Bind a function to pin0 with its context
     *
     * @param func Query function for pin0
     * @param context Context pointer for the query function
     */
    void bind_pin0(QueryFunc func, void* context) {
        pin0 = func;
        pin0_context = context;
    }

    /**
     * @brief Bind a function to pin1 with its context
     *
     * @param func Query function for pin1
     * @param context Context pointer for the query function
     */
    void bind_pin1(QueryFunc func, void* context) {
        pin1 = func;
        pin1_context = context;
    }

    /**
     * @brief Query the gate's output state at a specific time point
     *
     * Calculates the gate's output considering propagation delay and input states
     *
     * @param t Time point to query
     * @return bool Gate's output state at the given time point
     */
    bool query(float t) {
        if (t < 0)
            return false; // Negative time not supported

        float delay = propagation_delays[gate_type];
        if (gate_type == "NOT") {
            if (!pin0)
                return false;
            bool input = pin0(pin0_context, t - delay);
            return logic(input, false); // NOT gate ignores second parameter
        } else {
            if (!pin0 || !pin1)
                return false;
            bool input0 = pin0(pin0_context, t - delay);
            bool input1 = pin1(pin1_context, t - delay);
            return logic(input0, input1);
        }
    }

    /**
     * @brief Set propagation delay for a specific gate type
     *
     * @param gate_type Type of logic gate
     * @param delay Propagation delay value
     */
    static void set_propagation_delay(const std::string& gate_type, float delay) {
        propagation_delays[gate_type] = delay;
    }

private:
    // Static methods implementing logical operations for different gate types
    static bool and_gate(bool a, bool b) {
        return a && b;
    }
    static bool or_gate(bool a, bool b) {
        return a || b;
    }
    static bool not_gate(bool a, bool /*b*/) {
        return !a;
    }
    static bool nand_gate(bool a, bool b) {
        return !(a && b);
    }
    static bool nor_gate(bool a, bool b) {
        return !(a || b);
    }
    static bool xor_gate(bool a, bool b) {
        return a != b;
    }
    static bool xnor_gate(bool a, bool b) {
        return a == b;
    }
};

// Static member initialization for propagation delays
std::map<std::string, float> LogicGate::propagation_delays;

/**
 * @brief Helper function to query a Signal using function pointer mechanism
 *
 * @param context Pointer to Signal object
 * @param t Time point to query
 * @return bool Signal's state at the given time point
 */
bool signal_query(void* context, float t) {
    Signal* sig = static_cast<Signal*>(context);
    return sig->query(t);
}

/**
 * @brief Helper function to query a LogicGate using function pointer mechanism
 *
 * @param context Pointer to LogicGate object
 * @param t Time point to query
 * @return bool LogicGate's output state at the given time point
 */
bool gate_query(void* context, float t) {
    LogicGate* gate = static_cast<LogicGate*>(context);
    return gate->query(t);
}

// Global containers to store Signals and LogicGates using raw pointers
std::map<std::string, Signal*> signal_list;
std::map<std::string, LogicGate*> gate_list;

/**
 * Main program for logic circuit simulation
 *
 * Provides an interactive command-line interface to:
 * - Add signals and logic gates
 * - Set signal values and propagation delays
 * - Bind signals and gates
 * - Query signal and gate states
 *
 */
int main() {
    print_f("%d, %s, %.5f", 100, "1234 5678", 15.0);

    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "Add") {
            // Add a new signal or logic gate
            std::string subcommand, name;
            if (!(iss >> subcommand >> name)) {
                continue;
            }
            if (subcommand == "signal") {
                signal_list[name] = new Signal(name);
            } else if (
                subcommand == "AND" || subcommand == "OR" || subcommand == "NOT" || subcommand == "NAND" || subcommand == "NOR" || subcommand == "XOR" ||
                subcommand == "XNOR")
            {
                gate_list[name] = new LogicGate(name, subcommand);
            } else {
                continue;
            }
        } else if (command == "Set") {
            // Set propagation delays or signal values
            std::string subcommand, nameOrGate;
            float t;
            if (!(iss >> subcommand)) {
                continue;
            }
            if (subcommand == "propagation") {
                std::string gate_type;
                float delay;
                if (!(iss >> gate_type >> delay)) {
                    continue;
                }
                // Validate gate type
                if (gate_type != "AND" && gate_type != "OR" && gate_type != "NOT" && gate_type != "NAND" && gate_type != "NOR" && gate_type != "XOR" &&
                    gate_type != "XNOR") {
                    continue;
                }
                LogicGate::set_propagation_delay(gate_type, delay);
            } else {
                // Set signal value
                std::string value_str;
                if (!(iss >> value_str >> t)) {
                    continue;
                }
                bool value = (value_str == "True");
                if (signal_list.find(subcommand) != signal_list.end()) {
                    signal_list[subcommand]->set(t, value);
                } else {
                    continue;
                }
            }
        } else if (command == "Bind") {
            // Bind signals or gates to logic gate inputs
            std::string output_name, input_name;
            int pin_id;
            if (!(iss >> output_name >> input_name >> pin_id)) {
                continue;
            }
            if (gate_list.find(input_name) != gate_list.end()) {
                LogicGate* input_gate = gate_list[input_name];
                // Check if output is a signal or gate
                if (signal_list.find(output_name) != signal_list.end()) {
                    Signal* sig = signal_list[output_name];
                    if (pin_id == 0) {
                        input_gate->bind_pin0(signal_query, sig);
                    } else if (pin_id == 1) {
                        input_gate->bind_pin1(signal_query, sig);
                    } else {
                        continue;
                    }
                } else if (gate_list.find(output_name) != gate_list.end()) {
                    LogicGate* out_gate = gate_list[output_name];
                    if (pin_id == 0) {
                        input_gate->bind_pin0(gate_query, out_gate);
                    } else if (pin_id == 1) {
                        input_gate->bind_pin1(gate_query, out_gate);
                    } else {
                        continue;
                    }
                } else {
                    continue;
                }
            } else {
                continue;
            }
        } else if (command == "Query") {
            // Query signal or gate state at a specific time
            std::string name;
            float t;
            if (!(iss >> name >> t)) {
                continue;
            }
            if (gate_list.find(name) != gate_list.end()) {
                bool result = gate_list[name]->query(t);
                std::cout << (result ? "True" : "False") << std::endl;
            } else if (signal_list.find(name) != signal_list.end()) {
                bool result = signal_list[name]->query(t);
                std::cout << (result ? "True" : "False") << std::endl;
            } else {
                continue;
            }
        } else if (command == "EXIT") {
            break;
        }
    }

    return 0;
}
} // namespace OnlineJudge