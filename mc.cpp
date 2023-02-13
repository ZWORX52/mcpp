#include <chrono>
#include <ctime>
#include <fmt/chrono.h>
#include <fmt/core.h>
#include <iostream>
#include <ranges>
#include <toml++/toml.h>

namespace config {
bool show_date = true;
bool debug = false;

void load(const std::string &filename);
};  // namespace config

namespace ui {
int sections = 0;

void start_section(const std::string &section);
void end_section(const std::string &section);
void log(const std::string &msg);
void err(const std::string &msg);
inline void debug(const std::string &msg) {
    if (config::debug)
        ui::log(msg);
}
};  // namespace ui

int main() {
    ui::debug("initializing");
    config::load("config.toml");
}

namespace config {
void load(const std::string &filename) {
    toml::table table;
    try {
        table = toml::parse_file(filename);
    } catch (const toml::parse_error &e) {
        ui::err(fmt::format("failed to load config\n{}", e.description()));
    }

    if (table.contains("ui")) {
        toml::node_view config_ui = table["ui"];

        if (config_ui["debug"])
            debug = config_ui["debug"].as_boolean();
        else
            ui::debug("using default value of false for key debug");

        if (config::debug)
            ui::start_section("config::load");
        if (config_ui["show_date"])
            show_date = config_ui["show_date"].as_boolean();
        else
            ui::debug("using default value of true for key show_date");
    } else {
        ui::err(fmt::format("failed to load config: missing required section [ui]"));
    }
    if (config::debug) {
        std::stringstream ss;
        ss << table;
        ui::log(fmt::format("config:\n{}", ss.str()));
    }
    if (config::debug)
        ui::end_section("config::load");
}
};  // namespace config

namespace ui {
void show_log_prefix() {
    std::cout << '[';
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm time_tm = *std::localtime(&now_time_t);
    if (config::show_date) {
        std::cout << fmt::format("{0:%Y}-{0:%m}-{0:%d} ", time_tm);
    }
    std::cout << fmt::format("{0:%H}:{0:%M}:{0:%S}] ", time_tm);
    for (int i = 0; i < sections * 4; i++)
        std::cout << ' ';
}

void start_section(const std::string &section) {
    show_log_prefix();
    std::cout << "begin " << section << "\n";
    sections++;
}

void end_section(const std::string &section) {
    sections--;
    show_log_prefix();
    std::cout << "end " << section << "\n";
}

void log(const std::string &msg) {
    show_log_prefix();
    for (const char ch : msg) {
        std::cout << ch;
        if (ch == '\n') {
            show_log_prefix();
            std::cout << "    ";
        }
    }
    std::cout << '\n';
}

void err(const std::string &msg) {
    std::cout << "\033[38;5;1m";
    ui::log(msg);
    std::cout << "\033[0m";
}
};  // namespace ui
